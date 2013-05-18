/**	$MirOS: ports/infrastructure/pkgtools/lib/lib.h,v 1.28.2.7 2010/02/27 16:20:19 bsiegert Exp $ */
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
#include <sys/queue.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/file.h>

#include <ctype.h>
#include <dirent.h>
#include <libgen.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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
#define DEPENDS_FNAME		"+DEPENDS"

#define CMD_CHAR		'@'	/* prefix for extended PLIST cmd */

/* The name of the "prefix" environment variable given to scripts */
#define PKG_PREFIX_VNAME	"PKG_PREFIX"

/* maximum size of comment that will fit on one line */
#ifndef MAXINDEXSIZE
#define MAXINDEXSIZE 72
#endif

/* configuration file and directories */
#ifndef SYSCONFDIR
# define SYSCONFDIR "/etc"
#endif
#define CFGDIR SYSCONFDIR "/pkgtools/"
#define DEFAULT_CFGFILE CFGDIR "pkgtools.conf"
#define CACHEDIR CFGDIR "sources/"

/* Types */

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
	PLIST_LDCACHE,
	PLIST_EMUL,
	PLIST_NOLIB
} pl_ent_t;

/* type of dynamic linker */
typedef enum ld_type_t {
	LD_STATIC,
	LD_BSD,
	LD_GNU,
	LD_DYLD
} ld_type_t;

/* remove configuration on pkg_delete? */
typedef enum rm_cfg_t {
	RMCFG_NONE = 0,
	RMCFG_ALL,
	RMCFG_UNCHANGED
} rm_cfg_t;

/* type of compression of binary packages */
typedef enum pkg_cmp_t {
	COMP_NONE = 0,
	COMP_GZIP,
	COMP_LZMA,
	COMP_XZ
} pkg_cmp_t;

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

/* list of package sources */
LIST_HEAD(cfg_sourcelist, cfg_source);
struct cfg_source {
	unsigned long priority;
	bool remote;
	char *source;
	LIST_ENTRY(cfg_source) entries;
};

/* list of matching packages */
TAILQ_HEAD(matchlist, match);
struct match {
	char *pkgname;
	const char *source;
	TAILQ_ENTRY(match) entries;
};

/* type of function to be handed to findmatchingname; return value of this
 * is currently ignored */
typedef int (*matchfn)(const char *found, char *data, int len);

/* Prototypes */
/* Misc */
char		*piperead(const char *);
void		cleanup(int);
char		*make_playpen(char *, size_t, size_t);
char		*where_playpen(void);
void		leave_playpen(char *);
size_t		min_free(const char *);
void            save_dirs(char **c, char **p);
void            restore_dirs(char *c, char *p);
void		drop_privs(void);
void		raise_privs(void);
bool		have_emulation(char *);

/* String */
char 		*get_dash_string(char **);
char		*copy_string(const char *);
bool		suffix(char *, char *);
void		nuke_suffix(char *);
char		*find_version(const char *);
char		*nuke_version(char *, bool);
char		*find_flavour(const char *);
void		str_lowercase(char *);
char		*toabs(const char *, const char *);
char		*strconcat(const char *, const char *);
int		pmatch(const char *, const char *);
int		findmatchingname(const char *, const char *, matchfn, char *, int); /* doesn't really belong here */
int		findmatchingname_file(const char *, const char *, matchfn, char *, int); /* doesn't really belong here */
char		*findbestmatchingname(const char *, const char *); /* neither */
int		ispkgpattern(const char *);
void		normalize_name(char *);
char *		src_index_name(const char *);

/* File */
bool		fexists(const char *);
bool		isdir(const char *);
bool		islink(const char *);
bool		islinktodir(const char *);
bool		isemptydir(const char *);
bool		isemptyfile(const char *);
bool		isfile(const char *);
bool		isURL(const char *);
char		*ensure_tgz(char *);
bool		pkg_existing(const char *, char *, char *, size_t);
char		*fileGetURL(char *, char *);
char		*fileURLFilename(char *, char *, int);
char		*fileURLHost(char *, char *, int);
char		*fileFindByPath(char *, char *);
char		*fileGetContents(char *);
bool		make_preserve_name(char *, size_t, char *, char *);
int		write_file(const char *, const char *, const char *, ...)
		    __attribute__((__format__ (printf, 3, 4)));
void		copy_file(const char *, const char *, const char *);
void		move_file(const char *, const char *, char *);
void		copy_hierarchy(const char *, char *, bool);
int		delete_hierarchy(char *, bool, bool);
int		unpack(char *, const char *);
int		format_cmd(char *, size_t , const char *, const char *,
		    const char *);
int		trim_end(char *);
int		glob_package(char *, size_t, const char *);
void		update_src_index(void);

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
void		add_plist_glob(package_t *, plist_t *, const char *, const char *, bool);
void		delete_plist(package_t *pkg, bool all, pl_ent_t type, char *name);
void		write_plist(package_t *, FILE *);
void		read_plist(package_t *, FILE *);
int		plist_cmd(char *, char **);
int		delete_package(bool, bool, rm_cfg_t, bool, package_t *);
int		process_dirrm(plist_t *, bool, int *, RCDB *, const char *);
void		delete_extra(plist_t *, const char *, const rm_cfg_t, bool);

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

/* mem.c */
void *xcalloc(size_t, size_t);
void *xrealloc(void *, size_t, size_t);
#define xfree(p) xfree_((void **)&(p))
void xfree_(void **);
int xasprintf(char **, const char *, ...)
    __attribute__((nonnull (1)))
    __attribute__((format (printf, 2, 3)));
int xvasprintf(char **, const char *, va_list)
    __attribute__((nonnull (1)))
    __attribute__((format (printf, 2, 0)));
void *xstrdup(const void *);

/* proc.c */
char *format_arg(const char *)
    __attribute__((nonnull (1)));
#define format_comm(args) format_comm_((const char * const *)(args))
char *format_comm_(const char * const *)
    __attribute__((nonnull (1)));
void unlimit(void);
int mirsystem(const char *, bool)
    __attribute__((nonnull (1)));
int xsystem(bool, const char *, ...)
    __attribute__((format (printf, 2, 3)));
int vxsystem(bool, const char *, va_list)
    __attribute__((format (printf, 2, 0)));
int sxsystem(bool, const char *)
    __attribute__((nonnull (2)));

/* configuration file */
bool		cfg_read_config(const char*);
void		cfg_dump_vars(void);
void		cfg_dump_var(const char *);
char*		cfg_expand_vars(char*, size_t);
const char*	cfg_get_pager(void);
void		cfg_add_source(unsigned long, bool, const char*);
bool		cfg_remove_source(const char*);
void		cfg_dump_sources(void);
const struct cfg_sourcelist* cfg_get_sourcelist(void);

/* source list */
struct matchlist* findmatchingname_srcs(const struct cfg_sourcelist*, const char*);
void		matchlist_destroy(struct matchlist*);
 

#endif /* _INST_LIB_LIB_H_ */
