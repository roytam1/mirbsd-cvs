/* $MirOS: src/sys/lib/libsa/ustarfs.h,v 1.1 2010/01/10 19:21:38 tg Exp $ */

#ifndef _SYS_LIB_LIBSA_USTARFS_H
#define _SYS_LIB_LIBSA_USTARFS_H

/* ustarfs: offset of ustar archive from begin of filesystem */
#ifdef __sparc__
#define USTARFS_FIRSTSEC	1
#else
#define USTARFS_FIRSTSEC	0
#endif

int ustarfs_open(char *, struct open_file *);
int ustarfs_close(struct open_file *);
int ustarfs_read(struct open_file *, void *, size_t, size_t *);
int ustarfs_write(struct open_file *, void *, size_t, size_t *);
off_t ustarfs_seek(struct open_file *, off_t, int);
int ustarfs_stat(struct open_file *, struct stat *);
int ustarfs_readdir(struct open_file *, char *);

#endif
