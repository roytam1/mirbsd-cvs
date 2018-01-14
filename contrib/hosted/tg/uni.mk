#!/bin/mksh
rcsid='$MirOS: contrib/hosted/tg/uni.mk,v 1.4 2018/01/07 00:25:29 tg Exp $'
#-
# Copyright © 2017, 2018
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

vsn=$(sed -n '1s/^.*Width-\(.*\)\.txt.*$/\1/p' <EastAsianWidth.txt)
set -U
set -A jamo_initial -- G GG N D DD R M B BB S SS '' J JJ C K T P H
set -A jamo_medial -- A AE YA YAE EO E YEO YE O WA WAE OE YO U WEO WE WI YU EU YI I
set -A jamo_final -- '' G GG GS N NI NH D L LG LM LB LS LT LP LH \
    M B BS S SS NG J C K T P H
while IFS= read -r line; do
	if [[ $line != *'<Hangul Syllable, First>'* ]]; then
		print -r -- "$line"
		continue
	fi
	typeset -Uui16 -Z7 cdisp=0x${line%%;*}
	line=${line#*;}
	line=${line#*;}
	IFS=';' read -r endcode x
	let endc=0x$endcode
	let begc=cdisp--
	while (( ++cdisp <= endc )); do
		(( j1 = cdisp - begc ))
		(( j3 = j1 % 28 ))
		(( j1 /= 28 ))
		(( j2 = j1 % 21 ))
		(( j1 /= 21 ))
		n1='HANGUL SYLLABLE '${jamo_initial[j1]}${jamo_medial[j2]}${jamo_final[j3]}
		print -r -- "${cdisp#16#};$n1;$line"
	done
done <UnicodeData.txt >UnicodeData.jamo

exec >unidata.htm
cat <<EOF
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
 "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en"><head>
 <meta http-equiv="content-type" content="text/html; charset=ISO_646.irv:1991" />
 <meta http-equiv="Content-Style-Type" content="text/css" />
 <meta name="MSSmartTagsPreventParsing" content="TRUE" />
 <title>The Unicode Database $vsn (BMP)</title>
 <meta name="RCSId" content="$rcsid" />
</head><body>
<h1>Die Unicode-Datenbank $vsn (Basic Multilingual Plane)</h1>
<table style="table-layout:fixed; border:0px; padding:0px;">
EOF
td='<td style="width:3em;">'
sed '/^10000/,$d' <UnicodeData.jamo | while IFS= read -r line; do
	typeset -i10 x=0x${line::4}
	(( x = (x < 32) || (x >= 0x7F && x <= 0x9F) || \
	    (x >= 0xD800 && x <= 0xDFFF) || \
	    (x >= 0xEF80 && x <= 0xEFFF) || (x > 0xFFFD) ? 0 : x ))
	line=${line//'&'/'&amp;'}
	line=${line//'<'/'&lt;'}
	line=${line//'>'/'&gt;'}
	y=
	(( x )) && y="&#$x;"
	print -r -- "<tr>$td$y</td><td>U+$line</td></tr>"
	td='<td>'
done
print -r -- '</table></body></html>'

exec >unidata.txt
print -r -- "The Unicode $vsn Basic Multilingual Plane"
eqlen=${%vsn}
while (( eqlen-- )); do
	print -n =
done
print =====================================
print
sed '/^10000/,$d' <UnicodeData.jamo | while IFS= read -r line; do
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
done
print
print _______________________________________________________________________
print -r -- "$rcsid"

exec >uni_smp.txt
exec 4>uni_acronyms
print -ru4 -- " From miros${rcsid#?MirOS}"
print -ru4 -- " From unicode: $vsn"
print -r -- "Unicode $vsn (all planes)"
eqlen=${%vsn}
while (( eqlen-- )); do
	print -n =
done
print =====================
print
typeset -i1 j
while IFS= read -r line; do
	typeset -Uui16 -Z11 wi=0x${line%%;*}
	if (( wi < 0x10000 )); then
		typeset -Uui16 -Z7 x=wi
		(( j = (x < 32) || (x >= 0xD800 && x <= 0xDFFF) || \
		    (x >= 0xEF80 && x <= 0xEFFF) || (x > 0xFFFD) ? 1 : x ))
		m=${j#1#}
		n=${%m}
		aO="($m) "
		print -n "U+${x#16#} "
		if (( n == -1 )); then
			print -n " � "
			aO=
		elif (( n == 0 )); then
			print -nr -- "  $m "
		elif (( n == 1 )); then
			print -nr -- "$m  "
			(( x == 1#( || x == 1#) )) && aO="<$m> "
		elif (( n == 2 )); then
			print -nr -- "$m "
		else
			print -u2 Fatal $k $n
			exit 1
		fi
		aO="U+${x#16#}	$aO"
	else
		aO="U-${wi#16#}	("
		print -n "U-${wi#16#}  "
		set +U
		(( j = (wi >> 18) | 0xF0 ))
		print -nr -- "${j#1#}"
		aO+=${j#1#}
		(( j = ((wi >> 12) & 0x3F) | 0x80 ))
		print -nr -- "${j#1#}"
		aO+=${j#1#}
		(( j = ((wi >> 6) & 0x3F) | 0x80 ))
		print -nr -- "${j#1#}"
		aO+=${j#1#}
		(( j = (wi & 0x3F) | 0x80 ))
		print -nr -- "${j#1#}	"
		aO+=${j#1#}
		set -U
		aO+=') '
	fi
	print -r -- "${line#*;}"
	print -ru4 -- "$aO${line#*;}"
done <UnicodeData.jamo
print
print ______________________________________________________________________
print -r -- "$rcsid"
exec 4>&-

exec >utf-8
asn=
eqlen=${%vsn}
while (( eqlen-- )); do
	asn+=┄
done
cat <<EOF
┋ $rcsid

The Unicode $vsn Basic Multilingual Plane
┄┄┄┄┄┄┄┄┄┄┄┄$asn┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄

The width of these characters have been derived from
MirBSD’s new wcwidth code and thus, this file should
show up fine in an uxterm on MirOS (see xterm(1) for
further reference).

This file was generated (and hand-edited afterwards)
by mirabilos <m@mirbsd.org>. Because this is a data‐
base it can be used without the need for an explicit
licence, but if possible I would like to be credited
on derivates.

Now have fun cutting and pasting, although be remin‐
ded that unicode characters above U+00FF can only be
pasted while they are still marked in the source ux‐
term and the latter is visible on the screen. Alter‐
natively you can copy them using an UTF-8 aware edi‐
tor such as jupp: http://www.mirbsd.org/jupp.htm

Combining characters with single-cell width are pre‐
fixed by two spaces in the table below. Places where
a C0 and C1 control character would appear show FFFD
as the replacement character instead, again indented
by two spaces instead of one (to mark this).
▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁

s̲̲u̲p̲e̲r̲s̲c̲r̲i̲p̲t̲,̲ ̲s̲u̲b̲s̲c̲r̲i̲p̲t̲,̲ ̲K̲a̲p̲i̲t̲ä̲l̲c̲h̲e̲n̲ ̲a̲n̲d̲ ̲o̲t̲h̲e̲r̲ ̲s̲c̲r̲i̲p̲t̲

U ᵃᵇᶜᵈᵉᶠᵍʰⁱʲᵏˡᵐⁿᵒᵖ⁚ʳˢᵗᵘᵛʷˣʸᶻ⁰¹²³⁴⁵⁶⁷⁸⁹⁺⁻⁼⁽⁾
D ₐ⁚⁚⁚ₑ⁚⁚ₕᵢⱼₖₗₘₙₒₚ⁚ᵣₛₜᵤᵥ⁚ₓ⁚⁚₀₁₂₃₄₅₆₇₈₉₊₋₌₍₎

U ᴬᴮ⁚ᴰᴱ⁚ᴳᴴᴵᴶᴷᴸᴹᴺᴼᴾ⁚ᴿ⁚ᵀᵁⱽᵂ
K ᴀʙᴄᴅᴇꜰɢʜɪᴊᴋʟᴍɴᴏᴘ⁚ʀꜱᴛᴜᴠᴡ⁚ʏᴢ

U ᵅᵝᵞᵟᵋᶿᶥᶲ ᵠᵡ ªº C( ͣͣ ͤ ͥ ͦ ͧ ͨ ͩ ͪ ͫ ͬ ͭ ͮ ͯ) ʱʴʵʶˀˁˠˤ
D  ᵦᵧ     ᵨᵩᵪ

U ᴭᴯᴲᴻᴽᵄᵆᵊᵌᵎᵑᵓᵔᵕᵙᵚᵜᵸᶛᶝᶞᶟᶡᶢᶣᶤᶦᶧᶨᶩᶪᶫᶬᶭᶮᶯᶰᶱᶳᶴᶵᶶᶷᶸᶹᶺᶼᶽᶾ
K ᴁᴃᴆⱻᴣʛᵻᴌᴫᴎᴐɶᴕʁᴙᴚᵾꞮꟺꭆꝶᴦᴧꭥᴨᴪᴩ
S ℬ ℂ ℰ ℯ ℱ ℊ ℋℌℍ ℎ ℐℑ ℒ ℓ ℳ ℕ ℴ ℙ ℘ ℚ ℛℜℝ ℤℨ
▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁

╭───────┰────┬────┬────┬────┬────┬────┬────┬────┰───────╮
╽ #0000 ┃  � │  � │  � │  � │  � │  � │  � │  � ┃ #0007 ╽
╿ #0008 ┃  � │  � │  � │  � │  � │  � │  � │  � ┃ #000F ╿
╽ #0010 ┃  � │  � │  � │  � │  � │  � │  � │  � ┃ #0017 ╽
╿ #0018 ┃  � │  � │  � │  � │  � │  � │  � │  � ┃ #001F ╿
EOF
i=0x1F
typeset -i1 j
typeset -Uui16 -Z7 k
while (( (k = j = ++i) <= 0xFFFD )); do
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
done
cat <<\EOF
 ┟────┴────┚ #FFFD ╿
╰───────┸────┴────┴────┴────┴────┴────┸─────────────────╯
EOF

exec >&2
echo All OK.
