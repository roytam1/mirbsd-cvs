/* $MirOS: contrib/hosted/fwcf/fts_subs.c,v 1.3 2006/09/16 01:54:33 tg Exp $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
 */

#include <sys/param.h>
#include <sys/stat.h>
#include <err.h>
#include <errno.h>
#include <fts.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FTSF_INTERNALS
#include "fts_subs.h"

__RCSID("$MirOS: contrib/hosted/fwcf/fts_subs.c,v 1.3 2006/09/16 01:54:33 tg Exp $");

static FTS *handle;

char ftsf_prefix[PATH_MAX];
size_t ftsf_prefixlen;

void
ftsf_start(const char *root)
{
	char *paths[2];

	if (handle != NULL) {
		if (fts_close(handle))
			warn("fts_close");
		free(handle);
	}

	if (realpath(root, ftsf_prefix) == NULL)
		err(1, "determine realpath for %s", root);
	ftsf_prefixlen = strlen(ftsf_prefix) + 1;

	paths[0] = ftsf_prefix;
	paths[1] = NULL;

	handle = fts_open(paths, FTS_NOCHDIR | FTS_PHYSICAL, NULL);

	if (handle == NULL)
		err(1, "fts_open on %s for %s", ftsf_prefix, root);
}

int
ftsf_next(ftsf_entry *e)
{
	FTSENT *ent;
	char *ename;

	bzero(e, sizeof (ftsf_entry));

	if (handle == NULL) {
		warn("ftsf_next called before ftsf_open");
		return (-1);
	}

 ftsf_continue:
	if ((ent = fts_read(handle)) == NULL) {
		if (errno == 0) {
			if (fts_close(handle))
				warn("fts_close");
			handle = NULL;
			return (0);
		}
		warn("fts_read");
		if (fts_close(handle))
			warn("fts_close");
		handle = NULL;
		return (-1);
	}

	ename = ent->fts_path;
#if 0 /* debug */
	if (asprintf(&ename, "accpath<%s> path<%s> name<%s>", ent->fts_accpath,
	    ent->fts_path, ent->fts_name) == -1)
		err(1, "asprintf");
#endif
	if (strcmp(ename, ftsf_prefix)) {
		if (strlcpy(e->pathname, ename + ftsf_prefixlen,
		    sizeof (e->pathname)) >= sizeof (e->pathname))
			warn("truncating file name '%s' to '%s'", ename,
			    e->pathname);
	} else
		memcpy(e->pathname, ".", 2);

	switch (ent->fts_info) {
	case FTS_D:
		e->etype = FTSF_DIR;
		break;
	case FTS_DNR:
		warn("directory %s not readable, skipping: %s", ename,
		    strerror(ent->fts_errno));
		/* FALLTHROUGH */
	case FTS_DC:
	case FTS_DOT:
	case FTS_DP:
		goto ftsf_continue;
	case FTS_DEFAULT:
		if (S_ISDIR(ent->fts_statp->st_mode))
			e->etype = FTSF_DIR;
		else if (S_ISREG(ent->fts_statp->st_mode))
			e->etype = FTSF_FILE;
		else if (S_ISLNK(ent->fts_statp->st_mode))
			e->etype = FTSF_SYMLINK;
		else
			e->etype = FTSF_OTHER;
		break;
	case FTS_ERR:
		warn("generic error condition %s on %s, skipping",
		    strerror(ent->fts_errno), ename);
		goto ftsf_continue;
	case FTS_F:
		e->etype = FTSF_FILE;
		break;
	case FTS_NSOK:
		ent->fts_errno = 0;
		/* FALLTHROUGH */
	case FTS_NS:
		warn("skipping due to no stat(2) information on %s: %s",
		    ename, strerror(ent->fts_errno));
		goto ftsf_continue;
	case FTS_SL:
	case FTS_SLNONE:
		e->etype = FTSF_SYMLINK;
		break;
	default:
		warn("unknown fts_info field for %s: %d, skipping",
		    ename, (int)ent->fts_info);
		warn("ent->fts_errno = %d (%s)", ent->fts_errno,
		    strerror(ent->fts_errno));
		goto ftsf_continue;
	}

	e->statp = ent->fts_statp;
	return (1);
}

void
ftsf_debugent(ftsf_entry *e)
{
	fprintf(stderr,
	    "%s @%08X %06o %2u %u %06llX %lu:%lu %s/\033[1m%s\033[0m%c\n",
	    (e->etype == FTSF_DIR ? "DIR" : e->etype == FTSF_FILE ? "REG" :
	    e->etype == FTSF_SYMLINK ? "SYM" : "OTH"),
	    (unsigned)e->statp->st_ino, (unsigned)e->statp->st_mode,
	    e->statp->st_nlink, (unsigned)e->statp->st_mtime,
	    (uint64_t)e->statp->st_size, (u_long)e->statp->st_uid,
	    (u_long)e->statp->st_gid, ftsf_prefix, e->pathname,
	    ((e->statp->st_mode & S_IFMT) == S_IFDIR ? '/' :
	    (e->statp->st_mode & S_IFMT) == S_IFIFO ? '|' :
	    (e->statp->st_mode & S_IFMT) == S_IFLNK ? '@' :
	    (e->statp->st_mode & S_IFMT) == S_IFSOCK ? '=' :
	    (e->statp->st_mode & S_IFMT) == S_IFBLK ? '&' :
	    (e->statp->st_mode & S_IFMT) == S_IFCHR ? '%' :
	    (e->statp->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) ? '*' : '_'));
}
