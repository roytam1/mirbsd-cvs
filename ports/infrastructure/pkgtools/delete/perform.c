/**	$MirOS: ports/infrastructure/pkgtools/delete/perform.c,v 1.13 2008/11/02 18:56:29 tg Exp $ */
/*	$OpenBSD: perform.c,v 1.16 2003/08/21 20:24:56 espie Exp $	*/

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
 * This is the main body of the delete module.
 */

#include <sys/param.h>
#ifndef __INTERIX
#include <sys/mount.h>
#endif
#include <err.h>
#include "lib.h"
#include "delete.h"
#include <libgen.h>

__RCSID("$MirOS: ports/infrastructure/pkgtools/delete/perform.c,v 1.13 2008/11/02 18:56:29 tg Exp $");

static int pkg_do(char *);
static void sanity_check(char *);
static int undepend(const char *, char *, int);
static char LogDir[FILENAME_MAX];

int
pkg_perform(char **pkgs)
{
    int i, err_cnt = 0;

    for (i = 0; pkgs[i]; i++)
	err_cnt += pkg_do(pkgs[i]);
    return err_cnt;
}

static package_t Plist;

/* remove all links to the package as well */
static void
delete_pkg_links(const char *dir, const char *pkg)
{
    int base;
    int len;
    DIR *d;
    struct dirent *dp;
    struct stat sb;
    char name[FILENAME_MAX+1];

    base = open(".", O_RDONLY);
    if (base == -1)
    	return;
    if (chdir(dir) == -1) {
    	close(base);
	return;
    }
    d = opendir(".");
    if (d == NULL) {
    	fchdir(base);
	close(base);
	return;
    }
    while ((dp = readdir(d)) != NULL) {
    	if (lstat(dp->d_name, &sb) == -1 || !S_ISLNK(sb.st_mode))
	    continue;
	len = readlink(dp->d_name, name, FILENAME_MAX);
	if (len == -1)
	    continue;
	name[len] = 0;
	if (strcmp(name, pkg))
	    continue;
	unlink(dp->d_name);
    }
    closedir(d);
    fchdir(base);
    close(base);
}

