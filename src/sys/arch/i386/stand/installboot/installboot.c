/**	$MirOS: src/sys/arch/i386/stand/installboot/installboot.c,v 1.33 2009/06/07 13:08:57 tg Exp $ */
/*	$OpenBSD: installboot.c,v 1.47 2004/07/15 21:44:16 tom Exp $	*/
/*	$NetBSD: installboot.c,v 1.5 1995/11/17 23:23:50 gwr Exp $ */

/*-
 * Copyright (c) 2003, 2004, 2005, 2006, 2007, 2009
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
 *-
 * Notes:
 *	- this still splits by geometry, even if bootxx does that
 *	  by itself for quite a while
 *	- the -M option could be implemented similar to bxinst.i386
 *	- this is superfluous once we have getextent_ffs and a frontend
 */

/*
 * Copyright (c) 1997 Michael Shalayeff
 * Copyright (c) 1994 Paul Kranenburg
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
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by Paul Kranenburg.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/mount.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/disklabel.h>
#include <sys/dkio.h>
#include <sys/ioctl.h>
#include <ufs/ufs/dinode.h>
#include <ufs/ufs/dir.h>
#include <ufs/ffs/fs.h>
#include <sys/reboot.h>
#include <sys/errno.h>

#include <uvm/uvm_extern.h>
#include <sys/sysctl.h>

#include <machine/cpu.h>
#include <machine/biosvar.h>

#include <err.h>
#include <a.out.h>
#include <sys/exec_elf.h>
#include <fcntl.h>
#include <nlist.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <util.h>

__RCSID("$MirOS: src/sys/arch/i386/stand/installboot/installboot.c,v 1.33 2009/06/07 13:08:57 tg Exp $");

extern const char *__progname;
int	verbose, nowrite, nheads, nsectors, userspec = 0;
char	*boot, *proto, *dev, *realdev;
struct nlist nl[] = {
#define X_BLOCK_COUNT	0
	{{"_bkcnt"}},
#define X_BLOCK_TABLE	1
	{{"_bktbl"}},
#define	X_NUM_SECS	2
	{{"_geoms"}},
#define	X_NUM_HEADS	3
	{{"_geomh"}},
#define	X_PARTP		4
	{{"_partp"}},
#define X_START		5
	{{"__start"}},
	{{NULL}}
};

u_int8_t *block_count_p;	/* block count var. in prototype image */
u_int8_t *block_table_p;	/* block number array in prototype image */
u_int8_t *num_heads_p;		/* number of tracks per cylinder */
u_int8_t *num_secs_p;		/* number of sectors per track */
uint8_t  *partp_p;		/* user defined partition type */
uint8_t  *start_p;		/* begin (0000:7C00) of PBR */
u_int8_t *bblkend;		/* end of boot block table (+1) */
int	maxblocklen;		/* size of this array */
int	curblocklen = 0;	/* actually used up bytes */
int	force_mbr = 0;		/* install into MBR */
int	userpt = 0;		/* user defined partition type, self-local */

int biosdev;

static const char T_warning[] = "warning: ";

char		*loadprotoblocks(char *, long *);
int		loadblocknums(char *, int, struct disklabel *);
static void	devread(int, void *, daddr_t, size_t, char *);
static __dead void usage(void);
static int	record_block(u_int8_t *, daddr_t, u_int);
static int	do_record(u_int8_t *, daddr_t, u_int);


static void
usage(void)
{
	fprintf(stderr, "usage:\t%s [-Anv] [-P part] [-s sec-per-track] "
	    "[-h track-per-cyl]\n", __progname);
	fprintf(stderr, "\t    boot bootxx device\n");
	exit(1);
}

int
read_pt(int f, long offs, struct dos_mbr *target, size_t secsize)
{
#ifdef	DEBUG
	fprintf(stderr, "debug: read_pt at %d (0x%X)\n", offs, offs);
#endif
	if (lseek(f, (off_t)offs * secsize, SEEK_SET) < 0)
		return -1;
	if (read(f, target, secsize) < secsize)
		return -1;
	return 0;
}

