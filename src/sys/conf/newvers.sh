#!/bin/mksh
# $MirOS: src/sys/conf/newvers.sh,v 1.11 2006/06/04 00:28:43 tg Exp $
#-
# Copyright (c) 2003, 2004, 2005, 2006
#	Thorsten Glaser <tg@mirbsd.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a nontrivial bug.
#-
# Kernel version generation script
# Called with: MirBSD major minor level openbsdlevel
#
# List of files to check for version number bumps:
#	sys/sys/param.h, share/mk/sys.mk
#	share/tmac/mdoc/doc-{common,syms}
#	share/tmac/tmac.an.old

# MirBSD version cycle calculation
typeset -i     "_osrmj=${1:-9}"	# Major MirBSD revision number fallback
typeset -Uui16 "_osrmn=${2:-0}"	# only update the above once per release!
if (( _osrmn < 0 || _osrmn > 255 || _osrmj < 7 )); then
	print -u2 "Error: versioning information damaged!"
	exit 1
fi
let _osrmx=0
if ((_osrmn < 16)); then
	_osrtc="?"	# <unknown/damaged>
elif ((_osrmn < 128)); then
	_osrtc="n"	# nearly
elif ((_osrmn == 128)); then
	_osrtc="r"	# released
elif ((_osrmn < 160)); then
	_osrtc="s"	# stable
	let _osrmx=_osrmn-128
else
	_osrtc="u"	# unlocked
fi
if ((_osrmx < 1)); then
	_osrex=""	# regular release/snapshot/local build (-semel)
else			# released for the second, third... time
	case $_osrmx {
	(2)	_osrex=bis		;;
	(4)	_osrex=ter		;;
	(6)	_osrex=quater		;;
	(8)	_osrex=quinquies	;;
	(*)	_osrex=num.$((_osrmx / 2 + 1))ies ;;
	}
	(( (_osrmx % 2) == 1 )) && _osrex=-stable
	(( _osrmn == 159 )) && _osrex=-final
fi
onmj="${_osrmn#16#}$_osrex"
osl="${_osrmj}${_osrtc}${onmj}"

# Everything else
[[ -s version ]] || print 0 >version
touch version
let "wv=$(<version)"

if [[ $4 = +([0-9]).+([0-9]) ]]; then
	osc=" from OpenBSD $4"
else
	osc=
fi
ost="$(uname)"
tm="$(date)"
wd="$(pwd)"
wh="$(hostname)"
wk="$(basename "$wd")"
wt="$(TZ=UTC date '+%Y%m%d')"
wu="$(id -un 2>/dev/null)" || wu=root
myname="$(cd $(dirname "$0"); print -r "$(pwd)/$(basename "$0")")"

cat >vers.c <<EOF
/* Automatically generated by $myname - Do not edit. */

#ifdef INCLUDE_CONFIG_FILE
#include "config_file.h"
#endif

const char ostype[]="$ost";
const char osrelease[]="$_osrmj";
const char ospatchlevel[]="#${osl}-$wt";
const char osversion[]="${wk}#$wv";
const char sccs[]=
    "	@(#)$ost $_osrmj rev.${onmj}${osc} ($wk) #${wv}: ${tm}\n"
    "	generated by @(#)\$MirOS: src/sys/conf/newvers.sh,v 1.11 2006/06/04 00:28:43 tg Exp $\n";
const char version[]=
    "${ost}#$osl ($wk) #${wv}: ${tm}\n\t${wu}@${wh}:${wd}\n";
EOF

print $((wv + 1)) >version
