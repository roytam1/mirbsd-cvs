# $MirOS: src/usr.bin/kdump/Makefile,v 1.4 2005/11/23 20:38:20 tg Exp $
# $OpenBSD: Makefile,v 1.8 2003/07/02 20:54:17 deraadt Exp $

PROG=		kdump
CPPFLAGS+=	-I${.CURDIR}/../ktrace -I${.CURDIR}/../../sys
SRCS=		kdump.c ioctl.c subr.c
.PATH:		${.CURDIR}/../ktrace
CLEANFILES+=	ioctl.c

ioctl.c: ${.CURDIR}/mkioctls
	CC="${CC}" DESTDIR="${DESTDIR}" ${SHELL} ${.CURDIR}/mkioctls \
	    ${DESTDIR}/usr/include/sys/ioctl.h \
	    ${DESTDIR}/usr/include/sys/ioctl_compat.h \
	    ${DESTDIR}/usr/include/crypto/cryptodev.h \
	    ${DESTDIR}/usr/include/dev/biovar.h \
	    ${DESTDIR}/usr/include/dev/ccdvar.h \
	    ${DESTDIR}/usr/include/dev/ramdisk.h \
	    ${DESTDIR}/usr/include/dev/rndioctl.h \
	    ${DESTDIR}/usr/include/dev/systrace.h \
	    ${DESTDIR}/usr/include/dev/wscons/wsconsio.h \
	    ${DESTDIR}/usr/include/dev/vndioctl.h \
	    ${DESTDIR}/usr/include/net/bpf.h \
	    ${DESTDIR}/usr/include/net/if_ieee80211.h \
	    ${DESTDIR}/usr/include/net/if_ppp.h \
	    ${DESTDIR}/usr/include/net/if_pppoe.h \
	    ${DESTDIR}/usr/include/net/if_tun.h \
	    ${DESTDIR}/usr/include/net/pfvar.h \
	    ${DESTDIR}/usr/include/netinet6/in6_var.h \
	    ${DESTDIR}/usr/include/sys/agpio.h \
	    ${DESTDIR}/usr/include/sys/ataio.h \
	    ${DESTDIR}/usr/include/sys/audioio.h \
	    ${DESTDIR}/usr/include/sys/cdio.h \
	    ${DESTDIR}/usr/include/sys/chio.h \
	    ${DESTDIR}/usr/include/sys/dkio.h \
	    ${DESTDIR}/usr/include/sys/filio.h \
	    ${DESTDIR}/usr/include/sys/midiio.h \
	    ${DESTDIR}/usr/include/sys/mtio.h \
	    ${DESTDIR}/usr/include/sys/pciio.h \
	    ${DESTDIR}/usr/include/sys/radioio.h \
	    ${DESTDIR}/usr/include/sys/scanio.h \
	    ${DESTDIR}/usr/include/sys/scsiio.h \
	    ${DESTDIR}/usr/include/sys/sockio.h \
	    >$@

.include <bsd.prog.mk>
