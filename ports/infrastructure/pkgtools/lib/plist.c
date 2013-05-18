/**	$MirOS: ports/infrastructure/pkgtools/lib/plist.c,v 1.19 2010/03/15 17:25:31 tg Exp $ */
/*	$OpenBSD: plist.c,v 1.17 2003/08/21 20:24:57 espie Exp $	*/

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
 * General packing list routines.
 */

#include "lib.h"
#include <glob.h>
#include <err.h>
#include <md5.h>
#include "rcdb.h"

__RCSID("$MirOS: ports/infrastructure/pkgtools/lib/plist.c,v 1.19 2010/03/15 17:25:31 tg Exp $");

/* this struct defines a plist command type */
typedef struct cmd_t {
	const char	*c_s;		/* string to recognise */
	pl_ent_t	c_type;		/* type of command */
	int		c_argc;		/* # of arguments */
} cmd_t;

/* commands to recognise */
static cmd_t	cmdv[] = {
	{	"cwd",		PLIST_CWD,		1	},
	{	"src",		PLIST_SRC,		1	},
	{	"cd",		PLIST_CWD,		1	},
	{	"exec",		PLIST_CMD,		1	},
	{	"unexec",	PLIST_UNEXEC,		1	},
	{	"mode",		PLIST_CHMOD,		1	},
	{	"owner",	PLIST_CHOWN,		1	},
	{	"group",	PLIST_CHGRP,		1	},
	{	"comment",	PLIST_COMMENT,		1	},
	{	"ignore",	PLIST_IGNORE,		0	},
	{	"name",		PLIST_NAME,		1	},
	{	"display",	PLIST_DISPLAY,		1	},
	{	"pkgdep",	PLIST_PKGDEP,		1	},
	{	"pkgcfl",	PLIST_PKGCFL,		1	},
	{	"mtree",	PLIST_MTREE,		1	},
	{	"dirrm",	PLIST_DIR_RM,		1	},
	{	"option",	PLIST_OPTION,		1	},
	{	"newdepend",	PLIST_NEWDEP,		1	},
	{	"libdepend",	PLIST_LIBDEP,		1	},
	{	"extra",	PLIST_EXTRA,		1	},
	{	"extraunexec",	PLIST_EXTRAUNEXEC,	1	},
	{	"info",		PLIST_INFO,		1	},
	{	"man",		PLIST_MAN,		1	},
	{	"sample",	PLIST_SAMPLE,		1	},
	{	"lib",		PLIST_LIB,		1	},
	{	"shell",	PLIST_SHELL,		1	},
	{	"endfake",	PLIST_ENDFAKE,		0	},
	{	"ldcache",	PLIST_LDCACHE,		1	},
	{	"emul",		PLIST_EMUL,		1	},
	{	"nolib",	PLIST_NOLIB,		1	},
	{	NULL,		-1,			0	}
};

/* Add an item to the end of a packing list */
void
add_plist(package_t *p, pl_ent_t type, const char *arg)
{
	plist_t *tmp;

	tmp = new_plist_entry();
	tmp->name = copy_string(arg);
	tmp->type = type;
	if (!p->head) {
		p->head = p->tail = tmp;
	} else {
		tmp->prev = p->tail;
		p->tail->next = tmp;
		p->tail = tmp;
	}
}

/* add an item to the start of a packing list */
void
add_plist_top(package_t *p, pl_ent_t type, const char *arg)
{
	plist_t *tmp;

	tmp = new_plist_entry();
	tmp->name = copy_string(arg);
	tmp->type = type;
	if (!p->head) {
		p->head = p->tail = tmp;
	} else {
		tmp->next = p->head;
		p->head->prev = tmp;
		p->head = tmp;
	}
}

/* add an item after a certain entry of a packing list */
void add_plist_at(package_t *p, plist_t *after, pl_ent_t type, const char *arg)
{
	plist_t *tmp;

	tmp = new_plist_entry();
	tmp->name = copy_string(arg);
	tmp->type = type;
	tmp->prev = after;
	tmp->next = after->next;
	after->next = tmp;
	if (tmp->next)
		tmp->next->prev = tmp;
	if (p->tail == after)
		p->tail = tmp;
}

