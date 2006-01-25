#!/bin/sh
# $MirOS: ports/www/php/files/autogen.sh,v 1.1 2005/03/27 22:20:27 tg Exp $

set -e
set -x
aclocal -I .
autoheader
set +e
autoconf
rm -rf autom4te.cache
exit 0
