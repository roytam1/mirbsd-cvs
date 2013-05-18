/*-
 * Copyright (c) 2005, 2008, 2009
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
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/slibkern.h>
#include <lib/libsa/stand.h>
#include <lib/libsa/fat.h>

__RCSID("$MirOS: src/sys/lib/libsa/fat.c,v 1.15 2009/03/13 20:40:58 tg Exp $");

#if BYTE_ORDER != LITTLE_ENDIAN
#define getlew(ofs) (buf[(ofs)] + ((unsigned)buf[(ofs) + 1] << 8))
#define getled(ofs) (getlew(ofs) + (getlew((ofs) + 2) << 16))
#else
#define getlew(ofs) (*((uint16_t *)(&buf[(ofs)])))
#define getled(ofs) (*((uint32_t *)(&buf[(ofs)])))
#endif

enum fat_type {
	FAT12, FAT16, FAT28
};

struct fat_file {
	struct open_file *open_file;	/* our "parent" structure */
	uint32_t rootofs;		/* root offset (FAT12/FAT16) */
	uint32_t invalc;		/* first invalid cluster no. */
	uint32_t firstds;		/* first data sector */
	char *fatbuf;			/* sector buffer (FAT) */
	uint32_t fatsec;		/* which sector is buffered */
	char *databuf;			/* cluster buffer (data) */
	uint32_t datasec;		/* which cluster is buffered */
	uint32_t nodecluster;		/* current node: cluster */
	uint32_t nodeseekp;		/* current node: file offset */
	uint32_t nodesize;		/* current node: file size */
	uint16_t ress;			/* BPB: reserved sectors */
	uint16_t bpc;			/* BPB: bytes per cluster */
	uint8_t nodetype;		/* 1=directory 2=file */
	enum fat_type type;		/* FAT12, FAT16 or FAT28 */
};

static int rd(struct open_file *, void *, daddr_t, size_t);
static uint32_t getfat(struct fat_file *, uint32_t);
static int search_dir(struct open_file *, char *);

static unsigned char fat_dirbuf[32];

#define fillbuf(ff)	rd((ff)->open_file, (ff)->databuf, \
			    ((ff)->datasec - 2) * ((ff)->bpc / 512) + \
			    (ff)->firstds, (ff)->bpc)
#define locase(c)	(((c) < 'A') || ((c) > 'Z') ? (c) : (c) - 'A' + 'a')

static int
rd(struct open_file *f, void *buf, daddr_t blk, size_t size)
{
	size_t buflen;
	int rv;

	twiddle();
	if ((rv = (f->f_dev->dv_strategy)(f->f_devdata, F_READ,
	    blk, size, buf, &buflen)))
		;
	else if (buflen != size)
		rv = EINVAL;
	return (rv);
}

static uint32_t
getfat(struct fat_file *ff, uint32_t entry)
{
	uint32_t fofs, fsec, secofs, rv = 0, b;
	char *buf;

	b = (ff->type == FAT12) ? 1024 : 512;
	if (ff->fatbuf == NULL) {
		ff->fatbuf = alloc(b);
		ff->fatsec = 0;
	}
	buf = ff->fatbuf;

	fofs = (ff->type == FAT16) ? (entry << 1) :
	    ((ff->type == FAT28) ? (entry << 2) :
	    (entry + (entry / 2)));
	fsec = ff->ress + (fofs / 512);
	secofs = fofs % 512;

	if (fsec != ff->fatsec) {
		if ((rv = rd(ff->open_file, buf, fsec, b))) {
			free(buf, b);
			ff->fatbuf = NULL;
			return (rv | 0x80000000);
		}
		ff->fatsec = fsec;
	}

	switch (ff->type) {
	case FAT28:
		rv = getled(secofs) & 0x0FFFFFFF;
		break;
	case FAT16:
		rv = getlew(secofs);
		break;
	case FAT12:
		rv = getlew(secofs);
		if (entry & 1)
			rv >>= 4;
		else
			rv &= 0x0FFF;
		break;
	}
	return (rv);
}

