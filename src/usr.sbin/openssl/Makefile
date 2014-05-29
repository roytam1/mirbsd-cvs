# $MirOS: src/usr.sbin/openssl/Makefile,v 1.12 2007/09/28 12:41:54 tg Exp $
# $OpenBSD: Makefile,v 1.17 2005/04/29 05:42:55 djm Exp $

PROG=		openssl
LDADD=		-lssl -lcrypto -lmbfun
DPADD=		${LIBSSL} ${LIBCRYPTO} ${LIBMBFUN}

.include <bsd.own.mk>

SSLEAYDIST=	lib/libssl/src
SSLEAY_SRC_TOP=	${BSDSRCDIR}/${SSLEAYDIST}
SSLEAY_SRC=	${SSLEAY_SRC_TOP}/apps

CPPFLAGS+=	-DMONOLITH
CPPFLAGS+=	-DMBSD_CB_ARND
CPPFLAGS+=	-I${SSLEAY_SRC_TOP} -I${SSLEAY_SRC}

.include "${SSLEAY_SRC_TOP}/../Makefile.inc"

SRCS=	verify.c asn1pars.c req.c dgst.c dh.c enc.c passwd.c gendh.c errstr.c \
	pkcs7.c crl2p7.c crl.c ca.c \
	rsa.c dsa.c dsaparam.c \
	x509.c genrsa.c gendsa.c s_server.c s_client.c speed.c \
	s_time.c apps.c s_cb.c s_socket.c version.c sess_id.c \
	app_rand.c ciphers.c nseq.c pkcs12.c pkcs8.c spkac.c smime.c \
	dhparam.c openssl.c rand.c rsautl.c engine.c ocsp.c prime.c

.PATH:	${SSLEAY_SRC}

SRCS+=		asn1octetstream.c

.include <bsd.prog.mk>
