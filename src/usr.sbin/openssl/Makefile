# $MirOS$
# $OpenBSD: Makefile,v 1.16 2004/02/27 17:36:18 deraadt Exp $

PROG=	openssl
LDADD=	-lssl -lcrypto
DPADD=	${LIBSSL} ${LIBCRYPTO}

SSLEAYDIST= lib/libssl/src

SSLEAY_SRC= ${.CURDIR}/../../${SSLEAYDIST}/apps
SSLEAY_SRC_TOP= ${.CURDIR}/../../${SSLEAYDIST}

.if ${MACHINE_ARCH} == "i386" || ${MACHINE_ARCH} == "vax" || \
    ${MACHINE_ARCH} == "amd64"

CPPFLAGS+= -DL_ENDIAN
.elif ${MACHINE_ARCH} == "alpha"
# no ENDIAN stuff defined for alpha
.else
CPPFLAGS+= -DB_ENDIAN
.endif

CPPFLAGS+= -DMONOLITH -DOPENSSL_NO_IDEA -DTERMIOS -DANSI_SOURCE
CPPFLAGS+= -I${SSLEAY_SRC_TOP}

SRCS=	verify.c asn1pars.c req.c dgst.c dh.c enc.c passwd.c gendh.c errstr.c\
	pkcs7.c crl2p7.c crl.c ca.c \
	rsa.c dsa.c dsaparam.c \
	x509.c genrsa.c gendsa.c s_server.c s_client.c speed.c \
	s_time.c apps.c s_cb.c s_socket.c version.c sess_id.c \
	app_rand.c ciphers.c nseq.c pkcs12.c pkcs8.c spkac.c smime.c \
	dhparam.c openssl.c rand.c rsautl.c engine.c ocsp.c

.PATH:	${SSLEAY_SRC}

.include <bsd.prog.mk>
