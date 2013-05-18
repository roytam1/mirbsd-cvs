/* $MirOS: ports/infrastructure/pkgtools/add/extract.c,v 1.13 2008/03/27 21:00:37 bsiegert Exp $ */
/* $OpenBSD: extract.c,v 1.16 2003/07/04 17:31:19 avsm Exp $ */

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
 * This is the package extraction code for the add module.
 */

#include <sys/types.h>
#include <err.h>
#include <md5.h>
#include <time.h>
#include "lib.h"
#include "add.h"
#include "rcdb.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/add/extract.c,v 1.13 2008/03/27 21:00:37 bsiegert Exp $");

#if 0 /* defined(__OpenBSD__) && !defined(__MirBSD__) */
/* this gets rid of the requirement to run paxmirabilis
   on OpenBSD, but their pax is so broken sometimes...  */
#define STARTSTRING "tar -cf - "
#else
#define STARTSTRING "tar -Rcf - "
#endif
#define TOOBIG(str) ((strlen(str) + FILENAME_MAX + where_count > maxargs) \
		|| (strlen(str) + FILENAME_MAX + perm_count > maxargs))

#define PUSHOUT(todir) /* push out string */				\
        if (where_count > sizeof(STARTSTRING)-1) {			\
		    strlcat(where_args, "|tar xpf - -C ", maxargs); \
		    strlcat(where_args, todir, maxargs);		\
		    if (system(where_args)) {				\
			cleanup(0);					\
			errx(2, "can not invoke %lu byte tar pipeline: %s", \
				(u_long)strlen(where_args), where_args); \
		    }							\
		    strlcpy(where_args, STARTSTRING, maxargs);		\
		    where_count = sizeof(STARTSTRING)-1;		\
	}								\
	if (perm_count) {						\
		    apply_perms(todir, perm_args);			\
		    perm_args[0] = 0;					\
		    perm_count = 0;					\
	}

static void
rollback(char *name, const char *home, plist_t *start, plist_t *stop)
{
    plist_t *q;
    char try[FILENAME_MAX], bup[FILENAME_MAX];
    const char *dir;

    dir = home;
    for (q = start; q != stop; q = q->next) {
	if (q->type == PLIST_FILE) {
	    snprintf(try, sizeof(try), "%s/%s", dir, q->name);
	    if (make_preserve_name(bup, sizeof(bup), name, try) && fexists(bup)) {
#ifndef __INTERIX
		(void)chflags(try, 0);
#endif
		(void)unlink(try);
		if (rename(bup, try))
		    pwarnx("rollback: unable to rename %s back to %s", bup, try);
	    }
	}
	else if (q->type == PLIST_CWD) {
	    if (strcmp(q->name, "."))
		dir = q->name;
	    else
		dir = home;
	}
    }
}

static int
preserve(const char *fname)
{
    char copy[FILENAME_MAX];
    int i;

    for (i = 0; i < 50; i++) {
    	snprintf(copy, sizeof(copy), "%s-%d", fname, i);
	if (fexists(copy))
		continue;
	if (rename(fname, copy) == 0) {
		if (!Quiet)
			pwarnx("conflict: renamed existing %s to %s", fname, copy);
		if (!NoBackups)
			return (0);
		if (unlink(copy)) {
			char *try = malloc(FILENAME_MAX);
			if (try == NULL)
				err(1, "malloc");
			snprintf(try, FILENAME_MAX, "/tmp/Deleteme.%llu",
			    (unsigned long long)getpid() * time(NULL));
			if (!fexists(try) && rename(copy, try))
				goto removed;
			snprintf(try, FILENAME_MAX, "%s/Deleteme.XXXXXXXXXX",
			    getenv(PKG_PREFIX_VNAME));
			if (mkdtemp(try) == NULL)
				pwarnx("cannot mkdtemp; %s not removed", copy);
			else {
				strlcat(try, "/removeme", FILENAME_MAX);
				if (rename(copy, try))
					pwarnx("cannot remove %s", copy);
			}
removed:
			free(try);
		}
		return 0;
	}
    }
    return -1;
}

static char *
find_last_md5(plist_t *p)
{
    plist_t *q;

    for (q = p; q && (q->type != PLIST_COMMENT || strncmp(q->name, "MD5:", 4));
	q = q->prev) {
    }
    if (q)
    	return q->name + 4;
    else
	return NULL;
}


