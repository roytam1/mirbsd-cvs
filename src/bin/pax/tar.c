/*	$OpenBSD: tar.c,v 1.43 +1.57 +1.59 2010/12/02 04:08:27 tedu Exp $	*/
/*	$NetBSD: tar.c,v 1.5 1995/03/21 09:07:49 cgd Exp $	*/

/*-
 * Copyright (c) 2006, 2012, 2016, 2017
 *	mirabilos <m@mirbsd.org>
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
 */

#include <sys/param.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "pax.h"
#include "extern.h"
#include "tar.h"
#include "options.h"

__RCSID("$MirOS: src/bin/pax/tar.c,v 1.18 2017/08/07 20:10:19 tg Exp $");

/*
 * Routines for reading, writing and header identify of various versions of tar
 */

static size_t expandname(char *, size_t, char **, const char *, size_t);
static u_long tar_chksm(char *, int);
static char *name_split(char *, int);
static int ul_oct(u_long, char *, int, int);
static int ot_oct(ot_type, char *, int, int);

static void tar_dbgfld(const char *, const char *, size_t);

static uid_t uid_nobody;
static uid_t uid_warn;
static gid_t gid_nobody;
static gid_t gid_warn;

/*
 * Routines common to all versions of tar
 */

#ifndef SMALL
int tar_nodir;				/* do not write dirs under old tar */
#endif
char *gnu_name_string;			/* GNU ././@LongLink hackery name */
char *gnu_link_string;			/* GNU ././@LongLink hackery link */

/*
 * tar_endwr()
 *	add the tar trailer of two null blocks
 * Return:
 *	0 if ok, -1 otherwise (what wr_skip returns)
 */

int
tar_endwr(void)
{
	return(wr_skip((off_t)(NULLCNT*BLKMULT)));
}

/*
 * tar_endrd()
 *	no cleanup needed here, just return size of trailer (for append)
 * Return:
 *	size of trailer (2 * BLKMULT)
 */

off_t
tar_endrd(void)
{
	return((off_t)(NULLCNT*BLKMULT));
}

/*
 * tar_trail()
 *	Called to determine if a header block is a valid trailer. We are passed
 *	the block, the in_sync flag (which tells us we are in resync mode;
 *	looking for a valid header), and cnt (which starts at zero) which is
 *	used to count the number of empty blocks we have seen so far.
 * Return:
 *	0 if a valid trailer, -1 if not a valid trailer, or 1 if the block
 *	could never contain a header.
 */

int
tar_trail(ARCHD *ignore __attribute__((__unused__)), char *buf,
    int in_resync, int *cnt)
{
	int i;

	/*
	 * look for all zero, trailer is two consecutive blocks of zero
	 */
	for (i = 0; i < BLKMULT; ++i) {
		if (buf[i] != '\0')
			break;
	}

	/*
	 * if not all zero it is not a trailer, but MIGHT be a header.
	 */
	if (i != BLKMULT)
		return(-1);

	/*
	 * When given a zero block, we must be careful!
	 * If we are not in resync mode, check for the trailer. Have to watch
	 * out that we do not mis-identify file data as the trailer, so we do
	 * NOT try to id a trailer during resync mode. During resync mode we
	 * might as well throw this block out since a valid header can NEVER be
	 * a block of all 0 (we must have a valid file name).
	 */
	if (!in_resync && (++*cnt >= NULLCNT))
		return(0);
	return(1);
}

/*
 * ul_oct()
 *	convert an unsigned long to an octal string. many oddball field
 *	termination characters are used by the various versions of tar in the
 *	different fields. term selects which kind to use. str is '0' padded
 *	at the front to len. we are unable to use only one format as many old
 *	tar readers are very cranky about this.
 * Return:
 *	0 if the number fit into the string, -1 otherwise
 */

static int
ul_oct(u_long val, char *str, int len, int term)
{
	char *pt;

	/*
	 * term selects the appropriate character(s) for the end of the string
	 */
	pt = str + len - 1;
	switch (term) {
	case 3:
		*pt-- = '\0';
		break;
	case 2:
		*pt-- = ' ';
		*pt-- = '\0';
		break;
	case 1:
		*pt-- = ' ';
		break;
	case 0:
	default:
		*pt-- = '\0';
		*pt-- = ' ';
		break;
	}

	/*
	 * convert and blank pad if there is space
	 */
	while (pt >= str) {
		*pt-- = '0' + (char)(val & 0x7);
		if ((val = val >> 3) == (u_long)0)
			break;
	}

	while (pt >= str)
		*pt-- = '0';
	if (val != (u_long)0)
		return(-1);
	return(0);
}

/*
 * ot_oct()
 *	convert an ot_type to an octal string. one of many oddball
 *	field termination characters are used by the various versions
 *	of tar in the different fields. term selects which kind to use.
 *	str is '0' padded at the front to len. we are unable to use only
 *	one format as many old tar readers are very cranky about this.
 * Return:
 *	0 if the number fit into the string, -1 otherwise
 */

