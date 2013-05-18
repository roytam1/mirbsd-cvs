/* $MirOS: ports/infrastructure/pkgtools/add/perform.c,v 1.28 2009/12/14 19:20:02 bsiegert Exp $ */
/* $OpenBSD: perform.c,v 1.32 2003/08/21 20:24:56 espie Exp $	*/

/*
 * FreeBSD install - a package for the installation and maintainance
 * of non-core utilities.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * Jordan K. Hubbard
 * 18 July 1993
 *
 * This is the main body of the add module.
 */

#include <err.h>
#include "lib.h"
#include "add.h"

#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>
#include <errno.h>

__RCSID("$MirOS: ports/infrastructure/pkgtools/add/perform.c,v 1.28 2009/12/14 19:20:02 bsiegert Exp $");

static int pkg_do(char *);
static int sanity_check(char *);
static int install_dep_local(char *, char *);
static int install_dep_ftp(char *, char *);
#if 1
#define register_dep_ register_dep
#else
#define register_dep(a,b) do { 						\
		fprintf(stderr, "\n\tregistering dependency <%s> for"	\
		    " <%s> on %d\n", (b), (a), __LINE__);		\
		register_dep_((a), (b));				\
	} while (0)
#endif
static void register_dep_(char *, char *);
static void write_deps(void);

static char LogDir[FILENAME_MAX];
static int zapLogDir;          /* Should we delete LogDir? */
static char *PkgDeps = NULL;
static const char *dbdir = NULL;

int
pkg_perform(char **pkgs)
{
    int i, err_cnt = 0;

    signal(SIGINT, cleanup);
    signal(SIGHUP, cleanup);

    if (AddMode == SLAVE)
	err_cnt = pkg_do(NULL);
    else {
	for (i = 0; pkgs[i]; i++)
	    err_cnt += pkg_do(pkgs[i]);
    }
    return err_cnt;
}

static package_t Plist;
static char *Home;

/* called to see if pkg is already installed as some other version */
/* note found version in "note" */
static int
check_if_installed(const char *found, char *note, int len)
{
    strlcpy(note, found, len);
    return 0;
}

/*
 * This is seriously ugly code following.  Written very fast!
 * [And subsequently made even worse..  Sigh!  This code was just born
 * to be hacked, I guess.. :) -jkh]
 */
