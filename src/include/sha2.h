/*	$MirOS: src/include/sha2.h,v 1.4 2014/03/05 20:12:51 tg Exp $ */
/*	$OpenBSD: sha2.h,v 1.6 2004/06/22 01:57:30 jfb Exp $	*/

/*
 * FILE:	sha2.h
 * AUTHOR:	Aaron D. Gifford <me@aarongifford.com>
 * 
 * Copyright © 2013, 2015
 *	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
 * Copyright (c) 2000-2001, Aaron D. Gifford
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
 * 3. Neither the name of the copyright holder nor the names of contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTOR(S) ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTOR(S) BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $From: sha2.h,v 1.1 2001/11/08 00:02:01 adg Exp adg $
 */

#ifndef _SHA2_H
#define _SHA2_H


/*** SHA-256/384/512 Various Length Definitions ***********************/
#define SHA256_BLOCK_LENGTH		64
#define SHA256_DIGEST_LENGTH		32
#define SHA256_DIGEST_STRING_LENGTH	(SHA256_DIGEST_LENGTH * 2 + 1)
#define SHA384_BLOCK_LENGTH		128
#define SHA384_DIGEST_LENGTH		48
#define SHA384_DIGEST_STRING_LENGTH	(SHA384_DIGEST_LENGTH * 2 + 1)
#define SHA512_BLOCK_LENGTH		128
#define SHA512_DIGEST_LENGTH		64
#define SHA512_DIGEST_STRING_LENGTH	(SHA512_DIGEST_LENGTH * 2 + 1)


/*** SHA-256/384/512 Context Structures *******************************/
typedef struct SHA256state_st {
	u_int32_t	state[8];
	u_int64_t	bitcount;
	u_int8_t	buffer[SHA256_BLOCK_LENGTH];
} SHA256_CTX;
typedef struct SHA512state_st {
	u_int64_t	state[8];
	u_int64_t	bitcount[2];
	u_int8_t	buffer[SHA512_BLOCK_LENGTH];
} SHA512_CTX;

typedef SHA512_CTX SHA384_CTX;

#include <sys/cdefs.h>

__BEGIN_DECLS
int SHA256_Init(SHA256_CTX *);
void SHA256_Transform(void *, const unsigned char *)
	__attribute__((__bounded__(__minbytes__, 1, 32)))
	__attribute__((__bounded__(__minbytes__, 2, SHA256_BLOCK_LENGTH)));
int SHA256_Update(SHA256_CTX *, const void *, size_t)
	__attribute__((__bounded__(__string__, 2, 3)));
void SHA256_Pad(SHA256_CTX *);
int SHA256_Final(unsigned char *, SHA256_CTX *)
	__attribute__((__bounded__(__minbytes__, 1, SHA256_DIGEST_LENGTH)));
char *SHA256_End(SHA256_CTX *, char *)
	__attribute__((__bounded__(__minbytes__, 2, SHA256_DIGEST_STRING_LENGTH)));
char *SHA256_File(const char *, char *)
	__attribute__((__bounded__(__minbytes__, 2, SHA256_DIGEST_STRING_LENGTH)));
char *SHA256_FileChunk(const char *, char *, off_t, off_t)
	__attribute__((__bounded__(__minbytes__, 2, SHA256_DIGEST_STRING_LENGTH)));
char *SHA256_Data(const u_int8_t *, size_t, char *)
	__attribute__((__bounded__(__string__, 1, 2)))
	__attribute__((__bounded__(__minbytes__, 3, SHA256_DIGEST_STRING_LENGTH)));

int SHA384_Init(SHA384_CTX *);
void SHA384_Transform(void *, const unsigned char *)
	__attribute__((__bounded__(__minbytes__, 1, 64)))
	__attribute__((__bounded__(__minbytes__, 2, SHA384_BLOCK_LENGTH)));
int SHA384_Update(SHA384_CTX *, const void *, size_t)
	__attribute__((__bounded__(__string__, 2, 3)));
void SHA384_Pad(SHA384_CTX *);
int SHA384_Final(unsigned char *, SHA384_CTX *)
	__attribute__((__bounded__(__minbytes__, 1, SHA384_DIGEST_LENGTH)));
char *SHA384_End(SHA384_CTX *, char *)
	__attribute__((__bounded__(__minbytes__, 2, SHA384_DIGEST_STRING_LENGTH)));
char *SHA384_File(const char *, char *)
	__attribute__((__bounded__(__minbytes__, 2, SHA384_DIGEST_STRING_LENGTH)));
char *SHA384_FileChunk(const char *, char *, off_t, off_t)
	__attribute__((__bounded__(__minbytes__, 2, SHA384_DIGEST_STRING_LENGTH)));
char *SHA384_Data(const u_int8_t *, size_t, char *)
	__attribute__((__bounded__(__string__, 1, 2)))
	__attribute__((__bounded__(__minbytes__, 3, SHA384_DIGEST_STRING_LENGTH)));

int SHA512_Init(SHA512_CTX *);
void SHA512_Transform(void *, const unsigned char *)
	__attribute__((__bounded__(__minbytes__, 1, 64)))
	__attribute__((__bounded__(__minbytes__, 2, SHA512_BLOCK_LENGTH)));
int SHA512_Update(SHA512_CTX *, const void *, size_t)
	__attribute__((__bounded__(__string__, 2, 3)));
void SHA512_Pad(SHA512_CTX *);
int SHA512_Final(unsigned char *, SHA512_CTX *)
	__attribute__((__bounded__(__minbytes__, 1, SHA512_DIGEST_LENGTH)));
char *SHA512_End(SHA512_CTX *, char *)
	__attribute__((__bounded__(__minbytes__, 2, SHA512_DIGEST_STRING_LENGTH)));
char *SHA512_File(const char *, char *)
	__attribute__((__bounded__(__minbytes__, 2, SHA512_DIGEST_STRING_LENGTH)));
char *SHA512_FileChunk(const char *, char *, off_t, off_t)
	__attribute__((__bounded__(__minbytes__, 2, SHA512_DIGEST_STRING_LENGTH)));
char *SHA512_Data(const u_int8_t *, size_t, char *)
	__attribute__((__bounded__(__string__, 1, 2)))
	__attribute__((__bounded__(__minbytes__, 3, SHA512_DIGEST_STRING_LENGTH)));
__END_DECLS

#endif /* _SHA2_H */
