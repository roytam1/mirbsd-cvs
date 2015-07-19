/* $MirOS: src/lib/libssl/src/crypto/bf/blowfish.h,v 1.3 2014/12/15 21:04:22 tg Exp $ */

#ifndef HEADER_BLOWFISH_H
#define HEADER_BLOWFISH_H

#include <openssl/e_os2.h>
#include <sys/types.h>
#include <blf.h>

#ifdef OPENSSL_NO_BF
#error BF is disabled.
#endif

__BEGIN_DECLS

#define BF_ENCRYPT 1
#define BF_DECRYPT 0

#define BF_LONG u_int32_t

#define BF_ROUNDS BLF_N
#define BF_BLOCK 8

typedef struct {
	blf_ctx c;
} BF_KEY;

void BF_set_key(BF_KEY *key, int len, const unsigned char *data);

void BF_encrypt(BF_LONG *data,const BF_KEY *key);
void BF_decrypt(BF_LONG *data,const BF_KEY *key);

void BF_ecb_encrypt(const unsigned char *in, unsigned char *out,
	const BF_KEY *key, int enc);
void BF_cbc_encrypt(const unsigned char *in, unsigned char *out, long length,
	const BF_KEY *schedule, unsigned char *ivec, int enc);
void BF_cfb64_encrypt(const unsigned char *in, unsigned char *out, long length,
	const BF_KEY *schedule, unsigned char *ivec, int *num, int enc);
void BF_ofb64_encrypt(const unsigned char *in, unsigned char *out, long length,
	const BF_KEY *schedule, unsigned char *ivec, int *num);
const char *BF_options(void);

#define BF_encrypt(buf,key) do {					\
	BF_LONG *BLOWFISH_H_data = (BF_LONG *)(buf);			\
									\
	Blowfish_encipher(&((BF_KEY *)(key))->c,			\
	    &BLOWFISH_H_data[0], &BLOWFISH_H_data[1]);			\
} while (/* CONSTCOND */ 0)
#define BF_decrypt(buf,key) do {					\
	BF_LONG *BLOWFISH_H_data = (BF_LONG *)(buf);			\
									\
	Blowfish_decipher(&((BF_KEY *)(key))->c,			\
	    &BLOWFISH_H_data[0], &BLOWFISH_H_data[1]);			\
} while (/* CONSTCOND */ 0)
#define BF_cbc_encrypt(in,buf,l,s,iv,encrypt) do {			\
	unsigned char *BLOWFISH_H_out = (void *)(buf);			\
	long BLOWFISH_H_len = (l);					\
	const BF_KEY *BLOWFISH_H_schedule = (const void *)(s);		\
	unsigned char *BLOWFISH_H_ivec = (void *)(iv);			\
									\
	memcpy(BLOWFISH_H_out, (in), BLOWFISH_H_len);			\
	if (encrypt)							\
		blf_cbc_encrypt(&BLOWFISH_H_schedule->c,		\
		    BLOWFISH_H_ivec, BLOWFISH_H_out, BLOWFISH_H_len);	\
	else								\
		blf_cbc_decrypt(&BLOWFISH_H_schedule->c,		\
		    BLOWFISH_H_ivec, BLOWFISH_H_out, BLOWFISH_H_len);	\
} while (/* CONSTCOND */ 0)
#define BF_set_key(key,bsz,data) do {					\
	int BLOWFISH_H_len = (bsz);					\
									\
	blf_key(&((BF_KEY *)(key))->c, (data),				\
	    BLOWFISH_H_len > 65535 ? 65535 : BLOWFISH_H_len);		\
} while (/* CONSTCOND */ 0)

__END_DECLS

#endif
