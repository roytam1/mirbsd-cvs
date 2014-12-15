/* $MirOS: src/lib/libssl/src/crypto/cast/cast.h,v 1.2 2014/11/30 01:59:38 tg Exp $ */

#ifndef HEADER_CAST_H
#define HEADER_CAST_H

#include <sys/types.h>
#include <cast.h>

#ifdef OPENSSL_NO_CAST
#error CAST is disabled.
#endif

__BEGIN_DECLS

#define CAST_ENCRYPT 1
#define CAST_DECRYPT 0

#define CAST_LONG u_int32_t

#define CAST_BLOCK 8
#define CAST_KEY_LENGTH 16

#define CAST_KEY cast_key

void CAST_set_key(CAST_KEY *key, int len, const unsigned char *data);
void CAST_ecb_encrypt(const unsigned char *in,unsigned char *out,CAST_KEY *key,
		      int enc);
void CAST_encrypt(CAST_LONG *data,CAST_KEY *key);
void CAST_decrypt(CAST_LONG *data,CAST_KEY *key);
void CAST_cbc_encrypt(const unsigned char *in, unsigned char *out, long length,
		      CAST_KEY *ks, unsigned char *iv, int enc);
void CAST_cfb64_encrypt(const unsigned char *in, unsigned char *out,
			long length, CAST_KEY *schedule, unsigned char *ivec,
			int *num, int enc);
void CAST_ofb64_encrypt(const unsigned char *in, unsigned char *out, 
			long length, CAST_KEY *schedule, unsigned char *ivec,
			int *num);

#if (MirBSD >= 0x0AB5)
#define CAST_encrypt(data,key)		cast_encrypt2(key, data)
#define CAST_decrypt(data,key)		cast_decrypt2(key, data)
#endif
#define CAST_set_key(key,len,data)	cast_setkey(key, data, len)

__END_DECLS

#endif
