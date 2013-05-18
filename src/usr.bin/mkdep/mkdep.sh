#!/bin/mksh
# $MirOS: src/usr.bin/mkdep/mkdep.sh,v 1.5 2005/12/17 05:46:28 tg Exp $
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
# Advertising materials mentioning features or use of this work must
# display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a defect.
#-
# This is loosely based upon material provided by: the University of
# California, Berkeley, and its contributors.


function die
{
	print -u2 mkdep: "$@"
	exit 1
}

# select a suitable C compiler
CC=$(whence -p ${CC:-cc} 2>/dev/null) || CC=$(whence -p cc)
[[ -x $CC ]] || die no compiler found.

# default values
df=.depend
of=
flag_a=0
flag_p=0

# parse mkdep(1) options
while getopts ":af:p" opt; do
	case $opt {
	a)	flag_a=1 ;;
	f)	df="${OPTARG:-.depend}" ;;
	p)	flag_p=1 ;;
	\?)	break ;;
	}
done
shift $((OPTIND - 1))

# check if files given
if (( $# == 0 )); then
	print 'usage: mkdep [-ap] [-f .depend] [cc_flags] file ...'
	exit 1
fi

# check if output file given
set -A parms -- "$@"
let i=0
while (( i < ${#parms[*]} )); do
	if [[ ${parms[i]} = -o ]]; then
		of="${parms[++i]}"
	elif [[ ${parms[i]} = -o* ]]; then
		of="${parms[i]#-o}"
	fi
	let i++
done

# set up temporary work environment
tmp=$(mktemp /tmp/mkdep.XXXXXXXXXX) || exit 1
trap 'rm -f $tmp; trap 2; kill -2 $$' 1 2 3 5 13 15

# process
if [[ -z $of ]]; then
	$CC -D__IN_MKDEP -M "$@"
else
	$CC -D__IN_MKDEP -M "$@" && cat "$of"
fi | if (( flag_p == 0 )); then
	sed -e 's; \./; ;g' >$tmp
else
	sed -e 's;\.o[ ]*:; :;' -e 's; \./; ;g' >$tmp
fi

if [ $? != 0 ]; then
	rm -f $tmp
	die compile failed.
fi

if (( flag_a == 1 )); then
	if ! cat $tmp >>"$df"; then
		rm -f $tmp
		die append failed.
	fi
else
	if ! mv -f $tmp "$df"; then
		rm -f $tmp
		die rename failed.
	fi
fi

rm -f $tmp
exit 0
