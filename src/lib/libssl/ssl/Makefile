# $MirOS: src/lib/libssl/ssl/Makefile,v 1.20 2014/11/26 20:02:22 tg Exp $
# $OpenBSD: Makefile,v 1.21 2005/11/24 20:49:23 deraadt Exp $

SHLIB_VERSION?=	14.0
LIB=		ssl
DPADD+=		${LIBCRYPTO}
LDADD+=		-lcrypto
LDFLAGS+=	-Wl,-Bsymbolic

SSLEAYDIST=	src

LSSL_SRC=	${.CURDIR}/../${SSLEAYDIST}/ssl

.include <bsd.own.mk>

.if ${MACHINE_ARCH} == "i386"
CPPFLAGS+= -DBN_ASM
.endif

CPPFLAGS+= -DNO_ERR -I${.CURDIR}/../${SSLEAYDIST}

SRCS=	bio_ssl.c s3_both.c s3_srvr.c ssl_err2.c ssl_txt.c	\
	t1_srvr.c s23_clnt.c s3_clnt.c ssl_algs.c ssl_lib.c	\
	s23_lib.c s3_enc.c ssl_asn1.c ssl_rsa.c			\
	t1_clnt.c s23_meth.c s3_lib.c ssl_cert.c ssl_sess.c	\
	t1_enc.c s23_pkt.c s3_meth.c ssl_ciph.c ssl_stat.c	\
	t1_lib.c s23_srvr.c s3_pkt.c ssl_err.c t1_meth.c

HDRS=	ssl.h ssl2.h ssl3.h ssl23.h tls1.h
HDRSRC=	${LSSL_SRC}
HDRDST=	${DESTDIR}/usr/include/openssl

.PATH:	${LSSL_SRC}

prereq:

.include <bsd.lib.mk>
