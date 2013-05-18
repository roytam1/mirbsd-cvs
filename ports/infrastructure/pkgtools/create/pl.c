/**	$MirOS: ports/infrastructure/pkgtools/create/pl.c,v 1.25 2009/10/20 19:32:49 bsiegert Exp $ */
/*	$OpenBSD: pl.c,v 1.11 2003/08/15 00:03:22 espie Exp $	*/

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
 * Routines for dealing with the packing list.
 */

#include "lib.h"
#include "create.h"
#include <errno.h>
#include <err.h>
#include <fcntl.h>
#include <glob.h>
#include <md5.h>
#include <unistd.h>

__RCSID("$MirOS: ports/infrastructure/pkgtools/create/pl.c,v 1.25 2009/10/20 19:32:49 bsiegert Exp $");

ld_type_t LdType = LD_STATIC;

/* library name conversion for darwin */
static bool
convert_dylib(package_t *pkg, plist_t *p, char *cwd)
{
	char *tmp, pattern[FILENAME_MAX];
	size_t len;
	bool rv = false;

	tmp = strstr(p->name, ".so");
	if (!tmp) {
		return false;
	}
	*tmp = '\0';
	snprintf(pattern, sizeof(pattern), "%s.[0-9]*.dylib", p->name);
	add_plist_glob(pkg, p, strconcat(BaseDir, cwd), pattern, true);

	len = strlen(p->name) + 7;	/* .dylib\0 */
	tmp = realloc(p->name, len);
	if (!tmp) {
		pwarn("dylib realloc failed");
		return false;
	}
	strlcat(tmp, ".dylib", len);
	p->name = NULL;
	if (find_plist(pkg, PLIST_FILE, tmp))
		rv = true;
	p->name = tmp;
	p->type = PLIST_FILE;
	return rv;
}

static bool
check_lib(package_t *pkg, plist_t *p, char *cwd)
{
#ifndef AS_USER
	char *tmp;
#endif
#if 0 /* see below */
	size_t len;
#endif
	bool rv = false;

	if (!pkg || !p)
		return false;
	if (!p->name) {
		pwarnx("lib command without filename - the packing list is incorrect");
		return false;
	}

	switch (LdType) {
	case LD_DYLD:
		rv = convert_dylib(pkg, p, cwd);
		break;
	case LD_GNU:
#if 0 /* FIXME */
	    {
		char *tmp;
		size_t len;

		tmp = copy_string(p->name);
		len = strlen(tmp);
		while (len > 3 && strcmp(tmp + len - 3, ".so")) {
			for (; len > 0 && tmp[len] != '.'; len--);
			if (!len)
				break;
			tmp[len] = '\0';
			add_plist_at(pkg, p, PLIST_FILE, strdup(tmp));
		}
		free(tmp);
	    }
#endif
		break;
	case LD_BSD:
#ifndef AS_USER
	    {
		if (!find_plist(pkg, PLIST_UNEXEC, "ldconfig -U"))
			add_plist(pkg, PLIST_UNEXEC, "ldconfig -U");
		if (!find_plist(pkg, PLIST_UNEXEC, "ldconfig -R"))
			add_plist(pkg, PLIST_UNEXEC, "ldconfig -R");
		tmp = strconcat("ldconfig -m %D/", dirname(p->name));
		if (!find_plist(pkg, PLIST_CMD, tmp)) {
			plist_t *q;
			for (q = p; q->next && q->next->type != PLIST_CWD;
				q = q->next);
			add_plist_at(pkg, q, PLIST_CMD, strdup(tmp));
		}
	    }
#endif
		break;
	case LD_STATIC:
		/* We don't need to do anything on static arches */
		break;
	}
	return rv;
}

