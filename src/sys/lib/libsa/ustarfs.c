/*-
 * Copyright (c) 2010
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
#include <lib/libsa/ustar.h>
#include <lib/libsa/ustarfs.h>

__RCSID("$MirOS: src/sys/lib/libsa/ustarfs.c,v 1.2 2010/01/16 19:25:22 tg Exp $");

/* This is intentionally simple. We don’t support directories. */

struct ustarfs_file {
	struct open_file *open_file;	/* our "parent" structure */
	struct stat sb;			/* file properties */
	uint32_t sector;		/* header sector */
#define SEC_VDIR ((uint32_t)-1)
	uint32_t nodeseekp;		/* current file offset */
};

#undef DEBUG
#ifdef DEBUG
char assertion_size__ustar_hdr_t[sizeof(ustar_hdr_t) == 512 ? 1 : -1];
/* #define D(fmt, ...)	printf("D: %s[%u]:%s: " fmt "\n", __FILE__, __LINE__, \
			    __func__, ## __VA_ARGS__) */
#define D(fmt, ...)	printf("D: [%u]:%s: " fmt "\n", __LINE__, \
			    __func__, ## __VA_ARGS__)
#else
#define D(fmt, ...)	/* nothing */
#endif

#ifdef __i386__
extern uint8_t bounce_buf[4096];
#else
uint8_t bounce_buf[1536];
#endif
static ustar_hdr_t *hp = (ustar_hdr_t *)bounce_buf;
#define ISAFILE()	(!hp->typeflag || hp->typeflag == '0' || \
			    hp->typeflag == '7')
#define ISALINK()	(hp->typeflag == '1')
#define UNOCT(x)	unoct((x), sizeof(x))

static int rd(struct open_file *, uint32_t);
static int ustar_check(int);
static int ustar_cmpfn(const char *);
static int ustar_search(struct ustarfs_file *, const char *);
static void ustar_fillsb(struct ustarfs_file *);
static uint32_t unoct(char *, size_t);
static char *fn_normalise(const char *, const char *);


/* low-level helper routine to load one sector from disc */
static int
rd(struct open_file *f, uint32_t blk)
{
	size_t buflen;
	int rv;

	twiddle();
	D("block %u", blk);
	if ((rv = (f->f_dev->dv_strategy)(f->f_devdata, F_READ,
	    blk, 512, (void *)hp, &buflen)))
		D("error code %u", rv);
	else if (buflen != 512) {
		D("short read %u", (unsigned)buflen);
		rv = EIO;
	}
	return (rv);
}

/* low-level routine to check a loaded sector for ustar */
int
ustar_check(int chk_typeflag)
{
	ustar_hdr_t *h2 = hp + 1;
	uint32_t sum = 0, i = 0;
	int rv = 1;

	if (memcmp((char *)hp + offsetof(ustar_hdr_t, magic),
	    ustar_magic_version, sizeof(ustar_magic_version)))
		goto out;
	if (chk_typeflag) {
		if (hp->typeflag && (hp->typeflag < '0' || hp->typeflag > '7'))
			goto out;
	}
	memcpy(h2, hp, 512);
	memset(h2->chksum, ' ', sizeof(h2->chksum));
	while (i < 512)
		sum += ((unsigned char *)h2)[i++];
	if (sum != UNOCT(hp->chksum))
		goto out;
	rv = 0;
 out:
	D("rv = %d", rv);
	return (rv);
}

uint32_t
unoct(char *s, size_t n)
{
	uint32_t rv = 0;
	size_t i = 0;

	while (i < n && s[i] && s[i] != ' ') {
		if (s[i] < '0' || s[i] > '7')
			return ((uint32_t)-1);
		rv = (rv << 3) | (s[i++] & 7);
	}
	return (rv);
}

