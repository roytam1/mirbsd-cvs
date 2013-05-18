/**	$MirOS: ports/infrastructure/pkgtools/info/perform.c,v 1.6.2.1 2010/03/07 15:56:02 bsiegert Exp $ */
/*	$OpenBSD: perform.c,v 1.16 2003/08/23 09:14:43 tedu Exp $	*/

/* This is MirPorts pkg_install, based on:
 *
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
 * 23 Aug 1993
 *
 * This is the main body of the info module.
 */

#include "lib.h"
#include "info.h"

#include <sys/types.h>
#include <sys/stat.h>

#include <err.h>
#include <signal.h>
#include <dirent.h>
#include <ctype.h>
#include <libgen.h>

__RCSID("$MirOS: ports/infrastructure/pkgtools/info/perform.c,v 1.6.2.1 2010/03/07 15:56:02 bsiegert Exp $");

static char    *Home;

__dead void cleanup_and_exit(int);

static int
pkg_do(char *pkg)
{
	bool		isTMP = false;
	char            log_dir[FILENAME_MAX];
	char            fname[FILENAME_MAX];
	package_t       plist;
	FILE           *fp;
	struct stat     sb;
	char           *cp = NULL;
	int             code = 0;
	int             len;
	int		isurl = 0;
	bool		isInstalled = false;

	set_pkg(pkg);

	if (glob_package(log_dir, sizeof(log_dir), pkg) >= 1) {
		if (chdir(log_dir) == -1) {
			pwarnx("can't change directory to '%s'!", log_dir);
			return 1;
		}
		pkg = strdup(basename(log_dir));
		isInstalled = true;
	} else if (isURL(pkg)) {
		if ((cp = fileGetURL(NULL, pkg)) != NULL) {
			strlcpy(fname, cp, sizeof(fname));
			isTMP = true;
		}
		isurl = 1;
	} else if (fexists(pkg) && isfile(pkg)) {
		if (*pkg != '/') {
			if (!getcwd(fname, sizeof(fname))) {
			    cleanup(0);
			    err(1, "fatal error during execution: getcwd");
			}
			len = strlen(fname);
			snprintf(&fname[len], sizeof(fname) - len, "/%s", pkg);
		} else
			strlcpy(fname, pkg, sizeof(fname));
		cp = fname;
	} else if ((cp = fileFindByPath(NULL, pkg)) != NULL) {
		strlcpy(fname, cp, sizeof(fname));
		if (isURL(fname) && (cp = fileGetURL(NULL, fname))
		    != NULL) {
			strlcpy(fname, cp, sizeof(fname));
			isTMP = true;
			isurl = 1;
		} else if (cp && *cp != '/') {
			if (!getcwd(fname, sizeof(fname))) {
				cleanup(0);
				err(1, "fatal error during execution: "
				    "getcwd");
			}
			len = strlen(fname);
			snprintf(&fname[len], sizeof(fname) - len,
			    "/%s", cp);
		}
		pkg = fname;
	} else {
		pwarnx("cannot find package '%s' installed or in a file!", pkg);
		return 1;
	}

	if (cp) {
		if (isurl) {
			/* file is already unpacked by fileGetURL() */
			strlcpy(PlayPen, cp, PlayPenSize);
		} else {
			/*
			 * Apply a crude heuristic to see how much space the package will
			 * take up once it's unpacked.  I've noticed that most packages
			 * compress an average of 75%, but we're only unpacking the + files so
			 * be very optimistic.
			 */
			if (stat(fname, &sb) == -1) {
				pwarnx("can't stat package file '%s'", fname);
				code = 1;
				goto bail;
			}
			Home = make_playpen(PlayPen, PlayPenSize, sb.st_size / 2);
			if (unpack(fname, "+*")) {
				pwarnx("error during unpacking, no info for '%s' available", pkg);
				code = 1;
				goto bail;
			}
		}
	}

	/*
         * Index is special info type that has to override all others to make
         * any sense.
         */
	if (Flags & SHOW_INDEX) {
		show_index(pkg, COMMENT_FNAME);
	} else {
		/* Suck in the contents list */
		plist.head = plist.tail = NULL;
		fp = fopen(CONTENTS_FNAME, "r");
		if (!fp) {
			pwarnx("unable to open %s file", CONTENTS_FNAME);
			code = 1;
			goto bail;
		}
		/* If we have a prefix, add it now */
		read_plist(&plist, fp);
		fclose(fp);

		/* Start showing the package contents */
		if (!Quiet)
			printf("%sInformation for %s%s:\n\n", InfoPrefix, pkg,
					isInstalled ? " (installed)" : "");
		if (Flags & SHOW_COMMENT)
			show_file("Comment:\n", COMMENT_FNAME);
		if ((Flags & SHOW_REQBY) && !isemptyfile(REQUIRED_BY_FNAME))
			show_file("Required by:\n", REQUIRED_BY_FNAME);
		if (Flags & SHOW_DESC)
			show_file("Description:\n", DESC_FNAME);
		if ((Flags & SHOW_DISPLAY) && fexists(DISPLAY_FNAME))
			show_file("Install notice:\n", DISPLAY_FNAME);
		if ((Flags & SHOW_DEPENDS) && fexists(DEPENDS_FNAME))
			show_file("Dependencies:\n", DEPENDS_FNAME);
		if (Flags & SHOW_PLIST)
			show_plist("Packing list:\n", &plist, PLIST_SHOW_ALL);
		if ((Flags & SHOW_INSTALL) && fexists(INSTALL_FNAME))
			show_file("Install script:\n", INSTALL_FNAME);
		if ((Flags & SHOW_DEINSTALL) && fexists(DEINSTALL_FNAME))
			show_file("De-Install script:\n", DEINSTALL_FNAME);
		if ((Flags & SHOW_MTREE) && fexists(MTREE_FNAME))
			show_file("mtree file:\n", MTREE_FNAME);
		if (Flags & SHOW_PREFIX)
			show_plist("Prefix(s):\n", &plist, PLIST_CWD);
		if (Flags & SHOW_FILES)
			show_files("Files:\n", &plist);
		if (Flags & SHOW_SAMPLE)
			show_plist("Configuration file(s):\n", &plist, PLIST_SAMPLE);
		if (!Quiet)
			puts(InfoPrefix);
		free_plist(&plist);
	}
bail:
	leave_playpen(Home);
	if (isTMP)
		unlink(fname);
	return code;
}

