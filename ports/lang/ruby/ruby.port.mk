# $MirOS: ports/lang/ruby/ruby.port.mk,v 1.3 2007/04/07 15:00:47 bsiegert Exp $
# $OpenBSD: ruby.port.mk,v 1.4 2004/02/20 22:52:58 couderc Exp $

# ruby module

LIB_DEPENDS+=ruby::lang/ruby

# location of ruby libraries
MODRUBY_LIBDIR=		${LOCALBASE}/lib/ruby

# common directories for ruby extensions
# used to create docs and examples install path
MODRUBY_DOCDIR=		${PREFIX}/share/doc/ruby
MODRUBY_EXAMPLEDIR=	${PREFIX}/share/examples/ruby

CONFIGURE_STYLE?=	simple
CONFIGURE_SCRIPT?=	${LOCALBASE}/bin/ruby extconf.rb

REV=			1.8
SUB=			${MACHINE_ARCH}-${OStype:L}${OSREV}
SUBST_VARS+=		SUB REV

