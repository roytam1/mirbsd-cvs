/* $MirOS: contrib/hosted/fwcf/pack.h,v 1.2 2006/09/16 03:51:06 tg Exp $ */

/*
 * This file is part of the FreeWRT project. FreeWRT is copyrighted
 * material, please see the LICENCE file in the top-level directory
 * or at http://www.freewrt.org/license for details.
 */

#ifndef PACK_H
#define PACK_H

#define STOREB(x) do {				\
		if (hdrleft < 1)		\
			return (NULL);		\
		*hdrptr++ = (x) & 0xFF;		\
		--hdrleft;			\
	} while (0)

#define STOREW(x) do {				\
		if (hdrleft < 2)		\
			return (NULL);		\
		*hdrptr++ = (x) & 0xFF;		\
		*hdrptr++ = ((x) >> 8) & 0xFF;	\
		hdrleft -= 2;			\
	} while (0)

#define STORET(x) do {				\
		if (hdrleft < 3)		\
			return (NULL);		\
		*hdrptr++ = (x) & 0xFF;		\
		*hdrptr++ = ((x) >> 8) & 0xFF;	\
		*hdrptr++ = ((x) >> 16) & 0xFF;	\
		hdrleft -= 3;			\
	} while (0)

#define STORED(x) do {				\
		if (hdrleft < 4)		\
			return (NULL);		\
		*hdrptr++ = (x) & 0xFF;		\
		*hdrptr++ = ((x) >> 8) & 0xFF;	\
		*hdrptr++ = ((x) >> 16) & 0xFF;	\
		*hdrptr++ = ((x) >> 24) & 0xFF;	\
		hdrleft -= 4;			\
	} while (0)

__BEGIN_DECLS
char *ft_pack(ftsf_entry *);
char *ft_packm(void);
__END_DECLS

#endif
