/**	$MirOS: src/sys/arch/i386/i386/disksubr.c,v 1.8 2009/02/09 13:09:19 tg Exp $ */
/*	$OpenBSD: disksubr.c,v 1.44 2004/03/17 14:16:04 miod Exp $	*/
/*	$NetBSD: disksubr.c,v 1.21 1996/05/03 19:42:03 christos Exp $	*/

/*-
 * Copyright (c) 1996 Theo de Raadt
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
 * Copyright (c) 2004, 2007, 2008, 2009
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
 *	@(#)ufs_disksubr.c	7.16 (Berkeley) 5/4/91
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/device.h>
#include <sys/disklabel.h>
#include <sys/syslog.h>
#include <sys/disk.h>

#include <dev/rndvar.h>

void
dk_establish(dk, dev)
	struct disk *dk;
	struct device *dev;
{
}

int read_pt(long, long, void (*strat)(struct buf *),
    struct buf *, struct dos_partition *);
int scan_pt(struct dos_partition *, u_int8_t);
int find_mirbsd_disklabel(void (*strat)(struct buf *), struct buf *,
    struct disklabel *, struct dos_partition *);

int
read_pt(long offs, long secpercyl, void (*strat)(struct buf *),
    struct buf *bp, struct dos_partition *target)
{
	int i;

#ifdef DEBUG
	printf("debug: reading pt at %d (0x%X)\n", offs, offs);
#endif
	bp->b_blkno = offs;
	bp->b_flags = B_BUSY | B_READ;
	bp->b_cylinder = offs / secpercyl;
	(*strat)(bp);
	if (biowait(bp))
		return -1;

	memcpy(target, bp->b_data + DOSPARTOFF, NDOSPART * sizeof(*target));
	for (i = 0; i < NDOSPART; ++i)
		set_le(&target[i].dp_start,
		    get_le(&target[i].dp_start) + offs);

	return ((((struct dos_mbr *)(bp->b_data))->dmbr_sign ==
	    DOSMBR_SIGNATURE) ? 0 : 1);
}

int
scan_pt(struct dos_partition *dp, u_int8_t what)
{
	int part;

	for (part = 0; part < NDOSPART; ++part) {
		if ((!get_le(&dp[part].dp_size)) || (dp[part].dp_typ != what))
			continue;
#ifdef DEBUG
		printf("debug: found partition %d: "
		    "type %02X ofs %d (0x%Xh) size %d (0x%X)%s\n",
		    part, dp[part].dp_typ,
		    get_le(&dp[part].dp_start), get_le(&dp[part].dp_start),
		    get_le(&dp[part].dp_size), get_le(&dp[part].dp_size),
		    ( ((what == DOSPTYP_EXTENDL) || (what == DOSPTYP_EXTENDLX)
		       || (what == DOSPTYP_EXTEND)) ? ", chaining..." : "."));
#endif
		return part;
	}
	return NDOSPART;
}

/*
 * find "our" partition on the disc, following extended
 * partitions as much as possible
 */
int
find_mirbsd_disklabel(void (*strat)(struct buf *), struct buf *bp,
    struct disklabel *lp, struct dos_partition *dp)
{
	long mbrofs = DOSBBSECTOR;
	int part;

 loop:
	if (read_pt(mbrofs, lp->d_secpercyl, strat, bp, dp))
		return -1;
	if ((part = scan_pt(dp, DOSPTYP_MIRBSD)) < NDOSPART)
		goto found;
	if ((part = scan_pt(dp, DOSPTYP_OPENBSD)) < NDOSPART) {
		printf("warning: using OpenBSD partition!\n");
		goto found;
	}
	if ((part = scan_pt(dp, DOSPTYP_NETBSD)) < NDOSPART) {
		printf("warning: using NetBSD partition!\n");
		goto found;
	}
	if ((part = scan_pt(dp, DOSPTYP_FREEBSD)) < NDOSPART) {
		printf("warning: using FreeBSD partition!\n");
		goto found;
	}
	if ((part = scan_pt(dp, DOSPTYP_EXTEND)) == NDOSPART)
	    if ((part = scan_pt(dp, DOSPTYP_EXTENDL)) == NDOSPART)
	    if ((part = scan_pt(dp, DOSPTYP_EXTENDLX)) == NDOSPART)
		return -1;
	mbrofs = get_le(&dp[part].dp_start);
	goto loop;