static int
ot_oct(ot_type val, char *str, int len, int term)
{
	char *pt;

	/*
	 * term selects the appropriate character(s) for the end of the string
	 */
	pt = str + len - 1;
	switch (term) {
	case 3:
		*pt-- = '\0';
		break;
	case 2:
		*pt-- = ' ';
		*pt-- = '\0';
		break;
	case 1:
		*pt-- = ' ';
		break;
	case 0:
	default:
		*pt-- = '\0';
		*pt-- = ' ';
		break;
	}

	/*
	 * convert and blank pad if there is space
	 */
	while (pt >= str) {
		*pt-- = '0' + (char)(val & 0x7);
		if ((val = val >> 3) == 0)
			break;
	}

	while (pt >= str)
		*pt-- = '0';
	if (val != (ot_type)0)
		return (-1);
	return (0);
}

/*
 * tar_chksm()
 *	calculate the checksum for a tar block counting the checksum field as
 *	all blanks (BLNKSUM is that value pre-calculated, the sum of 8 blanks).
 *	NOTE: we use len to short circuit summing 0's on write since we ALWAYS
 *	pad headers with 0.
 * Return:
 *	unsigned long checksum
 */

static u_long
tar_chksm(char *blk, int len)
{
	char *stop;
	char *pt;
	u_long chksm = BLNKSUM;	/* initial value is checksum field sum */

	/*
	 * add the part of the block before the checksum field
	 */
	pt = blk;
	stop = blk + CHK_OFFSET;
	while (pt < stop)
		chksm += (u_long)(*pt++ & 0xff);
	/*
	 * move past the checksum field and keep going, spec counts the
	 * checksum field as the sum of 8 blanks (which is pre-computed as
	 * BLNKSUM).
	 * ASSUMED: len is greater than CHK_OFFSET. (len is where our 0 padding
	 * starts, no point in summing zero's)
	 */
	pt += CHK_LEN;
	stop = blk + len;
	while (pt < stop)
		chksm += (u_long)(*pt++ & 0xff);
	return(chksm);
}

#ifndef SMALL
/*
 * Routines for old BSD style tar (also made portable to sysV tar)
 */

/*
 * tar_id()
 *	determine if a block given to us is a valid tar header (and not a USTAR
 *	header). We have to be on the lookout for those pesky blocks of	all
 *	zero's.
 * Return:
 *	0 if a tar header, -1 otherwise
 */

int
tar_id(char *blk, int size)
{
	HD_TAR *hd;
	HD_USTAR *uhd;

	if (size < BLKMULT)
		return(-1);
	hd = (HD_TAR *)blk;
	uhd = (HD_USTAR *)blk;

	/*
	 * check for block of zero's first, a simple and fast test, then make
	 * sure this is not a ustar header by looking for the ustar magic
	 * cookie. We should use TMAGLEN, but some USTAR archive programs are
	 * wrong and create archives missing the \0. Last we check the
	 * checksum. If this is ok we have to assume it is a valid header.
	 */
	if (hd->name[0] == '\0')
		return(-1);
	if (strncmp(uhd->magic, TMAGIC, TMAGLEN - 1) == 0)
		return(-1);
	if (asc_ul(hd->chksum,sizeof(hd->chksum),OCT) != tar_chksm(blk,BLKMULT))
		return(-1);
	force_one_volume = 1;
	return(0);
}

/*
 * tar_opt()
 *	handle tar format specific -o options
 * Return:
 *	0 if ok -1 otherwise
 */

int
tar_opt(void)
{
	OPLIST *opt;

	while ((opt = opt_next()) != NULL) {
		if (strcmp(opt->name, TAR_OPTION) ||
		    strcmp(opt->value, TAR_NODIR)) {
			paxwarn(1, "Unknown tar format -o option/value pair %s=%s",
			    opt->name, opt->value);
			paxwarn(1,"%s=%s is the only supported tar format option",
			    TAR_OPTION, TAR_NODIR);
			return(-1);
		}

		/*
		 * we only support one option, and only when writing
		 */
		if ((act != APPND) && (act != ARCHIVE)) {
			paxwarn(1, "%s=%s is only supported when writing.",
			    opt->name, opt->value);
			return(-1);
		}
		tar_nodir = 1;
	}
	return(0);
}


/*
 * tar_rd()
 *	extract the values out of block already determined to be a tar header.
 *	store the values in the ARCHD parameter.
 * Return:
 *	0
 */

