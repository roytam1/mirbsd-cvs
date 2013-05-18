# $MirOS: src/sys/arch/i386/stand/ldsec/Makefile,v 1.2 2006/06/15 18:25:16 tg Exp $

SADIR=		${.CURDIR}/..

PROG=		bootxx
SRCS+=		ldsec.S
NOMAN=		Yes
INSTALL_STRIP=	# set to empty value
LDFLAGS=	-nostdlib -Ttext 0 -N -x -Bstatic
CPPFLAGS+=	${DEBUGFLAGS}

${PROG}: $(OBJS) $(DPADD)
	$(LD) $(LDFLAGS) -o $(PROG) $(OBJS) $(LDADD)
	@size $(PROG)

disasm: ${PROG}
	objcopy -O binary ${PROG} ${.OBJDIR}/.tmp; \
	ndisasm -b 16 ${.OBJDIR}/.tmp >${.CURDIR}/disasm

CLEANFILES+=	.tmp ${.CURDIR}/disasm

.include <bsd.prog.mk>
