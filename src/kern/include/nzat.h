/*-
 * Copyright © 2011
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un‐
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person’s immediate fault when using the work as intended.
 *-
 * The NZAT and NZAAT hashes are provided as inline macro bodies; see
 * below for some theory.
 *
 * NZATInit(h) ⇒ writes the IV of 0 to (h)
 * NZATUpdateByte(h,b) ⇒ updates (h) with (b)
 * NZATUpdateMem(h,p,z) ⇒ updates (h) with (p)[0..(z)[
 * NZATUpdateString(h,s) ⇒ updates (h) with (s)[0..strlen(s)[
 * NZATFinish(h) ⇒ return a non-zero 32-bit hash result in (h)
 * NZAATFinish(h) ⇒ return a 32-bit hash result in (h)
 */

#ifndef SYSKERN_NZAT_H
#define SYSKERN_NZAT_H

#include <sys/types.h>

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

/*-
 * This file defines the NZAT hash which is derived from Bob Jenkins’
 * one at a time hash with the goals to ① not have 00000000 as result
 * (for speed optimisations with hash table lookups) and ② change for
 * every input octet, even NUL bytes – no matter what state. For con‐
 * venience, NZAAT, which can have an all-zero result, for outside of
 * hash table lookup dereference deferral, is also provided.
 *
 * We define the following primitives (all modulo 2³²):
 *
 * OUP(s,b) → { OAV(s,b); MIX(s); }
 *	This is the Update function of Jenkins’ one-at-a-time hash
 * NUP(s,b) → { NAV(s,b); MIX(s); }
 *	This shall be the NZATUpdate function
 * OAV(s,b) → { ADD(s,b); }
 *	This is how the Add part of Jenkins’ one-at-a-time hash works
 * NAV(s,b) → { ADD(s,b+c); } – c const
 *	This is how the Add part of NZATUpdate differs – by a const
 * ADD(x,y) → { x += y; }
 *	Generic addition function
 * MIX(s) → { s += s << 10; s ^= s >> 6; }
 *	This is the Mix part of both Update functions (common)
 * FIN(s) → { s += s << 3; s ^= s >> 11; s += s << 15; result ← s; }
 *	This is the Postprocess function for the one-at-a-time hash
 * NZF(s) → { if(!s){++s;} FIN(s); }
 *	This is the Postprocess function for the NZAT hash
 *
 * This means that the difference between OAAT and NZAT is ① a factor
 * c (constant) that is added to the state in addition to every input
 * octet, ② preventing the hash result from becoming 0, by a volunta‐
 * ry collision on exactly(!) one value. It’s assumed the impact from
 * these changes doesn’t change the hash’s properties, except for the
 * new collision. NZAAT does not collide more than OAAT.
 *
 * First some observations on some of the above primitives, proven by
 * me empirically (can be proven algebraically as well):
 *
 * FIN(s) = 0 ⇐ s = 0
 *	Only a state of 0 yields a hash result of 0
 * MIX(s) = 0 ⇐ s = 0
 *	When updating only the Add part (not the Mix part) determines
 *	whether the next state is 0
 * ADD(s,v) = 0 ⇐ s = 100000000h - v (mod 2³²)
 *	For each input byte value there is exactly one previous-state
 *	producing a 0 next-state (that being -s mod 2³² for dword in‐
 *	put values and, for bytes, simpler -s mod 2⁸)
 * ADD(s,b+c) ≠ s ⇐ b is byte, c is 1, works
 *	Choose c arbitrarily, 1 is economical, even on e.g. ARM
 *
 * All this means we can use an IV of 0, add arbitrary octet data and
 * have a good result (for NZAAT) while having to provide for exactly
 * one 2-in-1 collision for NZAT manually. This implementation mainly
 * aims for economic code (small, fast, RISC CPUs notwithstanding).
 */

#define NZATInit(h) do {					\
	(h) = 0;						\
} while (/* CONSTCOND */ 0)

#define NZATUpdateByte(h,b) do {				\
	(h) += (uint8_t)(b);					\
	++(h);							\
	(h) += (h) << 10;					\
	(h) ^= (h) >> 6;					\
} while (/* CONSTCOND */ 0)

#define NZATUpdateMem(h,p,z) do {				\
	register const uint8_t *NZATUpdateMem_p;		\
	register size_t NZATUpdateMem_z = (z);			\
								\
	NZATUpdateMem_p = (const void *)(p);			\
	while (NZATUpdateMem_z--)				\
		NZATUpdateByte((h), *NZATUpdateMem_p++);	\
} while (/* CONSTCOND */ 0)

#define NZATUpdateString(h,s) do {				\
	register const char *NZATUpdateString_s;		\
	register uint8_t NZATUpdateString_c;			\
								\
	NZATUpdateString_s = (const void *)(s);			\
	while ((NZATUpdateString_c = *NZATUpdateString_s++))	\
		NZATUpdateByte((h), NZATUpdateString_c);	\
} while (/* CONSTCOND */ 0)

/* not zero after termination */
#define NZATFinish(h) do {					\
	if ((h) == 0)						\
		++(h);						\
	else							\
		NZAATFinish(h);					\
} while (/* CONSTCOND */ 0)

/* NULs zählen an allen Teilen */
#define NZAATFinish(h) do {					\
	(h) += (h) << 3;					\
	(h) ^= (h) >> 11;					\
	(h) += (h) << 15;					\
} while (/* CONSTCOND */ 0)

#endif
