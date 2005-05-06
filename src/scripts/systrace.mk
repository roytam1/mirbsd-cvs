#!/bin/ksh
# $MirOS: src/scripts/systrace.mk,v 1.1 2005/03/06 16:08:16 tg Exp $
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
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.
#-
# Call a programme with an appropriate systrace policy
# Syntax:
#  cd ${policydir}; env WRITEDIR="/a:/b:/c" NOWRITEDIR="/usr/obj" \
#    ${SHELL} systrace.mk prog ...
# To call the protected programmes:
#  /bin/systrace -e -i -a -f ${policydir}/.policy.mk prog args

[[ -n $WRITEDIR && -n $1 ]] || exit 1
saveIFS="$IFS"
IFS=:
set -o noglob
set -A rwdirs -- $WRITEDIR
set -A rodirs -- $NOWRITEDIR
set +o noglob
IFS="$saveIFS"

set -A progs
let i=0
for prog in "$@"; do
	[[ -x $prog ]] || prog=$(whence -p $prog)
	if [[ -x $prog ]]; then
		progs[i++]="$prog"
	else
		print -u2 "Warning: $prog not executable!"
	fi
done
(( i > 0 )) || exit 1

mydir=${0%/*}
[[ $mydir = $0 ]] && mydir=.
mydir=$(readlink -nf $mydir)

for prog in "${progs[@]}"; do
	sed "s#@@PROG@@#$prog#g" <$mydir/systrace.sed
done >.policy.mk

ed -s .policy.mk |&
set -o noglob
for dir in "${rwdirs[@]}"; do
	print -p '1,$g/@@RW_DIR@@/t.\\\n'"s:@@RW_DIR@@:$dir:g"
done
for dir in "${rodirs[@]}"; do
	print -p '1,$g/@@RO_DIR@@/t.\\\n'"s:@@RO_DIR@@:$dir:g"
done
set +o noglob
print -p "1,\$g/@@R[OW]_DIR@@/d\nwq"

sync
sleep 1
exit 0
