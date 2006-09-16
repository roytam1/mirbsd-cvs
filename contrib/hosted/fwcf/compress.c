/* $MirOS: contrib/hosted/fwcf/compress.c,v 1.3 2006/09/16 06:18:57 tg Exp $ */

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
#include <stdio.h>
#include <stdlib.h>

#include "compress.h"

__RCSID("$MirOS: contrib/hosted/fwcf/compress.c,v 1.3 2006/09/16 06:18:57 tg Exp $");

#ifdef DEBUG
#undef __inline
#define __inline /* nothing */
#endif

static void compress_initialise(void);

static fwcf_compressor *fwcf_compressors = NULL;

int
compress_register(fwcf_compressor *e)
{
	compress_initialise();
	if (e == NULL)
		return (1);

	if ((e->init == NULL) || (e->compress == NULL) ||
	    (e->decompress == NULL) || (e->name == NULL))
		return (1);
	if (fwcf_compressors[e->code].name != NULL)
		return (2);

	fwcf_compressors[e->code] = *e;
	return (0);
}

fwcf_compressor *
compress_enumerate(void)
{
	int i;
	fwcf_compressor *rv = NULL;

	compress_initialise();
	for (i = 0; i < 256; ++i)
		if (fwcf_compressors[i].name != NULL) {
			if (fwcf_compressors[i].code == i)
				rv = fwcf_compressors;
			else
				errx(1, "fwcf compressor registry invalid");
		}
	return (rv);
}

static void
compress_initialise(void)
{
	if (fwcf_compressors != NULL)
		return;
	if ((fwcf_compressors = calloc(256, sizeof (fwcf_compressor))) == NULL)
		err(1, "calloc");
}

int
compress_list(void)
{
	fwcf_compressor *cl;
	int i;

	if ((cl = compress_enumerate()) == NULL)
		return (1);

	for (i = 0; i < 256; ++i)
		if (cl[i].name != NULL)
			printf("%02Xh = %s%s\n", cl[i].code,
			    (i < 0xC0 ? "" : "PRIVATE "), cl[i].name);
	return (0);
}

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

int
list_compressors(void)
{
	int rv;

	printf("List of registered compressors:\n");
	if ((rv = compress_list()))
		printf("No compressor registered!\n");
	return (rv);
}
