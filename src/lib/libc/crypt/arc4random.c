/*	$OpenBSD: arc4random.c,v 1.20 2008/10/03 18:46:04 otto Exp $	*/

/*
 * Copyright (c) 2006, 2007, 2008, 2009 Thorsten Glaser <tg@mirbsd.org>
 * Copyright (c) 1996, David Mazieres <dm@uun.org>
 * Copyright (c) 2008, Damien Miller <djm@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syskern/libckern.h>
#include "thread_private.h"

__RCSID("$MirOS: src/lib/libc/crypt/arc4random.c,v 1.22 2009/01/21 19:41:37 tg Exp $");

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

static bool rs_initialized;
static struct arc4_stream rs;
static pid_t arc4_stir_pid;
static int arc4_count;

static inline u_int8_t arc4_getbyte(void);
void arc4random_atexit(void);

void
arc4random_atexit(void)
{
	struct {
		pid_t spid;
		u_int cnt;
		u_int8_t carr[240];
	} buf;
	int mib[2];

	_ARC4_LOCK();
	mib[0] = 0;
	while (mib[0] < 240)
		buf.carr[mib[0]++] = arc4_getbyte();
	buf.spid = arc4_stir_pid;
	buf.cnt = (u_int)arc4_count | rs_initialized ? 0 : 0x80000000;
	_ARC4_UNLOCK();

	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;
	sysctl(mib, 2, NULL, NULL, &buf, sizeof (buf));
}

static inline void
arc4_init(void)
{
	int     n;

	for (n = 0; n < 256; n++)
		rs.s[n] = n;
	rs.i = 0;
	rs.j = 0;
}

static inline void
arc4_addrandom(u_char *dat, int datlen)
{
	int     n;
	u_int8_t si;

	rs.i--;
	for (n = 0; n < 256; n++) {
		rs.i = (rs.i + 1);
		si = rs.s[rs.i];
		rs.j = (rs.j + si + dat[n % datlen]);
		rs.s[rs.i] = rs.s[rs.j];
		rs.s[rs.j] = si;
	}
	rs.j = rs.i;
}

static void
arc4_stir(void)
{
	int mib[2];
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
	volatile uint8_t carryover;

	if (!rs_initialized) {
		arc4_init();
		rs_initialized = true;
	}

	carryover ^= (arc4_getbyte() & 0x0F);
	taina_time(&sbuf.alignedbuf.wtime);
	sbuf.alignedbuf.thepid = arc4_stir_pid = getpid();
	clock_gettime(CLOCK_VIRTUAL, &sbuf.alignedbuf.vtime);
	clock_gettime(CLOCK_PROF, &sbuf.alignedbuf.ptime);
	clock_gettime(CLOCK_MONOTONIC, &sbuf.alignedbuf.ntime);
	arc4_addrandom(sbuf.charbuf, sizeof (sbuf.alignedbuf));
	carryover ^= (arc4_getbyte() & 0xF0);

	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;

	len = sizeof (sbuf);
	sysctl(mib, 2, sbuf.charbuf, &len, NULL, 0);

	/* discard by a randomly fuzzed factor as well */
	len = 256 * 4 + (arc4_getbyte() & 0x0F) + carryover;
	arc4_addrandom(sbuf.charbuf, sizeof (sbuf));

	/*
	 * Discard early keystream, as per recommendations in:
	 * http://www.wisdom.weizmann.ac.il/~itsik/RC4/Papers/Rc4_ksa.ps
	 */
	while (len--)
		(void)arc4_getbyte();
	arc4_count = 1600000;
}

static u_int8_t
arc4_getbyte(void)
{
	u_int8_t si, sj;

	rs.i = (rs.i + 1);
	si = rs.s[rs.i];
	rs.j = (rs.j + si);
	sj = rs.s[rs.j];
	rs.s[rs.i] = sj;
	rs.s[rs.j] = si;
	return (rs.s[(si + sj) & 0xff]);
}

static inline u_int32_t
arc4_getword(void)
{
	u_int32_t val;
	val = arc4_getbyte() << 24;
	val |= arc4_getbyte() << 16;
	val |= arc4_getbyte() << 8;
	val |= arc4_getbyte();
	return val;
}

void
arc4random_stir(void)
{
	_ARC4_LOCK();
	arc4_stir();
	_ARC4_UNLOCK();
}

void
arc4random_addrandom(u_char *dat, int datlen)
{
	_ARC4_LOCK();
	if (!rs_initialized)
		arc4_stir();
	arc4_addrandom(dat, datlen);
	_ARC4_UNLOCK();
}

