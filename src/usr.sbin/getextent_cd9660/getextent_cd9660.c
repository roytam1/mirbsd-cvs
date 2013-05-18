/*-
 * Copyright (c) 2008
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

#include <sys/param.h>
#include <sys/queue.h>
#include <isofs/cd9660/iso.h>
#include <ctype.h>
#include <err.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cd9660_eltorito.h"

#ifdef __RCSID
__RCSID("$MirOS: src/usr.sbin/getextent_cd9660/getextent_cd9660.c,v 1.4 2008/08/06 00:18:12 tg Exp $");
#endif

#ifndef __dead
#define __dead		/* nothing */
#endif

uint8_t bp[2048];
char *buf = bp;
#define vd ((struct iso_primary_descriptor *)bp)

const char **fns = NULL;
bool show_beg = false;
bool show_end = false;
bool show_name = false;
bool show_size = false;
char *isoname = NULL;
int fd;

__dead void usage(void);
void getblk(daddr_t, size_t);
void gotdir(struct iso_directory_record *);
void gotfile(const char *, u_int, u_int);
char *strdup_uc(const char *);

int
main(int argc, char *argv[])
{
	int i;
	daddr_t bno;
	size_t dsize;
	struct iso_directory_record *dp;
	char *cp = NULL;

	while ((i = getopt(argc, argv, "bef:sn")) != -1)
		switch (i) {
		case 'b':
			show_beg = true;
			break;
		case 'e':
			show_end = true;
			break;
		case 'f':
			isoname = strdup(optarg);
			break;
		case 'n':
			show_name = true;
			break;
		case 's':
			show_size = true;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (!show_beg && !show_end && !show_size && !show_name)
		show_beg = show_end = show_name = true;

	if (isoname == NULL)
		usage();

	if (argc) {
		if ((fns = calloc(argc + 1, sizeof (char *))) == NULL)
			err(1, "out of memory");
		for (i = 0; i < argc; ++i)
			fns[i] = strdup_uc(argv[i]);
		fns[argc] = NULL;
	}

	if ((fd = open(isoname, O_RDONLY)) < 0)
		err(1, "cannot open %s for reading", isoname);

	bno = 16;
 loadvd:
	getblk(bno++, 1);
	if (bcmp(vd->id, ISO_STANDARD_ID, sizeof (vd->id)))
		errx(1, "invalid descriptor found");
	switch (isonum_711(vd->type)) {
	case ISO_VD_END:
		goto endvd;
	case 0: {
		boot_volume_descriptor bv;
		boot_catalog_initial_entry ie;

		memcpy(&bv, buf, sizeof (bv));
		i = isonum_731(bv.boot_catalog_pointer);
		gotfile("$BootCatalog$", i, 2048);
		getblk(i, 1);
		memcpy(&ie, buf + 32, sizeof (ie));
		if (isonum_711(ie.boot_indicator) != ET_BOOTABLE)
			break;
		gotfile("$BootImage$", isonum_731(ie.load_rba),
		    isonum_721(ie.sector_count) << 9);
		break;
	}
	case ISO_VD_PRIMARY:
		if (isonum_723(vd->logical_block_size) != 2048)
			errx(1, "no support for blocks of size %d",
			    (int)isonum_723(vd->logical_block_size));

		dp = (struct iso_directory_record *)vd->root_directory_record;
		i = isonum_733(dp->extent);
		dsize = (isonum_733(dp->size) + 2047) >> 11;
		if ((buf = cp = calloc(dsize, 2048)) == NULL)
			err(1, "out of memory");
		getblk(i, dsize);
		buf = bp;
		dsize = isonum_733(dp->size);
		break;
	}
	goto loadvd;

 endvd:
	if ((buf = cp) == NULL)
		errx(1, "no valid descriptor found");
	cp += dsize;

 dir_loop:
	if (buf >= cp)
		goto dir_end;
	dp = (struct iso_directory_record *)buf;
	if (!isonum_711(dp->length)) {
		buf++;
		goto dir_loop;
	}
	gotdir(dp);
	buf += isonum_711(dp->length);
	goto dir_loop;

 dir_end:
	return (0);
}

void
gotdir(struct iso_directory_record *dp)
{
	char *cp, *name;
	size_t namelen;

	/* regular file? */
	if (dp->flags[0] & 6)
		return;

	if (!(namelen = isonum_711(dp->name_len)))
		return;
	if ((name = malloc(namelen + 1)) == NULL)
		err(1, "out of memory");
	memcpy(name, dp->name, namelen);
	name[namelen] = '\0';
	if (isdigit(*(cp = name + strlen(name) - 1))) {
		while (isdigit(*cp))
			--cp;
		if (cp < name)
			return;
		if (*cp == ';')
			*cp-- = '\0';
	}
	if (*(cp = name + strlen(name) - 1) == '.')
		*cp = '\0';

	gotfile(name, isonum_733(dp->extent), isonum_733(dp->size));
}

void
gotfile(const char *name, u_int extent, u_int size)
{
	bool sp = false;

	if (fns) {
		char *uc;
		const char **fp = fns;

		uc = strdup_uc(name);
		while (*fp && strcmp(uc, *fp))
			++fp;
		if (*fp == NULL)
			return;
		free(uc);
	}

	if (show_beg) {
		printf("%u", extent);
		sp = true;
	}

	if (show_end) {
		if (sp)
			putchar(' ');
		printf("%u", ((extent << 11) + size - 1) >> 11);
		sp = true;
	}

	if (show_size) {
		if (sp)
			putchar(' ');
		printf("%u", size);
		sp = true;
	}

	if (show_name) {
		if (sp)
			putchar(' ');
		printf("%s", name);
	}

	putchar('\n');
}

#ifndef __GNUC__
#undef toupper
#endif
char *
strdup_uc(const char *s)
{
	char *d, *cp;

	if ((d = cp = malloc(strlen(s) + 1)) == NULL)
		err(1, "out of memory");

	while ((*cp++ = toupper(*s++)))
		;
	return (d);
}

void
usage(void)
{
	extern const char *__progname;

	fprintf(stderr, "usage: %s [-besn] -f iso [name ...]\n", __progname);
	exit(1);
}

void
getblk(daddr_t blk, size_t num)
{
	if (lseek(fd, (off_t)blk << 11, SEEK_SET) == -1)
		err(1, "cannot seek");
	num <<= 11;
	if ((size_t)read(fd, buf, num) != num)
		err(1, "cannot read %zu bytes", num);
}
