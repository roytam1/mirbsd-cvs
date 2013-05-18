# $MirOS: src/sys/arch/i386/stand/pbr/ffs/Makefile,v 1.1.7.1 2005/03/06 16:33:43 tg Exp $

SADIR=		${.CURDIR}/..

PROG=		ldsec
SRCS+=		ldsec.S
NOMAN=		Yes
INSTALL_STRIP=	# set to empty value
LDFLAGS=	-nostdlib -Ttext 0 -N -x -Bstatic
CPPFLAGS+=	${DEBUGFLAGS}
DEBUGPROGS=	No

${PROG}: $(OBJS) $(DPADD)
	$(LD) $(LDFLAGS) -o $(PROG) $(OBJS) $(LDADD)
	@size $(PROG)

disasm: ${PROG}
	objcopy -O binary ${PROG} ${.OBJDIR}/.tmp; \
	ndisasm -b 16 ${.OBJDIR}/.tmp >${.CURDIR}/disasm

CLEANFILES+=	.tmp ${.CURDIR}/disasm

.include <bsd.prog.mk>
