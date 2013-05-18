/**	$XFree86$ */
/**	$MirOS: src/usr.bin/compress/zopen.c,v 1.10 2011/10/11 19:25:29 tg Exp $ */
/**	_MirOS: src/usr.bin/compress/zopen.c,v 1.10 2011/10/11 19:25:29 tg Exp $ */
/*	$OpenBSD: zopen.c,v 1.17 2005/08/25 17:07:56 millert Exp $	*/
/*	$NetBSD: zopen.c,v 1.5 1995/03/26 09:44:53 glass Exp $	*/

/*-
 * Copyright (c) 2005, 2006, 2011
 *	Thorsten Glaser <tg@mirbsd.de>
 * Copyright (c) 1985, 1986, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Diomidis Spinellis and James A. Woods, derived from original
 * work by Spencer Thomas and Joseph Orost.
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
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 *
 *	From: @(#)zopen.c	8.1 (Berkeley) 6/27/93
 */

/*-
 * fcompress.c - File compression ala IEEE Computer, June 1984.
 *
 * Compress authors:
 *		Spencer W. Thomas	(decvax!utah-cs!thomas)
 *		Jim McKie		(decvax!mcvax!jim)
 *		Steve Davies		(decvax!vax135!petsd!peora!srd)
 *		Ken Turkowski		(decvax!decwrl!turtlevax!ken)
 *		James A. Woods		(decvax!ihnp4!ames!jaw)
 *		Joe Orost		(decvax!vax135!petsd!joe)
 *
 * Cleaned up and converted to library returning I/O streams by
 * Diomidis Spinellis <dds@doc.ic.ac.uk>.
 * Converted to the libXfont interface by Thorsten Glaser, with
 * the X Consortium's implementation only used as interface spec.
 *
 * zopen(filename, bits)
 *	Returns a FILE * that can be used for read. On
 *	reading the file is decompressed.
 *	Any file produced by compress(1) can be read.
 */

#include "fontmisc.h"
#include <bufio.h>

#ifndef MIN
#define	MIN(a, b)	(((a) < (b)) ? (a) : (b))
#endif

#ifndef __RCSID
#define __RCSID(x)	static const char __rcsid[] = x
#endif

__RCSID("$MirOS: src/usr.bin/compress/zopen.c,v 1.10 2011/10/11 19:25:29 tg Exp $");

#define	BITS		16		/* Default bits. */
#define	HSIZE		69001		/* 95% occupancy */
#define	ZBUFSIZ		8192		/* I/O buffer size */

/* A code_int must be able to hold 2**BITS values of type int, and also -1. */
typedef long code_int;
typedef long count_int;

static const u_char z_magic[] =
	{'\037', '\235'};		/* 1F 9D */

#define	BIT_MASK	0x1f		/* Defines for third byte of header. */
#define	BLOCK_MASK	0x80

/*
 * Masks 0x40 and 0x20 are free.  I think 0x20 should mean that there is
 * a fourth header byte (for expansion).
 */
#define	INIT_BITS 9			/* Initial number of bits/code. */

#define	MAXCODE(n_bits)	((1 << (n_bits)) - 1)

struct s_zstate {
	BufFilePtr zs_file;		/* File stream for I/O */
	enum {
		S_START, S_MIDDLE, S_EOF
	} zs_state;			/* State of computation */
	int zs_n_bits;			/* Number of bits/code. */
	int zs_maxbits;			/* User settable max # bits/code. */
	code_int zs_maxcode;		/* Maximum code, given n_bits. */
	code_int zs_maxmaxcode;		/* Should NEVER generate this code. */
	count_int zs_htab[HSIZE];
	u_short zs_codetab[HSIZE];
	code_int zs_hsize;		/* For dynamic table sizing. */
	code_int zs_free_ent;		/* First unused entry. */
	/*
	 * Block compression parameters -- after all codes are used up,
	 * and compression rate changes, start over.
	 */
	int zs_block_compress;
	int zs_clear_flg;
	long zs_ratio;
	count_int zs_checkpoint;
	long zs_in_count;		/* Length of input. */
	long zs_bytes_out;		/* Length of output. */
	long zs_out_count;		/* # of codes output (for debugging).*/
	u_char zs_buf[ZBUFSIZ];		/* I/O buffer */
	u_char *zs_bp;			/* Current I/O window in the zs_buf */
	int zs_offset;			/* Number of bits in the zs_buf */
	union {
		struct {
			long zs_fcode;
			code_int zs_ent;
			code_int zs_hsize_reg;
			int zs_hshift;
		} w;			/* Write parameters */
		struct {
			u_char *zs_stackp, *zs_ebp;
			int zs_finchar;
			code_int zs_code, zs_oldcode, zs_incode;
			int zs_size;
		} r;			/* Read parameters */
	} u;
};