static void
inc_dir_counter(char *name, int *usedb, RCDB *ourdb)
{
    recno_t rr;
    int64_t rcount = 1;

    if (!*usedb)
	return;
    if ((rr = rcdb_lookup(ourdb, name)) == (recno_t)-1) {
	warn("rcdb_lookup");
	*usedb = 0;
	rcdb_close(ourdb);
	return;
    }
    if (rr) {
	if (rcdb_read(ourdb, rr, &rcount) == -1) {
	    warn("rcdb_read");
	    *usedb = 0;
	    rcdb_close(ourdb);
	    return;
	}
	if (rcount == LLONG_MAX) {
	    warnx("rcount reached LLONG_MAX in <%s>, not increasing", name);
	    return;
	}
	++rcount;
    }
    if (rcdb_store(ourdb, rcount, name) == (recno_t)-1) {
	warn("rcdb_write");
	*usedb = 0;
	rcdb_close(ourdb);
	return;
    }
}

void
extract_plist(const char *home, package_t *pkg)
{
    plist_t *p = pkg->head;
    char *last_file;
    char *where_args, *perm_args;
    const char *last_chdir;
    char *tmp;
    size_t add_count, maxargs, perm_count = 0, where_count = 0;
    static int usedb = 1;
    RCDB *ourdb;

    if ((ourdb = rcdb_open((tmp = getenv("PKG_REFCNTDB")) ? tmp : _PATH_REFCNTDB)) == NULL) {
	warn("rcdb_open: not using db");
	usedb = 0;
    }

    maxargs = sysconf(_SC_ARG_MAX) / 2;	/* Just use half the argument space */
    where_args = alloca(maxargs);
    if (!where_args) {
	cleanup(0);
	errx(2, "can't get argument list space");
    }
    perm_args = alloca(maxargs);
    if (!perm_args) {
	cleanup(0);
	errx(2, "can't get argument list space");
    }
    strlcpy(where_args, STARTSTRING, maxargs);
    where_count = sizeof(STARTSTRING)-1;
    perm_args[0] = 0;

    last_chdir = 0;

    /* Reset the world */
    Owner = NULL;
    Group = NULL;
    Mode = NULL;
    last_file = NULL;
    Directory = home;

    /* Do it */
    while (p) {
	char cmd[FILENAME_MAX];

	switch(p->type) {
	case PLIST_NAME:
	    PkgName = p->name;
	    if (Verbose)
		printf("extract: Package name is %s\n", p->name);
	    break;

	case PLIST_LIB:
	case PLIST_NOLIB:
	case PLIST_SHELL:
	case PLIST_FILE:
	    if (p->name[strlen(p->name) - 1] == '/') {	/* dir/ entry */
		/* cut off trailing / */
		tmp = strdup(p->name);
		if (!tmp) {
		    cleanup(0);
		    errx(2, "Out of memory!");
		}
		tmp[strlen(tmp) - 1] = '\0';
		if (Verbose)
		    printf("extract: make directory: %s\n", tmp);
		if (!Fake && make_hierarchy(tmp) == -1) {
		    cleanup(0);
		    errx(2, "unable to make directory '%s'", tmp);
		}
		inc_dir_counter(tmp, &usedb, ourdb);
		free(tmp);
		break;
	    }
	    last_file = p->name;
	    if (Verbose)
		printf("extract: %s/%s\n", Directory, p->name);
	    if (!Fake) {
		char try[FILENAME_MAX];

		if (strrchr(p->name,'\'')) {
		  cleanup(0);
		  errx(2, "Bogus filename \"%s\"", p->name);
		}

		/* first try to rename it into place */
		snprintf(try, sizeof(try), "%s/%s", Directory, p->name);
		if (fexists(try)) {
		    if (preserve(try) == -1) {
		    	pwarnx("unable to back up %s, aborting pkg_add", try);
			rollback(PkgName, home, pkg->head, p);
			return;
		    }
		}
		if (rename(p->name, try) == 0) {
		    /* try to add to list of perms to be changed and run in bulk. */
		    if (p->name[0] == '/' || TOOBIG(p->name)) {
			PUSHOUT(Directory);
		    }
		    add_count = snprintf(&perm_args[perm_count], maxargs - perm_count, "'%s' ", p->name);
		    if (add_count > maxargs - perm_count) {
			cleanup(0);
			errx(2, "oops, miscounted strings!");
		    }
		    perm_count += add_count;
		} else {
		    /* rename failed, try copying with a big tar command */
		    if (last_chdir != Directory) {
			PUSHOUT(last_chdir);
			last_chdir = Directory;
		    }
		    else if (p->name[0] == '/' || TOOBIG(p->name)) {
			PUSHOUT(Directory);
		    }
		    add_count = snprintf(&where_args[where_count], maxargs - where_count, " '%s'", p->name);
		    if (add_count > maxargs - where_count) {
			cleanup(0);
			errx(2, "oops, miscounted strings!");
		    }
		    where_count += add_count;
		    add_count = snprintf(&perm_args[perm_count],
					 maxargs - perm_count,
					 "'%s' ", p->name);
		    if (add_count > maxargs - perm_count) {
			cleanup(0);
			errx(2, "oops, miscounted strings!");
		    }
		    perm_count += add_count;
		}
	    }
	    break;

	case PLIST_CWD:
	    if (Verbose)
		printf("extract: CWD to %s\n", p->name);
	    PUSHOUT(Directory);
	    if (strcmp(p->name, ".")) {
		if (!Fake && make_hierarchy(p->name) == -1) {
		    cleanup(0);
		    errx(2, "unable to make directory '%s'", p->name);
		}
		Directory = p->name;
	    } else
		Directory = home;
	    break;

	case PLIST_CMD:
	    if (!format_cmd(cmd, sizeof(cmd), p->name, Directory, last_file)) {
		cleanup(0);
		if (last_file == NULL)
		    errx(2, "no last file specified for '%s' command", p->name);
		else
		    errx(2, "'%s' command could not expand", p->name);
	    }

	    PUSHOUT(Directory);
	    if (Verbose) {
		system("echo current wd is: $(pwd); ls -la");
		printf("extract: execute '%s'\n", cmd);
	    }
	    if (!Fake && system(cmd))
		pwarnx("command '%s' failed", cmd);
//	    if (Verbose) {
//		system("echo pause; read x");
//	    }
	    break;

	case PLIST_DIR_RM:
	    inc_dir_counter(p->name, &usedb, ourdb);
	    break;

	case PLIST_CHMOD:
	    PUSHOUT(Directory);
	    Mode = p->name;
	    break;

	case PLIST_CHOWN:
	    PUSHOUT(Directory);
	    Owner = p->name;
	    break;

	case PLIST_CHGRP:
	    PUSHOUT(Directory);
	    Group = p->name;
	    break;

	case PLIST_COMMENT:
	    break;

	case PLIST_IGNORE:
	    p = p->next;
	    break;

	case PLIST_SAMPLE:
	    PUSHOUT(Directory);
	    if (!p->name) {
		pwarnx("sample: empty file name");
		break;
	    }
	    if (p->name[strlen(p->name) - 1] == '/') {
		/* cut off trailing / */
		tmp = strdup(toabs(p->name, Directory));
		if (!tmp) {
		    cleanup(0);
		    errx(2, "Out of memory!");
		}
		tmp[strlen(tmp) - 1] = '\0';
		if (Verbose)
		    printf("extract: sample: make directory: %s\n", tmp);
		if (!Fake && make_hierarchy(tmp) == -1) {
		    cleanup(0);
		    errx(2, "unable to make directory '%s'", tmp);
		}
		free(tmp);
	    } else {
		char *tf, *cp = NULL;
		if (!last_file) {
		    pwarnx("sample: no file given");
		    break;
		}
		tf = toabs(p->name, Directory);
		if (!fexists(tf)) {
		    (void) snprintf(cmd, sizeof(cmd), "cp %s/%s %s",
			Directory, last_file, tf);
		    if (Verbose)
			printf("extract: install configuration file '%s'\n", tf);
		    if (!Fake) {
			if (system(cmd))
			    pwarnx("command '%s' failed", cmd);
			else
			    apply_perms(NULL, tf);
		    }
		} else if (strcmp(cp = MD5File(tf, NULL), find_last_md5(p)))
		    pwarnx("Config file '%s' was NOT updated, please do so yourself using the new version at '%s/%s'",
			tf, Directory, last_file);
		else if (Verbose)
		    printf("extract: Config file '%s' exists, but is the same as '%s/%s'\n",
			tf, Directory, last_file);
	    }
	    break;

	default:
	    break;
	}
	p = p->next;
    }
    if (usedb && rcdb_close(ourdb))
	warn("rcdb_close: not synched correctly");
    PUSHOUT(Directory);
}
