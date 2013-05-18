# $MirOS: src/sys/arch/i386/stand/Makefile,v 1.7 2006/04/10 19:10:50 tg Exp $
# $OpenBSD: Makefile,v 1.12 2004/06/23 00:29:56 tom Exp $

.if ${MACHINE} == "i386"
  SUBDIR+=	etc libsa libz
  SUBDIR+=	fdboot ldsec liveboot mbrldr mbrmgr
.endif
  SUBDIR+=	boot installboot pxeboot

TEST_DEVS= fd0 svnd0 svnd1

.for _i in ${TEST_DEVS}
test-${_i}:
	${SUDO} mount /dev/${_i}a /mnt
	${SUDO} cp /usr/mdec/boot /mnt
	${SUDO} /usr/mdec/installboot -vh2 -s18 /mnt/boot /usr/mdec/ldsec ${_i}
	${SUDO} umount /mnt

zero-${_i}:
	${SUDO} dd if=/dev/zero of=/dev/r${_i}a count=144 bs=10240

prep-${_i}:
	${SUDO} disklabel -rw ${_i} floppy
	${SUDO} newfs -O -m 0 -o space -i 3000 -c 80 /dev/r${_i}a
.endfor

prereq: _SUBDIRUSE

.include <bsd.subdir.mk>
