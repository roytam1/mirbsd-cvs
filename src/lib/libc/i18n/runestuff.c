/*-
 * Copyright (c) 2008
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

#define _ALL_SOURCE
#include <utf.h>
#include <wchar.h>

__RCSID("$MirOS: src/lib/libc/i18n/runestuff.c,v 1.1 2008/11/22 12:56:21 tg Exp $");

#define DECL_PS		mbstate_t ps = { 0, 0 }

#ifdef L_chartorune
size_t
chartorune(Rune *rp, const char *s)
{
	DECL_PS;
	size_t n;

	n = optu8to16(rp, s, UTFmax, &ps);
	return (iswoctet(*rp) ? 1 : n);
}
#endif

#ifdef L_fullrune
int
fullrune(const char *s, size_t n)
{
	DECL_PS;
	Rune r;

	return (optu8to16(&r, s, n, &ps) == (size_t)-2 ? 0 : 1);
}
#endif

#ifdef L_isalpharune
#include <wctype.h>
int
isalpharune(Rune r)
{
	return (iswalpha(r));
}
#endif

#ifdef L_islowerrune
#include <wctype.h>
int
islowerrune(Rune r)
{
	return (iswlower(r));
}
#endif

#ifdef L_isspacerune
#include <wctype.h>
int
isspacerune(Rune r)
{
	return (iswspace(r));
}
#endif

#ifdef L_istitlerune
#include <err.h>
#include <errno.h>
int
istitlerune(Rune r)
{
	errno = ENOCOFFEE;
	warn("istitlerune(%04X)", r);
	return (-1);
}
#endif

#ifdef L_isupperrune
#include <wctype.h>
int
isupperrune(Rune r)
{
	return (iswupper(r));
}
#endif

#ifdef L_runelen
size_t
runelen(wint_t wc)
{
	return ((wc < 0x80 || wc == WEOF) ? 1 :
	    wc < 0x0800 ? 2 : iswoctet(wc) ? 1 : 3);
}
#endif

#ifdef L_runenlen
size_t
runenlen(const Rune *ws, size_t len)
{
	size_t n = 0;
	Rune wc;

	while (len--)
		n += (wc = *ws++) < 0x80 ? 1 :
		    wc < 0x0800 ? 2 : iswoctet(wc) ? 1 : 3;
	return (n);
}
#endif

#ifdef L_runestrcat
__warn_references(runestrcat,
    "runestrcat() is almost always misused, please use wcslcat()");
Rune *
runestrcat(Rune *s1, const Rune *s2)
{
	return (wcscat(s1, s2));
}
#endif

#ifdef L_runestrchr
Rune *
runestrchr(Rune *s, Rune wc)
{
	return (wcschr(s, wc));
}
#endif

#ifdef L_runestrcmp
int
runestrcmp(const Rune *s1, const Rune *s2)
{
	return (wcscmp(s1, s2));
}
#endif

#ifdef L_runestrcpy
__warn_references(runestrcpy,
    "runestrcpy() is almost always misused, please use wcslcpy()");
Rune *
runestrcpy(Rune *s1, const Rune *s2)
{
	return (wcscpy(s1, s2));
}
#endif

#ifdef L_runestrdup
Rune *
runestrdup(const Rune *s)
{
	return (wcsdup(s));
}
#endif

#ifdef L_runestrecpy
Rune *
runestrecpy(Rune *s1, Rune *es1, const Rune *s2)
{
	if (s1 < es1)
		while ((*s1++ = *s2++))
			if (s1 == es1) {
				*--s1 = L'\0';
				break;
			}
	return (s1);
}
#endif

#ifdef L_runestrlen
size_t
runestrlen(const Rune *s)
{
	return (wcslen(s));
}
#endif

#ifdef L_runestrncat
Rune *
runestrncat(Rune *s1, const Rune *s2, size_t n)
{
	return (wcsncat(s1, s2, n));
}
#endif

#ifdef L_runestrncmp
int
runestrncmp(const Rune *s1, const Rune *s2, size_t n)
{
	return (wcsncmp(s1, s2, n));
}
#endif

#ifdef L_runestrncpy
Rune *
runestrncpy(Rune *s1, const Rune *s2, size_t n)
{
	return (wcsncpy(s1, s2, n));
}
#endif

#ifdef L_runestrrchr
Rune *
runestrrchr(Rune *s, Rune wc)
{
	return (wcsrchr(s, wc));
}
#endif

#ifdef L_runestrstr
Rune *
runestrstr(Rune *haystack, const Rune *needle)
{
	return (wcsstr(haystack, needle));
}
#endif

#ifdef L_runetochar
size_t
runetochar(char *s, const Rune *rp)
{
	DECL_PS;

	return (optu16to8(s, *rp, &ps));
}
#endif

#ifdef L_tolowerrune
#include <wctype.h>
Rune
tolowerrune(Rune r)
{
	return (towlower(r));
}
#endif

#ifdef L_totitlerune
#include <err.h>
#include <errno.h>
Rune
totitlerune(Rune r)
{
	errno = ENOCOFFEE;
	warn("totitlerune(%04X)", r);
	return (-1);
}
#endif

#ifdef L_toupperrune
#include <wctype.h>
Rune
toupperrune(Rune r)
{
	return (towupper(r));
}
#endif

#ifdef L_utfecpy
char *
utfecpy(char *dst, char *end, const char *src)
{
	size_t slen, dlen;
	wchar_t *buf, *bufp;
	DECL_PS;

	if (end <= dst)
		return (dst);

	slen = strlen(src);
	dlen = end - dst;	/* > 0 */
	if (slen < dlen) {
		memcpy(dst, src, slen + 1);
		return (dst + slen);
	}

	bufp = buf = ambstowcs(src);
	end = dst + wcsrtombs(dst, (const wchar_t **)&bufp, dlen - 1, &ps);
	free(buf);
	*end = '\0';
	if (mbsinit(&ps))
		/* no need to truncate last mbchar (valid OPTU-8) */
		return (end);
	/* truncate last mbchar (valid CESU-8) */
	--end;
	while ((*(unsigned char *)end & 0xC0) == 0x80)
		if (end > dst)
			--end;
		else
			break;
	*end = '\0';
	return (end);
}
#endif