int
tar_rd(ARCHD *arcn, char *buf)
{
	HD_TAR *hd;
	char *pt;

	/*
	 * we only get proper sized buffers passed to us
	 */
	if (tar_id(buf, BLKMULT) < 0)
		return(-1);
	memset(arcn, 0, sizeof(*arcn));
	arcn->org_name = arcn->name;
	arcn->sb.st_nlink = 1;

	/*
	 * copy out the name and values in the stat buffer
	 */
	hd = (HD_TAR *)buf;
	if (hd->linkflag != LONGLINKTYPE && hd->linkflag != LONGNAMETYPE) {
		arcn->nlen = expandname(arcn->name, sizeof(arcn->name),
		    &gnu_name_string, hd->name, sizeof(hd->name));
		arcn->ln_nlen = expandname(arcn->ln_name, sizeof(arcn->ln_name),
		    &gnu_link_string, hd->linkname, sizeof(hd->linkname));
	}
	arcn->sb.st_mode = (mode_t)(asc_ul(hd->mode,sizeof(hd->mode),OCT) &
	    0xfff);
	arcn->sb.st_uid = (uid_t)asc_ul(hd->uid, sizeof(hd->uid), OCT);
	arcn->sb.st_gid = (gid_t)asc_ul(hd->gid, sizeof(hd->gid), OCT);
	arcn->sb.st_size = (off_t)asc_ot(hd->size, sizeof(hd->size), OCT);
	arcn->sb.st_mtime = (time_t)asc_ul(hd->mtime, sizeof(hd->mtime), OCT);
	arcn->sb.st_ctime = arcn->sb.st_atime = arcn->sb.st_mtime;

	/*
	 * have to look at the last character, it may be a '/' and that is used
	 * to encode this as a directory
	 */
	pt = arcn->nlen > 0 ? &(arcn->name[arcn->nlen - 1]) : NULL;
	arcn->pad = 0;
	arcn->skip = 0;
	switch (hd->linkflag) {
	case SYMTYPE:
		/*
		 * symbolic link, need to get the link name and set the type in
		 * the st_mode so -v printing will look correct.
		 */
		arcn->type = PAX_SLK;
		arcn->sb.st_mode |= S_IFLNK;
		break;
	case LNKTYPE:
		/*
		 * hard link, need to get the link name, set the type in the
		 * st_mode and st_nlink so -v printing will look better.
		 */
		arcn->type = PAX_HLK;
		arcn->sb.st_nlink = 2;

		/*
		 * no idea of what type this thing really points at, but
		 * we set something for printing only.
		 */
		arcn->sb.st_mode |= S_IFREG;
		break;
	case LONGLINKTYPE:
	case LONGNAMETYPE:
		/*
		 * GNU long link/file; we tag these here and let the
		 * pax internals deal with it -- too ugly otherwise.
		 */
		arcn->type =
		    hd->linkflag == LONGLINKTYPE ? PAX_GLL : PAX_GLF;
		arcn->pad = TAR_PAD(arcn->sb.st_size);
		arcn->skip = arcn->sb.st_size;
		break;
	case DIRTYPE:
		/*
		 * It is a directory, set the mode for -v printing
		 */
		arcn->type = PAX_DIR;
		arcn->sb.st_mode |= S_IFDIR;
		arcn->sb.st_nlink = 2;
		break;
	case AREGTYPE:
	case REGTYPE:
	default:
		/*
		 * If we have a trailing / this is a directory and NOT a file.
		 */
		arcn->ln_name[0] = '\0';
		arcn->ln_nlen = 0;
		if (pt && *pt == '/') {
			/*
			 * it is a directory, set the mode for -v printing
			 */
			arcn->type = PAX_DIR;
			arcn->sb.st_mode |= S_IFDIR;
			arcn->sb.st_nlink = 2;
		} else {
			/*
			 * have a file that will be followed by data. Set the
			 * skip value to the size field and calculate the size
			 * of the padding.
			 */
			arcn->type = PAX_REG;
			arcn->sb.st_mode |= S_IFREG;
			arcn->pad = TAR_PAD(arcn->sb.st_size);
			arcn->skip = arcn->sb.st_size;
		}
		break;
	}

	/*
	 * strip off any trailing slash.
	 */
	if (pt && *pt == '/') {
		*pt = '\0';
		--arcn->nlen;
	}
	return(0);
}

/*
 * tar_wr()
 *	write a tar header for the file specified in the ARCHD to the archive.
 *	Have to check for file types that cannot be stored and file names that
 *	are too long. Be careful of the term (last arg) to ul_oct, each field
 *	of tar has it own spec for the termination character(s).
 *	ASSUMED: space after header in header block is zero filled
 * Return:
 *	0 if file has data to be written after the header, 1 if file has NO
 *	data to write after the header, -1 if archive write failed
 */

