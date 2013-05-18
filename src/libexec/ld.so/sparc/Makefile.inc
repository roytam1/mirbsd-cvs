# $MirOS: src/libexec/ld.so/sparc/Makefile.inc,v 1.3 2006/06/30 18:32:50 tg Exp $
# $OpenBSD: Makefile.inc,v 1.2 2002/11/23 19:14:25 drahn Exp $

COPTS+=		-fpic -msoft-float
CPPFLAGS+=	-I${LIBCSRCDIR}/arch/sparc -DSTRONG_SPARC
