# $MirOS: src/usr.bin/file/Makefile,v 1.2 2005/03/13 18:32:56 tg Exp $
# $OpenBSD: Makefile,v 1.10 2004/05/19 02:32:35 tedu Exp $

MAGIC=		/etc/magic
MAGICOWN=	${BINOWN}
MAGICGRP=	${CONFGRP}
MAGICMODE=	${NONBINMODE}

PROG=		file
SRCS=		file.c apprentice.c fsmagic.c softmagic.c ascmagic.c is_tar.c \
		print.c compress.c readelf.c magic.c funcs.c
CPPFLAGS+=	-DMAGIC='"$(MAGIC)"' -DUSE_UTIMES -DHAVE_CONFIG_H
MAN=		file.1 magic.5

CLEANFILES+=	magic
all:		file magic

MAGFILES=	$(.CURDIR)/magdir/Header\
		$(.CURDIR)/magdir/Localstuff\
		$(.CURDIR)/magdir/OpenBSD\
		$(.CURDIR)/magdir/[0-9a-z]*

magic: $(MAGFILES)
	cat $(MAGFILES) >$@

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o $(MAGICOWN) -g $(MAGICGRP) \
	    -m $(MAGICMODE) magic $(DESTDIR)$(MAGIC)

.include <bsd.prog.mk>
