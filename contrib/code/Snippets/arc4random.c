static const char __vcsid[] = "@(#) MirOS contributed arc4random.c (old)"
    "\n	@(#)rcsid_master: $MirOS: contrib/code/Snippets/arc4random.c,v 1.15 2009/08/02 11:24:40 tg Exp $"
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
 * Copyright (c) 2008, 2009
 *	Thorsten Glaser <tg@mirbsd.org>
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
#if defined(HAVE_SYS_SYSCTL_H) && HAVE_SYS_SYSCTL_H
#include <sys/sysctl.h>
#endif
#include <fcntl.h>
#if defined(HAVE_STDINT_H) && HAVE_STDINT_H
#include <stdint.h>
#elif defined(USE_INTTYPES)
#include <inttypes.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#if defined(__CYGWIN__) || defined(WIN32)
#define USE_MS_CRYPTOAPI
#define REDEF_USCORETYPES
#endif

#ifdef USE_MS_CRYPTOAPI
#define WIN32_WINNT 0x400
#define _WIN32_WINNT 0x400
#include <windows.h>
#include <wincrypt.h>

static uint8_t w32_buf[16*16384];	/* force reseed */
static uint8_t w32_hklm[80];		/* registry key (MS, Admin) */
static uint8_t w32_hkcu[256];		/* registry key (per user) */

static char w32_subkey[] = "SOFTWARE\\Microsoft\\Cryptography\\RNG";
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

static struct arc4_stream {
	uint8_t i;
	uint8_t j;
	uint8_t s[256];
} arc4_ctx;

static int rs_initialized;
static pid_t arc4_stir_pid;
static int arc4_count;
static const char __randomdev[] = _PATH_URANDOM;

static uint8_t arc4_getbyte(void);
static void stir_finish(int);
static void arc4_atexit(void);
static char arc4_writeback(uint8_t *, size_t, char);

#ifndef arc4random_pushk
u_int32_t arc4random(void);
void arc4random_addrandom(u_char *, int);
void arc4random_stir(void);
#ifdef USE_MS_CRYPTOAPI
uint32_t arc4random_pushb(const void *, size_t);
#endif
#endif

static void
arc4_init(void)
{
	int n;

	for (n = 0; n < 256; n++)
		arc4_ctx.s[n] = (uint8_t)n;
	arc4_ctx.i = 0;
	arc4_ctx.j = 0;
}

static void
arc4_addrandom(u_char *dat, int datlen)
{
	int n;
	uint8_t si;

	arc4_ctx.i--;
	for (n = 0; n < 256; n++) {
		arc4_ctx.i++;
		si = arc4_ctx.s[arc4_ctx.i];
		arc4_ctx.j = (uint8_t)(arc4_ctx.j + si + dat[n % datlen]);
		arc4_ctx.s[arc4_ctx.i] = arc4_ctx.s[arc4_ctx.j];
		arc4_ctx.s[arc4_ctx.j] = si;
	}
	arc4_ctx.j = arc4_ctx.i;
}

