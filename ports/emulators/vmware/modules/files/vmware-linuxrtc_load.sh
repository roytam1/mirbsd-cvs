#!/bin/sh
# $MirOS$
# $OpenBSD$

chmod=/bin/chmod
dev=/dev/rtc
echo=/bin/echo
mknod=/sbin/mknod
rm=/bin/rm

# didn't unload?
if [ -c $dev ]; then
	$rm -f $dev
fi

$mknod $dev c $3 0
$chmod 600 $dev
exit 0
