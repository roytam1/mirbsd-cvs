/**	$MirOS: src/sys/arch/i386/stand/libsa/debug.c,v 1.5 2009/01/11 19:05:59 tg Exp $ */
/*	$OpenBSD: debug.c,v 1.13 2004/03/09 19:12:12 tom Exp $	*/

/*
 * Copyright (c) 1997 Michael Shalayeff
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include <lib/libsa/stand.h>
#include <debug.h>
#include <dev/cons.h>

#define	VBASE	(0xb8000)

#ifndef SMALL_BOOT
char *const reg_names[] = { REG_NAMES };
const int nreg = NENTS(reg_names);
#endif
struct reg reg;
#ifndef SMALL_BOOT
u_int32_t *const reg_values[] = { REG_VALUES(reg) };
char *const trap_names[] = { TRAP_NAMES };
#endif

void d_putc(dev_t, int);

#ifdef DEBUG_DEBUG
#define	CKPT(c)	(*(u_short volatile *)(VBASE+160) = (0x1700 | (c)))
#else
#define	CKPT(c)	/* c */
#endif

void
dump_regs(u_int trapno, u_int arg)
{
#ifdef TRAP_ME_NOT
	static const char traptext[8] = {
		'T', 0x10, 'R', 0x10, 'A', 0x10, 'P', 0x10
	};

	memcpy((char *)VBASE + (76 * 2), traptext, sizeof (traptext));
#else
#ifndef SMALL_BOOT
	register int i;
#endif
	/* make it local, so it won't rely on .data/.bss corruption */
	struct consdev d_cons, *save_cons;

	/* init cons mod */
	save_cons = cn_tab;
	bzero(&d_cons, sizeof(d_cons));
	d_cons.cn_putc = &d_putc;
	cn_tab = &d_cons;

#ifdef SMALL_BOOT
	printf("\ftrap: %u(%x)\n",trapno, arg);
#else
	/* Trap info */
	printf("\ftrap: %u(%x): %s\ncn_tab=%p\n",
	    trapno, arg, trap_names[trapno], save_cons);

	/* Register dump */
	for (i = 1; i <= nreg; i++)
		printf("%s\t%x%c", reg_names[i-1], *reg_values[i-1],
		    ((i%4)? ' ': '\n'));

	dump_mem("Code dump", (void *)*reg_values[8], 8);
	/* %ebx (void *)((*reg_values[3] + 15) & ~0x0F) */
	dump_mem("Memory dump", (void *)0x1a000, 4 /* 48 */);
	dump_mem("Stack trace", (void *)(*reg_values[4]), 48);
#endif

	/* restore the console */
	cn_tab = save_cons;
#endif
}

#if !defined(SMALL_BOOT) && !defined(TRAP_ME_NOT)
void
dump_mem(char *l, void *p, size_t n)
{
	register int i;

	printf("%s [%p]:%s", l, p, (n > 6? "\n":" "));
	for (i = 1; i <= n; i++)
		printf("%x%c", *(u_int32_t *)p++, ((i%8)? ' ': '\n'));
	if (n % 8)
		printf("\n");
}
#endif

#ifndef TRAP_ME_NOT
u_int d_pos;

void
d_putc(dev_t d, int c)
{
	switch (c) {
	case '\n':	d_pos += 80;					break;
	case '\r':	d_pos -= d_pos % 80;				break;
	case '\b':	d_pos--;					break;
	case '\f':	bzero((void *)VBASE, 80*25*2); d_pos = 0;	break;
		/* print it */
	default:
		((u_int16_t volatile *)VBASE)[d_pos++] = 0x0700 | (u_char)c;
		break;
	}
}
#endif
