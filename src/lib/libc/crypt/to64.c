#include <sys/types.h>
#include <login_cap.h>

void
mbsd_crypt_32to64(const uint8_t *digits, char *dst, u_int32_t v, int n)
{
	while (--n >= 0) {
		*dst++ = digits[v & 0x3F];
		v >>= 6;
	}
}
