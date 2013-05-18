# $MirOS$
# $NetBSD: Makefile.inc,v 1.1.1.1 2001/01/06 13:00:10 martin Exp $

.ifndef _MODSRC_USR_SBIN_ISDN_MAKEFILE_INC
_MODSRC_USR_SBIN_ISDN_MAKEFILE_INC=1

.if exists(${.CURDIR}/../../Makefile.inc)
.  include "${.CURDIR}/../../Makefile.inc"
.endif

# optional build configuration:
# I4B_WITHOUT_CURSES=1	# don't compile curses into the daemon
I4B_EXTERNAL_MONITOR=1	# enable local and remote monitoring of the daemon
# I4B_NOTCPIP_MONITOR=1	# for the security concious: isdn monitoring only via
#			# local domain socket, no TCP socket supported

.endif
