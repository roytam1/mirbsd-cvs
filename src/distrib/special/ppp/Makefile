# $MirOS$
# $OpenBSD: Makefile,v 1.25 2002/05/11 00:20:21 espie Exp $

BSDSRCDIR?=	/usr/src
.PATH:	${BSDSRCDIR}/usr.sbin/ppp/ppp

PROG=	ppp
SRCS=	alias.c alias_cuseeme.c alias_db.c alias_ftp.c alias_irc.c \
	alias_nbt.c alias_pptp.c alias_proxy.c alias_smedia.c alias_util.c \
	acf.c arp.c async.c auth.c bundle.c cbcp.c ccp.c chap.c chap_ms.c \
	chat.c command.c datalink.c deflate.c defs.c exec.c filter.c fsm.c \
	hdlc.c iface.c ip.c ipcp.c ipv6cp.c iplist.c lcp.c link.c log.c lqr.c \
	main.c mbuf.c mp.c mppe.c ncp.c ncpaddr.c nat_cmd.c pap.c physical.c \
	pred.c probe.c prompt.c proto.c radius.c radlib.c route.c server.c \
	sig.c slcompress.c systems.c sync.c tcp.c tcpmss.c throughput.c \
	timer.c tty.c tun.c udp.c vjcomp.c i4b.c atm.c
MAN=

CPPFLAGS+=	-DNO_FW_PUNCH -DNONETGRAPH
CPPFLAGS+=	-DLOCALNAT -DLOCALRAD
LDADD+=		-lcrypto -ldes -lutil -lz
DPADD+=		${LIBDES} ${LIBUTIL} ${LIBZ} ${LIBCRYPTO}
CPPFLAGS+=	-I${BSDSRCDIR}/usr.sbin/ppp/ppp

CPPFLAGS+=	-DNOSUID

.include <bsd.prog.mk>
