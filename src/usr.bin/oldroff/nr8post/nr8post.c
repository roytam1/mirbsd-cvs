/* $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $ */

/*-
 * Copyright (c) 2004, 2007
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
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

#include <sys/param.h>
#include <stdio.h>
#include <unistd.h>

__RCSID("$MirOS: src/usr.bin/oldroff/nr8post/nr8post.c,v 1.2 2005/12/17 05:46:28 tg Exp $");

int
main(void)
{
	uint8_t c = 0;
	int i = 0, m = 0, b = 0;

	setvbuf(stdin, NULL, _IOFBF, 0);
	setvbuf(stdout, NULL, _IOFBF, 0);

	while (read(0, &c, 1) == 1) {
		if (m && (c == '\b')) {
			b = 1;
			if (read(0, &c, 1) != 1)
				break;
			if (c == 0241)
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

	return (0);
}