/* Definitions to retain old variable names */
#define zs_fcode	u.w.zs_fcode
#define zs_ent		u.w.zs_ent
#define zs_hsize_reg	u.w.zs_hsize_reg
#define zs_hshift	u.w.zs_hshift
#define zs_stackp	u.r.zs_stackp
#define zs_finchar	u.r.zs_finchar
#define zs_code		u.r.zs_code
#define zs_oldcode	u.r.zs_oldcode
#define zs_incode	u.r.zs_incode
#define zs_size		u.r.zs_size
#define zs_ebp		u.r.zs_ebp

/*
 * To save much memory, we overlay the table used by compress() with those
 * used by decompress().  The tab_prefix table is the same size and type as
 * the codetab.  The tab_suffix table needs 2**BITS characters.  We get this
 * from the beginning of htab.  The output stack uses the rest of htab, and
 * contains characters.  There is plenty of room for any possible stack
 * (stack used to be 8000 characters).
 */

#define	htabof(i)	zs->zs_htab[i]
#define	codetabof(i)	zs->zs_codetab[i]

#define	tab_prefixof(i)	codetabof(i)
#define	tab_suffixof(i)	((u_char *)(zs->zs_htab))[i]
#define	de_stack	((u_char *)&tab_suffixof(1 << BITS))

#define	CHECK_GAP 10000		/* Ratio check interval. */

/*
 * the next two codes should not be changed lightly, as they must not
 * lie within the contiguous general code space.
 */
#define	FIRST	257		/* First free entry. */
#define	CLEAR	256		/* Table clear output code. */

static int zclose(BufFilePtr, int);
static int zskip(BufFilePtr, int);
static int zread(BufFilePtr);
static code_int	getcode(struct s_zstate *);

/*-
 * Algorithm from "A Technique for High Performance Data Compression",
 * Terry A. Welch, IEEE Computer Vol 17, No 6 (June 1984), pp 8-19.
 *
 * Algorithm:
 *	Modified Lempel-Ziv method (LZW).  Basically finds common
 * substrings and replaces them with a variable size code.  This is
 * deterministic, and can be done on the fly.  Thus, the decompression
 * procedure needs no input table, but tracks the way the table was built.
 */

static int
zclose(BufFilePtr zsf, int doClose)
{
	struct s_zstate *zs;
	BufFilePtr f;

	if (zsf == NULL)
		return (0);

	zs = (struct s_zstate *)zsf->private;

	if (zs == NULL)
		return (0);

	f = zs->zs_file;
	xfree(zs);

	BufFileClose(f, doClose);
	return (1);
}

static int
zskip(BufFilePtr zsf, int len)
{
	code_int gcode;

	while (len--)
		if ((gcode = BufFileGet(zsf)) == BUFFILEEOF)
			return (BUFFILEEOF);
	return (0);
}

static const u_char rmask[9] =
	{0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};

/*
 * Decompress read.  This routine adapts to the codes in the file building
 * the "string" table on-the-fly; requiring no table to be stored in the
 * compressed file.  See the definitions above.
 */
