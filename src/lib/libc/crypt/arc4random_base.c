/*-
 * Copyright (c) 2010, 2011, 2012, 2014
 *	Thorsten Glaser <tg@mirbsd.org>
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
 *-
 * The idea of an arc4random(3) stems from David Mazieres for OpenBSD
 * but this has been reimplemented, improved, corrected, modularised.
 * The idea of pushing entropy back to the kernel on stir and after a
 * fork or before an exit is MirBSD specific.
 */

#include <sys/param.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <syskern/libckern.h>
#include <syskern/mirhash.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "arc4random.h"
#include "thread_private.h"

__RCSID("$MirOS: src/lib/libc/crypt/arc4random_base.c,v 1.10 2014/02/19 21:36:06 tg Exp $");

/* zero-initialises */
struct arc4random_status a4state;

void
arc4random_atexit(void)
{
	int mib[2];

	if (!a4state.a4s_initialised)
		return;

	_ARC4_LOCK();
	/* first put everything we have into the pool */
	arc4random_roundhash(a4state.pool, &a4state.a4s_poolptr,
	    &a4state.cipher, sizeof(a4state.cipher));
	arc4random_roundhash(a4state.pool, &a4state.a4s_poolptr,
	    &a4state.otherinfo, sizeof(a4state.otherinfo));
	/* then write the pool into the kernel */
	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;
	sysctl(mib, 2, NULL, NULL, a4state.pool, sizeof(a4state.pool));
	/* then, just in case we do NOT finish, blind */
	(void)arcfour_byte(&a4state.cipher);
	bzero(a4state.pool, sizeof(a4state.pool));
	_ARC4_UNLOCK();
}

u_int32_t
arc4random(void)
{
	uint32_t v;
	pid_t mypid = 0;

	_ARC4_LOCK();

	/* reinitialise after fork, (count) bytes or if not initialised */
	a4state.a4s_count -= 4;
	if (a4state.a4s_count <= 0 || !a4state.a4s_initialised ||
	    (a4state.a4s_stir_pid != (mypid = getpid())))
		arc4random_stir_locked(mypid);

	/* randomly skip a byte or two */
	/*XXX this should be constant-time */
	if (arcfour_byte(&a4state.cipher) & 1)
		(void)arcfour_byte(&a4state.cipher);

	v = ((uint32_t)arcfour_byte(&a4state.cipher) << 24) |
	    ((uint32_t)arcfour_byte(&a4state.cipher) << 16) |
	    ((uint32_t)arcfour_byte(&a4state.cipher) << 8) |
	    ((uint32_t)arcfour_byte(&a4state.cipher));

	_ARC4_UNLOCK();
	return (v);
}

void
arc4random_stir_locked(pid_t mypid)
{
	size_t n;
	unsigned int carry;
	int mib[2];
	union {
		uint8_t charbuf[256];
		uint32_t intbuf[64];
		struct {
			struct timespec rtime;
			struct timespec vtime;
			struct timespec ptime;
			struct timespec ntime;
			pid_t thepid;
		} tmpbuf;
	} sbuf;

	if (!a4state.a4s_initialised) {
		arcfour_init(&a4state.cipher);
		a4state.a4s_poolptr = 0;
	}
	carry = arcfour_byte(&a4state.cipher);
	/* throw stuff into the roundhash pool */
	arc4random_roundhash(a4state.pool, &a4state.a4s_poolptr,
	    &a4state.otherinfo, sizeof(a4state.otherinfo));
	clock_gettime(CLOCK_REALTIME, &sbuf.tmpbuf.rtime);
	clock_gettime(CLOCK_VIRTUAL, &sbuf.tmpbuf.vtime);
	clock_gettime(CLOCK_PROF, &sbuf.tmpbuf.ptime);
	clock_gettime(CLOCK_MONOTONIC, &sbuf.tmpbuf.ntime);
	sbuf.tmpbuf.thepid = mypid = mypid ? mypid : getpid();
	arc4random_roundhash(a4state.pool, &a4state.a4s_poolptr,
	    &sbuf.tmpbuf, sizeof(sbuf.tmpbuf));

	/* fill first 128 bytes with roundhash pool */
	n = 1 + (carry & 1);
	carry >>= 1;
	while (n--)
		(void)arcfour_byte(&a4state.cipher);
	for (n = 0; n < 32; ++n) {
		register uint32_t h;

		h = a4state.pool[n];
		/* mask and mix */
		BAFHUpdateOctet_reg(h, arcfour_byte(&a4state.cipher));
		BAFHFinish_reg(h);
		sbuf.intbuf[n] = h;
	}

	/* fill second 128 bytes with local random stuff */
	n = 1 + (carry & 1);
	carry >>= 1;
	while (n--)
		(void)arcfour_byte(&a4state.cipher);
	for (n = 128; n < 256; ++n)
		sbuf.charbuf[n] = arcfour_byte(&a4state.cipher);
	n = carry & 3;
	carry &= 0x3C;
	while (n--)
		(void)arcfour_byte(&a4state.cipher);

	/* exchange full 256 bytes with kernel */
	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;
	n = sizeof(sbuf);
	sysctl(mib, 2, sbuf.charbuf, &n, sbuf.charbuf, sizeof(sbuf));
	/* if (n != sizeof(sbuf)) something went wrong inside the kernel */

	/* mix first 128 bytes with/into roundhash pool */
	for (n = 0; n < 32; ++n) {
		register uint32_t ha, hr;

		ha = (a4state.pool[n] & 0xFFFF0000) |
		    (sbuf.intbuf[n] & 0x0000FFFF);
		hr = (a4state.pool[n] & 0x0000FFFF) |
		    (sbuf.intbuf[n] & 0xFFFF0000);
		/* mix then mask for arc4random */
		BAFHFinish_reg(ha);
		BAFHUpdateOctet_reg(ha, arcfour_byte(&a4state.cipher));
		sbuf.intbuf[n] = ha;
		/* mix then mask for roundhash */
		BAFHFinish_reg(hr);
		BAFHUpdateOctet_reg(hr, arcfour_byte(&a4state.cipher));
		a4state.pool[n] = hr;
	}
	/* mix full 256 bytes into arc4random pool */
	arcfour_ksa256(&a4state.cipher, sbuf.charbuf);

	/* trash stack */
	bzero(sbuf.charbuf, sizeof(sbuf));

	/* discard early keystream */
	carry += 256 * 12 + (arcfour_byte(&a4state.cipher) & 0x1F);
	while (carry--)
		(void)arcfour_byte(&a4state.cipher);

	a4state.a4s_poolptr = 0;
	a4state.a4s_initialised = true;
	a4state.a4s_stir_pid = mypid;
	a4state.a4s_count = 1600000;
}
