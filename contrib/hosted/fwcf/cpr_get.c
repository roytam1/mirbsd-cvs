/* $MirOS: contrib/hosted/fwcf/cpr_get.c,v 1.2 2006/09/23 23:21:04 tg Exp $ */

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

#include "defs.h"
#include "compress.h"

__RCSID("$MirOS: contrib/hosted/fwcf/cpr_get.c,v 1.2 2006/09/23 23:21:04 tg Exp $");

fwcf_compressor *
compressor_get(uint8_t algo)
{
	fwcf_compressor *list;

	if ((list = compress_enumerate()) == NULL)
		errx(1, "compress_enumerate");
	if (list[algo].name == NULL)
		errx(1, "compression algorithm %02Xh not loaded", algo);
	if (list[algo].init())
		errx(1, "cannot initialise %s compression", list[algo].name);

	return (&(list[algo]));
}
