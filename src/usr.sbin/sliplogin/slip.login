#!/bin/mksh
# $MirSecuCron$
# $MirOS: src/usr.sbin/sliplogin/slip.login,v 1.2 2005/07/07 13:40:08 tg Exp $
# $NetBSD: slip.login,v 1.3 1994/06/30 07:50:26 cgd Exp $
# @(#)slip.login	5.1 (Berkeley) 7/1/90

#
# generic login file for a slip line.  sliplogin invokes this with
# the parameters:
#      1        2         3        4          5         6     7-n
#   slipunit ttyspeed loginname local-addr remote-addr mask opt-args
#
UNIT=$1
LOCALADDR=$4
REMOTEADDR=$5
NETMASK=$6
shift 6
OPTARGS=$*

/sbin/ifconfig sl${UNIT} inet ${LOCALADDR} ${REMOTEADDR} netmask ${NETMASK} \
    ${OPTARGS}
exit
