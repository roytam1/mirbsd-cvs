/* $MirOS: contrib/hosted/fwcf/pack.h,v 1.10 2006/09/23 19:47:39 tg Exp $ */

/*
 * This file is part of the FreeWRT project. FreeWRT is copyrighted
 * material, please see the LICENCE file in the top-level directory
 * or at http://www.freewrt.org/license for details.
 */

#ifndef SYSDEPS_H
#define SYSDEPS_H

__BEGIN_DECLS
void pull_rndata(uint8_t *, size_t);
void push_rndata(uint8_t *, size_t);
__END_DECLS

#endif
