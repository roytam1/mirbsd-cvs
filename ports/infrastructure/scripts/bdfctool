#!/bin/mksh
# $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $
#-
# Copyright © 2012
#	Thorsten Glaser <tg@mirbsd.org>
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

uascii=-1
while getopts "acdeh" ch; do
	case $ch {
	(a) uascii=1 ;;
	(+a) uascii=0 ;;
	(c|d|e|h) mode=$ch ;;
	(*) mode= ;;
	}
done
shift $((OPTIND - 1))
(( $# )) && mode=

if [[ $mode = ?(h) ]]; then
	print -u2 "Usage: ${0##*/} -c | -d | -e [-a]"
	[[ $mode = h ]]; exit $?
fi

lno=0
if [[ $mode = e ]]; then
	if (( uascii == 1 )); then
		set -A BITv -- '.' '#' '|'
	else
		set -A BITv -- '　' '䷀' '▌'
	fi
	while IFS= read -r line; do
		(( ++lno ))
		if [[ $line = 'e '* ]]; then
			set -A f -- $line
			i=${f[3]}
			print -r -- "$line"
			while (( i-- )); do
				if IFS= read -r line; then
					print -r -- "$line"
					continue
				fi
				print -u2 "E: Unexpected end of 'e' command" \
				    "at line $lno"
				exit 2
			done
			(( lno += f[3] ))
			continue
		fi
		if [[ $line != 'c '* ]]; then
			print -r -- "$line"
			continue
		fi
		set -A f -- $line
		if (( (w = f[2]) > 32 || w < 1 )); then
			print -ru2 "E: width ${f[2]} not in 1‥32 at line $lno"
			exit 2
		fi
		if (( w <= 8 )); then
			adds=000000
		elif (( w <= 16 )); then
			adds=0000
		elif (( w <= 24 )); then
			adds=00
		else
			adds=
		fi
		(( shiftbits = 32 - w ))
		(( uw = 2 + w ))
		IFS=:
		set -A bmp -- ${f[3]}
		IFS=$' \t\n'
		f[3]=${#bmp[*]}
		print -r -- "${f[*]}"
		chl=0
		for ch in "${bmp[@]}"; do
			(( ++chl ))
			if [[ $ch != +([0-9A-F]) ]]; then
				print -ru2 "E: char '$ch' at #$chl in line $lno not hex"
				exit 2
			fi
			ch=$ch$adds
			if (( ${#ch} != 8 )); then
				print -ru2 "E: char '$ch' at #$chl in line $lno not valid"
				exit 2
			fi
			typeset -Uui2 -Z$uw bbin=16#$ch
			(( bbin >>= shiftbits ))
			b=${bbin#2#}
			b=${b//0/${BITv[0]}}
			b=${b//1/${BITv[1]}}
			print -r -- $b${BITv[2]}
		done
	done
	exit 0
fi

if (( uascii != -1 )); then
	print -u2 "E: ±a not allowed for -$mode mode"
	exit 1
fi
