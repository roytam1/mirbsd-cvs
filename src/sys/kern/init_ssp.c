/* $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $ */

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
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
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