 found:
	memcpy(dp, &dp[part], sizeof(*dp));
	return 0;
}


/*
 * Attempt to read a disk label from a device
 * using the indicated strategy routine.
 * The label must be partly set up before this:
 * secpercyl, secsize and anything required for a block i/o read
 * operation in the driver's strategy/start routines
 * must be filled in before calling us.
 *
 * If dos partition table requested, attempt to load it and
 * find disklabel inside a DOS partition. Also, if bad block
 * table needed, attempt to extract it as well. Return buffer
 * for use in signalling errors if requested.
 *
 * Returns null on success and an error string on failure.
 */
char *
readdisklabel(dev_t dev, void (*strat)(struct buf *), struct disklabel *lp,
    struct cpu_disklabel *osdep, int spoofonly)
{
	struct dos_partition *dp = osdep->dosparts;
	struct dkbad *bdp = &DKBAD(osdep);
	struct buf *bp = NULL;
	struct disklabel *dlp;
	char *msg = NULL, *cp;
	int i, dospartoff = 0, cyl = (LABELSECTOR / lp->d_secpercyl);
	u_int32_t d_secsize;	/* working number of bytes per sector */

	/* minimal requirements for archtypal disk label */
	if (lp->d_secsize < DEV_BSIZE)
		lp->d_secsize = DEV_BSIZE;
	if (lp->d_secpercyl == 0) {
		msg = "invalid geometry";
		goto done;
	}
	if (lp->d_secperunit == 0)
		lp->d_secperunit = 0x1fffffff;
	lp->d_npartitions = RAW_PART + 1;
	for (i = 0; i < RAW_PART; i++) {
		lp->d_partitions[i].p_size = 0;
		lp->d_partitions[i].p_offset = 0;
	}
	if (lp->d_partitions[i].p_size == 0)
		lp->d_partitions[i].p_size = 0x1fffffff;
	lp->d_partitions[i].p_offset = 0;

	/* get a buffer and initialise it */
	bp = geteblk((int)lp->d_secsize);
	bp->b_dev = dev;
	bp->b_bcount = d_secsize = lp->d_secsize;

	if (dp && !spoofonly)
		if (!find_mirbsd_disklabel(strat, bp, lp, dp)) {
			/*
			 * This is our MBR partition. need sector address
			 * for SCSI/IDE, cylinder for ESDI/ST506/RLL
			 */
			dospartoff = get_le(&dp->dp_start);
			cyl = DPCYL(dp->dp_scyl, dp->dp_ssect);

			/* XXX build a temporary disklabel */
			lp->d_partitions[0].p_size = get_le(&dp->dp_size);
			lp->d_partitions[0].p_offset =
				get_le(&dp->dp_start);
			if (lp->d_ntracks == 0)
				lp->d_ntracks = dp->dp_ehd + 1;
			if (lp->d_nsectors == 0)
				lp->d_nsectors = DPSECT(dp->dp_esect);
			if (lp->d_secpercyl == 0)
				lp->d_secpercyl = lp->d_ntracks *
				    lp->d_nsectors;
		}

