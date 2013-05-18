/*	$OpenBSD: arc4random.c,v 1.20 2008/10/03 18:46:04 otto Exp $	*/

/*
 * Copyright (c) 2006, 2007, 2008, 2009, 2010
 *	Thorsten Glaser <tg@mirbsd.org>
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

__RCSID("$MirOS: src/lib/libc/crypt/arc4random.c,v 1.29 2010/01/16 20:29:41 tg Exp $");

struct arc4_stream {
	u_int8_t i;
	u_int8_t j;
	u_int8_t s[256];
};

static bool rs_initialized;
static struct arc4_stream rs;
static pid_t arc4_stir_pid;
static int arc4_count;

#if 0
static void arc4_add_lazy(const uint8_t *, size_t)
    __attribute__((__bounded__ (__string__,1,2)));
#endif
static uint8_t arc4_getbyte(void);
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
#if 0
	arc4_add_lazy(NULL, 0);		/* flush buffer */
#endif
	mib[0] = 0;
	while (mib[0] < 240)
		buf.carr[mib[0]++] = arc4_getbyte();
	buf.spid = arc4_stir_pid;
	buf.cnt = (u_int)arc4_count | (rs_initialized ? 0 : 0x80000000);
	_ARC4_UNLOCK();

	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;
	sysctl(mib, 2, NULL, NULL, &buf, sizeof (buf));
}

static void
arc4_init(void)
{
	int n;

	for (n = 0; n < 256; n++)
		rs.s[n] = (uint8_t)n;
	rs.i = 0;
	rs.j = 0;
}

static void
arc4_addrandom(const u_char *dat, size_t datlen)
{
	size_t n = 0;
	uint8_t si;

	rs.i--;
	while (n < 256) {
		rs.i++;
		si = rs.s[rs.i];
		rs.j = (uint8_t)(rs.j + si + dat[n++ % datlen]);
		rs.s[rs.i] = rs.s[rs.j];
		rs.s[rs.j] = si;
	}
	rs.i++;
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

static uint8_t
arc4_getbyte(void)
{
	uint8_t si, sj;

	rs.i++;
	si = rs.s[rs.i];
	rs.j = (uint8_t)(rs.j + si);
	sj = rs.s[rs.j];
	rs.s[rs.i] = sj;
	rs.s[rs.j] = si;
	return (rs.s[(si + sj) & 0xff]);
}

static uint32_t
arc4_getword(void)
{
	uint32_t val;
	val = (uint32_t)arc4_getbyte() << 24;
	val |= (uint32_t)arc4_getbyte() << 16;
	val |= (uint32_t)arc4_getbyte() << 8;
	val |= (uint32_t)arc4_getbyte();
	return (val);
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

#if 0
/* len=0: flush; len=1..128: normal operation; 128..~238: inval/possible */
static void
arc4_add_lazy(const uint8_t *buf, size_t len)
{
	static uint8_t arc4_lazybuf[256];
	static uint8_t arc4_lazyfree = 0;
	static struct timeval arc4_lazytv = { 0, 0 };
	struct timeval curtv;

	/* assert(len <= 128); */

	if (arc4_lazyfree == 0) {
 arc4_lazy_start:
		if (len == 0)
			return;
		arc4_lazybuf[0] = arc4_getbyte();
		arc4_lazyfree = 255;
	}

	if (len == 0 || (len + sizeof(uint64_t)) > arc4_lazyfree) {
		int i = 256 - arc4_lazyfree, j;

		j = 256 + (arc4_getbyte() & 0x0F);
		/* diffusion, so that input is weighted the same */
		while (i < 256)
			arc4_lazybuf[i++] = arc4_getbyte();
		arc4_addrandom(arc4_lazybuf, 256);
		j += arc4_getbyte() & 0x0F;
		/* throw away some; fewer than normal stir though */
		while (j--)
			(void)arc4_getbyte();
		/* reset pool and re-do */
		goto arc4_lazy_start;
	}

	if (!gettimeofday(&curtv, NULL)) {
		struct timeval deltatv;
		uint64_t deltaval;

		timersub(&curtv, &arc4_lazytv, &deltatv);
		deltaval = deltatv.tv_sec * 1000000 + deltatv.tv_usec;
		arc4_lazytv = curtv;
		while (deltaval) {
			arc4_lazybuf[256 - arc4_lazyfree--] = deltaval & 0xFF;
			deltaval >>= 8;
		}
	}

	memcpy(arc4_lazybuf + 256 - arc4_lazyfree, buf, len);
	arc4_lazyfree -= len;
}

void
arc4random_add_lazy(const void *buf, size_t len)
{
	_ARC4_LOCK();
	if (!rs_initialized)
		arc4_stir();
	_ARC4_UNLOCK();

	while (len > 128) {
		_ARC4_LOCK();
		arc4_addrandom(buf, 128);
		_ARC4_UNLOCK();
		buf = (const char *)buf + 128;
		len -= 128;
	}

	if (len) {
		_ARC4_LOCK();
		arc4_add_lazy(buf, len);
		_ARC4_UNLOCK();
	}
}
#endif

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

void
arc4random_push(int n)
{
	arc4random_pushb(&n, sizeof (int));
}

uint32_t
arc4random_pushb(const void *buf, size_t len)
{
	size_t j;
	int mib[2];
	union {
		uint8_t buf[256];
		struct {
			tai64na_t tai64tm;
			const void *sp, *dp;
			size_t sz;
			uint32_t vu;
		} s;
	} uu;
	struct {
		uint32_t h;
		uint16_t u;
		uint8_t k[10];
	} av;

	{
		register uint32_t h;
		register size_t n = 0;
		register uint8_t c;

		av.u = arc4random() & 0xFFFF;
		uu.s.sp = &uu;
		uu.s.dp = buf;
		uu.s.sz = len;
		uu.s.vu = arc4random();
		taina_time(&uu.s.tai64tm);

		h = OAAT0Update(arc4random() & 0xFFFFFF00,
		    (void *)&uu, sizeof(uu.s));
		j = MAX(len, sizeof(uu.s));

		while (n < j) {
			c = ((const uint8_t *)buf)[n % len];
			uu.buf[n % sizeof(uu.buf)] ^= c;
			h += c;
			h += h << 10;
			h ^= h >> 6;
			++n;
		}

		len = MIN(sizeof(uu), j);
		av.h = OAAT0Final(h);
	}

	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;
	j = sizeof(av.k);

	av.u += sysctl(mib, 2, av.k, &j, &uu, len);

	_ARC4_LOCK();
	arc4_addrandom((void *)&av, sizeof(av));
	if (arc4_getbyte() & 1)
		(void)arc4_getbyte();
	av.h = arc4_getword();
	_ARC4_UNLOCK();

	return (av.h);
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
