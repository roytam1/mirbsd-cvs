# $MirOS: src/usr.sbin/openssl/Makefile,v 1.5 2005/04/30 22:54:27 tg Exp $
# $OpenBSD: Makefile,v 1.17 2005/04/29 05:42:55 djm Exp $

PROG=		openssl
LDADD=		-lssl -lcrypto
DPADD=		${LIBSSL} ${LIBCRYPTO}

.include <bsd.own.mk>

SSLEAYDIST=	lib/libssl/src
SSLEAY_SRC_TOP=	${BSDSRCDIR}/${SSLEAYDIST}
SSLEAY_SRC=	${SSLEAY_SRC_TOP}/apps

.if ${MACHINE} == "i386"
CPPFLAGS+=	-DL_ENDIAN
.elif ${MACHINE} == "sparc"
CPPFLAGS+=	-DB_ENDIAN
.else
.BEGIN:
	@echo No endianness defined.
	@exit 1
.endif

CPPFLAGS+=	-DMONOLITH -DOPENSSL_NO_IDEA -DTERMIOS -DANSI_SOURCE
CPPFLAGS+=	-I${SSLEAY_SRC_TOP}

SRCS=	verify.c asn1pars.c req.c dgst.c dh.c enc.c passwd.c gendh.c errstr.c \
	pkcs7.c crl2p7.c crl.c ca.c \
	rsa.c dsa.c dsaparam.c \
	x509.c genrsa.c gendsa.c s_server.c s_client.c speed.c \
	s_time.c apps.c s_cb.c s_socket.c version.c sess_id.c \
	app_rand.c ciphers.c nseq.c pkcs12.c pkcs8.c spkac.c smime.c \
	dhparam.c openssl.c rand.c rsautl.c engine.c ocsp.c prime.c

.PATH:	${SSLEAY_SRC}

.include <bsd.prog.mk>