static int
zread(BufFilePtr zsf)
{
	u_int count = BUFFILESIZE;
	struct s_zstate *zs;
	u_char *bp;

	if (zsf == NULL)
		return (BUFFILEEOF);
	bp = zsf->buffer;
	zs = (struct s_zstate *)zsf->private;
	if ((zs == NULL) || (bp == NULL))
		return (BUFFILEEOF);

	switch (zs->zs_state) {
	case S_START:
		zs->zs_state = S_MIDDLE;
		break;
	case S_MIDDLE:
		goto middle;
	case S_EOF:
		goto eof;
	}

	/* As above, initialize the first 256 entries in the table. */
	zs->zs_maxcode = MAXCODE(zs->zs_n_bits = INIT_BITS);
	for (zs->zs_code = 255; zs->zs_code >= 0; zs->zs_code--) {
		tab_prefixof(zs->zs_code) = 0;
		tab_suffixof(zs->zs_code) = (u_char) zs->zs_code;
	}
	zs->zs_free_ent = zs->zs_block_compress ? FIRST : 256;

	zs->zs_finchar = zs->zs_oldcode = getcode(zs);
	if (zs->zs_oldcode == -1)	/* EOF already? */
		return (0);	/* Get out of here */

	/* First code must be 8 bits = char. */
	*bp++ = (u_char)zs->zs_finchar;
	count--;
	zs->zs_stackp = de_stack;

	while ((zs->zs_code = getcode(zs)) > -1) {

		if ((zs->zs_code == CLEAR) && zs->zs_block_compress) {
			for (zs->zs_code = 255; zs->zs_code >= 0;
			    zs->zs_code--)
				tab_prefixof(zs->zs_code) = 0;
			zs->zs_clear_flg = 1;
			zs->zs_free_ent = FIRST - 1;
			if ((zs->zs_code = getcode(zs)) == -1)	/* O, untimely death! */
				break;
		}
		zs->zs_incode = zs->zs_code;

		/* Special case for KwKwK string. */
		if (zs->zs_code >= zs->zs_free_ent) {
			*zs->zs_stackp++ = zs->zs_finchar;
			zs->zs_code = zs->zs_oldcode;
		}

		/* Generate output characters in reverse order. */
		while (zs->zs_code >= 256) {
			/*
			 * Bad input file may cause zs_stackp to overflow
			 * zs_htab; check here and abort decompression,
			 * that's better than dumping core.
			 */
			if (zs->zs_stackp >= (u_char *)&zs->zs_htab[HSIZE]) {
				errno = EINVAL;
				return (-1);
			}
			*zs->zs_stackp++ = tab_suffixof(zs->zs_code);
			zs->zs_code = tab_prefixof(zs->zs_code);
		}
		*zs->zs_stackp++ = zs->zs_finchar = tab_suffixof(zs->zs_code);

		/* And put them out in forward order.  */
middle:		do {
			if (count-- == 0) {
				zs->zs_bytes_out += BUFFILESIZE;
				zsf->left = BUFFILESIZE - 1;
				zsf->bufp = zsf->buffer + 1;
				return (zsf->buffer[0]);
			}
			*bp++ = *--zs->zs_stackp;
		} while (zs->zs_stackp > de_stack);

		/* Generate the new entry. */
		if ((zs->zs_code = zs->zs_free_ent) < zs->zs_maxmaxcode) {
			tab_prefixof(zs->zs_code) = (u_short) zs->zs_oldcode;
			tab_suffixof(zs->zs_code) = zs->zs_finchar;
			zs->zs_free_ent = zs->zs_code + 1;
		}

		/* Remember previous code. */
		zs->zs_oldcode = zs->zs_incode;
	}
	zs->zs_state = S_EOF;
	zs->zs_bytes_out += BUFFILESIZE - count;
eof:
	if (BUFFILESIZE - count) {
		zsf->left = (BUFFILESIZE - count) - 1;
		zsf->bufp = zsf->buffer + 1;
		return (zsf->buffer[0]);
	}
	zsf->left = 0;
	return (BUFFILEEOF);
}

/*-
 * Read one code from the standard input.  If BUFFILEEOF, return -1.
 * Inputs:
 *	stdin
 * Outputs:
 *	code or -1 is returned.
 */