/* glob for files and add them to the packing list; if nodups is set,
 * the file is only added if it is not already in the plist as a file
 * entry.
 */
void
add_plist_glob(package_t *pkg, plist_t *after, const char *dir, const char *pattern,
    bool nodups)
{
	glob_t pglob;
	int fd;
	int i;

	memset(&pglob, 0, sizeof(pglob));
	fd = open(".", O_RDONLY, 0);
	chdir(dir);
	glob(pattern, 0, NULL, &pglob);
	fchdir(fd);
	close(fd);
	for (i = 0; i < pglob.gl_pathc; i++) {
		if (!nodups || !find_plist(pkg, PLIST_FILE, pglob.gl_pathv[i]))
			add_plist_at(pkg, after, PLIST_FILE,
			    strdup(pglob.gl_pathv[i]));
	}
	globfree(&pglob);

}

/* Return the last (most recent) entry in a packing list */
plist_t *
last_plist(package_t *p)
{
	return p->tail;
}

/* Mark all items in a packing list to prevent iteration over them */
void
mark_plist(package_t *pkg)
{
	plist_t	*pp;

	for (pp = pkg->head ; pp ; pp = pp->next) {
		pp->marked = true;
	}
}

/* Find a given item in a packing list and, if so, return it (else NULL) */
plist_t *
find_plist(package_t *pkg, pl_ent_t type, const char *name)
{
	plist_t	*pp;

	for (pp = pkg->head;
	    pp && (pp->type != type || (name && strcmp(name,pp->name)));
	    pp = pp->next)
		; /* nothing */
	return pp;
}

/* Look for a specific boolean option argument in the list */
char *
find_plist_option(package_t *pkg, const char *name)
{
	plist_t	*p;

	for (p = pkg->head ; p ; p = p->next) {
		if (p->type == PLIST_OPTION && strcmp(p->name, name) == 0) {
			return p->name;
		}
	}
	return NULL;
}

/*
 * Delete plist item 'type' in the list (if 'name' is non-null, match it
 * too.)  If 'all' is set, delete all items, not just the first occurance.
 */
void
delete_plist(package_t *pkg, bool all, pl_ent_t type, char *name)
{
    plist_t *p = pkg->head;

    while (p) {
	plist_t *pnext = p->next;

	if (p->type == type && (!name || !strcmp(name, p->name))) {
	    free(p->name);
	    if (p->prev)
		p->prev->next = pnext;
	    else
		pkg->head = pnext;
	    if (pnext)
		pnext->prev = p->prev;
	    else
		pkg->tail = p->prev;
	    free(p);
	    if (!all)
		return;
	    p = pnext;
	}
	else
	    p = p->next;
    }
}

/* Allocate a new packing list entry */
plist_t *
new_plist_entry(void)
{
	plist_t *ret;

	if ((ret = (plist_t *)malloc(sizeof(plist_t))) == NULL) {
		err(1, "can't allocate %d bytes", (int)sizeof(plist_t));
	}
	memset(ret, 0, sizeof(plist_t));
	return ret;
}

/* Free an entire packing list */
void
free_plist(package_t *pkg)
{
    plist_t *p = pkg->head;

    while (p) {
	plist_t *p1 = p->next;

	free(p->name);
	free(p);
	p = p1;
    }
    pkg->head = pkg->tail = NULL;
}

/*
 * For an ascii string denoting a plist command, return its code and
 * optionally its argument(s)
 */
int
plist_cmd(char *s, char **arg)
{
	cmd_t	*cmdp;
	char	cmd[FILENAME_MAX + 20];	/* 20 == fudge for max cmd len */
	char	*cp;
	char	*sp;

	(void) strlcpy(cmd, s, sizeof(cmd));
	str_lowercase(cmd);
	for (cp = cmd, sp = s ; *cp ; cp++, sp++) {
		if (isspace(*cp)) {
			for (*cp = '\0'; isspace(*sp) ; sp++) {
			}
			break;
		}
	}
	if (arg) {
		*arg = sp;
	}
	for (cmdp = cmdv ; cmdp->c_s && strcmp(cmdp->c_s, cmd) != 0 ; cmdp++) {
	}
	return cmdp->c_type;
}

