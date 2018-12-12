/*-
 * Copyright © 2011, 2016, 2017
 *	mirabilos <m@mirbsd.org>
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

#include <sys/types.h>
#if HAVE_BOTH_TIME_H
#include <sys/time.h>
#include <time.h>
#elif HAVE_SYS_TIME_H
#include <sys/time.h>
#elif HAVE_TIME_H
#include <time.h>
#endif
#include <sys/stat.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if HAVE_STRINGS_H
#include <strings.h>
#endif
#include <unistd.h>

#include "pax.h"
#include "extern.h"

__RCSID("$MirOS: src/bin/pax/ar.c,v 1.9 2017/10/21 19:19:38 tg Exp $");

/*
 * Routines for reading and writing Unix Archiver format libraries
 */

static /*const*/ char magic[8] = {
	0x21, 0x3C, 0x61, 0x72, 0x63, 0x68, 0x3E, 0x0A
};

/****************************************************

Libraries created by the Unix Archiver and compatible
with the DEB file format consist of an initial eight-
octet magic followed by a number of sections, per ar-
chive member, comprised of a header and a data part.

The magic is "<!arch>\n" (21 3C 61 72 63 68 3E 0A).

Each archive member section (header followed by data)
is aligned to a multiple of two octets. The magic and
member header are both of even size, so a padding oc-
tet "\n" (0Ah) can be appended after the data part of
that section; an archive always has an even length. A
header is 60 octets long and structured as follows:
	+0	char ar_name[16];
	+16	char ar_mtime[12];
	+28	char ar_uid[6];
	+34	char ar_gid[6];
	+40	char ar_mode[8];
	+48	char ar_size[10];
	+58	char ar_magic[2];

All header fields are left-justified and space-padded
at the end, if necessary. The composition for ar_name
will be described later. ar_mtime, ar_uid, ar_gid and
ar_size are the unsigned decimental representation of
the mtime as time_t, numeric user and group ID values
and the size of the data part, respectively. ar_mode,
on the other hand, is the octal representation of its
Unix file mode (permissions). ar_magic = { 60h, 0Ah }

Archive memeber filenames are basenames, i.e. they do
not contain a path.

If the filename is not longer than 16 octets and does
not contain a space, it is stored as ar_name directly
(although some implementations would trim the part of
the filename before a ".o" extension). Otherwise, the
ar_name field consists of the string "#1/" (23 31 2F)
followed by the length of the filename as decimal un-
signed integer (again space-padded); the APT archival
routines only support extended filenames of less than
300 octets. The actual filename is then stored as the
first part of the data part consequently incrementing
ar_size by its length. Since some versions of APT al-
so support the SYSV property of ending ar_name with a
slash "/" (2F), on encoding filenames containing them
should be written as extended filenames; on decoding,
a trailing slash in ar_name should be ignored. (Note,
SYSV does not encode filenames that contain spaces as
extended but BSD ar and APT truncate there then.)

There are no trailers; an archive file ends after its
last member section (including the padding).

****************************************************/

typedef struct {
	char ar_name[16];
	char ar_mtime[12];
	char ar_uid[6];
	char ar_gid[6];
	char ar_mode[8];
	char ar_size[10];
	char ar_magic[2];
} HD_AR;

/*
 * initialisation for ar write
 * returns 0 if ok, -1 otherwise
 */
int
uar_stwr(int is_app)
{
	return (is_app ? 0 : wr_rdbuf(magic, 8));
}

/*
 * check for ar magic
 * returns 0 if ok, -1 otherwise
 */
int
uar_ismagic(char *buf)
{
	return (memcmp(buf, magic, 8) ? -1 : 0);
}

/*
 * used during format identification, but we differ
 */
int
uar_id(char *buf __attribute__((__unused__)),
    int len __attribute__((__unused__)))
{
	errx(1, "internal error: %s should never have been called",
	    "uar_id");
}