	/* do dos partitions in the process of getting disklabel? */
	if (dp) {
	        daddr_t part_blkno = DOSBBSECTOR;
		int wander = 1, n = 0, loop = 0;

		/*
		 * Read dos partition table, follow extended partitions.
		 * Map the partitions to disklabel entries i-p
		 */
		while (wander && n < 8 && loop < 8) {
		        loop++;
			wander = 0;

			/* read boot record */
			switch (read_pt(part_blkno, lp->d_secpercyl, strat,
			    bp, dp)) {
			case -1:
				msg = "dos partition I/O error";
				goto done;
			case 1:
				if (loop == 1)
					goto dodospart_noparts;
				else
					goto dodospart_someparts;
			}

			/*
			 * In case the disklabel read below fails, we want to
			 * provide a fake label in i-p.
			 */
			for (i=0; i < NDOSPART && n < 8; ++i) {
				struct partition *pp = &lp->d_partitions[8+n];

				if (dp[i].dp_typ == DOSPTYP_MIRBSD)
					continue;
				if (get_le(&dp[i].dp_size) > lp->d_secperunit)
					continue;
				if (get_le(&dp[i].dp_size))
					pp->p_size = get_le(&dp[i].dp_size);
				if (get_le(&dp[i].dp_start))
					pp->p_offset =
					    get_le(&dp[i].dp_start);

				switch (dp[i].dp_typ) {
				case DOSPTYP_UNUSED:
					for (cp = (char *)(&dp[i]);
					    cp < (char *)(&dp[i+1]); cp++)
						if (*cp)
							break;
					/*
					 * Was it all zeroes?  If so, it is
					 * an unused entry that we don't
					 * want to show.
					 */
					if (cp == (char *)(&dp[i+1]))
					    continue;
					lp->d_partitions[8 + n++].p_fstype =
					    FS_UNUSED;
					break;

				case DOSPTYP_LINUX:
					pp->p_fstype = FS_EXT2FS;
					n++;
					break;

				case DOSPTYP_FAT12:
				case DOSPTYP_FAT16S:
				case DOSPTYP_FAT16B:
				case DOSPTYP_FAT32:
				case DOSPTYP_FAT32L:
				case DOSPTYP_FAT16L:
					pp->p_fstype = FS_MSDOS;
					n++;
					break;
				case DOSPTYP_NTFS:
					pp->p_fstype = FS_NTFS;
					n++;
					break;
				case DOSPTYP_EXTEND:
				case DOSPTYP_EXTENDL:
				case DOSPTYP_EXTENDLX:
					part_blkno = get_le(&dp[i].dp_start);
#ifdef DEBUG
					printf("debug: wandering, found %X at"
					    " %d (0x%X)\n", dp[i].dp_typ,
					    part_blkno, part_blkno);
#endif
					wander = 1;
					break;
				default:
					pp->p_fstype = FS_OTHER;
					n++;
					break;
				}
			}
		}
 dodospart_someparts:
		lp->d_bbsize = 8192;
		lp->d_sbsize = 64*1024;		/* XXX ? */
		lp->d_npartitions = MAXPARTITIONS;
 dodospart_noparts:
		;
	}

	/* don't read the on-disk label if we are in spoofed-only mode */
	if (spoofonly)
		goto done;

	/* retrieve the PBR, for fun */
	if (dospartoff) {
		bp->b_blkno = dospartoff;
		bp->b_cylinder = cyl;
		bp->b_bcount = lp->d_secsize;
		bp->b_flags = B_BUSY | B_READ;
		(*strat)(bp);
		if (!biowait(bp))
			rnd_lopool_addh(bp->b_data, lp->d_secsize);
	}

	/* next, dig out disk label */
	bp->b_blkno = dospartoff + LABELSECTOR;
	bp->b_cylinder = cyl;
	bp->b_bcount = lp->d_secsize;
	bp->b_flags = B_BUSY | B_READ;
	(*strat)(bp);

	/* if successful, locate disk label within block and validate */
	if (biowait(bp)) {
		/* XXX we return the faked label built so far */
		msg = "disk label I/O error";
		goto done;
	}
	for (dlp = (struct disklabel *)bp->b_data;
	    dlp <= (struct disklabel *)(bp->b_data + lp->d_secsize - sizeof(*dlp));
	    dlp = (struct disklabel *)((char *)dlp + sizeof(long))) {
		if (dlp->d_magic != DISKMAGIC || dlp->d_magic2 != DISKMAGIC) {
			if (msg == NULL)
				msg = "no disk label";
		} else if (dkcksum(dlp) ||
		    dlp->d_npartitions > MAXPARTITIONS ||
		    dlp->d_secpercyl == 0)
			msg = "disk label corrupted";
		else {
			*lp = *dlp;
			msg = NULL;
			break;
		}
	}

