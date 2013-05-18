/* $MirOS: src/sys/lib/libsa/lmbmfs.h,v 1.2 2009/08/11 13:24:00 tg Exp $ */

#ifndef _SYS_LIB_LIBSA_LMBMFS_H
#define _SYS_LIB_LIBSA_LMBMFS_H

struct lmbm_modinfo;

int lmbmfs_open(char *, struct open_file *);
int lmbmfs_close(struct open_file *);
int lmbmfs_read(struct open_file *, void *, size_t, size_t *);
int lmbmfs_write(struct open_file *, void *, size_t, size_t *);
off_t lmbmfs_seek(struct open_file *, off_t, int);
int lmbmfs_stat(struct open_file *, struct stat *);
int lmbmfs_readdir(struct open_file *, char *);

int lmbmfs_init(void);

extern uint32_t lmbm_num;

#endif
