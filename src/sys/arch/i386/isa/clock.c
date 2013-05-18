/**	$MirOS: src/sys/arch/i386/isa/clock.c,v 1.13 2011/02/19 13:04:59 tg Exp $ */
/*	$OpenBSD: clock.c,v 1.31 2004/02/27 21:07:49 grange Exp $	*/
/*	$NetBSD: clock.c,v 1.39 1996/05/12 23:11:54 mycroft Exp $	*/

/*-
 * Copyright (c) 2004, 2005, 2010, 2011
 *	Thorsten Glaser <tg@mirbsd.org>
 * Copyright (c) 1993, 1994 Charles Hannum.
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz and Don Ahn.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
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
 *
 *	@(#)clock.c	7.2 (Berkeley) 5/12/91
 */
/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
  Copyright 1988, 1989 by Intel Corporation, Santa Clara, California.

		All Rights Reserved

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appears in all
copies and that both the copyright notice and this permission notice
appear in supporting documentation, and that the name of Intel
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

INTEL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL INTEL BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
 * Primitive clock interrupt routines.
 */
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/time.h>
#include <sys/kernel.h>
#include <sys/device.h>
#include <sys/taitime.h>
#include <sys/timeout.h>

#include <dev/rndvar.h>

#include <machine/cpu.h>
#include <machine/intr.h>
#include <machine/pio.h>
#include <machine/cpufunc.h>

#include <dev/isa/isareg.h>
#include <dev/isa/isavar.h>
#include <dev/ic/mc146818reg.h>
#include <i386/isa/nvram.h>
#include <i386/isa/timerreg.h>

#include "pcppi.h"
#if (NPCPPI > 0)
#include <dev/isa/pcppivar.h>

#define __BROKEN_INDIRECT_CONFIG /* XXX */
#ifdef __BROKEN_INDIRECT_CONFIG
int sysbeepmatch(struct device *, void *, void *);
#else
int sysbeepmatch(struct device *, struct cfdata *, void *);
#endif
void sysbeepattach(struct device *, struct device *, void *);

struct cfattach sysbeep_ca = {
	sizeof(struct device), sysbeepmatch, sysbeepattach
};

struct cfdriver sysbeep_cd = {
	NULL, "sysbeep", DV_DULL
};

static int ppi_attached;
static pcppi_tag_t ppicookie;
#endif /* PCPPI */

void	spinwait(int);
void	findcpuspeed(void);
int	clockintr(void *);
int	gettick(void);
void	sysbeep(int, int);
int	rtcget(mc_todregs *);
void	rtcput(mc_todregs *);
int 	hexdectodec(int);
int	dectohexdec(int);
int	rtcintr(void *);
void	rtcdrain(void *);

u_int mc146818_read(void *, u_int);
void mc146818_write(void *, u_int, u_int);

#if defined(I586_CPU) || defined(I686_CPU)
int pentium_mhz;
#endif
#if defined(I486_CPU) || defined(I586_CPU) || defined(I686_CPU)
int clock_broken_latch;
#endif

#define	SECMIN	((unsigned)60)			/* seconds per minute */
#define	SECHOUR	((unsigned)(60*SECMIN))		/* seconds per hour */
#define	SECDAY	((unsigned long)86400)
#define	SECYR	((unsigned long)SECDAY * 365)

u_int
mc146818_read(sc, reg)
	void *sc;					/* XXX use it? */
	u_int reg;
{
	int s;
	u_char v;

	s = splhigh();
	outb(IO_RTC, reg);
	DELAY(1);
	v = inb(IO_RTC+1);
	DELAY(1);
	splx(s);
	return (v);
}

void
mc146818_write(sc, reg, datum)
	void *sc;					/* XXX use it? */
	u_int reg, datum;
{
	int s;

	s = splhigh();
	outb(IO_RTC, reg);
	DELAY(1);
	outb(IO_RTC+1, datum);
	DELAY(1);
	splx(s);
}

void
startrtclock(void)
{
	int s;

	findcpuspeed();		/* use the clock (while it's free)
					to find the cpu speed */
	initrtclock();

	/* Check diagnostic status */
	if ((s = mc146818_read(NULL, NVRAM_DIAG)) != 0)	/* XXX softc */
		printf("RTC BIOS diagnostic error %d %s\n", (unsigned int) s,
		    NVRAM_DIAG_BITS);
}

