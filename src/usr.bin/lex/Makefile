# $MirOS: src/usr.bin/lex/Makefile,v 1.4 2007/04/28 00:12:48 tg Exp $
# $OpenBSD: Makefile,v 1.9 2003/12/09 12:42:41 jmc Exp $
#
# By default, flex will be configured to generate 8-bit scanners only if the
# -8 flag is given.  If you want it to always generate 8-bit scanners, add
# "-DDEFAULT_CSIZE=256" to CFLAGS.  Note that doing so will double the size
# of all uncompressed scanners.
#
# If on your system you have trouble building flex due to 8-bit character
# problems, remove the -8 from FLEX_FLAGS and the "#define FLEX_8_BIT_CHARS"
# from the beginning of flexdef.h.
#
# To bootstrap lex, cp initscan.c to scan.c and run make.

PROG=		flex
SRCS=		ccl.c dfa.c ecs.c gen.c main.c misc.c nfa.c \
		parse.y scan.l skel.c sym.c tblcmp.c yylex.c
CPPFLAGS+=	-I.
CLEANFILES+=	skel.c
LDADD=		-ll
DPADD=		${LIBL}

LINKS=		${BINDIR}/flex ${BINDIR}/lex \
		${BINDIR}/flex ${BINDIR}/flex++
MLINKS=		flex.1 lex.1 flex.1 flex++.1
HDRS=		FlexLexer.h

# This just gets installed verbatim
.if make(install)
SUBDIR+=	 PSD.doc
.endif

skel.c:	flex.skl mkskel.sh
	${SHELL} ${.CURDIR}/mkskel.sh ${.CURDIR}/flex.skl >$@

includes:
	@cd ${.CURDIR}; for i in ${HDRS}; do \
		if cmp -s "$$i" ${DESTDIR:Q}/usr/include/"$$i"; then \
			print Header ${DESTDIR:Q}/usr/include/"$$i" \
			    is up to date.; \
		else \
			print Header ${DESTDIR:Q}/usr/include/"$$i" \
			    "<-- $$i"; \
			${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} \
			    -m ${NONBINMODE} "$$i" ${DESTDIR}/usr/include/; \
		fi; \
	done

.include <bsd.prog.mk>
