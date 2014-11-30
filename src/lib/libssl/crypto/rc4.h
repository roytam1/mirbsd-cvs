/* $MirOS$ */

#ifndef HEADER_RC4_H
#define HEADER_RC4_H

#ifdef OPENSSL_NO_RC4
#error RC4 is disabled.
#endif

#include <syskern/libckern.h>
#include <openssl/opensslconf.h> /* RC4_INT */

__BEGIN_DECLS

typedef struct arcfour_status RC4_KEY;

const char *RC4_options(void);
void RC4_set_key(RC4_KEY *key, int len, const unsigned char *data)
    __attribute__((__bounded__(__buffer__, 3, 2)));
void RC4(RC4_KEY *key, unsigned long len, const unsigned char *indata,
    unsigned char *outdata)
    __attribute__((__bounded__(__buffer__, 4, 2)))
    __attribute__((__bounded__(__buffer__, 3, 2)));

__END_DECLS

#endif