	if (msg) {
#if defined(CD9660)
		if (iso_disklabelspoof(dev, strat, lp) == 0)
			msg = NULL;
#endif
		goto done;
	}

	if (lp->d_secsize < DEV_BSIZE) {
		/* retain working sector size */
		lp->d_secsize = d_secsize;
		lp->d_checksum = dkcksum(lp);
	}

	/* obtain bad sector table if requested and present */
	if (bdp && (lp->d_flags & D_BADSECT)) {
		struct dkbad *db;

		i = 0;
		do {
			/* read a bad sector table */
			bp->b_flags = B_BUSY | B_READ;
			bp->b_blkno = lp->d_secperunit - lp->d_nsectors + i;
			if (lp->d_secsize > DEV_BSIZE)
				bp->b_blkno *= lp->d_secsize / DEV_BSIZE;
			else
				bp->b_blkno /= DEV_BSIZE / lp->d_secsize;
			bp->b_bcount = lp->d_secsize;
			bp->b_cylinder = lp->d_ncylinders - 1;
			(*strat)(bp);

			/* if successful, validate, otherwise try another */
			if (biowait(bp)) {
				msg = "bad sector table I/O error";
			} else {
				db = (struct dkbad *)(bp->b_data);
#define DKBAD_MAGIC 0x4321
				if (db->bt_mbz == 0
					&& db->bt_flag == DKBAD_MAGIC) {
					msg = NULL;
					*bdp = *db;
					break;
				} else
					msg = "bad sector table corrupted";
			}
		} while ((bp->b_flags & B_ERROR) && (i += 2) < 10 &&
			i < lp->d_nsectors);
	}

 done:
	if (bp) {
		bp->b_flags |= B_INVAL;
		brelse(bp);
	}
	return (msg);
}

/*
 * Check new disk label for sensibility
 * before setting it.
 */
int
setdisklabel(struct disklabel *olp, struct disklabel *nlp,
    u_long openmask, struct cpu_disklabel *osdep)
{
	int i;
	struct partition *opp, *npp;

	/* sanity clause */
	if (nlp->d_secpercyl == 0 || nlp->d_secsize == 0 ||
	    (nlp->d_secsize % DEV_BSIZE) != 0)
		return(EINVAL);

	/* special case to allow disklabel to be invalidated */
	if (nlp->d_magic == 0xffffffff) {
		*olp = *nlp;
		return (0);
	}

	if (nlp->d_magic != DISKMAGIC || nlp->d_magic2 != DISKMAGIC ||
	    dkcksum(nlp) != 0)
		return (EINVAL);

	/* XXX missing check if other dos partitions will be overwritten */

	while (openmask != 0) {
		i = ffs(openmask) - 1;
		openmask &= ~(1 << i);
		if (nlp->d_npartitions <= i)
			return (EBUSY);
		opp = &olp->d_partitions[i];
		npp = &nlp->d_partitions[i];
		if (npp->p_offset != opp->p_offset || npp->p_size < opp->p_size)
			return (EBUSY);
		/*
		 * Copy internally-set partition information
		 * if new label doesn't include it.		XXX
		 */
		if (npp->p_fstype == FS_UNUSED && opp->p_fstype != FS_UNUSED) {
			npp->p_fstype = opp->p_fstype;
			npp->p_fsize = opp->p_fsize;
			npp->p_frag = opp->p_frag;
			npp->p_cpg = opp->p_cpg;
		}
	}
	nlp->d_checksum = 0;
	nlp->d_checksum = dkcksum(nlp);
	*olp = *nlp;
	return (0);
}


/*
 * Write disk label back to device after modification.
 */
int
writedisklabel(dev_t dev, void (*strat)(struct buf *),
    struct disklabel *lp, struct cpu_disklabel *osdep)
{
	struct dos_partition *dp = osdep->dosparts;
	struct buf *bp;
	struct disklabel *dlp;
	int error, dospartoff, cyl;

