#!/bin/sh
# $MirOS$
# $OpenBSD$

dev=/dev/vmnet
rm=/bin/rm

for i in 0 1 2 3; do
	if [ -c "$dev""$i" ]; then
		$rm -f "$dev""$i"
	fi
done

exit 0
