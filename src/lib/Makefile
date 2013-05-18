# $MirOS: src/lib/Makefile,v 1.15 2008/10/16 21:59:45 tg Exp $
# $OpenBSD: Makefile,v 1.49 2003/05/14 01:46:51 hin Exp $
# $NetBSD: Makefile,v 1.20.4.1 1996/06/14 17:22:38 cgd Exp $

.include <bsd.own.mk>

  SUBDIR+= csu
  SUBDIR+= libarch
  SUBDIR+= libc
.if ${NOPIC:L} == "no"
  SUBDIR+= libcitrus_iconv
.endif
  SUBDIR+= libcompat
  SUBDIR+= libdes
  SUBDIR+= libedit		# depends: (test) libotermcap
  SUBDIR+= libevent
  SUBDIR+= libexpat
  SUBDIR+= libform
  SUBDIR+= libkeynote
  SUBDIR+= libkvm		# depends: libz
  SUBDIR+= libl
  SUBDIR+= libm
  SUBDIR+= libmbfun
  SUBDIR+= libmdsup
  SUBDIR+= libmenu
  SUBDIR+= libncurses
  SUBDIR+= libocurses
  SUBDIR+= libossaudio
  SUBDIR+= libpanel
  SUBDIR+= libpcap
  SUBDIR+= libpng		# depends: libm libz
  SUBDIR+= libpthread
  SUBDIR+= libresolv
  SUBDIR+= librpcsvc
  SUBDIR+= libsectok
  SUBDIR+= libskey
  SUBDIR+= libssl		# depends: libz (libssl/ssl) libssl/crypto
  SUBDIR+= libusbhid
  SUBDIR+= libutil
  SUBDIR+= liby
  SUBDIR+= libz
  SUBDIR+= ../gnu/usr.bin/binutils/libiberty

.include <bsd.subdir.mk>
