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
#-
# Read unifont.hex and remove glyphs from blanks.hex and rc-priv.hex
# then pad 8x16 to 9x18 and 16x16 to 18x18 and output them into bdfc
# stub files, separate by glyph width. (Character width is ignored.)

set -A skip
while IFS=: read i data rest; do
	if [[ $data = 00542A542A542A542A542A542A542A00 ]]; then
		skip[0x$i]=1
	else
		print -ru2 E: unknown blanks line "$i:$data:$rest"
		exit 1
	fi
done <blanks.hex
while IFS=: read i data rest; do
	if [[ $data = FFB9C5EDD5D5D5D5D5D5D5D5EDB991FF ]]; then
		skip[0x$i]=1
	else
		print -ru2 E: unknown rc-priv line "$i:$data:$rest"
		exit 1
	fi
done <rc-priv.hex

function check_hw {
	typeset -Uui16 -Z5 q r

	q=0x${data: 0:2}
	r=0x${data: 30:2}
	(( top |= (q || r) ))
}

function check_fw {
	typeset -Uui16 -Z5 q r

	q=0x${data: 0:4}
	r=0x${data: 60:4}
	(( top |= (q || r) ))
	if [[ $data = @(AAAA00018000*5555|555580000001*AAAA) ]]; then
		top=0
		odd=0
	fi
}

function merge_hw {
	typeset -Uui16 -Z5 q

	q=0x${data: j*2:2}
	(( odd |= (q & 1) ))
	l+=:${q#16#}00
}

function merge_fw {
	typeset -Uui16 -Z9 q

	q=0x${data: j*4:4}
	(( odd |= (q & 1) ))
	(( q <<= 7 ))
	l+=:${q#16#}
}

exec 4>unihalf9x18.bdfc 5>unihalf18x18.bdfc

print -ru4 -- =bdfc 1
print -ru4 -- C
print -ru4 -- d 540 0 9 0 0 -4

print -ru5 -- =bdfc 1
print -ru5 -- C
print -ru5 -- d 1080 0 18 0 0 -3

typeset -i1 ch
while IFS=: read i data rest; do
	if (( skip[(ch = 0x$i)] )); then
		print SKIP $i
		continue
	fi
	if (( ${#data} == 32 )); then
		ofd=4
		nulls=0000
		sz=hw
		l="c $i 9 $nulls"
	elif (( ${#data} == 64 )); then
		ofd=5
		nulls=000000
		sz=fw
		l="c $i 18 $nulls"
	else
		print E:UW $i ${#data}
		continue
	fi
	odd=0 top=0
	j=-1
	while (( ++j < 16 )); do
		eval merge_$sz
	done
	l+=:$nulls
	print -ru$ofd -- $l
	eval check_$sz
	(( odd )) && print HORZ $i
	(( top )) && print VERT $i
done <unifont.hex | tee hexpad.log

print -u4 .
print -u5 .
exec 4>&- 5>&-
print DONE