/* Check a list for files that require preconversion */
void
check_list(char *home, package_t *pkg, bool syshack)
{
	plist_t	*tmp;
	plist_t	*p;
	char	*cwd = home;
	char	*there = NULL;
	char	*cp;
	char	name[FILENAME_MAX];
	char	buf[LegibleChecksumLen];
	int     len;

	for (p = pkg->head ; p ; p = p->next) {
		switch (p->type) {
		case PLIST_OPTION:
			if (!strcmp(p->name, "dylib"))
				LdType = LD_DYLD;
			else if (!strcmp(p->name, "gnu-ld"))
				LdType = LD_GNU;
			else if (!strcmp(p->name, "ldcache"))
				LdType = LD_BSD;
			else if (!strcmp(p->name, "static"))
				LdType = LD_STATIC;
			break;
		case PLIST_CWD:
			cwd = p->name;
			break;
		case PLIST_IGNORE:
			p = p->next;
			break;
		case PLIST_SRC:
			there = p->name;
			break;
		case PLIST_COMMENT:
			if (p->name != NULL &&
			    strcmp(p->name, "no checksum") == 0)
				p = p->next;
			break;
		case PLIST_ENDFAKE:
			p = p->prev;
			delete_plist(pkg, false, PLIST_ENDFAKE, NULL);
			break;
		case PLIST_INFO:
			p->type = PLIST_FILE;
			/* search for other chapter files */
			memset(name, 0, sizeof(name));
			snprintf(name, sizeof(name), "%s-*", p->name);
			add_plist_glob(pkg, p, strconcat(BaseDir, cwd), name, true);
			add_plist_at(pkg, p, PLIST_CMD, strconcat(
			    "install-info --info-dir=%D/info %D/", p->name));
			add_plist_at(pkg, p->next, PLIST_UNEXEC, strconcat(
			    "install-info --delete --info-dir=%D/info %D/", p->name));
			p = p->prev;
			break;
		case PLIST_MAN:
			p->type = PLIST_FILE;
			p = p->prev;
			break;
		case PLIST_LIB:
			if (check_lib(pkg, p, cwd)) {
				p = p->prev;
				delete_plist(pkg, false, p->next->type,
						p->next->name);
				break;
			}
			/* FALLTHROUGH */
		case PLIST_NOLIB:
		case PLIST_SHELL:
		case PLIST_FILE:
			if (!p->name)
				break;
			len = strlen(p->name);
			tmp = NULL;
			if (syshack &&
			    ((!strncmp(p->name, "man/", 4))
			    || (!strncmp(p->name, "info/", 5)))) {
				cp = strconcat("share/", p->name);
				free(p->name);
				p->name = copy_string(cp);
			}
			if (p->name[len - 1] != '/') {   /* not a dir/ entry */
				if (BaseDir)
					(void) snprintf(name, sizeof(name),
					    "%s/%s/%s", BaseDir, there ? there : cwd,
					    p->name);
				else
					(void) snprintf(name, sizeof(name),
					    "%s/%s", there ? there : cwd, p->name);
				if (islink(name))	/* symbolic link */
					break;
				if ((cp = MD5File(name, buf)) != NULL)
					add_plist_at(pkg, p, PLIST_COMMENT, strconcat("MD5:", cp));
			}
			break;
		case PLIST_LDCACHE:
			if (p->name && (p->name[0] == '1'))
				LdType = LD_BSD;
			else
				LdType = LD_STATIC;
			break;
		default:
			break;
		}
	}
}

static int
trylink(const char *from, const char *to)
{
	char	*cp;

	if (link(from, to) == 0) {
		return 0;
	}
	if (errno == ENOENT) {
		/* try making the container directory */
		if ((cp = strrchr(to, '/')) != NULL) {
			xsystem(false, "mkdir -p %.*s", (int)(cp - to), to);
		}
		return link(from, to);
	}
	return -1;
}

#define STARTSTRING "tar cf -"
#define TOOBIG(str) strlen(str) + 6 + strlen(home) + where_count > maxargs
#define PUSHOUT() /* push out string */					\
	if (where_count > sizeof(STARTSTRING)-1) {			\
		    strlcat(where_args, "|tar xpf -", maxargs);		\
		    if (sxsystem(false, where_args)) {			\
			cleanup(0);					\
			errx(2, "can't invoke tar pipeline");		\
		    }							\
		    memset(where_args, 0, maxargs);			\
 		    last_chdir = NULL;					\
		    strlcpy(where_args, STARTSTRING, maxargs);		\
		    where_count = sizeof(STARTSTRING)-1;		\
	}

