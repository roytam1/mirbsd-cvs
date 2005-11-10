#!/bin/ksh
# $MirOS: contrib/code/mirmake/dist/contrib/mktemp.sh,v 1.3 2005/09/18 21:01:46 tg Exp $
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
# *INSECURE* mktemp(1) replacement. DO NOT USE. Needs pdksh.

# Globals

set -A chars 0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p q r s \
    t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V W X Y Z

let RAN=$$
me=${0##*/}

# Functions

function usage
{
	(( q == 1 )) || \
	    print -u2 "Syntax: $me [-dqtu] [-p directory] [template]"
	exit 1
}

function getrndc
{
	let RAN+=RANDOM
	print -n ${chars[RAN % ${#chars[*]}]}
	let RAN++
}

function getrnd
{
	let x=$1
	while (( x > 0 )); do
		getrndc
		let --x
	done
}

# main

let d=0
let q=0
let t=0
let u=0
p=/tmp
while getopts "dp:qtu" opt; do
	case $opt {
	d)	let d=1 ;;
	p)	let t=1
		p="$OPTARG" ;;
	q)	let q=1 ;;
	t)	let t=1 ;;
	u)	let u=1 ;;
	\?)	usage ;;
	}
done
shift $((OPTIND - 1))

case $# {
1)	template=$1 ;;
0)	let t=1
	template=tmp.XXXXXXXXXX ;;
*)	usage ;;
}

if (( t == 1 )); then
	if [[ $template = */* ]]; then
		(( q == 1 )) || print -u2 "$me: template must not" \
		    "contain directory separators in -t mode"
		exit 1
	fi
	[[ -n $TMPDIR ]] && p=$TMPDIR
	while [[ $p = */ ]]; do
		p=${p%/}
	done
	template=$p/$template
fi

saveumask=$(umask)
umask 077
let numx=0
while [[ $template != ${template%X} ]]; do
	let numx++
	template=${template%X}
done

let gotit=0
while (( gotit == 0 )); do
	n=${template}$(getrnd $numx)
	[[ -e $n ]] && continue

	if (( d == 1 )); then
		if /bin/mkdir -pm 0700 "$n" 2>/dev/null; then
			if [[ -d $n && -O $n ]]; then
				let gotit=1
				(( u == 1 )) && /bin/rmdir "$n"
			fi
		fi
	else
		if (print -n >"$n") 2>/dev/null; then
			if [[ -f $n && -O $n ]]; then
				let gotit=1
				(( u == 1 )) && /bin/rm -f "$n"
			fi
		fi
	fi
done
print -r -- "$n"
exit 0
