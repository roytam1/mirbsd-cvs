# $MirOS: src/lib/libkeynote/Makefile,v 1.4 2007/04/28 00:12:44 tg Exp $
# $OpenBSD: Makefile,v 1.15 2004/06/25 05:06:49 msf Exp $

LIB=	keynote
MAN=	keynote.3 keynote.4 keynote.5
MLINKS=	keynote.3 kn_init.3 keynote.3 kn_add_assertion.3 \
        keynote.3 kn_remove_assertion.3 keynote.3 kn_add_action.3 \
        keynote.3 kn_remove_action.3 keynote.3 kn_add_authorizer.3 \
        keynote.3 kn_remove_authorizer.3 keynote.3 kn_do_query.3 \
        keynote.3 kn_get_failed.3 keynote.3 kn_cleanup_action_environment.3 \
        keynote.3 kn_close.3 keynote.3 kn_query.3 keynote.3 \
        kn_read_asserts.3 keynote.3 kn_keycompare.3 keynote.3 \
        kn_get_authorizer.3 keynote.3 kn_get_licensees.3 keynote.3 \
        kn_encode_base64.3 keynote.3 kn_decode_base64.3 keynote.3 \
        kn_encode_hex.3 keynote.3 kn_decode_hex.3 keynote.3 \
        kn_encode_key.3 keynote.3 kn_decode_key.3 keynote.3 \
        kn_sign_assertion.3 keynote.3 kn_verify_assertion.3 \
	keynote.3 kn_free_key.3 keynote.3 kn_get_string.3
NOPIC=		yes
.include <bsd.own.mk>
COPTS+=		-Wall
CPPFLAGS+=	-I.
LFLAGS=		-Cr -Pkn -s -i
YFLAGS=		-d -p kn -b k

HDRS=	keynote.h
SRCS=	k.tab.c lex.kn.c environment.c parse_assertion.c signature.c auxil.c \
	base64.c

CLEANFILES+=	k.tab.c k.tab.h lex.kn.c

k.tab.c: keynote.y keynote.h signature.h
	${YACC.y} ${.CURDIR}/keynote.y

lex.kn.c: keynote.l keynote.y keynote.h assertion.h signature.h
	${LEX.l} ${.CURDIR}/keynote.l

.include <bsd.lib.mk>
