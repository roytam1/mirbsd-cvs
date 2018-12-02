#!/bin/mksh
rcsid='$MirOS: contrib/hosted/tg/uni.mk,v 1.8 2018/08/10 01:47:02 tg Exp $'
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
#-
# Copyright © 1991-2018 Unicode, Inc. All rights reserved. Distributed
# under the Terms of Use in: http://www.unicode.org/copyright.html
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of the Unicode data files and any associated documentation (the
# "Data Files") or Unicode software and any associated documentation
# (the "Software") to deal in the Data Files or Software without
# restriction, including without limitation the rights to use, copy,
# modify, merge, publish, distribute, and/or sell copies of the Data
# Files or Software, and to permit persons to whom the Data Files or
# Software are furnished to do so, provided that either (a) this
# copyright and permission notice appear with all copies of the Data
# Files or Software, or (b) this copyright and permission notice appear
# in associated Documentation.
#
# THE DATA FILES AND SOFTWARE ARE PROVIDED "AS IS", WITHOUT WARRANTY
# OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
# AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE
# COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR
# ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR
# ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
# PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
# TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THE DATA FILES OR SOFTWARE.
#
# Except as contained in this notice, the name of a copyright holder
# shall not be used in advertising or otherwise to promote the sale,
# use or other dealings in these Data Files or Software without
# prior written authorization of the copyright holder.

mis=0
chkfile() {
	[[ ! -s $1 ]] || return 0
	print -ru2 -- "E: $1 is missing"
	mis=1
}
chkfile EastAsianWidth.txt
chkfile UnicodeData.txt
chkfile Unihan_Readings.txt
(( mis == 0 )) || exit 1

. "$(dirname "$0")/progress-bar"

fgrep kDefinition Unihan_Readings.txt >JamoBMP.txt
Pucd=$(wc -l <UnicodeData.txt)
(( Pbmp = Pucd * 2 / 3 ))
Phan=$(wc -l <JamoBMP.txt)
Pjamo=11172
(( Pbmp = Pucd / 2 + Phan + Pjamo ))
(( Pucd += Phan + Pjamo ))
Psort=10001
Pgrep=5001
Puni=3957
init_progress_bar $((Pucd + Psort + Pgrep + Pbmp*2 + Pucd + Puni))

gen=\$miros${rcsid#?MirOS}
vsn=$(sed -n '1s/^.*Width-\(.*\)\.txt.*$/\1/p' <EastAsianWidth.txt)
vun=$(sed -n '/^# Unicode version: /{s///p;q;}' <Unihan_Readings.txt)
if [[ $vun != "$vsn" ]]; then
	print -ru2 "E: UCD and Unihan versions differ!"
	exit 1
fi
typeset -Uui16 -Z11 cp
set -U
set -A jamo_initial -- G GG N D DD R M B BB S SS '' J JJ C K T P H
set -A jamo_medial -- A AE YA YAE EO E YEO YE O WA WAE OE YO U WEO WE WI YU EU YI I
set -A jamo_final -- '' G GG GS N NI NH D L LG LM LB LS LT LP LH \
    M B BS S SS NG J C K T P H
print -ru2 -- "I: reading UCD"
while IFS= read -r line; do
	cp=16#${line%%;*}
	line=${line#*;}
	if [[ $line != *'<Hangul Syllable, First>'* ]]; then
		print -r -- "${cp#16#};$line"
		draw_progress_bar
		continue
	fi
	print -ru2 -- "I: generating Jamo"
	line=${line#*;}
	IFS=';' read -r endcode x
	let endc=0x$endcode
	let begc=cp--
	while (( ++cp <= endc )); do
		(( j1 = cp - begc ))
		(( j3 = j1 % 28 ))
		(( j1 /= 28 ))
		(( j2 = j1 % 21 ))
		(( j1 /= 21 ))
		n1='HANGUL SYLLABLE '${jamo_initial[j1]}${jamo_medial[j2]}${jamo_final[j3]}
		print -r -- "${cp#16#};$n1;$line"
		draw_progress_bar
	done
	print -ru2 -- "I: back to UCD"
done <UnicodeData.txt >JamoData.txt

print -ru2 -- "I: reading CJK"
while IFS='	' read u k d; do
	[[ $k = kDefinition ]] || continue
	[[ $u = U[+-]+([0-9A-F]) ]] || continue
	cp=16#${u#U?}
	print -r -- "${cp#16#};[UkD] $d"
	draw_progress_bar
done <JamoBMP.txt >>JamoData.txt
print -ru2 -- "I: sorting data"
sort -o JamoData.txt JamoData.txt
let _cur_progress_bar+=Psort-1; draw_progress_bar
sed '/^00010000/,$d' <JamoData.txt >JamoBMP.txt
let _cur_progress_bar+=Pgrep-1; draw_progress_bar

Pucd=$(wc -l <JamoData.txt)
Pbmp=$(wc -l <JamoBMP.txt)
Phan=0
Pjamo=0
redo_progress_bar $((Pucd + Psort + Pgrep + Pbmp*2 + Pucd + Puni))

print -ru2 -- "I: generating HTML"
exec >unidata.htm
cat <<EOF
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
 "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en"><head>
 <meta http-equiv="content-type" content="text/html; charset=ISO_646.irv:1991" />
 <meta http-equiv="Content-Style-Type" content="text/css" />
 <meta name="MSSmartTagsPreventParsing" content="TRUE" />
 <title>ISO 10646 (BMP)</title>
 <meta name="RCSId" content="$rcsid" />
 <meta name="generator" content="$gen" />
</head><body>
<h1>The Universal Coded Character Set $vsn (Basic Multilingual Plane)</h1>
<table style="table-layout:fixed; border:0px; padding:0px;">
EOF
td='<td style="width:3em;">'
while IFS= read -r line; do
	typeset -i10 x=0x${line:4:4}
	(( x = (x < 32) || (x >= 0x7F && x <= 0x9F) || \
	    (x >= 0xD800 && x <= 0xDFFF) || \
	    (x >= 0xEF80 && x <= 0xEFFF) || (x > 0xFFFD) ? 0 : x ))
	line=${line//'&'/'&amp;'}
	line=${line//'<'/'&lt;'}
	line=${line//'>'/'&gt;'}
	y=
	(( x )) && y="&#$x;"
	print -r -- "<tr>$td$y</td><td>U+${line:4}</td></tr>"
	td='<td>'
	draw_progress_bar
done <JamoBMP.txt
print -r -- '</table>'
print -r -- '</body></html>'

print -ru2 -- "I: generating BMP"
exec >unidata.txt
asn=
eqlen=${%vsn}
while (( eqlen-- )); do
	asn+==
done
print -r -- "The Universal Coded Character Set $vsn Basic Multilingual Plane"
print -r -- "==================================$asn========================="
print
while IFS= read -r line; do
	typeset -Uui16 -Z7 x=0x${line:4:4}
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
	print -r -- " ${line:9}"
	draw_progress_bar
done <JamoBMP.txt
print
print _______________________________________________________________________
print -r -- "$rcsid"
print -r -- "$gen"

print -ru2 -- "I: generating SMP"
exec >uni_smp.txt
exec 4>uni_acronyms
print -ru4 -- " From ${gen#?}"
print -ru4 -- " From ucd: $vsn"
print -r -- "The Universal Coded Character Set $vsn (all planes)"
print -r -- "==================================$asn============="
print
typeset -i1 j
while IFS= read -r line; do
	typeset -Uui16 -Z11 wi=0x${line::8}
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
	line=${line:9}
	print -r -- "$line"
	print -ru4 -- "$aO$line"
	draw_progress_bar
done <JamoData.txt
print
print ______________________________________________________________________
print -r -- "$rcsid"
print -r -- "$gen"
exec 4>&-

print -ru2 -- "I: generating U"
exec >utf-8
asn=
eqlen=${%vsn}
while (( eqlen-- )); do
	asn+=┄
done
cat <<EOF
┋ $rcsid
┋ $gen

The Universal Coded Character Set $vsn Basic Multilingual Plane
┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄$asn┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄

The width of these characters have been derived from
MirBSD’s new wcwidth code and thus, this file should
show up fine in an uxterm on MirOS (see xterm(1) for
further reference). This is a generated file, see a‐
bove for the RCS ID of the generator script and read
it for the licence terms on this file. Please credit
mirabilos in derivative works, if possible.

Combining characters with single-cell width are pre‐
fixed by two spaces in the table below. Places where
a C0 and C1 control character would appear show FFFD
as the replacement character instead, again indented
by two spaces instead of one, to denote this.

Now have fun copying and pasting, although be remin‐
ded to either use a recent version of xterm to do a‐
way with cut buffers or keep the selection active in
the source window during pasting; alternatively, use
an editor like jupp: http://www.mirbsd.org/jupp.htm
▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁
EOF
# NOTE: these are manually synchronised with acronyms,v
# specifically: KAPITÄLCHEN, SCRIPT, SUBSCRIPT, SUPERSCRIPT
cat <<EOF

s̲̲u̲p̲e̲r̲s̲c̲r̲i̲p̲t̲,̲ ̲s̲u̲b̲s̲c̲r̲i̲p̲t̲,̲ ̲K̲a̲p̲i̲t̲ä̲l̲c̲h̲e̲n̲ ̲a̲n̲d̲ ̲o̲t̲h̲e̲r̲ ̲s̲c̲r̲i̲p̲t̲

U ᵃᵇᶜᵈᵉᶠᵍʰⁱʲᵏˡᵐⁿᵒᵖ⁚ʳˢᵗᵘᵛʷˣʸᶻ⁰¹²³⁴⁵⁶⁷⁸⁹⁺⁻⁼⁽⁾
D ₐ⁚⁚⁚ₑ⁚⁚ₕᵢⱼₖₗₘₙₒₚ⁚ᵣₛₜᵤᵥ⁚ₓ⁚⁚₀₁₂₃₄₅₆₇₈₉₊₋₌₍₎

U ᴬᴮ⁚ᴰᴱ⁚ᴳᴴᴵᴶᴷᴸᴹᴺᴼᴾ⁚ᴿ⁚ᵀᵁⱽᵂ
K ᴀʙᴄᴅᴇꜰɢʜɪᴊᴋʟᴍɴᴏᴘꞯʀꜱᴛᴜᴠᴡ⁚ʏᴢ

U ᵅᵝᵞᵟᵋᶿᶥᶲ ᵠᵡ ªº C( ͣ ͨ ͩ ͤ ᷚ ᷛ ͪ ͥ ᷜ ᷝ ᷞ ͫ ᷟ ᷠ ᷡ ͦ ͬ ᷢ ᷤ ᷥ ͭ ͧ ͮ ͯ ᷦ) ʱʴʵʶˀˁˠˤ
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
		draw_progress_bar
	fi
done
cat <<\EOF
 ┟────┴────┚ #FFFD ╿
╰───────┸────┴────┴────┴────┴────┴────┸─────────────────╯

Valid octet sequences for UTF-8/CESU-8:
• 00‥7F				(ASCII)
• C2‥DF 80‥BF			(BMP U+00A0‥U+07FF)
•    E0 A0‥BF 80‥BF		(BMP U+0800‥U+0FFF)
• E1‥EF 80‥BF 80‥BF		(BMP U+1000‥U+FFFF)
•    F0 90‥BF 80‥BF 80‥BF	(astral planes)
• F1‥F3 80‥BF 80‥BF 80‥BF	(   "     "   )
•    F4 80‥8F 80‥BF 80‥BF	(   "     "   )
UTF-8: Exclude ED followed by A0‥BF (surrogates).
CESU-8: Exclude astral planes; ensure valid surrogates.
OPTU-8: Exclude astral planes and EE followed by BE‥BF.
EOF
# Note the above are also manually synchronised (UTF-8/CESU-8/OPTU-8)

exec >&2
done_progress_bar
print -ru2 -- All OK.
