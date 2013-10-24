/* $MirOS: src/lib/csu/i386_elf/md_init.h,v 1.1 2007/04/18 11:31:28 tg Exp $ */
/* $NetBSD: dot_init.h,v 1.3 2002/11/22 06:45:00 thorpej Exp $ */

/*-
 * Copyright (c) 2004, 2005
 *	Thorsten "mirabilos" Glaser <tg@MirBSD.de>
 * Copyright (c) 2001 Ross Harvey
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

#include <sys/cdefs.h>

/*
 * These must be extern to avoid warnings ("declared static but never defined")
 * However, only the declaration is extern, the actually __asm() defines them
 * as static.
 */
#define	INIT_FALLTHRU_DECL void init_fallthru(void)
#define	FINI_FALLTHRU_DECL void fini_fallthru(void)

#define	INIT_FALLTHRU()	init_fallthru()
#define	FINI_FALLTHRU()	fini_fallthru()

/* placement of the nop & .balign _after_ the label is intentional */
#define	MD_SECTION_PROLOGUE(sect, entry_pt)			\
	__asm__(".section " __STRING(sect) ",\"ax\",@progbits"	\
	"\n" __STRING(entry_pt) ":"				\
	"\n	nop"						\
	"\n	.balign 4"					\
	"\n	/* fall thru */"				\
	"\n	.previous")

#define	MD_SECTION_EPILOGUE(sect)				\
	__asm__(".section " __STRING(sect) ",\"ax\",@progbits"	\
	"\n	ret"						\
	"\n	.previous")

#define	MD_INIT_SECTION_PROLOGUE MD_SECTION_PROLOGUE(.init, init_fallthru)
#define	MD_FINI_SECTION_PROLOGUE MD_SECTION_PROLOGUE(.fini, fini_fallthru)

#define	MD_INIT_SECTION_EPILOGUE MD_SECTION_EPILOGUE(.init)
#define	MD_FINI_SECTION_EPILOGUE MD_SECTION_EPILOGUE(.fini)

#define MD_CALL_STATIC_FUNCTION(section, func)	\
	__asm__(".section " __STRING(section)	\
	"\n	call " __STRING(func)		\
	"\n	.previous");

__RCSID("$MirOS: src/lib/csu/i386_elf/md_init.h,v 1.1 2007/04/18 11:31:28 tg Exp $");