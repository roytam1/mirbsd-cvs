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

#ifndef ZOPEN_H
#define ZOPEN_H

#ifndef __SCCSID
#define __SCCSID(x)	/* nothing */
#endif

struct z_info {
	u_int64_t total_in;	/* # bytes in */
	u_int64_t total_out;	/* # bytes out */
	u_int32_t crc;		/* crc */
	u_int32_t hlen;		/* header length */
	time_t mtime;		/* timestamp */
};

__BEGIN_DECLS
extern void *z_open(int, const char *, char *, int, uint32_t, int);
extern FILE *zopen(const char *, const char *,int);
extern int zread(void *, char *, int);
extern int zwrite(void *, const char *, int);
extern int z_close(void *, struct z_info *);
__END_DECLS

#endif