/* This is seriously ugly code following.  Written very fast! */
static int
pkg_do(char *pkg)
{
    FILE *cfile;
    int homefd;
    char fbuf[FILENAME_MAX];
    plist_t *p;
    const char *dbdir;
    char *filename;

    set_pkg(pkg);
    /* Reset some state */
    if (Plist.head)
	free_plist(&Plist);

    dbdir = getenv(PKG_DBDIR);
    if (!dbdir)
       dbdir = DEF_LOG_DIR;

    switch (glob_package(LogDir, sizeof(LogDir), pkg)) {
    case -1:
	pwarnx("error while handling package name");
	return 1;
    case 0:
	pwarnx("no such package installed");
	return 1;
    case 1:
	/* good */
	break;
    default:
	pwarnx("more than one match for package specification");
	return 1;
    }
    pkg = strdup(basename(LogDir));

    if ((homefd = open(".", O_RDONLY, 0555)) == -1) {
	cleanup(0);
	err(2, "unable to get current working directory");
    }
    if (chdir(LogDir) == -1) {
	pwarnx("unable to change directory to %s! deinstall failed", LogDir);
	free(pkg);
	return 1;
    }
    sanity_check(LogDir);
    cfile = fopen(CONTENTS_FNAME, "r");
    if (!cfile) {
	pwarnx("unable to open '%s' file", CONTENTS_FNAME);
	free(pkg);
	return 1;
    }
    /* If we have a prefix, add it now */
    if (Prefix)
	add_plist(&Plist, PLIST_CWD, Prefix);
    read_plist(&Plist, cfile);
    fclose(cfile);
    if (!KeepFiles && find_plist_option(&Plist, "base-package") != NULL) {
	pwarnx("package '%s' is considered a BASE PACKAGE.\n"
		"DELETING IT WILL ALMOST CERTAINLY BREAK YOUR SYSTEM%s.",
		pkg, Force ? "\n(but I'll delete it anyway)" :
		".\nUse -f if you are really sure what you are doing");
	if (!Force) {
	    free(pkg);
	    return 1;
	}
    }
    if (!isemptyfile(REQUIRED_BY_FNAME)) {
	char buf[512];
	pwarnx("package '%s' is required by these other packages\n"
		"and may not be deinstalled%s:",
		pkg, Force ? " (but I'll delete it anyway)" : "" );
	cfile = fopen(REQUIRED_BY_FNAME, "r");
	if (cfile) {
	    while (fgets(buf, sizeof(buf), cfile))
		fprintf(stderr, "%s", buf);
	    fclose(cfile);
	} else
	    pwarnx("cannot open requirements file '%s'", REQUIRED_BY_FNAME);
	if (!Force) {
	    free(pkg);
	    return 1;
	}
    }
    p = find_plist(&Plist, PLIST_CWD, NULL);
    if (!p) {
	pwarnx("package '%s' doesn't have a prefix", pkg);
	free(pkg);
	return 1;
    }
#ifndef __INTERIX
    {
	struct statfs buffer;

	if (statfs(p->name, &buffer) == -1) {
	    pwarnx("package '%s' prefix (%s) does not exist", pkg, p->name);
	    free(pkg);
	    return 1;
	}
	if (buffer.f_flags & MNT_RDONLY) {
	    pwarnx("package'%s' mount point %s is read-only", pkg,
		buffer.f_mntonname);
	    free(pkg);
	    return 1;
	}
    }
#endif

    setenv(PKG_PREFIX_VNAME, p->name, 1);
    setenv("PKG_DELETE_EXTRA", (CleanConf ? "Yes" : "No"), 1);
    if (fexists(REQUIRE_FNAME)) {
	if (Verbose)
	    printf("Executing 'require' script.\n");
	xsystem(false, "chmod +x %s", REQUIRE_FNAME);	/* be sure */
	if (xsystem(false, "./%s %s DEINSTALL", REQUIRE_FNAME, pkg)) {
	    pwarnx("package %s fails requirements %s", pkg,
		   Force ? "" : "- not deleted");
	    if (!Force) {
		free(pkg);
		return 1;
	    }
	}
    }
    if (!NoDeInstall && fexists(DEINSTALL_FNAME)) {
	if (Fake)
	    printf("Would execute de-install script at this point.\n");
	else {
	    xsystem(false, "chmod +x %s", DEINSTALL_FNAME);	/* make sure */
	    if (xsystem(false, "./%s %s DEINSTALL", DEINSTALL_FNAME, pkg)) {
		pwarnx("deinstall script returned error status");
		if (!Force) {
		    free(pkg);
		    return 1;
		}
	    }
	}
    }
    if (fchdir(homefd) == -1) {
	(void) close(homefd);
	cleanup(0);
	err(2, "Cannot change back to former working directory");
    }
    (void) close(homefd);
    if (!Fake) {
	/* Some packages aren't packed right, so we need to just ignore delete_package()'s status.  Ugh! :-( */
	if (delete_package(KeepFiles, CleanDirs, CleanConf, CheckMD5, &Plist) == -1)
	    pwarnx(
	"couldn't entirely delete package (perhaps the packing list is "
	"incorrectly specified?)");
    }
    /* Remove package dependencies */
    filename = toabs(DEPENDS_FNAME, LogDir);
    if (fexists(filename)) {
	if (Verbose)
	    printf("Dependency file found, using it for unregistering dependencies\n");
	cfile = fopen(filename, "r");
	if (cfile == NULL) {
	    pwarn("couldn't open dependency file '%s'", DEPENDS_FNAME);
	    free(pkg);
	    return 1;
	}
	while (fgets(fbuf, sizeof(fbuf), cfile) != NULL) {
	    if (fbuf[strlen(fbuf)-1] == '\n')
		fbuf[strlen(fbuf)-1] = '\0';
	    if (Verbose)
		printf("Attempting to remove dependency on package '%s'\n", fbuf);
	    drop_privs();
	    undepend(fbuf, pkg, 0);
	    raise_privs();
	}
	(void) fclose(cfile);
    } else for (p = Plist.head; p ; p = p->next) {
	if (p->type != PLIST_PKGDEP)
	    continue;
	if (Verbose)
	    printf("Attempting to remove dependency on package '%s'\n", p->name);
	drop_privs();
	if (!Fake)
	    findmatchingname(dbdir, p->name, undepend, pkg, 0);
	raise_privs();
    }
    if (!Fake) {
	if (xsystem(false, "%s -r %s", REMOVE_CMD, LogDir)) {
	    pwarnx("couldn't remove log entry in %s, deinstall failed", LogDir);
	    if (!Force) {
		free(pkg);
		return 1;
	    }
	}
	delete_pkg_links(dbdir, pkg);
    }
    free(pkg);
    return 0;
}

