/* $MirOS: src/sys/lib/libsa/fat.h,v 1.2 2005/12/17 05:46:26 tg Exp $ */

#ifndef _SYS_LIB_LIBSA_CD9660_H
#define _SYS_LIB_LIBSA_CD9660_H

int cd9660_open(char *, struct open_file *);
int cd9660_close(struct open_file *);
int cd9660_read(struct open_file *, void *, size_t, size_t *);
int cd9660_write(struct open_file *, void *, size_t, size_t *);
off_t cd9660_seek(struct open_file *, off_t, int);
int cd9660_stat(struct open_file *, struct stat *);
int cd9660_readdir(struct open_file *, char *);

#endif
