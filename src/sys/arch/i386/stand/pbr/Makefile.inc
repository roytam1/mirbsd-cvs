# $MirOS$

SADIR=		${.CURDIR}/../..

PROG?=		pbr
SRCS+=		pbr.S

.PATH:		${.CURDIR}/..

NOMAN?=		Yes
INSTALL_STRIP=	# set to empty value
LDFLAGS=	-nostdlib -Ttext 0 -N -x -Bstatic
CPPFLAGS+=	${DEBUGFLAGS}
INSTALL_BIN?=	No

${PROG}: $(OBJS) $(DPADD)
	$(LD) $(LDFLAGS) -o $(PROG) $(OBJS) $(LDADD)
	@size $(PROG)
.if ${INSTALL_BIN:L} == "yes"
	@if [ -x ${.OBJDIR}/${PROG} ]; then \
		objcopy -O binary ${PROG} ${.OBJDIR}/.tmp; \
		mv -f ${.OBJDIR}/.tmp ${.OBJDIR}/${PROG}; \
		ls -l ${.OBJDIR}/${PROG}; \
	fi
.endif

disasm: ${PROG}
.if ${INSTALL_BIN:L} != "yes"
	objcopy -O binary ${PROG} ${.OBJDIR}/.tmp; \
	ndisasm -b 16 ${.OBJDIR}/.tmp >${.CURDIR}/disasm
.else
	ndisasm -b 16 ${PROG} >${.CURDIR}/disasm
.endif

CLEANFILES+=	.tmp ${.CURDIR}/disasm

.include "../Makefile.inc"