void
rtcdrain(void *v)
{
	struct timeout *to = (struct timeout *)v;

	if (to != NULL)
		timeout_del(to);

	/*
	 * Drain any un-acknowledged RTC interrupts.
	 * See comment in cpu_initclocks().
	 */
  	while (mc146818_read(NULL, MC_REGC) & MC_REGC_PF)
		; /* Nothing. */
}

void
initrtclock(void)
{
	/* initialize 8253 clock */
	outb(TIMER_MODE, TIMER_SEL0|TIMER_RATEGEN|TIMER_16BIT);

	/* Correct rounding will buy us a better precision in timekeeping */
	outb(IO_TIMER1, TIMER_DIV(hz) % 256);
	outb(IO_TIMER1, TIMER_DIV(hz) / 256);
}

int
clockintr(void *arg)
{
	struct clockframe *frame = arg;		/* not strictly necessary */

	hardclock(frame);
	return (1);
}

int
rtcintr(void *arg)
{
	struct clockframe *frame = arg;		/* not strictly necessary */
	u_int stat = 0;

	/*
	 * If rtcintr is 'late', next intr may happen immediately.
	 * Get them all. (Also, see comment in cpu_initclocks().)
	 */
	while (mc146818_read(NULL, MC_REGC) & MC_REGC_PF) {
		statclock(frame);
		stat = 1;
	}
	return (stat);
}

int
gettick(void)
{

#if defined(I586_CPU) || defined(I686_CPU)
	if (clock_broken_latch) {
		int v1, v2, v3;
		int w1, w2, w3;

		disable_intr();

		v1 = inb(TIMER_CNTR0);
		v1 |= inb(TIMER_CNTR0) << 8;
		v2 = inb(TIMER_CNTR0);
		v2 |= inb(TIMER_CNTR0) << 8;
		v3 = inb(TIMER_CNTR0);
		v3 |= inb(TIMER_CNTR0) << 8;

		enable_intr();

		if (v1 >= v2 && v2 >= v3 && v1 - v3 < 0x200)
			return (v2);

#define _swap_val(a, b) do { \
	int c = a; \
	a = b; \
	b = c; \
} while (0)

		/* sort v1 v2 v3 */
		if (v1 < v2)
			_swap_val(v1, v2);
		if (v2 < v3)
			_swap_val(v2, v3);
		if (v1 < v2)
			_swap_val(v1, v2);

		/* compute the middle value */
		if (v1 - v3 < 0x200)
			return (v2);
		w1 = v2 - v3;
		w2 = v3 - v1 + TIMER_DIV(hz);
		w3 = v1 - v2;
		if (w1 >= w2) {
			if (w1 >= w3)
				return (v1);
		} else {
			if (w2 >= w3)
				return (v2);
		}
		return (v3);
	} else
#endif
	{
		u_char lo, hi;

		disable_intr();
		/* Select counter 0 and latch it. */
		outb(TIMER_MODE, TIMER_SEL0 | TIMER_LATCH);
		lo = inb(TIMER_CNTR0);
		hi = inb(TIMER_CNTR0);

		enable_intr();
		return ((hi << 8) | lo);
	}
}

/*
 * Wait "n" microseconds.
 * Relies on timer 1 counting down from (TIMER_FREQ / hz) at TIMER_FREQ Hz.
 * Note: timer had better have been programmed before this is first used!
 * (Note that we use `rate generator' mode, which counts at 1:1; `square
 * wave' mode counts at 2:1).
 */
void
delay(int n)
{
	int limit, tick, otick;

	/*
	 * Read the counter first, so that the rest of the setup overhead is
	 * counted.
	 */
	otick = gettick();

#ifdef __GNUC__
	/*
	 * Calculate ((n * TIMER_FREQ) / 1e6) using explicit assembler code so
	 * we can take advantage of the intermediate 64-bit quantity to prevent
	 * loss of significance.
	 */
	n -= 5;
	if (n < 0)
		return;
	__asm __volatile("mul %2\n\tdiv %3"
			 : "=a" (n) 
			 : "0" (n), "r" (TIMER_FREQ), "r" (1000000)
			 : "%edx", "cc");
#else
	/*
	 * Calculate ((n * TIMER_FREQ) / 1e6) without using floating point and
	 * without any avoidable overflows.
	 */
	n -= 20;
	{
		int sec = n / 1000000,
		    usec = n % 1000000;
		n = sec * TIMER_FREQ +
		    usec * (TIMER_FREQ / 1000000) +
		    usec * ((TIMER_FREQ % 1000000) / 1000) / 1000 +
		    usec * (TIMER_FREQ % 1000) / 1000000;
	}
#endif

	limit = TIMER_FREQ / hz;

	while (n > 0) {
		tick = gettick();
		if (tick > otick)
			n -= limit - (tick - otick);
		else
			n -= otick - tick;
		otick = tick;
	}
}

