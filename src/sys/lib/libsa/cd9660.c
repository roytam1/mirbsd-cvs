/*-
 * Copyright (c) 2009
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
#include <lib/libsa/cd9660.h>
#include <isofs/cd9660/iso.h>

__RCSID("$MirOS: src/sys/lib/libsa/fat.c,v 1.14 2009/01/15 21:42:50 tg Exp $");

struct cd9660_file {
	struct open_file *open_file;	/* our "parent" structure */
	char databuf[2048];		/* sector buffer (data) */
	uint32_t datasec;		/* which sector is buffered */
	uint32_t nodecluster;		/* current node: sector */
	uint32_t nodeseekp;		/* current node: file offset */
	uint32_t nodesize;		/* current node: file size */
	uint8_t nodetype;		/* 1=directory 2=file */
};

static int fillbuf(struct cd9660_file *);
static int fillofs(struct cd9660_file *);
static int search_dir(struct open_file *, char *);

#define locase(c)	(((c) < 'A') || ((c) > 'Z') ? (c) : (c) - 'A' + 'a')

static int
fillofs(struct cd9660_file *ff)
{
	uint32_t sn;

	sn = ff->nodeseekp >> 11;
	if (sn == ff->datasec)
		return (0);
	ff->datasec = sn;
	return (fillbuf(ff));
}

static int
fillbuf(struct cd9660_file *ff)
{
	size_t buflen;
	int rv;

	twiddle();
	if ((rv = (ff->open_file->f_dev->dv_strategy)(ff->open_file->f_devdata,
	    F_READ, ff->datasec * (2048 / 512), 2048, ff->databuf, &buflen)))
		;
	else if (buflen != 2048)
		rv = EINVAL;
	return (rv);
}

int
cd9660_open(char *path, struct open_file *f)
{
	struct cd9660_file *ff;
	int rv;
	struct iso_directory_record *dp;
#define vd ((struct iso_primary_descriptor *)(ff->databuf))

	/* allocate fs specific data structure */
	ff = alloc(sizeof (struct cd9660_file));
	bzero(ff, sizeof (struct cd9660_file));
	f->f_fsdata = ff;
	ff->open_file = f;

	/* search for PVD */
	ff->datasec = 16;
 search_pvd:
	if ((rv = fillbuf(ff)))
		goto out;

	/* parse VD */
	rv = EINVAL;
	if (bcmp(vd->id, ISO_STANDARD_ID, sizeof (vd->id)))
		goto out;
	switch (isonum_711(vd->type)) {
	case ISO_VD_END:
		goto out;
	case ISO_VD_PRIMARY:
		break;
	default:
		++ff->datasec;
		goto search_pvd;
	}
	if (isonum_723(vd->logical_block_size) != 2048)
		goto out;
	dp = (struct iso_directory_record *)vd->root_directory_record;
	ff->nodetype = 1;	/* 1 = directory, 2 = file */
	ff->nodecluster = isonum_733(dp->extent);
	ff->nodeseekp = 0;
	ff->nodesize = isonum_733(dp->size);
#undef vd

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
	if (rv) {
		free(ff, sizeof (struct cd9660_file));
	}
	return (rv);
}

int
cd9660_close(struct open_file *f)
{
	struct cd9660_file *ff;

	if (f == NULL)
		return (0);

	ff = f->f_fsdata;
	if (ff) {
		if (ff->cd9660buf)
			free(ff->cd9660buf, (ff->type == FAT12) ? 1024 : 512);
		if (ff->databuf)
			free(ff->databuf, ff->bpc);
		free(ff, sizeof (struct cd9660_file));
	}
	return (0);
}

