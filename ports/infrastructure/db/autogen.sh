#!/bin/mksh
# $MirOS: ports/infrastructure/db/autogen.sh,v 1.4 2005/10/02 18:19:26 tg Exp $
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
# All advertising materials mentioning features or use of this soft-
# ware must display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a nontrivial bug.

if [[ -z $AUTOCONF_VERSION ]]; then
	export AUTOCONF_VERSION=2.13
	print Warning: AUTOCONF_VERSION unset!
fi

todel=
for f in libtool.m4 m4salt.inc m4sugar.inc; do
	[[ -e $f ]] || todel="$todel $f"
	[[ -h $f ]] && rm -f $f
	[[ -s $f ]] || ln -sf "$(dirname "$0")/$f" .
done

set -e
set -x
aclocal -I .
[[ -n $NO_AUTOHEADER ]] || autoheader
set +e
[[ ! -e Makefile.am ]] || automake --foreign -i
autoconf && chmod 664 configure
[[ -z $todel ]] || eval rm -f $todel
[[ -e autom4te.cache ]] && rm -rf autom4te.cache
exit 0