int
tar_wr(ARCHD *arcn)
{
	HD_TAR *hd;
	int len;
	char hdblk[sizeof(HD_TAR)];

	/*
	 * check for those filesystem types which tar cannot store
	 */
	switch (arcn->type) {
	case PAX_DIR:
		/*
		 * user asked that dirs not be written to the archive
		 */
		if (tar_nodir)
			return(1);
		break;
	case PAX_CHR:
		paxwarn(1, "tar cannot archive a character device %s",
		    arcn->org_name);
		return(1);
	case PAX_BLK:
		paxwarn(1, "tar cannot archive a block device %s", arcn->org_name);
		return(1);
	case PAX_SCK:
		paxwarn(1, "tar cannot archive a socket %s", arcn->org_name);
		return(1);
	case PAX_FIF:
		paxwarn(1, "tar cannot archive a fifo %s", arcn->org_name);
		return(1);
	case PAX_SLK:
	case PAX_HLK:
	case PAX_HRG:
		if ((size_t)arcn->ln_nlen > sizeof(hd->linkname)) {
			paxwarn(1, "Link name too long for tar %s",
			    arcn->ln_name);
			return(1);
		}
		break;
	case PAX_REG:
	case PAX_CTG:
	default:
		break;
	}

	/*
	 * check file name len, remember extra char for dirs (the / at the end)
	 */
	len = arcn->nlen;
	if (arcn->type == PAX_DIR)
		++len;
	if ((size_t)len > sizeof(hd->name)) {
		paxwarn(1, "File name too long for tar %s", arcn->name);
		return(1);
	}

	/*
	 * Copy the data out of the ARCHD into the tar header based on the type
	 * of the file. Remember, many tar readers want all fields to be
	 * padded with zero so we zero the header first.  We then set the
	 * linkflag field (type), the linkname, the size, and set the padding
	 * (if any) to be added after the file data (0 for all other types,
	 * as they only have a header).
	 */
	memset(hdblk, 0, sizeof(hdblk));
	hd = (HD_TAR *)hdblk;
	fieldcpy(hd->name, sizeof(hd->name), arcn->name, sizeof(arcn->name));
	arcn->pad = 0;

	if (arcn->type == PAX_DIR) {
		/*
		 * directories are the same as files, except have a filename
		 * that ends with a /, we add the slash here. No data follows
		 * dirs, so no pad.
		 */
		hd->linkflag = AREGTYPE;
		hd->name[len-1] = '/';
		if (ul_oct((u_long)0L, hd->size, sizeof(hd->size), 1))
			goto out;
	} else if (arcn->type == PAX_SLK) {
		/*
		 * no data follows this file, so no pad
		 */
		hd->linkflag = SYMTYPE;
		fieldcpy(hd->linkname, sizeof(hd->linkname), arcn->ln_name,
		    sizeof(arcn->ln_name));
		if (ul_oct((u_long)0L, hd->size, sizeof(hd->size), 1))
			goto out;
	} else if ((arcn->type == PAX_HLK) || (arcn->type == PAX_HRG)) {
		/*
		 * no data follows this file, so no pad
		 */
		hd->linkflag = LNKTYPE;
		fieldcpy(hd->linkname, sizeof(hd->linkname), arcn->ln_name,
		    sizeof(arcn->ln_name));
		if (ul_oct((u_long)0L, hd->size, sizeof(hd->size), 1))
			goto out;
	} else {
		/*
		 * data follows this file, so set the pad
		 */
		hd->linkflag = AREGTYPE;
		if (ot_oct(arcn->sb.st_size, hd->size, sizeof(hd->size), 1)) {
			paxwarn(1,"File is too large for tar %s", arcn->org_name);
			return(1);
		}
		arcn->pad = TAR_PAD(arcn->sb.st_size);
	}

	/*
	 * copy those fields that are independent of the type
	 */
	if (ul_oct((u_long)arcn->sb.st_mode, hd->mode, sizeof(hd->mode), 0) ||
	    ul_oct((u_long)arcn->sb.st_uid, hd->uid, sizeof(hd->uid), 0) ||
	    ul_oct((u_long)arcn->sb.st_gid, hd->gid, sizeof(hd->gid), 0) ||
	    ul_oct((u_long)(u_int)arcn->sb.st_mtime, hd->mtime, sizeof(hd->mtime), 1))
		goto out;

	/*
	 * calculate and add the checksum, then write the header. A return of
	 * 0 tells the caller to now write the file data, 1 says no data needs
	 * to be written
	 */
	if (ul_oct(tar_chksm(hdblk, sizeof(HD_TAR)), hd->chksum,
	    sizeof(hd->chksum), 3))
		goto out;
	if (wr_rdbuf(hdblk, sizeof(HD_TAR)) < 0)
		return(-1);
	if (wr_skip((off_t)(BLKMULT - sizeof(HD_TAR))) < 0)
		return(-1);
	if ((arcn->type == PAX_CTG) || (arcn->type == PAX_REG))
		return(0);
	return(1);

 out:
	/*
	 * header field is out of range
	 */
	paxwarn(1, "tar header field is too small for %s", arcn->org_name);
	return(1);
}
#endif

/*
 * Routines for POSIX ustar
 */

/*
 * ustar_strd()
 *	initialization for ustar read
 * Return:
 *	0 if ok, -1 otherwise
 */

int
ustar_strd(void)
{
	if ((usrtb_start() < 0) || (grptb_start() < 0))
		return(-1);
	return(0);
}

/*
 * ustar_stwr()
 *	initialization for ustar write
 * Return:
 *	0 if ok, -1 otherwise
 */

