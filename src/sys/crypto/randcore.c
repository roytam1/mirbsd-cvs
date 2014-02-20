/* $MirOS: src/sys/crypto/randcore.c,v 1.11 2014/02/19 22:17:25 tg Exp $ */

/*-
 * Copyright © 2010, 2011, 2014
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un‐
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person’s immediate fault when using the work as intended.
 *-
 * This file contains the core random device implementation and stee‐
 * ring point for the random subsystem in MirBSD. It also contains an
 * implementation of the “lopool”, i.e. a hashed pool where userspace
 * non-root processes and the kernel can send “untrusted” entropy to,
 * which then is periodically “collapsed” into an arcfour state named
 * lopool_collapse which in turn is used by arc4random_reinit when it
 * stirs the main arcfour state used in arc4random(9).
 */

#define IN_RANDOM_CORE

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/conf.h>
#include <sys/kernel.h>
#include <sys/timeout.h>
#include <crypto/randimpl.h>
#include <mirhash.h>

/* import from vers.c generated by conf/newvers.sh */
extern uint32_t _randseed;
/* only bytes actually changed by config(8) */
extern unsigned char initial_entropy[16];

struct rnd_pooladd {
	union {
		struct timeval tv;
#if defined(I586_CPU) || defined(I686_CPU)
		unsigned long long tsc;
#endif
	} u;
	const void *sp, *dp;
	size_t sz;
};

void rnd_lopool_dequeue(void *);

/*
 * This variable secures the following things: rndpool (tytso code) is
 * operational; timeouts for arc4random and lopool-collapse can be run;
 * lopool-collapse arcfour state has been initialised
 */
int rnd_attached = 0;

size_t lopool_content = 0;
uint32_t lopool_uhash[32];
uint8_t lopool_uptr = 0;

struct arcfour_status lopool_collapse;
struct timeout arc4random_timeout;
struct timeout rnd_lopool_timeout;

/*
 * Backend routine for adding some bytes, together with pointer,
 * size, stack, and timing information, into the hash lopool.
 * We use the BAFH transformation only for folding the user-
 * specified information into 32 BAFH states (128 bytes)
 * and count the bytes we added. (rnd_lopool_addh adds an BAFH
 * hash of the data, not the data itself.) Once the content is
 * 128 bytes or more, rnd_lopool_dequeue collapses them into
 * lopool_collapse where it will be picked up by the next run
 * of the arc4random(9) stir function.
 */
static void
rnd_pool_add(struct rnd_pooladd *sa, const void *d, size_t n)
{
	int s;

#if defined(I586_CPU) || defined(I686_CPU)
	if (pentium_mhz) {
		__asm __volatile("rdtsc" : "=A" (sa->u.tsc));
	} else
#endif
	    {
		/* cannot use memcpy since mono_time is volatile */
		sa->u.tv.tv_sec = mono_time.tv_sec;
		sa->u.tv.tv_usec = mono_time.tv_usec;
	}
	sa->sp = sa;

	RNDEBUG(RD_HASHLOPOOL, "rnd: lopool += %lu(%lu) bytes\n",
	    (u_long)n, (u_long)sa->sz);

	s = splhigh();
	arc4random_roundhash(lopool_uhash, &lopool_uptr, sa, sizeof(*sa));
	arc4random_roundhash(lopool_uhash, &lopool_uptr, d, n);
	lopool_content += n;
	rndstats.lopool_bytes += n;
	++rndstats.lopool_enq;
	splx(s);
}

/*
 * called from most of the initialisation code; historical because
 * we used to be unable to run either lopool’s predecessor or
 * arc4random itself early in the boot process; nowadays, this is
 * merely a “big data” function, e.g. for the pre-start log message
 * buffer, which may have leftovers from the last kernel, or some
 * filesystem superblock or other data of few entropic value
 */
void
rnd_lopool_addh(const void *vp, size_t n)
{
	struct rnd_pooladd pa;
	uint32_t h;

	h = arc4random();
	BAFHUpdateMem_reg(h, vp, n);
	BAFHFinish_reg(h);

	pa.dp = vp;
	pa.sz = n;
	rnd_pool_add(&pa, &h, sizeof(h));
}

/* these two directly add their argument into the lopool */

/* pointer and length, read data */
void
rnd_lopool_add(const void *buf, size_t len)
{
	struct rnd_pooladd pa;

	pa.dp = buf;
	pa.sz = len;
	rnd_pool_add(&pa, buf, len);
}

