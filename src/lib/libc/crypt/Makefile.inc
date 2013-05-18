# $MirOS: src/lib/libc/crypt/Makefile.inc,v 1.7 2010/09/12 17:10:50 tg Exp $
# $OpenBSD: Makefile.inc,v 1.15 2003/08/12 01:22:17 deraadt Exp $

.PATH: ${LIBCSRCDIR}/arch/${MACHINE_ARCH}/crypt ${LIBCSRCDIR}/crypt

SRCS+=	cast.c crypt.c crypt2.c md5crypt.c blowfish.c
SRCS+=  bcrypt.c pwd_gensalt.c skipjack.c to64.c

MAN+=	crypt.3 blowfish.3 arc4random.3
MLINKS+=crypt.3 encrypt.3 crypt.3 setkey.3 crypt.3 des_cipher.3
MLINKS+=crypt.3 bcrypt_gensalt.3 crypt.3 bcrypt.3 crypt.3 md5crypt.3
MLINKS+=crypt.3 des_setkey.3 blowfish.3 blf_key.3 blowfish.3 blf_enc.3
MLINKS+=blowfish.3 blf_dec.3 blowfish.3 blf_ecb_encrypt.3
MLINKS+=blowfish.3 blf_ecb_decrypt.3 blowfish.3 blf_cbc_encrypt.3
MLINKS+=blowfish.3 blf_cbc_decrypt.3

SRCS+=	arc4random_addrandom.c
SRCS+=	arc4random_base.c
SRCS+=	arc4random_buf.c
SRCS+=	arc4random_pushb_fast.c
SRCS+=	arc4random_push✲_old.c
SRCS+=	arc4random_stir.c
MLINKS+=arc4random.3 arc4random_buf.3
MLINKS+=arc4random.3 arc4random_uniform.3
MLINKS+=arc4random.3 arc4random_stir.3
MLINKS+=arc4random.3 arc4random_addrandom.3
MLINKS+=arc4random.3 arc4random_push.3
MLINKS+=arc4random.3 arc4random_pushb.3
MLINKS+=arc4random.3 arc4random_pushb_fast.3
MLINKS+=arc4random.3 arc4random_pushk.3
