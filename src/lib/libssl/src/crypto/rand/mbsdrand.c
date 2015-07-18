/*-
 * Copyright © 2014
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
 */

#include <stdlib.h>
#include <openssl/rand.h>

__RCSID("$MirOS: src/lib/libssl/src/crypto/rand/mbsdrand.c,v 1.6 2014/11/26 19:16:45 tg Exp $");

const char RAND_version[] = "MirBSD";

extern void arc4random_ctl(unsigned int);

static void ssleay_rand_seed(const void *, int);
static int ssleay_rand_bytes(unsigned char *, int);
static void ssleay_rand_cleanup(void);
static void ssleay_rand_add(const void *, int, double);
static void ssleay_rand_addb(int, const void *, int, double);

RAND_METHOD rand_ssleay_meth = {
	ssleay_rand_seed,
	ssleay_rand_bytes,
	ssleay_rand_cleanup,
	ssleay_rand_add,
	ssleay_rand_bytes,
	RAND_poll
};

RAND_METHOD *
RAND_SSLeay(void)
{
	return (&rand_ssleay_meth);
}

int
RAND_poll(void)
{
	(void)arc4random();
	return (1);
}

static void
ssleay_rand_seed(const void *buf, int num)
{
	ssleay_rand_addb(1, buf, num, num);
}

static int
ssleay_rand_bytes(unsigned char *buf, int num)
{
	if ((buf != NULL) && (num > 0))
		arc4random_buf(buf, num);
	return (1);
}

static void
ssleay_rand_cleanup(void)
{
}

static void
ssleay_rand_add(const void *buf, int num, double add_entropy)
{
	ssleay_rand_addb(2, buf, num, add_entropy);
}

static void
ssleay_rand_addb(int w, const void *buf, int num, double add_entropy)
{
	struct {
		double e;
		const void *bp;
		int n;
		int w;
	} x;

	x.bp = buf;
	x.n = num;
	x.e = add_entropy;
	x.w = w;
	arc4random_pushb_fast(&x, sizeof(x));
	if ((buf != NULL) && (num > 0))
		arc4random_pushb_fast(buf, num);
	arc4random_ctl(0);
}