/* integral argument, passed on the stack */
void
rnd_lopool_addv(unsigned long v)
{
	struct rnd_pooladd pa;

	pa.sz = 0;
	rnd_pool_add(&pa, &v, sizeof(v));
}

#ifndef rnd_lopool_addvq
/* for use by the hardclockent routines: no RNDEBUG, no counting */
void
rnd_lopool_addvq(unsigned long v)
{
	int s;

	s = splhigh();
	arc4random_roundhash(lopool_uhash, &lopool_uptr, &v, sizeof(v));
	splx(s);
}
#endif

/*
 * This is the function called all 1‥3 seconds to collapse the
 * lopool’s hash into its arcfour state if there was enough data.
 */
void
rnd_lopool_dequeue(void *arg __unused)
{
	int s;
	struct timeval tv[2];

	s = splhigh();

	if (!rnd_attached) {
		RNDEBUG(RD_ALWAYS, "rnd: lopool dequeue before attach\n");
		goto out;
	}

	/* if we were called directly instead of from timeout */
	timeout_del(&rnd_lopool_timeout);

	if (lopool_content >= 128) {
		RNDEBUG(RD_ARC4LOPOOL, "rnd: lopool dequeues %lu bytes\n",
		    (u_long)lopool_content);

		/* add current time (mono and TAI) first */
		tv[0].tv_sec = mono_time.tv_sec;
		tv[0].tv_usec = mono_time.tv_usec;
		tv[1].tv_sec = time.tv_sec;
		tv[1].tv_usec = time.tv_usec;
		arc4random_roundhash(lopool_uhash, &lopool_uptr, tv,
		    sizeof(tv));

		/* finalise all 32 one-at-a-time hashes */
		for (lopool_uptr = 0; lopool_uptr < 32; ++lopool_uptr)
			BAFHFinish_mem(lopool_uhash[lopool_uptr]);

		/* stir the collapse pool with the result */
		arcfour_ksa(&lopool_collapse, (void *)lopool_uhash,
		    sizeof(lopool_uhash));

		/* assert(lopool_uptr == 32); */
		while (lopool_uptr--)
			/* re-initialise all 32 BAFH states from RNG */
			lopool_uhash[lopool_uptr] = arc4random();

		/* sync statistic data / counter */
		lopool_content = 0;
		lopool_uptr = 0;

		/*
		 * note: we don't throw away the “early keystream” like
		 * with arc4random(9) because this is never used/exposed
		 * to anything save arc4random_reinit, and we don’t care
		 * about bias here either, this is just for distribution
		 */

		++rndstats.lopool_deq;
	}

	/* 1 + [0;2[ seconds */
	timeout_add(&rnd_lopool_timeout, hz + arc4random_uniform(hz << 1));

 out:
	splx(s);
}


void
randomattach(void)
{
	if (rnd_attached) {
		RNDEBUG(RD_ALWAYS, "random: second attach\n");
		return;
	}

	timeout_set(&arc4random_timeout, arc4random_reinit, NULL);
	timeout_set(&rnd_lopool_timeout, rnd_lopool_dequeue, NULL);

	/* dev/rnd.c */
	rndpool_init();

	arcfour_init(&lopool_collapse);
	/* this dword is where also locore.s writes to */
	add_true_randomness(
	    ((uint32_t)initial_entropy[3] << 24) |
	    ((uint32_t)initial_entropy[2] << 16) |
	    ((uint32_t)initial_entropy[1] << 8) |
	    (uint32_t)initial_entropy[0]);
	memcpy(initial_entropy, &_randseed, 4);
	arcfour_ksa(&lopool_collapse, initial_entropy, 16);
	/* just in case there’s something actually using these */
	arc4random_buf(initial_entropy, 16);
	_randseed = arc4random();

	rnd_attached = 1;
	/* initialises both lopool and arc4random timeouts */
	rnd_flush();
}


/* called from RNDSTIRARC4 ioctl by pid 1, during boot and reboot */
void
rnd_flush(void)
{
	int s;

	RNDEBUG(RD_ALWAYS, "rnd: flushing\n");
	s = splhigh();
	if (lopool_content < 128)
		/* force rnd_lopool_dequeue() to act */
		lopool_content = 128;
	rnd_lopool_dequeue(NULL);
	arc4random_reinit(NULL);
	splx(s);
}
