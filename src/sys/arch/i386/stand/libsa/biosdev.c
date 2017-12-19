/**	$MirOS: src/sys/arch/i386/stand/libsa/biosdev.c,v 1.47 2012/12/23 19:19:48 tg Exp $ */
/*	$OpenBSD: biosdev.c,v 1.74 2008/06/25 15:32:18 reyk Exp $	*/

/*
 * Copyright (c) 1996 Michael Shalayeff
 * Copyright (c) 2003 Tobias Weingartner
 * Copyright (c) 2002, 2003, 2004, 2005, 2008, 2009, 2012
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

#include <sys/param.h>
#include <sys/reboot.h>
#include <sys/disklabel.h>
#include <machine/tss.h>
#include <machine/biosvar.h>
#include <lib/libsa/saerrno.h>
#include <lib/libsa/ustar.h>
#include <isofs/cd9660/iso.h>
#include "disk.h"
#include "debug.h"
#include "libsa.h"
#include "biosdev.h"

const char *biosdisk_err(u_int);
int biosdisk_errno(u_int);

extern int biosdev_lbaprobe(int drive);
extern int biosdev_CHS(int ah, int dev, int cyl, int head, int sec, int nsec);
extern int biosdev_LBA(int ah, int dev, u_int blk_lo, u_int blk_hi, int nsec);

extern int debug;
int i386_flag_oldbios = 0;

/*
 * reset disk system
 */
int
biosdreset(int dev)
{
	int rv;

	__asm __volatile (DOINT(0x13) "; setc %b0" : "=a" (rv)
	    : "0" (0), "d" (dev) : "%ecx", "cc");

	return ((rv & 0xff)? rv >> 8 : 0);
}

/*
 * Fill out a bios_diskinfo_t for this device.
 * Return 0 if all ok.
 * Return 1 if not ok.
 */
int
bios_getdiskinfo(int dev, bios_diskinfo_t *pdi)
{
	u_int rv;
	int lback;

	/* kernel interface, binary compatibility */
	pdi->old_bios_edd = -1;

	pdi->flags &= ~(BDI_LBA | BDI_EL_TORITO);
	lback = biosdev_lbaprobe(dev);

	/* Just reset, don't check return code */
	rv = biosdreset(dev);

	if (lback & 0x10) {
		pdi->bios_number = dev;
		/* CD-ROM, we don’t care what the BIOS says for CHS or LBA */
		pdi->bios_heads = 16;
		pdi->bios_cylinders = 16;
		pdi->bios_sectors = 32;
		/* http://www.mirbsd.org/permalinks/news_e20090126-tg.htm */
		pdi->flags |= BDI_LBA | BDI_EL_TORITO;
		pdi->old_bios_edd = (lback | 9) & 7;
		return (0);
	}

#ifdef BIOS_DEBUG
	if (debug)
		printf("getinfo: try #8, 0x%x, %p\n", dev, pdi);
#endif
	__asm __volatile (DOINT(0x13) "\n\t"
	    "setc %b0; movzbl %h1, %1\n\t"
	    "movzbl %%cl, %3; andb $0x3f, %b3\n\t"
	    "xchgb %%cl, %%ch; rolb $2, %%ch"
	    : "=a" (rv), "=d" (pdi->bios_heads),
	      "=c" (pdi->bios_cylinders),
	      "=b" (pdi->bios_sectors)
	    : "0" (0x0800), "1" (dev) : "cc");

#ifdef BIOS_DEBUG
	if (debug) {
		printf("getinfo: got #8\n");
		printf("disk 0x%x: %d,%d,%d\n", dev, pdi->bios_cylinders,
		    pdi->bios_heads, pdi->bios_sectors);
	}
#endif

	if (rv & 0xFF) {
		if ((lback & 0x09) != 0x09)
			return (1);
		printf("bios_getdiskinfo(%X): LBA but no CHS: %X\n", dev, lback);
		pdi->bios_heads = 15;
		pdi->bios_cylinders = 15;
		pdi->bios_sectors = 63;
	}

	/* Fix up info */
	pdi->bios_number = dev;
	pdi->bios_heads++;
	pdi->bios_cylinders &= 0x3ff;
	pdi->bios_cylinders++;

	if ((lback & 0x09) == 0x09) {
		pdi->flags |= BDI_LBA;
		pdi->old_bios_edd = lback & 7;
	} else if (pdi->bios_cylinders < 2 || pdi->bios_heads < 2 ||
	    pdi->bios_sectors < 1) {
#ifdef BIOS_DEBUG
		printf("sanity: c/h/s values insane: %d/%d/%d\n",
		    pdi->bios_cylinders, pdi->bios_heads, pdi->bios_sectors);
#endif
		return (1);
	}

	return (0);
}