#if (NPCPPI > 0)
int
sysbeepmatch(parent, match, aux)
	struct device *parent;
#ifdef __BROKEN_INDIRECT_CONFIG
	void *match;
#else
	struct cfdata *match;
#endif
	void *aux;
{
	return (!ppi_attached);
}

void
sysbeepattach(parent, self, aux)
	struct device *parent, *self;
	void *aux;
{
	printf("\n");

	ppicookie = ((struct pcppi_attach_args *)aux)->pa_cookie;
	ppi_attached = 1;
}
#endif

void
sysbeep(int pitch, int period)
{
#if (NPCPPI > 0)
	if (ppi_attached)
		pcppi_bell(ppicookie, pitch, period, 0);
#endif
}

unsigned int delaycount;	/* calibrated loop variable (1 millisecond) */

#define FIRST_GUESS   0x2000

void
findcpuspeed(void)
{
	unsigned int i, guess = FIRST_GUESS;
	int remainder;
	uint64_t j;

	goto start_loop;

	do {
		guess <<= 1;
		printf("clock: another round trying to find CPU speed\n");
 start_loop:
		if (!guess) {
			/* yuk */
			printf("clock: couldn't find CPU speed\n");
			delaycount = 1024;
			return;
		}

		/* Put counter in count down mode */
		outb(TIMER_MODE, TIMER_SEL0 | TIMER_16BIT | TIMER_RATEGEN);
		outb(TIMER_CNTR0, 0xff);
		outb(TIMER_CNTR0, 0xff);
		for (i = guess; i; i--)
			;
		/* Read the value left in the counter */
		remainder = gettick();
	} while (remainder == 0xFFFF);

	/*
	 * Formula for delaycount is:
	 *  (loopcount * timer clock speed) / (counter ticks * 1000)
	 */
	j = guess;
	j *= TIMER_DIV(1000);
	j /= 0xFFFF - remainder;
	if (j > 0xFFFFFFFFULL) {
		/* yuk */
		printf("clock: CPU speed too large\n");
		j = 0xFFFFFFFFULL;
	}
	delaycount = j;

	if (guess != FIRST_GUESS)
		printf("clock: if this is qemu, try with '-icount auto'\n");
}

#if defined(I586_CPU) || defined(I686_CPU)
void
calibrate_cyclecounter(void)
{
	uint64_t last_count;
#ifdef PENTIUM_BROKEN_TSC
	uint64_t next_count;
#else
#define next_count pentium_base_tsc
#endif
	/* XXX this is a hack, we'd better do precision timekeeping */
	struct timeval tv;

	disable_intr();
	tv = time;
	enable_intr();
	/* it's probably not exactly one second, but pretty good */
	tv.tv_sec++;

	__asm __volatile("rdtsc" : "=A" (last_count));
	delay(1000000);
	__asm __volatile("rdtsc" : "=A" (next_count));
	pentium_mhz = ((next_count - last_count) + 999999) / 1000000;

	disable_intr();
	time = tv;
	enable_intr();
#undef next_count
}
#endif

void
cpu_initclocks(void)
{
	static struct timeout rtcdrain_timeout;
	stathz = 128;
	profhz = 1024;

	/*
	 * XXX If you're doing strange things with multiple clocks, you might
	 * want to keep track of clock handlers.
	 */
	(void)isa_intr_establish(NULL, 0, IST_PULSE, IPL_CLOCK, clockintr,
	    0, "clock");
	(void)isa_intr_establish(NULL, 8, IST_PULSE, IPL_CLOCK, rtcintr,
	    0, "rtc");

	mc146818_write(NULL, MC_REGA, MC_BASE_32_kHz | MC_RATE_128_Hz);
	mc146818_write(NULL, MC_REGB, MC_REGB_24HR | MC_REGB_PIE);

	/*
	 * On a number of i386 systems, the rtc will fail to start when booting
	 * the system. This is due to us missing to acknowledge an interrupt
	 * during early stages of the boot process. If we do not acknowledge
	 * the interrupt, the rtc clock will not generate further interrupts.
	 * To solve this, once interrupts are enabled, use a timeout (once)
	 * to drain any un-acknowledged rtc interrupt(s).
	 */

	timeout_set(&rtcdrain_timeout, rtcdrain, (void *)&rtcdrain_timeout);
	timeout_add(&rtcdrain_timeout, 1);
}