int
fat_open(char *path, struct open_file *f)
{
	struct fat_file *ff;
	unsigned char *buf;
	int rv;
	uint32_t spc, nfats, rootcnt, spd, spf, dblk;

	/* allocate fs specific data structure */
	ff = alloc(sizeof (struct fat_file));
	bzero(ff, sizeof (struct fat_file));
	f->f_fsdata = ff;
	ff->open_file = f;

	/* allocate space and read BPB */
	buf = alloc(512);
	if ((rv = rd(f, buf, 0, 512)))
		goto out;

	/* parse BPB */
	rv = EINVAL;
	if (((buf[0] != 0xEB) || (buf[2] != 0x90)) && (buf[0] != 0xE9))
		goto out;
	if ((buf[510] != 0x55) || (buf[511] != 0xAA))
		goto out;

	/* only 512 Bytes per sector for now */
	if (getlew(11) != 512)
		goto out;

	spc = buf[13];
	ff->bpc = spc * 512;
	if ((ff->ress = getlew(14)) < 1)
		goto out;
	nfats = buf[16];
	rootcnt = (getlew(17) * 32 + 511) / 512;
	spd = getlew(19);
	spf = getlew(22);
	if (!spd)
		spd = getled(32);
	if (!spf)
		spf = getled(36);
	ff->rootofs = ff->ress + (nfats * spf);
	ff->firstds = ff->rootofs + rootcnt;
	dblk = (spd - ff->firstds) / spc;
	ff->type = (dblk < 4085) ? FAT12 : ((dblk < 65525) ? FAT16 : FAT28);
	switch (ff->type) {
	case FAT12:
		ff->invalc = 0x0FF7;
		break;
	case FAT16:
		ff->invalc = 0xFFF7;
		break;
	case FAT28:
		ff->invalc = 0x0FFFFFF7;
		if ((ff->rootofs = getled(44)) < 2)
			goto out;
		break;
	}

	ff->nodetype = 1;	/* 1 = directory, 2 = file */
	ff->nodecluster = 1;	/* 1 = root directory (special) */
	ff->nodeseekp = 0;
	if (ff->type == FAT28)
		/* we have a real root directory file */
		ff->nodecluster = ff->rootofs;
	else
		ff->nodesize = rootcnt * 512;

	while (*path) {
		char c, *cp, *npath;
		size_t len;

		/* remove extra separators */
		while (*path == '/')
			++path;
		if (*path == '\0')
			break;

		/* check that current node is a directory */
		if (ff->nodetype != 1) {
			rv = ENOTDIR;
			goto out;
		}

		/* get next component of path name */
		len = 0;
		cp = path;
		while (((c = *cp) != '\0') && (c != '/')) {
			if (++len > 14) {
				rv = ENOENT;
				goto out;
			}
			cp++;
		}
		if (cp == path + 1 && *path == '.') {
			path = cp;
			continue;
		}
		npath = cp;
		*cp = '\0';

		/* look up component in current directory */
		rv = search_dir(f, path);
		*cp = c;
		if (rv)
			goto out;
		path = npath;
	}

	/* found terminal component */
	rv = 0;
 out:
	free(buf, 512);
	if (rv) {
		if (ff->fatbuf)
			free(ff->fatbuf, (ff->type == FAT12) ? 1024 : 512);
		if (ff->databuf)
			free(ff->databuf, ff->bpc);
		free(ff, sizeof (struct fat_file));
	}
	return (rv);
}

int
fat_close(struct open_file *f)
{
	struct fat_file *ff;

	if (f == NULL)
		return (0);

	ff = f->f_fsdata;
	if (ff) {
		if (ff->fatbuf)
			free(ff->fatbuf, (ff->type == FAT12) ? 1024 : 512);
		if (ff->databuf)
			free(ff->databuf, ff->bpc);
		free(ff, sizeof (struct fat_file));
	}
	return (0);
}

int
fat_read(struct open_file *f, void *buf, size_t size, size_t *resid)
{
	struct fat_file *ff = f->f_fsdata;
	int rv = 0, otmp, isroot = 0, blksiz = ff->bpc;
	size_t stmp;

	if (!ff->databuf) {
		ff->databuf = alloc(ff->bpc);
		ff->datasec = 0;
	}

	if (ff->nodecluster == 1) {
		isroot = 1;
		blksiz = 512;
	}

	if (ff->datasec == 0) {
		int skip = (ff->nodeseekp / ff->bpc);
		ff->datasec = ff->nodecluster;
		if (ff->datasec == 1) {
			ff->datasec = ff->nodeseekp / 512 + ff->rootofs;
			if ((rv = rd(f, ff->databuf, ff->datasec, 512))) {
				ff->datasec = 0;
				goto out;
			}
			goto filled;
		}
		if ((ff->datasec == 0) || (ff->datasec >= ff->invalc)) {
 invclust:
			ff->datasec = rv = 0;
			goto out;
		}
		while (skip--) {
			ff->datasec = getfat(ff, ff->datasec);
			if ((ff->datasec == 0) || (ff->datasec >= ff->invalc))
				goto invclust;
		}
		if ((rv = fillbuf(ff))) {
 rderr:
			ff->datasec = 0;
			goto out;
		}
	}
 filled:

	while (size > 0) {
		/* don't read beyond EOF */
		if (ff->nodesize && (ff->nodeseekp >= ff->nodesize))
			break;

		otmp = ff->nodeseekp % blksiz;
		stmp = blksiz - otmp;
		if (ff->nodesize && (ff->nodesize - ff->nodeseekp) < stmp)
			stmp = ff->nodesize - ff->nodeseekp;
		if (stmp >= size)
			stmp = size;
		memmove(buf, ff->databuf + otmp, stmp);

		size -= stmp;
		buf += stmp;
		ff->nodeseekp += stmp;

		if (ff->nodeseekp % blksiz == 0) {
			if (isroot) {
				ff->datasec++;
				if ((rv = rd(f, ff->databuf, ff->datasec, 512)))
					goto rderr;
				goto refilled;
			}
			ff->datasec = getfat(ff, ff->datasec);
			if ((ff->datasec >= ff->invalc) || (rv = fillbuf(ff)))
				ff->datasec = 0;
			if (ff->datasec == 0 && size)
				goto out;
 refilled:		;
 		}
	}
 out:
	if (resid)
		*resid = size;
	return (rv);
}

