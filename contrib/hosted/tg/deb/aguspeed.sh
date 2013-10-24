#!/bin/mksh
# $MirOS: contrib/hosted/tg/deb/aguspeed.sh,v 1.2 2011/06/09 20:30:24 tg Exp $
# $Id$
#-
# From Planet Debian. Not complicated enough for copyright.

unset LANGUAGE
export LC_ALL=C

(( USER_ID )) && exec sudo mksh "$0" "$@"

if [[ $1 = -f ]]; then
	fflag=1
	shift
else
	fflag=0
fi

if [[ -n $1 && -s /etc/apt/sources.list.$1 ]]; then
	cat "/etc/apt/sources.list.$1" >/etc/apt/sources.list
fi

rv=
set -x
apt-get update || rv=$?
dpkg --clear-avail || rv=${rv:-$?}
# this emits a harmless warning on squeeze
dpkg --forget-old-unavail || rv=${rv:-$?}
(( fflag )) || if sa=$(whence -p sync-available); then
	# call with mksh due to *buntu bug
	mksh "$sa" || rv=${rv:-$?}
fi
exit $rv