int
scan_pt(struct dos_partition *dp, u_int8_t what)
{
	int part;

	for (part = 0; part < NDOSPART; ++part) {
		if ((!get_le(&dp[part].dp_size)) || (dp[part].dp_typ != what))
			continue;
		fprintf(stderr, "# found partition %d: "
		    "type %02X ofs %d (0x%Xh) size %d (0x%X)%s\n",
		    part, dp[part].dp_typ,
		    get_le(&dp[part].dp_start), get_le(&dp[part].dp_start),
		    get_le(&dp[part].dp_size), get_le(&dp[part].dp_size),
		    ( ((what == DOSPTYP_EXTENDL) || (what == DOSPTYP_EXTENDLX)
		       || (what == DOSPTYP_EXTEND)) ? ", chaining..." : "."));
		return part;
	}
	return NDOSPART;
}

int
main(int argc, char *argv[])
{
	int	c;
	int	devfd;
	char	*protostore;
	long	protosize;
	struct stat sb;
	struct disklabel dl;
	struct dos_mbr mbr;
	struct dos_partition *dp;
	off_t startoff = 0;
	int mib[4];
	size_t size;
	dev_t devno;
	bios_diskinfo_t di;
	long mbrofs;
	int mbrpart;

	fprintf(stderr, "MirOS BSD installboot " __BOOT_VER "\n");

	nsectors = nheads = -1;
	while ((c = getopt(argc, argv, "1Ah:MnP:s:v")) != -1) {
		switch (c) {
		case '1':
			break;
		case 'A':
			nheads = 0;
			nsectors = 99;
			userspec = 1;
			break;
		case 'h':
			nheads = atoi(optarg);
			if (nheads < 1 || nheads > 256) {
				warnx("invalid value for -h");
				nheads = -1;
			} else	userspec = 1;
			break;
		case 'M':
#if 0
			++force_mbr;
#else
			fprintf(stderr, "error: -M not supported yet!\n");
#endif
			break;
		case 'n':
			/* Do not actually write the bootblock to disk */
			nowrite = 1;
			break;
		case 'P':
			userpt = (int)strtonum(optarg, 1, 255, NULL);
			if (!userpt) {
				warnx("invalid value for -P");
				userpt = 0;
			}
			break;
		case 's':
			nsectors = atoi(optarg);
			if (nsectors < 1 || nsectors > 63) {
				warnx("invalid value for -s");
				nsectors = -1;
			} else	userspec = 1;
			break;
		case 'v':
			/* Chat */
			verbose = 1;
			break;
		default:
			usage();
		}
	}

	if (argc - optind < 3) {
		usage();
	}

	boot = argv[optind];
	proto = argv[optind + 1];
	realdev = dev = argv[optind + 2];

	/* Open and check raw disk device */
	if ((devfd = opendev(dev, (nowrite? O_RDONLY:O_RDWR),
			     OPENDEV_PART, &realdev)) < 0)
		err(1, "open: %s", realdev);

	if (verbose) {
		fprintf(stderr, "boot: %s\n", boot);
		fprintf(stderr, "proto: %s\n", proto);
		fprintf(stderr, "device: %s\n", realdev);
	}

	if (ioctl(devfd, DIOCGDINFO, &dl) != 0)
		err(1, "disklabel: %s", realdev);

	/* check disklabel */
	if (dl.d_magic != DISKMAGIC)
		err(1, "bad disklabel magic=%0x8x", dl.d_magic);

	/* warn on unknown disklabel types */
	if (dl.d_type == 0)
		warnx("disklabel type unknown");

	/* Load proto blocks into core */
	if ((protostore = loadprotoblocks(proto, &protosize)) == NULL)
		exit(1);

	/* XXX - Paranoia: Make sure size is aligned! */
	if (protosize & (DEV_BSIZE - 1))
		err(1, "proto %s bad size=%ld", proto, protosize);

	/* Write patched proto bootblocks into the superblock */
	if (protosize > SBSIZE - DEV_BSIZE)
		errx(1, "proto bootblocks too big");

	if (fstat(devfd, &sb) < 0)
		err(1, "stat: %s", realdev);

	if (!S_ISCHR(sb.st_mode))
		errx(1, "%s: Not a character device", realdev);

	if (nheads == -1 || nsectors == -1) {
		mib[0] = CTL_MACHDEP;
		mib[1] = CPU_CHR2BLK;
		mib[2] = sb.st_rdev;
		size = sizeof(devno);
		if(sysctl(mib, 3, &devno, &size, NULL, 0) >= 0) {
			devno = MAKEBOOTDEV(major(devno), 0, 0,
			    DISKUNIT(devno), RAW_PART);
			mib[0] = CTL_MACHDEP;
			mib[1] = CPU_BIOS;
			mib[2] = BIOS_DISKINFO;
			mib[3] = devno;
			size = sizeof(di);
			if(sysctl(mib, 4, &di, &size, NULL, 0) >= 0) {
				nheads = di.bios_heads;
				nsectors = di.bios_sectors;
			}
		}
	}

	/* Extract and load block numbers */
	if (loadblocknums(boot, devfd, &dl) != 0)
		exit(1);

	/* Sync filesystems (to clean in-memory superblock?) */
	sync(); sleep(1);

	if (dl.d_type != 0 && dl.d_type != DTYPE_FLOPPY &&
	    dl.d_type != DTYPE_VND && !force_mbr) {
		mbrofs = DOSBBSECTOR;
 loop:		if (read_pt(devfd, mbrofs, &mbr, dl.d_secsize))
			err(4, "can't read partition table");

		if (mbr.dmbr_sign != DOSMBR_SIGNATURE)
			errx(1, "broken MBR");

		dp = mbr.dmbr_parts;
		for (mbrpart = 0; mbrpart < NDOSPART; ++mbrpart)
			set_le(&dp[mbrpart].dp_start,
			    get_le(&dp[mbrpart].dp_start) + mbrofs);

		if (userpt) if ((mbrpart = scan_pt(dp, userpt)) < NDOSPART) {
			warnx("using USER partition, type %02Xh", userpt);
			goto found;
		}
		if ((mbrpart = scan_pt(dp, DOSPTYP_MIRBSD)) < NDOSPART)
			goto found;
		if ((mbrpart = scan_pt(dp, DOSPTYP_OPENBSD)) < NDOSPART) {
			warnx("using OpenBSD partition!");
			goto found;
		}
		if ((mbrpart = scan_pt(dp, DOSPTYP_NETBSD)) < NDOSPART) {
			warnx("using NetBSD partition!");
			goto found;
		}
		if ((mbrpart = scan_pt(dp, DOSPTYP_FREEBSD)) < NDOSPART) {
			warnx("using FreeBSD partition!");
			goto found;
		}

		/* no native partition found, try extended ones */
		if ((mbrpart = scan_pt(dp, DOSPTYP_EXTEND)) == NDOSPART)
		    if ((mbrpart = scan_pt(dp, DOSPTYP_EXTENDL)) == NDOSPART)
		    if ((mbrpart = scan_pt(dp, DOSPTYP_EXTENDLX)) == NDOSPART)
			errx(1, "no BSD partition");

		/* found extended partition, loop back */
		mbrofs = get_le(&dp[mbrpart].dp_start);
		goto loop;

 found:		startoff = (off_t)get_le(&dp[mbrpart].dp_start);
	}

	while (bblkend < (block_table_p + maxblocklen))
		if (((ptrdiff_t)(bblkend - start_p) & 0xFFCF) == 0x01C2)
			*bblkend++ = 0;
		else
			*bblkend++ = arc4random() & 0xFF;

	if (nheads == -1 || nsectors == -1) {
		fprintf(stderr, "%sUnable to get BIOS geometry, "
		    "must/should specify -h and -s\n%sthe drive "
		    "may not boot in non-LBA mode\n", T_warning, T_warning);
		nsectors = -1;
	}

	fprintf(stderr, "writing bootblock to sector %ld (0x%lX)\n",
	    (long)startoff, (unsigned long)startoff);
	if (nsectors == 99 || nsectors == -1) {
		if (verbose || nsectors == -1)
			fprintf(stderr, "%susing automatic disc geometry\n",
			    nsectors == -1 ? T_warning : "");
		nheads = 0;
		nsectors = 0;
	} else if (verbose)
		fprintf(stderr, "using disc geometry of %d heads, %d sectors"
		    " per track\n", nheads, nsectors);
	startoff *= dl.d_secsize;

	*num_heads_p = nheads & 255;
	*(num_heads_p + 1) = nheads >> 8;
	*num_secs_p = nsectors & 63;
	*partp_p = userpt;

	if (!nowrite) {
		if (lseek(devfd, startoff, SEEK_SET) < 0 ||
		    write(devfd, protostore, protosize) != protosize)
			err(1, "write bootstrap");
	}

	(void)close(devfd);

	return 0;
}

