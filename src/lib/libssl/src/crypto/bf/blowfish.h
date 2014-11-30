/* $MirOS$ */

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

__END_DECLS

#endif
