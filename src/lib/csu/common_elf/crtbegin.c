/* $MirOS: src/lib/csu/common_elf/crtbegin.c,v 1.3 2008/11/08 23:03:50 tg Exp $
 * derived from the following files:
 * $NetBSD: crtbegin.c,v 1.26 2004/08/28 00:19:22 thorpej Exp $
 * $OpenBSD: crtbegin.c,v 1.10 2004/10/10 18:29:15 kettenis Exp $
 */

/*-
 * Copyright (c) 2003, 2004, 2004
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
 * Copyright (c) 1998, 2001, 2002 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Paul Kranenburg, Ross Harvey, and Jason R. Thorpe.
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
 *        This product includes software developed by the NetBSD
 *        Foundation, Inc. and its contributors.
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

#include <sys/param.h>
#include <sys/exec.h>
#include <sys/exec_elf.h>
#include <stdlib.h>

#include "dot_init.h"

__RCSID("$MirOS: src/lib/csu/common_elf/crtbegin.c,v 1.3 2008/11/08 23:03:50 tg Exp $");

/*
 * Run-time module which handles constructors and destructors.
 *
 * The linker constructs the following arrays of pointers to global
 * constructors and destructors. The first element contains the
 * number of pointers in each or -1 to indicate that the run-time
 * code should figure out how many there are.  The tables are also
 * null-terminated.
 */

/*
 * WE SHOULD BE USING GCC-SUPPLIED crtbegin.o FOR GCC 3.3 AND
 * LATER!!!
 */
#if !defined(HAVE_VERSION_SPECIFIC_GCC_LIBS) && __GNUC_PREREQ__(3, 3)
#error "Use GCC-supplied crtbegin.o"
#endif

#if __GNUC_PREREQ__(3, 0)
#define	USED_NOINLINE __attribute__((__used__,__noinline__))
#else
#define	USED_NOINLINE __attribute__((__unused__))
#endif


static void (*__CTOR_LIST__[1])(void)
    __attribute__((section(".ctors"))) = { (void *)-1 };	/* XXX */
static void (*__DTOR_LIST__[1])(void)
    __attribute__((section(".dtors"))) = { (void *)-1 };	/* XXX */

#ifdef	DWARF2_EH
struct dwarf2_eh_object {
	void *space[8];
};

extern void __register_frame_info(const void *,
    struct dwarf2_eh_object *) __attribute__((weak));
extern void __deregister_frame_info(const void *) __attribute__((weak));

static const char __EH_FRAME_BEGIN__[]
    __attribute__((section(".eh_frame"), aligned(4))) = { };
#endif

#if defined(JCR) && defined(__GNUC__)
extern void _Jv_RegisterClasses(void *) __attribute__((weak));

static void *__JCR_LIST__[]
    __attribute__((section(".jcr"))) = { };
#endif

#if defined(DSO_HANDLE) && defined(__GNUC__)
/*
 * The __dso_handle variable is used to hang C++ local destructors off
 * of.  In the main program (i.e. using crtbegin.o), the value is 0.
 * In shared objects (i.e. using crtbeginS.o), the value must be unique.
 * The symbol is hidden, but the dynamic linker will still relocate it.
 */
#ifdef SHARED
void	*__dso_handle = &__dso_handle;
#else
void	*__dso_handle = NULL;
#endif
__asm(".hidden	__dso_handle");

#ifdef SHARED
extern void __cxa_finalize(void *) __attribute__((weak));
#endif
#endif

#ifndef MD_CALL_STATIC_FUNCTION
#if defined(__GNUC__)
#define	MD_CALL_STATIC_FUNCTION(section, func)				\
static void __attribute__((__unused__))					\
__call_##func(void)							\
{									\
	__asm __volatile (".section " #section);			\
	func();								\
	__asm __volatile (".previous");					\
}
#else
#error Need MD_CALL_STATIC_FUNCTION
#endif
#endif /* ! MD_CALL_STATIC_FUNCTION */

static void
__ctors(void)
{
	unsigned long i = (unsigned long) __CTOR_LIST__[0];
	void (**p)(void);

	if (i == (unsigned long) -1)  {
		for (i = 1; __CTOR_LIST__[i] != NULL; i++)
			;
		i--;
	}
	p = __CTOR_LIST__ + i;
	while (i--)
		(**p--)();
}

static void
__dtors(void)
{
	void (**p)(void) = __DTOR_LIST__ + 1;

	while (*p)
		(**p++)();
}

static void USED_NOINLINE
__do_global_ctors_aux(void)
{
	static int initialized;
#ifdef DWARF2_EH
#if defined(__GNUC__)
	static struct dwarf2_eh_object object;
#endif /* __GNUC__ */
#endif /* DWARF2_EH */

	if (!initialized) {
		initialized = 1;

#ifdef DWARF2_EH
#if defined(__GNUC__)
		if (__register_frame_info != NULL)
			__register_frame_info(__EH_FRAME_BEGIN__, &object);
#endif /* __GNUC__ */
#endif /* DWARF2_EH */

#if defined(JCR) && defined(__GNUC__)
		if (__JCR_LIST__[0] != NULL && _Jv_RegisterClasses != NULL)
			_Jv_RegisterClasses(__JCR_LIST__);
#endif /* JCR && __GNUC__ */

		/*
		 * Call global constructors.
		 */
		(__ctors)();
	}
}
MD_CALL_STATIC_FUNCTION(.init, __do_global_ctors_aux)

static void USED_NOINLINE
__do_global_dtors_aux(void)
{
	static int finished = 0;

	if (finished)
		return;

#if defined(DSO_HANDLE) && defined(__GNUC__) && defined(SHARED)
	/*
	 * Call local destructors.
	 */
	if (__cxa_finalize != NULL)
		__cxa_finalize(__dso_handle);
#endif /* DSO_HANDLE && __GNUC__ && SHARED */

	/*
	 * Call global destructors.
	 */
	(__dtors)();

#ifdef DWARF2_EH
#if defined(__GNUC__)
	if (__deregister_frame_info != NULL)
		__deregister_frame_info(__EH_FRAME_BEGIN__);
#endif /* __GNUC__ */
#endif /* DWARF2_EH */

	finished = 1;
}
MD_CALL_STATIC_FUNCTION(.fini, __do_global_dtors_aux)
