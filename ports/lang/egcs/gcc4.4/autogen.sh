# $MirOS$

rv=0
for i in $MODGNU_RECURSE_DIRS; do
	cd "$i"
	$MKSH "${PORTSDIR}/infrastructure/scripts/autogen.sh" || rv=1
done
exit $rv
