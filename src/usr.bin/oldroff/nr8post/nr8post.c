/* $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $ */

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
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
 */

#include <sys/param.h>
#include <stdio.h>
#include <unistd.h>

__RCSID("$MirOS$");

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