int
ustar_stwr(int is_app __attribute__((__unused__)))
{
	if ((uidtb_start() < 0) || (gidtb_start() < 0))
		return(-1);
	return(0);
}

/*
 * ustar_id()
 *	determine if a block given to us is a valid ustar header. We have to
 *	be on the lookout for those pesky blocks of all zero's
 * Return:
 *	0 if a ustar header, -1 otherwise
 */

int
ustar_id(char *blk, int size)
{
	HD_USTAR *hd;

	if (size < BLKMULT)
		return(-1);
	hd = (HD_USTAR *)blk;

	/*
	 * check for block of zero's first, a simple and fast test then check
	 * ustar magic cookie. We should use TMAGLEN, but some USTAR archive
	 * programs are fouled up and create archives missing the \0. Last we
	 * check the checksum. If ok we have to assume it is a valid header.
	 */
	if (hd->prefix[0] == '\0' && hd->name[0] == '\0')
		return(-1);
	if (strncmp(hd->magic, TMAGIC, TMAGLEN - 1) != 0)
		return(-1);
	if (asc_ul(hd->chksum,sizeof(hd->chksum),OCT) != tar_chksm(blk,BLKMULT))
		return(-1);
	return(0);
}

/*
 * ustar_rd()
 *	extract the values out of block already determined to be a ustar header.
 *	store the values in the ARCHD parameter.
 * Return:
 *	0
 */

int
ustar_rd(ARCHD *arcn, char *buf)
{
	HD_USTAR *hd;
	char *dest;
	int cnt = 0;
	dev_t devmajor;
	dev_t devminor;

	/*
	 * we only get proper sized buffers
	 */
	if (ustar_id(buf, BLKMULT) < 0)
		return(-1);
	memset(arcn, 0, sizeof(*arcn));
	arcn->org_name = arcn->name;
	arcn->sb.st_nlink = 1;
	hd = (HD_USTAR *)buf;

	/*
	 * see if the filename is split into two parts. if, so joint the parts.
	 * we copy the prefix first and add a / between the prefix and name.
	 */
	dest = arcn->name;
	if (*(hd->prefix) != '\0') {
		cnt = fieldcpy(dest, sizeof(arcn->name) - 1, hd->prefix,
		    sizeof(hd->prefix));
		dest += cnt;
		*dest++ = '/';
		cnt++;
	} else {
		cnt = 0;
	}

	if (hd->typeflag != LONGLINKTYPE && hd->typeflag != LONGNAMETYPE) {
		arcn->nlen = cnt + expandname(dest, sizeof(arcn->name) - cnt,
		    &gnu_name_string, hd->name, sizeof(hd->name));
		arcn->ln_nlen = expandname(arcn->ln_name, sizeof(arcn->ln_name),
		    &gnu_link_string, hd->linkname, sizeof(hd->linkname));
	}

	/*
	 * follow the spec to the letter. we should only have mode bits, strip
	 * off all other crud we may be passed.
	 */
	arcn->sb.st_mode = (mode_t)(asc_ul(hd->mode, sizeof(hd->mode), OCT) &
	    0xfff);
	arcn->sb.st_size = (off_t)asc_ot(hd->size, sizeof(hd->size), OCT);
	arcn->sb.st_mtime = (time_t)asc_ul(hd->mtime, sizeof(hd->mtime), OCT);
	arcn->sb.st_ctime = arcn->sb.st_atime = arcn->sb.st_mtime;

	/*
	 * If we can find the ascii names for gname and uname in the password
	 * and group files we will use the uid's and gid they bind. Otherwise
	 * we use the uid and gid values stored in the header. (This is what
	 * the posix spec wants).
	 */
	hd->gname[sizeof(hd->gname) - 1] = '\0';
	if ((anonarch & ANON_NUMID) ||
	    (gid_name(hd->gname, &(arcn->sb.st_gid)) < 0))
		arcn->sb.st_gid = (gid_t)asc_ul(hd->gid, sizeof(hd->gid), OCT);
	hd->uname[sizeof(hd->uname) - 1] = '\0';
	if ((anonarch & ANON_NUMID) ||
	    (uid_name(hd->uname, &(arcn->sb.st_uid)) < 0))
		arcn->sb.st_uid = (uid_t)asc_ul(hd->uid, sizeof(hd->uid), OCT);

	/*
	 * set the defaults, these may be changed depending on the file type
	 */
	arcn->pad = 0;
	arcn->skip = 0;
	arcn->sb.st_rdev = (dev_t)0;

	/*
	 * set the mode and PAX type according to the typeflag in the header
	 */
	switch (hd->typeflag) {
	case FIFOTYPE:
		arcn->type = PAX_FIF;
		arcn->sb.st_mode |= S_IFIFO;
		break;
	case DIRTYPE:
		arcn->type = PAX_DIR;
		arcn->sb.st_mode |= S_IFDIR;
		arcn->sb.st_nlink = 2;

		/*
		 * Some programs that create ustar archives append a '/'
		 * to the pathname for directories. This clearly violates
		 * ustar specs, but we will silently strip it off anyway.
		 */
		if (arcn->name[arcn->nlen - 1] == '/')
			arcn->name[--arcn->nlen] = '\0';
		break;
	case BLKTYPE:
	case CHRTYPE:
		/*
		 * this type requires the rdev field to be set.
		 */
		if (hd->typeflag == BLKTYPE) {
			arcn->type = PAX_BLK;
			arcn->sb.st_mode |= S_IFBLK;
		} else {
			arcn->type = PAX_CHR;
			arcn->sb.st_mode |= S_IFCHR;
		}
		devmajor = (dev_t)asc_ul(hd->devmajor,sizeof(hd->devmajor),OCT);
		devminor = (dev_t)asc_ul(hd->devminor,sizeof(hd->devminor),OCT);
		arcn->sb.st_rdev = TODEV(devmajor, devminor);
		break;
	case SYMTYPE:
	case LNKTYPE:
		if (hd->typeflag == SYMTYPE) {
			arcn->type = PAX_SLK;
			arcn->sb.st_mode |= S_IFLNK;
		} else {
			arcn->type = PAX_HLK;
			/*
			 * so printing looks better
			 */
			arcn->sb.st_mode |= S_IFREG;
			arcn->sb.st_nlink = 2;
		}
		break;
	case LONGLINKTYPE:
	case LONGNAMETYPE:
		/*
		 * GNU long link/file; we tag these here and let the
		 * pax internals deal with it -- too ugly otherwise.
		 */
		arcn->type =
		    hd->typeflag == LONGLINKTYPE ? PAX_GLL : PAX_GLF;
		arcn->pad = TAR_PAD(arcn->sb.st_size);
		arcn->skip = arcn->sb.st_size;
		break;
	case CONTTYPE:
	case AREGTYPE:
	case REGTYPE:
	default:
		/*
		 * these types have file data that follows. Set the skip and
		 * pad fields.
		 */
		arcn->type = PAX_REG;
		arcn->pad = TAR_PAD(arcn->sb.st_size);
		arcn->skip = arcn->sb.st_size;
		arcn->sb.st_mode |= S_IFREG;
		break;
	}
	return(0);
}

