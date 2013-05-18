/* $MirOS: contrib/code/mirmake/dist/contrib/arc4random.c,v 1.1 2006/08/26 16:45:26 tg Exp $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
 */

#include <sys/param.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

__RCSID("$MirOS: contrib/code/mirmake/dist/contrib/arc4random.c,v 1.1 2006/08/26 16:45:26 tg Exp $");

void
arc4random_push(int n)
{
	arc4random_pushb(&n, sizeof (int));
}

uint32_t
arc4random_pushb(const void *buf, size_t len)
{
	uint64_t v;
	struct timeval tv;
	size_t j;

	gettimeofday(&tv, NULL);
	v = tv.tv_sec;
	v ^= (v >> 32);
	v <<= 32;
	v ^= tv.tv_usec;
	v ^= (random() << 16) + len;
	if (len == 4)
		v += *((uint32_t *)buf);
	else
		for (j = 0; j < len; ++j)
			v += ((uint8_t *)buf)[j];
	v += arc4random() * (random() & 0xFF);
	v += (ptrdiff_t)buf;

	arc4random_addrandom(&v, sizeof (v));
}

#ifndef _ARC4RANDOM_WRAP

#if defined(__gnu_linux__)
#define USE_SYSCTL
#else
#undef USE_SYSCTL
#endif

#ifdef USE_SYSCTL
#include <sys/sysctl.h>
#else
static int arc4stir_fd = -1;
#endif

/**	_MirOS: src/lib/libc/crypt/arc4random.c,v 1.7 2006/08/19 02:03:08 tg Exp $ */
/*	$OpenBSD: arc4random.c,v 1.14 2005/06/06 14:57:59 kjell Exp $	*/

/*
 * Copyright (c) 1996, David Mazieres <dm@uun.org>
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
	struct timeval tv;
	char *tvp;
	int i;
#ifdef USE_SYSCTL
	int     mib[2];
	size_t	len;
	u_char rnd[128];

#if defined(__OpenBSD__)
	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;
#elif defined(__gnu_linux__)
	mib[0] = CTL_KERN;
	mib[1] = KERN_RANDOM;
#else
# error which sysctl do I use?
#endif

	len = sizeof(rnd);
	if (sysctl(mib, 2, rnd, &len, NULL, 0) == -1) {
		for (i = 0; i < sizeof(rnd) / sizeof(u_int); i ++) {
			len = sizeof(u_int);
			if (sysctl(mib, 2, &rnd[i * sizeof(u_int)], &len,
			    NULL, 0) == -1)
				break;
		}
	}
#else
#ifdef __INTERIX
	/* slow /dev/urandom */
	uint32_t rnd[2];
#define RND_READ_BYTES 4
#else
	uint32_t rnd[9];
#define RND_READ_BYTES 32
#endif

	/*
	 * TODO: spawn entropy gathering dæmon here,
	 * especially for systems with malfunctioning
	 * /dev/urandom such as Interix
	 */

	rnd[0] = (uint32_t)getpid() * (uint32_t)getppid();

	if (arc4stir_fd == -1)
		arc4stir_fd = open("/dev/urandom", O_RDONLY);
	if (arc4stir_fd == -1)
		arc4stir_fd = open("/dev/random", O_RDONLY);
	if (arc4stir_fd == -1)
		arc4stir_fd = open("/C/PUTTY.RND", O_RDONLY);
	if (arc4stir_fd == -1)
		arc4stir_fd = open("/PUTTY.RND", O_RDONLY);
	if (arc4stir_fd == -1)
		arc4stir_fd = open("/RANDSEED.BIN", O_RDONLY);
	if (arc4stir_fd == -1)
		arc4stir_fd = open("C:\\PUTTY.RND", O_RDONLY);
	if (arc4stir_fd == -1)
		arc4stir_fd = open("C:\\RANDSEED.BIN", O_RDONLY);
	if (arc4stir_fd == -1)
		arc4stir_fd = open("URANDOM$", O_RDONLY);
	if (arc4stir_fd == -1)
		arc4stir_fd = open("RANDOM$", O_RDONLY);

	rnd[0] += arc4stir_fd;
	rnd[0] += (i = read(arc4stir_fd, &rnd[1], RND_READ_BYTES));
	if (i != RND_READ_BYTES) {
		lseek(arc4stir_fd, 0, SEEK_SET);
		rnd[0] += (i = read(arc4stir_fd, &rnd[1], RND_READ_BYTES));
	}
	if (i != RND_READ_BYTES)
		if ((i = open("/dev/urandom", O_RDONLY)) >= 0)
			if (read(i, &rnd[1], RND_READ_BYTES) > 0) {
				close(arc4stir_fd);
				arc4stir_fd = i;
				rnd[0] += i;
				i = RND_READ_BYTES;
			}
	if (i != RND_READ_BYTES)
		if ((i = open("/C/PUTTY.RND", O_RDONLY)) >= 0)
			if (read(i, &rnd[1], RND_READ_BYTES) > 0) {
				close(arc4stir_fd);
				arc4stir_fd = i;
				rnd[0] += i;
				i = RND_READ_BYTES;
			}
	if (i != RND_READ_BYTES)
		if ((i = open("/PUTTY.RND", O_RDONLY)) >= 0)
			if (read(i, &rnd[1], RND_READ_BYTES) > 0) {
				close(arc4stir_fd);
				arc4stir_fd = i;
				rnd[0] += i;
				i = RND_READ_BYTES;
			}
	if (i != RND_READ_BYTES)
		if ((i = open("C:\\PUTTY.RND", O_RDONLY)) >= 0)
			if (read(i, &rnd[1], RND_READ_BYTES) > 0) {
				close(arc4stir_fd);
				arc4stir_fd = i;
				rnd[0] += i;
				i = RND_READ_BYTES;
			}
#undef RND_READ_BYTES
#endif

	arc4_stir_pid = getpid();
	gettimeofday(&tv, NULL);
	if ((tvp = malloc(sizeof (rnd) + sizeof (tv) + 1)) == NULL) {
		arc4_addrandom(as, &tv, sizeof (rv));
		arc4_addrandom(as, rnd, sizeof (rnd));
	} else {
		memmove(tvp + 1, &tv, sizeof (tv));
		memmove(tvp + sizeof (tv) + 1, rnd, sizeof (rnd));
		*tvp = random() & 0xFF;
		arc4_addrandom(as, tvp, sizeof (rnd) + sizeof (tv) + 1);
	}

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
#endif
