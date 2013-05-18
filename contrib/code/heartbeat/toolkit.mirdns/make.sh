#!/bin/mksh
# $MirOS: src/share/misc/licence.template,v 1.6 2006/01/24 22:24:02 tg Rel $
#-
# Copyright (c) 2004, 2006
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
# Call 'make' in my own directory. 50 times, if it breaks.
# This script must be chmod'd +x to work.


# Just in case...
export PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/bin:/usr/mpkg/bin

# Do it!
cd $(dirname $0)
F=${1:-all}
[[ -n $1 ]] && shift

let i=50
while (( i > 0 )); do
	if make $F $MFLAGS "$@"; then
		exit 0
	fi
	let i-=1
	sleep 3
done
