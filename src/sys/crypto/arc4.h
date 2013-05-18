/* $MirOS: src/sys/crypto/arc4.h,v 1.2 2010/09/12 17:10:45 tg Exp $ */

/* rewritten; no code left, only the API */

#include <sys/slibkern.h>

/* struct rc4_ctx == struct arcfour_status */
#define rc4_ctx arcfour_status

/* this is actually correct, unlike OpenBSD's which is 256 = too small */
#define RC4STATE	sizeof(struct rc4_ctx)
#define RC4KEYLEN	16

void	rc4_keysetup(struct rc4_ctx *, const u_char *, u_int32_t);
void	rc4_crypt(struct rc4_ctx *, const u_char *, u_char *, u_int32_t);
