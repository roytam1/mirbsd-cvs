#include <openssl/cast.h>

#undef CAST_set_key

void
CAST_set_key(CAST_KEY *key, int len, const unsigned char *data)
{
	cast_setkey(key, data, len);
}
