/*	$OpenBSD: pax.h,v 1.29 2017/09/12 17:11:11 otto Exp $	*/
/*	$NetBSD: pax.h,v 1.3 1995/03/21 09:07:41 cgd Exp $	*/

/*-
 * Copyright © 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010,
 *	       2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018
 *	mirabilos <m@mirbsd.org>
 * Copyright © 2018
 *	mirabilos <t.glaser@tarent.de>
 * The UCB copyright below is considered part of this notice.
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un‐
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person’s immediate fault when using the work as intended.
 */

/*-
 * Copyright (c) 1992 Keith Muller.
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Keith Muller of the University of California, San Diego.
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
 *	@(#)pax.h	8.2 (Berkeley) 4/18/94
 */

#if HAVE_SYS_MKDEV_H
#include <sys/mkdev.h>
#endif
#if HAVE_SYS_SYSMACROS_H
#include <sys/sysmacros.h>
#endif
#if HAVE_STDINT_H
#include <stdint.h>
#endif

#undef __attribute__
#if HAVE_ATTRIBUTE_BOUNDED
#define MKSH_A_BOUNDED(x,y,z)	__attribute__((__bounded__(x, y, z)))
#else
#define MKSH_A_BOUNDED(x,y,z)	/* nothing */
#endif
#if HAVE_ATTRIBUTE_FORMAT
#define MKSH_A_FORMAT(x,y,z)	__attribute__((__format__(x, y, z)))
#else
#define MKSH_A_FORMAT(x,y,z)	/* nothing */
#endif
#if HAVE_ATTRIBUTE_NONNULL
#define MKSH_A_NONNULL(x)	__attribute__((__nonnull__(x)))
#else
#define MKSH_A_NONNULL(x)	/* nothing */
#endif
#if HAVE_ATTRIBUTE_NORETURN
#define MKSH_A_NORETURN		__attribute__((__noreturn__))
#else
#define MKSH_A_NORETURN		/* nothing */
#endif
#if HAVE_ATTRIBUTE_PURE
#define MKSH_A_PURE		__attribute__((__pure__))
#else
#define MKSH_A_PURE		/* nothing */
#endif
#if HAVE_ATTRIBUTE_UNUSED
#define MKSH_A_UNUSED		__attribute__((__unused__))
#else
#define MKSH_A_UNUSED		/* nothing */
#endif
#if HAVE_ATTRIBUTE_USED
#define MKSH_A_USED		__attribute__((__used__))
#else
#define MKSH_A_USED		/* nothing */
#endif

#if defined(MirBSD) && (MirBSD >= 0x09A1) && \
    defined(__ELF__) && defined(__GNUC__) && \
    !defined(__llvm__) && !defined(__NWCC__)
/*
 * We got usable __IDSTRING __COPYRIGHT __RCSID __SCCSID macros
 * which work for all cases; no need to redefine them using the
 * "portable" macros from below when we might have the "better"
 * gcc+ELF specific macros or other system dependent ones.
 */
#else
#undef __IDSTRING
#undef __IDSTRING_CONCAT
#undef __IDSTRING_EXPAND
#undef __COPYRIGHT
#undef __RCSID
#undef __SCCSID
#define __IDSTRING_CONCAT(l,p)		__LINTED__ ## l ## _ ## p
#define __IDSTRING_EXPAND(l,p)		__IDSTRING_CONCAT(l,p)
#ifdef MKSH_DONT_EMIT_IDSTRING
#define __IDSTRING(prefix, string)	/* nothing */
#else
#define __IDSTRING(prefix, string)				\
	static const char __IDSTRING_EXPAND(__LINE__,prefix) []	\
	    MKSH_A_USED = "@(""#)" #prefix ": " string
#endif
#define __COPYRIGHT(x)		__IDSTRING(copyright,x)
#define __RCSID(x)		__IDSTRING(rcsid,x)
#define __SCCSID(x)		__IDSTRING(sccsid,x)
#endif

#ifdef EXTERN
__IDSTRING(rcsid_pax_h, "$MirOS: src/bin/pax/pax.h,v 1.1.1.8.2.3 2018/12/12 03:13:34 tg Exp $");
#endif

