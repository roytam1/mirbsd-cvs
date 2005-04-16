/* $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $ */

/*-
 * Copyright (c) 2004, 2005
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

__RCSID("$MirOS: src/usr.bin/oldroff/nr8pre/nr8pre.c,v 1.1.7.1 2005/03/06 16:56:02 tg Exp $");

#define	putstr(x)	fputs((x), stdout)

int
main(int argc, char *argv[])
{
	uint8_t c = 0;
	int i, v = 0, status = 0, max = 127;

	if ((argc > 1) && (argv[1][0] == '-'))
		switch(argv[1][1]) {
		case '7':
			max = 255;
			break;
		}

	setvbuf(stdin, NULL, _IOFBF, 0);
	setvbuf(stdout, NULL, _IOFBF, 0);

	while (read(0, &c, 1) == 1)
		switch (status) {
		case 4:
		case 3:
			if (c == '\'') {
				status = 0;
				c = v;
				goto special;
			}
			if (status == 4)
				break;
			if ((c < '0') || (c > '9')) {
				status = 4;
				break;
			}
			v = (v * 10) + (c - '0');
			break;
		case 2:
			if (c == '\'') {
				status = 3;
				v = 0;
				break;
			}
			status = 0;
			putchar('\\');
			putchar('N');
			goto regular;
			break;
		case 1:
			if (c == 'N') {
				status = 2;
				break;
			}
			status = 0;
			putchar('\\');
			goto regular;
			break;
		case 0:
			if (c == '\\') {
				status = 1;
				break;
			}
		regular:
			if (c < max)
				putchar(c);
			else {
			special:
				putstr("\\(88");
				for (i = 128 | 32768; i > 128; i >>= 1)
					if (c & (i & 255))
						putstr("\\(81");
					else
						putstr("\\(80");
			}
			break;
		}

	return 0;
}