/* Read a packing list from a file */
void
read_plist(package_t *pkg, FILE *fp)
{
    char *cp, pline[FILENAME_MAX];
    int cmd;

    while (fgets(pline, FILENAME_MAX, fp)) {
	int len = strlen(pline);

	while (len && isspace(pline[len - 1]))
	    pline[--len] = '\0';
	if (!len)
	    continue;
	cp = pline;
	if (pline[0] == CMD_CHAR) {
	    cmd = plist_cmd(pline + 1, &cp);
	    if (cmd == -1) {
		pwarnx("Unrecognised PLIST command '%s'", pline);
		continue;
	    }
	    if (*cp == '\0')
		cp = NULL;
	}
	else
	    cmd = PLIST_FILE;
	add_plist(pkg, cmd, cp);
    }
}

/* Write a packing list to a file, converting commands to ascii equivs */
void
write_plist(package_t *pkg, FILE *fp)
{
	plist_t	*p;
	cmd_t	*cmdp;

	for (p = pkg->head ; p ; p = p->next) {
		if (p->type == PLIST_FILE) {
			/* Fast-track files - these are the most common */
			(void) fprintf(fp, "%s\n", p->name);
			continue;
		}
		for (cmdp = cmdv ; cmdp->c_type != -1 && cmdp->c_type != p->type ; cmdp++) {
		}
		if (cmdp->c_type == -1) {
			pwarnx("Unknown PLIST command type %d (%s)", p->type, p->name);
		} else if (cmdp->c_argc == 0) {
			(void) fprintf(fp, "%c%s\n", CMD_CHAR, cmdp->c_s);
		} else {
			(void) fprintf(fp, "%c%s %s\n", CMD_CHAR, cmdp->c_s,
					(p->name) ? p->name : "");
		}
	}
}

/*
 * Delete the results of a package installation.
 *
 * This is here rather than in the pkg_delete code because pkg_add needs to
 * run it too in cases of failure.
 */
