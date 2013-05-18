#include <sys/types.h>

__RCSID("$MirOS$");

const uint8_t mbsd_digits_dec[11] = "0123456789";
const uint8_t mbsd_digits_hex[17] = "0123456789abcdef";
const uint8_t mbsd_digits_HEX[17] = "0123456789ABCDEF";

/* RFC 1521, pad character not part of this */
const uint8_t mbsd_digits_base64[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* crypt, md5crypt */
const uint8_t mbsd_digits_md5crypt[65] =	/* 0..63 => ASCII - 64 */
    "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
/*   0000000000111111111122222222223333333333444444444455555555556666 */
/*   0123456789012345678901234567890123456789012345678901234567890123 */

/* bcrypt */
const uint8_t mbsd_digits_bcrypt[65] =
    "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
