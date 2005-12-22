/**	$MirOS$ */
/*	$NetBSD: kern_timeout.c,v 1.13 2003/10/30 04:32:56 thorpej Exp $	*/
/*	$OpenBSD: kern_timeout.c,v 1.18 2003/06/03 12:05:25 art Exp $	*/

/*-
 * Copyright (c) 2003 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jason R. Thorpe.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the NetBSD
 *	Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 2003, 2005 Thorsten Glaser <tg@66h.42h.de>
 * Copyright (c) 2001 Thomas Nordin <nordin@openbsd.org>
 * Copyright (c) 2000-2001 Artur Grabowski <art@openbsd.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL  DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/lock.h>
#include <sys/timeout.h>

#ifdef DDB
#include <machine/db_machdep.h>
#include <ddb/db_interface.h>
#include <ddb/db_access.h>
#include <ddb/db_sym.h>
#include <ddb/db_output.h>
#endif

/*
 * Timeouts are kept in a hierarchical timing wheel. The to_time is the value
 * of the global variable "ticks" when the timeout should be called.
 * There are four levels with 256 buckets each. See 'Scheme 7' in
 * "Hashed and Hierarchical Timing Wheels: Efficient Data Structures for
 * Implementing a Timer Facility" by George Varghese and Tony Lauck.
 */
#define BUCKETS 1024
#define WHEELSIZE 256
#define WHEELMASK 255
#define WHEELBITS 8

static struct timeout_circq timeout_wheel[BUCKETS];	/* Queues of timeouts */
static struct timeout_circq timeout_todo;		/* Worklist */

#define MASKWHEEL(wheel, time) (((time) >> ((wheel)*WHEELBITS)) & WHEELMASK)

#define BUCKET(rel, abs)						\
    (((rel) <= (1 << (2*WHEELBITS)))					\
    	? ((rel) <= (1 << WHEELBITS))					\
            ? &timeout_wheel[MASKWHEEL(0, (abs))]			\
            : &timeout_wheel[MASKWHEEL(1, (abs)) + WHEELSIZE]		\
        : ((rel) <= (1 << (3*WHEELBITS)))				\
            ? &timeout_wheel[MASKWHEEL(2, (abs)) + 2*WHEELSIZE]		\
            : &timeout_wheel[MASKWHEEL(3, (abs)) + 3*WHEELSIZE])

#define MOVEBUCKET(wheel, time)						\
    CIRCQ_APPEND(&timeout_todo,						\
        &timeout_wheel[MASKWHEEL((wheel), (time)) + (wheel)*WHEELSIZE])

/*
 * All wheels are locked with the same lock (which must also block out all
 * interrupts).
 */
static struct simplelock callout_slock;

#define	CALLOUT_LOCK(s)							\
do {									\
	s = splhigh();							\
	simple_lock(&callout_slock);					\
} while (/*CONSTCOND*/0)

#define	CALLOUT_UNLOCK(s)						\
do {									\
	simple_unlock(&callout_slock);					\
	splx((s));							\
} while (/*CONSTCOND*/0)

/*
 * Circular queue definitions.
 */

#define CIRCQ_INIT(list)						\
do {									\
        (list)->next_l = (list);			\
        (list)->prev_l = (list);			\
} while (/*CONSTCOND*/0)

#define CIRCQ_INSERT(elem, list)					\
do {									\
        (elem)->prev_e = (list)->prev_e;		\
        (elem)->next_l = (list);			\
        (list)->prev_l->next_l = (elem);		\
        (list)->prev_l = (elem);			\
} while (/*CONSTCOND*/0)

#define CIRCQ_APPEND(fst, snd)						\
do {									\
        if (!CIRCQ_EMPTY(snd)) {			\
                (fst)->prev_l->next_l = (snd)->next_l;	\
                (snd)->next_l->prev_l = (fst)->prev_l;	\
                (snd)->prev_l->next_l = (fst);		\
                (fst)->prev_l = (snd)->prev_l;		\
                CIRCQ_INIT(snd);			\
        }						\
} while (/*CONSTCOND*/0)

#define CIRCQ_REMOVE(elem)						\
do {									\
        (elem)->next_l->prev_e = (elem)->prev_e;	\
        (elem)->prev_l->next_e = (elem)->next_e;	\
} while (/*CONSTCOND*/0)

#define	CIRCQ_FIRST(list)	((list)->next_e)
#define	CIRCQ_NEXT(elem)	((elem)->next_e)
#define	CIRCQ_LAST(elem,list)	((elem)->next_l == (list))
#define	CIRCQ_EMPTY(list)	((list)->next_l == (list))

/*
 * Some of the "math" in here is a bit tricky.
 *
 * We have to beware of wrapping ints.
 * We use the fact that any element added to the queue must be added with a
 * positive time. That means that any element `to' on the queue cannot be
 * scheduled to timeout further in time than INT_MAX, but c->to_time can
 * be positive or negative so comparing it with anything is dangerous.
 * The only way we can use the c->to_time value in any predictable way
 * is when we calculate how far in the future `to' will timeout -
 * "c->to_time - ticks". The result will always be positive for
 * future timeouts and 0 or negative for due timeouts.
 */
extern int ticks;		/* XXX - move to sys/X.h */

void
timeout_startup(void)
{
	int b;

	CIRCQ_INIT(&timeout_todo);
	for (b = 0; b < BUCKETS; b++)
		CIRCQ_INIT(&timeout_wheel[b]);
	simple_lock_init(&callout_slock);
}

