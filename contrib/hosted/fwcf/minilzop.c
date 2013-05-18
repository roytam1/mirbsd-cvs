/* $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $ */

/*-
 * Copyright (c) 2007
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

#include <sys/param.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "defs.h"
#include "adler.h"
#include "compress.h"
#include "minilzop.h"

__RCSID("$MirOS$");

#define lodsw(s)	__extension__({				\
		uint8_t *lodsw_buf = (s);			\
		uint16_t lodsw_val;				\
								\
		lodsw_val = lodsw_buf[0];			\
		lodsw_val |= lodsw_buf[1] << 8;			\
		(lodsw_val);					\
	})
#define lodsd(s)	__extension__({				\
		uint8_t *lodsd_buf = (s);			\
		uint32_t lodsd_val;				\
								\
		lodsd_val = lodsd_buf[0];			\
		lodsd_val |= lodsd_buf[1] << 8;			\
		lodsd_val |= lodsd_buf[2] << 16;		\
		lodsd_val |= lodsd_buf[3] << 24;		\
		(lodsd_val);					\
	})
#define stosw(s,w)	do {					\
		uint8_t *stosw_buf = (s);			\
		uint16_t stosw_val = (w);			\
								\
		stosw_buf[0] = stosw_val & 0xFF;		\
		stosw_buf[1] = (stosw_val >> 8) & 0xFF;		\
	} while (0)
#define stosd(s,dw)	do {					\
		uint8_t *stosd_buf = (s);			\
		uint32_t stosd_val = (dw);			\
								\
		stosd_buf[0] = stosd_val & 0xFF;		\
		stosd_buf[1] = (stosd_val >> 8) & 0xFF;		\
		stosd_buf[2] = (stosd_val >> 16) & 0xFF;	\
		stosd_buf[3] = (stosd_val >> 24) & 0xFF;	\
	} while (0)

void
read_aszdata(int dfd, char **dbuf, size_t *dlen)
{
	size_t len;
	uint8_t hdrbuf[8];
	ADLER_DECL;

	if (read(dfd, hdrbuf, 8) != 8)
		err(1, "short read");
	*dlen = lodsd(hdrbuf + 4);
	if ((*dbuf = malloc(*dlen)) == NULL)
		err(255, "out of memory trying to allocate %zu bytes", *dlen);
	if ((size_t)read(dfd, *dbuf, *dlen) != *dlen)
		err(1, "short read");
	len = 4;
	ADLER_CALC(hdrbuf + 4);
	len = *dlen;
	ADLER_CALC(*dbuf);
	if ((lodsw(hdrbuf) != s1) || (lodsw(hdrbuf + 2) != s2))
		err(2, "checksum mismatch, size %zu,"
		    " want 0x%02X%02X%02X%02X got 0x%04X%04X", *dlen,
		    hdrbuf[3], hdrbuf[2], hdrbuf[1], hdrbuf[0], s2, s1);
}

void
write_aszdata(int dfd, const char *dbuf, size_t dlen)
{
	size_t len;
	uint8_t hdrbuf[8];
	ADLER_DECL;

	stosd(hdrbuf + 4, dlen);
	len = 4;
	ADLER_CALC(hdrbuf + 4);
	len = dlen;
	ADLER_CALC(dbuf);
	stosw(hdrbuf, s1);
	stosw(hdrbuf + 2, s2);
	if (write(dfd, hdrbuf, 8) != 8)
		err(1, "short write");
	if ((size_t)write(dfd, dbuf, dlen) != dlen)
		err(1, "short write");
}
