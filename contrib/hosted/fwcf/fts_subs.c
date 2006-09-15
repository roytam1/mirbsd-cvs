/* $MirOS: src/share/misc/licence.template,v 1.14 2006/08/09 19:35:23 tg Rel $ */

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
#include <stdlib.h>

#include "fts_subs.h"

__RCSID("$MirOS$");

static FTS *handle;

void
ftsf_start(const char *root)
{
	char *paths[2], real_root[PATH_MAX];

	if (handle != NULL) {
		if (fts_close(handle))
			warn("fts_close");
		free(handle);
	}

	if (realpath(root, real_root) == NULL)
		err(1, "determine realpath for %s", root);

	paths[0] = real_root;
	paths[1] = NULL;

	handle = fts_open(paths, FTS_NOCHDIR | FTS_PHYSICAL, NULL);

	if (handle == NULL)
		err(1, "fts_open on %s for %s", real_root, root);
}

int
ftsf_next(ftsf_entry *e)
{
	FTSENT *ent;

	if (handle == NULL) {
		warn("ftsf_next called before ftsf_open");
		return (-1);
	}

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

XXX fill in ftsf_entry *e structure