/* internal parsing functions */
static uint64_t
uar_atoi64(const char *buf, size_t len)
{
	char c;
	uint64_t res = 0;

 loop:
	if (!len-- || (c = *buf++) < '0' || c > '9')
		return (res);
	res = (res * 10) + (c - '0');
	goto loop;
}

static uint32_t
uar_atoi32(const char *buf, size_t len)
{
	char c;
	uint32_t res = 0;

 loop:
	if (!len-- || (c = *buf++) < '0' || c > '9')
		return (res);
	res = (res * 10) + (c - '0');
	goto loop;
}

static uint32_t
uar_otoi32(const char *buf, size_t len)
{
	char c;
	uint32_t res = 0;

 loop:
	if (!len-- || (c = *buf++) < '0' || c > '7')
		return (res);
	res = (res << 3) | (c & 7);
	goto loop;
}

/*
 * parse header
 */
int
uar_rd(ARCHD *arcn, char *buf)
{
	HD_AR *h = (HD_AR *)buf;
	uint64_t i;

	if (h->ar_magic[0] != 0x60 || h->ar_magic[1] != 0x0A)
		return (-1);

	memset(arcn, 0, sizeof(*arcn));
	arcn->org_name = arcn->name;
	arcn->sb.st_nlink = 1;
	arcn->type = PAX_REG;

	arcn->sb.st_ctime = arcn->sb.st_atime = arcn->sb.st_mtime =
	    uar_atoi64(h->ar_mtime, sizeof(h->ar_mtime));
	arcn->sb.st_uid = uar_atoi32(h->ar_uid, sizeof(h->ar_uid));
	arcn->sb.st_gid = uar_atoi32(h->ar_gid, sizeof(h->ar_gid));
	arcn->sb.st_mode = uar_otoi32(h->ar_mode, sizeof(h->ar_mode)) |
	    S_IFREG;
	i = uar_atoi64(h->ar_size, sizeof(h->ar_size));
	arcn->pad = i & 1;

	if (h->ar_name[0] == 0x23 &&
	    h->ar_name[1] == 0x31 &&
	    h->ar_name[2] == 0x2F) {
		arcn->nlen = uar_atoi32(&(h->ar_name[3]),
		    sizeof(h->ar_name) - 3);
		if (arcn->nlen < 0 || arcn->nlen > PAXPATHLEN)
			/*XXX just skip over this file */
			return (-1);
		if (rd_wrbuf(arcn->name, arcn->nlen) != arcn->nlen)
			return (-1);
		i -= arcn->nlen;
	} else {
		register char c;

		/*arcn->nlen = 0;*/
		while (arcn->nlen < (int)sizeof(h->ar_name)) {
			c = h->ar_name[arcn->nlen];
			if (c == ' ' || c == '/' || c == '\0')
				break;
			arcn->name[arcn->nlen++] = c;
		}
	}
	arcn->name[arcn->nlen] = '\0';
	arcn->sb.st_size = i;
	arcn->skip = i;
	return (0);
}

/* internal emission functions */
static char *
uar_itoa64(char *dst, uint64_t num)
{
	if (num >= 10)
		dst = uar_itoa64(dst, num / 10);
	*dst++ = '0' + (num % 10);
	return (dst);
}

static char *
uar_itoa32(char *dst, uint32_t num)
{
	if (num >= 10)
		dst = uar_itoa32(dst, num / 10);
	*dst++ = '0' + (num % 10);
	return (dst);
}

static char *
uar_itoo32(char *dst, uint32_t num)
{
	if (num & ~7)
		dst = uar_itoo32(dst, num >> 3);
	*dst++ = '0' | (num & 7);
	return (dst);
}

/*
 * write a header
 */
