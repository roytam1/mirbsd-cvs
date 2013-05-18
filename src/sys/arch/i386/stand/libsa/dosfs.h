/* $MirOS: src/sys/lib/libsa/lmbmfs.h,v 1.2 2009/08/11 13:24:00 tg Exp $ */

#ifndef _SYS_ARCH_I386_STAND_LIBSA_DOSFS_H
#define _SYS_ARCH_I386_STAND_LIBSA_DOSFS_H

int dosfs_open(char *, struct open_file *);
int dosfs_close(struct open_file *);
int dosfs_read(struct open_file *, void *, size_t, size_t *);
int dosfs_write(struct open_file *, void *, size_t, size_t *);
off_t dosfs_seek(struct open_file *, off_t, int);
int dosfs_stat(struct open_file *, struct stat *);
int dosfs_readdir(struct open_file *, char *);

int dosfs_init(void);

#endif
