/* $MirOS: src/include/utf.h,v 1.1 2008/11/22 12:56:20 tg Exp $ */

/*-
 * Copyright (c) 2008, 2013
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
 *-
 * Interface for Plan 9’s Rune API, slightly modified yet compatible
 */

#ifndef _UTF_H_
#define _UTF_H_

#include <sys/cdefs.h>

#if !defined(_GCC_SIZE_T)
#define	_GCC_SIZE_T
typedef	__SIZE_TYPE__	size_t;
#endif

#if !defined(_GCC_WCHAR_T) && !defined(__cplusplus)
#define	_GCC_WCHAR_T
typedef	__WCHAR_TYPE__	wchar_t;
#endif

#if !defined(_GCC_WINT_T)
#define	_GCC_WINT_T
typedef	__WINT_TYPE__	wint_t;
#endif

typedef wchar_t Rune;

enum {
	UTFmax = 3,		/* maximum number of octets per Rune */
	Runesync = 0x80,	/* cannot represent part of UTF sequence (<) */
	Runeself = 0x80,	/* rune and UTF sequences are the same (<) */
	Runeerror = 0xFFFE	/* decoding error in UTF */
};

__BEGIN_DECLS
size_t chartorune(Rune *, const char *)
    __attribute__((__nonnull__(1, 2)));
int fullrune(const char *, size_t)
    __attribute__((__nonnull__(1)))
    __attribute__((__bounded__(__string__, 1, 2)));
int isalpharune(Rune);
int islowerrune(Rune);
int isspacerune(Rune);
int istitlerune(Rune);
int isupperrune(Rune);
size_t runelen(wint_t);
size_t runenlen(const Rune *, size_t)
    __attribute__((__nonnull__(1)));
Rune *runestrcat(Rune *, const Rune *)
    __attribute__((__nonnull__(1, 2)));
Rune *runestrchr(Rune *, Rune)
    __attribute__((__nonnull__(1)));
int runestrcmp(const Rune *, const Rune *)
    __attribute__((__nonnull__(1, 2)));
Rune *runestrcpy(Rune *, const Rune *)
    __attribute__((__nonnull__(1, 2)));
Rune *runestrdup(const Rune *)
    __attribute__((__nonnull__(1)));
Rune *runestrecpy(Rune *, Rune *, const Rune *)
    __attribute__((__nonnull__(1, 2, 3)));
size_t runestrlen(const Rune *)
    __attribute__((__nonnull__(1)));
Rune *runestrncat(Rune *, const Rune *, size_t)
    __attribute__((__nonnull__(1, 2)));
int runestrncmp(const Rune *, const Rune *, size_t)
    __attribute__((__nonnull__(1, 2)));
Rune *runestrncpy(Rune *, const Rune *, size_t)
    __attribute__((__nonnull__(1, 2)));
Rune *runestrrchr(Rune *, Rune)
    __attribute__((__nonnull__(1)));
Rune *runestrstr(Rune *, const Rune *)
    __attribute__((__nonnull__(1, 2)));
size_t runetochar(char *, const Rune *)
    __attribute__((__nonnull__(1, 2)))
    __attribute__((__bounded__(__minbytes__, 1, 3)));
Rune tolowerrune(Rune);
Rune totitlerune(Rune);
Rune toupperrune(Rune);
char *utfecpy(char *, char *, const char *)
    __attribute__((__nonnull__(1, 2, 3)));
size_t utflen(const char *)
    __attribute__((__nonnull__(1)));
size_t utfnlen(const char *, size_t);
    __attribute__((__nonnull__(1)))
    __attribute__((__bounded__(__string__, 1, 2)));
char *utfrrune(char *, wint_t)
    __attribute__((__nonnull__(1)));
char *utfrune(char *, wint_t)
    __attribute__((__nonnull__(1)));
char *utfutf(char *, const char *)
    __attribute__((__nonnull__(1)));
__END_DECLS

#endif
