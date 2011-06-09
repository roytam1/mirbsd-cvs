#!/bin/mksh
# $MirOS: contrib/hosted/tg/deb/aguspeed.sh,v 1.1 2011/05/25 17:46:54 tg Exp $
# $Id$
#-
# From Planet Debian. Not complicated enough for copyright.

unset LANGUAGE
export LC_ALL=C

(( USER_ID )) && exec sudo mksh "$0" "$@"

if [[ -n $1 && -s /etc/apt/sources.list.$1 ]]; then
	cat "/etc/apt/sources.list.$1" >/etc/apt/sources.list
fi

rv=
set -x
apt-get update || rv=$?
dpkg --clear-avail || rv=${rv:-$?}
# this emits a harmless warning on squeeze
dpkg --forget-old-unavail || rv=${rv:-$?}
if sa=$(whence -p sync-available); then
	# call with mksh due to *buntu bug
	mksh "$sa" || rv=${rv:-$?}
fi
exit $rv
