/* $MirOS: src/share/misc/licence.template,v 1.14 2006/08/09 19:35:23 tg Rel $ */

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
#ifdef DEBUG
#include <zlib.h>
#endif

#include "defs.h"
#include "fts_subs.h"
#include "pack.h"

__RCSID("$MirOS: contrib/hosted/fwcf/ft_pack.c,v 1.5 2006/09/16 03:51:06 tg Exp $");

char *
mkheader(char *f_header, size_t hdrsize, uint32_t outer_len,
    uint32_t inner_len, uint8_t algo)
{
	char *hdrptr = f_header;
	size_t hdrleft = hdrsize;

	STOREB('F');
	STOREB('W');
	STOREB('C');
	STOREB('F');

	outer_len = (outer_len & 0xFFFFFF) | (FWCF_VER << 24);
	STORED(outer_len);

	inner_len = (inner_len & 0xFFFFFF) | (algo << 24);
	STORED(inner_len);
	return (hdrptr);
}

char *
mktrailer(char *data, size_t len)
{
	char *hdrptr = data + len;
	uint8_t *buf = (uint8_t *)data;
	size_t hdrleft = 4;
	unsigned s1 = 1, s2 = 0, n;
#ifdef DEBUG
	uint32_t adler = adler32(1, buf, len);
#endif

#define BASE	65521	/* largest prime smaller than 65536 */
#define NMAX	5552	/* largest n: 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */
	while (len) {
		len -= (n = MIN(len, NMAX));
		while (n--) {
			s1 += *buf++;
			s2 += s1;
		}
		s1 %= BASE;
		s2 %= BASE;
	}

#ifdef DEBUG
	if ((s1 != (adler & 0xFFFF)) || (s2 != (adler >> 16)))
		errx(255, "adler32 implementation error: %04X%04X vs %08X",
		    s2, s1, adler);
#endif
	STOREW(s1);
	STOREW(s2);
	return (data);
#undef BASE
#undef NMAX
}
