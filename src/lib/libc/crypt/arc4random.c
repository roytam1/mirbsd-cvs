/**	$MirOS: src/lib/libc/crypt/arc4random.c,v 1.7 2006/08/19 02:03:08 tg Exp $ */
/*	$OpenBSD: arc4random.c,v 1.14 2005/06/06 14:57:59 kjell Exp $	*/

/*
 * Copyright (c) 2006, 2007 Thorsten Glaser <tg@mirbsd.de>
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
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

__RCSID("$MirOS: src/lib/libc/crypt/arc4random.c,v 1.7 2006/08/19 02:03:08 tg Exp $");

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
arc4_addrandom(struct arc4_stream *as, u_char *dat, int datlen)
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
	size_t	i, len;
	u_char rnd[128];
	tai64na_t tm;

	taina_time(&tm);
	arc4_addrandom(as, (void *)&tm, sizeof (tm));

	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;

	len = sizeof(rnd);
	if (sysctl(mib, 2, rnd, &len, NULL, 0) == -1) {
		for (i = 0; i < sizeof(rnd) / sizeof(u_int); i ++) {
			len = sizeof(u_int);
			if (sysctl(mib, 2, &rnd[i * sizeof(u_int)], &len,
			    NULL, 0) == -1)
				break;
		}
	}

	arc4_stir_pid = getpid();
	arc4_addrandom(as, rnd, sizeof(rnd));

	/*
	 * Discard early keystream, as per recommendations in:
	 * http://www.wisdom.weizmann.ac.il/~itsik/RC4/Papers/Rc4_ksa.ps
	 */
	for (i = 0; i < 256; i++)
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
	uint32_t v, i, k;
	size_t j;
	int mib[2];
	uint8_t sbuf[256];

	v = (rand() << 16) + len;
	for (j = 0; j < len; ++j)
		v += ((uint8_t *)buf)[j];
	len = MIN(len, 256 - sizeof (tai64na_t));
	v += (k = arc4random()) & 3;
	memmove(sbuf + sizeof (tai64na_t), buf, len);
	taina_time((void *)sbuf);
	len += sizeof (tai64na_t);
	v += (intptr_t)buf & 0xFFFFFFFF;

	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;
	j = sizeof (i);

	if (sysctl(mib, 2, &i, &j, sbuf, len) != 0)
		i = (((v & 1) + 1) * (rand() & 0xFF)) ^ arc4random() ^
		    *((uint32_t *)(sbuf + (len - 4)));

	len = sizeof (uint32_t);
	memmove(sbuf, &v, len);
	memmove(sbuf + len, &i, len);
	arc4_addrandom(&rs, sbuf, 2 * len);

	return ((k & ~3) ^ i);
}