int
rtcget(mc_todregs *regs)
{
	if ((mc146818_read(NULL, MC_REGD) & MC_REGD_VRT) == 0) /* XXX softc */
		return (-1);
	MC146818_GETTOD(NULL, regs);			/* XXX softc */
	return (0);
}

void
rtcput(mc_todregs *regs)
{
	MC146818_PUTTOD(NULL, regs);			/* XXX softc */
}

int
hexdectodec(int n)
{

	return (((n >> 4) & 0x0f) * 10 + (n & 0x0f));
}

int
dectohexdec(int n)
{

	return ((u_char)(((n / 10) << 4) & 0xf0) | ((n % 10) & 0x0f));
}

static int timeset;

/*
 * check whether the CMOS layout is "standard"-like (ie, not PS/2-like),
 * to be called at splclock()
 */
int cmoscheck(void);

int
cmoscheck(void)
{
	int i;
	unsigned short cksum = 0;

	for (i = 0x10; i <= 0x2d; i++)
		cksum += mc146818_read(NULL, i); /* XXX softc */

	return (cksum == (mc146818_read(NULL, 0x2e) << 8)
			  + mc146818_read(NULL, 0x2f));
}

/*
 * patchable to control century byte handling:
 * 1: always update
 * -1: never touch
 * 0: try to figure out itself
 */
int rtc_update_century = 0;

/*
 * Expand a two-digit year as read from the clock chip
 * into full width.
 * Being here, deal with the CMOS century byte.
 */
int clock_expandyear(int);

int
clock_expandyear(int clockyear)
{
	int s, clockcentury, cmoscentury;

	clockcentury = (clockyear < 70) ? 20 : 19;
	clockyear += 100 * clockcentury;

	if (rtc_update_century < 0)
		return (clockyear);

	s = splclock();
	if (cmoscheck())
		cmoscentury = mc146818_read(NULL, NVRAM_CENTURY);
	else
		cmoscentury = 0;
	splx(s);
	if (!cmoscentury) {
#ifdef DIAGNOSTIC
		printf("clock: unknown CMOS layout\n");
#endif
		return (clockyear);
	}
	cmoscentury = hexdectodec(cmoscentury);

	if (cmoscentury != clockcentury) {
		/* XXX note: saying "century is 20" might confuse the naive. */
		printf("WARNING: NVRAM century is %d but RTC year is %d\n",
		       cmoscentury, clockyear);

		/* Kludge to roll over century. */
		if ((rtc_update_century > 0) ||
		    ((cmoscentury == 19) && (clockcentury == 20) &&
		     (clockyear == 2000))) {
			printf("WARNING: Setting NVRAM century to %d\n",
			       clockcentury);
			s = splclock();
			mc146818_write(NULL, NVRAM_CENTURY,
				       dectohexdec(clockcentury));
			splx(s);
		}
	} else if (cmoscentury == 19 && rtc_update_century == 0)
		rtc_update_century = 1; /* will update later in resettodr() */

	return (clockyear);
}

/*
 * Initialize the time of day register, based on the time base which is, e.g.
 * from a filesystem.
 */