/*
 * Copy unmarked files in packing list to playpen - marked files
 * have already been copied in an earlier pass through the list.
 */
void
copy_plist(char *home, package_t *plist)
{
    plist_t *p = plist->head;
    char *where = home;
    char *there = NULL;
    char *where_args;
    const char *mythere, *last_chdir, *root = "/";
    size_t maxargs, where_count = 0, add_count;
    struct stat stb;
    dev_t curdir;

    maxargs = sysconf(_SC_ARG_MAX);
    maxargs -= 64;			/* some slop for the tar cmd text,
					   and sh -c */
    where_args = malloc(maxargs);
    if (!where_args) {
	cleanup(0);
	errx(2, "can't get argument list space");
    }

    memset(where_args, 0, maxargs);
    strlcpy(where_args, STARTSTRING, maxargs);
    where_count = sizeof(STARTSTRING)-1;
    last_chdir = 0;

    if (stat(".", &stb) == 0)
	curdir = stb.st_dev;
    else
	curdir = (dev_t) -1;		/* It's ok if this is a valid dev_t;
					   this is just a hint for an
					   optimization. */

    while (p) {
	if (p->type == PLIST_CWD)
	    where = p->name;
	else if (p->type == PLIST_SRC)
	    there = p->name;
	else if (p->type == PLIST_IGNORE)
	    p = p->next;
	else if (p->type == PLIST_FILE && !p->marked) {
	    char fn[FILENAME_MAX];


	    /* First, look for it in the "home" dir */
	    (void) snprintf(fn, sizeof(fn), "%s/%s", home, p->name);
	    if (fexists(fn)) {
		if (lstat(fn, &stb) == 0 && stb.st_dev == curdir &&
		    S_ISREG(stb.st_mode)) {
		    /* if we can link it to the playpen, that avoids a copy
		       and saves time. */
		    if (p->name[0] != '/') {
			/* don't link abspn stuff--it doesn't come from
			   local dir! */
			if (trylink(fn, p->name) == 0) {
			    p = p->next;
			    continue;
			}
		    }
		}
		if (TOOBIG(fn)) {
		    PUSHOUT();
		}
		if (p->name[0] == '/') {
		    add_count = snprintf(&where_args[where_count],
					 maxargs - where_count,
					 " %s %s",
					 last_chdir == root ? "" : "-C /",
					 p->name);
		    last_chdir = root;
		} else {
		    add_count = snprintf(&where_args[where_count],
					 maxargs - where_count,
					 " %s%s %s",
					 last_chdir == home ? "" : "-C ",
					 last_chdir == home ? "" : home,
					 p->name);
		    last_chdir = home;
		}
		if (add_count > maxargs - where_count) {
		    cleanup(0);
		    errx(2, "oops, miscounted strings!");
		}
		where_count += add_count;
	    }
	    /*
	     * Otherwise, try along the actual extraction path..
	     */
	    else {
		if (p->name[0] == '/')
		    mythere = root;
		else mythere = there;
		(void) snprintf(fn, sizeof(fn), "%s/%s", mythere ? mythere : where, p->name);
		if (lstat(fn, &stb) == 0 && stb.st_dev == curdir &&
		    S_ISREG(stb.st_mode)) {
		    /* if we can link it to the playpen, that avoids a copy
		       and saves time. */
		    if (trylink(fn, p->name) == 0) {
			p = p->next;
			continue;
		    }
		}
		if (TOOBIG(p->name)) {
		    PUSHOUT();
		}
		if (last_chdir == (mythere ? mythere : where))
		    add_count = snprintf(&where_args[where_count],
					 maxargs - where_count,
					 " %s", p->name);
		else
		    add_count = snprintf(&where_args[where_count],
					 maxargs - where_count,
					 " -C %s %s",
					 mythere ? mythere : where,
					 p->name);
		if (add_count > maxargs - where_count) {
		    cleanup(0);
		    errx(2, "oops, miscounted strings!");
		}
		where_count += add_count;
		last_chdir = (mythere ? mythere : where);
	    }
	}
	p = p->next;
    }
    PUSHOUT();
    free(where_args);
}
