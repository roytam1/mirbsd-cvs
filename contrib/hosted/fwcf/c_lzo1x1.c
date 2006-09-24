/* $MirOS: contrib/hosted/fwcf/c_lzo1x1.c,v 1.1 2006/09/24 21:46:16 tg Exp $ */

/*-
 * MiniLZO (LZO1X-1) compression plug-in for FWCF
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 1, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "compress.h"

__RCSID("$MirOS: contrib/hosted/fwcf/c_lzo1x1.c,v 1.1 2006/09/24 21:46:16 tg Exp $");

#define C_LZO1X1_T1(a,b)			c_lzo1x1_ ## a ## _ ## b
#define C_LZO1X1_T2(a,b)			C_LZO1X1_T1(a,b)
#define LZO_COMPILE_TIME_ASSERT_HEADER(e)	\
		extern int C_LZO1X1_T2(__LINE__,__lzo_cta)[1-2*!(e)];
#define MINILZO_CFG_SKIP_LZO1X_DECOMPRESS	1
#define MINILZO_CFG_SKIP_LZO_PTR		1
#define MINILZO_CFG_SKIP_LZO_STRING		1
#include "minilzo.c"

static void c_lzo1x1_load(void) __attribute__((constructor));
static int c_init(void);
static int c_compress(char **, char *, size_t)
    __attribute__((bounded (string, 2, 3)));
static int c_decompress(char *, size_t, char *, size_t)
    __attribute__((bounded (string, 1, 2)))
    __attribute__((bounded (string, 3, 4)));

static fwcf_compressor c_lzo1x1 = {
	c_init,			/* init */
	c_compress,		/* compress */
	c_decompress,		/* decompress */
	"lzo1x1",		/* name */
	0x10			/* code */
};

/* Work-memory needed for compression. Allocate memory in units
 * of `lzo_align_t' (instead of `char') to make sure it is properly aligned.
 */

#define HEAP_ALLOC(var,size) \
    lzo_align_t __LZO_MMODEL var [ ((size) + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t) ]

static HEAP_ALLOC(wrkmem,LZO1X_1_MEM_COMPRESS);

static void
c_lzo1x1_load(void)
{
	if (compress_register(&c_lzo1x1))
		fputs("warning: cannot register compressor 'lzo1x1'!\n", stderr);
}

static int
c_init(void)
{
	return ((lzo_init() == LZO_E_OK) ? 0 : 1);
}

static int
c_compress(char **dst, char *src, size_t len)
{
	lzo_bytep ldst;
	lzo_uint ldlen = len + (len / 16) + 64 + 3;

	if ((ldst = malloc(ldlen)) == NULL)
		return (-1);
#ifdef DEBUG
	fprintf(stderr, "LZO1X-1 compress %lu bytes -> (%lu)", len, ldlen);
#endif
	lzo1x_1_compress((lzo_bytep)src, len, ldst, &ldlen, wrkmem);
#ifdef DEBUG
	fprintf(stderr, " %lu bytes\n", ldlen);
#endif
	*dst = (char *)ldst;
	return (ldlen);
}

static int
c_decompress(char *dst, size_t dstlen, char *src, size_t srclen)
{
	lzo_uint ldlen = dstlen;
	int i;

#ifdef DEBUG
	fprintf(stderr, "LZO1X decompress %lu -> %lu bytes\n", srclen, dstlen);
#endif
	if (((i = lzo1x_decompress((lzo_bytep)src, srclen, (lzo_bytep)dst,
	    &ldlen, wrkmem)) == LZO_E_OK) || (i == LZO_E_INPUT_NOT_CONSUMED))
		return (ldlen);
#ifdef DEBUG
	fprintf(stderr, "LZO1X decompress error code %d\n", i);
#endif
	return (-1);
}
