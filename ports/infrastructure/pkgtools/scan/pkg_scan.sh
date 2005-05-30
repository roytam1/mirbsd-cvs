#!/bin/mksh
# $MirOS: ports/infrastructure/pkgtools/scan/pkg_scan.sh,v 1.1.7.1 2005/03/18 15:47:18 tg Exp $
#-
# Copyright (c) 2004, 2005
#	Benny Siegert <bsiegert@66h.42h.de>
#	Thorsten "mirabile" Glaser <tg@66h.42h.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.
#-
# Regenerates the "shared directories" database from scratch.

if [[ -z $1 || $1 = -h ]]; then
	echo "Usage:"
	echo " $0 [-f | -d] [targetfilename]"
	exit 1
fi

if [[ $1 = -f ]]; then
	let FORCE=1
	shift
else
	let FORCE=0
fi

if [[ $1 = -d ]]; then
	let DRY=1
	let FORCE=0
	shift
else
	let DRY=0
fi

DB="$1"
[[ -z $DB ]] && DB=@@dbdir@@/shareddirs.db
[[ -e $DB ]] && if (( FORCE == 0 )); then
	echo "Error: destination ($DB) already exists!"
	exit 1
fi

T=$(mktemp /tmp/pkg_scan.XXXXXXXXXX) || exit 1
trap 'rm -f $T ; exit 0' 0
trap 'rm -f $T ; exit 1' 1 2 3 13 15

awk '
/^@dirrm/	{ ++dirs[$2] }
/^[^@].*\/$/	{ ++dirs[substr($1, 0, length($1) - 1)] }

END {
	OFS = "|"
	for (i in dirs)
		print dirs[i], i
}' @@dbdir@@/pkg/*/+CONTENTS >"$T" 2>/dev/null

if [[ -s $T ]]; then
	if (( DRY == 0 )); then
		install -c -o root -g bin -m 644 "$T" "$DB"
	else
		install -c -m 400 "$T" "$DB"
	fi
	exit 0
fi

echo "Error: cannot create non-empty database."
exit 1
