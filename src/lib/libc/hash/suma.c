/*-
 * Copyright (c) 2006, 2007
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <suma.h>

__RCSID("$MirOS: src/lib/libc/hash/suma.c,v 1.2 2007/05/07 15:55:27 tg Exp $");

void
SUMAInit(SUMA_CTX *ctx)
{
	if (ctx != NULL)
		*ctx = 0xFFFFFFFF;
}

void
SUMAUpdate(SUMA_CTX *ctx, const uint8_t *data, size_t len)
{
	size_t cnt;
	uint32_t crc, eax, cf, i;

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
			cf = crc & 0x80000000;
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
SUMAPad(SUMA_CTX *ctx)
{
	uint32_t crc, i, cf;

	if (ctx == NULL)
		return;

	crc = *ctx;
	for (i = 32; i; --i) {
		cf = crc & 0x80000000;
		crc <<= 1;
		if (cf)
			crc ^= 0x04563521;
	}
	*ctx = crc;
}

void
SUMAFinal(uint8_t *dst, SUMA_CTX *ctx)
{
	uint32_t tmp;

	if (dst) {
		SUMAPad(ctx);
		tmp = htobe32(*ctx);
		memcpy(dst, &tmp, 4);
	}
	*ctx = 0;
}