/* fn to be called for pkgs found */
static int
foundpkg(const char *found, char *data, int len)
{
    if(!Quiet)
	printf(len ? "%-30s%s\n" : "%s%s", found, data);
    return 0;
}

static int
findpkg_srcs(char *pkgspec, const char *dbdir)
{
	struct matchlist *matches;
	struct match *mp;
	int found;
	char *msg;

	/* look for an installed package first */
	if (!(msg = strdup(" (installed)")))
		err(1, NULL);
	found = findmatchingname(dbdir, pkgspec, foundpkg, msg, strlen(msg));

	matches = findmatchingname_srcs(cfg_get_sourcelist(), pkgspec);
	TAILQ_FOREACH(mp, matches, entries) {
		found++;
		if (!Quiet)
			printf("%-30s at %s\n", mp->pkgname, mp->source);
	}
	
	matchlist_destroy(matches);
	free(matches);
	return found;
}

/* check if a package "pkgspec" (which can be a pattern) is installed */
/* return 0 if found, 1 otherwise (indicating an error). */
static int
check4pkg(char *pkgspec, const char *dbdir)
{
	if (strpbrk(pkgspec, "<>[]?*{")) {
	    /* expensive (pattern) match */
	    int found;
	    char *empty;

	    if (!(empty = strdup("")))
		    err(1, NULL);

	    found=findmatchingname(dbdir, pkgspec, foundpkg, empty, 0);
	    return !found;
	} else {
		/* simple match */
	char            buf[FILENAME_MAX];
	int             error;
		struct stat     st;

		snprintf(buf, sizeof(buf), "%s/%s", dbdir, pkgspec);
		error = (stat(buf, &st) < 0);
		if (!error && !Quiet)
		printf("%s\n", pkgspec);

	return error;
	}
}

void
cleanup(int sig __attribute__((unused)))
{
	leave_playpen(Home);		/* XXX signal race */
	/* _do_ return, so errx(3) works */
}

__dead void
cleanup_and_exit(int sig)
{
	cleanup(sig);			/* XXX signal race */
	_exit(1);
}

int
pkg_perform(char **pkgs)
{
	int             i, err_cnt = 0;
	const char	*tmp;

	signal(SIGINT, cleanup_and_exit);

	tmp = getenv(PKG_DBDIR);
	if (!tmp)
		tmp = DEF_LOG_DIR;
	/* Overriding action? */
	if (CheckPkg)
		err_cnt += check4pkg(CheckPkg, tmp);
	else if (FindPkg)
		err_cnt += findpkg_srcs(FindPkg, tmp);
	else if (AllInstalled) {
		struct dirent  *dp;
		DIR            *dirp;

		if (!(isdir(tmp) || islinktodir(tmp)))
			return 1;
		if (chdir(tmp) != 0)
			return 1;
		if ((dirp = opendir(".")) != NULL) {
			while ((dp = readdir(dirp)) != NULL) {
				if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
					err_cnt += pkg_do(dp->d_name);
				}
			}
			(void) closedir(dirp);
		}
	} else {
		for (i = 0; pkgs[i]; i++) {
			err_cnt += pkg_do(pkgs[i]);
		}
	}
	return err_cnt;
}
