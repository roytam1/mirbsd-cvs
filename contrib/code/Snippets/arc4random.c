static const char __vcsid[] =
    "@(#)rcsid_master: $MirOS: contrib/code/Snippets/arc4random.c,v 1.8 2008/12/08 13:31:58 tg Exp $"
    ;

/*-
 * Arc4 random number generator for OpenBSD.
 * Copyright 1996 David Mazieres <dm@lcs.mit.edu>.
 *
 * Modification and redistribution in source and binary forms is
 * permitted provided that due credit is given to the author and the
 * OpenBSD project by leaving this copyright notice intact.
 */

/*-
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

/*-
 * Modified by Robert Connolly from OpenBSD lib/libc/crypt/arc4random.c v1.11.
 * This is arc4random(3) using urandom.
 */

/*-
 * Copyright (c) 2008
 *	Thorsten Glaser <tg@mirbsd.de>
 * This is arc4random(3) made more portable,
 * as well as arc4random_pushb(3) for Cygwin.
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
#include <sys/types.h>
#include <sys/time.h>
#if HAVE_SYS_SYSCTL_H
#include <sys/sysctl.h>
#endif
#include <fcntl.h>
#if HAVE_STDINT_H
#include <stdint.h>
#elif defined(USE_INTTYPES)
#include <inttypes.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#if defined(__CYGWIN__)
#define USE_MS_CRYPTOAPI
#endif

#ifdef USE_MS_CRYPTOAPI
#define WIN32_WINNT 0x400
#define _WIN32_WINNT 0x400
#include <windows.h>
#include <wincrypt.h>
#endif

#ifndef MIN
#define	MIN(a,b)	(((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define	MAX(a,b)	(((a)>(b))?(a):(b))
#endif

#ifdef REDEF_USCORETYPES
#define u_int32_t	uint32_t
#endif

#ifndef _PATH_URANDOM
#define _PATH_URANDOM	"/dev/urandom"
#endif

struct arc4_stream {
	uint8_t i;
	uint8_t j;
	uint8_t s[256];
};

static int rs_initialized;
static struct arc4_stream rs;
static pid_t arc4_stir_pid;
static int arc4_count;
static const char __randomdev[] = _PATH_URANDOM;

static uint8_t arc4_getbyte(struct arc4_stream *);
static void stir_finish(struct arc4_stream *, int);
static void arc4_atexit(void);
static char arc4_writeback(uint8_t *, size_t, char);
#ifdef USE_MS_CRYPTOAPI
static char w32_cryptoapi_getrand(uint8_t *, size_t);
#define arc4_writeback(buf, n, do_rd)	w32_cryptoapi_getrand((buf), (n))
#endif

#ifndef arc4random_pushk
u_int32_t arc4random(void);
void arc4random_addrandom(u_char *, int);
void arc4random_stir(void);
#ifdef USE_MS_CRYPTOAPI
uint32_t arc4random_pushb(const void *, size_t);
#endif
#endif

static void
arc4_init(struct arc4_stream *as)
{
	int     n;

	for (n = 0; n < 256; n++)
		as->s[n] = n;
	as->i = 0;
	as->j = 0;
}

static void
arc4_addrandom(struct arc4_stream *as, u_char *dat, int datlen)
{
	int     n;
	uint8_t si;

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
	int fd;
	struct {
		struct timeval tv;
		pid_t pid;
		u_int rnd[(128 - (sizeof (struct timeval) + sizeof (pid_t))) / sizeof(u_int)];
	} rdat;
	size_t sz = 0;

	gettimeofday(&rdat.tv, NULL);
	rdat.pid = getpid();
	memcpy(rdat.rnd, __vcsid, MIN(sizeof (__vcsid), sizeof (rdat.rnd)));

#ifdef USE_MS_CRYPTOAPI
	if (w32_cryptoapi_getrand((char *)rdat.rnd, sizeof (rdat.rnd)))
		goto stir_okay;
#endif

	/* /dev/urandom is a multithread interface, sysctl is not. */
	/* Try to use /dev/urandom before sysctl. */
	fd = open(__randomdev, O_RDONLY);
	if (fd != -1) {
		sz = (size_t)read(fd, rdat.rnd, sizeof (rdat.rnd));
		close(fd);
	}
	if (sz > sizeof (rdat.rnd))
		sz = 0;
	if (fd == -1 || sz != sizeof (rdat.rnd)) {
		/* /dev/urandom failed? Maybe we're in a chroot. */
#if /* Linux */ defined(_LINUX_SYSCTL_H) || \
    /* OpenBSD */ (defined(CTL_KERN) && defined(KERN_ARND))
		int mib[3], nmib = 3;
		size_t i = sz / sizeof (u_int), len;

#ifdef _LINUX_SYSCTL_H
		mib[0] = CTL_KERN;
		mib[1] = KERN_RANDOM;
		mib[2] = RANDOM_UUID;
#else
		mib[0] = CTL_KERN;
		mib[1] = KERN_ARND;
		nmib = 2;
#endif

		while (i < sizeof (rdat.rnd) / sizeof (u_int)) {
			len = sizeof(u_int);
			if (sysctl(mib, nmib, &rdat.rnd[i++], &len,
			    NULL, 0) == -1) {
				fputs("warning: no entropy source\n", stderr);
				break;
			}
		}
#else
		/* XXX kFreeBSD doesn't seem to have KERN_ARND or so */
		;
#endif
	}

