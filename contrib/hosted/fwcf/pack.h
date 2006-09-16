/* $MirOS: contrib/hosted/fwcf/pack.h,v 1.4 2006/09/16 04:40:25 tg Exp $ */

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

#define LOADW(x) __extension__({		\
		uint8_t *lwbf = (uint8_t *)(x);	\
		uint32_t res = 0;		\
		res = (res << 8) | lwbf[1];	\
		res = (res << 8) | lwbf[0];	\
		res;				\
	})

#define LOADT(x) __extension__({		\
		uint8_t *lwbf = (uint8_t *)(x);	\
		uint32_t res = 0;		\
		res = (res << 8) | lwbf[2];	\
		res = (res << 8) | lwbf[1];	\
		res = (res << 8) | lwbf[0];	\
		res;				\
	})

__BEGIN_DECLS
char *ft_pack(ftsf_entry *);
char *ft_packm(void);

char *mkheader(char *, size_t, uint32_t, uint32_t, uint8_t);
char *mktrailer(char *, size_t);
__END_DECLS

#endif
