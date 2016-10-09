#!/bin/mksh
# $MirOS: contrib/fonts/tools/bdfc2lst.sh,v 1.1 2016/10/09 18:11:57 tg Exp $
#-
# .bdfc -> .lst (list of characters contained within)

if [[ $1 = -w ]]; then
	# enable widths
	alias postprocess='sort | addwidths'
else
	alias postprocess=sort
fi

function addwidths {
	local hex s
	local -i1 ch
	set -U

	while read hex; do
		ch=0x$hex
		if (( ch )); then
			s=${ch#1#}
			print -r -- "$hex ${%s}"
		else
			print -r -- "$hex 0"
		fi
	done
}

for i in *.bdfc; do
	o=${i%.bdfc}.lst
	sed -n '/^c \([0-9A-F][0-9A-F][0-9A-F][0-9A-F]\) .*$/s//\1/p' \
	    <"$i" | postprocess >"$o"
done