char *
loadprotoblocks(char *fname, long *size)
{
	int	fd;
	size_t	tdsize;		/* text+data size */
	char	*bp;
	struct	nlist *nlp;
	Elf_Ehdr eh;
	Elf_Word phsize;
	Elf_Phdr *ph;

	fd = -1;
	bp = NULL;

	/* Locate block number array in proto file */
	if (nlist(fname, nl) != 0) {
		warnx("nlist: %s: symbols not found", fname);
		return NULL;
	}
	/* Validate symbol types (global data). */
	for (nlp = nl; nlp->n_un.n_name; nlp++) {
		if (nlp->n_type != (N_TEXT) && nlp->n_type != (N_DATA)) {
			warnx("nlist: %s: wrong type %x", nlp->n_un.n_name,
			nlp->n_type);
			return NULL;
		}
	}

	if ((fd = open(fname, O_RDONLY)) < 0) {
		warn("open: %s", fname);
		return NULL;
	}
	if (read(fd, &eh, sizeof(eh)) != sizeof(eh)) {
		warn("read: %s", fname);
		goto bad;
	}
	if (!IS_ELF(eh)) {
		errx(1, "%s: bad magic: 0x%02x%02x%02x%02x",
		boot,
		eh.e_ident[EI_MAG0], eh.e_ident[EI_MAG1],
		eh.e_ident[EI_MAG2], eh.e_ident[EI_MAG3]);
	}

	/*
	 * We have to include the exec header in the beginning of
	 * the buffer, and leave extra space at the end in case
	 * the actual write to disk wants to skip the header.
	 */

	/* program load header */
	if (eh.e_phnum != 1) {
		errx(1, "%s: only supports one ELF load section", boot);
	}
	phsize = eh.e_phnum * sizeof(Elf_Phdr);
	ph = malloc(phsize);
	if (ph == NULL) {
		errx(1, "%s: unable to allocate program header space",
		    boot);
	}
	lseek(fd, eh.e_phoff, SEEK_SET);

	if (read(fd, ph, phsize) != phsize) {
		errx(1, "%s: unable to read program header space", boot);
	}

	tdsize = ph->p_filesz;

	/*
	 * Allocate extra space here because the caller may copy
	 * the boot block starting at the end of the exec header.
	 * This prevents reading beyond the end of the buffer.
	 */
	if ((bp = calloc(tdsize, 1)) == NULL) {
		warnx("malloc: %s: no memory", fname);
		goto bad;
	}
	/* Read the rest of the file. */
	lseek(fd, ph->p_offset, SEEK_SET);
	if (read(fd, bp, tdsize) != tdsize) {
		warn("read: %s", fname);
		goto bad;
	}

	*size = tdsize;	/* not aligned to DEV_BSIZE */

	/* Calculate the symbols' locations within the proto file */
#define SYMADDR(x)	((uint8_t *)(bp + nl[x].n_value - nl[X_START].n_value))
	block_count_p = SYMADDR(X_BLOCK_COUNT);
	block_table_p = SYMADDR(X_BLOCK_TABLE);
	num_heads_p = SYMADDR(X_NUM_HEADS);
	num_secs_p = SYMADDR(X_NUM_SECS);
	partp_p = SYMADDR(X_PARTP);
	start_p = SYMADDR(X_START);
	maxblocklen = *block_count_p;
	if (force_mbr) maxblocklen -= 64;

	if (verbose) {
		fprintf(stderr, "%s: entry point %#x\n", fname, eh.e_entry);
		fprintf(stderr, "proto bootblock size %ld\n", *size);
		fprintf(stderr,
		    "room for average %d filesystem blocks (%d bytes) at %#lx\n",
		    (int)(((double)maxblocklen)/4.5), maxblocklen,
		    nl[X_BLOCK_TABLE].n_value);
	}

	close(fd);
	return bp;

 bad:
	if (bp)
		free(bp);
	if (fd >= 0)
		close(fd);
	return NULL;
}

