/**	$MirOS$ */
/*	$OpenBSD: extern.h,v 1.6 2003/06/03 02:56:20 millert Exp $	*/
/*	$NetBSD: extern.h,v 1.4 1995/11/01 00:45:22 pk Exp $	*/

/*-
 * Copyright (c) 2007
 *	Thorsten Glaser <tg@mirbsd.de>
 * Copyright (c) 1991, 1993
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
 *
 *	@(#)extern.h	8.1 (Berkeley) 6/6/93
 */

typedef struct {
	enum { STRING1, STRING2 } which;
	enum { EOS, INFINITE, NORMAL, RANGE, SEQUENCE, SET, WCLASS, WTRANS } state;
	int cnt;			/* character count */
	union {
		wchar_t *set_;		/* set of characters */
		wctype_t class_;	/* character class */
	} setext;
#define set	setext.set_
#define wclass	setext.class_
	wchar_t *str;			/* user's string */
	wchar_t equiv[2];		/* equivalence set */
#define cnext equiv[0]			/* next char to try with class */
	wctrans_t wtrans;		/* character conversion class */
	wchar_t lastch;			/* last character */
	bool use_wctrans;
} STR;

#if WCHAR_MAX != 0xFFFD
#warning results untested, WCHAR_MAX ≠ 0xFFFD
#endif

#define	NCHARS	(WCHAR_MAX + 1)		/* Number of possible characters. */
#define	OOBCH	(WCHAR_MAX + 1)		/* Out of band character value. */

bool next(STR *);
