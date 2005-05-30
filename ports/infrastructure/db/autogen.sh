#!/bin/mksh
# $MirOS: ports/infrastructure/db/autogen.sh,v 1.2 2005/04/28 20:33:05 tg Exp $
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
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.

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
automake --foreign -i
autoconf && chmod 664 configure
[[ -z $todel ]] || eval rm -f $todel
[[ -e autom4te.cache ]] && rm -rf autom4te.cache
exit 0
