#!/bin/sh
# $MirOS$
# $OpenBSD$

chmod=/bin/chmod
dev=/dev/vmnet
echo=/bin/echo
mknod=/sbin/mknod
rm=/bin/rm

# didn't unload?
for i in 0 1 2 3; do
	if [ -c "$dev""$i" ]; then
		$rm -f "$dev""$i"
	fi
done

for i in 0 1 2 3; do
	$mknod "$dev""$i" c $3 $(expr "$i" \* 16)
	$chmod 600 "$dev""$i"
done

exit 0
