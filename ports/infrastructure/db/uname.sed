#!/usr/bin/env mksh
# $MirOS: src/share/misc/licence.template,v 1.24 2008/04/22 11:43:31 tg Rel $
#-
# Copyright (c) 2004, 2008
#	Thorsten "mirabilos" Glaser <tg@mirbsd.de>
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
# Fake FreeBSD for MidnightBSD and OpenBSD for MirBSD, to aid broken
# build systems (Schily, Mozilla, ...)

function usage {
	print -u2 'usage: uname [-ailmnprsv]'
	exit 1
}

flag_a=
flag_i=
flag_l=
flag_m=
flag_n=
flag_p=
flag_r=
flag_s=
flag_v=
integer has_one=0

sysname=@@OStype@@
version=@@OScompat@@

while getopts "ailmnprsv" c; do
	case $c {
	(a)
		flag_l=-l
		flag_m=-m
		flag_n=-n
		flag_r=-r
		flag_s=-s
		flag_v=-v
		has_one=1 ;;
	(i|l|m|n|p|r|s|v)
		eval flag_$c=-$c
		has_one=1 ;;
	(*)
		usage ;;
	}
done
shift $((OPTIND - 1))

(( $# )) && usage

(( has_one )) || flag_s=-s
[[ $sysname = MirBSD ]] || flag_l=
[[ $sysname = MidnightBSD ]] || flag_i=

integer rv=0
if [[ -n $flag_n ]]; then
	nodename="$(/usr/bin/uname -n)"
	rv=$?
fi
reststr=
if [[ -n $flag_l$flag_v$flag_m$flag_p$flag_i ]]; then
	reststr="$(/usr/bin/uname $flag_l $flag_v $flag_m $flag_p $flag_i)"
	has_one=$?
	(( rv = rv ? rv : has_one ))
fi

outstr=
sp=
if [[ -n $flag_s ]]; then
	if [[ $sysname = MidnightBSD ]]; then
		outstr=FreeBSD
	elif [[ $sysname = MirBSD ]]; then
		outstr=OpenBSD
	else
		print -u2 "uname: unknown host os '$sysname'"
		exit 1
	fi
	sp=' '
fi
if [[ -n $flag_n ]]; then
	outstr=$outstr$sp$nodename
	sp=' '
fi
if [[ -n $flag_r ]]; then
	outstr=$outstr$sp$version
	sp=' '
fi
[[ -n $reststr ]] && outstr=$outstr$sp$reststr

print -r -- "$outstr"
exit $rv
