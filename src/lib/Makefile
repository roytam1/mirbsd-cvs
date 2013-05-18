# $MirOS: src/lib/Makefile,v 1.11 2006/10/28 19:22:10 tg Exp $
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
  SUBDIR+= libedit		# depends: libtermcap (for test programme)
  SUBDIR+= libevent
  SUBDIR+= libexpat
  SUBDIR+= libform
  SUBDIR+= libkeynote
  SUBDIR+= libkvm		# depends: libz
  SUBDIR+= libl
  SUBDIR+= libm
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
  SUBDIR+= libssl		# depends: libz libssl/libcrypto
  SUBDIR+= libusbhid
  SUBDIR+= libutil
  SUBDIR+= liby
  SUBDIR+= libz
  SUBDIR+= ../gnu/usr.bin/binutils/libiberty

.include <bsd.subdir.mk>
