#!/bin/ksh
# $MirOS$

set -e
set -x
aclocal -I .
autoheader
set +e
autoconf
[[ -e autom4te.cache ]] && rm -rf autom4te.cache
exit 0
