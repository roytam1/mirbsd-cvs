#!/bin/ksh
# $MirOS$
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
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.
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
