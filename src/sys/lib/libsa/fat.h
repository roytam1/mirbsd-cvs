/* $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $ */

/*-
 * Copyright (c) 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
 */

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
