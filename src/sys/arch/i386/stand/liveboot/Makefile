# $MirOS: src/sys/arch/i386/stand/liveboot/Makefile,v 1.4 2007/03/18 04:46:22 tg Exp $

BOOTSELECT_HOOK=yes
BOOTLDR_PATH=	${.CURDIR}/../boot
NOMAN=		yes

DUALIVE?=	No
.if ${DUALIVE:L} == "yes"
CPPFLAGS+=	-DHAVE_DUALIVE
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