/* arithmetic types: C implementation */
#if !HAVE_CAN_INTTYPES
#if !HAVE_CAN_UCBINTS
typedef signed int int32_t;
typedef unsigned int uint32_t;
#else
typedef u_int32_t uint32_t;
#endif
#endif
#if !HAVE_CAN_INT16TYPE
#if !HAVE_CAN_UCBINT16
typedef unsigned short int uint16_t;
#else
typedef u_int16_t uint16_t;
#endif
#endif

#ifdef MKSH_TYPEDEF_SSIZE_T
typedef MKSH_TYPEDEF_SSIZE_T ssize_t;
#endif

#if HAVE_ST_MTIM
#define st_atim_cmp(sbpa,sbpb,op) \
		timespeccmp(&(sbpa)->st_atim, &(sbpb)->st_atim, op)
#define st_ctim_cmp(sbpa,sbpb,op) \
		timespeccmp(&(sbpa)->st_ctim, &(sbpb)->st_ctim, op)
#define st_mtim_cmp(sbpa,sbpb,op) \
		timespeccmp(&(sbpa)->st_mtim, &(sbpb)->st_mtim, op)
#elif HAVE_ST_MTIMENSEC
#define st_atim_cmp(sbpa,sbpb,op) ( \
		((sbpa)->st_atime == (sbpb)->st_atime) ? \
		    ((sbpa)->st_atimensec op (sbpb)->st_atimensec) : \
		    ((sbpa)->st_atime op (sbpb)->st_atime) \
		)
#define st_ctim_cmp(sbpa,sbpb,op) ( \
		((sbpa)->st_ctime == (sbpb)->st_ctime) ? \
		    ((sbpa)->st_ctimensec op (sbpb)->st_ctimensec) : \
		    ((sbpa)->st_ctime op (sbpb)->st_ctime) \
		)
#define st_mtim_cmp(sbpa,sbpb,op) ( \
		((sbpa)->st_mtime == (sbpb)->st_mtime) ? \
		    ((sbpa)->st_mtimensec op (sbpb)->st_mtimensec) : \
		    ((sbpa)->st_mtime op (sbpb)->st_mtime) \
		)
#else
#define st_atim_cmp(sbpa,sbpb,op) \
		((sbpa)->st_atime op (sbpb)->st_atime)
#define st_ctim_cmp(sbpa,sbpb,op) \
		((sbpa)->st_ctime op (sbpb)->st_ctime)
#define st_mtim_cmp(sbpa,sbpb,op) \
		((sbpa)->st_mtime op (sbpb)->st_mtime)
#endif

/* compat.c */

#if !HAVE_DPRINTF
/* replacement only as powerful as needed for this */
void dprintf(int, const char *, ...)
    MKSH_A_FORMAT(__printf__, 2, 3);
#endif

/*
 * BSD PAX global data structures and constants.
 */

#define	MAXBLK		64512	/* MAX blocksize supported (posix SPEC) */
				/* WARNING: increasing MAXBLK past 32256 */
				/* will violate posix spec. */
#define	MAXBLK_POSIX	32256	/* MAX blocksize supported as per POSIX */
#define BLKMULT		512	/* blocksize must be even mult of 512 bytes */
				/* Don't even think of changing this */
#define DEVBLK		8192	/* default read blksize for devices */
#define FILEBLK		10240	/* default read blksize for files */
#define PAXPATHLEN	3072	/* maximum path length for pax. MUST be */
				/* longer than the system PATH_MAX */

/*
 * Pax modes of operation
 */
#define	LIST		0	/* List the file in an archive */
#define	EXTRACT		1	/* extract the files in an archive */
#define ARCHIVE		2	/* write a new archive */
#define APPND		3	/* append to the end of an archive */
#define	COPY		4	/* copy files to destination dir */
#define DEFOP		LIST	/* if no flags default is to LIST */

/*
 * Device type of the current archive volume
 */