/*
 * Read given sector, handling retry/errors/etc.
 */
int
biosd_io(int rw, bios_diskinfo_t *bd, daddr_t off, int nsect, void *buf)
{
	int rv, n, ssh = 0, i, spre = 0;
	volatile int c, h, s; /* fsck gcc, uninitialised it is not */

#ifndef SMALL_BOOT
	/* we do all I/O in 512 byte sectors, the El Torito BIOS doesn't */
	if (bd->flags & BDI_EL_TORITO) {
		ssh = 2;	/* sector shift */
		/* read only part of a CD sector */
		if (off & 3) {
			spre = off & 3;
			off -= spre;
			nsect += spre;
		}
		/* odd nsect does not matter, we read CDs one by one */
	}
#endif

 loop:
	n = (ssh || i386_flag_oldbios) ? 1 << ssh : MIN(nsect, 4096/512);
	if (!(bd->flags & BDI_LBA)) {
		/* note: BDI_EL_TORITO implies BDI_LBA, d/w about ssh here */
		btochs(off, c, h, s, bd->bios_heads, bd->bios_sectors);
		if (s + n >= bd->bios_sectors)
			n = bd->bios_sectors - s;
	}
	if ((buf || spre) && rw != F_READ)
		memmove(bounce_buf + spre * 512, buf ? buf : bounce_buf,
		    MIN(n - spre, nsect) * 512);
	/* try operation up to 5 times */
	rv = 1;
	i = 5;
	while (rv && i--) {
		if (bd->flags & BDI_LBA) {
#if 0
			printf(" trying biosdev_LBA(%X, %X, %d, %d, %d)",
			    rw == F_READ ? 0x42 : 0x43, bd->bios_number,
			    (int)((off >> ssh) & 0xFFFFFFFF),
			    (int)(sizeof (daddr_t) > 4 ?
			    (off >> ssh) >> 32 : 0), n >> ssh);
#endif
			rv = biosdev_LBA(rw == F_READ ? 0x42 : 0x43,
			    bd->bios_number, (off >> ssh) & 0xFFFFFFFF,
			    sizeof (daddr_t) > 4 ? (off >> ssh) >> 32 : 0,
			    n >> ssh);
		} else {
#if 0
			printf(" trying biosdev_CHS(%X, %X, %d, %d, %d, %d)",
			    rw == F_READ ? 0x02 : 0x03, bd->bios_number,
			    c, h, s, n);
#endif
			rv = biosdev_CHS(rw == F_READ ? 0x02 : 0x03,
			    bd->bios_number, c, h, s, n);
		}
/*		printf(" => %X\n", rv);	*/
		switch (rv) {
		case 0x11:	/* ECC corrected */
			rv = 0;
		case 0x00:	/* no errors */
			break;
		default:	/* all other errors */
#ifdef BIOS_DEBUG
			if (debug)
				printf("\nBIOS error 0x%X (%s)\n",
				    rv, biosdisk_err(rv));
#endif
			biosdreset(bd->bios_number);
			break;
		}
	}
#ifdef BIOS_DEBUG
	if (debug) {
		if (rv != 0)
			printf("=0x%x(%s)", rv, biosdisk_err(rv));
		putchar('\n');
	}
#endif
	if (rv)
		return (rv);
	if ((buf || spre) && rw == F_READ)
		memmove(buf ? buf : bounce_buf, bounce_buf + spre * 512,
		    MIN(n - spre, nsect) * 512);
	if ((nsect -= n) <= 0)
		return (0);
	if (!buf) {
#ifndef SMALL_BOOT
		printf("panic: cannot loop biosd_io on bounce_buf\n");
#endif
		return (0);
	}
	buf += (n - spre) * 512;
	off += n;
	spre = 0;
	goto loop;
}

