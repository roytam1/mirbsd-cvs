# $MirOS: contrib/code/heartbeat/toolkit.mirdns/Makefile,v 1.2 2005/05/25 23:50:30 tg Exp $
#-
# Copyright (c) 2004
#	Thorsten "mirabile" Glaser <tg@66h.42h.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# All advertising materials mentioning features or use of this soft-
# ware must display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a nontrivial bug.
#-
# Use "make.sh" to call this file, don't run (bsd)make directly.
# make.sh sets up the correct $PATH

.if exists(Makefile.inc)
.  include "Makefile.inc"
.endif

SHELL=	/bin/mksh
SERVER=	http://users.mirsolutions.de/~tg/.DNS/
TDNS?=	/service/tinymaster
HBCL?=	/service/mirdns

all: data.cdb

data: tdata ipscript
	${SHELL} ${.CURDIR}/ipscript <tdata >data

data.cdb: data
	tinydns-data

editdata:
	co -l tdata
	${EDITOR} tdata
	ci -u tdata

ipscript::
	${SHELL} ${.CURDIR}/mkscript.sh >$@

ip.tun0::
	ifconfig tun0 | grep "inet " | while read a b c; do \
		echo $$b; done >ip.tmp
	echo 0.0.0.0 >>ip.tmp
	head -n 1 <ip.tmp >ip.tun0
	rm -f ip.tmp

dialin: service
.ifdef KILLHBCL
	svc -u ${HBCL}
.endif

dialout:
.ifdef NAMESERVER
	svc -d ${TDNS}
.endif
.ifdef KILLHBCL
	svc -d ${HBCL}
.endif

.ifdef NAMESERVER
dialin-local: dialin all

service: ip.tun0
	@svc -d ${TDNS} >/dev/null 2>&1
	cat ip.tun0 >${TDNS}/env/IP
	svc -u ${TDNS}
.else
service:
.endif

.ifdef MASTER
tdata,v.gz: tdata,v
	gzip -9c tdata,v >tdata,v.gz
	cat tdata,v.gz >~tg/pub/.DNS/tdata,v.gz

zip:	tdata,v.gz
	@rm tdata,v.gz

fetch:
	# Nothing here so far...
.else
fetch:
	@rm -f tdata,v.gz
	ftp ${SERVER}tdata,v.gz || wget ${SERVER}tdata,v.gz
	test ! -e tdata,v.gz || rm -f tdata,v
	test ! -e tdata,v.gz || test -e tdata,v || gzip -d tdata,v.gz
.endif

extract: fetch
	@co -u tdata,v

.PHONY:	all editdata dialin dialout dialin-local service zip fetch extract
