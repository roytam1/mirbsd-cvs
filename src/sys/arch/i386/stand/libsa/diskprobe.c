/**	$MirOS: src/sys/arch/i386/stand/libsa/diskprobe.c,v 1.19 2009/02/01 14:38:41 tg Exp $ */
/*	$OpenBSD: diskprobe.c,v 1.29 2007/06/18 22:11:20 krw Exp $	*/

/*
 * Copyright (c) 1997 Tobias Weingartner
 * Copyright (c) 2002, 2003, 2009, 2012
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

/* We don't want the disk type names from disklabel.h */
#undef DKTYPENAMES

#include <sys/param.h>
#include <sys/queue.h>
#include <sys/reboot.h>
#include <sys/disklabel.h>
#include <stand/boot/bootarg.h>
#include <machine/biosvar.h>
#include <zlib.h>
#include "disk.h"
#include "biosdev.h"
#include "libsa.h"

#define MAX_CKSUMLEN MAXBSIZE / DEV_BSIZE	/* Max # of blks to cksum */

/* Local Prototypes */
static int disksum(int);
static void hardprobe_one(int);

/* List of disk devices we found/probed */
struct disklist_lh disklist;

/* Pointer to boot device */
struct diskinfo *bootdev_dip = NULL;

/* Pointer to original boot device */
struct diskinfo *start_dip = NULL;

extern int debug;

/* Probe for all BIOS floppies */
static void
floppyprobe(void)
{
	struct diskinfo *dip;
	int i;

	/* Floppies */
	for (i = 0; i < 4; i++) {
		dip = alloc(sizeof(struct diskinfo));
		bzero(dip, sizeof(*dip));

		if (bios_getdiskinfo(i, &dip->bios_info)) {
#ifdef BIOS_DEBUG
			if (debug)
				printf(" <!fd%u>", i);
#endif
			free(dip, 0);
			break;
		}

		if (!start_dip && i386_biosdev == i)
			start_dip = dip;

		dip->name[0] = 'f';
		dip->name[1] = 'd';
		dip->name[2] = '0' + i;
		dip->name[3] = '\0';
		printf(" %s", dip->name);

		/* Fill out best we can - (fd?) */
		dip->bios_info.bsd_dev = MAKEBOOTDEV(2, 0, 0, i, RAW_PART);

		/*
		 * Delay reading the disklabel until we're sure we want
		 * to boot from the floppy. Doing this avoids a delay
		 * (sometimes very long) when trying to read the label
		 * and the drive is unplugged.
		 */
		dip->bios_info.flags |= BDI_BADLABEL;

		/* Add to queue of disks */
		TAILQ_INSERT_TAIL(&disklist, dip, list);
	}
}

/* Probe for all BIOS hard disks */
static void
hardprobe(void)
{
	int i;

	if (i386_biosdev & 0x80)
		hardprobe_one(i386_biosdev);
	for (i = 0x80; i < 0x88; i++)
		if (i != i386_biosdev)
			hardprobe_one(i);
}

static void
hardprobe_one(int i)
{
	static unsigned int cddv = 0, ide = 0, scsi = 0;
	struct diskinfo *dip;
	u_int bsdunit, type;

	dip = alloc(sizeof(struct diskinfo));
	bzero(dip, sizeof(*dip));

	if (bios_getdiskinfo(i, &dip->bios_info)) {
#ifdef BIOS_DEBUG
		if (debug)
			printf(" <!hd%u>", i&0x7f);
#endif
		free(dip, 0);
		return;
	}

	if (!start_dip && i386_biosdev == i)
		start_dip = dip;

	dip->name[0] = 'h';
	dip->name[1] = 'd';
	dip->name[2] = '0' + (i & 0x7F);
	dip->name[3] = '\0';
	if (dip->bios_info.flags & BDI_EL_TORITO) {
		dip->name[0] = 'c';
		dip->name[2] = '0' + cddv++;
	}
	printf(" %s%s", dip->name, dip->bios_info.flags & BDI_LBA ? "+" : "");

	/* Try to find the label, to figure out device type */
	if ((bios_getdisklabel(&dip->bios_info, &dip->disklabel)) ) {
		if (dip->bios_info.flags & BDI_EL_TORITO) {
			bsdunit = dip->name[2] - '0';
			type = 6;	/* CD-ROM */
		} else {
			printf("*");
			bsdunit = ide++;
			type = 0;	/* XXX let it be IDE */
		}
	} else {
		/* Best guess */
		switch (dip->disklabel.d_type) {
		case DTYPE_SCSI:
			type = 4;
			bsdunit = scsi++;
			dip->bios_info.flags |= BDI_GOODLABEL;
			break;

		case DTYPE_ESDI:
		case DTYPE_ST506:
			type = 0;
			bsdunit = ide++;
			dip->bios_info.flags |= BDI_GOODLABEL;
			break;

		case DTYPE_ATAPI:
			bsdunit = dip->name[2] - '0';
			type = 6;	/* CD-ROM */
			dip->bios_info.flags |= BDI_GOODLABEL;
			break;

		default:
			dip->bios_info.flags |= BDI_BADLABEL;
			type = 0;	/* XXX Suggest IDE */
			bsdunit = ide++;
		}
	}

	dip->bios_info.checksum = 0; /* just in case */
	/* Fill out best we can */
	dip->bios_info.bsd_dev =
	    MAKEBOOTDEV(type, 0, 0, bsdunit, RAW_PART);

	/* Add to queue of disks */
	TAILQ_INSERT_TAIL(&disklist, dip, list);
}