int
fat_write(struct open_file *f, void *buf, size_t size, size_t *resid)
{
	return (EROFS);
}

off_t
fat_seek(struct open_file *f, off_t offset, int where)
{
	switch (where) {
	case SEEK_SET:
		((struct fat_file *)f->f_fsdata)->nodeseekp = offset;
		break;
	case SEEK_CUR:
		((struct fat_file *)f->f_fsdata)->nodeseekp += offset;
		break;
	case SEEK_END:
		((struct fat_file *)f->f_fsdata)->nodeseekp =
		    ((struct fat_file *)f->f_fsdata)->nodesize + offset;
		break;
	default:
		return (-1);
	}
	/* invalidate file data buffer */
	((struct fat_file *)f->f_fsdata)->datasec = 0;
	return (((struct fat_file *)f->f_fsdata)->nodeseekp);
}

int
fat_stat(struct open_file *f, struct stat *sb)
{
	/* quick and dirty */
	bzero(sb, sizeof (struct stat));
	sb->st_mode = (((struct fat_file *)f->f_fsdata)->nodetype == 1) ?
	    040555 : 0444;
	sb->st_size = ((struct fat_file *)f->f_fsdata)->nodesize;

	return (0);
}

int
fat_readdir(struct open_file *f, char *name)
{
	int rv;
	char ch, *cp;
	size_t sr;

	/* reset? */
	if (name == NULL) {
		fat_seek(f, 0, SEEK_SET);
		return (0);
	}

	*name = '\0';
 getrec:
	if ((rv = fat_read(f, fat_dirbuf, sizeof (fat_dirbuf), &sr)))
		return (rv);
	if (sr)
		return (EIO);
	/* end of directory? */
	if (fat_dirbuf[0] == 0)
		return (ENOENT);
	/* deleted file? */
	if (fat_dirbuf[0] == 0xE5)
		goto getrec;
	/* part of long filename? */
	if ((fat_dirbuf[11] & 0x3F) == 0x0F)
		goto getrec;
	/* volume label or FCFS symlink? */
	if ((fat_dirbuf[11] & 0xC8))
		goto getrec;
	/* okay, we have a directory or regular file */
	cp = fat_dirbuf;
	rv = 0;
	while (*cp != 0x20) {
		ch = *cp++;
		*name++ = locase(ch);
		if (++rv == 8)
			break;
	}
	cp = fat_dirbuf + 8;
	if (*cp != 0x20)
		*name++ = '.';
	rv = 0;
	while (*cp != 0x20) {
		ch = *cp++;
		*name++ = locase(ch);
		if (++rv == 3)
			break;
	}
	*name++ = '\0';

	return (0);
}

static int
search_dir(struct open_file *f, char *name)
{
	struct fat_file *ff = f->f_fsdata;
	int rv;
	char fn[14];
	char *buf = fat_dirbuf;

	if ((rv = fat_readdir(f, NULL)))
		return (rv);
	while ((rv = fat_readdir(f, fn)) == 0)
		if (!strcmp(fn, name)) {
			/* found a match, follow it */
			ff->nodecluster = getlew(20) << 16 | getlew(26);
			ff->nodesize = getled(28);
			if (ff->nodecluster < 2 && ff->nodesize != 0)
				return (ENOENT);
			ff->nodeseekp = 0;
			ff->nodetype = (buf[11] & 0x10) ? 1 : 2;
			/* invalidate file data buffer */
			ff->datasec = 0;
			return (0);
		}
	return (ENOENT);
}
