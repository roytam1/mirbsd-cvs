#if 0

all: testaslr

testaslr: testaslr.c

clean:
	rm -f testaslr.o testaslr
.if "0" == "1"
#endif

/*-
 * Copyright (c) 2010
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
 * compile without optimisation; pipe output through “column -t”; try
 * to compile statically too; run several times in sequence
 */

#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>

static const char __rcsid[] =
    "$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $";

#ifndef MAP_ANON
#define MAP_ANON	0
#endif

extern void *ptrstackarg(int);
extern void *ptrstackvar(void);

int
main(void)
{
	void *m12, *m257, *m8M, *sarg, *sloc, *mmapped;

	m12 = malloc(12);
	m257 = malloc(257);
	m8M = malloc(8 * 1048576);
	sarg = ptrstackarg(1);
	sloc = ptrstackvar();
	mmapped = mmap(NULL, 16 * 1048576, PROT_READ | PROT_WRITE,
	    MAP_ANON | MAP_PRIVATE, -1, 0);

	printf("12_bytes 257_bytes 8mebibytes stackarg stackvar anonmmap"
	    " ptr_main ptr_exit\n%p %p %p %p %p %p %p %p\n",
	    m12, m257, m8M, sarg, sloc, mmapped, &main, &exit);
	return (0);
}

void *
ptrstackarg(int i)
{
	return (&i);
}

void *
ptrstackvar(void)
{
	int i;

	return (&i);
}

#if 0
.endif
#endif