u_int32_t
arc4random(void)
{
	u_int32_t val;
	_ARC4_LOCK();
	arc4_count -= 4;
	if (arc4_count <= 0 || !rs_initialized || arc4_stir_pid != getpid())
		arc4_stir();
	if (arc4_getbyte() & 1)
		(void)arc4_getbyte();
	val = arc4_getword();
	_ARC4_UNLOCK();
	return val;
}

void
arc4random_buf(void *_buf, size_t n)
{
	u_char *buf = (u_char *)_buf;
	_ARC4_LOCK();
	if (!rs_initialized || arc4_stir_pid != getpid())
		arc4_stir();
	buf[0] = arc4_getbyte() % 3;
	while (buf[0]--)
		(void)arc4_getbyte();
	while (n--) {
		if (--arc4_count <= 0)
			arc4_stir();
		buf[n] = arc4_getbyte();
	}
	_ARC4_UNLOCK();
}

/*
 * Calculate a uniformly distributed random number less than upper_bound
 * avoiding "modulo bias".
 *
 * Uniformity is achieved by generating new random numbers until the one
 * returned is outside the range [0, 2**32 % upper_bound).  This
 * guarantees the selected random number will be inside
 * [2**32 % upper_bound, 2**32) which maps back to [0, upper_bound)
 * after reduction modulo upper_bound.
 */
u_int32_t
arc4random_uniform(u_int32_t upper_bound)
{
	u_int32_t r, min;

	if (upper_bound < 2)
		return 0;

#if (ULONG_MAX > 0xffffffffUL)
	min = 0x100000000UL % upper_bound;
#else
	/* Calculate (2**32 % upper_bound) avoiding 64-bit math */
	if (upper_bound > 0x80000000)
		min = 1 + ~upper_bound;		/* 2**32 - upper_bound */
	else {
		/* (2**32 - (x * 2)) % x == 2**32 % x when x <= 2**31 */
		min = ((0xffffffff - (upper_bound * 2)) + 1) % upper_bound;
	}
#endif

	/*
	 * This could theoretically loop forever but each retry has
	 * p > 0.5 (worst case, usually far better) of selecting a
	 * number inside the range we need, so it should rarely need
	 * to re-roll.
	 */
	_ARC4_LOCK();
	if (!rs_initialized || arc4_stir_pid != getpid())
		arc4_stir();
	if (arc4_getbyte() & 1)
		(void)arc4_getbyte();
	for (;;) {
		arc4_count -= 4;
		if (arc4_count <= 0)
			arc4_stir();
		r = arc4_getword();
		if (r >= min)
			break;
	}
	_ARC4_UNLOCK();

	return r % upper_bound;
}

void
arc4random_push(int n)
{
	arc4random_pushb(&n, sizeof (int));
}

uint32_t
arc4random_pushb(const void *buf, size_t len)
{
	uint32_t h, vu, vk;
	size_t j;
	int mib[2];
	union {
		uint8_t buf[256];
		tai64na_t tai64tm;
		struct {
			const void *sp, *dp;
			size_t sz;
		} s;
		struct {
			uint32_t h, v;
		} u;
	} uu;

	vu = arc4random();
	uu.s.sp = &uu;
	uu.s.dp = buf;
	uu.s.sz = len;
	h = OAAT0Update(arc4random() & 0xFFFFFF00, (void *)&uu, sizeof(uu.s));

	taina_time(&uu.tai64tm);
	for (j = 0; j < len; ++j) {
		register uint8_t c;

		c = ((const uint8_t *)buf)[j];
		uu.buf[j % 256] ^= c;
		h += c;
		h += h << 10;
		h ^= h >> 6;
	}
	len = MIN(256, len);

	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;
	j = sizeof(vk);

	if (sysctl(mib, 2, &vk, &j, &uu, len) != 0)
		vk = 0;

	uu.u.h = OAAT0Final(h);
	uu.u.v = (vk & 0xFFFF0000) | (vu & 0x0000FFFF);
	_ARC4_LOCK();
	arc4_addrandom((void *)&uu, sizeof(uu.u));
	_ARC4_UNLOCK();
	if (/* kernel failed */ !vk)
		vk = arc4random();

	return ((vk & 0x0000FFFF) ^ (vu & 0xFFFF0000) ^ (uu.u.h & 0x00073000));
}

#if 0
/*-------- Test code for i386 --------*/
#include <stdio.h>
#include <machine/pctr.h>
int
main(int argc, char **argv)
{
	const int iter = 1000000;
	int     i;
	pctrval v;

	v = rdtsc();
	for (i = 0; i < iter; i++)
		arc4random();
	v = rdtsc() - v;
	v /= iter;

	printf("%qd cycles\n", v);
}
#endif
