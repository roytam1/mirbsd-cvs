# $MirOS: ports/x11/p5-Gtk/Makefile,v 1.8 2007/05/07 19:48:39 bsiegert Exp $
# $OpenBSD: Makefile,v 1.15 2004/06/26 23:09:15 jcs Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=	set of modules to use Gtk+ libraries from Perl
VERSION=	0.7008
DISTNAME=	Gtk-Perl-${VERSION}
PKGNAME=	p5-Gtk-${VERSION}-0
CATEGORIES=	x11 devel perl5

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

HOMEPAGE=	http://www.gtkperl.org/
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Gtk/}

USE_X11=	Yes
USE_CXX=	Yes # depends on libungif, which uses CXX

LIB_DEPENDS=	gtk.1.2,glib.1.2::x11/gtk+1 \
		gdk_pixbuf.2::graphics/gdk-pixbuf \
		gdk_imlib.19::graphics/imlib
RUN_DEPENDS=	:p5-XML-Parser-*:textproc/p5-XML-Parser \
		:p5-XML-Writer-*:textproc/p5-XML-Writer
BUILD_DEPENDS=	${RUN_DEPENDS}

CONFIGURE_STYLE= perl
CONFIGURE_ARGS=	--without-gtkhtml --without-gtkxmhtml \
		--without-gnomeprint --without-applets --without-glade

MAKE_FLAGS=	INST_MAN3DIR="../blib/man3p"

PERLDIR=	"${DESTDIR}/${PREFIX}/libdata/perl5/site_perl"
FAKE_FLAGS=	${MAKE_FLAGS} \
		INSTALLPRIVLIB="${PERLDIR}" \
		INSTALLARCHLIB="${PERLDIR}/${MACHINE_ARCH}-openbsd" \
		INSTALLSITELIB="${PERLDIR}" \
		INSTALLSITEARCH="${PERLDIR}/${MACHINE_ARCH}-openbsd" \
		INSTALLMAN3DIR="${DESTDIR}/${PREFIX}/man/man3p" \
		INSTALLSITEMAN3DIR="${DESTDIR}/${PREFIX}/man/man3p"

FLAVOURS=	gtkglarea #gnome #XXX needs gnome2?
FLAVOUR?=	

.if ${FLAVOUR:L:Mgtkglarea}
LIB_DEPENDS+=	gtkgl.1.2::x11/gtkglarea
CONFIGURE_ARGS+= --with-gtkglarea-force
SED_PLIST+=     |sed -e '/^!%%gtkglarea%%/r${PKGDIR}/PFRAG.gtkglarea' -e '//d'
.else
CONFIGURE_ARGS+= --without-gtkglarea
SED_PLIST+=     |sed -e '/^!%%gtkglarea%%/d'
.endif

.if ${FLAVOUR:L:Mgnome}
LIB_DEPENDS+=	gnome.1::x11/gnome/libs
CONFIGURE_ARGS+= --with-gnome
SED_PLIST+=     |sed -e '/^!%%gnome%%/r${PKGDIR}/PFRAG.gnome' -e '//d'
.else
CONFIGURE_ARGS+= --without-gnome
SED_PLIST+=     |sed -e '/^!%%gnome%%/d'
.endif

.include <bsd.port.mk>