#ifdef L_utflen
size_t
utflen(const char *s)
{
	DECL_PS;

	return (mbsrtowcs(NULL, &s, 0, &ps));
}
#endif

#ifdef L_utfnlen
size_t
utfnlen(const char *s, size_t n)
{
	DECL_PS;

	return (mbsnrtowcs(NULL, &s, n, 0, &ps));
}
#endif

#ifdef L_utfrrune
char *
utfrrune(char *s, wint_t wc)
{
	DECL_PS;

	if (wc < 0x80)
		return (strrchr(s, wc));
	else if (!iswoctet(wc)) {
		char buf[5];
		char *match = NULL, *cp;

		bzero(buf, sizeof (buf));
		optu16to8(buf, wc, &ps);
		while ((cp = strchr(s, buf[0])) != NULL) {
			if ((cp[1] == buf[1]) && (!buf[2] ||
			    (cp[2] == buf[2])))
				match = cp;
			s = cp + 1;
		}
		return (match);
	} else {
		wchar_t *buf, *match, *cp;

		buf = ambstowcs(s);
		if ((match = wcsrchr(buf, wc)) != NULL) {
			cp = buf;
			while (cp < match)
				s += runelen(*cp++);
		} else
			s = NULL;
		free(buf);
		return (s);
	}
}
#endif

#ifdef L_utfrune
char *
utfrune(char *s, wint_t wc)
{
	DECL_PS;

	if (wc < 0x80)
		return (strchr(s, wc));
	else if (!iswoctet(wc)) {
		char buf[5];

		bzero(buf, sizeof (buf));
		optu16to8(buf, wc, &ps);
		return (strstr(s, buf));
	} else {
		wchar_t *buf, *match, *cp;

		buf = ambstowcs(s);
		if ((match = wcschr(buf, wc)) != NULL) {
			cp = buf;
			while (cp < match)
				s += runelen(*cp++);
		} else
			s = NULL;
		free(buf);
		return (s);
	}
}
#endif

#ifdef L_utfutf
char *
utfutf(char *s1, const char *s2)
{
	if (s2 != NULL && *s2) {
		wchar_t *buf1, *buf2, *match, *cp;

		buf1 = ambstowcs(s1);
		buf2 = ambstowcs(s2);
		if ((match = wcsstr(buf1, buf2)) != NULL) {
			cp = buf1;
			while (cp < match)
				s1 += runelen(*cp++);
		} else
			s1 = NULL;
		free(buf1);
		free(buf2);
	}
	return (s1);
}
#endif
