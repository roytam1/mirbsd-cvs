/*-
 * Copyright (c) 2007, 2013
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.de>
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratory.
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
 */

#include <sys/param.h>
#include <ctype.h>
#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

__SCCSID("@(#)sun_disklabel.h	8.1 (Berkeley) 6/11/93");
__RCSID("$MirOS: src/distrib/tools/sundsklbl.c,v 1.3 2007/09/28 22:27:27 tg Exp $");

/*
 * SunOS disk label layout (only relevant portions discovered here).
 */

#define SUN_DKMAGIC	55998
#define SL_XPMAG	(0x199d1fe2 + 8)

/* partition info */
struct sun_dkpart {
	int32_t sdkp_cyloffset;		/* starting cylinder */
	int32_t sdkp_nsectors;		/* number of sectors */
};

/* SunOS disklabel sector (512 bytes in total) */
struct sun_disklabel {
	uint8_t sl_text[128];		/* some descriptive text, or… */
	uint32_t sl_xpsum;		/* 32-bit additive [sl_xpmag,sl_xxx1) */
	uint32_t sl_xpmag;		/* "extended" magic number */
	struct sun_dkpart sl_xpart[8];	/* "extended" partitions, i through p */
	uint8_t sl_xxx1[220];		/* padding or something like that */
	uint16_t sl_rpm;		/* rotational speed */
	uint16_t sl_pcylinders;		/* number of physical cylinders */
	uint16_t sl_sparespercyl;	/* spare sectors per cylinder */
	uint8_t sl_xxx3[4];		/* padding / reserved */
	uint16_t sl_interleave;		/* interleave factor */
	uint16_t sl_ncylinders;		/* data cylinders */
	uint16_t sl_acylinders;		/* alternate cylinders */
	uint16_t sl_ntracks;		/* tracks per cylinder */
	uint16_t sl_nsectors;		/* sectors per track */
	uint8_t sl_xxx4[4];		/* padding / reserved */
	struct sun_dkpart sl_part[8];	/* partition layout */
	uint16_t sl_magic;		/* == SUN_DKMAGIC */
	uint16_t sl_cksum;		/* 16-bit XOR, [sl_text,sl_cksum) */
} __attribute__((__packed__));

struct sun_disklabel thelabel;

void dump_para(uint8_t *, size_t);

void
dump_para(uint8_t *cp, size_t cutoff)
{
	size_t i;

	for (i = 0; i < 16; ++i)
		printf("%02X%s%s", cp[i],
		    i >= cutoff ? "\b\b  " : "",
		    i == 7 ? " - " : " ");
	printf(" |");
	for (i = 0; i < cutoff; ++i)
		putchar(isprint(cp[i]) ? cp[i] : '.');
	printf("|\n");
}