static int
pkg_do(char *pkg)
{
    char pkg_fullname[FILENAME_MAX];
    char playpen[FILENAME_MAX];
    char extract_contents[FILENAME_MAX];
    char solve_deps[FILENAME_MAX+50];
    char installed[FILENAME_MAX];
    char *where_to, *tmp, *extract;
    FILE *cfile;
    int code;
    plist_t *p;
    struct stat sb;

    set_pkg(pkg);
    code = 0;
    zapLogDir = 0;
    LogDir[0] = '\0';
    strlcpy(playpen, FirstPen, sizeof(playpen));
    dbdir = (tmp = getenv(PKG_DBDIR)) ? tmp : DEF_LOG_DIR;

    snprintf(solve_deps, sizeof solve_deps, "pkg%s dependencies solve %s",
	Verbose ? " -v": "", CONTENTS_FNAME);
    if (Prefix)
    	setenv("PKG_PREFIX", Prefix, 1);
    else
    	unsetenv("PKG_PREFIX");
    /* Are we coming in for a second pass, everything already extracted? */
    /* (Slave mode) */
    if (!pkg) {
	fgets(playpen, FILENAME_MAX, stdin);
	playpen[strlen(playpen) - 1] = '\0'; /* pesky newline! */
	if (chdir(playpen) == -1) {
	    pwarnx("add in SLAVE mode can't chdir to '%s'", playpen);
	    return 1;
	}
	read_plist(&Plist, stdin);
	where_to = playpen;
    }
    /* Nope - do it now */
    else {
	/* Is it an ftp://foo.bar.baz/file.tgz specification? */
	if (isURL(pkg)) {
	    if (ispkgpattern(pkg)) {
		pwarnx("patterns not allowed in URLs, "
		     "please install manually!");
		/* ... until we come up with a better solution :-/  - HF */
		goto bomb;
	    }

	    if (!(Home = fileGetURL(NULL, pkg))) {
		pwarnx("unable to fetch '%s' by URL", pkg);
		return 1;
	    }
	    where_to = Home;
	    strlcpy(pkg_fullname, pkg, sizeof(pkg_fullname));
	    system(solve_deps);
	    cfile = fopen(CONTENTS_FNAME, "r");
	    if (!cfile) {
		pwarnx(
		"unable to open table of contents file '%s' - not a package?",
		CONTENTS_FNAME);
		goto bomb;
	    }
	    read_plist(&Plist, cfile);
	    fclose(cfile);
	} else {
	    strlcpy(pkg_fullname, ensure_tgz(pkg), sizeof(pkg_fullname));
	    if (strcmp(pkg, "-")) {
		if (ispkgpattern(pkg_fullname))
		    sb.st_size = 100000;
		else if (stat(pkg_fullname, &sb) == -1) {
		    pwarnx("can't stat package file '%s'", pkg_fullname);
		    goto bomb;
		}
		strlcpy(extract_contents, CONTENTS_FNAME,
			sizeof(extract_contents));
		extract = extract_contents;
	    } else {
		extract = NULL;
		sb.st_size = 100000;	/* Make up a plausible average size */
	    }
	    Home = make_playpen(playpen, sizeof(playpen), sb.st_size * 4);
	    if (!Home)
		pwarnx("unable to make playpen for %ld bytes",
		    (long)(sb.st_size * 4));
	    where_to = Home;
	    if (unpack(pkg_fullname, extract)) {
		pwarnx(
	"unable to extract table of contents from '%s'\n"
	"Is this a Package, or a simple .tgz archive ?  See tar(1).",
		pkg_fullname);
		goto bomb;
	    }
	    system(solve_deps);
	    cfile = fopen(CONTENTS_FNAME, "r");
	    if (!cfile) {
		pwarnx(
	"unable to open table of contents file '%s'\n"
	"Is this a Package, or a simple .tgz archive ?  See tar(1).",
		CONTENTS_FNAME);
		goto bomb;
	    }
	    read_plist(&Plist, cfile);
	    fclose(cfile);

	    /*
	     * Apply a crude heuristic to see how much space the package will
	     * take up once it's unpacked.  I've noticed that most packages
	     * compress an average of 75%, so multiply by 4 for good
	     * measure.  Ignore if extract is null as we've already
	     * extracted the full file, anyway.
	     */

	    if (!extract && min_free(playpen) < (size_t)sb.st_size * 4) {
		pwarnx("projected size of %ld exceeds available free space\n"
		       "Please set your PKG_TMPDIR variable to point to a"
		       "location with more\n"
		       "free space and try again", (long)(sb.st_size * 4));
		pwarnx("not extracting '%s'\ninto '%s', sorry!", pkg_fullname,
		       where_to);
		goto bomb;
	    }

	    /* Finally unpack the whole mess.  If extract is null we already
	       did so so don't bother doing it again. */
	    if (extract && unpack(pkg_fullname, NULL)) {
		pwarnx("unable to extract '%s'!", pkg_fullname);
		goto bomb;
	    }
	} /* isURL(pkg) */

	/* Check for sanity and dependencies */
	if (sanity_check(pkg))
	    goto bomb;

	/* If we're running in MASTER mode, just output the plist and return */
	if (AddMode == MASTER) {
	    printf("%s\n", where_playpen());
	    write_plist(&Plist, stdout);
	    return 0;
	}
    }

    /*
     * If we have a prefix, delete the first one we see and add this
     * one in place of it.
     */
    if (Prefix) {
	delete_plist(&Plist, false, PLIST_CWD, NULL);
	add_plist_top(&Plist, PLIST_CWD, Prefix);
    }

    setenv(PKG_PREFIX_VNAME, (p = find_plist(&Plist, PLIST_CWD, NULL)) ? p->name : ".", 1);
    /* Protect against old packages with bogus @name fields */
    PkgName = (p = find_plist(&Plist, PLIST_NAME, NULL)) ? p->name : NULL;
    if (PkgName == NULL) {
	pwarnx("package name not set in package file");
	goto bomb;
    }

    /* See if we're already registered */
    (void) snprintf(LogDir, sizeof(LogDir), "%s/%s", dbdir, PkgName);
    if ((isdir(LogDir) || islinktodir(LogDir)) && !Force) {
	pwarnx("package already recorded as installed");
	code = 1;
	goto success;	/* close enough for government work */
    }

    /* See if some other version of us is already installed */
    tmp = nuke_version(PkgName, true);


    if (findmatchingname(dbdir, tmp, check_if_installed, installed, sizeof(installed))) {
	pwarnx("other version '%s' already installed", installed);
	if (find_plist_option(&Plist, "no-default-conflict") != NULL) {
	    pwarnx("proceeding with installation anyway");
	} else {
	    if (tmp)
		free(tmp);
	    code = 1;
	    goto success;	/* close enough for government work */
	}
    }
    if (tmp)
	free(tmp);

    /* Do we have the right binary emulation? */
    for (p = Plist.head; p ; p = p->next) {
	if (p->type != PLIST_EMUL)
	    continue;
	if (Verbose)
	    printf("Package '%s' needs %s binary emulation\n", PkgName, p->name);

	if (!have_emulation(p->name)) {
	    pwarnx("Package requires %s binary emulation layer, which is not"
		   " enabled or not available! See the compat_%s(8) manpage"
		   " for details.%s",
		    p->name, p->name, Force ? " (continuing anyway)" : "");
	    if (!Force)
		goto bomb;
	}
    }
    
    /* See if there are conflicting packages installed */
    for (p = Plist.head; p ; p = p->next) {
	char insttst[FILENAME_MAX];

	if (p->type != PLIST_PKGCFL)
	    continue;
	if (Verbose)
	    printf("Package '%s' conflicts with '%s'\n", PkgName, p->name);

	if(findmatchingname(dbdir, p->name, check_if_installed, insttst, sizeof(insttst))){
	    pwarnx("Conflicting package installed, please use\n\t\"pkg_delete %s\" first to remove it!",  insttst);
	    ++code;
	}
    }

    /* Now check the packing list for dependencies */
    for (p = Plist.head; p ; p = p->next) {
	char insttst[FILENAME_MAX];

	if (p->type != PLIST_PKGDEP)
	    continue;
	if (Verbose)
	    printf("Package '%s' depends on '%s'\n", PkgName, p->name);
	if (!findmatchingname(dbdir, p->name, check_if_installed, insttst, sizeof(insttst))) {
	    if (!Fake) {
		if (!isURL(pkg) && !getenv("PKG_ADD_BASE"))
		    code += install_dep_local(pkg, p->name);
		else
		    code += install_dep_ftp(pkg, p->name);
	    } else {
		if (Verbose)
		    printf("and was not found%s\n", Force ? " (proceeding anyway)" : "");
		else
		    printf("Package dependency '%s' for '%s' not found%s\n", p->name, pkg,
			   Force ? " (proceeding anyway)" : "!");
		if (!Force)
		    ++code;
	    }
	} else {
	    if (Verbose)
		printf(" - '%s' already installed\n", insttst);
	    register_dep(pkg, insttst);
	}
    }

    if (code != 0)
	goto bomb;

    /* Look for the requirements file */
    if (fexists(REQUIRE_FNAME)) {
	xsystem(false, "chmod +x %s", REQUIRE_FNAME);	/* be sure */
	if (Verbose)
	    printf("Running requirements file first for '%s'\n", PkgName);
	if (!Fake && xsystem(false, "./%s %s INSTALL", REQUIRE_FNAME, PkgName)) {
	    pwarnx("package '%s' fails requirements %s", pkg_fullname,
		   Force ? "installing anyway" : "- not installed");
	    if (!Force) {
		code = 1;
		goto success;	/* close enough for government work */
	    }
	}
    }

    /* If we're really installing, and have an installation file, run it */
    if (!NoInstall && fexists(INSTALL_FNAME)) {
	xsystem(false, "chmod +x %s", INSTALL_FNAME);	/* make sure */
	if (Verbose)
	    printf("Running install with PRE-INSTALL for '%s'\n", PkgName);
	if (!Fake && xsystem(false, "./%s %s PRE-INSTALL", INSTALL_FNAME, PkgName)) {
	    pwarnx("install script returned error status");
	    unlink(INSTALL_FNAME);
	    code = 1;
	    goto success;		/* nothing to uninstall yet */
	}
    }

    extract_plist(".", &Plist);

    if (!Fake && fexists(MTREE_FNAME)) {
	if (Verbose)
	    printf("Running mtree for '%s'\n", PkgName);
	p = find_plist(&Plist, PLIST_CWD, NULL);
	if (Verbose)
	    printf("mtree -q -U -f %s -d -e -p %s\n", MTREE_FNAME,
		   p ? p->name : "/");
	if (!Fake) {

	    if (xsystem(false, "mtree -q -U -f %s -d -e -p %s", MTREE_FNAME,
			p ? p->name : "/"))
		pwarnx("mtree returned a non-zero status - continuing");
	}
	unlink(MTREE_FNAME);
    }

    /* Run the installation script one last time? */
    if (!NoInstall && fexists(INSTALL_FNAME)) {
	if (Verbose)
	    printf("Running install with POST-INSTALL for '%s'\n", PkgName);
	if (!Fake && xsystem(false, "./%s %s POST-INSTALL", INSTALL_FNAME, PkgName)) {
	    pwarnx("install script returned error status");
	    unlink(INSTALL_FNAME);
	    code = 1;
	    goto fail;
	}
	unlink(INSTALL_FNAME);
    }

    /* Time to record the deed? */
    if (!NoRecord && !Fake) {
	char contents[FILENAME_MAX];

	umask(022);
#ifndef AS_USER
	if (getuid() != 0)
	    pwarnx("not running as root - trying to record install anyway");
#endif
	if (!PkgName) {
	    pwarnx("no package name! can't record package, sorry");
	    code = 1;
	    goto success;	/* well, partial anyway */
	}
	(void) snprintf(LogDir, sizeof(LogDir), "%s/%s", dbdir, PkgName);
	zapLogDir = 1;
	if (Verbose)
	    printf("Attempting to record package into '%s'\n", LogDir);
	drop_privs();
	if (make_hierarchy(LogDir)) {
	    pwarnx("can't record package into '%s', you're on your own!",
		   LogDir);
	    memset(LogDir, 0, FILENAME_MAX);
	    raise_privs();
	    code = 1;
	    goto success;	/* close enough for government work */
	}
	raise_privs();
	/* Make sure pkg_info can read the entry */
	xsystem(false, "chmod a+rx %s", LogDir);
	if (fexists(DEINSTALL_FNAME))
	    move_file(".", DEINSTALL_FNAME, LogDir);
	if (fexists(REQUIRE_FNAME))
	    move_file(".", REQUIRE_FNAME, LogDir);
	(void) snprintf(contents, sizeof(contents), "%s/%s", LogDir, CONTENTS_FNAME);
	drop_privs();
	cfile = fopen(contents, "w");
	if (!cfile) {
	    raise_privs();
	    pwarnx("can't open new contents file '%s'! can't register pkg",
		contents);
	    goto success; /* can't log, but still keep pkg */
	}
	write_plist(&Plist, cfile);
	fclose(cfile);
	raise_privs();
	move_file(".", DESC_FNAME, LogDir);
	move_file(".", COMMENT_FNAME, LogDir);
	if (fexists(DISPLAY_FNAME))
	    move_file(".", DISPLAY_FNAME, LogDir);
	write_deps();

	if (Verbose)
	    printf("Package '%s' registered in '%s'\n", PkgName, LogDir);
    }

    if ((p = find_plist(&Plist, PLIST_DISPLAY, NULL)) != NULL) {
	const char *Pager;
	char buf[BUFSIZ];
	struct stat sbuf;

	switch(DisplayMode) {
	    case CAT:
		Pager = "/bin/cat";
		break;
	    case LESS:
		Pager = "less";
		break;
	    case MORE:
		Pager = NULL;
		break;
	    case ENV:
		Pager = getenv("PAGER");
		break;
	    default:
		Pager = "more";
	}

	snprintf(buf, sizeof buf, "%s/%s", LogDir, p->name);
	if (stat(buf,&sbuf) == -1 || xsystem(false, "%s %s", Pager, buf)) {
	    pwarnx("cannot open '%s' as display file", buf);
	    DisplayMode = CAT;	/* in case the pager is just missing */
	}
    }

    goto success;

 bomb:
    code = 1;
    goto success;

 fail:
    /* Nuke the whole (installed) show, XXX but don't clean directories */
    if (!Fake)
	delete_package(false, false, RMCFG_NONE, false, &Plist);

 success:
    /* delete the packing list contents */
    free_plist(&Plist);
    leave_playpen(Home);
    return code;
}

