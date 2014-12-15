#include <stdio.h>
#include <string.h>
#include <openssl/blowfish.h>

#undef BF_set_key

void
BF_set_key(BF_KEY *key, int len, const unsigned char *data)
{
	blf_key(&key->c, data, len > 65535 ? 65535 : len);
}
