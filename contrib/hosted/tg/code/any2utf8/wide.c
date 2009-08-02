/* $MirOS: contrib/hosted/tg/deb/any2utf8/wide.c,v 1.3 2009/02/20 19:22:52 tg Exp $ */

/*-
 * Copyright (c) 2008, 2009
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
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

#include <stdlib.h>

/* From MirOS: src/lib/libc/i18n/optu8to16vis.c,v 1.2 2008/11/22 09:02:33 tg Exp */
/* Note: 0x278A..0x278E mappings are placeholders akin to U+2400 ff. */
static unsigned short vistable[32] = {
	0x20AC, 0x278A, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,
	0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0x278B, 0x017D, 0x278C,
	0x278D, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
	0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0x278E, 0x017E, 0x0178,
};

/**
 * For a given multibyte string, decode the first Unicode character
 * found in it; if an encoding error occurs, decode the first octet
 * as if the string were in the ISO-8859-1 or ANSI CP1252 character
 * set instead.
 * From MirOS: src/kern/c/optu8to16.c,v 1.2 2008/08/02 00:10:01 tg Exp
 */
size_t
ucs_8to32(const char *src, unsigned int *dst)
{
	const unsigned char *s = (const unsigned char *)src;
	unsigned int wc, w2, count = 0, isinval = 0;
	unsigned char c;
	static int recurse = 0;

	wc = *s++;
	if (wc < 0xC2 || wc >= 0xFE) {
		if (wc >= 0x80)
			isinval = 1;
	} else if (wc < 0xE0) {
		count = 1; /* one byte follows */
		wc = (wc & 0x1F) << 6;
	} else if (wc < 0xF0) {
		count = 2; /* two bytes follow */
		wc = (wc & 0x0F) << 12;
	} else if (wc < 0xF8) {
		count = 3; /* three bytes follow */
		wc = (wc & 0x07) << 18;
	} else if (wc < 0xFC) {
		count = 4; /* four bytes follow */
		wc = (wc & 0x03) << 24;
	} else /* (wc < 0xFE) */ {
		count = 5; /* five bytes follow */
		wc = (wc & 0x01) << 30;
	}

	while (!isinval) {
		if (((c = *s++) & 0xC0) != 0x80)
			isinval = 1;
		wc |= (c & 0x3F) << (6 * --count);
		if (!count)
			break;
		if (wc < (1U << (5 * count + 6)))
			isinval = 1;
	}
	/* UTF-16 to UCS-4 conversion */
	if (!isinval && wc >= 0xDC00 && wc <= 0xDFFF)
		isinval = 1;
	if (!isinval && !recurse && wc >= 0xD800 && wc <= 0xDBFF) {
		recurse = 1;
		s += ucs_8to32((const char *)s, &w2);
		recurse = 0;
		if (w2 >= 0xDC00 && w2 <= 0xDFFF)
			wc = 0x10000 + ((wc & 0x3FF) << 10) + (w2 & 0x3FF);
		else
			isinval = 1;
	}
	if (wc == 0xFFFE || wc == 0xFFFF || wc > 0x7FFFFFFF ||
	    (wc >= 0xD800 && wc <= 0xDFFF))
		isinval = 1;
	if (isinval) {
		s = (const unsigned char *)src;
		wc = *s++ & 0xFF;		/* ISO 8859-1 */
	}
	if (wc >= 0x80 && wc < 0xA0 && (isinval || fixansi))
		wc = vistable[(int)wc - 0x80];	/* ANSI 1252 */
	*dst = wc;
	return ((size_t)((const char *)s - src));
}

/**
 * For a given wide character (UCS-4), encode it in UTF-8 if the
 * target’s wchar_t is 4 bytes wide, CESU-8 otherwise.
 * From MirOS: src/kern/c/optu16to8.c,v 1.2 2008/11/22 09:02:33 tg Exp
 */
size_t
ucs_32to8(char *dst, unsigned int wc)
{
	unsigned char *cp = (unsigned char *)dst;
	unsigned int count;

#if WCHAR_SIZE == 2
	if (wc > 0x10FFFF)
		wc = 0xFFFD;	/* beyond UTF-16 */
	else if (wc > 0xFFFF) {
		wc -= 0x10000;	/* encode using CESU-8 */
		cp += ucs_32to8(dst, 0xD800 | (wc >> 10));
		wc = 0xDC00 | (wc & 0x3FF);
	}
#else
	if (wc > 0x7FFFFFFF)
		wc = 0xFFFD;	/* beyond UTF-8 */
#endif

	if (wc < 0x80) {
		count = 0;
		*cp++ = wc;
	} else if (wc < 0x0800) {
		count = 1;
		*cp++ = (wc >> 6) | 0xC0;
	} else if (wc < 0x00010000) {
		count = 2;
		*cp++ = (wc >> 12) | 0xE0;
	} else if (wc < 0x00200000) {
		count = 3;
		*cp++ = (wc >> 18) | 0xF0;
	} else if (wc < 0x04000000) {
		count = 4;
		*cp++ = (wc >> 24) | 0xFC;
	} else {
		count = 5;
		*cp++ = (wc >> 30) | 0xFE;
	}

	while (count)
		*cp++ = ((wc >> (6 * --count)) & 0x3F) | 0x80;

	return ((size_t)((char *)cp - dst));
}
