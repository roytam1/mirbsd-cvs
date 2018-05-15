/*	$NetBSD: vis.c,v 1.35 2006/08/28 20:42:12 christos Exp $	*/

/*-
 * Copyright © 2018
 *	mirabilos <m@mirbsd.org>
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*-
 * Copyright (c) 1999, 2005 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__RCSID("$MirOS: src/lib/libc/gen/vis.c,v 1.3 2010/01/07 22:34:50 tg Exp $");
__RCSID("$OpenBSD: vis.c,v 1.19 2005/09/01 17:15:49 millert Exp $");
__RCSID("$NetBSD: vis.c,v 1.35 2006/08/28 20:42:12 christos Exp $");

#include <sys/types.h>

#include <assert.h>
#include <vis.h>
#include <stdlib.h>

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

extern const uint8_t mbsd_digits_hex[17];

#define isoctal(c)	(((u_char)(c)) >= '0' && ((u_char)(c)) <= '7')
#define iswhite(c)	(c == ' ' || c == '\t' || c == '\n')
#define issafe(c)	(c == '\b' || c == '\a' || c == '\r' || isgraph((u_char)(c)))
#define xtoa(c)		mbsd_digits_hex[c]

#define MAXEXTRAS	9


#define MAKEEXTRALIST(flag, extra, orig_str)				      \
do {									      \
	const char *orig = orig_str;					      \
	const char *o = orig;						      \
	char *e;							      \
	while (*o++)							      \
		continue;						      \
	extra = malloc((size_t)((o - orig) + MAXEXTRAS));		      \
	if (!extra) break;						      \
	for (o = orig, e = extra; (*e++ = *o++) != '\0';)		      \
		continue;						      \
	e--;								      \
	if (flag & VIS_SP) *e++ = ' ';					      \
	if (flag & VIS_TAB) *e++ = '\t';				      \
	if (flag & VIS_NL) *e++ = '\n';					      \
	if ((flag & VIS_NOSLASH) == 0) *e++ = '\\';			      \
	if (flag & VIS_GLOB) {						      \
		*e++ = '*';						      \
		*e++ = '?';						      \
		*e++ = '[';						      \
		*e++ = '#';						      \
	}								      \
	*e = '\0';							      \
} while (/*CONSTCOND*/0)


/*
 * This is HVIS, the macro of vis used to HTTP style (RFC 1808)
 */
#define HVIS(dst, c, flag, nextc, extra)				      \
do									      \
	if (!isascii(c) || !isalnum(c) || strchr("$-_.+!*'(),", c) != NULL) { \
		*dst++ = '%';						      \
		*dst++ = xtoa(((unsigned int)c >> 4) & 0xf);		      \
		*dst++ = xtoa((unsigned int)c & 0xf);			      \
	} else {							      \
		SVIS(dst, c, flag, nextc, extra);			      \
	}								      \
while (/*CONSTCOND*/0)

/*
 * This is SVIS, the central macro of vis.
 * dst:	      Pointer to the destination buffer
 * c:	      Character to encode
 * flag:      Flag word
 * nextc:     The character following 'c'
 * extra:     Pointer to the list of extra characters to be
 *	      backslash-protected.
 */
