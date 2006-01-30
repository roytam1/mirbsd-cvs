/* $MirOS: src/share/misc/licence.template,v 1.6 2006/01/24 22:24:02 tg Rel $ */
/* $OpenBSD: x509.c,v 1.2 2005/05/28 08:07:45 marius Exp $ */
/* _MirOS: src/usr.bin/ssh/ssh-keygen.c,v 1.9 2006/01/30 15:47:04 tg Exp $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 */

#include <sys/param.h>
#include <sys/uio.h>
#include <openssl/ssl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "extern.h"
#include "key.h"
#include "pemrsa.h"

__RCSID("$MirOS$");

#define PEMRSA_PUBKEY_MAGIC	"-----BEGIN PUBLIC KEY-----"

int
pemrsa_load_public(struct key *k, struct iovec *iov)
{
	BIO *bio;
	RSA *rsa;

	if (strncmp((char *)iov->iov_base, PEMRSA_PUBKEY_MAGIC,
	    strlen(PEMRSA_PUBKEY_MAGIC)))
		return (-1);

	if ((bio = BIO_new(BIO_s_mem())) == NULL)
		return (-1);

	if (BIO_write(bio, iov->iov_base, iov->iov_len + 1) <= 0) {
		BIO_free(bio);
		return (-1);
	}

	rsa = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
	BIO_free(bio);

	if (rsa == NULL)
		return (-1);

	k->type = KEY_RSA;
	k->data = rsa;
	return (0);
}