/* Probe for all BIOS supported disks */
u_int32_t bios_cksumlen;
void
diskprobe(void)
{
	struct diskinfo *dip;
	int i;

	/* These get passed to kernel */
	bios_diskinfo_t *bios_diskinfo;

	/* Do probes */
	floppyprobe();
#ifdef BIOS_DEBUG
	if (debug)
		printf(";");
#endif
	hardprobe();

	if (!start_dip)
		start_dip = TAILQ_FIRST(&disklist);

	/* Checksumming of hard disks */
	for (i = 0; disksum(i++) && i < MAX_CKSUMLEN; )
		;
	bios_cksumlen = i;

	/* Get space for passing bios_diskinfo stuff to kernel */
	for (i = 0, dip = TAILQ_FIRST(&disklist); dip;
	    dip = TAILQ_NEXT(dip, list))
		i++;
	bios_diskinfo = alloc(++i * sizeof(bios_diskinfo_t));

	/* Copy out the bios_diskinfo stuff */
	for (i = 0, dip = TAILQ_FIRST(&disklist); dip;
	    dip = TAILQ_NEXT(dip, list))
		bios_diskinfo[i++] = dip->bios_info;

	bios_diskinfo[i++].bios_number = -1;
	/* Register for kernel use */
	addbootarg(BOOTARG_CKSUMLEN, sizeof(u_int32_t), &bios_cksumlen);
	addbootarg(BOOTARG_DISKINFO, i * sizeof(bios_diskinfo_t),
	    bios_diskinfo);
}

void
dump_diskinfo(void)
{
	struct diskinfo *dip;

#ifndef SMALL_BOOT
	printf("Disk\tBIOS#\tType\tCyls\tHeads\tSecs\tFlags\tChecksum\n");
#endif
	for (dip = TAILQ_FIRST(&disklist); dip; dip = TAILQ_NEXT(dip, list)) {
		bios_diskinfo_t *bdi = &dip->bios_info;

		if (bdi->flags & BDI_NOTADISK) {
			printf("%s\tnone\n", dip->name);
			continue;
		}
		printf("%s\t0x%X\t%s\t%d\t%d\t%d\t0x%X\t0x%X\n",
		    dip->name, bdi->bios_number,
		    (bdi->flags & BDI_BADLABEL) ? "*none*" : "label",
		    bdi->bios_cylinders, bdi->bios_heads, bdi->bios_sectors,
		    bdi->flags, bdi->checksum);
	}
}

/*
 * Checksum one more block on all harddrives
 *
 * Use the adler32() function from libz,
 * as it is quick, small, and available.
 */
int
disksum(int blk)
{
	struct diskinfo *dip, *dip2;
	int st, reprobe = 0;
	char *buf;

	buf = alloc(DEV_BSIZE);
	for (dip = TAILQ_FIRST(&disklist); dip; dip = TAILQ_NEXT(dip, list)) {
		bios_diskinfo_t *bdi = &dip->bios_info;

		/* Skip this disk if it is not a HD or has had an I/O error */
		if (!(bdi->bios_number & 0x80) ||
		    bdi->flags & (BDI_INVALID | BDI_NOTADISK))
			continue;

		/* Adler32 checksum */
		st = biosd_io(F_READ, bdi, blk, 1, buf);
		if (st) {
			bdi->flags |= BDI_INVALID;
			continue;
		}
		bdi->checksum = adler32(bdi->checksum, buf, DEV_BSIZE);

		for (dip2 = TAILQ_FIRST(&disklist); dip2 != dip;
				dip2 = TAILQ_NEXT(dip2, list)) {
			bios_diskinfo_t *bd = &dip2->bios_info;
			if ((bd->bios_number & 0x80) &&
			    !(bd->flags & (BDI_INVALID | BDI_NOTADISK)) &&
			    bdi->checksum == bd->checksum)
				reprobe = 1;
		}
	}
	free(buf, DEV_BSIZE);

	return reprobe;
}
