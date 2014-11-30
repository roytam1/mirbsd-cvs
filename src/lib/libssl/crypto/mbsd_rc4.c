#include <openssl/rc4.h>

const char RC4_version[] __attribute__((__used__)) = "$MirOS: src/lib/libssl/crypto/mbsd_md4.c,v 1.1 2014/11/29 23:47:03 tg Exp $";

const char *
RC4_options(void)
{
	char RC4_INT_correct_size[(sizeof(RC4_INT) == 1) ? 1 : -1];

	return ("rc4(ptr,char)");
}

void
RC4_set_key(RC4_KEY *key, int len, const unsigned char *data)
{
	arcfour_init(key);
	arcfour_ksa(key, data, len);
}

void
RC4(RC4_KEY *key, unsigned long len, const unsigned char *indata,
    unsigned char *outdata)
{
	while (len--)
		*outdata++ = *indata++ ^ arcfour_byte(key);
}
