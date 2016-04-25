/*-
 * Copyright (c) 2009, 2016
 *	mirabilos <m@mirbsd.org>
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
#include <lib/libsa/lmbmfs.h>

/*#define LMBMFS_DEBUG*/

__RCSID("$MirOS: src/sys/lib/libsa/lmbmfs.c,v 1.5 2010/01/10 17:47:52 tg Exp $");

extern struct lmbm_modinfo {
	void *mod_start;
	void *mod_end;
	char *mod_string;
	void *mod_reserved;
} *lmbm_ofs;

static struct lmbm_item {
	char *name;
	char *data;
	size_t size;
} *allitems;

struct lmbmfs_file {
	struct open_file *open_file;	/* our "parent" structure */
	struct lmbm_item *item;
	size_t nodeseekp;		/* current node: file offset */
};

/**
 * We need to move the modules passed to us by the Multiboot loader
 * out of the way. We just assume that, when we are loaded by a
 * Multiboot bootloader and be passed modules, that the modules are
 * loaded past us (so at a little above 1 MiB in RAM), and that the
 * area from 20 MiB in RAM and up is unused, and that the kernel is
 * loaded below that (MirBSD kernels are currently loaded to a lit-
 * tle past 1 MiB; recent OpenBSD kernels a little past 2 MiB).
 */

/* where modules are moved to */
#define STARTADDR	((char *)(20 * 1048576))

int
lmbmfs_init(void)
{
	uint32_t i = lmbm_num;
	char *dstaddr = STARTADDR;
	static int initialised = 0;

	if (!lmbm_num)
		return (ENXIO);
	if (initialised)
		goto init_ok;
	initialised = 1;

	allitems = alloc(lmbm_num * sizeof(struct lmbm_item));

#ifdef LMBMFS_DEBUG
	printf(" lmbm...\n");
#endif
	for (i = 0; i < lmbm_num; ++i) {
		char *cp, *bp;

		bp = cp = lmbm_ofs[i].mod_string;
#ifdef LMBMFS_DEBUG
		printf("\t%X: '%s' ", i, cp);
#endif
		while (*cp && *cp != ' ')
			if (*cp++ == '/')
				bp = cp;
		*cp = '\0';
		if (cp++ - bp) {
			allitems[i].name = alloc(cp - bp);
			memcpy(allitems[i].name, bp, cp - bp);
		} else {
			allitems[i].name = alloc(8);
			snprintf(allitems[i].name, 8, "%X", i);
		}
		allitems[i].data = dstaddr;
		allitems[i].size = lmbm_ofs[i].mod_end - lmbm_ofs[i].mod_start;
#ifdef LMBMFS_DEBUG
		printf("%s(%lu)\n", allitems[i].name, (u_long)allitems[i].size);
#endif
		memcpy(dstaddr, lmbm_ofs[i].mod_start, allitems[i].size);
		dstaddr += allitems[i].size;
	}
 init_ok:
	printf(" lmbm(%u=%u bytes)", i, dstaddr - STARTADDR);
	return (0);
}


int
lmbmfs_open(char *path, struct open_file *f)
{
	struct lmbmfs_file *ff;
	char *bp = path, *cp = path;
	uint32_t i = 0;

	twiddle();
	/* find file */
	while (*cp)
		if (*cp++ == '/')
			bp = cp;
	if (!*bp || !strcmp(bp, "."))
		bp = NULL;
	if (bp) {
		/* not the (root) directory */

		while (i < lmbm_num) {
			twiddle();
			if (!strcmp(bp, allitems[i].name))
				break;
			else
				++i;
		}
		if (i == lmbm_num)
			return (ENOENT);
	}

	/* allocate fs specific data structure */
	ff = alloc(sizeof(struct lmbmfs_file));
	f->f_fsdata = ff;
	ff->open_file = f;
	ff->item = bp ? &allitems[i] : NULL;
	ff->nodeseekp = 0;

	return (0);
}

int
lmbmfs_close(struct open_file *f)
{
	if (f)
		free(f->f_fsdata, sizeof(struct lmbmfs_file));

	return (0);
}

int
lmbmfs_read(struct open_file *f, void *buf, size_t size, size_t *resid)
{
	struct lmbmfs_file *ff = f->f_fsdata;
	size_t n;

	if (!ff->item)
		return (EISDIR);

	twiddle();
	if (ff->nodeseekp >= ff->item->size)
		n = 0;
	else if ((n = ff->item->size - ff->nodeseekp) > size)
		n = size;
	if (n) {
		memcpy(buf, ff->item->data + ff->nodeseekp, n);
		ff->nodeseekp += n;
	}
	if (resid)
		*resid = size - n;
	return (0);
}

int
lmbmfs_write(struct open_file *f, void *buf, size_t size, size_t *resid)
{
	return (EROFS);
}

off_t
lmbmfs_seek(struct open_file *f, off_t offset, int where)
{
	if (!((struct lmbmfs_file *)f->f_fsdata)->item)
		return (EISDIR);

	switch (where) {
	case SEEK_SET:
		((struct lmbmfs_file *)f->f_fsdata)->nodeseekp = offset;
		break;
	case SEEK_CUR:
		((struct lmbmfs_file *)f->f_fsdata)->nodeseekp += offset;
		break;
	case SEEK_END:
		((struct lmbmfs_file *)f->f_fsdata)->nodeseekp =
		    ((struct lmbmfs_file *)f->f_fsdata)->item->size + offset;
		break;
	default:
		return (-1);
	}
	return (((struct lmbmfs_file *)f->f_fsdata)->nodeseekp);
}

int
lmbmfs_stat(struct open_file *f, struct stat *sb)
{
	/* quick and dirty */
	bzero(sb, sizeof(struct stat));
	if (((struct lmbmfs_file *)f->f_fsdata)->item == NULL) {
		sb->st_mode = 040555;
		sb->st_size = 1;
	} else {
		sb->st_mode = 0444;
		sb->st_size = ((struct lmbmfs_file *)f->f_fsdata)->item->size;
	}

	return (0);
}

int
lmbmfs_readdir(struct open_file *f, char *name)
{
	struct lmbmfs_file *ff = f->f_fsdata;

	if (ff->item)
		return (ENOTDIR);

	/* reset? */
	if (name == NULL) {
		ff->nodeseekp = 0;
		return (0);
	}

	if (ff->nodeseekp == lmbm_num) {
		*name = '\0';
		return (ENOENT);
	}
	strlcpy(name, allitems[ff->nodeseekp++].name, PATH_MAX);
	return (0);
}