#define SVIS(dst, c, flag, nextc, extra)				      \
do {									      \
	int isextra;							      \
	isextra = strchr(extra, c) != NULL;				      \
	if (!isextra && isascii(c) && (isgraph(c) || iswhite(c) ||	      \
	    ((flag & VIS_SAFE) && issafe(c)))) {			      \
		*dst++ = c;						      \
		break;							      \
	}								      \
	if (flag & VIS_CSTYLE) {					      \
		switch (c) {						      \
		case '\n':						      \
			*dst++ = '\\'; *dst++ = 'n';			      \
			continue;					      \
		case '\r':						      \
			*dst++ = '\\'; *dst++ = 'r';			      \
			continue;					      \
		case '\b':						      \
			*dst++ = '\\'; *dst++ = 'b';			      \
			continue;					      \
		case '\a':						      \
			*dst++ = '\\'; *dst++ = 'a';			      \
			continue;					      \
		case '\v':						      \
			*dst++ = '\\'; *dst++ = 'v';			      \
			continue;					      \
		case '\t':						      \
			*dst++ = '\\'; *dst++ = 't';			      \
			continue;					      \
		case '\f':						      \
			*dst++ = '\\'; *dst++ = 'f';			      \
			continue;					      \
		case ' ':						      \
			*dst++ = '\\'; *dst++ = 's';			      \
			continue;					      \
		case '\0':						      \
			*dst++ = '\\'; *dst++ = '0';			      \
			if (isoctal(nextc)) {				      \
				*dst++ = '0';				      \
				*dst++ = '0';				      \
			}						      \
			continue;					      \
		default:						      \
			if (isgraph(c)) {				      \
				*dst++ = '\\'; *dst++ = c;		      \
				continue;				      \
			}						      \
		}							      \
	}								      \
	if (isextra || ((c & 0177) == ' ') || (flag & VIS_OCTAL)) {	      \
		*dst++ = '\\';						      \
		*dst++ = (u_char)(((u_int32_t)(u_char)c >> 6) & 03) + '0';    \
		*dst++ = (u_char)(((u_int32_t)(u_char)c >> 3) & 07) + '0';    \
		*dst++ =			     (c	      & 07) + '0';    \
	} else {							      \
		if ((flag & VIS_NOSLASH) == 0) *dst++ = '\\';		      \
		if (c & 0200) {						      \
			c &= 0177; *dst++ = 'M';			      \
		}							      \
		if (iscntrl(c)) {					      \
			*dst++ = '^';					      \
			if (c == 0177)					      \
				*dst++ = '?';				      \
			else						      \
				*dst++ = c + '@';			      \
		} else {						      \
			*dst++ = '-'; *dst++ = c;			      \
		}							      \
	}								      \
} while (/*CONSTCOND*/0)


/*
 * svis - visually encode characters, also encoding the characters
 *	  pointed to by `extra'
 */
char *
svis(char *dst, int c, int flag, int nextc, const char *extra)
{
	char *nextra = NULL;

	MAKEEXTRALIST(flag, nextra, extra);
	if (!nextra) {
		*dst = '\0';		/* can't create nextra, return "" */
		return dst;
	}
	if (flag & VIS_HTTPSTYLE)
		HVIS(dst, c, flag, nextc, nextra);
	else
		SVIS(dst, c, flag, nextc, nextra);
	free(nextra);
	*dst = '\0';
	return dst;
}


/*
 * strsvis, strnsvis, strsvisx - visually encode characters from src into dst
 *
 *	Extra is a pointer to a \0-terminated list of characters to
 *	be encoded, too. These functions are useful e. g. to
 *	encode strings in such a way so that they are not interpreted
 *	by a shell.
 *
 *	Dst must be 4 times the size of src to account for possible
 *	expansion.  The length of dst, not including the trailing NUL,
 *	is returned.
 *
 *	Strsvisx encodes exactly len bytes from src into dst.
 *	This is useful for encoding a block of data.
 */
int
strsvis(char *dst, const char *csrc, int flag, const char *extra)
{
	int c;
	char *start;
	char *nextra = NULL;
	const unsigned char *src = (const unsigned char *)csrc;

	MAKEEXTRALIST(flag, nextra, extra);
	if (!nextra) {
		*dst = '\0';		/* can't create nextra, return "" */
		return 0;
	}
	if (flag & VIS_HTTPSTYLE) {
		for (start = dst; (c = *src++) != '\0'; /* empty */)
			HVIS(dst, c, flag, *src, nextra);
	} else {
		for (start = dst; (c = *src++) != '\0'; /* empty */)
			SVIS(dst, c, flag, *src, nextra);
	}
	free(nextra);
	*dst = '\0';
	return (dst - start);
}


