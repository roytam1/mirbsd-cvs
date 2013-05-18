#!/usr/bin/env mksh
# $MirOS: src/usr.bin/mkdep/mkdep.sh,v 1.9 2008/10/05 16:39:14 tg Exp $
#-
# Copyright (c) 2004, 2005, 2007, 2008, 2009
#	Thorsten Glaser <tg@mirbsd.org>
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
# This is loosely based upon material provided by: the University of
# California, Berkeley, and its contributors.


function die
{
	print -u2 mkdep: "$@"
	exit 1
}

# select a suitable C compiler
cc=${CC:-cc}
cc=${cc##@(?(+([! ])/)ccache+([	 ]))}
[[ -x $cc || -x ${cc%% *} ]] || cc=$(whence -p $cc) || \
    cc=$(whence -p ${cc%% *}) || cc=$(whence -p cc)
[[ -x $cc || -x ${cc%% *} ]] || die no compiler found.
CC=$cc; export CC

# default values
df=.depend
of=
flag_a=0
flag_p=0

# parse mkdep(1) options
oi=$OPTIND
while getopts ":af:p" opt; do
	case $opt {
	a)	flag_a=1 ;;
	f)	df="${OPTARG:-.depend}" ;;
	p)	flag_p=1 ;;
	\?)	break ;;
	*)	break ;;	# e.g. '+a'
	}
	# This is needed because we 'break' in the case \? above,
	# where OPTIND varies between *ksh versions due to a bug,
	# inherited from pdksh via oksh, in mksh < 39.9.20091015
	oi=$OPTIND
done
shift $((oi - 1))

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
export CCACHE_DISABLE=1
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
