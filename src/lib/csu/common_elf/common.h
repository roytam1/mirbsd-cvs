/* $MirOS: src/lib/csu/common_elf/common.h,v 1.2 2005/03/06 20:28:21 tg Exp $
 * derived from the following files:
 * $NetBSD: common.h,v 1.10 2004/08/26 20:57:47 thorpej Exp $
 */

/*
 * Copyright (c) 2003, 2004, 2005
 *	Thorsten "mirabile" Glaser <tg@MirBSD.org>
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

#ifndef	_COMMON_H
#define	_COMMON_H

#include <sys/param.h>
#include <sys/exec.h>
#include <sys/syscall.h>
#include <stdlib.h>

typedef void Obj_Entry;

char *__progname;
char **environ;
struct ps_strings *__ps_strings = NULL;

char __progname_storage[NAME_MAX + 1];

extern void _init(void);
extern void _fini(void);
static char *_strrchr(char *, int);

#ifdef	MCRT0
extern void monstartup(u_long, u_long);
extern void _mcleanup(void);
extern unsigned char _etext, _eprol;
#endif

__dead void ___start(int argc, char **argv, char **envp,
    void (*cleanup) (void), const Obj_Entry *obj,
    struct ps_strings *ps_strings);
int main(int argc, char **argv, char **envp);

#endif
