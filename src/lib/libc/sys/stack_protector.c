/*	$OpenBSD: stack_protector.c,v 1.10 2006/03/31 05:34:44 deraadt Exp $	*/

/*
 * Copyright © 2009, 2011, 2013
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
 * Copyright (c) 2002 Hiroaki Etoh, Federico G. Schwindt, and Miodrag Vallat.
 * All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <sys/param.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

__RCSID("$MirOS: src/lib/libc/sys/stack_protector.c,v 1.11 2011/04/27 21:54:07 tg Exp $");

#if (defined(__SSP__) || defined(__SSP_ALL__)) && \
    !defined(__IN_MKDEP) && !defined(lint)
#error "You must compile this file with -fno-stack-protector"
#endif

#ifdef lint
#define	CONSTRUCTOR
#elif defined(__PCC__)
#define	CONSTRUCTOR	_Pragma("init")
#else
#define	CONSTRUCTOR	static __attribute__((__constructor__))
#endif

extern void _thread_sys__exit__(int) __dead;
extern void arc4random_atexit(void);

long __guard[8] = {0, 0, 0, 0, 0, 0, 0, 0};	/* gcc (3.4 ProPolice) */
int __stack_chk_guard;				/* gcc4 libssp and pcc */
CONSTRUCTOR void __guard_setup(void);
__dead void __stack_smash_handler(const char func[], int damaged);
__dead void __stack_chk_fail(void);

static const char message[] = "stack overflow in function %s (damaged: %d)";

CONSTRUCTOR void
__guard_setup(void)
{
	uint8_t newguard[MAX(sizeof(__guard), sizeof(__stack_chk_guard))];

	if (__guard[0] != 0)
		return;

	while (__guard[0] == 0) {
		arc4random_buf(newguard, sizeof(newguard));
		newguard[17] = 0;
		newguard[18] = '\n';
		newguard[19] = 255;
		memcpy(__guard, newguard, sizeof(__guard));
	}
	while (__stack_chk_guard == 0) {
		arc4random_buf(newguard, sizeof(__stack_chk_guard));
		memcpy(&__stack_chk_guard, newguard, sizeof(__stack_chk_guard));
	}
}

/* ARGSUSED1 */
void
__stack_smash_handler(const char func[], int damaged)
{
	struct syslog_data sdata = SYSLOG_DATA_INIT;
	struct sigaction sa;
	sigset_t mask;

	/* Immediately block all signal handlers from running code */
	sigfillset(&mask);
	sigdelset(&mask, SIGABRT);
	sigprocmask(SIG_BLOCK, &mask, NULL);

	/* This may fail on a chroot jail... */
	syslog_r(LOG_CRIT, &sdata, message, func, damaged);

	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGABRT, &sa, NULL);

	arc4random_atexit();

	kill(getpid(), SIGABRT);

	_thread_sys__exit__(127);
}

void
__stack_chk_fail(void)
{
	__stack_smash_handler("unknown (libssp or pcc)", 0);
}