static void
devread(int fd, void *buf, daddr_t blk, size_t size, char *msg)
{
	if (lseek(fd, dbtob((off_t)blk), SEEK_SET) != dbtob((off_t)blk))
		err(1, "%s: devread: lseek", msg);

	if (read(fd, buf, size) != size)
		err(1, "%s: devread: read", msg);
}

static char sblock[SBSIZE];

int
loadblocknums(char *boot, int devfd, struct disklabel *dl)
{
	int		i, fd;
	struct stat	statbuf, sb;
	struct statfs	statfsbuf;
	struct partition *pl;
	struct fs	*fs;
	char		*buf;
	daddr_t		blk, *ap;
	struct ufs1_dinode	*ip;
	int		ndb;
	u_int8_t	*bt;
	int		mib[4];
	size_t		size;
	dev_t dev;

	/*
	 * Open 2nd-level boot program and record the block numbers
	 * it occupies on the filesystem represented by 'devfd'.
	 */

	/* Make sure the (probably new) boot file is on disk. */
	sync(); sleep(1);

	if ((fd = open(boot, O_RDONLY)) < 0)
		err(1, "open: %s", boot);

	if (fstatfs(fd, &statfsbuf) != 0)
		err(1, "statfs: %s", boot);

	if (strncmp(statfsbuf.f_fstypename, "ffs", MFSNAMELEN) &&
	    strncmp(statfsbuf.f_fstypename, "ufs", MFSNAMELEN) ) {
		errx(1, "%s: must be on an FFS filesystem", boot);
	}

#if 0
	if (read(fd, &eh, sizeof(eh)) != sizeof(eh)) {
		errx(1, "read: %s", boot);
	}

	if (!IS_ELF(eh)) {
		errx(1, "%s: bad magic: 0x%02x%02x%02x%02x",
		boot,
		eh.e_ident[EI_MAG0], eh.e_ident[EI_MAG1],
		eh.e_ident[EI_MAG2], eh.e_ident[EI_MAG3]);
	}
#endif

	if (fsync(fd) != 0)
		err(1, "fsync: %s", boot);

	if (fstat(fd, &statbuf) != 0)
		err(1, "fstat: %s", boot);

	if (fstat(devfd, &sb) != 0)
		err(1, "fstat: %s", realdev);

	/* check devices */
	mib[0] = CTL_MACHDEP;
	mib[1] = CPU_CHR2BLK;
	mib[2] = sb.st_rdev;
	size = sizeof(dev);
	if (sysctl(mib, 3, &dev, &size, NULL, 0) >= 0)
		if (statbuf.st_dev / MAXPARTITIONS != dev / MAXPARTITIONS)
			errx(1, "cross-device install");

	pl = &dl->d_partitions[DISKPART(statbuf.st_dev)];
	close(fd);

	/* Read superblock */
	devread(devfd, sblock, pl->p_offset + SBLOCK, SBSIZE, "superblock");
	fs = (struct fs *)sblock;

	/* Sanity-check super-block. */
	if (fs->fs_magic != FS_MAGIC)
		errx(1, "Bad magic number in superblock");
	if (fs->fs_inopb <= 0)
		err(1, "Bad inopb=%d in superblock", fs->fs_inopb);

	/* Read inode */
	if ((buf = malloc(fs->fs_bsize)) == NULL)
		errx(1, "No memory for filesystem block");

	blk = fsbtodb(fs, ino_to_fsba(fs, statbuf.st_ino));
	devread(devfd, buf, pl->p_offset + blk, fs->fs_bsize, "inode");
	ip = (struct ufs1_dinode *)(buf) + ino_to_fsbo(fs, statbuf.st_ino);

	/*
	 * Have the inode.  Figure out how many blocks we need.
	 */
	ndb = howmany(ip->di_size, fs->fs_bsize);
	if (ndb <= 0)
		errx(1, "No blocks to load");
	if (verbose)
		fprintf(stderr, "Will load %d blocks of size %d each.\n",
			ndb, fs->fs_bsize);

	if ((dl->d_type != 0 && dl->d_type != DTYPE_FLOPPY &&
	    dl->d_type != DTYPE_VND) || (userspec && nsectors != 99)) {
		/* adjust disklabel w/ synthetic geometry */
		dl->d_nsectors = nsectors;
		dl->d_secpercyl = dl->d_nsectors * nheads;
	}

	if (verbose)
		fprintf(stderr, "Using disk geometry of %u sectors and %u heads.\n",
			dl->d_nsectors, dl->d_secpercyl/dl->d_nsectors);

	/*
	 * Get the block numbers; we don't handle fragments
	 */
	ap = ip->di_db;
	bt = block_table_p;
	for (i = 0; i < NDADDR && *ap && ndb; i++, ap++, ndb--)
		bt += record_block(bt, pl->p_offset + fsbtodb(fs, *ap),
					    fs->fs_bsize / 512);
	if (ndb != 0) {

		/*
		 * Just one level of indirections; there isn't much room
		 * for more in the 2nd-level /boot anyway.
		 */
		blk = fsbtodb(fs, ip->di_ib[0]);
		devread(devfd, buf, pl->p_offset + blk, fs->fs_bsize,
			"indirect block");
		ap = (daddr_t *)buf;
		for (; i < NINDIR(fs) && *ap && ndb; i++, ap++, ndb--)
			bt += record_block(bt, pl->p_offset + fsbtodb(fs, *ap),
					   fs->fs_bsize / 512);
	}

	bt += record_block(bt, 0, 0);

	if ((bblkend = bt) > (block_table_p + maxblocklen))
		errx(1, "Too many blocks");

	if (verbose)
		fprintf(stderr, "%s: %d entries total (%d bytes)\n",
			boot, block_count_p[0], curblocklen);

	return 0;
}

