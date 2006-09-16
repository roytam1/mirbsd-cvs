/* $MirOS: contrib/hosted/fwcf/wraps.c,v 1.1 2006/09/16 07:09:49 tg Exp $ */

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
#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "defs.h"
#include "adler.h"
#include "compress.h"
#include "fts_subs.h"
#include "pack.h"

__RCSID("$MirOS: contrib/hosted/fwcf/wraps.c,v 1.1 2006/09/16 07:09:49 tg Exp $");

char *
fwcf_pack(const char *dir, int algo, size_t *dstsz)
{
	size_t i, k;
	int j;
	char *data, *cdata;

	ftsf_start(dir);
	data = ft_packm();
	i = *(size_t *)data - sizeof (size_t);
	if (i > 0xFFFFFF)
		errx(1, "inner size of %d too large", i);

	if ((j = compressor_get(algo)->compress(&cdata, data + sizeof (size_t),
	    i)) == -1)
		errx(1, "%s compression failed", compressor_get(algo)->name);
	free(data);

	/* 12 bytes header, padding to 4-byte boundary, 4 bytes trailer */
	k = ((j + 19) / 4) * 4;
#if DEF_FLASHPART > 0xFFFFFF
# error DEF_FLASHPART too large
#endif
	if (k > DEF_FLASHPART)
		errx(1, "%d bytes too large for flash partition of %d KiB",
		    k, DEF_FLASHPART / 1024);
	/* padded to size of flash block */
#if (DEF_FLASHBLOCK & 3)
# error DEF_FLASHBLOCK must be dword-aligned
#endif
	*dstsz = ((i + (DEF_FLASHBLOCK - 1)) / DEF_FLASHBLOCK) * DEF_FLASHBLOCK;
	if ((data = malloc(*dstsz)) == NULL)
		err(1, "malloc");
	mkheader(data, *dstsz, k, i, algo);
	memcpy(data + 12, cdata, j);
	free(cdata);
	k = j + 12;
	while (k & 3)
		data[k++] = 0;
	mktrailer(data, k);
	k += 4;
	while (k < *dstsz) {
		*(uint32_t *)(data + k) = arc4random();
		k += 4;
	}
	return (data);
}