/*
 * Try to read the bsd label on the given BIOS device
 */
const char *
bios_getdisklabel(bios_diskinfo_t *bd, struct disklabel *label)
{
	daddr_t off = 0;
	struct dos_mbr *mbr = (struct dos_mbr *)bounce_buf;
	int error, i;
	long mbrofs;

	/* Sanity check */
	if (bd->bios_heads == 0 || bd->bios_sectors == 0)
		return ("failed to read disklabel");

	/* MBR is a harddisk thing */
	if (bd->bios_number & 0x80) {
		/* Read MBR */
		mbrofs = DOSBBSECTOR;
 loop:
		error = biosd_io(F_READ, bd, mbrofs, 1, NULL);
		if (error)
			return (biosdisk_err(error));

		if (!memcmp((char *)mbr + offsetof(ustar_hdr_t, magic),
		    ustar_magic_version, sizeof(ustar_magic_version)))
			return "found ustar magic\n";

		/* check mbr signature */
		if (mbr->dmbr_sign != DOSMBR_SIGNATURE)
			return "bad MBR signature\n";

		/* extend all start offsets by mbrofs */
		for (i = 0; i < NDOSPART; i++)
			mbr->dmbr_parts[i].dp_start += mbrofs;

		/* Search for MirBSD partition */
		if (i386_userpt) for (i = 0; off == 0 && i < NDOSPART; i++)
			if (mbr->dmbr_parts[i].dp_typ == i386_userpt)
				off = i + 1;
		if (!off) for (i = 0; off == 0 && i < NDOSPART; i++)
			if (mbr->dmbr_parts[i].dp_typ == DOSPTYP_MIRBSD)
				off = i + 1;

		/* just in case */
		if (!off) for (i = 0; off == 0 && i < NDOSPART; i++)
			if (mbr->dmbr_parts[i].dp_typ == DOSPTYP_OPENBSD)
				off = i + 1;

		/* just in case */
		if (!off) for (i = 0; off == 0 && i < NDOSPART; i++)
			if (mbr->dmbr_parts[i].dp_typ == DOSPTYP_NETBSD)
				off = i + 1;

		/* just in case */
		if (!off) {
		    for (i = 0; off == 0 && i < NDOSPART; i++)
			if (mbr->dmbr_parts[i].dp_typ == DOSPTYP_EXTEND) {
				mbrofs = mbr->dmbr_parts[i].dp_start;
				goto loop;
			}
		    for (i = 0; off == 0 && i < NDOSPART; i++)
			if (mbr->dmbr_parts[i].dp_typ == DOSPTYP_EXTENDL) {
				mbrofs = mbr->dmbr_parts[i].dp_start;
				goto loop;
			}
		    for (i = 0; off == 0 && i < NDOSPART; i++)
			if (mbr->dmbr_parts[i].dp_typ == DOSPTYP_EXTENDLX) {
				mbrofs = mbr->dmbr_parts[i].dp_start;
				goto loop;
			}
		}
	}
	if (off) {
		off = mbr->dmbr_parts[off - 1].dp_start + LABELSECTOR;
	} else
		off = LABELSECTOR;

	/* Load BSD disklabel */
#ifdef BIOS_DEBUG
	if (debug)
		printf("loading disklabel @ %u\n", off);
#endif
	/* read disklabel */
	error = biosd_io(F_READ, bd, off, 1, NULL);

	if (error)
		return ("failed to read disklabel");

	/* Fill in disklabel */
	return (getdisklabel(bounce_buf, label));
}

