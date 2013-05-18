# $MirOS: src/bin/md5/Makefile,v 1.18 2009/11/22 21:11:28 tg Exp $
# $OpenBSD: Makefile,v 1.10 2005/05/24 21:57:47 millert Exp $

PROG=	cksum
MAN=	cksum.1 md5.1 sha1.1 rmd160.1
LINKS=	${BINDIR}/cksum ${BINDIR}/sha1 \
	${BINDIR}/cksum ${BINDIR}/rmd160 \
	${BINDIR}/cksum ${BINDIR}/md5 \
	${BINDIR}/cksum ${BINDIR}/sum
MLINKS= cksum.1 sum.1

.if exists(${.SYSMK}/libmirmake.a)
CPPFLAGS+=	-D_GNU_SOURCE -D_MIRMAKE_DEFNS
LDADD+=		-L${.SYSMK} -lmirmake
.endif

ALGOS=	adler32 cdb md4 md5 oaat oaat1 oaat1s rmd160 sfv sha1 \
	sha256 sha384 sha512 size sum suma sysvsum tiger whirlpool

CLEANFILES+=	${ALGOS} ${ALGOS:=sum}

algos:
.for _lnk in ${ALGOS}
	ln -sf ${PROG} ${_lnk}
	ln -sf ${PROG} ${_lnk}sum
.endfor
	# these don't make any sense
	-rm -f sumsum sysvsumsum

regress: ${PROG}
	./${PROG} -a adler32 -a cdb -a cksum -a md4 -a md5 \
	    -a oaat -a oaat1 -a oaat1s -a rmd160 -a sfv \
	    -a sha1 -a sha256 -a sha384 -a sha512 -a size \
	    -a sum -a suma -a sysvsum -a tiger -a whirlpool \
	    -x | diff -u ${.CURDIR}/testres -

.include <bsd.prog.mk>
