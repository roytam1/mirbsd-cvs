/* $MirOS$ */

/* rewritten; no code left, only the API */

#include <sys/types.h>
#include <crypto/arc4.h>

void
rc4_keysetup(struct rc4_ctx *ctx, u_char *key, u_int32_t klen)
{
	arcfour_init(ctx);
	arcfour_ksa(ctx, key, klen);
}

void
rc4_crypt(struct rc4_ctx *ctx, u_char *src, u_char *dst, u_int32_t len)
{
	while (len--)
		*dst++ = *src++ ^ arcfour_byte(ctx);
}