static char *
fn_normalise(const char *p1, const char *p2)
{
	char *rv, *buf = (char *)(void *)(hp + 1);
	size_t n = 0, i = 260;

	D("s1=%s%s%s s2='%s'", p1 ? "'" : "", p1 ? p1 : "(null)",
	    p1 ? "'" : "", p2);

	/* construct filename at [buf+260;buf+1024[ and NUL-terminate */
	buf[260] = '/';
	if (p1 == NULL) {
		/* external filename */
		strlcpy(buf + 261, p2, 1024 - 261);
	} else {
		if (*p1) {
			/* ustar header prefix */
			memcpy(buf + 261, p1, 155);
			buf[261 + 155] = '\0';
		} else
			/* empty string */
			buf[261] = '\0';
		/* ustar header name or linkname */
		memcpy(buf + 600, p2, 100);
		buf[600 + 100] = '\0';
		strlcat(buf + 261, "/", 512);
		strlcat(buf + 261, buf + 600, 512);
	}
	/* D("s1+s2='%s'", buf + 260); */

	/* normalise filename from buf+261 to [buf+1;buf+257] */
	/* buf[0] will always contain a slash from buf[260] */
 expect_slash:
	while (buf[i] == '/')
		i++;
	if (!buf[i])
		goto got_NUL;
	buf[n++] = '/';
 expect_nonslash:
	if (n == 257)		/* overflow check */
		goto got_NUL;
	if (buf[i] == '/')
		goto expect_slash;
	else if (buf[i]) {
		buf[n++] = buf[i++];
		goto expect_nonslash;
	}
 got_NUL:
	buf[n++] = '\0';

	rv = alloc(n);
	memcpy(rv, buf, n);
	D("rv = '%s'", rv);
	return (rv);
}

static int
ustar_search(struct ustarfs_file *ff, const char *ofn)
{
	uint32_t i;
	int rv, lastwasNUL = 0;

	D("@%u, ofn=%s%s%s", ff->sector, ofn ? "'" : "",
	    ofn ? ofn : "(null)", ofn ? "'" : "");

	if (ff->sector == SEC_VDIR) {
		/* search from start */
		ff->sector = USTARFS_FIRSTSEC;
		goto loadsec;
	}

 skipdata:
	/* skip data sectors, if any */
	if (ISAFILE())
		ff->sector += (UNOCT(hp->size) + 511) / 512;
 skiphdr:
	/* skip (current sector) ustar header block */
	ff->sector++;

 loadsec:
	/* load next (hopefully) ustar header block */
	if ((rv = rd(ff->open_file, ff->sector))) {
		D("I/O error %d", rv);
		return (rv);
	}

	/* check for header (or end of such) */
	if (ustar_check(1)) {
		/* check for end of archive */
		for (i = 0; i < 512; ++i)
			if (((char *)(void *)hp)[i])
				break;
		if (i == 512) {
			/* sector was all NULs */
			if (lastwasNUL++) {
				D("end of archive");
				return (ENOENT);
			}
		} else
			/* sector was not all NULs */
			lastwasNUL = 0;
		goto skiphdr;
	}
	/* sector contains a valid and known ustar header */
	lastwasNUL = 0;

	if (ofn && ustar_cmpfn(ofn))
		/* filename does not match expectations */
		goto skipdata;

	/* found ustar header which, if given, matches filename */
	D("found");
	return (0);
}

static int
ustar_cmpfn(const char *ofn)
{
	char *hfn;
	int rv = 0;

	hfn = fn_normalise(hp->prefix, hp->name);
	D("ofn '%s' with hfn '%s'", ofn, hfn);
	if (strcmp(ofn, hfn))
		rv = 1;
	free(hfn, strlen(hfn) + 1);
	return (rv);
}

static void
ustar_fillsb(struct ustarfs_file *ff)
{
	bzero(&ff->sb, sizeof(ff->sb));

	ff->sb.st_mode = UNOCT(hp->mode);
	ff->sb.st_uid = UNOCT(hp->uid);
	ff->sb.st_gid = UNOCT(hp->gid);
#if 0
	ff->sb.st_rdev = makedev(UNOCT(hp->devmajor), UNOCT(hp->devminor));
	ff->sb.st_mtime = UNOCT(hp->mtime);
#endif
	if (ISAFILE())
		ff->sb.st_size = UNOCT(hp->size);
}

int
ustarfs_open(char *path, struct open_file *f)
{
	int rv = 0;
	struct ustarfs_file *ff;

	D("path='%s'", path);
	if (path[0] == '/' && path[1] == '.' && path[2] == '/')
		path += 3;

	/* check first sector for valid ustar header */
	if ((rv = rd(f, USTARFS_FIRSTSEC)) || ustar_check(0))
		return (rv ? rv : EUNLAB);

	/* allocate fs specific data structure */
	ff = alloc(sizeof(struct ustarfs_file));
	bzero(ff, sizeof(struct ustarfs_file));
	f->f_fsdata = ff;
	ff->open_file = f;

	/* check if we want “the directory” (e.g. for “ls”) */
	if (!path[0] || (path[0] == '/' && (!path[1] ||
	    (path[1] == '.' && !path[2])))) {
		/* “” or “/” or “/.” */
		ff->sector = SEC_VDIR;
		ff->nodeseekp = SEC_VDIR;
		D("got directory");
		return (0);
	}

	path = fn_normalise(NULL, path);
	ff->sector = USTARFS_FIRSTSEC;
	ff->nodeseekp = 0;
	if (ustar_cmpfn(path)) {
 do_search:
		rv = ustar_search(ff, path);
	}
	if (rv) {
		D("cannot find, error %d", rv);
		free(ff, sizeof(struct ustarfs_file));
	} else if (ISALINK()) {
		D("got link, redoing");
		free(path, strlen(path) + 1);
		path = fn_normalise("", hp->linkname);
		/* redo from start */
		ff->sector = SEC_VDIR;
		goto do_search;
	} else
		ustar_fillsb(ff);
	free(path, strlen(path) + 1);
	D("success");
	return (rv);
}

