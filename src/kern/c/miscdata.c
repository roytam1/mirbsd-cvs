/* collection of data, not copyrightable */

#include <sys/types.h>

__RCSID("$MirOS$");

#ifdef L_mbsd_digits_dec
const uint8_t mbsd_digits_dec[11] = "0123456789";
#endif

#ifdef L_mbsd_digits_hex
const uint8_t mbsd_digits_hex[17] = "0123456789abcdef";
#endif

#ifdef L_mbsd_digits_HEX
const uint8_t mbsd_digits_HEX[17] = "0123456789ABCDEF";
#endif

/* RFC 1521 */

#ifdef L_mbsd_digits_base64
const uint8_t mbsd_digits_base64[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
#endif

#ifdef L_RFC1321_padding
const uint8_t RFC1321_padding[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
#endif

#ifdef L_mbsd_digits_md5crypt
/* crypt, md5crypt */
const uint8_t mbsd_digits_md5crypt[65] =	/* 0..63 => ASCII - 64 */
    "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
/*   0000000000111111111122222222223333333333444444444455555555556666 */
/*   0123456789012345678901234567890123456789012345678901234567890123 */
#endif

#ifdef L_mbsd_digits_bcrypt
/* bcrypt */
const uint8_t mbsd_digits_bcrypt[65] =
    "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
#endif
