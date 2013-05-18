#!/bin/mksh
# $MirOS: src/share/misc/licence.template,v 1.24 2008/04/22 11:43:31 tg Rel $
#-
# Copyright (c) 2006, 2008
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
# Enhance ld(1) (and libtool(1) on Darwin, with tweaks for Leopard's
# weird gcc) by new functionality

_LD=/usr/bin/ld
[[ $0 = *(*/)libtool ]] && _LD=/usr/bin/libtool
[[ $0 = *(*/)collect2 ]] && if [[ $1 = -Ww,collect2 ]]; then
	_LD=$2
	shift
	shift
else
	_LD=$(gcc -print-prog-name=collect2)
fi

set -A args
libafter=
for arg in "$@"; do
	[[ $arg = @(-Wl,)* ]] && \
	    arg=$(print -nr -- ${arg#-Wl,} | tr ',' ' ')
	if [[ $arg != @(--library-after=)* ]]; then
		args[${#args[*]}]=$arg
		continue
	fi
	libafter="$libafter -L${arg#--library-after=}"
done
[[ -z $LDVERBOSE ]] || print -r "${_LD} ${args[*]} $libafter"
exec ${_LD} "${args[@]}" $libafter
