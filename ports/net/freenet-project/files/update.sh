#!/bin/sh
# $MirOS$
#-
# Copyright (c) 2003
#	Thorsten Glaser <x86@ePost.de>, for the MirOS Project
#
# Subject to these terms, everybody who obtained a copy of this work
# is hereby permitted to deal in the work without restriction inclu-
# ding without limitation the rights to use, distribute, sell, modi-
# fy, publically perform, give away, merge or sublicense it provided
# this notice is kept and the authors and contributors are given due
# credit in derivates or accompanying documents.
#
# This work is provided "as is" with no explicit or implicit warran-
# ties whatsoever to the maximum extend permitted by applicable law;
# in no event may an author or contributor be held liable for damage
# that is, directly or indirectly, caused by the work, even if advi-
# sed of the possibility of such damage.
#-
# Update script for FreenetProject

if [ $(id -u) -ne 0 ]; then
	echo 'This script must be run as root, exiting...'
	exit 1
fi

cd $(dirname $0)
svc -d .
rm -f node/freenet-latest.jar
(cd node; ftp http://www.freenetproject.org/snapshots/freenet-latest.jar)
if [ ! -e node/freenet-latest.jar ]; then
	echo 'Update failed.'
	exit 2
fi
mv node/freenet.jar node/freenet-old.jar
mv node/freenet-latest.jar node/freenet.jar
echo 'Update done.'
svc -u .
exit 0