void
timeout_set(struct timeout *new, void (*fn)(void *), void *arg)
{
	new->to_time = 0;
	new->to_func = fn;
	new->to_arg = arg;
	new->to_flags = TIMEOUT_INITIALIZED;
}

void
timeout_add(struct timeout *c, int to_ticks)
{
	int s, old_time;

#ifdef DIAGNOSTIC
	if (!(c->to_flags & TIMEOUT_INITIALIZED))
		panic("timeout_add: not initialized");
	if (to_ticks < 0)
		panic("timeout_add: to_ticks < 0");
#endif

	CALLOUT_LOCK(s);

	/* Initialize the time here, it won't change. */
	old_time = c->to_time;
	c->to_time = to_ticks + ticks;
	c->to_flags &= ~TIMEOUT_TRIGGERED;

	/*
	 * If this timeout is already scheduled and now is moved
	 * earlier, reschedule it now. Otherwise leave it in place
	 * and let it be rescheduled later.
	 */
	if (c->to_flags & TIMEOUT_ONQUEUE) {
		if (c->to_time - old_time < 0) {
			CIRCQ_REMOVE(&c->to_list);
			CIRCQ_INSERT(&c->to_list, &timeout_todo);
		}
	} else {
		c->to_flags |= TIMEOUT_ONQUEUE;
		CIRCQ_INSERT(&c->to_list, &timeout_todo);
	}

	CALLOUT_UNLOCK(s);
}

void
timeout_del(struct timeout *c)
{
	int s;

	CALLOUT_LOCK(s);

	if (c->to_flags & TIMEOUT_ONQUEUE) {
		CIRCQ_REMOVE(&c->to_list);
		c->to_flags &= ~TIMEOUT_ONQUEUE;
	}

	c->to_flags &= ~TIMEOUT_TRIGGERED;

	CALLOUT_UNLOCK(s);
}

/*
 * This is called from hardclock() once every tick.
 * We return !0 if we need to schedule a softclock.
 *
 * We don't need locking in here.
 */
int
timeout_hardclock_update(void)
{
	MOVEBUCKET(0, ticks);
	if (MASKWHEEL(0, ticks) == 0) {
		MOVEBUCKET(1, ticks);
		if (MASKWHEEL(1, ticks) == 0) {
			MOVEBUCKET(2, ticks);
			if (MASKWHEEL(2, ticks) == 0)
				MOVEBUCKET(3, ticks);
		}
	}

	return !CIRCQ_EMPTY(&timeout_todo);
}

/* ARGSUSED */
void
softclock(void)
{
	struct timeout *c;
	void (*func)(void *);
	void *arg;
	int s;

	CALLOUT_LOCK(s);

	while (!CIRCQ_EMPTY(&timeout_todo)) {
		c = CIRCQ_FIRST(&timeout_todo);
		CIRCQ_REMOVE(&c->to_list);

		/* If due run it, otherwise insert it into the right bucket. */
		if (c->to_time - ticks > 0) {
			CIRCQ_INSERT(&c->to_list,
			    BUCKET((c->to_time - ticks), c->to_time));
		} else {
#ifdef DEBUG
			if (c->to_time - ticks < 0)
				printf("timeout delayed %d\n", c->to_time -
				    ticks);
#endif
			c->to_flags &= ~TIMEOUT_ONQUEUE;
			c->to_flags |= TIMEOUT_TRIGGERED;

			func = c->to_func;
			arg = c->to_arg;

			CALLOUT_UNLOCK(s);
			(*func)(arg);
			CALLOUT_LOCK(s);
		}
	}

	CALLOUT_UNLOCK(s);
}

#ifdef DDB
static void db_show_callout_bucket(struct timeout_circq *);

static void
db_show_callout_bucket(struct timeout_circq *bucket)
{
	struct timeout *c;
	db_expr_t offset;
	char *name;

	if (CIRCQ_EMPTY(bucket))
		return;

	for (c = CIRCQ_FIRST(bucket); /*nothing*/; c = CIRCQ_NEXT(&c->to_list)) {
		db_find_sym_and_offset((db_addr_t)(intptr_t)c->to_func, &name,
		    &offset);
		name = name ? name : "?";
#ifdef _LP64
#define	POINTER_WIDTH	"%16lX"
#else
#define	POINTER_WIDTH	"%8lX"
#endif
		db_printf("%9d %2d/%-4d " POINTER_WIDTH "  %s\n",
		    c->to_time - ticks,
		    (int)((bucket - timeout_wheel) / WHEELSIZE),
		    (int)(bucket - timeout_wheel), (u_long) c->to_arg, name);

		if (CIRCQ_LAST(&c->to_list, bucket))
			break;
	}
}

void
db_show_callout(db_expr_t addr, int haddr, db_expr_t count, char *modif)
{
	int b;

	db_printf("ticks now: %d\n", ticks);
#ifdef _LP64
	db_printf("    ticks  wheel       arg  func\n");
#else
	db_printf("    ticks  wheel       arg  func\n");
#endif

	/*
	 * Don't lock the callwheel; all the other CPUs are paused
	 * anyhow, and we might be called in a circumstance where
	 * some other CPU was paused while holding the lock.
	 */

	db_show_callout_bucket(&timeout_todo);
	for (b = 0; b < BUCKETS; b++)
		db_show_callout_bucket(&timeout_wheel[b]);
}
#endif /* DDB */
