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
#include LIBC_TPH

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

const char RAND_version[] = "MirBSD";

extern void arc4random_stir_locked(pid_t);

static void ssleay_rand_seed(const void *, int);
static int ssleay_rand_bytes(unsigned char *, int);
static void ssleay_rand_cleanup(void);
static void ssleay_rand_add(const void *, int, double);
static void ssleay_rand_addb(const void *, int, double, int);

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
	return (1);
}

static void
ssleay_rand_seed(const void *buf, int num)
{
	ssleay_rand_addb(buf, num, num, 1);
}

static int
ssleay_rand_bytes(unsigned char *buf, int num)
{
	if (num > 0)
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
	ssleay_rand_addb(buf, num, add_entropy, 2);
}

static void
ssleay_rand_addb(const void *buf, int num, double add_entropy, int w)
{
	struct {
		const void *bp;
		double e;
		int n;
		int w;
	} x;

	x.bp = buf;
	x.n = num;
	x.e = add_entropy;
	x.w = w;
	arc4random_pushb_fast(&x, sizeof(x));
	if (num > 0)
		arc4random_pushb_fast(buf, num);
	if ((add_entropy <= num) && (add_entropy > 127)) {
		_ARC4_LOCK();
		arc4random_stir_locked(0);
		_ARC4_UNLOCK();
	}
}
