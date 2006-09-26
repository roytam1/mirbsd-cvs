/* $MirOS: contrib/hosted/fwcf/sysdeps.h,v 1.1 2006/09/23 20:20:01 tg Exp $ */

/*
 * This file is part of the FreeWRT project. FreeWRT is copyrighted
 * material, please see the LICENCE file in the top-level directory
 * or at http://www.freewrt.org/licence for details.
 */

#ifndef SYSDEPS_H
#define SYSDEPS_H

__BEGIN_DECLS
void pull_rndata(uint8_t *, size_t);
void push_rndata(uint8_t *, size_t);
__END_DECLS

#endif
