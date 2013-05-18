#!/bin/mksh
# $MirOS: src/share/misc/licence.template,v 1.24 2008/04/22 11:43:31 tg Rel $
#-
# Copyright (c) 2004, 2005, 2006
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

if [[ -z $AUTOCONF_VERSION ]]; then
	export AUTOCONF_VERSION=2.13
	print Warning: AUTOCONF_VERSION unset!
fi

if [[ -z $AUTOMAKE_VERSION ]]; then
	export AUTOMAKE_VERSION=1.9
	print Warning: AUTOMAKE_VERSION unset!
fi

todel=
for f in libtool.m4 m4salt.inc m4sugar.inc; do
	[[ -e $f ]] || todel="$todel $f"
	[[ -h $f ]] && rm -f $f
	[[ -s $f ]] || ln -sf "$(dirname "$0")/$f" .
done

set -e
set -x
ACLOCAL_AMFLAGS=
[[ -e Makefile.am ]] && ACLOCAL_AMFLAGS=$(grep '^[:space:]*ACLOCAL_AMFLAGS' Makefile.am | cut -d '=' -f 2)
aclocal -I . $ACLOCAL_AMFLAGS
f=configure.ac
[[ ! -e $f ]] && f=configure.in
if fgrep -q -e AC_CONFIG_HEADER -e AM_CONFIG_HEADER $f; then
	[[ -n $NO_AUTOHEADER ]] || autoheader
fi
set +e
[[ ! -e Makefile.am ]] || automake --foreign -i --add-missing
autoconf && chmod 664 configure
(cd ogonkify && autoconf && chmod 664 configure)
[[ -z $todel ]] || eval rm -f $todel
[[ -e autom4te.cache ]] && rm -rf autom4te.cache
exit 0
