#include <openssl/blowfish.h>
#include <string.h>

#undef BF_encrypt
#undef BF_decrypt
#undef BF_cbc_encrypt

void
BF_encrypt(BF_LONG *data, const BF_KEY *key)
{
	Blowfish_encipher(&key->c, &data[0], &data[1]);
}

void
BF_decrypt(BF_LONG *data, const BF_KEY *key)
{
	Blowfish_decipher(&key->c, &data[0], &data[1]);
}

void
BF_cbc_encrypt(const unsigned char *in, unsigned char *out, long length,
    const BF_KEY *schedule, unsigned char *ivec, int encrypt)
{
	memcpy(out, in, length);
	if (encrypt)
		blf_cbc_encrypt(&schedule->c, ivec, out, length);
	else
		blf_cbc_decrypt(&schedule->c, ivec, out, length);
}