#define ISREG		0	/* regular file */
#define ISCHR		1	/* character device */
#define ISBLK		2	/* block device */
#define ISTAPE		3	/* tape drive */
#define ISPIPE		4	/* pipe/socket */

/*
 * Pattern matching structure
 *
 * Used to store command line patterns
 */
typedef struct pattern {
	char		*pstr;		/* pattern to match, user supplied */
	char		*pend;		/* end of a prefix match */
	char		*chdname;	/* the dir to change to if not NULL.  */
	size_t		plen;		/* length of pstr */
	int		flgs;		/* processing/state flags */
#define MTCH		0x1		/* pattern has been matched */
#define DIR_MTCH	0x2		/* pattern matched a directory */
	struct pattern	*fow;		/* next pattern */
} PATTERN;

/*
 * General Archive Structure (used internal to pax)
 *
 * This structure is used to pass information about archive members between
 * the format independent routines and the format specific routines. When
 * new archive formats are added, they must accept requests and supply info
 * encoded in a structure of this type. The name fields are declared statically
 * here, as there is only ONE of these floating around, size is not a major
 * consideration. Eventually converting the name fields to a dynamic length
 * may be required if and when the supporting operating system removes all
 * restrictions on the length of pathnames it will resolve.
 */
typedef struct {
	int nlen;			/* file name length */
	char name[PAXPATHLEN+1];	/* file name */
	int ln_nlen;			/* link name length */
	char ln_name[PAXPATHLEN+1];	/* name to link to (if any) */
	char *org_name;			/* orig name in file system */
	PATTERN *pat;			/* ptr to pattern match (if any) */
	struct stat sb;			/* stat buffer see stat(2) */
	off_t pad;			/* bytes of padding after file xfer */
	off_t skip;			/* bytes of real data after header */
					/* IMPORTANT. The st_size field does */
					/* not always indicate the amount of */
					/* data following the header. */
	uint32_t crc;			/* file crc */
	int type;			/* type of file node */
#define PAX_DIR		1		/* directory */
#define PAX_CHR		2		/* character device */
#define PAX_BLK		3		/* block device */
#define PAX_REG		4		/* regular file */
#define PAX_SLK		5		/* symbolic link */
#define PAX_SCK		6		/* socket */
#define PAX_FIF		7		/* fifo */
#define PAX_HLK		8		/* hard link */
#define PAX_HRG		9		/* hard link to a regular file */
#define PAX_CTG		10		/* high performance file */
#define PAX_GLL		11		/* GNU long symlink */
#define PAX_GLF		12		/* GNU long file */
} ARCHD;

#define PAX_IS_REG(type)	((type) == PAX_REG || (type) == PAX_CTG)
#define PAX_IS_HARDLINK(type)	((type) == PAX_HLK || (type) == PAX_HRG)
#define PAX_IS_LINK(type)	((type) == PAX_SLK || PAX_IS_HARDLINK(type))

/*
 * Format Specific Routine Table
 *
 * The format specific routine table allows new archive formats to be quickly
 * added. Overall pax operation is independent of the actual format used to
 * form the archive. Only those routines which deal directly with the archive
 * are tailored to the oddities of the specific format. All other routines are
 * independent of the archive format. Data flow in and out of the format
 * dependent routines pass pointers to ARCHD structure (described below).
 */
