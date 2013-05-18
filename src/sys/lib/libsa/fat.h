/* $MirOS: src/sys/lib/libsa/fat.h,v 1.1 2005/08/07 15:37:42 tg Exp $ */

#ifndef _SYS_LIB_LIBSA_FAT_H
#define _SYS_LIB_LIBSA_FAT_H

int fat_open(char *, struct open_file *);
int fat_close(struct open_file *);
int fat_read(struct open_file *, void *, size_t, size_t *);
int fat_write(struct open_file *, void *, size_t, size_t *);
off_t fat_seek(struct open_file *, off_t, int);
int fat_stat(struct open_file *, struct stat *);
int fat_readdir(struct open_file *, char *);

#endif
