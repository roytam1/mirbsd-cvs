/* $MirOS: src/sys/kern/init_ssp.c,v 1.5 2010/09/19 18:55:39 tg Exp $ */

/*-
 * Copyright (c) 2004, 2013
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
 * Copyright (c) by The OpenBSD Project.
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

#ifdef __SSP_ALL__
#error "You must compile this file with -fno-stack-protector-all"
#endif

#include <sys/param.h>
#include <sys/systm.h>
#include <dev/rndvar.h>

void init_ssp(void);
#ifndef	NO_PROPOLICE
void __stack_smash_handler(char [], int);
#endif

#define GUARDLEN 8

#ifndef	NO_PROPOLICE
long __guard[GUARDLEN];
#endif

void
init_ssp(void)
{
#ifndef	NO_PROPOLICE
	long tmp[GUARDLEN];
	int i = GUARDLEN;

	/*
	 * this is so arc4random_buf does not
	 * cause a kernel panic for smashing...
	 */
	arc4random_buf(tmp, sizeof(tmp));
	while (i--)
		__guard[i] = tmp[i];
#endif
}

#ifndef	NO_PROPOLICE
__dead void
__stack_smash_handler(char func[], int damaged __attribute__((__unused__)))
{
	panic("ProPolice: kernel stack smashed in %s", func);
}
#endif
