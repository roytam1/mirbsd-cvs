/* $MirOS: src/lib/csu/common_elf/common.c,v 1.7 2009/08/30 18:02:08 tg Exp $
 * derived from the following files:
 * $NetBSD: common.c,v 1.16 2004/08/26 21:01:12 thorpej Exp $
 * $OpenBSD: crt0.c,v 1.11 2003/06/27 22:30:38 deraadt Exp $
 */

/*
 * Copyright (c) 2003, 2004, 2005, 2009, 2013
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
 * Copyright (c) 1995 Christopher G. Demetriou
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
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *          This product includes software developed for the
 *          NetBSD Project.  See http://www.NetBSD.org/ for
 *          information about NetBSD.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * <<Id: LICENSE,v 1.2 2000/06/14 15:57:33 cgd Exp>>
 */

#ifndef _COMMON_H
#error	not a stand-alone file
#endif

__RCSID("$MirOS: src/lib/csu/common_elf/common.c,v 1.7 2009/08/30 18:02:08 tg Exp $");

struct ps_strings *__ps_strings = NULL;
char __progname_storage[NAME_MAX + 1];

static char *
_strrchr(char *p, int ch)
{
	char *save;

	for (save = NULL;; ++p) {
		if (*p == ch)
			save = (char *)p;
		if (!*p)
			return (save);
	}
/* NOTREACHED */
}

#ifdef MCRT0
__asm__(".text"
    "\n_eprol:");
#endif

void ___start(int argc, char **argv, char **envp,
    void (*cleanup) (void) __attribute__((__unused__)),
    const Obj_Entry *obj __attribute__((__unused__)),
    struct ps_strings *ps_strings)
{
	char *namep, *s;

	environ = envp;

	if ((namep = argv[0]) != NULL) {	/* NULL ptr if argc == 0 */
		if ((__progname = _strrchr(namep, '/')) == NULL)
			__progname = namep;
		else
			++__progname;
		for (s = __progname_storage; (*__progname) &&
		    (s < &__progname_storage[NAME_MAX]); /* nothing */ )
			*s++ = *__progname++;
		*s = '\0';
		__progname = __progname_storage;
	}
	if (ps_strings != (struct ps_strings *)0)
		__ps_strings = ps_strings;

#ifdef MCRT0
	atexit(_mcleanup);
	monstartup((u_long)&_eprol, (u_long)&_etext);
#endif

	atexit(_fini);
	_init();

	exit(main(argc, argv, environ));
}
