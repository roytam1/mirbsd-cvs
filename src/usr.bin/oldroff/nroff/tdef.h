/**	$MirOS$ */

/*-
 * Copyright (c) 1979, 1980, 1981, 1986, 1988, 1990, 1991, 1992
 *     The Regents of the University of California.
 * Copyright (C) Caldera International Inc.  2001-2002.
 * Copyright (c) 2003, 2004
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms,
 * with or without modification, are permitted provided
 * that the following conditions are met:
 *
 * Redistributions of source code and documentation must retain
 * the above copyright notice, this list of conditions and the
 * following disclaimer.  Redistributions in binary form must
 * reproduce the above copyright notice, this list of conditions
 * and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 *
 * All advertising materials mentioning features or use of this
 * software must display the following acknowledgement:
 *   This product includes software developed or owned by
 *   Caldera International, Inc.
 *
 * Neither the name of Caldera International, Inc. nor the names
 * of other contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * USE OF THE SOFTWARE PROVIDED FOR UNDER THIS LICENSE BY CALDERA
 * INTERNATIONAL, INC. AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL CALDERA INTERNATIONAL, INC. BE
 * LIABLE FOR ANY DIRECT, INDIRECT INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *	@(#)tdef.h	4.9 (Berkeley) 4/18/91
 */

#ifndef	_TDEF_H
#define	_TDEF_H

#include <sys/param.h>
#include <signal.h>

#undef	CMASK			/* XXX */
#undef	BIG			/* XXX */
#define	MAXPTR (-1)		/* max value of any pointer variable */

#ifdef	NROFF			/* NROFF */
#define	EM	t.Em
#define	HOR	t.Hor
#define	VERT	t.Vert
#define	INCH	240		/* increments per inch */
#define	SPS	INCH/10		/* space size */
#define	SS	INCH/10		/* " */
#define	TRAILER	0
#define	UNPAD	0227
#define	PO	0		/* page offset */
#define	ASCII	1
#define	PTID	1
#define	LG	0
#define	DTAB	0		/* set at 8 Ems at init time */
#define	ICS	2*SPS
/*#define	TEMP	256		/* 65K */
#define	TEMP	1536		/* 384K */
#endif

#ifndef	NROFF			/* TROFF */
#define	INCH	432		/* troff resolution */
#define	SPS	20		/* space size at 10pt; 1/3 Em */
#define	SS	12		/* space size in 36ths of an em */
#define	TRAILER	6048		/* 144*14*3 = 14 inches */
#define	UNPAD	027
#define	PO	416		/* page offset 26/27ths inch */
#define	HOR	1
#define	VERT	3
#define	EM	(6*(pts&077))
#define	ASCII	0
#define	PTID	0
#define	LG	1
#define	DTAB	(INCH/2)
#define	ICS	3*SPS
/* #define	TEMP	512		/* 128K */
#define	TEMP	2048		/* 512K */
#endif

#define	NARSP	0177		/* narrow space */
#define	HNSP	0226		/* half narrow space */
#define	PS	10		/* default point size */
#define	FT	0		/* default font position */
#define	LL	65*INCH/10	/* line length; 39picas=6.5in */
#define	VS	INCH/6		/* vert space; 12points */

#ifdef	VMUNIX
#define	NN	2048		/* number registers */
#else
#define	NN	132		/* number registers */
#endif
/* #define NN 200	*/

#define	NNAMES	14		/* predefined reg names */
#define	NIF	63		/* if-else nesting */
#define	NS	256		/* name buffer */
#define	NTM	1024		/* tm buffer */
#define	NEV	4		/* environments */
#define	EVLSZ	32		/* size of ev stack */
/* #define EVS 4*256	*/

#ifdef	VMUNIX
#define	NM	3600
#define	EVS	80*256		/* environment size in words */
#else
#define	NM	300		/* requests + macros */
#define	EVS	3*256		/* environment size in words */
#endif

#define	DELTA	2048		/* delta core bytes */
#define	NHYP	12		/* max hyphens per word */
#define	NHEX	256		/* byte size of exception word list */
#define	NTAB	45		/* tab stops */
#define	NSO	12		/* "so" depth */

#ifdef	VMUNIX
#define	WDSIZE	2048		/* word buffer size */
#define	LNSIZE	5760		/* line buffer size */
#else
#define	WDSIZE	170		/* word buffer size */
#define	LNSIZE	480		/* line buffer size */
#endif
/* #define LNSIZE 680	*/

#define	NDI	5		/* number of diversions */
#define	DBL	0100000		/* double size indicator */
#define	MOT	0100000		/* motion character indicator */
#define	MOTV	0160000		/* clear for motion part */
#define	VMOT	0040000		/* vert motion bit */
#define	NMOT	0020000		/* negative motion indicator */
#define	MMASK	0100000		/* macro mask indicator */
#define	CMASK	0100377
#define	ZBIT	0400		/* zero width char */
#define	BMASK	0377
#define	BYTE	8
#define	IMP	004		/* impossible char */
#define	FILLER	037
#define	PRESC	026
#define	HX	0376		/* High-order part of xlss */
#define	LX	0375		/* low-order part of xlss */
#define	CONT	025
#define	COLON	013
#define	XPAR	030
#define	ESC	033
#define	FLSS	031
#define	RPT	014
#define	JREG	0374
#define	NTRAP	20		/* number of traps */
#define	NPN	20		/* numbers in "-o" */
#define	T_PAD	0101		/* cat padding */
#define	T_INIT	0100
#define	T_IESC	16		/* initial offset */
#define	T_STOP	0111
#define	NPP	10		/* pads per field */

#ifdef	VMUNIX
#define	FBUFSZ	2048
#else
#define	FBUFSZ	256		/* field buf size words */
#endif

#define	OBUFSZ	147456		/* bytes */
#define	IBUFSZ	16384		/* bytes */
#define	NC	256		/* cbuf size words */
#define	NOV	10		/* number of overstrike chars */
#define	TDELIM	032
#define	LEFT	035
#define	RIGHT	036
#define	LEADER	001
#define	TAB	011
#define	TMASK	037777
#define	RTAB	0100000
#define	CTAB	0040000
#define	OHC	024

#define	PAIR(A,B)	(A|(B<<BYTE))

#define	BLK	256		/* alloc block words */

#ifdef	VMUNIX
#define	BIG	4096
#endif

#ifdef	BIG
typedef long filep;
#define	NBLIST	BIG		/* allocation , BIG = 256 per 65k */
#define	BLKBITS	8		/* for BLK=256 */
#else	/* def BIG */
typedef unsigned filep;
#define	NBLIST	TEMP		/* allocation list, TEMP<=512 */
/* BLK*NBLIST<=65536 words, if filep=unsigned */
#define	BLKBITS	0
#endif

#endif	/* ndef _TDEF_H */
