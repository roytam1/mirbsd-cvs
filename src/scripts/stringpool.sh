#!/bin/mksh
# $MirOS: src/scripts/stringpool.sh,v 1.1 2016/07/24 20:14:25 tg Exp $
#-
# Copyright © 2016, 2017
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
#-
# Overwrites $1 with string pool content, cf. mircvs://mksh/sh.h

set -A filelines	# content of entire file
set -A rawlinecontent	# content of raw line in block
set -A rawlinenumber	# item number, or -1 for not an item (ifdef)
set -A itemname		# name of item in block
set -A itemcontent	# string content of item
set -A itemlength	# length of string content
set -A sorteditems	# item* IDs, sorted by length
set -A itemtarget	# target item* ID, or -1 for use content
set -A itemoffset	# offset in itemtarget, if any
nfilelines=0
nrawlines=0
nitems=0

[[ -s $1 ]] || exit 1

function cstrlen {
	#XXX real C strlen() would be better
	local s
	eval s=\$\'"${1//\'/\\\'}"\'
	REPLY=${#s}
}

state=0
while IFS= read -r fline; do
	case $state:$fline {
	(0:*'helpers for pooled strings'*)
		state=1
		;&
	(0:*)
		filelines[nfilelines++]=$fline
		;;
	(1:*'helpers for string pooling'*)
		state=2
		sepline=$fline
		;;
	(2:*'end of string pooling'*)
		# sort lines by content length
		i=-1
		while (( ++i < nitems )); do
			print -r -- ${itemlength[i]} $i
		done | sort -k1,1nr -k2n |&
		j=-1
		while read -p len nr; do
			sorteditems[++j]=$nr
		done
		# find same-end strings of higher length
		i=0
		while (( ++i < nitems )); do
			si=${sorteditems[i]}
			j=-1
			while (( ++j < i )); do
				sj=${sorteditems[j]}
				delta=${itemcontent[sj]%"${itemcontent[si]}"}
				[[ ${itemcontent[sj]} = "$delta" ]] && continue
				itemtarget[si]=$sj
				itemoffset[si]=${|cstrlen "$delta";}
				break
			done
		done
		# append target lines to filelines
		i=-1
		while (( ++i < nrawlines )); do
			if (( rawlinenumber[i] == -1 )); then
				filelines[nfilelines++]=${rawlinecontent[i]}
			elif (( itemtarget[rawlinenumber[i]] == -1 )); then
				filelines[nfilelines++]="EXTERN const char ${itemname[rawlinenumber[i]]}[] E_INIT(\"${itemcontent[rawlinenumber[i]]});"
			else
				filelines[nfilelines++]="#define ${itemname[rawlinenumber[i]]} (${itemname[itemtarget[rawlinenumber[i]]]} + ${itemoffset[rawlinenumber[i]]})"
			fi
		done
		# append source lines to filelines
		filelines[nfilelines++]=$sepline
		i=-1
		while (( ++i < nrawlines )); do
			filelines[nfilelines++]=${rawlinecontent[i]}
		done
		filelines[nfilelines++]=$fline
		state=3
		;;
	(2:*)
		# parse line
		rawlinecontent[nrawlines]=$fline
		if [[ $fline != '#define T'+([0-9A-Za-z_])' "'*\" ]]; then
			rawlinenumber[nrawlines++]=-1
		else
			rawlinenumber[nrawlines++]=$nitems
			fline=${fline#?define?}
			itemname[nitems]=${fline%%' '*}
			fline=${fline#*' "'}
			itemcontent[nitems]=$fline
			itemlength[nitems]=${|cstrlen "$fline";}
			itemtarget[nitems++]=-1
		fi
		;;
	(3:*)
		filelines[nfilelines++]=$fline
		;;
	}
done <"$1"

i=-1
while (( ++i < nfilelines )); do
	print -r -- "${filelines[i]}"
done >"$1"
