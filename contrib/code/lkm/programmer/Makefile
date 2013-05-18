# $MirOS: contrib/code/lkm/programmer/Makefile,v 1.1 2005/11/17 12:31:00 tg Exp $
#-
# Sample LKM of type CDEV which can be opened and closed (currently,
# it ignores the device minor - the script uses minor 1), and on all
# defined operations (read, write, ioctl) returns ENOCOFFEE.

LKM=		programmer
SRCS=		lkm_intf.c
NOMAN=		Yes

.include <bsd.lkm.mk>
