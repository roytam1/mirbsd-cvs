#!/bin/sh
# $MirOS$
# $OpenBSD$

dev=/dev/rtc
rm=/bin/rm

if [ -c $dev ]; then
	$rm $dev
fi

exit 0
