/*	$OpenBSD: adddi3.c,v 1.3 2003/06/02 23:28:07 millert Exp $	*/
/*	$NetBSD: adddi3.c,v 1.5 1995/10/07 09:26:14 mycroft Exp $	*/

/*-
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
#if 0
static char sccsid[] = "@(#)adddi3.c	8.1 (Berkeley) 6/4/93";
#else
static char rcsid[] = "$OpenBSD: adddi3.c,v 1.3 2003/06/02 23:28:07 millert Exp $";
#endif
#endif /* LIBC_SCCS and not lint */

#include "quad.h"

/*
 * Add two quads.  This is trivial since a one-bit carry from a single
 * u_long addition x+y occurs if and only if the sum x+y is less than
 * either x or y (the choice to compare with x or y is arbitrary).
 */
quad_t
__adddi3(a, b)
	quad_t a, b;
{
	union uu aa, bb, sum;

	aa.q = a;
	bb.q = b;
	sum.ul[L] = aa.ul[L] + bb.ul[L];
	sum.ul[H] = aa.ul[H] + bb.ul[H] + (sum.ul[L] < bb.ul[L]);
	return (sum.q);
}
