#!/bin/mksh
# $MirOS: src/scripts/systrace.mk,v 1.7 2008/10/05 16:26:18 tg Exp $
#-
# Copyright (c) 2004, 2005
#	Thorsten Glaser <tg@mirbsd.de>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# Advertising materials mentioning features or use of this work must
# display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.
#-
# Call a program with an appropriate systrace policy
# Syntax:
#  cd ${policydir}; env WRITEDIR="/a:/b:/c" NOWRITEDIR="/usr/obj" \
#    ${SHELL} systrace.mk prog ...
# To call the protected programs:
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
mydir=$(realpath $mydir)

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