static void
arc4_stir(void)
{
	int fd;
	struct {
		struct timeval tv;
		pid_t pid;
		u_int rnd[(128 - (sizeof(struct timeval) + sizeof(pid_t))) / sizeof(u_int)];
	} rdat;
	size_t sz = 0;

	gettimeofday(&rdat.tv, NULL);
	rdat.pid = getpid();
	memcpy(rdat.rnd, __vcsid, MIN(sizeof(__vcsid), sizeof(rdat.rnd)));

#ifdef USE_MS_CRYPTOAPI
	if (arc4_writeback((char *)rdat.rnd, sizeof(rdat.rnd), 1))
		goto stir_okay;
#endif

	/* /dev/urandom is a multithread interface, sysctl is not. */
	/* Try to use /dev/urandom before sysctl. */
	fd = open(__randomdev, O_RDONLY);
	if (fd != -1) {
		sz = (size_t)read(fd, rdat.rnd, sizeof(rdat.rnd));
		close(fd);
	}
	if (sz > sizeof(rdat.rnd))
		sz = 0;
	if (fd == -1 || sz != sizeof(rdat.rnd)) {
		/* /dev/urandom failed? Maybe we're in a chroot. */
#if /* Linux */ defined(_LINUX_SYSCTL_H) || \
    /* OpenBSD */ (defined(CTL_KERN) && defined(KERN_ARND))
		int mib[3], nmib = 3;
		size_t i = sz / sizeof(u_int), len;

#ifdef _LINUX_SYSCTL_H
		mib[0] = CTL_KERN;
		mib[1] = KERN_RANDOM;
		mib[2] = RANDOM_UUID;
#else
		mib[0] = CTL_KERN;
		mib[1] = KERN_ARND;
		nmib = 2;
#endif

		while (i < sizeof(rdat.rnd) / sizeof(u_int)) {
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
	fd = arc4_getbyte();

	/*
	 * Time to give up. If no entropy could be found then we will just
	 * use gettimeofday and getpid.
	 */
	arc4_addrandom((u_char *)&rdat, sizeof(rdat));

	stir_finish(fd);
}

static void
stir_finish(int av)
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
	n = 256 * 4 + (arc4_getbyte() & 0x0FU);
	while (av) {
		n += (av & 0x0F);
		av >>= 4;
	}
	while (n--)
		arc4_getbyte();
	while (n < sizeof(tb))
		tb[n++] = arc4_getbyte();
	if (arc4_writeback(tb, sizeof(tb), 0))
		arc4_getbyte();
	arc4_count = 400000;
}

static uint8_t
arc4_getbyte(void)
{
	uint8_t si, sj;

	arc4_ctx.i++;
	si = arc4_ctx.s[arc4_ctx.i];
	arc4_ctx.j = (uint8_t)(arc4_ctx.j + si);
	sj = arc4_ctx.s[arc4_ctx.j];
	arc4_ctx.s[arc4_ctx.i] = sj;
	arc4_ctx.s[arc4_ctx.j] = si;
	return (arc4_ctx.s[(si + sj) & 0xff]);
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
	if (!rs_initialized) {
		arc4_init();
		rs_initialized = 1;
		atexit(arc4_atexit);
	}
	arc4_stir();
}

void
arc4random_addrandom(u_char *dat, int datlen)
{
	if (!rs_initialized)
		arc4random_stir();
	arc4_addrandom(dat, datlen);
}

u_int32_t
arc4random(void)
{
	if (--arc4_count == 0 || !rs_initialized || arc4_stir_pid != getpid())
		arc4random_stir();
	return arc4_getword();
}

/*
 * Returns 0 if write error; 0 if do_rd and read error;
 * 1 if !do_rd and read error but not write error;
 * 1 if no error occured.
 */
static char
arc4_writeback(uint8_t *buf, size_t len, char do_rd)
{
#ifdef USE_MS_CRYPTOAPI
	static char has_provider = 0;
	static HCRYPTPROV p;
	HKEY hKeyLM, hKeyCU;
	DWORD ksz;
	char rc = 6, has_rkey = 0, w32_a4b[16];
	size_t i, j, xlen;

	for (i = 0; i < sizeof(w32_a4b); ++i)
		w32_a4b[i] = arc4_getbyte();
	for (i = arc4_getbyte() & 15; i; --i)
		arc4_getbyte();

	ksz = sizeof(w32_buf);
	if ((/* read-write */ RegOpenKeyEx(HKEY_LOCAL_MACHINE, w32_subkey,
	    0, KEY_QUERY_VALUE | KEY_SET_VALUE, &hKeyLM) == ERROR_SUCCESS ||
	    /* try read-only */ RegOpenKeyEx(HKEY_LOCAL_MACHINE, w32_subkey,
	    0, KEY_QUERY_VALUE, &hKeyLM) == ERROR_SUCCESS) && /* get value */
	    (RegQueryValueEx(hKeyLM, "Seed", NULL, NULL, w32_buf, &ksz) ==
	    ERROR_SUCCESS) && /* got any content? */ ksz) {
		/* we got HKLM key, read-write or read-only */
		has_rkey |= 1;
		/* move content to destination */
		memset(w32_hklm, '\0', sizeof(w32_hklm));
		for (i = 0; i < MAX(ksz, sizeof(w32_hklm)); ++i)
			w32_hklm[i % sizeof(w32_hklm)] ^= w32_buf[i % ksz];
	}
	ksz = sizeof(w32_buf);
	if ((/* read-write */ RegCreateKeyEx(HKEY_CURRENT_USER, w32_subkey,
	    0, NULL, 0, KEY_QUERY_VALUE | KEY_SET_VALUE, NULL, &hKeyCU,
	    NULL) == ERROR_SUCCESS || /* R/O */ RegOpenKeyEx(HKEY_CURRENT_USER,
	    w32_subkey, 0, KEY_QUERY_VALUE, &hKeyLM) == ERROR_SUCCESS) &&
	    /* get value */ (RegQueryValueEx(hKeyLM, "Seed", NULL, NULL,
	    w32_buf, &ksz) == ERROR_SUCCESS) && /* got any content? */ ksz) {
		/* we got HKCU key, created, read-write or read-only */
		has_rkey |= 2;
		/* move content to destination */
		memset(w32_hkcu, '\0', sizeof(w32_hkcu));
		for (i = 0; i < MAX(ksz, sizeof(w32_hkcu)); ++i)
			w32_hkcu[i % sizeof(w32_hkcu)] ^= w32_buf[i % ksz];
	}

	if (!has_provider) {
		if (!CryptAcquireContext(&p, NULL, NULL, PROV_RSA_FULL, 0)) {
			if ((HRESULT)GetLastError() != NTE_BAD_KEYSET)
				goto nogen_out;
			if (!CryptAcquireContext(&p, NULL, NULL, PROV_RSA_FULL,
			    CRYPT_NEWKEYSET))
				goto nogen_out;
		}
		has_provider = 1;
	}
	i = 0;
	while (i < 256)
		w32_buf[i++] = arc4_getbyte();
	if (!CryptGenRandom(p, sizeof(w32_buf), w32_buf)) {
 nogen_out:
		rc |= 1;
		memset(w32_buf, '\0', 256);
	}
	xlen = MIN(sizeof(w32_buf) - sizeof(w32_hklm) - sizeof(w32_hkcu) -
	    sizeof(w32_a4b), len);
	j = xlen + sizeof(w32_buf) + sizeof(w32_hklm) + sizeof(w32_hkcu) +
	    sizeof(w32_a4b);
	for (i = 0; i < MAX(j, len); ++i)
		w32_buf[i % j] ^= w32_hklm[i % sizeof(w32_hklm)] ^
		    w32_hkcu[i % sizeof(w32_hkcu)] ^ buf[i % len] ^
		    arc4_getbyte();
	if (has_rkey & 1) {
		if (RegSetValueEx(hKeyLM, "Seed", 0, REG_BINARY,
		    w32_buf, sizeof(w32_hklm)) == ERROR_SUCCESS)
			rc &= ~2;
		RegCloseKey(hKeyLM);
	}
	if (has_rkey & 2) {
		if (RegSetValueEx(hKeyCU, "Seed", 0, REG_BINARY,
		    w32_buf + sizeof(w32_hklm), sizeof(w32_hkcu)) ==
		    ERROR_SUCCESS)
			rc &= ~4;
		RegCloseKey(hKeyCU);
	}
	for (i = 0; i < sizeof(w32_a4b); ++i)
		w32_a4b[i] ^= w32_buf[sizeof(w32_hklm) + sizeof(w32_hkcu) + i];
	arc4_addrandom(w32_a4b, sizeof(w32_a4b));

	i = sizeof(w32_hklm) + sizeof(w32_hkcu) + sizeof(w32_a4b);
	while (len) {
		memcpy(buf, w32_buf + i, xlen);
		buf += xlen;
		i += xlen;
		len -= xlen;
	}

	memset(w32_buf, '\0', sizeof(w32_buf));

	return (
	    /* read error occured */
	    (!has_rkey && (rc & 1)) ? 0 :
	    /* don't care about write errors */
	    !do_rd ? 1 :
	    /* couldn't write */
	    (rc & 6) == 6 ? 0 :
	    /* at least one RegSetValueEx succeeded */
	    1);
#elif defined(arc4random_pushk)
	uint32_t num;

	num = arc4random_pushk(buf, len);
	memcpy(buf, &num, sizeof(num));
	return (do_rd ? 0 : 1);
#else
	int fd;

	if ((fd = open(__randomdev, O_WRONLY)) != -1) {
		if (write(fd, buf, len) < 4)
			do_rd = 1;
		close(fd);
	}
	return (do_rd || fd == -1 ? 0 : 1);
#endif
}

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
		arc4_init();
		rs_initialized = 1;
	}

	gettimeofday(&idat.tv, NULL);
	for (rlen = 0; rlen < len; ++rlen)
		idat.buf[rlen % sizeof(idat)] ^= cbuf[rlen];
	rlen = MIN(sizeof(idat), MAX(sizeof(struct timeval), len));

	if (arc4_writeback(&idat.buf[0], rlen, 1))
		res = 0;
	arc4_addrandom(&idat.buf[0], rlen);
	if (res)
		res = idat.xbuf;
	else
		/* we got entropy from the kernel, so consider us stirred */
		stir_finish(idat.buf[5]);
	return (res ^ arc4_getword());
}
#endif

static void
arc4_atexit(void)
{
	struct {
		pid_t spid;
		int cnt;
		uint8_t carr[240];
	} buf;
	int i = 0;

	while (i < 240)
		buf.carr[i++] = arc4_getbyte();
	buf.spid = arc4_stir_pid;
	buf.cnt = arc4_count;

	arc4_writeback((uint8_t *)&buf, sizeof(buf), 0);
}
