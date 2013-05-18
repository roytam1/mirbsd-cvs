/* $MirOS: src/bin/md5/suma-mi.c,v 1.5 2006/05/25 12:56:58 tg Exp $ */

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
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 */

#include <sys/param.h>
#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include "suma.h"

void
SUMA_Init(SUMA_CTX *ctx)
{
	if (ctx != NULL)
		*ctx = 0xFFFFFFFF;
}

void
SUMA_Update(SUMA_CTX *ctx, const uint8_t *data, size_t len)
{
	size_t cnt;
	uint32_t crc, eax;
	int i;
	bool cf;

	if ((len == 0) || (ctx == NULL) || (data == NULL))
		return;

	crc = *ctx;
	cnt = len >> 2;
	while (cnt--) {
		eax = (*(data + 3) << 24) |
		    (*(data + 2) << 16) |
		    (*(data + 1) << 8) | *data;
		data += 4;
		for (i = 32; i; --i) {
			cf = !!(crc & 0x80000000);
			crc <<= 1;
			if (eax & 0x80000000)
				++crc;
			eax <<= 1;
			if (cf)
				crc ^= 0x04563521;
		}
	}
	cnt = len & 3;
	if (cnt--) {
		eax = *data++;
		if (cnt--)
			eax |= (*data++) << 8;
		if (cnt--)
			eax |= (*data++) << 16;
		for (i = 32; i; --i) {
			cf = !!(crc & 0x80000000);
			crc <<= 1;
			if (eax & 0x80000000)
				++crc;
			eax <<= 1;
			if (cf)
				crc ^= 0x04563521;
		}
	}
	*ctx = crc;
}

void
SUMA_Final(SUMA_CTX *ctx)
{
	uint32_t crc;
	int i;
	bool cf;

	if (ctx == NULL)
		return;

	crc = *ctx;
	for (i = 32; i; --i) {
		cf = !!(crc & 0x80000000);
		crc <<= 1;
		if (cf)
			crc ^= 0x04563521;
	}
	*ctx = crc;
}