/*
 * ustar_wr()
 *	write a ustar header for the file specified in the ARCHD to the archive
 *	Have to check for file types that cannot be stored and file names that
 *	are too long. Be careful of the term (last arg) to ul_oct, we only use
 *	'\0' for the termination character (this is different than picky tar)
 *	ASSUMED: space after header in header block is zero filled
 * Return:
 *	0 if file has data to be written after the header, 1 if file has NO
 *	data to write after the header, -1 if archive write failed
 */

int
ustar_wr(ARCHD *arcn)
{
	HD_USTAR *hd;
	char *pt;
	char hdblk[sizeof(HD_USTAR)];

	u_long t_uid, t_gid, t_mtime;

	anonarch_init();

	/*
	 * check for those filesystem types ustar cannot store
	 */
	if (arcn->type == PAX_SCK) {
		paxwarn(1, "ustar cannot archive a socket %s", arcn->org_name);
		return(1);
	}

	/*
	 * check the length of the linkname
	 */
	if (((arcn->type == PAX_SLK) || (arcn->type == PAX_HLK) ||
	    (arcn->type == PAX_HRG)) &&
	    ((size_t)arcn->ln_nlen > sizeof(hd->linkname))) {
		paxwarn(1, "Link name too long for ustar %s", arcn->ln_name);
		return(1);
	}

	/*
	 * if -M gslash: append a slash if directory
	 */
	if ((anonarch & ANON_DIRSLASH) && arcn->type == PAX_DIR &&
	    (size_t)arcn->nlen < (sizeof(arcn->name) - 1)) {
		arcn->name[arcn->nlen++] = '/';
		arcn->name[arcn->nlen] = '\0';
	}

	/*
	 * split the path name into prefix and name fields (if needed). if
	 * pt != arcn->name, the name has to be split
	 */
	if ((pt = name_split(arcn->name, arcn->nlen)) == NULL) {
		paxwarn(1, "File name too long for ustar %s", arcn->name);
		return(1);
	}

	/*
	 * zero out the header so we don't have to worry about zero fill below
	 */
	memset(hdblk, 0, sizeof(hdblk));
	hd = (HD_USTAR *)hdblk;
	arcn->pad = 0L;

	/*
	 * split the name, or zero out the prefix
	 */
	if (pt != arcn->name) {
		/*
		 * name was split, pt points at the / where the split is to
		 * occur, we remove the / and copy the first part to the prefix
		 */
		*pt = '\0';
		fieldcpy(hd->prefix, sizeof(hd->prefix), arcn->name,
		    sizeof(arcn->name));
		*pt++ = '/';
	}

	/*
	 * copy the name part. this may be the whole path or the part after
	 * the prefix
	 */
	fieldcpy(hd->name, sizeof(hd->name), pt,
	    sizeof(arcn->name) - (pt - arcn->name));

	t_uid   = (anonarch & ANON_UIDGID) ? 0UL : (u_long)arcn->sb.st_uid;
	t_gid   = (anonarch & ANON_UIDGID) ? 0UL : (u_long)arcn->sb.st_gid;
	t_mtime = (anonarch & ANON_MTIME) ? 0UL : (u_long)(u_int)arcn->sb.st_mtime;

	/*
	 * set the fields in the header that are type dependent
	 */
	switch (arcn->type) {
	case PAX_DIR:
		hd->typeflag = DIRTYPE;
		if (ul_oct((u_long)0L, hd->size, sizeof(hd->size), 3))
			goto out;
		break;
	case PAX_CHR:
	case PAX_BLK:
		if (arcn->type == PAX_CHR)
			hd->typeflag = CHRTYPE;
		else
			hd->typeflag = BLKTYPE;
		if (ul_oct((u_long)MAJOR(arcn->sb.st_rdev), hd->devmajor,
		   sizeof(hd->devmajor), 3) ||
		   ul_oct((u_long)MINOR(arcn->sb.st_rdev), hd->devminor,
		   sizeof(hd->devminor), 3) ||
		   ul_oct((u_long)0L, hd->size, sizeof(hd->size), 3))
			goto out;
		break;
	case PAX_FIF:
		hd->typeflag = FIFOTYPE;
		if (ul_oct((u_long)0L, hd->size, sizeof(hd->size), 3))
			goto out;
		break;
	case PAX_SLK:
	case PAX_HLK:
	case PAX_HRG:
		if (arcn->type == PAX_SLK)
			hd->typeflag = SYMTYPE;
		else
			hd->typeflag = LNKTYPE;
		fieldcpy(hd->linkname, sizeof(hd->linkname), arcn->ln_name,
		    sizeof(arcn->ln_name));
		if (ul_oct((u_long)0L, hd->size, sizeof(hd->size), 3))
			goto out;
		break;
	case PAX_REG:
	case PAX_CTG:
	default:
		/*
		 * file data with this type, set the padding
		 */
		if (arcn->type == PAX_CTG)
			hd->typeflag = CONTTYPE;
		else
			hd->typeflag = REGTYPE;
		arcn->pad = TAR_PAD(arcn->sb.st_size);
		if (ot_oct(arcn->sb.st_size, hd->size, sizeof(hd->size), 3)) {
			paxwarn(1,"File is too long for ustar %s",arcn->org_name);
			return(1);
		}
		break;
	}

	strncpy(hd->magic, TMAGIC, TMAGLEN);
	strncpy(hd->version, TVERSION, TVERSLEN);

	/*
	 * set the remaining fields. Some versions want all 16 bits of mode
	 * we better humor them (they really do not meet spec though)....
	 */
	if (ul_oct(t_uid, hd->uid, sizeof(hd->uid), 3)) {
		if (uid_nobody == 0) {
			if (uid_name("nobody", &uid_nobody) == -1)
				goto out;
		}
		if (uid_warn != t_uid) {
			uid_warn = t_uid;
			paxwarn(1,
			    "ustar header field is too small for uid %lu, "
			    "using nobody", t_uid);
		}
		if (ul_oct((u_long)uid_nobody, hd->uid, sizeof(hd->uid), 3))
			goto out;
	}
	if (ul_oct(t_gid, hd->gid, sizeof(hd->gid), 3)) {
		if (gid_nobody == 0) {
			if (gid_name("nobody", &gid_nobody) == -1)
				goto out;
		}
		if (gid_warn != t_gid) {
			gid_warn = t_gid;
			paxwarn(1,
			    "ustar header field is too small for gid %lu, "
			    "using nobody", t_gid);
		}
		if (ul_oct((u_long)gid_nobody, hd->gid, sizeof(hd->gid), 3))
			goto out;
	}
	if (ul_oct((u_long)arcn->sb.st_mode, hd->mode, sizeof(hd->mode), 3) ||
	    ul_oct(t_mtime,hd->mtime,sizeof(hd->mtime),3))
		goto out;
#define name_id(x) ((anonarch & ANON_NUMID) ? "" : (const char *)(x))
	strncpy(hd->uname, name_id(name_uid(t_uid, 0)), sizeof(hd->uname));
	strncpy(hd->gname, name_id(name_gid(t_gid, 0)), sizeof(hd->gname));
#undef name_id

	/*
	 * calculate and store the checksum write the header to the archive
	 * return 0 tells the caller to now write the file data, 1 says no data
	 * needs to be written
	 */
	if (ul_oct(tar_chksm(hdblk, sizeof(HD_USTAR)), hd->chksum,
	   sizeof(hd->chksum), 3))
		goto out;

	if (anonarch & ANON_DEBUG) {
		tar_dbgfld(NULL, NULL, 0);
		tar_dbgfld("writing name '", hd->name, TNMSZ);
		tar_dbgfld("' mode ", hd->mode, 8);
		tar_dbgfld(" uid ", hd->uid, 8);
		tar_dbgfld(" (", hd->uname, 32);
		tar_dbgfld(") gid ", hd->gid, 8);
		tar_dbgfld(" (", hd->gname, 32);
		tar_dbgfld(") size ", hd->size, 12);
		tar_dbgfld(" mtime ", hd->mtime, 12);
		tar_dbgfld(" type ", &(hd->typeflag), 1);
		tar_dbgfld(" linked to '", hd->linkname, TNMSZ);
		tar_dbgfld("' magic '", hd->magic, TMAGLEN);
		tar_dbgfld("' v", hd->version, TVERSLEN);
		tar_dbgfld(" device '", hd->devmajor, 8);
		tar_dbgfld(":", hd->devminor, 8);
		tar_dbgfld("' prefix '", hd->prefix, TPFSZ);
		tar_dbgfld("' checksum ", hd->chksum, CHK_LEN);
		tar_dbgfld(NULL, NULL, 1);
	}

	if (wr_rdbuf(hdblk, sizeof(HD_USTAR)) < 0)
		return(-1);
	if (wr_skip((off_t)(BLKMULT - sizeof(HD_USTAR))) < 0)
		return(-1);
	if ((arcn->type == PAX_CTG) || (arcn->type == PAX_REG))
		return(0);
	return(1);

 out:
	/*
	 * header field is out of range
	 */
	paxwarn(1, "ustar header field is too small for %s", arcn->org_name);
	return(1);
}