int
delete_package(bool keep_files, bool nukedirs, rm_cfg_t remove_config,
    bool check_md5, package_t *pkg)
{
    plist_t *p, *pp;
    const char *Where = ".", *last_file = "";
    int fail = 0;
    int len;
    char tmp[FILENAME_MAX], *cp;
    static int usedb = 1;
    RCDB *ourdb;

    if ((ourdb = rcdb_open((cp = getenv("PKG_REFCNTDB")) ? cp : _PATH_REFCNTDB)) == NULL) {
	warn("rcdb_open: not using db");
	usedb = 0;
    }

    for (p = pkg->head; p; p = p->next) {
	switch (p->type)  {
	case PLIST_IGNORE:
	    p = p->next;
	    break;

	case PLIST_CWD:
	    Where = p->name;
	    if (Verbose)
		printf("Change working directory to %s\n", Where);
	    break;

	case PLIST_EXTRAUNEXEC:
	    if (!remove_config)
	    	break;
	    /*FALLTHRU*/
	case PLIST_UNEXEC:
	    if (!format_cmd(tmp, sizeof(tmp), p->name, Where, last_file)) {
	    	pwarnx("unexec command '%s' could not expand", p->name);
		fail = -1;
	    } else {
		if (Verbose)
		    printf("Execute '%s'\n", tmp);
		if (!Fake && sxsystem(false, tmp)) {
		    pwarnx("unexec command for '%s' failed", tmp);
		    fail = -1;
		}
	    }
	    break;

	case PLIST_LIB:
	case PLIST_NOLIB:
	case PLIST_SHELL:
	case PLIST_FILE:
	    if (p->name[strlen(p->name) - 1] == '/')
		break;
	    last_file = p->name;
	    if (keep_files)
		break;
	    (void) snprintf(tmp, sizeof(tmp), "%s/%s", Where, p->name);
	    if (isdir(tmp)) {
		pwarnx("attempting to delete directory '%s' as a file\n"
	   "this packing list is incorrect - ignoring delete request", tmp);
	    }
	    else {
		if (check_md5 && p->next && p->next->type == PLIST_COMMENT && !strncmp(p->next->name, "MD5:", 4)) {
		    char buf[LegibleChecksumLen];

		    if ((cp = MD5File(tmp, buf)) != NULL) {
			/* Mismatch? */
			if (strcmp(cp, p->next->name + 4)) {
			    printf("%s fails original MD5 checksum - %s\n",
				       tmp, Force ? "deleted anyway." : "not deleted.");
			    if (!Force) {
				fail = -1;
				continue;
			    }
			}
		    }
		}
		if (Verbose)
		    printf("Delete file %s\n", tmp);
		if (!Fake) {
		    if (delete_hierarchy(tmp, false, nukedirs))
		    fail = -1;
		}
	    }
	    break;

	case PLIST_SAMPLE:
	case PLIST_EXTRA:
	    if (!remove_config)
	    	break;
	    if (!p->name)
	    	break;
	    delete_extra(p, Where, remove_config, false);
	    break;
	case PLIST_DIR_RM:
	    last_file = p->name;
	    fail = fail | process_dirrm(p, keep_files, &usedb, ourdb, Where);
	    break;
	default:
	    break;
	}
    }

    /* reversely traverse list for dir/ entries */
    for (p = pkg->tail; p; p = p->prev) {
	if (p->type == PLIST_FILE || (remove_config &&
		(p->type == PLIST_SAMPLE || p->type == PLIST_EXTRA))) {
	    len = strlen(p->name);
	    if (p->name[len - 1] == '/') {
		/* cwd might have changed, hunt for a @cwd entry */
		for (pp = p; pp && pp->type != PLIST_CWD; pp = pp->prev) {
		}
		if (pp) {
		    Where = pp->name;
		}
		if (p->type == PLIST_FILE) {
		    p->name[--len] = '\0';
		    fail = fail | process_dirrm(p, keep_files, &usedb, ourdb, Where);
		} else
		    delete_extra(p, Where, remove_config, true);
	    }
	}
    }

    if (usedb && rcdb_close(ourdb))
	warn("rcdb_close: not synched correctly");
    return fail;
}

int
process_dirrm(plist_t *p, bool keep_files, int *usedb, RCDB *ourdb,
    const char *Where)
{
    recno_t rr;
    char tmp[FILENAME_MAX];
    int64_t rcount = 0;

    if (*usedb) {
	if ((rr = rcdb_lookup(ourdb, p->name)) == (recno_t)-1) {
	    warn("rcdb_lookup");
	    *usedb = 0;
	    rcdb_close(ourdb);
	}
	if (rr) {
	    /* found record; will reduce number by one
	     * and delete record and dir if zero */
	    if (rcdb_read(ourdb, rr, &rcount) == -1) {
		warn("rcdb_read");
		*usedb = 0;
		rcdb_close(ourdb);
	    }
	    if (!rcount)	/* wrong entry */
		rcount = 1;
	    if (rcount--) {
		if (!Fake && rcount && rcdb_modify(ourdb, rr, rcount,
			p->name) == -1) {
		    warn("rcdb_modify");
		    *usedb = 0;
		    rcdb_close(ourdb);
		} else if (!Fake && !rcount && rcdb_delete(ourdb, rr) == -1) {
		    warn("rcdb_delete");
		    *usedb = 0;
		    rcdb_close(ourdb);
		}
	    }
	} /* else record not in database, go on */
    }
    if (rcount)
	return 0;

    (void) snprintf(tmp, sizeof(tmp), "%s/%s", Where, p->name);
    if (!isdir(tmp)) {
	if (fexists(tmp)) {
	    pwarnx("attempting to delete file '%s' as a directory\n"
	       "this packing list is incorrect - ignoring delete request", tmp);
	} else {
	    pwarnx("attempting to delete non-existent directory '%s'\n"
	       "this packing list is incorrect - ignoring delete request", tmp);
	}
    } else if (!keep_files) {
	if (Verbose)
	    printf("Delete directory %s\n", tmp);
	if (!Fake && delete_hierarchy(tmp, false, false)) {
	    pwarnx("unable to completely remove directory '%s'", tmp);
	    return -1;
	}
    }
    return 0;
}

