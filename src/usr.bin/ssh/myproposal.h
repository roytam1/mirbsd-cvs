/* $MirOS: src/usr.bin/ssh/myproposal.h,v 1.11 2007/09/13 13:52:54 tg Exp $ */
/* $OpenBSD: myproposal.h,v 1.23 2009/01/23 07:58:11 djm Exp $ */

/*
 * Copyright (c) 2000 Markus Friedl.  All rights reserved.
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

#define KEX_DEFAULT_KEX		\
	"diffie-hellman-group-exchange-sha256," \
	"diffie-hellman-group-exchange-sha1," \
	"diffie-hellman-group14-sha1," \
	"diffie-hellman-group1-sha1"
#define	KEX_DEFAULT_PK_ALG	"ssh-rsa,ssh-dss"

#define	KEX_DEFAULT_ENCRYPT \
	"aes256-ctr,arcfour256,aes256-cbc,cast128-cbc,aes128-cbc," \
	"blowfish-cbc,rijndael-cbc@lysator.liu.se,aes128-ctr," \
	"arcfour128,arcfour,aes192-cbc,aes192-ctr,3des-cbc"
#define	KEX_DEFAULT_MAC \
	"umac-64@openssh.com,hmac-ripemd160,hmac-ripemd160@openssh.com," \
	"hmac-sha1,hmac-sha1-96,hmac-md5,hmac-md5-96"
#define	KEX_DEFAULT_COMP	"none,zlib@openssh.com,zlib"
#define	KEX_DEFAULT_LANG	""


static const char *myproposal[PROPOSAL_MAX] = {
	KEX_DEFAULT_KEX,
	KEX_DEFAULT_PK_ALG,
	KEX_DEFAULT_ENCRYPT,
	KEX_DEFAULT_ENCRYPT,
	KEX_DEFAULT_MAC,
	KEX_DEFAULT_MAC,
	KEX_DEFAULT_COMP,
	KEX_DEFAULT_COMP,
	KEX_DEFAULT_LANG,
	KEX_DEFAULT_LANG
};
