/**	$MirOS$ */
/*	$OpenBSD: lib.h,v 1.14 2003/08/21 20:24:57 espie Exp $	*/

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
 * Include and define various things wanted by the library routines.
 */

#ifndef _INST_LIB_LIB_H_
#define _INST_LIB_LIB_H_

/* Includes */
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/file.h>

#include <ctype.h>
#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "rcdb.h"

/* Usually "rm", but often "echo" during debugging! */
#define REMOVE_CMD		"rm"

/* Usually "rm", but often "echo" during debugging! */
#define RMDIR_CMD		"rmdir"

/* just in case we change the environment variable name */
#define PKG_DBDIR		"PKG_DBDIR"

/* The names of our "special" files */
#define CONTENTS_FNAME		"+CONTENTS"
#define COMMENT_FNAME		"+COMMENT"
#define DESC_FNAME		"+DESC"
#define INSTALL_FNAME		"+INSTALL"
#define DEINSTALL_FNAME		"+DEINSTALL"
#define REQUIRE_FNAME		"+REQUIRE"
#define REQUIRED_BY_FNAME	"+REQUIRED_BY"
#define DISPLAY_FNAME		"+DISPLAY"
#define MTREE_FNAME		"+MTREE_DIRS"

#define CMD_CHAR		'@'	/* prefix for extended PLIST cmd */

/* The name of the "prefix" environment variable given to scripts */
#define PKG_PREFIX_VNAME	"PKG_PREFIX"

/* maximum size of comment that will fit on one line */
#ifndef MAXINDEXSIZE
#define MAXINDEXSIZE 72
#endif

/* enumerated constants for plist entry types */
typedef enum pl_ent_t {
	PLIST_SHOW_ALL = -1,
	PLIST_FILE,
	PLIST_CWD,
	PLIST_CMD,
	PLIST_CHMOD,
	PLIST_CHOWN,
	PLIST_CHGRP,
	PLIST_COMMENT,
	PLIST_ARCH,
	PLIST_IGNORE,
	PLIST_NAME,
	PLIST_UNEXEC,
	PLIST_SRC,
	PLIST_DISPLAY,
	PLIST_PKGDEP,
	PLIST_MTREE,
	PLIST_DIR_RM,
	PLIST_OPTION,
	PLIST_PKGCFL,
	PLIST_EXTRA,
	PLIST_EXTRAUNEXEC,
	PLIST_NEWDEP,
	PLIST_LIBDEP,
	PLIST_INFO,
	PLIST_MAN,
	PLIST_SAMPLE,
	PLIST_LIB,
	PLIST_SHELL,
	PLIST_ENDFAKE,
	PLIST_LDCACHE
} pl_ent_t;

/* Types */

/* this structure describes a packing list entry */
typedef struct plist_t {
	struct plist_t	*prev;		/* previous entry */
	struct plist_t	*next;		/* next entry */
	char		*name;		/* name of entry */
	bool		marked;		/* whether entry has been marked */
	pl_ent_t	type;		/* type of entry */
} plist_t;

/* this structure describes a package's complete packing list */
typedef struct package_t {
	plist_t		*head;		/* head of list */
	plist_t		*tail;		/* tail of list */
} package_t;

enum {
	ChecksumLen = 16,
	LegibleChecksumLen = 33
};

/* type of function to be handed to findmatchingname; return value of this
 * is currently ignored */
typedef int (*matchfn)(const char *found, char *data, int len);

/* Prototypes */
/* Misc */
int		vsystem(const char *, ...)
		    __attribute__((__format__ (printf, 1, 2)));
void		cleanup(int);
char		*make_playpen(char *, size_t, size_t);
char		*where_playpen(void);
void		leave_playpen(char *);
off_t		min_free(const char *);
void            save_dirs(char **c, char **p);
void            restore_dirs(char *c, char *p);

/* String */
char 		*get_dash_string(char **);
char		*copy_string(const char *);
bool		suffix(char *, char *);
void		nuke_suffix(char *);
void		str_lowercase(char *);
char		*toabs(const char *, const char *);
char		*strconcat(const char *, const char *);
int		pmatch(const char *, const char *);
int		findmatchingname(const char *, const char *, matchfn, char *, int); /* doesn't really belong here */
char		*findbestmatchingname(const char *, const char *); /* neither */
int		ispkgpattern(const char *);
char		*strnncpy(char *to, size_t tosize, char *from, size_t cc);

/* File */
bool		fexists(const char *);
bool		isdir(const char *);
bool		islinktodir(const char *);
bool		isemptydir(const char *fname);
bool		isemptyfile(const char *fname);
bool		isfile(const char *);
bool		isURL(const char *);
char		*ensure_tgz(char *);
char		*fileGetURL(char *, char *);
char		*fileURLFilename(char *, char *, int);
char		*fileURLHost(char *, char *, int);
char		*fileFindByPath(char *, char *);
char		*fileGetContents(char *);
bool		make_preserve_name(char *, size_t, char *, char *);
void		write_file(const char *, const char *);
void		copy_file(const char *, const char *, const char *);
void		move_file(const char *, const char *, char *);
void		copy_hierarchy(const char *, char *, bool);
int		delete_hierarchy(char *, bool, bool);
int		unpack(char *, const char *);
int		format_cmd(char *, size_t , const char *, const char *,
		    const char *);

/* Packing list */
plist_t		*new_plist_entry(void);
plist_t		*last_plist(package_t *);
plist_t		*find_plist(package_t *, pl_ent_t, const char *);
char		*find_plist_option(package_t *, const char *);
void		plist_delete(package_t *, bool, pl_ent_t, char *);
void		free_plist(package_t *);
void		mark_plist(package_t *);
void		csum_plist_entry(char *, plist_t *);
void		add_plist(package_t *, pl_ent_t, const char *);
void		add_plist_top(package_t *, pl_ent_t, const char *);
void		add_plist_at(package_t *, plist_t *, pl_ent_t, const char *);
void		add_plist_glob(package_t *, plist_t *, const char *, const char *);
void		delete_plist(package_t *pkg, bool all, pl_ent_t type, char *name);
void		write_plist(package_t *, FILE *);
void		read_plist(package_t *, FILE *);
int		plist_cmd(char *, char **);
int		delete_package(bool, bool, bool, bool, package_t *);
int		process_dirrm(plist_t *, bool, int *, RCDB *, const char *);
void		delete_extra(const char *, bool);

/* For all */
int		pkg_perform(char **);

void		set_pkg(char *);
void 		pwarnx(const char *, ...)
		    __attribute__((__format__ (printf, 1, 2)));
void 		pwarn(const char *, ...)
		    __attribute__((__format__ (printf, 1, 2)));

/* Externs */
extern bool	Verbose;
extern bool	Fake;
extern bool	Force;

#ifndef	__SCCSID
#define	__SCCSID(x)	static const char sccsid[] = x
#endif

#ifndef	__RCSID
#define	__RCSID(x)	static const char rcsid[] = x
#endif

#endif /* _INST_LIB_LIB_H_ */
