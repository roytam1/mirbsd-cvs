/*	$OpenBSD: lroundf.c,v 1.1 2005/11/17 20:07:40 otto Exp $	*/
/* $NetBSD: lroundf.c,v 1.3 2008/04/26 23:49:50 christos Exp $ */

/*-
 * Copyright (c) 2004
 *	Matthias Drochner. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <math.h>
#include <sys/types.h>
#include <sys/limits.h>
#include <ieeefp.h>
#include <machine/ieee.h>
#include "math_private.h"

#ifndef LROUNDNAME
#define LROUNDNAME lroundf
#define RESTYPE long int
#define RESTYPE_MIN LONG_MIN
#define RESTYPE_MAX LONG_MAX
#endif

#define RESTYPE_BITS (sizeof(RESTYPE) * 8)

RESTYPE
LROUNDNAME(float x)
{
	u_int32_t i0;
	int e, s, shift;
	RESTYPE res;

	GET_FLOAT_WORD(i0, x);
	e = i0 >> SNG_FRACBITS;
	s = (uint32_t)e >> SNG_EXPBITS;
	e = (e & 0xff) - SNG_EXP_BIAS;

	/* 1.0 x 2^-1 is the smallest number which can be rounded to 1 */
	if (e < -1)
		return (0);
	/* 1.0 x 2^31 (or 2^63) is already too large */
	if (e >= (int)RESTYPE_BITS - 1)
		return (s ? RESTYPE_MIN : RESTYPE_MAX); /* ??? unspecified */

	/* >= 2^23 is already an exact integer */
	if (e < SNG_FRACBITS) {
		/* add 0.5, extraction below will truncate */
		x += (s ? -0.5 : 0.5);
	}

	GET_FLOAT_WORD(i0, x);
	e = ((i0 >> SNG_FRACBITS) & 0xff) - SNG_EXP_BIAS;
	i0 &= 0x7fffff;
	i0 |= (1 << SNG_FRACBITS);

	shift = e - SNG_FRACBITS;
	if (shift >=0)
		res = (shift < 32 ? (RESTYPE)i0 << shift : 0);
	else
		res = (shift > -32 ? i0 >> -shift : 0);

	return (s ? -res : res);
}