/* install depending pkg from local disk */
static int
install_dep_local(char *base, char *pattern)
{
    char *cp;
    char path[FILENAME_MAX];

    snprintf(path, sizeof(path), "%s/%s", Home, ensure_tgz(pattern));
    if (fexists(path))
	cp = path;
    else
	cp = fileFindByPath(base, pattern);
    if (cp) {
	if (Verbose)
	    printf("Loading it from '%s'\n", cp);
	if (xsystem(false, "pkg_add %s%s %s%s",
		     Prefix ? "-p " : "",
		     Prefix ? Prefix : "",
		     Verbose ? "-v " : "", cp)) {
	    pwarnx("autoload of dependency '%s' failed%s",
		cp, Force ? " (proceeding anyway)" : "!");
	    if (!Force)
		return 1;
	}
	register_dep(base, cp);
    } else {
	pwarnx("add of dependency '%s' failed%s",
		pattern, Force ? " (proceeding anyway)" : "!");
	     if (!Force)
		 return 1;
    }
    return 0;
}

/* install depending pkg via FTP */
static int
install_dep_ftp(char *base, char *pattern)
{
    char *cp;

    if (ispkgpattern(pattern)){
	pwarnx("can't install dependent pkg '%s' via FTP, "
	     "please install manually!", pattern);
	/* ... until we come up with a better solution - HF */
	return 1;
    } else {
	char *saved_Current;   /* allocated/set by save_dirs(), */
	char *saved_Previous;  /* freed by restore_dirs() */

	save_dirs(&saved_Current, &saved_Previous);

	if ((cp = fileGetURL(base, pattern)) != NULL) {
	    if (Verbose)
		printf("Finished loading '%s' over FTP\n", pattern);
	    /*system(solve_deps); * XXX */
	    if (!fexists(CONTENTS_FNAME)) {
		pwarnx("autoloaded package '%s' has no %s file?",
		      pattern, CONTENTS_FNAME);
		if (!Force)
		    return 1;
	    } else if (xsystem(false, "(pwd; cat %s) | pkg_add %s%s %s-S",
			     CONTENTS_FNAME,
			     Prefix ? "-p " : "",
			     Prefix ? Prefix : "",
			     Verbose ? "-v " : "")) {
		pwarnx("add of dependency '%s' failed%s",
		      pattern, Force ? " (proceeding anyway)" : "!");
		if (!Force)
		    return 1;
	    } else if (Verbose)
		printf("\t'%s' loaded successfully\n", pattern);
	    /* Nuke the temporary playpen */
	    leave_playpen(cp);
	    free(cp);

	    restore_dirs(saved_Current, saved_Previous);
	    register_dep(base, pattern);
	}
    }
    return 0;
}

