# $OpenBSD: ghc.port.mk,v 1.3 2004/04/26 23:48:50 dons Exp $
# Module for Glasgow Haskell Compiler

# Not yet ported to other architectures
# See comments in lang/ghc/Makefile for more information
ONLY_FOR_PLATFORM=	OpenBSD:*:i386 OpenBSD:*:sparc OpenBSD:*:amd64

BUILD_DEPENDS+=	bin/ghc::lang/ghc
RUN_DEPENDS+=	bin/ghc::lang/ghc