void
inittodr(time_t base)
{
	struct {
		mc_todregs rtclk;
		time_t basetime, rtctime;
	} x;
	struct tm tm;
	int s;

	/*
	 * We mostly ignore the suggested time and go for the RTC clock time
	 * stored in the CMOS RAM.  If the time can't be obtained from the
	 * CMOS, or if the time obtained from the CMOS is 5 or more years
	 * less than the suggested time, we used the suggested time.  (In
	 * the latter case, it's likely that the CMOS battery has died.)
	 */

	if (base < 15*SECYR) {	/* if before 1985, something's odd... */
		printf("WARNING: preposterous time in file system\n");
		/* read the system clock anyway */
		base = 17*SECYR + 186*SECDAY + SECDAY/2;
	}

	time.tv_usec = 0;

	s = splclock();
	if (rtcget(&x.rtclk)) {
		splx(s);
		printf("WARNING: invalid time in clock chip\n");
		goto fstime;
	}
	splx(s);

	tm.tm_sec = hexdectodec(x.rtclk[MC_SEC]);
	tm.tm_min = hexdectodec(x.rtclk[MC_MIN]);
	tm.tm_hour = hexdectodec(x.rtclk[MC_HOUR]);
	tm.tm_mday = hexdectodec(x.rtclk[MC_DOM]);
	tm.tm_mon = hexdectodec(x.rtclk[MC_MONTH]) - 1;
	tm.tm_year = clock_expandyear(hexdectodec(x.rtclk[MC_YEAR])) - 1900;
	tm.tm_gmtoff = 0;

	/*
	 * If time_t is 32 bits, then the "End of Time" is
	 * Mon Jan 18 22:14:07 2038 (US/Eastern)
	 * This code copes with RTC's past the end of time if time_t
	 * is an int32 or less. Needed because sometimes RTCs screw
	 * up or are badly set, and that would cause the time to go
	 * negative in the calculation below, which causes Very Bad
	 * Mojo. This at least lets the user boot and fix the problem.
	 * Note the code is self eliminating once time_t goes to 64 bits.
	 */
	if (sizeof(time_t) <= sizeof(int32_t)) {
		if (tm.tm_year >= 2038 - 1900) {
			printf("WARNING: RTC time at or beyond 2038.\n");
			tm.tm_year = 2037 - 1900;
			printf("WARNING: year set back to 2037.\n");
			printf("WARNING: CHECK AND RESET THE DATE!\n");
		}
	}

	time.tv_sec = tz.tz_minuteswest * 60;
	if (tz.tz_dsttime)
		time.tv_sec -= 3600;
	time.tv_sec += tai2timet(mjd2tai(tm2mjd(tm)));
	x.rtctime = time.tv_sec;

	if (base < time.tv_sec - 5*SECYR)
		printf("WARNING: file system time much less than clock time\n");
	else if (base > time.tv_sec + 5*SECYR) {
		printf("WARNING: clock time much less than file system time\n");
		printf("WARNING: using file system time\n");
		goto fstime;
	}
	goto oktime;

 fstime:
	time.tv_sec = base;
	printf("WARNING: CHECK AND RESET THE DATE!\n");

 oktime:
	x.basetime = base;
	rnd_lopool_add(&x, sizeof(x));
	timeset = 1;
	return;
}

/*
 * Reset the clock.
 */
void
resettodr(void)
{
	mc_todregs rtclk;
	struct tm tm;
	int diff;
	int century;
	int s;

	/*
	 * We might have been called by boot() due to a crash early
	 * on.  Don't reset the clock chip in this case.
	 */
	if (!timeset)
		return;

	s = splclock();
	if (rtcget(&rtclk))
		bzero(&rtclk, sizeof(rtclk));
	splx(s);

	diff = tz.tz_minuteswest * 60;
	if (tz.tz_dsttime)
		diff -= 3600;
	tm = mjd2tm(tai2mjd(timet2tai(time.tv_sec - diff)));

	rtclk[MC_SEC] = dectohexdec(tm.tm_sec);
	rtclk[MC_MIN] = dectohexdec(tm.tm_min);
	rtclk[MC_HOUR] = dectohexdec(tm.tm_hour);
	rtclk[MC_DOW] = tm.tm_wday;
	rtclk[MC_YEAR] = dectohexdec(tm.tm_year % 100);
	rtclk[MC_MONTH] = dectohexdec(tm.tm_mon + 1);
	rtclk[MC_DOM] = dectohexdec(tm.tm_mday);
	s = splclock();
	rtcput(&rtclk);
	if (rtc_update_century > 0) {
		century = dectohexdec(tm.tm_year / 100 + 19);
		mc146818_write(NULL, NVRAM_CENTURY, century); /* XXX softc */
	}
	splx(s);
}

void
setstatclockrate(int arg)
{
	if (arg == stathz)
		mc146818_write(NULL, MC_REGA, MC_BASE_32_kHz | MC_RATE_128_Hz);
	else
		mc146818_write(NULL, MC_REGA, MC_BASE_32_kHz | MC_RATE_1024_Hz);
}