static void
sanity_check(char *pkg)
{
    if (!fexists(CONTENTS_FNAME)) {
	cleanup(0);
	errx(2, "installed package %s has no %s file!", pkg, CONTENTS_FNAME);
    }
}

void
cleanup(int sig __attribute__((unused)))
{
	/* return here, for errx(3) calls to succeed */
}

/* deppkgname is the pkg from which's +REQUIRED_BY file we are
 * about to remove pkg2delname. This function is called from
 * findmatchingname(), deppkgname is expanded from a (possible) pattern.
 */
int
undepend(const char *deppkgname, char *pkg2delname,
    int unused __attribute__((unused)))
{
     char fname[FILENAME_MAX], ftmp[FILENAME_MAX];
     char fbuf[FILENAME_MAX];
     FILE *fp, *fpwr;
     char *tmp;
     int s;

     (void) snprintf(fname, sizeof(fname), "%s/%s/%s",
	     (tmp = getenv(PKG_DBDIR)) ? tmp : DEF_LOG_DIR,
	     deppkgname, REQUIRED_BY_FNAME);
     fp = fopen(fname, "r");
     if (fp == NULL) {
	 pwarnx("couldn't open dependency file '%s'", fname);
	 return 0;
     }
     (void) snprintf(ftmp, sizeof(ftmp), "%s.XXXXXXXXXX", fname);
     s = mkstemp(ftmp);
     if (s == -1) {
	 fclose(fp);
	 pwarnx("couldn't open temp file '%s'", ftmp);
	 return 0;
     }
     fpwr = fdopen(s, "w");
     if (fpwr == NULL) {
	 close(s);
	 fclose(fp);
	 pwarnx("couldn't fdopen temp file '%s'", ftmp);
	 remove(ftmp);
	 return 0;
     }
     while (fgets(fbuf, sizeof(fbuf), fp) != NULL) {
	 if (fbuf[strlen(fbuf)-1] == '\n')
	     fbuf[strlen(fbuf)-1] = '\0';
	 if (strcmp(fbuf, pkg2delname))		/* no match */
	     fputs(fbuf, fpwr), putc('\n', fpwr);
     }
     (void) fclose(fp);
     if (fchmod(s, 0644) == -1) {
	 pwarnx("error changing permission of temp file '%s'", ftmp);
	 fclose(fpwr);
	 remove(ftmp);
	 return 0;
     }
     if (fclose(fpwr) == EOF) {
	 pwarnx("error closing temp file '%s'", ftmp);
	 remove(ftmp);
	 return 0;
     }
     if (rename(ftmp, fname) == -1)
	 pwarnx("error renaming '%s' to '%s'", ftmp, fname);
     remove(ftmp);			/* just in case */

     return 0;
}
