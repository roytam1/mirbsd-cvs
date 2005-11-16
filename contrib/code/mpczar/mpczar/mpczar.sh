#!/bin/mksh
# $MirOS: contrib/code/mpczar/mpczar/mpczar.sh,v 1.5 2005/11/16 21:46:15 tg Exp $
#-
# Copyright (c) 2005
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

function usage
{
	print -u2 "Usage: mpczar [-v] [-I ignore]... [-r dir]... [-o outfile] [file...]"
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

helper=$(readlink -nf $(dirname "$me")/../libexec/mpczar.z)
if [[ ! -x $helper ]]; then
	print -u2 Cannot find helper, aborting...
	exit 1
fi

function whattopack
{
	let i=0
	while (( i < nf )); do
		print -r -- "${files[i++]}"
	done
	(( nd > 0 )) && find "${dirs[@]}" -type f
}

function whattoignore
{
	sed 's!^[\./]*!!' | if [[ ${ignore[0]} = -v ]]; then
		fgrep "${ignore[@]}" | sort
	else
		sort
	fi
}

while getopts "I:o:r:v" c; do
	case $c {
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

[[ $outf != - && $outf != *@(.mcz) ]] && outf=${outf}.mcz

( whattopack | whattoignore | cpio $v -oHv4norm ) |&
exec 3<&p
$helper "$outf" <&3 || rv=2
wait % || rv=1
[[ $rv = 0 || $outf = - ]] || rm -f "$outf"
exit $rv