/* add a dependent package to the internal depends list */
static void
register_dep_(char *pkg, char *dep)
{
    char *dep2, *bdep, *new_pkgdeps;

    if (!pkg || !dep)
	return;

    if ((dep2 = strdup(dep)) == NULL) {
	pwarn("dependency registration on %s is incomplete", dep);
	return;
    }
    if ((bdep = basename(dep2)) == NULL) {
	free(dep2);
	pwarn("dependency registration on %s is incomplete", dep);
	return;
    }

    trim_end(bdep);
    if (asprintf(&new_pkgdeps, "%s%s\n", PkgDeps ? PkgDeps : "", bdep) < 0)
	pwarn("dependency registration on %s is incomplete", dep);
    else {
	free(PkgDeps);
	PkgDeps = new_pkgdeps;
    }
    free(dep2);
}

/* write the dependencies of a package into its dbdir and register them */
static void
write_deps(void)
{
    char filename[FILENAME_MAX];
    char *cp, *token;

    if (!PkgDeps || !LogDir)
	return;

    (void) snprintf(filename, sizeof(filename), "%s/%s", LogDir, DEPENDS_FNAME);
    drop_privs();
    (void)write_file(filename, "w", "%s", PkgDeps);
    raise_privs();

    token = PkgDeps;
    while ((cp = strsep(&token, "\n")) != NULL) {
	if (*cp == '\0')
	    continue;
	if (Verbose)
	    printf("Attempting to record dependency on package '%s'\n", cp);
	snprintf(filename, sizeof(filename), "%s/%s/%s", dbdir, cp,
	    REQUIRED_BY_FNAME);
	drop_privs();
	if (write_file(filename, "a", "%s\n", PkgName))
	    pwarnx("dependency registration is incomplete");
	raise_privs();
    }
    free(PkgDeps);
    PkgDeps = NULL;
}

