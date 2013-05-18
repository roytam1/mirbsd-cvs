# $MirOS: src/sys/arch/i386/stand/liveboot/Makefile,v 1.8 2009/02/01 10:47:36 tg Exp $

BOOTSELECT_HOOK=yes
BOOTLDR_PATH=	${.CURDIR}/../boot
NOMAN=		yes

BSD4GRML?=	No
.if ${BSD4GRML:L} == "yes"
DUALIVE=	No
GRML=		No
CPPFLAGS+=	-DFORGRML
MBSD_PREFIX=	/boot/mirbsd
NOMAN=		No
.endif

DUALIVE?=	No
.if ${DUALIVE:L} == "yes"
CPPFLAGS+=	-DHAVE_DUALIVE
.endif

GRML?=		No
.if ${GRML:L} == "yes"
CPPFLAGS+=	-DHAVE_GRML
.endif

CPPFLAGS+=	-Dmbsd_major=\"${OSrev:Q}\"
.if ${OSrpl} < 128
CPPFLAGS+=	-Dmbsd_type=\"-beta\"
.elif ${OSrpl} == 128
CPPFLAGS+=	-Dmbsd_type=\"\"
.elif ${OSrpl} == 130
CPPFLAGS+=	-Dmbsd_type=\"bis\"
.elif ${OSrpl} == 132
CPPFLAGS+=	-Dmbsd_type=\"ter\"
.elif ${OSrpl} == 134
CPPFLAGS+=	-Dmbsd_type=\"quater\"
.elif ${OSrpl} == 136
CPPFLAGS+=	-Dmbsd_type=\"quinquies\"
.elif ${OSrpl} < 160
CPPFLAGS+=	-Dmbsd_type=\"-stable\"
.else
CPPFLAGS+=	-Dmbsd_type=\"-current\"
.endif

# This doesn't get installed
install:

.PATH: ${BOOTLDR_PATH}
.include "${BOOTLDR_PATH}/Makefile"

.if ${BSD4GRML:L} == "yes"
all: ldbsd.txt

ldbsd.txt: __MANALL
	col -bx <boot.cat8 >$@ || (rm -f $@; exit 1)
.endif

CLEANFILES+=	ldbsd.txt
