/* $MirOS: src/lib/libssl/crypto/rc4.h,v 1.2 2014/12/15 21:04:21 tg Exp $ */

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

#define RC4_version		"$MirOS: src/lib/libssl/crypto/rc4.h,v 1.2 2014/12/15 21:04:21 tg Exp $"
#define RC4_options()		"rc4(ptr,char)"
#define RC4_set_key(key,len,data) do {			\
	arcfour_init(key);				\
	arcfour_ksa(key, data, (int)len);		\
} while (/* CONSTCOND */ 0)
#define RC4(key,bsz,inbuf,outbuf) do {			\
	unsigned long RC4_H_len = (bsz);		\
	const uint8_t *RC4_H_indata = (inbuf);		\
	uint8_t *RC4_H_outdata = (outbuf);		\
							\
	while (RC4_H_len--)				\
		*RC4_H_outdata++ = *RC4_H_indata++ ^	\
		    arcfour_byte(key);			\
} while (/* CONSTCOND */ 0)

__END_DECLS

#endif
