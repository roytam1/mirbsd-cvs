# $MirOS: src/sys/arch/i386/stand/Makefile,v 1.4 2005/04/29 18:34:57 tg Exp $
# $OpenBSD: Makefile,v 1.12 2004/06/23 00:29:56 tom Exp $

.if ${MACHINE} == "i386"
  SUBDIR+= etc libsa libz mbrldr mbrmgr pbr
.endif
  SUBDIR+= boot installboot
  SUBDIR+= pxeboot

TEST_DEVS= fd0 svnd0 svnd1

.for _i in ${TEST_DEVS}
test-${_i}:
	${SUDO} mount /dev/${_i}a /mnt
	${SUDO} cp /usr/mdec/boot /mnt
	${SUDO} /usr/mdec/installboot -vh2 -s18 \
	    /mnt/boot /usr/mdec/ffspbr ${_i}
	${SUDO} umount /mnt

zero-${_i}:
	${SUDO} dd if=/dev/zero of=/dev/r${_i}a count=144 bs=10240

prep-${_i}:
	${SUDO} disklabel -rw ${_i} floppy
	${SUDO} newfs -O -m 0 -o space -i 3000 -c 80 /dev/r${_i}a
.endfor

prereq: _SUBDIRUSE

.include <bsd.subdir.mk>