int
biosopen(struct open_file *f, ...)
{
	va_list ap;
	register char *cp, **file;
	dev_t unit, part;
	struct diskinfo *dip;
	int i;

	va_start(ap, f);
	file = va_arg(ap, char **);
	va_end(ap);

	if (file == NULL || (cp = *file) == NULL)
		return (EINVAL);

#ifdef BIOS_DEBUG
	if (debug)
		printf("biosopen(%s)\n", cp);
#endif

	f->f_devdata = NULL;

	/* search for device specification */
	while (*cp != ':' && *cp)
		++cp;
	if (*cp == '\0' || cp - *file < 2) {
		cp = *file;
		goto nodevspec;
	}

	for (dip = TAILQ_FIRST(&disklist); dip; dip = TAILQ_NEXT(dip, list))
		if (!strncmp(*file, dip->name, cp - *file - 1))
			break;
	if (!dip) {
		cp = *file;
		goto nodevspec;
	}

	/* get partition */
	unit = cp[-2] - '0';
	part = cp[-1] - 'a';
	++cp;

	bootdev_dip = dip;

	/* Fix up bootdev */
	{ dev_t bsd_dev;
		bsd_dev = dip->bios_info.bsd_dev;
		dip->bsddev = MAKEBOOTDEV(B_TYPE(bsd_dev), B_ADAPTOR(bsd_dev),
		    B_CONTROLLER(bsd_dev), unit, part);
		dip->bootdev = MAKEBOOTDEV(B_TYPE(bsd_dev), B_ADAPTOR(bsd_dev),
		    B_CONTROLLER(bsd_dev), B_UNIT(bsd_dev), part);
	}

 nodevspec:
	if ((dip = bootdev_dip) == NULL)
		if ((dip = bootdev_dip = start_dip) == NULL)
			return (EADAPT);

#ifdef BIOS_DEBUG
	if (debug) {
		printf("BIOS geometry: heads=%u, s/t=%u; EDD=%s\n",
		    dip->bios_info.bios_heads, dip->bios_info.bios_sectors,
		    dip->bios_info.flags & BDI_LBA ? "on" : "off");
	}
#endif

	/* Try for disklabel again (might be removable media) */
	if ((i = disk_trylabel(dip)))
		return (i);

	f->f_devdata = dip;

	if (*cp != 0)
		*file = cp;
	else
		f->f_flags |= F_RAW;

	return 0;
}

const u_char bidos_errs[] =
#ifndef SMALL_BOOT
/* ignored	"\x00" "successful completion\0" */
		"\x01" "invalid function/parameter\0"
		"\x02" "address mark not found\0"
		"\x03" "write-protected\0"
		"\x04" "sector not found\0"
		"\x05" "reset failed\0"
		"\x06" "disk changed\0"
		"\x07" "drive parameter activity failed\0"
		"\x08" "DMA overrun\0"
		"\x09" "data boundary error\0"
		"\x0A" "bad sector detected\0"
		"\x0B" "bad track detected\0"
		"\x0C" "invalid media\0"
		"\x0E" "control data address mark detected\0"
		"\x0F" "DMA arbitration level out of range\0"
		"\x10" "uncorrectable CRC or ECC error on read\0"
