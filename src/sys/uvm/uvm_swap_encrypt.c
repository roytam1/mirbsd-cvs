/**	$MirOS: src/sys/uvm/uvm_swap_encrypt.c,v 1.5 2010/09/19 19:14:42 tg Exp $ */
/*	$OpenBSD: uvm_swap_encrypt.c,v 1.12 2003/12/26 10:04:49 markus Exp $	*/

/*-
 * Copyright 2008 Thorsten Glaser <tg@mirbsd.org>
 * Copyright 1999 Niels Provos <provos@citi.umich.edu>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by Niels Provos.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/malloc.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <sys/conf.h>
#include <dev/rndvar.h>
#include <crypto/rijndael.h>

#include <uvm/uvm.h>

struct swap_key *kcur = NULL;
rijndael_ctx swap_ctxt;

int uvm_doswapencrypt = 1;
u_int uvm_swpkeyscreated = 0;
u_int uvm_swpkeysdeleted = 0;

int swap_encrypt_initialized = 0;

int
swap_encrypt_ctl(name, namelen, oldp, oldlenp, newp, newlen, p)
	int *name;
	u_int namelen;
	void *oldp;
	size_t *oldlenp;
	void *newp;
	size_t newlen;
	struct proc *p;
{
	/* all sysctl names at this level are terminal */
	if (namelen != 1)
		return (ENOTDIR);		/* overloaded */

	switch (name[0]) {
	case SWPENC_ENABLE: {
		int doencrypt = uvm_doswapencrypt;
		int result;

		result = sysctl_int(oldp, oldlenp, newp, newlen, &doencrypt);
		if (result)
			return result;

		/* Swap Encryption has been turned on, we need to
		 * initialize state for swap devices that have been
		 * added
		 */
		if (doencrypt)
			uvm_swap_initcrypt_all();
		uvm_doswapencrypt = doencrypt;
		return (0);
	}
	case SWPENC_CREATED:
		return (sysctl_rdint(oldp, oldlenp, newp, uvm_swpkeyscreated));
	case SWPENC_DELETED:
		return (sysctl_rdint(oldp, oldlenp, newp, uvm_swpkeysdeleted));
	default:
		return (EOPNOTSUPP);
	}
	/* NOTREACHED */
}

void
swap_key_create(struct swap_key *key)
{
	key->refcount = 0;
	arc4random_buf(key->key, sizeof(key->key));

	uvm_swpkeyscreated++;
}

void
swap_key_delete(struct swap_key *key)
{
	/* Make sure that this key gets removed if we just used it */
	swap_key_cleanup(key);

	memset(key, 0, sizeof(*key));
	uvm_swpkeysdeleted++;
}

/*
 * Encrypt the data before it goes to swap, the size should be 128-bit
 * aligned.
 */

void
swap_encrypt(struct swap_key *key, caddr_t src, caddr_t dst,
	     u_int64_t block, size_t count)
{
	u_int32_t iv[4];

	if (!swap_encrypt_initialized)
		swap_encrypt_initialized = 1;

	swap_key_prepare(key, 1);

	iv[0] = block >> 32; iv[1] = block; iv[2] = ~iv[0]; iv[3] = ~iv[1];
	(*rijndael_cbc_encrypt_fast)(&swap_ctxt, NULL, (u_char *)iv,
	    (u_char *)iv, 1);
	(*rijndael_cbc_encrypt_fast)(&swap_ctxt, (u_char *)iv, (u_char *)src,
	    (u_char *)dst, count / 16);
}

/*
 * Decrypt the data after we retrieved it from swap, the size should be 128-bit
 * aligned.
 */

void
swap_decrypt(struct swap_key *key, caddr_t src, caddr_t dst,
	     u_int64_t block, size_t count)
{
	u_int32_t iv[4];

	if (!swap_encrypt_initialized)
		panic("swap_decrypt: key not initialized");

	swap_key_prepare(key, 0);

	iv[0] = block >> 32; iv[1] = block; iv[2] = ~iv[0]; iv[3] = ~iv[1];
	(*rijndael_cbc_encrypt_fast)(&swap_ctxt, NULL, (u_char *)iv,
	    (u_char *)iv, 1);
	(*rijndael_cbc_decrypt_fast)(&swap_ctxt, (u_char *)iv, (u_char *)src,
	    (u_char *)dst, count / 16);
}

void
swap_key_prepare(struct swap_key *key, int encrypt)
{
	/* Check if we have prepared for this key already,
	 * if we only have the encryption schedule, we have
	 * to recompute and get the decryption schedule also
	 */
	if (kcur == key && (encrypt || !swap_ctxt.enc_only))
		return;

	if (encrypt)
		(*rijndael_set_key_enc_only_fast)(&swap_ctxt,
		    (u_char *)key->key, sizeof (key->key) * 8);
	else
		(*rijndael_set_key_fast)(&swap_ctxt,
		    (u_char *)key->key, sizeof (key->key) * 8);

	kcur = key;
}

/*
 * Make sure that a specific key is no longer available.
 */

void
swap_key_cleanup(struct swap_key *key)
{
	/* Check if we have a key */
	if (kcur == NULL || kcur != key)
		return;

	/* Zero out the subkeys */
       	memset(&swap_ctxt, 0, sizeof(swap_ctxt));

	kcur = NULL;
}