int
main(void)
{
	int i;
	uint16_t s;
	uint32_t l;

	if (sizeof (thelabel) != 512)
		errx(1, "label size wrong, check your compiler types!");

	if (read(0, &thelabel, 512) != 512)
		err(1, "cannot read input");

	printf("sl_text");
	for (i = 0; i < 128; i += 16) {
		printf("\t\t");
		dump_para(&thelabel.sl_text[i], 16);
	}
	l = betoh32(thelabel.sl_xpmag);
	for (i = 0; i < 8; ++i) {
		l += betoh32(thelabel.sl_xpart[i].sdkp_cyloffset);
		l += betoh32(thelabel.sl_xpart[i].sdkp_nsectors);
	}
	printf("sl_xpsum\t%08X (calc %08X)\n",
	    betoh32(thelabel.sl_xpsum), l);
	printf("sl_xpmag\t%08X (want %08X)\n",
	    betoh32(thelabel.sl_xpmag), SL_XPMAG);
	for (i = 0; i < 8; ++i) {
		printf("sl_xpart[%d] (%c)\t%08X @%08X (%3$u)\n", i, i + 'i',
		    betoh32(thelabel.sl_xpart[i].sdkp_nsectors),
		    betoh32(thelabel.sl_xpart[i].sdkp_cyloffset));
	}
	printf("sl_xxx1");
	for (i = 0; i < 220; i += 16) {
		printf("\t\t");
		dump_para(&thelabel.sl_xxx1[i], i == 208 ? 12 : 16);
	}
	printf("sl_rpm\t\t%04X (%1$u)\n", betoh16(thelabel.sl_rpm));
	printf("sl_pcylind.\t%04X (%1$u)\n", betoh16(thelabel.sl_pcylinders));
	printf("sl_sp_p_cyl\t%04X (%1$u)\n", betoh16(thelabel.sl_sparespercyl));
	printf("sl_xxx3\t\t%02X %02X %02X %02X |%c%c%c%c|\n",
	    thelabel.sl_xxx3[0], thelabel.sl_xxx3[1],
	    thelabel.sl_xxx3[2], thelabel.sl_xxx3[3],
	    isprint(thelabel.sl_xxx3[0]) ? thelabel.sl_xxx3[0] : '.',
	    isprint(thelabel.sl_xxx3[1]) ? thelabel.sl_xxx3[1] : '.',
	    isprint(thelabel.sl_xxx3[2]) ? thelabel.sl_xxx3[2] : '.',
	    isprint(thelabel.sl_xxx3[3]) ? thelabel.sl_xxx3[3] : '.');
	printf("sl_interleave\t%04X (%1$u)\n", betoh16(thelabel.sl_interleave));
	printf("sl_ncylinders\t%04X (%1$u)\n", betoh16(thelabel.sl_ncylinders));
	printf("sl_acylinders\t%04X (%1$u)\n", betoh16(thelabel.sl_acylinders));
	printf("sl_ntracks\t%04X (%1$u)\n", betoh16(thelabel.sl_ntracks));
	printf("sl_nsectors\t%04X (%1$u)\n", betoh16(thelabel.sl_nsectors));
	printf("sl_xxx4\t\t%02X %02X %02X %02X |%c%c%c%c|\n",
	    thelabel.sl_xxx4[0], thelabel.sl_xxx4[1],
	    thelabel.sl_xxx4[2], thelabel.sl_xxx4[3],
	    isprint(thelabel.sl_xxx4[0]) ? thelabel.sl_xxx4[0] : '.',
	    isprint(thelabel.sl_xxx4[1]) ? thelabel.sl_xxx4[1] : '.',
	    isprint(thelabel.sl_xxx4[2]) ? thelabel.sl_xxx4[2] : '.',
	    isprint(thelabel.sl_xxx4[3]) ? thelabel.sl_xxx4[3] : '.');
	for (i = 0; i < 8; ++i) {
		printf("sl_part[%d] (%c)\t%08X @%08X (%3$u)\n", i, i + 'a',
		    betoh32(thelabel.sl_part[i].sdkp_nsectors),
		    betoh32(thelabel.sl_part[i].sdkp_cyloffset));
	}
	printf("sl_magic\t%04X (want %04X)\n",
	    betoh16(thelabel.sl_magic), SUN_DKMAGIC);
	s = 0; i = 0;
	while (i < 510) {
		s ^= (((uint8_t *)&thelabel)[i++] << 8);
		s ^= (((uint8_t *)&thelabel)[i++]);
	}
	printf("sl_cksum\t%04X (want %04X, total %04X, must be zero)\n",
	    betoh16(thelabel.sl_cksum), s, betoh16(thelabel.sl_cksum) ^ s);

	printf("i386_magic\t%02X%02X (dangerous 55AA)\n",
	    ((uint8_t *)&thelabel)[510], ((uint8_t *)&thelabel)[511]);
	printf("i386_part0\t%02X (dangerous 27, A5, A6, A9)\n",
	    ((uint8_t *)&thelabel)[0x1C2]);
	printf("i386_part1\t%02X (dangerous 27, A5, A6, A9)\n",
	    ((uint8_t *)&thelabel)[0x1D2]);
	printf("i386_part2\t%02X (dangerous 27, A5, A6, A9)\n",
	    ((uint8_t *)&thelabel)[0x1E2]);
	printf("i386_part3\t%02X (dangerous 27, A5, A6, A9)\n",
	    ((uint8_t *)&thelabel)[0x1F2]);

	return (0);
}
