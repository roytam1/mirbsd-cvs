#!/bin/sh
# $MirOS$
# $OpenBSD$

dev=/dev/vmmon
rm=/bin/rm

if [ -c $dev ]; then
	$rm $dev
fi

exit 0
