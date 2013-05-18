# $MirOS: src/lib/libssl/ssl/Makefile,v 1.12 2006/09/20 23:30:24 tg Exp $
# $OpenBSD: Makefile,v 1.21 2005/11/24 20:49:23 deraadt Exp $

SHLIB_VERSION?=	11.1
LIB=		ssl
DPADD+=		${LIBCRYPTO}
LDADD+=		-lcrypto

SSLEAYDIST=	src

LSSL_SRC=	${.CURDIR}/../${SSLEAYDIST}/ssl

.include <bsd.own.mk>

.if ${MACHINE_ARCH} == "i386"
CPPFLAGS+= -DBN_ASM
.endif

CPPFLAGS+= -DNO_ERR -I${.CURDIR}/../${SSLEAYDIST}

SRCS=	bio_ssl.c s2_clnt.c s3_both.c s3_srvr.c ssl_err2.c ssl_txt.c	\
	t1_srvr.c s23_clnt.c s2_enc.c s3_clnt.c ssl_algs.c ssl_lib.c	\
	s23_lib.c s2_lib.c s3_enc.c ssl_asn1.c ssl_rsa.c	\
	t1_clnt.c s23_meth.c s2_meth.c s3_lib.c ssl_cert.c ssl_sess.c	\
	t1_enc.c s23_pkt.c s2_pkt.c s3_meth.c ssl_ciph.c ssl_stat.c	\
	t1_lib.c s23_srvr.c s2_srvr.c s3_pkt.c ssl_err.c \
	t1_meth.c

HDRS=	ssl.h ssl2.h ssl3.h ssl23.h tls1.h kssl.h

.PATH:	${LSSL_SRC}

includes:
	@test -d ${DESTDIR}/usr/include/openssl || \
	    mkdir ${DESTDIR}/usr/include/openssl
	@cd ${LSSL_SRC}; for i in $(HDRS); do \
		j="cmp -s $$i ${DESTDIR}/usr/include/openssl/$$(basename $$i) \
		    || cp -p $$i ${DESTDIR}/usr/include/openssl/"; \
		echo $$j; \
		eval "$$j"; \
	done

.include <bsd.lib.mk>
