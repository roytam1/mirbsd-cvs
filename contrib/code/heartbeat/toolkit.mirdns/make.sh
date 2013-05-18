#!/bin/mksh
# $MirOS: contrib/code/heartbeat/toolkit.mirdns/make.sh,v 1.2 2005/05/25 23:50:30 tg Exp $
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
# Call 'make' in my own directory. 50 times, if it breaks.
# This script must be chmod'd +x to work.


# Just in case...
export PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/bin

# Do it!
cd $(dirname $0)
F=${1:-data.cdb}
[[ -n $1 ]] && shift

let i=50
while (( i > 0 )); do
	if make $F $MFLAGS "$@"; then
		exit 0
	fi
	let i-=1
	sleep 3
done
