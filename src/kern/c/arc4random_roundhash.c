/*-
 * Copyright (c) 2010, 2011, 2012, 2013
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

#include <libckern.h>
#include <nzat.h>

__RCSID("$MirOS: src/kern/c/arc4random_roundhash.c,v 1.5 2013/10/18 21:58:45 tg Exp $");

void
arc4random_roundhash(uint32_t pools[32], uint8_t *poolptr,
    const void *buf_, size_t len)
{
	register uint32_t h;
	register unsigned int pool;
	const uint8_t *buf = (const uint8_t *)buf_;

	pool = *poolptr;
	while (len--) {
		pool = (pool + 1) & 31;
		h = pools[pool];
		NZATUpdateByte(h, *buf++);
		pools[pool] = h;
	}
	*poolptr = pool;
}

/*-
 * TODO:
 * mix the content after precisely 128 bytes have been roundhashed
 * idea for an algorithm:
 *
 * register uint32_t h;
 * uint32_t irest, ilow3, ihigh, j, i;
 * union {
 *	uint32_t dw[32];
 *	uint8_t db[128];
 * } tmpa;
 * uint32_t tmpb[32];
 * typeof(*poolptr) saved;
 *
 * saved = *poolptr;
 * arc4random_roundhash(pools, poolptr, &saved, sizeof(saved)); //optional
 * for (irest = 0; irest < 32; ++irest) { //using irest as counter coz register
 *	h = pools[irest];
 *	NZAATFinish(h);
 *	tmpa.dw[irest] = h;
 * }
 * for (ihigh = 0; ihigh < 8; ihigh += 4)
 *	for (irest = 0; irest < 4; ++irest)
 *		for (ilow3 = 0; ilow3 < 4; ++ilow3) {
 *			j = ((ihigh + irest) << 4) + ilow3;
 *			h = make_dword(tmpa.db[j; j+4; j+8; j+12]);
 *			NZAATFinish(h);
 *			pools[((ihigh + ilow3) << 2) + irest] = h;
 *			tmpb[(irest << 3) + ilow3 + (ihigh ^ 4)] = h;
 *		 }
 * *poolptr = 0;
 * arc4random_roundhash(pools, poolptr, tmpb, 128);
 * *poolptr = saved;
 *
 * XXX check this against {{{

			⎜               ⎜               ⎜               ⎜               ⎜               ⎜               ⎜               .
	<--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><--><-->
finish	 F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F
yields	00000000000000001111111111111111222222222222222233333333333333334444444444444444555555555555555566666666666666667777777777777777
	0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF
	12341234123412341234123412341234123412341234123412341234123412341234123412341234123412341234123412341234123412341234123412341234
swab¹	    \     /
	    /     \
result	00000000000000001111111111111111222222222222222233333333333333334444444444444444555555555555555566666666666666667777777777777777
	048C159D26AE37BF048C159D26AE37BF048C159D26AE37BF048C159D26AE37BF048C159D26AE37BF048C159D26AE37BF048C159D26AE37BF048C159D26AE37BF
finish	 F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F   F
yields	00000000000000001111111111111111222222222222222233333333333333334444444444444444555555555555555566666666666666667777777777777777
	0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF
+ copyto
	44444444444444440000000000000000555555555555555511111111111111116666666666666666222222222222222277777777777777773333333333333333
	0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF01234567
+ also				    \     /
				    /     \
	00001111222233330000111122223333000011112222333300001111222233334444555566667777444455556666777744445555666677774444555566667777
	0123012301230123456745674567456789AB89AB89AB89ABCDEFCDEFCDEFCDEF0123012301230123456745674567456789AB89AB89AB89ABCDEFCDEFCDEFCDEF
X roundhash with copy-from-above
	45674567456745674567456745674567456745674567456745674567456745670123012301230123012301230123012301230123012301230123012301230123
	0000111122223333444455556666777788889999AAAABBBBCCCCDDDDEEEEFFFF0000111122223333444455556666777788889999AAAABBBBCCCCDDDDEEEEFFFF
⇒ directly usable hash states

① although just swapping then running NZAATFinish() is very probably not
  guaranteed to avalanche enough; just adding the four bytes will do, as
  will adding three to the existing one (which gets a slightly different
  outcome for the next mixing stage), or even four…

 * }}} XXX
 */