int
cd9660_read(struct open_file *f, void *buf, size_t size, size_t *resid)
{
	struct cd9660_file *ff = f->f_fsdata;
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
			ff->datasec = getcd9660(ff, ff->datasec);
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
			ff->datasec = getcd9660(ff, ff->datasec);
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
cd9660_write(struct open_file *f, void *buf, size_t size, size_t *resid)
{
	return (EROFS);
}

off_t
cd9660_seek(struct open_file *f, off_t offset, int where)
{
	switch (where) {
	case SEEK_SET:
		((struct cd9660_file *)f->f_fsdata)->nodeseekp = offset;
		break;
	case SEEK_CUR:
		((struct cd9660_file *)f->f_fsdata)->nodeseekp += offset;
		break;
	case SEEK_END:
		((struct cd9660_file *)f->f_fsdata)->nodeseekp =
		    ((struct cd9660_file *)f->f_fsdata)->nodesize - offset;
		break;
	default:
		return (-1);
	}
	/* invalidate file data buffer */
	((struct cd9660_file *)f->f_fsdata)->datasec = 0;
	return (((struct cd9660_file *)f->f_fsdata)->nodeseekp);
}

int
cd9660_stat(struct open_file *f, struct stat *sb)
{
	/* quick and dirty */
	bzero(sb, sizeof (struct stat));
	sb->st_mode = (((struct cd9660_file *)f->f_fsdata)->nodetype == 1) ?
	    040555 : 0444;
	sb->st_size = ((struct cd9660_file *)f->f_fsdata)->nodesize;

	return (0);
}

int
cd9660_readdir(struct open_file *f, char *name)
{
	int rv, namelen;
	char ch, *cp;
	size_t sr;
	struct cd9660_file *ff = f->f_fsdata;
	struct iso_directory_record *dp;

	/* reset? */
	if (name == NULL) {
		cd9660_seek(f, 0, SEEK_SET);
		return (0);
	}

 getrec:
	if (ff->nodeseekp >= ff->nodesize) {
		rv = ENOENT;
		goto out;
	}
	if ((rv = fillofs(ff))) {
 out:
		*name = '\0';
		return (rv);
	}
	dp = (struct iso_directory_record *)(ff->databuf +
	    (ff->nodeseekp % 2048));
	if (!isonum_711(dp->length)) {
		++ff->nodeseekp;
		goto getrec;
	}

	if (dp->flags[0] & 4)
		goto skiprec;
	if (!(namelen = isonum_711(dp->name_len)) || namelen > 37)
		goto skiprec;
	memcpy(name, dp->name, namelen);
	name[namelen] = '\0';
	if (isdigit(*(cp = name + strlen(name) - 1))) {
		while (isdigit(*cp))
			if (--cp < name)
				break;
		if (cp > name && *cp == ';')
			*cp = '\0';
	}
	if (*(cp = name + strlen(name) - 1) == '.')
		*cp = '\0';

	/* okay, we have a directory or regular file */
	cp = name;
	while ((ch = *cp))
		*cp++ = locase(ch);//XXX
	rv = 0;
	do {
		ch = *cp++;
		name[rv++] = locase(ch);
	} while (cp);

	return (0);

 skiprec:
	ff->nodeseekp += isonum_711(dp->length);
	goto getrec;
}

static int
search_dir(struct open_file *f, char *name)
{
	struct cd9660_file *ff = f->f_fsdata;
	int rv;
	char fn[38];
	struct iso_directory_record *dp;

	if ((rv = cd9660_readdir(f, NULL)))
		return (rv);
	while ((rv = cd9660_readdir(f, fn)) == 0)
		if (!strcmp(fn, name)) {
			/* found a match, follow it */
			dp = (struct iso_directory_record *)(ff->databuf +
			    (ff->nodeseekp % 2048));
			ff->nodecluster = isonum_733(dp->extent);
			ff->nodesize = isonum_733(dp->size);
			ff->nodeseekp = 0;
			ff->nodetype = (dp->flags[0] & 2) ? 1 : 2;
			/* invalidate file data buffer */
			ff->datasec = 0;
			return (0);
		}
	return (ENOENT);
}
