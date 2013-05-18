#!/usr/bin/env mksh
# $MirOS: ports/infrastructure/install/ld-wrapper.ksh,v 1.4 2006/08/16 19:43:53 tg Exp $
#-
# Copyright (c) 2006, 2008
#	Thorsten Glaser <tg@mirbsd.de>
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
