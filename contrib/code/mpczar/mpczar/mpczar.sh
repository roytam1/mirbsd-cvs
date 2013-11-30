#!/bin/mksh
# $MirOS: contrib/code/mpczar/mpczar/mpczar.sh,v 1.12 2008/11/01 21:28:54 tg Exp $
#-
# Copyright (c) 2005, 2006, 2013
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

function usage {
	print -u2 "Usage: mpczar [-Cv] [-I ignore]... [-r dir]... [-o outfile] [file...]"
	exit 1
}

set -A ignore no
let ni=1
set -A dirs
let nd=0
set -A files
let nf=0

v=
me=$0
outf=-
rv=0
fmt=sv4crc

helper=$(dirname "$(realpath "$me")/../libexec/mpczar.z")
if [[ ! -x $helper ]]; then
	print -u2 Cannot find helper, aborting...
	exit 1
fi

function whattopack {
	let i=0
	while (( i < nf )); do
		print -r -- "${files[i++]}"
	done
	(( nd > 0 )) && find "${dirs[@]}" -type f
}

function whattoignore {
	if [[ ${ignore[0]} = -v ]]; then
		fgrep "${ignore[@]}" | sort
	else
		sort
	fi | sed 's!^\(\./\)*!!'
}

while getopts "CI:o:r:v" c; do
	case $c {
	(C)	fmt=cpio
		;;
	(I)	(( ni == 1 )) && ignore[0]=-v
		ignore[ni++]=-e
		ignore[ni++]=$OPTARG
		;;
	(o)	outf=$OPTARG
		;;
	(r)	dirs[nd++]=$OPTARG
		;;
	(v)	v=-v
		;;
	(*)	usage
		;;
	}
done
shift $((OPTIND - 1))

while [ $# -gt 0 ]; do
	files[nf++]=$1
	shift
done

(( (nf == 0) && (nd == 0) )) && usage

[[ $outf != - && $outf != *.mcz ]] && outf=$outf.mcz

( whattopack | whattoignore | cpio $v -oC512 -H$fmt -M0x0F ) |&
exec 3<&p
"$helper" "$outf" <&3 || rv=2
wait % || rv=1
[[ $rv = 0 || $outf = - ]] || rm -f "$outf"
exit $rv
