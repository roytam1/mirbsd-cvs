# $MirOS: src/distrib/miniroot/runlist.sh,v 1.3 2006/07/24 00:24:01 tg Exp $

SHELLCMD="mksh -e"
if [[ $1 = -d ]]; then
	SHELLCMD=cat
	shift
fi
cat "$@" | awk -f $(dirname $0)/list2sh.awk | ${SHELLCMD}
