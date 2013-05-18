# $MirOS: src/sys/arch/i386/stand/Makefile,v 1.16 2009/01/17 11:50:48 tg Exp $
# $OpenBSD: Makefile,v 1.15 2007/11/25 18:25:31 deraadt Exp $

.if ${MACHINE_ARCH} == "i386"
  SUBDIR+=	etc
  SUBDIR+=	libsa
  SUBDIR+=	bootxx
  SUBDIR+=	bootxx_ustarfs
  SUBDIR+=	mbr
  SUBDIR+=	fdboot
.endif
.if make(obj) || make(clean) || make(cleandir)
  SUBDIR+=	liveboot
.endif
  SUBDIR+=	boot
  SUBDIR+=	installboot

TEST_DEVS= fd0 svnd0 svnd1

.for _i in ${TEST_DEVS}
test-${_i}:
	${SUDO} mount /dev/${_i}a /mnt
	${SUDO} cp /usr/mdec/boot /mnt
	${SUDO} /usr/mdec/installboot -vh2 -s18 /mnt/boot /usr/mdec/bootxx ${_i}
	${SUDO} umount /mnt

zero-${_i}:
	${SUDO} dd if=/dev/zero of=/dev/r${_i}a count=144 bs=10240

prep-${_i}:
	${SUDO} disklabel -rw ${_i} floppy
#	${SUDO} newfs -O 0 -m 0 -o space -i 3000 -c 80 /dev/r${_i}a
	${SUDO} newfs -O -m 0 -o space -i 3000 -c 80 /dev/r${_i}a
.endfor

prereq: _SUBDIRUSE

.include <bsd.subdir.mk>
