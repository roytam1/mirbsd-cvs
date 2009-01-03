#if 0
.if 0
#endif
/*-
 * Copyright (c) 2009
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

#include <sys/types.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

uint8_t deco_table[256] = {
	0x00, 0xFF, 0x89, 0x8B, 0x04, 0x83, 0xE8, 0x75,
	0x66, 0x08, 0x05, 0x74, 0x0F, 0x01, 0x45, 0x20,
	0x10, 0x55, 0x0C, 0xC7, 0xC0, 0xEB, 0x85, 0x65,
	0xC1, 0x5D, 0x8D, 0x53, 0x68, 0xEC, 0x6A, 0x31,
	0xC3, 0x02, 0xF0, 0xD8, 0xB8, 0x56, 0x73, 0x03,
	0x4D, 0x7D, 0x64, 0x72, 0xC4, 0x50, 0x14, 0xE5,
	0x80, 0xAB, 0x18, 0x57, 0x6F, 0xF8, 0x0A, 0x61,
	0x5E, 0x43, 0x39, 0xD2, 0xE9, 0xB0, 0x58, 0xE0,
	0x40, 0x5F, 0x70, 0x6E, 0x09, 0x25, 0x5B, 0xE4,
	0x15, 0x84, 0x06, 0x6C, 0x69, 0xAA, 0xC8, 0xB6,
	0xD0, 0xFE, 0x16, 0x1C, 0x07, 0x63, 0xC6, 0x90,
	0x24, 0x81, 0x3D, 0x30, 0x42, 0xD3, 0x5A, 0x77,
	0x46, 0x76, 0xBB, 0xDC, 0xC9, 0x51, 0xF7, 0xFA,
	0x52, 0x78, 0x29, 0xF4, 0x11, 0x59, 0x7F, 0xF6,
	0x0D, 0x44, 0x8A, 0xB7, 0x47, 0x3B, 0x3C, 0xDB,
	0x3A, 0x7E, 0x6D, 0x41, 0x88, 0x35, 0xCA, 0xC2,
	0x19, 0xD4, 0xBE, 0x0B, 0x4B, 0x79, 0x8F, 0x38,
	0x1E, 0x21, 0xBA, 0xF9, 0x7C, 0x28, 0x48, 0x62,
	0x2C, 0x1F, 0xA8, 0x12, 0x0E, 0xE2, 0xFC, 0xEA,
	0x8E, 0xD1, 0x60, 0x17, 0xFB, 0xBC, 0x6B, 0x7B,
	0x2B, 0x13, 0x1D, 0xEE, 0xA1, 0x4E, 0xCC, 0x34,
	0x4F, 0xAE, 0xA0, 0x2E, 0x67, 0xAF, 0xE3, 0xA3,
	0x22, 0xD9, 0xE1, 0x4A, 0x54, 0xF3, 0x23, 0x33,
	0xF2, 0xDA, 0xAC, 0xCD, 0xCF, 0xD6, 0x2F, 0x99,
	0x4C, 0xB4, 0x1A, 0x8C, 0xF1, 0xD7, 0x1B, 0x3E,
	0xCB, 0xBF, 0xB3, 0x95, 0xFD, 0xB9, 0xE6, 0x2D,
	0xA4, 0xDE, 0xCE, 0x82, 0xE7, 0x86, 0x5C, 0x49,
	0x37, 0xB5, 0x3F, 0x92, 0x26, 0x71, 0x9D, 0x27,
	0x32, 0x36, 0xEF, 0xDF, 0xA9, 0x94, 0xD5, 0xB1,
	0xED, 0x87, 0x98, 0x2A, 0x91, 0xDD, 0xBD, 0x9C,
	0x9E, 0x7A, 0x9A, 0xF5, 0x93, 0x9F, 0xB2, 0xA5,
	0x96, 0xAD, 0x97, 0xA7, 0xA2, 0xC5, 0x9B, 0xA6
};

uint8_t enco_table[256];

uint8_t enco_size[256] = {
	1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
	8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
};

extern const char *__progname;

void doit(const char *, const char *);
extern unsigned int gent_sz;
extern void gent_proc(void *);

static void
asm_gentable(void)
{
	gent_proc(deco_table);
}

int
main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("syntax: %s infile\n", __progname);
		return (1);
	}

	doit(argv[1], "opt");
	asm_gentable();
	doit(argv[1], "mir");
	printf("asm size: %u\n", gent_sz);
	return (0);
}

uint8_t buf[65536];

void
doit(const char *ifile, const char *ext)
{
	int ifd, ofd;
	size_t n, i;
	char *ofile;
	uint8_t ch, k, bits = 0;
	uint32_t wch = 0;

	asprintf(&ofile, "%s.%s", ifile, ext);
	if ((ifd = open(ifile, O_RDONLY)) < 0)
		err(1, "open infile %s", ifile);
	if ((ofd = open(ofile, O_WRONLY | O_CREAT, 0666)) < 0)
		err(1, "open outfile %s", ofile);

	if ((n = read(ifd, buf, 65536)) == (size_t)-1)
		err(1, "read");
	close(ifd);

	ch = n & 0xFF;
	write(ofd, &ch, 1);
	ch = n >> 8;
	write(ofd, &ch, 1);
	ch = 0;
	write(ofd, &ch, 1);
	write(ofd, &ch, 1);

	/* generate enco_table */
	for (i = 0; i < 256; ++i)
		enco_table[deco_table[i]] = i;

	/* compress */
	for (i = 0; i < n; ++i) {
		ch = enco_table[buf[i]];
		k = enco_size[ch];
		wch = wch << 3 | (k - 1);
		wch = wch << k | ch;
		bits += 3 + k;

		/*-
			 0: .... .... .... .... .... .... .... ....
			 1: .... .... .... .... .... .... .... ...x
			 2: .... .... .... .... .... .... .... ..xx
			 3: .... .... .... .... .... .... .... .xxx
			 4: .... .... .... .... .... .... .... xxxx
			 5: .... .... .... .... .... .... ...x xxxx
			 6: .... .... .... .... .... .... ..xx xxxx
			 7: .... .... .... .... .... .... .xxx xxxx
			 8: .... .... .... .... .... .... #### ####
			 9: .... .... .... .... .... ...# #### ###x
			10: .... .... .... .... .... ..## #### ##xx
			11: .... .... .... .... .... .### #### #xxx
			12: .... .... .... .... .... #### #### xxxx
			13: .... .... .... .... ...# #### ###x xxxx
			14: .... .... .... .... ..## #### ##xx xxxx
			15: .... .... .... .... .### #### #xxx xxxx
			16: .... .... .... .... #### #### ==== ====
			17: .... .... .... ...# #### ###= ==== ===x
			18: .... .... .... ..## #### ##== ==== ==xx
		*/

		while (bits > 7) {
			ch = wch >> (bits - 8);
			write(ofd, &ch, 1);
			bits -= 8;
		}
	}
	if (bits) {
		ch = wch << (8 - bits);
		write(ofd, &ch, 1);
	}
	close(ofd);
}

#if 0
.endif

PROG=		hscompr
SRCS=		hscompr.c hscmpmir.S
NOMAN=		Yes

.include <bsd.prog.mk>
#endif