#ifdef USE_MS_CRYPTOAPI
 stir_okay:
#endif
	fd = arc4_getbyte(as);

	/*
	 * Time to give up. If no entropy could be found then we will just
	 * use gettimeofday and getpid.
	 */
	arc4_addrandom(as, (void *)&rdat, sizeof(rdat));

	stir_finish(as, fd);
}

static void
stir_finish(struct arc4_stream *as, int av)
{
	size_t n;
	uint8_t tb[16];

	arc4_stir_pid = getpid();

	/*
	 * Discard early keystream, as per recommendations in:
	 * http://www.wisdom.weizmann.ac.il/~itsik/RC4/Papers/Rc4_ksa.ps
	 * We discard 256 words. A long word is 4 bytes.
	 * We also discard a randomly fuzzed amount.
	 */
	n = 256 * 4 + (arc4_getbyte(as) & 0x0F);
	while (av) {
		n += (av & 0x0F);
		av >>= 4;
	}
	while (n--)
		arc4_getbyte(as);
	while (n < sizeof (tb))
		tb[n++] = arc4_getbyte(as);
	if (arc4_writeback(tb, sizeof (tb), 0))
		arc4_getbyte(as);
	arc4_count = 400000;
}

static uint8_t
arc4_getbyte(struct arc4_stream *as)
{
	uint8_t si, sj;

	as->i = (as->i + 1);
	si = as->s[as->i];
	as->j = (as->j + si);
	sj = as->s[as->j];
	as->s[as->i] = sj;
	as->s[as->j] = si;
	return (as->s[(si + sj) & 0xff]);
}

static uint32_t
arc4_getword(struct arc4_stream *as)
{
	uint32_t val;
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
		atexit(arc4_atexit);
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

#ifdef USE_MS_CRYPTOAPI
static char
w32_cryptoapi_getrand(uint8_t *buf, size_t len)
{
	static char has_provider = 0;
	static HCRYPTPROV p;

	if (!has_provider) {
		if (!CryptAcquireContext(&p, NULL, NULL, PROV_RSA_FULL, 0)) {
			if ((HRESULT)GetLastError() != NTE_BAD_KEYSET)
				return (0);
			if (!CryptAcquireContext(&p, NULL, NULL, PROV_RSA_FULL,
			    CRYPT_NEWKEYSET))
				return (0);
		}
		has_provider = 1;
	}
	return (CryptGenRandom(p, len, buf) ? 1 : 0);
}
#else
static char
arc4_writeback(uint8_t *buf, size_t n, char do_rd)
{
	int fd;

#ifdef arc4random_pushk
	fd = arc4random_pushk(buf, n);
	memcpy(buf, &fd, sizeof (fd));
	return (do_rd ? 0 : 1);
#else
	if ((fd = open(__randomdev, O_WRONLY)) != -1) {
		if (write(fd, buf, n) < 4)
			do_rd = 1;
		close(fd);
	}
	return (do_rd || fd == -1 ? 0 : 1);
#endif
}
#endif

#if defined(USE_MS_CRYPTOAPI) || defined(arc4random_pushk)
uint32_t
arc4random_pushb(const void *src, size_t len)
{
	size_t rlen;
	union {
		uint8_t buf[256];
		struct timeval tv;
		uint32_t xbuf;
	} idat;
	const uint8_t *cbuf = (const uint8_t *)src;
	uint32_t res = 1;

	if (!rs_initialized) {
		arc4_init(&rs);
		rs_initialized = 1;
	}

	gettimeofday(&idat.tv, NULL);
	for (rlen = 0; rlen < len; ++rlen)
		idat.buf[rlen % sizeof (idat)] ^= cbuf[rlen];
	rlen = MIN(sizeof (idat), MAX(sizeof (struct timeval), len));

	if (arc4_writeback(&idat.buf[0], rlen, 1))
		res = 0;
	arc4_addrandom(&rs, &idat.buf[0], rlen);
	if (res)
		res = idat.xbuf;
	else
		/* we got entropy from the kernel, so consider us stirred */
		stir_finish(&rs, idat.buf[5]);
	return (res ^ arc4_getword(&rs));
}
#endif

static void
arc4_atexit(void)
{
	struct {
		pid_t spid;
		int cnt;
		u_int8_t carr[240];
	} buf;
	int i = 0;

	while (i < 240)
		buf.carr[i++] = arc4_getbyte(&rs);
	buf.spid = arc4_stir_pid;
	buf.cnt = arc4_count;

	arc4_writeback((uint8_t *)&buf, sizeof (buf), 0);
}
