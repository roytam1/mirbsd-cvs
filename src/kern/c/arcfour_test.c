#if 0

PROG=		arcfour_test
NOMAN=		Yes

SRCS=		arcfour_test.c
SRCS+=		arcfour_base.c
SRCS+=		arcfour_ksa.c
SRCS+=		arcfour_ksa256.c

CPPFLAGS+=	-I${.CURDIR}/../include

.include <bsd.prog.mk>

.if "0" == "1"
#endif

/*-
 * Copyright (c) 2010
 *	Thorsten Glaser <tg@mirbsd.org>
 * Test vectors from the English Wikipedia page on Alledged RC4(tm)
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
#include <assert.h>
#include <stdio.h>
#include <string.h>

__RCSID("$MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $");

const char *keys[] = {
	"Key",
	"Wiki",
	"Secret",
	NULL
};

const char *plain[] = {
	"Plaintext",
	"pedia",
	"Attack at dawn",
	NULL
};

const char *ciphered[] = {
	"BB F3 16 E8 D9 40 AF 0A D3",
	"10 21 BF 04 20",
	"45 A0 1F 64 5F C3 5B 38 35 52 54 4B 9B F5",
	NULL
};

struct arcfour_status cipher, ciph256;
uint8_t keybuf[256], encrypted[32];

int
main(void)
{
	size_t i, j, k = 0;

	do {
		arcfour_init(&cipher);
		arcfour_ksa(&cipher, keys[k], strlen(keys[k]));

		arcfour_init(&ciph256);
		j = strlen(keys[k]);
		for (i = 0; i < 256; ++i)
			keybuf[i] = keys[k][i % j];
		arcfour_ksa256(&ciph256, keybuf);

		printf("Test for ksa, key '%s' ksa %s i=%u j=%u keystream:\n",
		    keys[k], memcmp(&cipher, &ciph256, sizeof(cipher)) ?
		    "FAIL" : "good", cipher.i, cipher.j);
		memhexdump(cipher.S, 0, 32);

		assert(strlen(plain[k]) < 32);
		for (i = 0; i < strlen(plain[k]); ++i)
			encrypted[i] = plain[k][i] ^ arcfour_byte(&cipher);

		printf("Result for plaintext '%s':\n", plain[k]);
		memhexdump(encrypted, 0, 32);

		printf("Expected results: %s\n\n", ciphered[k]);
	} while (keys[++k]);
	return (0);
}

#if 0
.endif
#endif