static int
sanity_check(char *pkg)
{
    int code = 0;

    if (!fexists(CONTENTS_FNAME)) {
	pwarnx("package '%s' has no CONTENTS file!", pkg);
	code = 1;
    }
    else if (!fexists(COMMENT_FNAME)) {
	pwarnx("package '%s' has no COMMENT file!", pkg);
	code = 1;
    }
    else if (!fexists(DESC_FNAME)) {
	pwarnx("package '%s' has no DESC file!", pkg);
	code = 1;
    }
    return code;
}

void
cleanup(int signo)
{
    int save_errno = errno;
    static int	alreadyCleaning;
    void (*oldint)(int);
    void (*oldhup)(int);
    char buf[1024];
    oldint = signal(SIGINT, SIG_IGN);
    oldhup = signal(SIGHUP, SIG_IGN);

    /* XXX big signal race, nearly all of it! */
    if (!alreadyCleaning) {
    	alreadyCleaning = 1;
	if (signo) {
	    snprintf(buf, sizeof buf,
		"Signal %d received, cleaning up\n", signo);
	    write(STDOUT_FILENO, buf, strlen(buf));
	}
	if (!Fake && zapLogDir && LogDir[0])
	    xsystem(false, "%s -rf %s", REMOVE_CMD, LogDir);	/* XXX */
	leave_playpen(Home);				/* XXX */
	if (signo)
	    _exit(1);
    }
    signal(SIGINT, oldint);
    signal(SIGHUP, oldhup);
    errno = save_errno;
}
