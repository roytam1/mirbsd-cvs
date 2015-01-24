# $MirOS: ports/emulators/bochs/Makefile,v 1.4 2009/08/16 10:21:08 bsiegert Exp $
# $OpenBSD: Makefile,v 1.36 2004/05/12 22:40:11 pedro Exp $
# $NetBSD: Makefile,v 1.2 1998/09/22 06:11:36 garbled Exp $

BROKEN=		fails to build

COMMENT=		x86 machine simulator
DISTNAME=		bochs-2.1.1
DASH_VER=		1
CATEGORIES=		emulators
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=bochs/}
HOMEPAGE=		http://bochs.sourceforge.net/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_CXX=		Yes
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--enable-cdrom \
			--enable-fpu \
			--enable-ne2000 \
			--with-nogui \
			--with-term \
			--enable-all-optimizations

FLAVOURS=	debug i386 i486 i686 x86_64 smp smp_4 smp_8 \
		no_x11 no_mmx no_comp no_pci no_debug_readline
FLAVOUR?=

.if ${FLAVOUR:L:Mdebug}
CONFIGURE_ARGS+= --enable-debugger --enable-disasm --enable-x86-debugger
.  if ${FLAVOUR:L:Mno_debug_readline}
CONFIGURE_ARGS+= --enable-readline
.  endif
.endif

USE_CXX=	Yes
.if !${FLAVOUR:L:Mno_x11}
USE_X11=	Yes
CONFIGURE_ARGS+= --with-x11
.endif

.if ${FLAVOUR:L:Mi386}
FLAVOUR+=	no_mmx
CONFIGURE_ARGS+= --enable-cpu-level="3" --disable-mmx
. if ${FLAVOUR:L:Mi486} || ${FLAVOUR:L:Mi686} || ${FLAVOUR:L:Mx86_64}
ERRORS +=	"Fatal: cannot use i486, i686, or x86_64 flavours with i386"
. endif
.endif

.if ${FLAVOUR:L:Mi486}
FLAVOUR+=	no_mmx
CONFIGURE_ARGS+= --enable-cpu-level="4" --disable-mmx
. if ${FLAVOUR:L:Mi386} ||  ${FLAVOUR:L:Mi686} || ${FLAVOUR:L:Mx86_64}
ERRORS +=	"Fatal: cannot use i386, i686, or x86_64 flavours with i486"
. endif
.endif

.if ! ${FLAVOUR:L:Mi386} && ! ${FLAVOUR:L:Mi486} && ! ${FLAVOUR:L:Mi686}
CONFIGURE_ARGS+= --enable-cpu-level="5"
.endif

.if ${FLAVOUR:L:Mi686}
CONFIGURE_ARGS+= --enable-cpu-level="6"
. if ${FLAVOUR:L:Mi386} ||  ${FLAVOUR:L:Mi486}
ERRORS +=	"Fatal: cannot use i386 or i486 flavours with i686"
. endif
.endif

.if ${FLAVOUR:L:Mx86_64}
.  if !${FLAVOUR:L:Mi686}
ERRORS+=	"Fatal: i686 flavour required for x86_64"
.  else
CONFIGURE_ARGS+= --enable-x86-64
.  endif
.else
CONFIGURE_ARGS+= --disable-x86-64
.endif

.if !${FLAVOUR:L:Mno_pci}
CONFIGURE_ARGS+= --enable-pci
.endif

.if ${FLAVOUR:L:Msmp} || ${FLAVOUR:L:Msmp_4} || ${FLAVOUR:L:Msmp_8}
. if ! ${FLAVOUR:L:Mi686}
ERRORS += "Fatal: i686 flavour required for smp"
. endif
. if ${FLAVOUR:L:Msmp_8}
CONFIGURE_ARGS+= --enable-processors=8
. elif ${FLAVOUR:L:Msmp_4}
CONFIGURE_ARGS+= --enable-processors=4
. else
CONFIGURE_ARGS+= --enable-processors=2
. endif
CONFIGURE_ARGS+= --enable-apic
.else
CONFIGURE_ARGS+= --disable-apic
.endif

.if !${FLAVOUR:L:Mno_mmx}
CONFIGURE_ARGS+= --enable-mmx
.endif

.if !${FLAVOUR:L:Mno_comp}
CONFIGURE_ARGS+= --enable-compressed-hd
.endif

post-extract:
	cd ${WRKSRC:Q} && exec ${MKSH} ${.CURDIR}/patches/unfree__fontinstall

post-configure:
	@sed -e 's@!!PREFIX!!@${PREFIX}@' \
	    <${WRKSRC}/.bochsrc >${WRKSRC}/bochsrc

NO_REGRESS=	Yes

.for _ncpu in 2 4 8
BIOS +=	BIOS-bochs-${_ncpu}-processors
.endfor
BIOS +=	BIOS-bochs-latest
BIOS +=	VGABIOS-elpin-2.40 VGABIOS-elpin-LICENSE
BIOS +=	VGABIOS-lgpl-latest VGABIOS-lgpl-README

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/bochs/bios
	${INSTALL_DATA_DIR} ${PREFIX}/share/bochs/doc
	cd ${WRKBUILD}; ${INSTALL_PROGRAM} bochs bximage ${PREFIX}/bin
	cd ${WRKSRC}/bios; ${INSTALL_DATA} ${BIOS} ${PREFIX}/share/bochs/bios
	${INSTALL_MAN} ${WRKSRC}/doc/man/*.1 ${PREFIX}/man/man1
	${INSTALL_MAN} ${WRKSRC}/doc/man/*.5 ${PREFIX}/man/man5
	${INSTALL_DATA} ${WRKSRC}/docs-html/*.html ${PREFIX}/share/bochs/doc
	${INSTALL_DATA} ${WRKSRC}/bochsrc ${PREFIX}/share/bochs

.include <bsd.port.mk>
