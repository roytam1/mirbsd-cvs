/* $MirOS: src/sys/lib/libsa/lmbmfs.h,v 1.2 2009/08/11 13:24:00 tg Exp $ */

#ifndef _SYS_LIB_LIBSA_DUMMYDEV_H
#define _SYS_LIB_LIBSA_DUMMYDEV_H

int dummydev_strategy(void *, int, daddr_t, size_t, void *, size_t *);
int dummydev_open(struct open_file *, ...);
int dummydev_close(struct open_file *);
int dummydev_ioctl(struct open_file *, u_long, void *);

#endif
