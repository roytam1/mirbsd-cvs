/**	$MirOS: src/lib/libc/crypt/arc4random.c,v 1.16 2008/07/06 15:34:46 tg Exp $ */
/*	$OpenBSD: arc4random.c,v 1.14 2005/06/06 14:57:59 kjell Exp $	*/

/*
 * Copyright (c) 2006, 2007, 2008 Thorsten Glaser <tg@mirbsd.de>
 * Copyright (c) 1996, David Mazieres <dm@uun.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * The following disclaimer must also be retained:
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

/*
 * Arc4 random number generator for OpenBSD.
 *
 * This code is derived from section 17.1 of Applied Cryptography,
 * second edition, which describes a stream cipher allegedly
 * compatible with RSA Labs "RC4" cipher (the actual description of
 * which is a trade secret).  The same algorithm is used as a stream
 * cipher called "arcfour" in Tatu Ylonen's ssh package.
 *
 * Here the stream cipher has been modified always to include the time
 * when initializing the state.  That makes it impossible to
 * regenerate the same random sequence twice, so this can't be used
 * for encryption, but will generate good random numbers.
 *
 * RC4 is a registered trademark of RSA Laboratories.
 */

#include <sys/param.h>
#include <sys/sysctl.h>
#include <sys/taitime.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

__RCSID("$MirOS: src/lib/libc/crypt/arc4random.c,v 1.16 2008/07/06 15:34:46 tg Exp $");

#ifdef __GNUC__
#define inline __inline
#else				/* !__GNUC__ */
#define inline
#endif				/* !__GNUC__ */

struct arc4_stream {
	u_int8_t i;
	u_int8_t j;
	u_int8_t s[256];
};

static int rs_initialized;
static struct arc4_stream rs;
static pid_t arc4_stir_pid;
static int arc4_count;

static inline u_int8_t arc4_getbyte(struct arc4_stream *);

static inline void
arc4_init(struct arc4_stream *as)
{
	int     n;

	for (n = 0; n < 256; n++)
		as->s[n] = n;
	as->i = 0;
	as->j = 0;
}

static inline void
arc4_addrandom(struct arc4_stream *as, uint8_t *dat, int datlen)
{
	int     n;
	u_int8_t si;

	as->i--;
	for (n = 0; n < 256; n++) {
		as->i = (as->i + 1);
		si = as->s[as->i];
		as->j = (as->j + si + dat[n % datlen]);
		as->s[as->i] = as->s[as->j];
		as->s[as->j] = si;
	}
	as->j = as->i;
}

static void
arc4_stir(struct arc4_stream *as)
{
	int     mib[2];
	size_t len;
	union {
		uint8_t charbuf[128];
		uint32_t intbuf[32];
		struct {
			tai64na_t wtime;
			struct timespec vtime;
			struct timespec ptime;
			struct timespec ntime;
			pid_t thepid;
		} alignedbuf;
	} sbuf;

	taina_time(&sbuf.alignedbuf.wtime);
	sbuf.alignedbuf.thepid = arc4_stir_pid = getpid();
	clock_gettime(CLOCK_VIRTUAL, &sbuf.alignedbuf.vtime);
	clock_gettime(CLOCK_PROF, &sbuf.alignedbuf.ptime);
	clock_gettime(CLOCK_MONOTONIC, &sbuf.alignedbuf.ntime);
	arc4_addrandom(as, sbuf.charbuf, sizeof (sbuf.alignedbuf));

	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;

	len = 128;
	if (sysctl(mib, 2, &sbuf.charbuf, &len, NULL, 0) == -1) {
		size_t i;

		for (i = 0; i < 32; i++) {
			len = 4;
			if (sysctl(mib, 2, &sbuf.intbuf[i], &len,
			    NULL, 0) == -1)
				break;
		}
	}
	/* discard by a randomly fuzzed factor as well */
	len = 256 * 4 + (arc4_getbyte(as) & 0x0F);
	arc4_addrandom(as, sbuf.charbuf, sizeof (sbuf));

	/*
	 * Discard early keystream, as per recommendations in:
	 * http://www.wisdom.weizmann.ac.il/~itsik/RC4/Papers/Rc4_ksa.ps
	 */
	while (len--)
		(void)arc4_getbyte(as);
	arc4_count = 400000;
}

static inline u_int8_t
arc4_getbyte(struct arc4_stream *as)
{
	u_int8_t si, sj;

	as->i = (as->i + 1);
	si = as->s[as->i];
	as->j = (as->j + si);
	sj = as->s[as->j];
	as->s[as->i] = sj;
	as->s[as->j] = si;
	return (as->s[(si + sj) & 0xff]);
}

static inline u_int32_t
arc4_getword(struct arc4_stream *as)
{
	u_int32_t val;
	val = arc4_getbyte(as) << 24;
	val |= arc4_getbyte(as) << 16;
	val |= arc4_getbyte(as) << 8;
	val |= arc4_getbyte(as);
	return val;
}

void
arc4random_stir(void)
{
	if (!rs_initialized) {
		arc4_init(&rs);
		rs_initialized = 1;
	}
	arc4_stir(&rs);
}

void
arc4random_addrandom(u_char *dat, int datlen)
{
	if (!rs_initialized)
		arc4random_stir();
	arc4_addrandom(&rs, dat, datlen);
}

u_int32_t
arc4random(void)
{
	if (--arc4_count == 0 || !rs_initialized || arc4_stir_pid != getpid())
		arc4random_stir();
	return arc4_getword(&rs);
}

void
arc4random_push(int n)
{
	arc4random_pushb(&n, sizeof (int));
}

uint32_t
arc4random_pushb(const void *buf, size_t len)
{
	uint32_t v, i, k, tr;
	size_t j;
	int mib[2];
	union {
		uint8_t buf[256];
		tai64na_t tai64tm;
		uint32_t xbuf[2];
	} idat;

	tr = arc4random();
	v = (rand() << 16) + len;
	taina_time(&idat.tai64tm);
	for (j = 0; j < len; ++j) {
		register uint8_t c;

		c = ((const uint8_t *)buf)[j];
		v += c;
		idat.buf[j % 256] ^= c;
	}
	j = MAX(sizeof (tai64na_t), 2 * sizeof (uint32_t));
	len = MIN(256, MAX(j, len));
	v += (k = arc4random()) & 3;
	v += (intptr_t)buf & 0xFFFFFFFF;

	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;
	j = sizeof (i);

	idat.xbuf[1] ^= tr;
	if (sysctl(mib, 2, &i, &j, &idat.buf[0], len) != 0)
		i = idat.xbuf[0] ^
		    (((v & 1) + 1) * (rand() & 0xFF)) ^ arc4random();
	idat.xbuf[1] ^= tr;

	taina_time(&idat.tai64tm);
	idat.xbuf[0] ^= v;
	idat.xbuf[1] ^= i ^ (k & 12);
	j = MAX(sizeof (tai64na_t), 2 * sizeof (uint32_t));
	arc4_addrandom(&rs, &idat.buf[0], j);

	return ((k & ~15) ^ i);
}