	/* get a buffer and initialize it */
	bp = geteblk((int)lp->d_secsize);
	bp->b_dev = dev;

	/* do dos partitions in the process of getting disklabel? */
	dospartoff = DOSBBSECTOR;
	cyl = LABELSECTOR / lp->d_secpercyl;
	if (dp) if (!find_mirbsd_disklabel(strat, bp, lp, dp)) {
		dospartoff = get_le(&dp->dp_start);
		cyl = DPCYL(dp->dp_scyl, dp->dp_ssect);
	}

	/* next, dig out disk label */
	bp->b_blkno = dospartoff + LABELSECTOR;
	bp->b_cylinder = cyl;
	bp->b_bcount = lp->d_secsize;
	bp->b_flags = B_BUSY | B_READ;
	(*strat)(bp);

	/* if successful, locate disk label within block and validate */
	if ((error = biowait(bp)) != 0)
		goto done;
	for (dlp = (struct disklabel *)bp->b_data;
	    dlp <= (struct disklabel *)(bp->b_data + lp->d_secsize - sizeof(*dlp));
	    dlp = (struct disklabel *)((char *)dlp + sizeof(long))) {
		if (dlp->d_magic == DISKMAGIC && dlp->d_magic2 == DISKMAGIC &&
		    dkcksum(dlp) == 0) {
			*dlp = *lp;
			bp->b_flags = B_BUSY | B_WRITE;
			(*strat)(bp);
			error = biowait(bp);
			goto done;
		}
	}

	/* Write it in the regular place. */
	*(struct disklabel *)bp->b_data = *lp;
	bp->b_flags = B_BUSY | B_WRITE;
	(*strat)(bp);
	error = biowait(bp);
	goto done;

 done:
	bp->b_flags |= B_INVAL;
	brelse(bp);
	return (error);
}

/*
 * Determine the size of the transfer, and make sure it is
 * within the boundaries of the partition. Adjust transfer
 * if needed, and signal errors or early completion.
 */
int
bounds_check_with_label(bp, lp, osdep, wlabel)
	struct buf *bp;
	struct disklabel *lp;
	struct cpu_disklabel *osdep;
	int wlabel;
{
#define blockpersec(count, lp) ((count) * (((lp)->d_secsize) / DEV_BSIZE))
	struct partition *p = lp->d_partitions + DISKPART(bp->b_dev);
	int labelsector = blockpersec(lp->d_partitions[RAW_PART].p_offset, lp) +
	    LABELSECTOR;
	int sz = howmany(bp->b_bcount, DEV_BSIZE);

	/* avoid division by zero */
	if (lp->d_secpercyl == 0) {
		bp->b_error = EINVAL;
		goto bad;
	}

	/* beyond partition? */
	if (bp->b_blkno + sz > blockpersec(p->p_size, lp)) {
		sz = blockpersec(p->p_size, lp) - bp->b_blkno;
		if (sz == 0) {
			/* If exactly at end of disk, return EOF. */
			bp->b_resid = bp->b_bcount;
			goto done;
		}
		if (sz < 0) {
			/* If past end of disk, return EINVAL. */
			bp->b_error = EINVAL;
			goto bad;
		}
		/* Otherwise, truncate request. */
		bp->b_bcount = sz << DEV_BSHIFT;
	}

	/* Overwriting disk label? */
	if (bp->b_blkno + blockpersec(p->p_offset, lp) <= labelsector &&
#if LABELSECTOR != 0
	    bp->b_blkno + blockpersec(p->p_offset, lp) + sz > labelsector &&
#endif
	    (bp->b_flags & B_READ) == 0 && !wlabel) {
		bp->b_error = EROFS;
		goto bad;
	}

	/* calculate cylinder for disksort to order transfers with */
	bp->b_cylinder = (bp->b_blkno + blockpersec(p->p_offset, lp)) /
		lp->d_secpercyl;
	return (1);

 bad:
	bp->b_flags |= B_ERROR;
 done:
	return (0);
}
