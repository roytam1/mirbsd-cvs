#!/bin/sh
# $MirOS$
# $OpenBSD$

modload=/sbin/modload
modunload=/sbin/modunload
prefix=@PREFIX@
lkmbase=$prefix/lib/vmware/modules
scriptbase=$prefix/libexec/vmware
sysctl=/sbin/sysctl

sl=$($sysctl -n kern.securelevel)

check_perms() {
	if [ $(id -u) -ne 0 ]; then
		echo "ERROR: You must be root to run this script."
		exit 1
	fi
}

check_securelevel() {
	if [ "$sl" -gt 0 ]; then
		cat <<_EOF
ERROR:	The system's securelevel is currently set to ${sl}.
	It must be less than or equal to 0 in order to load
	kernel modules.
	Consult securelevel(7) and rc(8) as well as the file
	/etc/rc.securelevel for more information on lowering
	the securelevel and its effects.
_EOF
	fi
}

load_modules() {
	TMPFILE1=$(mktemp /tmp/linuxrtc.XXXXXXXXXX) || exit 1
	TMPFILE2=$(mktemp /tmp/vmmon.XXXXXXXXXX) || exit 1
	TMPFILE3=$(mktemp /tmp/if_hub.XXXXXXXXXX) || exit 1
	$modload -e rtc_lkmentry -o $TMPFILE1 \
		-p $scriptbase-linuxrtc_load.sh $lkmbase/linuxrtc.o
	$modload -e vmmon_lkmentry -o $TMPFILE2 \
		-p $scriptbase-vmmon_load.sh $lkmbase/vmmon.o
	$modload -e vmnet_lkmentry -o $TMPFILE3 \
		-p $scriptbase-vmnet_load.sh $lkmbase/if_hub.o
}

unload_modules() {
	$modunload -n linuxrtc -p $scriptbase-linuxrtc_unload.sh
	$modunload -n vmmon -p $scriptbase-vmmon_unload.sh
	$modunload -n vmnet -p $scriptbase-vmnet_unload.sh
}

check_perms
check_securelevel

case $1 in
	load)
		load_modules
		;;
	unload)
		unload_modules
		;;
	*)
		echo "usage: $0 $1 [ load | unload ]"
		exit 1
		;;
esac

exit 0
