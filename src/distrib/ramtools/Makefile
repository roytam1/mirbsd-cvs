# $MirOS: src/distrib/ramtools/Makefile,v 1.1 2006/05/15 19:20:15 tg Exp $
#-
# Tools necessary to be compiled differently for
# all ramdiscs (floppy, small and big ones)

  SUBDIR+=	init
.if ${MACHINE} == "i386"
  SUBDIR+=	less
  SUBDIR+=	ppp
  SUBDIR+=	sshd
.endif

.include <bsd.subdir.mk>
