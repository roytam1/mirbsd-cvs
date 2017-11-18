#!/bin/mksh
# $MirOS$

set -U
sed '/^10000/,$d' <UnicodeData.txt | while IFS= read -r line; do
	typeset -i10 x=0x${line::4}
	(( x = (x < 32) || (x >= 0x7F && x <= 0x9F) || \
	    (x >= 0xD800 && x <= 0xDFFF) || \
	    (x >= 0xEF80 && x <= 0xEFFF) || (x > 0xFFFD) ? 0 : x ))
	line=${line//'&'/'&amp;'}
	line=${line//'<'/'&lt;'}
	line=${line//'>'/'&gt;'}
	y=
	(( x )) && y="&#$x;"
	print -r -- "<tr><td>$y</td><td>U+$line</td></tr>"
done >unidata.htm
sed '/^10000/,$d' <UnicodeData.txt | while IFS= read -r line; do
	typeset -Uui16 -Z7 x=0x${line::4}
	typeset -i1 j
	(( j = (x < 32) || (x >= 0xD800 && x <= 0xDFFF) || \
	    (x >= 0xEF80 && x <= 0xEFFF) || (x > 0xFFFD) ? 1 : x ))
	m=${j#1#}
	n=${%m}
	print -n "U+${x#16#} "
	if (( n == -1 )); then
		print -n " �"
	elif (( n == 0 )); then
		print -nr -- "  $m"
	elif (( n == 1 )); then
		print -nr -- "$m "
	elif (( n == 2 )); then
		print -nr -- "$m"
	else
		print -u2 Fatal $k $n
		exit 1
	fi
	print -r -- " ${line:5}"
done >unidata.txt
typeset -i1 j
while IFS= read -r line; do
	typeset -Uui16 -Z11 wi=0x${line%%;*}
	if (( wi < 0x10000 )); then
		typeset -Uui16 -Z7 x=wi
		(( j = (x < 32) || (x >= 0xD800 && x <= 0xDFFF) || \
		    (x >= 0xEF80 && x <= 0xEFFF) || (x > 0xFFFD) ? 1 : x ))
		m=${j#1#}
		n=${%m}
		print -n "U+${x#16#} "
		if (( n == -1 )); then
			print -n " � "
		elif (( n == 0 )); then
			print -nr -- "  $m "
		elif (( n == 1 )); then
			print -nr -- "$m  "
		elif (( n == 2 )); then
			print -nr -- "$m "
		else
			print -u2 Fatal $k $n
			exit 1
		fi
	else
		print -n "U-${wi#16#}  "
		set +U
		(( j = (wi >> 18) | 0xF0 ))
		print -nr -- "${j#1#}"
		(( j = ((wi >> 12) & 0x3F) | 0x80 ))
		print -nr -- "${j#1#}"
		(( j = ((wi >> 6) & 0x3F) | 0x80 ))
		print -nr -- "${j#1#}"
		(( j = (wi & 0x3F) | 0x80 ))
		print -nr -- "${j#1#}	"
		set -U
	fi
	print -r -- "${line#*;}"
done <UnicodeData.txt >uni_smp.txt
i=0x1f
typeset -i1 j
typeset -Uui16 -Z7 k

while (( (k = j = ++i) < 0x10000 )); do
	(( i == 0xD800 )) && k=j=i=0xE000
	(( i == 0xEF80 )) && k=j=i=0xF000
	if (( !(i & 0xFFF) )); then
		print '┝━━━━━━━╋━━━━┿━━━━┿━━━━┿━━━━┿━━━━┿━━━━┿━━━━┿━━━━╋━━━━━━━┥'
	elif (( !(i & 0xFF) )); then
		print '├───────╂────┼────┼────┼────┼────┼────┼────┼────╂───────┤'
	fi
	(( l = i & 15 ))
	if (( l == 0 )); then
		print -n "╽ ${k#16} ┃ "
	elif (( l == 8 )); then
		print -n "╿ ${k#16} ┃ "
	else
		print -n " │ "
	fi
	m=${j#1#}
	n=${%m}
	if (( n == -1 )); then
		print -n " �"
	elif (( n == 0 )); then
		print -nr -- "  $m"
	elif (( n == 1 )); then
		print -nr -- "$m "
	elif (( n == 2 )); then
		print -nr -- "$m"
	else
		print -u2 Fatal $k $n
		exit 1
	fi
	if (( l == 7 )); then
		print " ┃ ${k#16} ╽"
	elif (( l == 15 )); then
		print " ┃ ${k#16} ╿"
	fi
done >utf-8
