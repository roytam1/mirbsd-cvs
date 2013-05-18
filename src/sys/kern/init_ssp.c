/* $MirOS: src/sys/kern/init_ssp.c,v 1.1.7.1 2005/03/06 16:33:47 tg Exp $ */

/*-
 * Copyright (c) 2004
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 * Copyright (c) by The OpenBSD Project.
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
 * the possibility of such damage or existence of a nontrivial bug.
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
	 * this is so arc4random_bytes does not
	 * cause a kernel panic for smashing...
	 */
	arc4random_bytes(tmp, sizeof(tmp));
	while (i--)
		__guard[i] = tmp[i];
#endif
}

#ifndef	NO_PROPOLICE
__dead void
__stack_smash_handler(char func[], int damaged __attribute__((unused)))
{
	panic("ProPolice: kernel stack smashed in %s", func);
}
#endif