#ifdef DEBUG
#define RMDIR(dir)	RM_DEBUG(RMDIR_CMD, "", (dir))
#define REMOVE(dir, ie)	RM_DEBUG(REMOVE_CMD, ((ie) ? "-f " : ""), (dir))
#define RM_DEBUG(cmd, arg1, arg2) ({				\
	int rv;							\
	char *a2;						\
	a2 = format_arg(arg2);					\
	rv = xsystem(false, "%s %s%s", (cmd), (arg1), a2);	\
	xfree(a2);						\
	(rv);							\
})
#else
#define RMDIR rmdir
#define	REMOVE(file,ie) (remove(file) && !(ie))
#endif

/* Selectively delete a hierarchy */
int
delete_hierarchy(char *dir, bool ign_err, bool nukedirs)
{
    char *cp1, *cp2;

    cp1 = cp2 = dir;
    if (!fexists(dir)) {
	if (!ign_err)
	    pwarnx("%s '%s' doesn't really exist",
		isdir(dir) ? "directory" : "file", dir);
	return !ign_err;
    }
    else if (nukedirs) {
	int rv;
	cp1 = format_arg(dir);
	rv = xsystem(false, "%s -r%s %s", REMOVE_CMD, ign_err ? "f" : "", cp1);
	xfree(cp1);
	if (rv)
	    return 1;
	cp1 = dir;
    }
    else if (isdir(dir)) {
	if (RMDIR(dir) && !ign_err)
	    return 1;
    }
    else {
	if (REMOVE(dir, ign_err))
	    return 1;
    }

    if (!nukedirs)
	return 0;
    while (cp2) {
	if ((cp2 = strrchr(cp1, '/')) != NULL)
	    *cp2 = '\0';
	if (!isemptydir(dir))
	    return 0;
	if (RMDIR(dir) && !ign_err) {
	    if (!fexists(dir))
		pwarnx("directory '%s' doesn't really exist", dir);
	    else
		return 1;
	}
	/* back up the pathname one component */
	if (cp2) {
	    cp1 = dir;
	}
    }
    return 0;
}

/* Delete extra files and directories (@extra, @sample).
 * the 'dir' parameter defines whether only files or only directories
 * will be deleted. Rationale: dirs will be removed in a second pass
 * after the files.
 */
void
delete_extra(plist_t *p, const char *Where, const rm_cfg_t remove_config, bool dir)
{
    char *fname;
    char *cp, buf[LegibleChecksumLen];
    size_t len;
    bool b;

    if (!p || !Where || !remove_config)
	return;

    fname = toabs(p->name, Where);
    len = strlen(fname);
    if (len == 0) {
	pwarnx("empty extra filename");
	return;
    }
    /* don't warn if stuff does not exist */
    if (!fexists(fname))
	return;

    b = isdir(fname);
    if (dir) {
	if (b && remove_config == RMCFG_ALL) {
	    if (Verbose)
		printf("Delete extra directory %s\n", fname);
	    if (!Fake && rmdir(fname) == -1)
		pwarn("problem removing directory %s",
		    fname);
	} else if (!b) {
	    pwarnx("extra directory %s is not a directory",
		fname);
	}
    } else if (fname[len - 1] != '/') {
	if (b) {
	    pwarnx("extra file %s is a directory", fname);
	} else {
	    if (remove_config == RMCFG_UNCHANGED
		    && p->prev->type == PLIST_COMMENT
		    && !strncmp(p->prev->name, "MD5:", 4)
		    && (cp = MD5File(fname, buf)) != NULL) {
		/* Mismatch? */
		if (strcmp(cp, p->prev->name + 4)) {
		    if (Verbose)
			printf("Extra file %s was changed -- not removing it\n", fname);
		    return;
		}
	    }

	    if (Verbose)
		printf("Delete extra file %s\n", fname);
	    if (!Fake && unlink(fname) == -1)
		pwarn("problem removing %s", fname);
	}
    }
}