int
uar_wr(ARCHD *arcn)
{
	HD_AR h;
	u_long t_uid, t_gid;
	time_t t_mtime = 0;
	char *extname;
	size_t n;
	u_long t_mode[sizeof(arcn->sb.st_mode) <= sizeof(u_long) ? 1 : -1];

	anonarch_init();

	switch (arcn->type) {
	case PAX_CTG:
	case PAX_REG:
	case PAX_HRG:
		/* regular files, more or less */
		break;
	case PAX_DIR:
		/* directory, ignore silently */
		return (1);
	default:
		paxwarn(1, "ar can only archive regular files, which %s is not",
		    arcn->org_name);
		return (1);
	}

	/* trim trailing slashes */
	n = strlen(arcn->name) - 1;
	while (n && arcn->name[n] == '/')
		--n;
	arcn->name[++n] = '\0';
	/* find out basename */
	if ((extname = strrchr(arcn->name, '/')) == NULL)
		extname = arcn->name;
	else
		++extname;

	t_uid = (anonarch & ANON_UIDGID) ? 0UL : (u_long)arcn->sb.st_uid;
	t_gid = (anonarch & ANON_UIDGID) ? 0UL : (u_long)arcn->sb.st_gid;
	t_mode[0] = arcn->sb.st_mode;
	if (!(anonarch & ANON_MTIME))
		t_mtime = arcn->sb.st_mtime;

	if (sizeof(time_t) > 4 && t_mtime > (time_t)999999999999ULL) {
		paxwarn(1, "%s overflow for %s", "mtime", arcn->org_name);
		t_mtime = (time_t)999999999999ULL;
	}
	if (t_uid > 999999UL) {
		paxwarn(1, "%s overflow for %s", "uid", arcn->org_name);
		t_uid = 999999UL;
	}
	if (t_gid > 999999UL) {
		paxwarn(1, "%s overflow for %s", "gid", arcn->org_name);
		t_gid = 999999UL;
	}
	if (t_mode[0] > 077777777UL) {
		paxwarn(1, "%s overflow for %s", "mode", arcn->org_name);
		t_mode[0] &= 077777777UL;
	}
	if ((uint64_t)arcn->sb.st_size > ((uint64_t)9999999999ULL)) {
		paxwarn(1, "%s overflow for %s", "size", arcn->org_name);
		return (1);
	}

	if (anonarch & ANON_DEBUG)
		paxwarn(0, "writing mode %8lo user %ld:%ld "
		    "mtime %08lX name '%s'", t_mode[0],
		    t_uid, t_gid, (u_long)t_mtime, extname);

	memset(&h, ' ', sizeof(HD_AR));

	if ((n = strlen(extname)) <= sizeof(h.ar_name)) {
		while (n)
			if (extname[--n] == ' ')
				break;
		if (n == 0) {
			memcpy(h.ar_name, extname, strlen(extname));
			extname = NULL;
			goto got_name;
		}
	}
	n = strlen(extname);
	/* assert: n <= PAXPATHLEN <= 9999999999999 */
	h.ar_name[0] = 0x23;
	h.ar_name[1] = 0x31;
	h.ar_name[2] = 0x2F;
	uar_itoa32(&(h.ar_name[3]), n);
 got_name:
	uar_itoa64(h.ar_mtime, t_mtime);
	uar_itoa32(h.ar_uid, t_uid);
	uar_itoa32(h.ar_gid, t_gid);
	uar_itoo32(h.ar_mode, t_mode[0]);
	uar_itoa64(h.ar_size, arcn->sb.st_size +
	    (extname ? strlen(extname) : 0));
	h.ar_magic[0] = 0x60;
	h.ar_magic[1] = 0x0A;
	arcn->pad = (arcn->sb.st_size + (extname ? strlen(extname) : 0)) & 1;

	if (wr_rdbuf((void *)&h, sizeof(HD_AR)) < 0)
		return (-1);
	if (extname) {
		if (wr_rdbuf(extname, strlen(extname)) < 0)
			return (-1);
	}
	/* so let the data follow */
	return (0);
}

/*
 * return size of trailer
 */
off_t
uar_endrd(void)
{
	return (0);
}

/*
 * another artefact of paxtar integration
 */
int
uar_trail(ARCHD *ignore __attribute__((__unused__)),
    char *buf __attribute__((__unused__)),
    int in_resync __attribute__((__unused__)),
    int *cnt __attribute__((__unused__)))
{
	errx(1, "internal error: %s should never have been called",
	    "uar_trail");
}
