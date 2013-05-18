/* $MirOS$ */
/* $OpenBSD: fgetwc.c,v 1.1 2005/06/17 20:40:32 espie Exp $	*/
/* $NetBSD: fgetwc.c,v 1.3 2003/03/07 07:11:36 tshiozak Exp $ */

/*-
 * Copyright (c) 2007 Thorsten Glaser
 * Copyright (c)2001 Citrus Project,
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
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Citrus$
 */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <wchar.h>
#include "local.h"

__RCSID("$MirOS: src/lib/libc/stdio/fgetwc.c,v 1.4 2007/02/01 23:43:29 tg Exp $");

wint_t __fgetwc_unlock(FILE *);

wint_t
__fgetwc_unlock(FILE *fp)
{
	struct wchar_io_data *wcio;
	mbstate_t *st;
	wchar_t wc;
	size_t size;
	bool firstc = true;

	_SET_ORIENTATION(fp, 1);
	wcio = WCIO_GET(fp);
	if (wcio == 0) {
		errno = ENOMEM;
		return WEOF;
	}

	/* if there're ungetwc'ed wchars, use them */
	if (wcio->wcio_ungetwc_inbuf) {
		wc = wcio->wcio_ungetwc_buf[--wcio->wcio_ungetwc_inbuf];

		return wc;
	}

	st = &wcio->wcio_mbstate_in;

	do {
		char c;
		int ch = __sgetc(fp);

		if (ch == EOF) {
			return WEOF;
		}

		c = ch;
		size = mbrtowc(&wc, &c, 1, st);
		if (size == (size_t)-1) {
			if (!firstc) {
				ungetc(ch, fp);
				if (st->count == 1 && st->value >= 0x20)
					ungetc(0x80 | (st->value & 0x3F), fp);
			}
			st->count = 0;	/* clear mbstate_t */
			fp->_flags |= __SERR;
			errno = EILSEQ;
			return WEOF;
		}
		firstc = false;
	} while (size == (size_t)-2);

	return wc;
}

wint_t
fgetwc(FILE *fp)
{
	wint_t r;

	flockfile(fp);
	r = __fgetwc_unlock(fp);
	funlockfile(fp);

	return (r);
}
