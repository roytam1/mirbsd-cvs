# $MirOS$

SHELLCMD="mksh -e"
if [[ $1 = -d ]]; then
	SHELLCMD=cat
	shift
fi
cat "$@" | awk -f $(dirname $0)/list2sh.awk | ${SHELLCMD}
