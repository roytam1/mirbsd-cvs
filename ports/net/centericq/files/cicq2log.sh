#!/usr/bin/env mksh
# $MirOS: src/share/misc/licence.template,v 1.24 2008/04/22 11:43:31 tg Rel $
#-
# Copyright (c) 2007
#	Thorsten Glaser <tg@mirbsd.de>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
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
# convert a centericq format log file to something IRC-like readable

if [[ $1 = -a ]]; then
	sep='|'
	shift
else
	sep='⎜'
fi

if [[ -z $1 || -z $2 ]]; then
	print "syntax: $0 [-a] <othernick> <mynick> [<logfile>]"
	exit 1
fi

in="<$1> "
sin=$(printf "%${#in}s" " ")
out="<$2> "
sin=$(printf "%${#out}s" " ")
nl='
'
file=$3
if [[ -n $file && $file != - ]]; then
	[[ -f $file && -s $file ]] || filex=~/.centericq/$file
	[[ -f $file && -s $file ]] || file=${file}/history
	[[ -f $file && -s $file ]] || file=${filex}/history
	if ! [[ -f $file && -s $file ]]; then
		print -u2 warning: cannot open "'$3'", using stdin
		file=
	fi
fi
[[ -n $file ]] || file=-

status=0
if [[ $file = - ]]; then
	pipe=
else
	pipe=-p
	cat "$file" |&
fi
while IFS= read $pipe -r line; do
	case $status {
	(0)	if [[ $line = IN ]]; then
			d=$in
			s=$sin
			status=1
		elif [[ $line = OUT ]]; then
			d=$out
			s=$sout
			status=1
		fi
		;;
	(1)	[[ $line = MSG ]] && status=2
		;;
	(2)	ts=$line
		status=3
		;;
	(3)	status=4
		lbuf=
		;;
	(4)	if [[ $line = '' ]]; then
			print -r -- "$lbuf"
			status=0
		elif [[ -z $lbuf ]]; then
			lbuf="$(date -r $ts +%H:%M:%S)$sep$d$line"
		else
			lbuf="$lbuf$nl        $sep$s$line"
		fi
		;;
	}
done
print -r -- "$lbuf"
exit 0
