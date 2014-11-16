#!/bin/mksh
# $MirOS: contrib/code/heartbeat/toolkit.mirdns/distribute.sh,v 1.10 2013/11/30 13:45:18 tg Exp $
#-
# Copyright (c) 2004, 2005, 2006, 2013
#	Thorsten Glaser <tg@mirbsd.de>
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
# Distribute the zone information from ./data (generated from tdata)
# to the djbdns secondaries (using scp) and trigger a NOTIFY request
# for each domain handled to the axfr secondaries.
# This script must be chmod'd +x to work.
#
# You need to visudo on the target machine and add a line such as:
#	mirdns	ALL = NOPASSWD: /service/tinymaster/.etc/svc -t /service/dnscache
# and create a symlink for the update process to work.


# Just in case...
export PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/bin:/usr/mpkg/bin

tinydns=$(realpath "$0/..")
cd $tinydns

if [[ -z $1 ]]; then
	# master distributor
	for m in N-*; do
		[[ -e $m ]] || break
		${SHELL:-/bin/mksh} $0 $m >/dev/null 2>&1 &
	done
	let rv=0
	[[ -s Z-zones && -s Z-slaves ]] && for m in $(<Z-zones); do
		zonenotify $m $(<Z-slaves) || rv=1
	done
	exit $rv
else
	nice scp ${2:--BCpq} -i $tinydns/id_rsa -F $tinydns/ssh_config \
	    $tinydns/data mirdns@$1:$tinydns/data && \
	    nice ssh -T -i $tinydns/id_rsa -F $tinydns/ssh_config \
	    -l mirdns $1 "cd $tinydns; /usr/mpkg/bin/tinydns-data; \
		sudo ${tinydns%root}.etc/svc -t /service/dnscache"
fi