/* ignored	"\x11" "data ECC corrected\0" */
		"\x20" "controller failure\0"
		"\x31" "no media in drive\0"
		"\x32" "incorrect drive type in CMOS\0"
		"\x40" "seek failed\0"
		"\x80" "operation timed out\0"
		"\xAA" "drive not ready\0"
		"\xB0" "volume not locked in drive\0"
		"\xB1" "volume locked in drive\0"
		"\xB2" "volume not removable\0"
		"\xB3" "volume in use\0"
		"\xB4" "lock count exceeded\0"
		"\xB5" "valid eject request failed\0"
		"\xBB" "undefined error\0"
		"\xCC" "write fault\0"
		"\xE0" "status register error\0"
		"\xFF" "sense operation failed\0"
#endif
		"\x00" "\0";

const char *
biosdisk_err(u_int error)
{
	register const u_char *p = bidos_errs;

	while (*p && *p != error)
		while (*p++);

	return ++p;
}

const struct biosdisk_errors {
	u_char error;
	u_char errno;
} tab[] = {
	{ 0x01, EINVAL },
	{ 0x03, EROFS },
	{ 0x08, EINVAL },
	{ 0x09, EINVAL },
	{ 0x0A, EBSE },
	{ 0x0B, EBSE },
	{ 0x0C, ENXIO },
	{ 0x0D, EINVAL },
	{ 0x10, EECC },
	{ 0x20, EHER },
	{ 0x31, ENXIO },
	{ 0x32, ENXIO },
	{ 0x00, EIO }
};

int
biosdisk_errno(u_int error)
{
	register const struct biosdisk_errors *p;

	if (error == 0)
		return 0;

	for (p = tab; p->error && p->error != error; p++);

	return p->errno;
}

int
biosstrategy(void *devdata, int rw, daddr_t blk, size_t size, void *buf,
    size_t *rsize)
{
	struct diskinfo *dip = (struct diskinfo *)devdata;
	bios_diskinfo_t *bd = &dip->bios_info;
	u_int8_t error = 0;
	size_t nsect;

	nsect = (size + DEV_BSIZE-1) / DEV_BSIZE;
	if (rsize != NULL)
		blk += dip->disklabel.
			d_partitions[B_PARTITION(dip->bsddev)].p_offset;

	/* Read all, sub-functions handle track boundaries */
	error = biosd_io(rw, bd, blk, nsect, buf);

#ifdef BIOS_DEBUG
	if (debug) {
		if (error != 0)
			printf("=0x%x(%s)", error, biosdisk_err(error));
		putchar('\n');
	}
#endif

	if (rsize != NULL)
		*rsize = nsect * DEV_BSIZE;

	return (biosdisk_errno(error));
}

int
biosclose(struct open_file *f)
{
	f->f_devdata = NULL;

	return 0;
}

int
biosioctl(struct open_file *f, u_long cmd, void *data)
{
	return 0;
}