typedef struct {
	char *name;		/* name of format, this is the name the user */
				/* gives to -x option to select it. */
	int bsz;		/* default block size. used when the user */
				/* does not specify a blocksize for writing */
				/* Appends continue to with the blocksize */
				/* the archive is currently using. */
	int hsz;		/* Header size in bytes. this is the size of */
				/* the smallest header this format supports. */
				/* Headers are assumed to fit in a BLKMULT. */
				/* If they are bigger, get_head() and */
				/* get_arc() must be adjusted */
	int udev;		/* does append require unique dev/ino? some */
				/* formats use the device and inode fields */
				/* to specify hard links. when members in */
				/* the archive have the same inode/dev they */
				/* are assumed to be hard links. During */
				/* append we may have to generate unique ids */
				/* to avoid creating incorrect hard links */
	int hlk;		/* does archive store hard links info? if */
				/* not, we do not bother to look for them */
				/* during archive write operations */
	int blkalgn;		/* writes must be aligned to blkalgn boundary */
	int inhead;		/* is the trailer encoded in a valid header? */
				/* if not, trailers are assumed to be found */
				/* in invalid headers (i.e like tar) */
	int (*id)(char *,	/* checks if a buffer is a valid header */
	    int);		/* returns 1 if it is, o.w. returns a 0 */
	int (*st_rd)(void);	/* initialize routine for read. so format */
				/* can set up tables etc before it starts */
				/* reading an archive */
	int (*rd)(ARCHD *,	/* read header routine. passed a pointer to */
	    char *);		/* ARCHD. It must extract the info from the */
				/* format and store it in the ARCHD struct. */
				/* This routine is expected to fill all the */
				/* fields in the ARCHD (including stat buf) */
				/* 0 is returned when a valid header is */
				/* found. -1 when not valid. This routine */
				/* set the skip and pad fields so the format */
				/* independent routines know the amount of */
				/* padding and the number of bytes of data */
				/* which follow the header. This info is */
				/* used skip to the next file header */
	off_t (*end_rd)(void);	/* read cleanup. Allows format to clean up */
				/* and MUST RETURN THE LENGTH OF THE TRAILER */
				/* RECORD (so append knows how many bytes */
				/* to move back to rewrite the trailer) */
	int (*st_wr)(void);	/* initialize routine for write operations */
	int (*wr)(ARCHD *);	/* write archive header. Passed an ARCHD */
				/* filled with the specs on the next file to */
				/* archived. Returns a 1 if no file data is */
				/* is to be stored; 0 if file data is to be */
				/* added. A -1 is returned if a write */
				/* operation to the archive failed. this */
				/* function sets the skip and pad fields so */
				/* the proper padding can be added after */
				/* file data. This routine must NEVER write */
				/* a flawed archive header. */
	int (*end_wr)(void);	/* end write. write the trailer and do any */
				/* other format specific functions needed */
				/* at the end of an archive write */
	int (*trail)(ARCHD *,	/* returns 0 if a valid trailer, -1 if not */
	    char *, int,	/* For formats which encode the trailer */
	    int *);		/* outside of a valid header, a return value */
				/* of 1 indicates that the block passed to */
				/* it can never contain a valid header (skip */
				/* this block, no point in looking at it)  */
				/* CAUTION: parameters to this function are */
				/* different for trailers inside or outside */
				/* of headers. See get_head() for details */
	int (*options)(void);	/* process format specific options (-o) */
} FSUB;

/*
 * Time data for a given file.  This is usually embedded in a structure
 * indexed by dev+ino, by name, by order in the archive, etc.  set_attr()
 * takes one of these and will only change the times or mode if the file
 * at the given name has the indicated dev+ino.
 */
struct file_times {
	ino_t	ft_ino;			/* inode number to verify */
	struct	timespec ft_mtim;	/* times to set */
	struct	timespec ft_atim;
	char	*ft_name;		/* name of file to set the times on */
	dev_t	ft_dev;			/* device number to verify */
};

/*
 * Format Specific Options List
 *
 * Used to pass format options to the format options handler
 */
typedef struct oplist {
	char		*name;		/* option variable name e.g. name= */
	char		*value;		/* value for option variable */
	struct oplist	*fow;		/* next option */
} OPLIST;

/*
 * General Macros
 */
#define MINIMUM(a, b)	(((a) < (b)) ? (a) : (b))
#define MAJOR(x)	major(x)
#define MINOR(x)	minor(x)
#define TODEV(x, y)	makedev((x), (y))

#define FILEBITS	(S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO)
#define SETBITS		(S_ISUID | S_ISGID)
#define ABITS		(FILEBITS | SETBITS)

/*
 * General Defines
 */
#define HEX		16
#define OCT		8
#define _PAX_		1
#define _TFILE_BASE	"paxXXXXXXXXXX"
#if HAVE_TIMET_LLONG
#define MAX_TIME_T	LLONG_MAX
#else
#define MAX_TIME_T	LONG_MAX
#endif
