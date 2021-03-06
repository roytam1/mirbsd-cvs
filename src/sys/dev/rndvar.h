/**	$MirOS: src/sys/dev/rndvar.h,v 1.30 2010/09/25 01:08:49 tg Exp $ */
/*	$OpenBSD: rndvar.h,v 1.19 2003/11/03 18:24:28 tedu Exp $	*/

/*
 * Copyright (c) 2004, 2005, 2006, 2008, 2009, 2010, 2013
 *	Thorsten Glaser <tg@mirbsd.org>
 * Copyright (c) 1996,2000 Michael Shalayeff.
 *
 * This software derived from one contributed by Theodore Ts'o.
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
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef __RNDVAR_H__
#define __RNDVAR_H__

#ifndef POOLWORDS
#define POOLWORDS	1024	/* power of 2 - note this is 32-bit words */
#endif

#define RND_RND		0	/* real hw entropy like nuclear chips */
#define RND_SRND	1	/* strong random source */
#define RND_URND	2	/* less strong random source */
#define RND_PRND	3	/* pseudo random source */
#define RND_ARND	4	/* arcfour based stretching RNG */
#define RND_NODEV	5	/* first invalid minor device number */

#define	RND_SRC_TRUE	0
#define	RND_SRC_TIMER	1
#define	RND_SRC_MOUSE	2
#define	RND_SRC_TTY	3
#define	RND_SRC_DISK	4
#define	RND_SRC_NET	5
#define	RND_SRC_AUVIS	6
#define	RND_SRC_IMACS	7
/* size of stats structure */
#define	RND_SRC_NUM	8
/* internal-use quirk */
#define	RND_SRC_LPC	24

struct rndstats {
	quad_t rnd_total;	/* total bits of entropy generated */
	quad_t rnd_used;	/* strong data bits read so far */
	quad_t rnd_reads;	/* strong read calls */
	quad_t arc4_reads;	/* aRC4 data bytes read so far */
	quad_t arc4_nstirs;	/* arc4 pool stirs */
	quad_t arc4_stirs;	/* arc4 pool stirs (bytes used) */
	quad_t lopool_deq;	/* calls to lopool dequeue (128 bytes each) */
	quad_t lopool_enq;	/* calls to lopool enqueue */
	quad_t lopool_bytes;	/* bytes added during lopool enqueue */

	quad_t rnd_pad_who_this_uses_is_stupid[2];

	quad_t rnd_waits;	/* sleeps for data */
	quad_t rnd_enqs;	/* enqueue calls */
	quad_t rnd_deqs;	/* dequeue calls */
	quad_t rnd_drops;	/* queue-full drops */
	quad_t rnd_drople;	/* queue low watermark low entropy drops */

	quad_t rnd_ed[32];	/* entropy feed distribution */
	quad_t rnd_sc[RND_SRC_NUM]; /* add* calls */
	quad_t rnd_sb[RND_SRC_NUM]; /* add* bits */
};

#ifdef _KERNEL

#include <sys/slibkern.h>

extern struct rndstats rndstats;

#define	add_true_randomness(d)	enqueue_randomness(RND_SRC_TRUE,  (int)(d))
#define	add_timer_randomness(d)	enqueue_randomness(RND_SRC_TIMER, (int)(d))
#define	add_mouse_randomness(d)	enqueue_randomness(RND_SRC_MOUSE, (int)(d))
#define	add_tty_randomness(d)	enqueue_randomness(RND_SRC_TTY,   (int)(d))
#define	add_disk_randomness(d)	enqueue_randomness(RND_SRC_DISK,  (int)(d))
#define	add_net_randomness(d)	enqueue_randomness(RND_SRC_NET,   (int)(d))
#define	add_auvis_randomness(d)	enqueue_randomness(RND_SRC_AUVIS, (int)(d))
#define	add_imacs_randomness(d)	enqueue_randomness(RND_SRC_IMACS, (int)(d))
/* compatibility */
#define	add_audio_randomness(d)	enqueue_randomness(RND_SRC_AUVIS, (int)(d))
#define	add_video_randomness(d)	enqueue_randomness(RND_SRC_AUVIS, (int)(d))

void enqueue_randomness(int, int);
void get_random_bytes(void *, size_t)
    __attribute__((__bounded__(__string__, 1, 2)));
void arc4random_buf(void *, size_t)
    __attribute__((__bounded__(__string__, 1, 2)));
u_int32_t arc4random(void);

void rnd_lopool_add(const void *, size_t)
    __attribute__((__bounded__(__string__, 1, 2)));
void rnd_lopool_addh(const void *, size_t)
    __attribute__((__bounded__(__string__, 1, 2)));
void rnd_lopool_addv(unsigned long);

#endif /* _KERNEL */

#endif /* __RNDVAR_H__ */
