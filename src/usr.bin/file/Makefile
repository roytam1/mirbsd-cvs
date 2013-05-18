# $MirOS: src/usr.bin/file/Makefile,v 1.4 2007/07/10 14:22:35 tg Exp $
# $OpenBSD: Makefile,v 1.10 2004/05/19 02:32:35 tedu Exp $

MAGIC=		/etc/magic
MAGICOWN=	${BINOWN}
MAGICGRP=	${CONFGRP}
MAGICMODE=	${NONBINMODE}

PROG=		file
SRCS=		file.c apprentice.c fsmagic.c softmagic.c ascmagic.c is_tar.c \
		print.c compress.c readelf.c magic.c funcs.c
CPPFLAGS+=	-DMAGIC='"$(MAGIC)"' -DUSE_UTIMES -DHAVE_CONFIG_H
CPPFLAGS+=	-DHAVE_STDINT_H
MAN=		file.1 magic.5

CLEANFILES+=	magic
all:		file magic

MAGFILES=	$(.CURDIR)/magdir/Localstuff \
		$(.CURDIR)/magdir/OpenBSD \
		$(.CURDIR)/magdir/[0-9a-z]*

magic: $(.CURDIR)/magdir/Header $(MAGFILES)
	for i in $(MAGFILES); do \
		echo; \
		cat "$$i"; \
	done | cat $(.CURDIR)/magdir/Header - >$@

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o $(MAGICOWN) -g $(MAGICGRP) \
	    -m $(MAGICMODE) magic $(DESTDIR)$(MAGIC)

.include <bsd.prog.mk>