static int
record_block(u_int8_t *bt, daddr_t blk, u_int bs)
{
	static u_int W_num = 0;
	static daddr_t W_ofs = 0;

	int flush = 0, cache = 0, retval = 0;
	int i;

	if (!blk) {
		++flush;
	} else if (!W_ofs) {
		++cache;
	} else if (blk == (W_ofs+W_num)) {
		++cache;
	} else {
		++flush;
		++cache;
	}

	if (flush) {
		/*
		 * Flush the blocks cached to the disc.
		 * Obey the track boundaries if possible.
		 */
		if (!W_num) goto flush_end;
		if ((nheads == -1) || (nsectors == -1) || (nsectors == 99)) {
			retval += do_record(bt+retval, W_ofs, W_num);
			goto flush_end;
		}

		i = W_ofs % nsectors;		/* sector within track -1 */
		if (i < (nsectors-1)) {
			i = nsectors - i;
			if (i > W_num) i=W_num;
			retval += do_record(bt+retval, W_ofs, i);
			W_ofs += i;
			W_num -= i;
		}

		while (W_num > nsectors) {
			retval += do_record(bt+retval, W_ofs, nsectors);
			W_ofs += nsectors;
			W_num -= nsectors;
		}

		if (W_num)
			retval += do_record(bt+retval, W_ofs, W_num);

	flush_end:
		W_ofs=0; W_num=0;
	}

	if (cache) {
		if (!W_ofs) W_ofs = blk;
		W_num += bs;
	}

	return (retval);
}