/*
 * name_split()
 *	see if the name has to be split for storage in a ustar header. We try
 *	to fit the entire name in the name field without splitting if we can.
 *	The split point is always at a /
 * Return
 *	character pointer to split point (always the / that is to be removed
 *	if the split is not needed, the points is set to the start of the file
 *	name (it would violate the spec to split there). A NULL is returned if
 *	the file name is too long
 */

static char *
name_split(char *name, int len)
{
	char *start;

	/*
	 * check to see if the file name is small enough to fit in the name
	 * field. if so just return a pointer to the name.
	 * The strings can fill the complete name and prefix fields
	 * without a NUL terminator.
	 */
	if (len <= TNMSZ)
		return(name);
	if (len > (TPFSZ + TNMSZ + 1))
		return(NULL);

	/*
	 * we start looking at the biggest sized piece that fits in the name
	 * field. We walk forward looking for a slash to split at. The idea is
	 * to find the biggest piece to fit in the name field (or the smallest
	 * prefix we can find) (the -1 is correct the biggest piece would
	 * include the slash between the two parts that gets thrown away)
	 */
	start = name + len - TNMSZ - 1;

	/*
	 * the prefix may not be empty, so skip the first character when
	 * trying to split a path of exactly TNMSZ+1 characters.
	 * NOTE: This means the ustar format can't store /str if
	 * str contains no slashes and the length of str == TNMSZ
	 */
	if (start == name)
		++start;

	while ((*start != '\0') && (*start != '/'))
		++start;

	/*
	 * if we hit the end of the string, this name cannot be split, so we
	 * cannot store this file.
	 */
	if (*start == '\0')
		return(NULL);

	/*
	 * the split point isn't valid if it results in a prefix
	 * longer than TPFSZ
	 */
	if ((start - name) > TPFSZ)
		return(NULL);

	/*
	 * ok have a split point, return it to the caller
	 */
	return(start);
}