int
disk_trylabel(struct diskinfo *dip)
{
	const char *st = NULL;
	bios_diskinfo_t *bd = &dip->bios_info;
	struct dos_mbr *mbr = (struct dos_mbr *)bounce_buf;
	int i, totsiz;

	if (dip->bios_info.flags & BDI_GOODLABEL)
		return (0);

	if (dip->bios_info.flags & BDI_BADLABEL) {
		st = bios_getdisklabel(&dip->bios_info, &dip->disklabel);
		if (st == NULL)
			dip->bios_info.flags &= ~BDI_BADLABEL;
	}

	if (dip->bios_info.flags & BDI_BADLABEL ||
	    !(dip->bios_info.flags & BDI_GOODLABEL)) {
#ifndef SMALL_BOOT
		int maybe_sun = 0;

		/* create an imaginary disk label */

		st = "failed to read disklabel";
		if (bd->bios_heads == 0 || bd->bios_sectors == 0)
			goto out;

		totsiz = 2880;

		if (!(bd->bios_number & 0x80) || bd->flags & BDI_EL_TORITO ||
		    (bios_bootpte.active & 0x7F) /* || !bios_bootpte.partyp */)
			bios_bootpte.partyp = 0;
		if (bd->bios_number & 0x80) {
			/* read MBR */
			i = biosd_io(F_READ, bd, DOSBBSECTOR, 1, NULL);
			if (i)
				goto nombr;
			if (!memcmp((char *)mbr + offsetof(ustar_hdr_t, magic),
			    ustar_magic_version, sizeof(ustar_magic_version)))
				goto nombr;
			if (mbr->dmbr_sign != DOSMBR_SIGNATURE)
				goto nombr;
			if (bounce_buf[0x1FC] == 0xDA &&
			    bounce_buf[0x1FD] == 0xBE) {
				for (i = 0x080; i < 0x088; ++i)
					if (bounce_buf[i])
						break;
				if (i == 0x088) {
					maybe_sun = 1;
					bios_bootpte.partyp = 0;
				}
			}
			for (i = 0; i < NDOSPART; i++)
				if (mbr->dmbr_parts[i].dp_typ &&
				    (mbr->dmbr_parts[i].dp_start +
				    mbr->dmbr_parts[i].dp_size > totsiz))
					totsiz = mbr->dmbr_parts[i].dp_start +
					    mbr->dmbr_parts[i].dp_size;
			goto mbrok;
		}
 nombr:
		for (i = 0; i < NDOSPART; i++)
			mbr->dmbr_parts[i].dp_typ = 0;
 mbrok:

		dip->disklabel.d_secsize = 512;
		dip->disklabel.d_ntracks = bd->bios_heads;
		dip->disklabel.d_nsectors = bd->bios_sectors;
		dip->disklabel.d_secpercyl = dip->disklabel.d_ntracks *
		    dip->disklabel.d_nsectors;
		totsiz += dip->disklabel.d_secpercyl - 1;
		dip->disklabel.d_ncylinders = totsiz /
		    dip->disklabel.d_secpercyl;
		memcpy(dip->disklabel.d_typename, "FAKE", 5);
		dip->disklabel.d_type = DTYPE_VND;
		strncpy(dip->disklabel.d_packname, "fictitious",
		    sizeof (dip->disklabel.d_packname));
		dip->disklabel.d_secperunit = dip->disklabel.d_ncylinders *
		    dip->disklabel.d_secpercyl;
		totsiz = dip->disklabel.d_secperunit;
		dip->disklabel.d_rpm = 3600;
		dip->disklabel.d_interleave = 1;

		dip->disklabel.d_bbsize = 8192;
		dip->disklabel.d_sbsize = 65536;

		bzero(dip->disklabel.d_partitions,
		    sizeof (dip->disklabel.d_partitions));

		if (bios_bootpte.partyp &&
		    (bios_bootpte.p_ofs || bios_bootpte.p_siz)) {
			/* 'a' partition passed from MBR/SYSLINUX */
			dip->disklabel.d_partitions[0].p_offset = bios_bootpte.p_ofs;
			dip->disklabel.d_partitions[0].p_size = bios_bootpte.p_siz;
			dip->disklabel.d_partitions[0].p_fstype = FS_MANUAL;
		} else {
			/* 'a' partition covering the "whole" disk */
			dip->disklabel.d_partitions[0].p_offset = 0;
			dip->disklabel.d_partitions[0].p_size = totsiz;
			dip->disklabel.d_partitions[0].p_fstype =
			    maybe_sun ? FS_MANUAL : FS_OTHER;
		}

		/* The raw partition is special */
		dip->disklabel.d_partitions[RAW_PART].p_offset = 0;
		dip->disklabel.d_partitions[RAW_PART].p_size = totsiz;
		dip->disklabel.d_partitions[RAW_PART].p_fstype = FS_UNUSED;

		for (i = 0; i < NDOSPART; i++) {
			if (!mbr->dmbr_parts[i].dp_typ)
				continue;
			dip->disklabel.d_partitions[RAW_PART+i+1].p_offset =
			    mbr->dmbr_parts[i].dp_start;
			dip->disklabel.d_partitions[RAW_PART+i+1].p_size =
			    mbr->dmbr_parts[i].dp_size;
			dip->disklabel.d_partitions[RAW_PART+i+1].p_fstype =
			    FS_MANUAL;
			if (dip->disklabel.d_partitions[0].p_fstype ==
			    FS_MANUAL)
				continue;
			/* a GUID Partition Table cannot become 'a' slice */
			if (mbr->dmbr_parts[i].dp_typ == 0xEE)
				continue;
			/* 'a' partition covering the first partition */
			dip->disklabel.d_partitions[0].p_offset =
			    mbr->dmbr_parts[i].dp_start;
			dip->disklabel.d_partitions[0].p_size =
			    mbr->dmbr_parts[i].dp_size;
			dip->disklabel.d_partitions[0].p_fstype = FS_MANUAL;
		}
#else /* SMALL_BOOT */
		/* check if ustar, if so fake a disklabel */

		st = "failed to read disklabel";
		if (bd->bios_heads == 0 || bd->bios_sectors == 0)
			goto out;

		totsiz = 2880;

		i = biosd_io(F_READ, bd, DOSBBSECTOR, 1, NULL);
		if (i)
			goto out;
		if (memcmp((char *)mbr + offsetof(ustar_hdr_t, magic),
		    ustar_magic_version, sizeof(ustar_magic_version)))
			goto out;

		dip->disklabel.d_secsize = 512;
		dip->disklabel.d_ntracks = bd->bios_heads;
		dip->disklabel.d_nsectors = bd->bios_sectors;
		dip->disklabel.d_secpercyl = dip->disklabel.d_ntracks *
		    dip->disklabel.d_nsectors;
		totsiz += dip->disklabel.d_secpercyl - 1;
		dip->disklabel.d_ncylinders = totsiz /
		    dip->disklabel.d_secpercyl;
		memcpy(dip->disklabel.d_typename, "FAKE", 5);
		dip->disklabel.d_type = DTYPE_VND;
		strncpy(dip->disklabel.d_packname, "fictitious",
		    sizeof (dip->disklabel.d_packname));
		dip->disklabel.d_secperunit = dip->disklabel.d_ncylinders *
		    dip->disklabel.d_secpercyl;
		totsiz = dip->disklabel.d_secperunit;
		dip->disklabel.d_rpm = 300;
		dip->disklabel.d_interleave = 1;

		dip->disklabel.d_bbsize = 8192;
		dip->disklabel.d_sbsize = 65536;

		bzero(dip->disklabel.d_partitions,
		    sizeof (dip->disklabel.d_partitions));

		/* 'a' partition covering the "whole" disk */
		dip->disklabel.d_partitions[0].p_offset = 0;
		dip->disklabel.d_partitions[0].p_size = totsiz;
		dip->disklabel.d_partitions[0].p_fstype = FS_MANUAL;

		/* The raw partition is special */
		dip->disklabel.d_partitions[RAW_PART].p_offset = 0;
		dip->disklabel.d_partitions[RAW_PART].p_size = totsiz;
		dip->disklabel.d_partitions[RAW_PART].p_fstype = FS_UNUSED;
#endif
		dip->disklabel.d_npartitions = MAXPARTITIONS;

		dip->disklabel.d_magic = DISKMAGIC;
		dip->disklabel.d_magic2 = DISKMAGIC;
		dip->disklabel.d_checksum = dkcksum(&dip->disklabel);

		dip->bios_info.flags &= ~BDI_BADLABEL;
		dip->bios_info.flags |= BDI_GOODLABEL;
		st = NULL;
	}
 out:
	if ((dip->bios_info.flags & BDI_BADLABEL) && st == NULL)
		st = "*none*";
	if (st != NULL) {
		printf("%s\n", st);
		return ERDLAB;
	}

	return (0);
}
