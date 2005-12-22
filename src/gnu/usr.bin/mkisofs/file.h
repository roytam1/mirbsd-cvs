/* @(#)file.h	1.1 00/03/05 joerg */
/*
 * hfsutils - tools for reading and writing Macintosh HFS volumes
 * Copyright (C) 1996, 1997 Robert Leslie
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "hfs.h"
#include "internal.h"

enum {
  fkData = 0x00,
  fkRsrc = 0xff
};

void f_selectfork	__PR((hfsfile *, int));
void f_getptrs		__PR((hfsfile *, unsigned long **, unsigned long **, ExtDataRec **));

int f_doblock		__PR((hfsfile *, unsigned long, block *,
	   		   int (*)(hfsvol *, unsigned int, unsigned int, block *)));

# define f_getblock(file, num, bp)	f_doblock(file, num, bp, b_readab)
# define f_putblock(file, num, bp)	f_doblock(file, num, bp, b_writeab)

int f_alloc		__PR((hfsfile *));
int f_trunc		__PR((hfsfile *));
int f_flush		__PR((hfsfile *));
/* @(#)file.h	1.6 03/03/06 joerg */
/*
 * file.h - definitions for file(1) program
 * @(#)$Id$
 *
 * Copyright (c) Ian F. Darwin, 1987.
 * Written by Ian F. Darwin.
 *
 * This software is not subject to any license of the American Telephone
 * and Telegraph Company or of the Regents of the University of California.
 *
 * Permission is granted to anyone to use this software for any purpose on
 * any computer system, and to alter it and redistribute it freely, subject
 * to the following restrictions:
 *
 * 1. The author is not responsible for the consequences of use of this
 *    software, no matter how awful, even if they arise from flaws in it.
 *
 * 2. The origin of this software must not be misrepresented, either by
 *    explicit claim or by omission.  Since few users ever read sources,
 *    credits must appear in the documentation.
 *
 * 3. Altered versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.  Since few users
 *    ever read sources, credits must appear in the documentation.
 *
 * 4. This notice may not be removed or altered.
 */

#ifndef __file_h__
#define __file_h__

#ifndef	_MCONFIG_H
#include <mconfig.h>
#endif
#include <utypes.h>

#ifndef HOWMANY
# define HOWMANY 8192		/* how much of the file to look at */
#endif
#define MAXMAGIS 1000		/* max entries in /etc/magic */
#define MAXDESC	50		/* max leng of text description */
#define MAXstring 32		/* max leng of "string" types */

struct magic {
	short flag;		
#define INDIR	1		/* if '>(...)' appears,  */
#define	UNSIGNED 2		/* comparison is unsigned */
#define ADD	4		/* if '>&' appears,  */
	short cont_level;	/* level of ">" */
	struct {
		char type;	/* byte short long */
		Int32_t offset;	/* offset from indirection */
	} in;
	Int32_t offset;		/* offset to magic number */
	unsigned char reln;	/* relation (0=eq, '>'=gt, etc) */
	char type;		/* int, short, long or string. */
	char vallen;		/* length of string value, if any */
#define 			BYTE	1
#define				SHORT	2
#define				LONG	4
#define				STRING	5
#define				DATE	6
#define				BESHORT	7
#define				BELONG	8
#define				BEDATE	9
#define				LESHORT	10
#define				LELONG	11
#define				LEDATE	12
	union VALUETYPE {
		unsigned char b;
		unsigned short h;
		UInt32_t l;
		char s[MAXstring];
		unsigned char hs[2];	/* 2 bytes of a fixed-endian "short" */
		unsigned char hl[4];	/* 2 bytes of a fixed-endian "long" */
	} value;		/* either number or string */
	UInt32_t mask;	/* mask before comparison with value */
	char nospflag;		/* supress space character */
	char desc[MAXDESC];	/* description */
};

#include <stdio.h>	/* Include that here, to make sure __P gets defined */

extern int   init_magic		__PR((char *));
extern int   ascmagic		__PR((unsigned char *, int));
/*extern void  error		__PR((const char *, ...));*/
extern void  ckfputs		__PR((const char *, FILE *));
struct stat;
extern int   fsmagic		__PR((const char *, struct stat *));
extern int   is_compress	__PR((const unsigned char *, int *));
extern int   is_tar		__PR((unsigned char *, int));
extern void  magwarn		__PR((const char *, ...));
extern void  mdump		__PR((struct magic *));
extern char *get_magic_magic	__PR((const char *));
extern void  showstr		__PR((FILE *, const char *, int));
extern char *softmagic		__PR((unsigned char *, int));
extern int   tryit		__PR((unsigned char *, int, int));
extern int   zmagic		__PR((unsigned char *, int));
extern void  ckfprintf		__PR((FILE *, const char *, ...));
#ifndef __BEOS__
extern UInt32_t signextend	__PR((struct magic *, UInt32_t));
#endif /* __BEOS__ */
extern int internatmagic	__PR((unsigned char *, int));
extern void tryelf		__PR((int, char *, int));


extern char *progname;		/* the program name 			*/
extern char *magicfile;		/* name of the magic file		*/
extern int lineno;		/* current line number in magic file	*/

extern struct magic *__f_magic;	/* array of magic entries		*/
extern int __f_nmagic;		/* number of valid magic[]s 		*/


extern int debug;		/* enable debugging?			*/
extern int zflag;		/* process compressed files?		*/
extern int lflag;		/* follow symbolic links?		*/

extern int optind;		/* From getopt(3)			*/
extern char *optarg;

#if defined(sun) || defined(__sun__) || defined (__sun)
# if defined(__svr4) || defined (__SVR4) || defined(__svr4__)
#  define SOLARIS
# else
#  define SUNOS
# endif
#endif


#if !defined(__STDC__) || defined(SUNOS) || defined(__convex__)
extern int sys_nerr;
extern char *sys_errlist[];
#define strerror(e) \
	(((e) >= 0 && (e) < sys_nerr) ? sys_errlist[(e)] : "Unknown error")
#define strtoul(a, b, c)	strtol(a, b, c)
#endif

#endif /* __file_h__ */