static code_int
getcode(struct s_zstate *zs)
{
	code_int gcode;
	int r_off, bits;
	u_char *bp;

	if (zs->zs_clear_flg > 0 || zs->zs_offset >= zs->zs_size ||
	    zs->zs_free_ent > zs->zs_maxcode) {

		zs->zs_bp += zs->zs_n_bits;
		/*
		 * If the next entry will be too big for the current gcode
		 * size, then we must increase the size.  This implies reading
		 * a new buffer full, too.
		 */
		if (zs->zs_free_ent > zs->zs_maxcode) {
			zs->zs_n_bits++;
			if (zs->zs_n_bits == zs->zs_maxbits) {
				/* Won't get any bigger now. */
				zs->zs_maxcode = zs->zs_maxmaxcode;
			} else
				zs->zs_maxcode = MAXCODE(zs->zs_n_bits);
		}
		if (zs->zs_clear_flg > 0) {
			zs->zs_maxcode = MAXCODE(zs->zs_n_bits = INIT_BITS);
			zs->zs_clear_flg = 0;
		}

		/* fill the buffer up to the neck */
		if (zs->zs_bp + zs->zs_n_bits > zs->zs_ebp) {
			for (bp = zs->zs_buf; zs->zs_bp < zs->zs_ebp;
				*bp++ = *zs->zs_bp++);
			bits = 0;
			while ((bits < (ZBUFSIZ - (bp - zs->zs_buf)))
			    && ((gcode = BufFileGet(zs->zs_file))
			    != BUFFILEEOF)) {
				*bp++ = gcode;
				++bits;
			}
			zs->zs_in_count += bits;
			zs->zs_bp = zs->zs_buf;
			zs->zs_ebp = bp;
		}
		zs->zs_offset = 0;
		zs->zs_size = MIN(zs->zs_n_bits, zs->zs_ebp - zs->zs_bp);
		if (zs->zs_size == 0)
			return (-1);
		/* Round size down to integral number of codes. */
		zs->zs_size = (zs->zs_size << 3) - (zs->zs_n_bits - 1);
	}

	bp = zs->zs_bp;
	r_off = zs->zs_offset;
	bits = zs->zs_n_bits;

	/* Get to the first byte. */
	bp += (r_off >> 3);
	r_off &= 7;

	/* Get first part (low order bits). */
	gcode = (*bp++ >> r_off);
	bits -= (8 - r_off);
	r_off = 8 - r_off;	/* Now, roffset into gcode word. */

	/* Get any 8 bit parts in the middle (<=1 for up to 16 bits). */
	if (bits >= 8) {
		gcode |= *bp++ << r_off;
		r_off += 8;
		bits -= 8;
	}

	/* High order bits. */
	gcode |= (*bp & rmask[bits]) << r_off;
	zs->zs_offset += zs->zs_n_bits;

	return (gcode);
}

BufFilePtr
BufFilePushCompressed(BufFilePtr f)
{
	struct s_zstate *zs;
	code_int gcode;

	if ((gcode = BufFileGet(f)) != z_magic[0])
		return (0);
	if ((gcode = BufFileGet(f)) != z_magic[1])
		return (0);
	if ((gcode = BufFileGet(f)) == BUFFILEEOF)
		return (0);

	if ((zs = xalloc(sizeof(struct s_zstate))) == NULL)
		return (NULL);
	memset(zs, '\0', sizeof(struct s_zstate));

	/* max # bits/code. */
	zs->zs_maxbits = gcode & BIT_MASK;
	if (zs->zs_maxbits > BITS || zs->zs_maxbits < 12)
		return (0);
	/* Should NEVER generate this code. */
	zs->zs_maxmaxcode = 1L << zs->zs_maxbits;
	zs->zs_hsize = HSIZE;		/* For dynamic table sizing. */
	zs->zs_free_ent = 0;		/* First unused entry. */
	zs->zs_block_compress = gcode & BLOCK_MASK;
	zs->zs_clear_flg = 0;
	zs->zs_ratio = 0;
	zs->zs_checkpoint = CHECK_GAP;
	zs->zs_in_count = 3;		/* Length of input. */
	zs->zs_out_count = 0;		/* # of codes output (for debugging).*/
	zs->zs_state = S_START;
	zs->zs_offset = 0;
	zs->zs_size = 0;
	zs->zs_bp = zs->zs_ebp = zs->zs_buf;
	zs->zs_file = f;

	return (BufFileCreate((char *)zs, zread, NULL, zskip, zclose));
}
