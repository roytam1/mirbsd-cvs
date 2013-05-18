/* $MirOS: src/usr.bin/oldroff/nr8post/nr8post.c,v 1.1.7.1 2005/03/06 16:56:02 tg Exp $ */

/*-
 * Copyright (c) 2004
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
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
#include <stdio.h>
#include <unistd.h>

__RCSID("$MirOS: src/usr.bin/oldroff/nr8post/nr8post.c,v 1.1.7.1 2005/03/06 16:56:02 tg Exp $");

int
main()
{
	uint8_t c = 0;
	int i = 0, m = 0, b = 0;

	setvbuf(stdin, NULL, _IOFBF, 0);
	setvbuf(stdout, NULL, _IOFBF, 0);

	while (read(0, &c, 1) == 1) {
		if (m && (c == 'b')) {
			b = 1;
			continue;
		}
		switch (c) {
		case 0241:
			m = 8;
			i = b = 0;
			break;
		case 0253:
		case 0273:
			if (!m)
				break;
			i <<= 1;
			if (c == 0273)
				++i;
			--m;
			if (!m) {
				putchar(i);
				if (b) {
					putchar('\b');
					putchar(i);
				}
			}
			break;
		default:
			putchar(c);
			break;
		}
	}

	return 0;
}