static int
do_record(u_int8_t *bt, daddr_t blk, u_int bs)
{
	static u_int i = 0;
	u_int8_t tv, len;
	u_int64_t bk, wbk;
	u_int j;
	int wbs, retval = 0;
	u_int8_t *wbt;

	if ((!blk) || (!bt))
		return 0;

	if (bs > 768)	/* after that there's VGA memory */
		errx(1, "Too many blocks in a chunk!");

	wbs = bs;
	wbt = bt;
	bk = blk;
	if (verbose)
		fprintf(stderr, "%2d: %2d @%lld (0x%08llX)\n",
		    i, bs, bk, bk);

	do {
		++i;

		if (bk < 0x0000000000000100ULL)
			len = 0;
		else if (bk < 0x0000000000010000ULL)
			len = 1;
		else if (bk < 0x0000000001000000ULL)
			len = 2;
		else if (bk < 0x0000000100000000ULL)
			len = 3;
		else if (bk < 0x0000010000000000ULL)
			len = 4;
		else if (bk < 0x0001000000000000ULL)
			len = 5;
		else if (bk < 0x0100000000000000ULL)
			len = 6;
		else	len = 7;

		if (wbs < 33)
			tv = (len << 5) | (wbs - 1);
		  else	tv = (len << 5) | 31;

		*(wbt++) = tv;
		wbk = bk;
		bk += 1 + (tv & 31);
		for (j = 0; j <= len; ++j) {
			*(wbt++) = (wbk & 0xFF);
			wbk >>= 8;
		}

		wbs -= 32;
		retval += (len+2);
	} while (wbs > 0);

	*block_count_p = i;
	curblocklen += retval;
	return (retval);
}
