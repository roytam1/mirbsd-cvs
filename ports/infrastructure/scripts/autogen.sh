#!/bin/mksh
# $MirOS: ports/infrastructure/scripts/autogen.sh,v 1.12 2009/12/06 13:03:57 tg Exp $
#-
# Copyright (c) 2004, 2005, 2006, 2008, 2009
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

if [[ -z $AUTOCONF_VERSION ]]; then
	export AUTOCONF_VERSION=2.13
	print -u2 Warning: AUTOCONF_VERSION unset, using $AUTOCONF_VERSION!
fi

if [[ -z $AUTOMAKE_VERSION ]]; then
	export AUTOMAKE_VERSION=1.9
	print -u2 Warning: AUTOMAKE_VERSION unset, using $AUTOMAKE_VERSION!
fi

if [[ -z $PORTSDIR || ! -d $PORTSDIR/. ]]; then
	manual_mode=1
	PORTSDIR=/usr/ports
else
	manual_mode=0
fi
: ${GNUSYSTEM_AUX_DIR:=$PORTSDIR/infrastructure/db}

export AUTOCONF_VERSION AUTOMAKE_VERSION GNUSYSTEM_AUX_DIR

AM_FLAGS="--miros --ignore-deps"
[[ $AUTOMAKE_VERSION = 1.4 ]] && AM_FLAGS=-i
[[ -n $flags ]] && AM_FLAGS=$flags

todel=
for f in $files ChangeLog ltmain.sh; do
	[[ -e $f ]] && continue
	ln -s /dev/null $f
	todel="$todel $f"
done

for f in libtool.m4 m4salt.inc m4sugar.inc; do
	[[ -e $f ]] || todel="$todel $f"
	[[ -h $f ]] && rm -f $f
	[[ -s $f ]] || ln -sf "$GNUSYSTEM_AUX_DIR/$f" .
done

set -e
set -x
ACLOCAL_AMFLAGS=
[[ -e Makefile.am ]] && ACLOCAL_AMFLAGS=$(grep '^[:space:]*ACLOCAL_AMFLAGS' \
    Makefile.am | cut -d '=' -f 2)
[[ -n $NO_ACLOCAL ]] || aclocal -I . $ACLOCAL_AMFLAGS $ACLOCAL_FLAGS
f=configure.ac
[[ ! -e $f ]] && f=configure.in
[[ -n $NO_AUTOHEADER ]] || if fgrep -q \
    -e AC_CONFIG_HEADER -e AM_CONFIG_HEADER $f; then
	autoheader $AUTOHEADER_FLAGS
fi
set +e
integer rv=0
[[ ! -e Makefile.am ]] || automake --foreign -a $AM_FLAGS || rv=$?
if autoconf $AUTOCONF_FLAGS; then
	chmod 664 configure
else
	(( rv = rv ? rv : 1 ))
fi
(( manual_mode )) || rm -rf autom4te.cache $todel
exit $rv
