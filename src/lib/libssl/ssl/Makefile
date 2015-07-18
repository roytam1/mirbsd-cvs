# $MirOS: src/lib/libssl/ssl/Makefile,v 1.25 2014/11/29 22:18:32 tg Exp $
# $OpenBSD: Makefile,v 1.21 2005/11/24 20:49:23 deraadt Exp $

SHLIB_VERSION?=	14.1
LIB=		ssl
DPADD+=		${LIBCRYPTO}
LDADD+=		-lcrypto
LDFLAGS+=	-Wl,-Bsymbolic

SSLEAYDIST=	src

LSSL_SRC=	${.CURDIR}/../${SSLEAYDIST}/ssl

.include <bsd.own.mk>

CPPFLAGS+=	-I${.CURDIR}/../${SSLEAYDIST}

SRCS=	bio_ssl.c s23_pkt.c s23_srvr.c s3_both.c s3_clnt.c s3_enc.c \
	s3_lib.c s3_pkt.c s3_srvr.c ssl_algs.c ssl_asn1.c ssl_cert.c \
	ssl_ciph.c ssl_err.c ssl_err2.c ssl_lib.c ssl_rsa.c ssl_sess.c \
	ssl_stat.c ssl_txt.c t1_clnt.c t1_enc.c t1_lib.c t1_meth.c t1_srvr.c

HDRS=	ssl.h ssl2.h ssl3.h ssl23.h tls1.h
HDRSRC=	${LSSL_SRC}
HDRDST=	${DESTDIR}/usr/include/openssl

.PATH:	${LSSL_SRC}

prereq:

.include <bsd.lib.mk>
