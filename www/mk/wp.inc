rcsid_wp_inc='$MirOS: www/files/wp.pm,v 1.2 2018/08/29 01:29:21 tg Exp $';
#-
# Copyright © 2018
#	mirabilos <m@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un‐
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person’s immediate fault when using the work as intended.

# $1 = waypoint code
# $2 = name of variable to store classifyer into, or empty
# $3 = name of variable to store hyperlink label into, or empty
# returns URL of waypoint site (value substitution)
function explwp {
	local _explwp_wp=$1 _explwp_classifyer _explwp_label
	[[ -n $2 ]] && nameref _explwp_classifyer=$2
	[[ -n $3 ]] && nameref _explwp_label=$3
	_explwp_classifyer=""
	_explwp_label=$_explwp_wp
	REPLY=""

	case $_explwp_wp {
	(BC+([0-9]))
		REPLY="https://bessercacher.de/forum/viewtopic.php?t=${_explwp_wp#BC}"
		_explwp_label="BesserCacher#${_explwp_wp#BC}"
		_explwp_classifyer=BC ;;
	(EC+([0-9]))
		REPLY="http://extremcaching.com/index.php/output-2/${_explwp_wp#EC}"
		_explwp_classifyer=EC ;;
	(GA[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="https://geocaching.com.au/cache/$_explwp_wp"
		_explwp_classifyer=GA ;;
	(GC[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="https://www.geocaching.com/seek/cache_details.aspx?wp=$_explwp_wp"
		_explwp_classifyer=GC ;;
	(GD[0-9A-Z][0-9A-Z]-[A-Z][A-Z][A-Z][A-Z])
		REPLY="http://geodashing.gpsgames.org/cgi-bin/dp.pl?dp=$_explwp_wp"
		_explwp_classifyer=GD ;;
	(GE[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="http://geocaching.gpsgames.org/cgi-bin/ge.pl?wp=$_explwp_wp"
		_explwp_classifyer=GE ;;
	(GG[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="http://golf.gpsgames.org/cgi-bin/golf.pl?course=$_explwp_wp&coursedetails=Go"
		_explwp_classifyer=GG ;;
	(GK+([0-9A-F]))
		REPLY="https://geokrety.org/konkret.php?id=$((16#${_explwp_wp#GK}))"
		_explwp_classifyer=GK ;;
	(GL[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="http://coord.info/$_explwp_wp"
		_explwp_classifyer=GL ;;
	(N[0-9][0-9A-F][0-9A-F][0-9A-F][0-9A-F])
		REPLY="http://www.navicache.com/cgi-bin/db/displaycache2.pl?CacheID=$((16#${_explwp_wp#N}))"
		_explwp_classifyer=NC ;;
	(OB[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="https://www.opencaching.nl/viewcache.php?wp=$_explwp_wp"
		_explwp_classifyer=OB ;;
	(OC[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="https://www.opencaching.de/viewcache.php?wp=$_explwp_wp"
		_explwp_classifyer=OC ;;
	(OK[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="https://opencache.uk/viewcache.php?wp=$_explwp_wp"
		_explwp_classifyer=OK ;;
	(OP[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="https://opencaching.pl/viewcache.php?wp=$_explwp_wp"
		_explwp_classifyer=OP ;;
	(OR[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="https://www.opencaching.ro/viewcache.php?wp=$_explwp_wp"
		_explwp_classifyer=OR ;;
	(OU[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="http://www.opencaching.us/viewcache.php?wp=$_explwp_wp"
		_explwp_classifyer=OU ;;
	(OZ[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="https://opencaching.cz/viewcache.php?wp=$_explwp_wp"
		_explwp_classifyer=OZ ;;
	(PR[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="http://coord.info/$_explwp_wp"
		_explwp_classifyer=PR ;;
	(SH[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="http://shutterspot.gpsgames.org/cgi-bin/sh.pl?wp=$_explwp_wp"
		_explwp_classifyer=SH ;;
	(TB[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="https://www.geocaching.com/track/details.aspx?tracker=$_explwp_wp"
		_explwp_classifyer=TB ;;
	([TLC]C[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="https://play.terracaching.com/Cache/$_explwp_wp"
		_explwp_classifyer=TC ;;
	(VX[0-9A-Z][0-9A-Z]-[A-Z][A-Z][A-Z][A-Z])
		REPLY="http://geovexilla.gpsgames.org/cgi-bin/vx.pl?listwaypointlogs=yes&wp=$_explwp_wp"
		_explwp_classifyer=VX ;;
	(WM[0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]?([0-9A-Z]))))))
		REPLY="http://www.waymarking.com/waymarks/$_explwp_wp"
		_explwp_classifyer=WM ;;
	(m/+([0-9A-Za-z_-])/+([0-9])?(/))
		_explwp_wp=${_explwp_wp%/}
		REPLY="https://www.munzee.com/$_explwp_wp/"
		_explwp_classifyer=m/ ;;
	(2[0-9][0-9][0-9]-[0-1][0-9]-[0-3][0-9]_@(?(-)+([0-9])_?(-)+([0-9])|global))
		local _explwp_m _explwp_saveIFS=$IFS
		IFS='-_'
		set -- $_explwp_wp
		set -A _explwp_m 0 31 28 31 30 31 30 31 31 30 31 30 31
		(( _explwp_m[2] = (($1 % 4) == 0 && (($1 % 100) != 0 || ($1 % 400) == 0)) ? 29 : 28 ))
		REPLY="http://wiki.xkcd.com/geohashing/$_explwp_wp"
		IFS=_
		(( $2 >= 1 && $2 <= 12 && $3 >= 1 && $3 <= _explwp_m[$2] )) && \
		    if [[ $_explwp_wp = *_global ]]; then
			_explwp_classifyer=Gh
		elif set -- $_explwp_wp && \
		    (( $2 >= -90 && $2 <= 90 && $3 >= -180 && $3 <= 180 )); then
			_explwp_classifyer=gh
		fi
		IFS=$_explwp_saveIFS
		;;
	}
}

# test vectors
if [[ -n $test_wp_inc ]]; then
	exec <"$(dirname "$0")/wp.t"
	while IFS= read -r line; do
		[[ $line = __DATA__ ]] && break
	done
	code= label=
	while IFS= read -r line; do
		url=${|explwp "$line" code label;}
		#print -r -- "lynx ${url@Q} # ($code) <$label>"
		print -r -- "lynx '${url//\'/\'\\\'\'}' # ($code) <$label>"
	done
fi
