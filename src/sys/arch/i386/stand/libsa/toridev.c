/**	$MirOS$ */
/*	$OpenBSD: biosdev.c,v 1.68 2004/03/09 19:12:12 tom Exp $	*/

/*
 * Copyright (c) 1996 Michael Shalayeff
 * Copyright (c) 2003 Tobias Weingartner
 * Copyright (c) 2002, 2003, 2004
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/reboot.h>
#include <sys/disklabel.h>
#include <machine/tss.h>
#include <machine/biosvar.h>
#include <lib/libsa/saerrno.h>
#include "disk.h"
#include "debug.h"
#include "libsa.h"
#include "biosdev.h"
#include "tori.h"

static __inline int CD_rw(u_int64_t, void *);

extern int biosdreset(int);
extern const char *biosdisk_err(u_int);
extern int biosdisk_errno(u_int);

extern int debug;

u_int8_t tori_iobuf[2048];

struct EDD_CB {
	u_int8_t  edd_len;   /* size of packet */
	u_int8_t  edd_res1;  /* reserved */
	u_int8_t  edd_nblk;  /* # of blocks to transfer */
	u_int8_t  edd_res2;  /* reserved */
	u_int16_t edd_off;   /* address of buffer (offset) */
	u_int16_t edd_seg;   /* address of buffer (segment) */
	u_int64_t edd_daddr; /* starting block */
};

static __inline int
CD_rw(u_int64_t daddr, void *buf)
{
	int rv;
	int dev = T_DRV;
	volatile static struct EDD_CB cb;

	/* Zero out reserved stuff */
	cb.edd_res1 = 0;
	cb.edd_res2 = 0;

	/* Fill in parameters */
	cb.edd_len = sizeof(cb);
	cb.edd_nblk = 1;
	cb.edd_seg = ((u_int32_t)buf >> 4) & 0xffff;
	cb.edd_off = (u_int32_t)buf & 0xf;
	cb.edd_daddr = daddr;

	/* if offset/segment are zero, punt */
	if (!cb.edd_seg && !cb.edd_off)
		return (1);

	/* Call extended read/write (with disk packet) */
	BIOS_regs.biosr_ds = (u_int32_t)&cb >> 4;
	__asm __volatile (DOINT(0x13) "; setc %b0" : "=a" (rv)
			  : "0" (0x4200),
			    "d" (dev), "S" ((int) (&cb) & 0xf) : "%ecx", "cc");
	return (rv & 0xff)? rv >> 8 : 0;
}

/*
 * Read given sector, handling retry/errors/etc.
 */
int
tori_io(daddr_t off, void *buf)
{
	int j, error;
	void *bb = tori_iobuf;

	if (!(off & 3))
		bb = buf;

	/* Try to do operation up to 5 times */
	for (error = 1, j = 5; j-- && error;) {
		error = CD_rw(off >> 2, bb);
		switch (error) {
		case 0x00:	/* No errors */
		case 0x11:	/* ECC corrected */
			error = 0;
			break;

		default:	/* All other errors */
#ifdef BIOS_DEBUG
			if (debug) {
				printf("\nBIOS error 0x%X (%s)\n",
					error, biosdisk_err(error));
				getchar();
			}
#endif
			biosdreset(T_DRV);
			break;
		}
	}

	if (off & 3) {
		bb += (512*(off & 3));
		memmove(buf, bb, 2048-(512*(off & 3)));
	}

#ifdef BIOS_DEBUG
	if (debug) {
		if (error != 0)
			printf("=0x%X(%s)", error, biosdisk_err(error));
		putchar('\n');
	}
#endif

	return (error);
}

int
toriopen(struct open_file *f, ...)
{
	va_list ap;
	register char	*cp, **file;
	dev_t	maj, unit, part;

	va_start(ap, f);
	cp = *(file = va_arg(ap, char **));
	va_end(ap);

#ifdef BIOS_DEBUG
	if (debug)
		printf("%s\n", cp);
#endif

	f->f_devdata = NULL;
	/* search for device specification */
	cp += 2;
	if (cp[2] != ':') {
		if (cp[3] != ':')
			return ENOENT;
		else
			cp++;
	}

	for (maj = 0; maj < nbdevs &&
	     strncmp(*file, bdevs[maj], cp - *file); maj++);
	if (maj >= nbdevs) {
		printf("Unknown device: ");
		for (cp = *file; *cp != ':'; cp++)
			putchar(*cp);
		putchar('\n');
		return EADAPT;
	}

	/* get unit */
	if ('0' <= *cp && *cp <= '9')
		unit = *cp++ - '0';
	else {
		printf("Bad unit number\n");
		return EUNIT;
	}
	/* get partition */
	if ('a' <= *cp && *cp <= 'p')
		part = *cp++ - 'a';
	else {
		printf("Bad partition id\n");
		return EPART;
	}

	switch (maj) {
	case 6:  /* cd */
		break;
	default:
		return ENXIO;
	}

	cp++;	/* skip ':' */
	if (*cp != 0)
		*file = cp;
	else
		f->f_flags |= F_RAW;

	return 0;
}

int
toristrategy(void *devdata, int rw, daddr_t blk, size_t size, void *buf,
    size_t *rsize)
{
	u_int8_t error = 0;
	size_t rsizeres = 0;
	daddr_t off = blk;

	/* first: always reads at least 1 sector if off isn't aligned */
	if (off & 3) {
		error = tori_io(off, buf);
		rsizeres = ((4-(off & 3)) * 512);
		size -= rsizeres;
		buf += rsizeres;
		off += (4-(off & 3));
	}

	/* then: read the remaining stuff if any is left */
	while ((size > 0) && (!error)) {
		error = tori_io(off, buf);
		rsizeres += 2048;
		size -= 2048;
		buf += 2048;
		off += 4;
	}

#ifdef BIOS_DEBUG
	if (debug) {
		if (error != 0)
			printf("=0x%X(%s)", error, biosdisk_err(error));
		putchar('\n');
	}
#endif

	if (rsize != NULL)
		*rsize = rsizeres;

	return biosdisk_errno(error);
}

int
toriclose(struct open_file *f)
{
	f->f_devdata = NULL;
	return 0;
}

int
toriioctl(struct open_file *f, u_long cmd, void *data)
{
	return 0;
}