int
strnsvis(char *dst, const char *src, size_t siz, int flag, const char *extra)
{
	char *start, *end;
	char tbuf[5];
	int c, i;
	char *nextra = NULL;
	const char *srcend = src + strlen(src);

	MAKEEXTRALIST(flag, nextra, extra);
	if (!nextra) {
		*dst = '\0';		/* can't create nextra, return "" */
		return 0;
	}

	i = 0;
	for (start = dst, end = start + siz - 1; (c = *src) && dst < end; ) {
		if (flag & VIS_UTF8) {
			wchar_t Wc;

			Wc = (unsigned char)src[0];
			if (Wc < 0xC2 || Wc >= 0xF0)
				goto utfout;
			else if (Wc < 0xE0) {
				i = 1;
				Wc = (Wc & 0x1F) << 6;
			} else {
				i = 2;
				Wc = (Wc & 0x0F) << 12;
			}
			if (srcend - src <= i)
				goto utfout;
			if (((unsigned char)src[1] ^ 0x80) > 0x3F)
				goto utfout;
			if (i > 1) {
				if (((unsigned char)src[2] ^ 0x80) > 0x3F)
					goto utfout;
				Wc |= ((unsigned char)src[1] ^ 0x80) << 6;
				if (Wc < 0x0800)
					goto utfout;
			}
			Wc |= ((unsigned char)src[i] ^ 0x80);
			/* Wc is now in [0x0080; 0xFFFF] */
			if (dst + ++i >= end)
				goto utfout;
			if (Wc > 0xFFFD || wcwidth(Wc) < 0) {
 utfout:
				/* FALLTHROUGH */;
			} else {
				memcpy(dst, src, i);
				src += i;
				dst += i;
				continue;
			}
		}
		/* unoptimised but safe to extend version */
		i = vis(tbuf, c, flag, *++src) - tbuf;
		if (dst + i <= end) {
			memcpy(dst, tbuf, i);
			dst += i;
		} else {
			src--;
			break;
		}
	}
	if (siz > 0)
		*dst = '\0';
	if (dst + i > end) {
		/* adjust return value for truncation */
		while ((c = *src))
			dst += vis(tbuf, c, flag, *++src) - tbuf;
	}
	free(nextra);
	return (dst - start);
}


int
strsvisx(char *dst, const char *csrc, size_t len, int flag, const char *extra)
{
	unsigned char c;
	char *start;
	char *nextra = NULL;
	const unsigned char *src = (const unsigned char *)csrc;

	MAKEEXTRALIST(flag, nextra, extra);
	if (! nextra) {
		*dst = '\0';		/* can't create nextra, return "" */
		return 0;
	}

	if (flag & VIS_HTTPSTYLE) {
		for (start = dst; len > 0; len--) {
			c = *src++;
			HVIS(dst, c, flag, len ? *src : '\0', nextra);
		}
	} else {
		for (start = dst; len > 0; len--) {
			c = *src++;
			SVIS(dst, c, flag, len ? *src : '\0', nextra);
		}
	}
	free(nextra);
	*dst = '\0';
	return (dst - start);
}

/*
 * vis - visually encode characters
 */
char *
vis(char *dst, int c, int flag, int nextc)
{
	char *extra = NULL;
	unsigned char uc = (unsigned char)c;

	MAKEEXTRALIST(flag, extra, "");
	if (! extra) {
		*dst = '\0';		/* can't create extra, return "" */
		return dst;
	}
	if (flag & VIS_HTTPSTYLE)
		HVIS(dst, uc, flag, nextc, extra);
	else
		SVIS(dst, uc, flag, nextc, extra);
	free(extra);
	*dst = '\0';
	return dst;
}


/*
 * strvis, strnvis, strvisx - visually encode characters from src into dst
 *
 *	Dst must be 4 times the size of src to account for possible
 *	expansion.  The length of dst, not including the trailing NUL,
 *	is returned.
 *
 *	Strnvis will write no more than siz-1 bytes (and will NUL terminate).
 *	The number of bytes needed to fully encode the string is returned.
 *
 *	Strvisx encodes exactly len bytes from src into dst.
 *	This is useful for encoding a block of data.
 */
int
strvis(char *dst, const char *src, int flag)
{
	char *extra = NULL;
	int rv;

	MAKEEXTRALIST(flag, extra, "");
	if (!extra) {
		*dst = '\0';		/* can't create extra, return "" */
		return 0;
	}
	rv = strsvis(dst, src, flag, extra);
	free(extra);
	return rv;
}


int
strnvis(char *dst, const char *src, size_t siz, int flag)
{
	char *extra = NULL;
	int rv;

	MAKEEXTRALIST(flag, extra, "");
	if (!extra) {
		*dst = '\0';		/* can't create extra, return "" */
		return 0;
	}
	rv = strnsvis(dst, src, siz, flag, extra);
	free(extra);
	return rv;
}


int
strvisx(char *dst, const char *src, size_t len, int flag)
{
	char *extra = NULL;
	int rv;

	MAKEEXTRALIST(flag, extra, "");
	if (!extra) {
		*dst = '\0';		/* can't create extra, return "" */
		return 0;
	}
	rv = strsvisx(dst, src, len, flag, extra);
	free(extra);
	return rv;
}