int
ustarfs_close(struct open_file *f)
{
	struct ustarfs_file *ff;

	if (f == NULL)
		return (0);

	ff = f->f_fsdata;
	if (ff) {
		free(ff, sizeof(struct ustarfs_file));
	}
	return (0);
}

int
ustarfs_read(struct open_file *f, void *buf, size_t size, size_t *resid)
{
	struct ustarfs_file *ff = f->f_fsdata;
	uint32_t datasec, dataofs, n;
	int rv = 0;

	D("%u @ %u", (unsigned)size, ff->nodeseekp);

	/* are we at or past EOF already? */
	if (ff->nodeseekp >= ff->sb.st_size)
		goto out;

	datasec = ff->sector + 1 + (ff->nodeseekp / 512);
	dataofs = ff->nodeseekp & 511;

	/* remaining octets in the sector */
	n = 512 - dataofs;

	/* amount we actually want to read */
	if (n > size)
		n = size;

	/* bounds check against file size */
	if (ff->nodeseekp + n > ff->sb.st_size)
		n = ff->sb.st_size - ff->nodeseekp;

	/* n is now amount of bytes we actually CAN read from one sector */

	/* try to read the sector we’re in */
	if ((rv = rd(ff->open_file, datasec)))
		goto out;

	/* copy (part) of the sector */
	memcpy(buf, ((char *)hp) + dataofs, n);
	ff->nodeseekp += n;
	size -= n;
	D("success, read %u bytes", n);

 out:
	if (resid)
		*resid = size;
	return (rv);
}

int
ustarfs_write(struct open_file *f, void *buf, size_t size, size_t *resid)
{
	return (EROFS);
}

off_t
ustarfs_seek(struct open_file *f, off_t offset, int where)
{
	struct ustarfs_file *ff = f->f_fsdata;

	if (ff->sector == SEC_VDIR) {
		if (where == SEEK_SET && offset == 0) {
			ff->nodeseekp = SEC_VDIR;
			return (0);
		}
		return (-1);
	}

	switch (where) {
	case SEEK_SET:
		ff->nodeseekp = offset;
		break;
	case SEEK_CUR:
		ff->nodeseekp += offset;
		break;
	case SEEK_END:
		ff->nodeseekp = ff->sb.st_size + offset;
		break;
	default:
		return (-1);
	}
	return (ff->nodeseekp);
}

int
ustarfs_stat(struct open_file *f, struct stat *sb)
{
	struct ustarfs_file *ff = f->f_fsdata;

	if (ff->sector == SEC_VDIR) {
		/* quick and dirty */
		bzero(sb, sizeof(struct stat));
		sb->st_mode = 040555;
	} else
		memcpy(sb, &ff->sb, sizeof(struct stat));

	return (0);
}

int
ustarfs_readdir(struct open_file *f, char *name)
{
	struct ustarfs_file *ff = f->f_fsdata;
	int rv;

	if (ff->sector != SEC_VDIR)
		return (EINVAL);

	/* reset? */
	if (name == NULL) {
		ff->nodeseekp = SEC_VDIR;
		return (0);
	}

	ff->sector = ff->nodeseekp;
	if (ff->sector != SEC_VDIR)
		if ((rv = rd(ff->open_file, ff->sector)))
			goto oops;
	rv = ustar_search(ff, NULL);
 oops:
	ff->nodeseekp = ff->sector;
	ff->sector = SEC_VDIR;

	if (!rv) {
		char *fn;

		fn = fn_normalise(hp->prefix, hp->name);
		memcpy(name, fn, strlen(fn) + 1);
		free(fn, strlen(fn) + 1);
	} else
		*name = '\0';

	return (rv);
}
