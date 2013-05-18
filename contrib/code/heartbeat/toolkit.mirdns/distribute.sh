#!/bin/mksh
# $MirOS: contrib/code/heartbeat/toolkit.mirdns/distribute.sh,v 1.3 2005/10/07 22:12:33 tg Exp $
#-
# Copyright (c) 2004, 2005
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
# Distribute the 'data.cdb' file just made to the secondaries.
# This script must be chmod'd +x to work.
#
# You need to visudo on the target machine and add a line such as:
#	mirdns	ALL = NOPASSWD: /usr/local/bin/svc -t /service/dnscache
# for the update process to work.


# Just in case...
export PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/bin

tinydns=$(cd $(dirname $0); pwd)
cd $tinydns

if [[ -z $1 ]]; then
	# master distributor
	for m in N-*; do
		if [[ -e $m ]]; then
			$0 $m >/dev/null 2>&1 &
		else
			exit 0
		fi
	done
	exit 0
else
	nice scp -BCpq -i $tinydns/id_rsa -F $tinydns/ssh_config \
	    $tinydns/data.cdb mirdns@$1:$tinydns/data.cdb && \
	    nice ssh -T -i $tinydns/id_rsa -F $tinydns/ssh_config \
	    -l mirdns $1 "sudo svc -t /service/dnscache"
fi