static size_t
expandname(char *buf, size_t len, char **gnu_name, const char *name,
    size_t limit)
{
	size_t nlen;

	if (*gnu_name) {
		/* *gnu_name is NUL terminated */
		if ((nlen = strlcpy(buf, *gnu_name, len)) >= len)
			nlen = len - 1;
		free(*gnu_name);
		*gnu_name = NULL;
	} else
		nlen = fieldcpy(buf, len, name, limit);
	return(nlen);
}

static void
tar_dbgfld(const char *pfx, const char *sp, size_t len)
{
	static char fbuf[256];
	char tbuf[256], *s;

	if ((pfx == NULL) || (sp == NULL)) {
		if ((pfx == NULL) && (sp == NULL)) {
			if (len == 0) {
				*fbuf = 0;
			} else {
				paxwarn(0, "%s", fbuf);
			}
		} else
			paxwarn(0, "tar_dbgfld: wrong call");
		return;
	}

	strlcat(fbuf, pfx, sizeof (fbuf));

	if (len == 0)
		return;

	if (len > (sizeof (tbuf) - 1))
		len = sizeof (tbuf) - 1;

	memmove(s = tbuf, sp, len);
	tbuf[len] = 0;
	while (*s == ' ')
		++s;
	while (s[strlen(s) - 1] == ' ')
		s[strlen(s) - 1] = 0;

	strlcat(fbuf, tbuf, sizeof (fbuf));
}
