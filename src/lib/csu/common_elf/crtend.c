/**	$MirOS: src/lib/csu/common_elf/crtend.c,v 1.2 2005/03/06 20:28:21 tg Exp $ */
/*	$NetBSD: crtend.c,v 1.11 2004/08/28 00:19:22 thorpej Exp $	*/

#include <sys/cdefs.h>
#include "dot_init.h"

__RCSID("$MirOS: src/lib/csu/common_elf/crtend.c,v 1.2 2005/03/06 20:28:21 tg Exp $");

/*
 * WE SHOULD BE USING GCC-SUPPLIED crtend.o FOR GCC 3.3 AND
 * LATER!!!
 */
#if !defined(HAVE_VERSION_SPECIFIC_GCC_LIBS) && __GNUC_PREREQ__(3, 3)
#error "Use GCC-supplied crtend.o"
#endif

static void (*__CTOR_LIST__[1])(void)
    __attribute__((__unused__))
    __attribute__((section(".ctors"))) = { (void *)0 };		/* XXX */
static void (*__DTOR_LIST__[1])(void)
    __attribute__((__unused__))
    __attribute__((section(".dtors"))) = { (void *)0 };		/* XXX */

#ifdef DWARF2_EH
static unsigned int __FRAME_END__[]
    __attribute__((__unused__))
    __attribute__((section(".eh_frame"))) = { 0 };
#endif

#if defined(JCR) && defined(__GNUC__)
static void *__JCR_END__[1]
    __attribute__((__unused__, section(".jcr"))) = { (void *) 0 };
#endif
