#include <openssl/cast.h>

void
CAST_set_key(CAST_KEY *key, int len, const unsigned char *data)
{
	cast_setkey(key, data, len);
}
