#!/bin/mksh
# $MirOS: contrib/code/Snippets/mkpicidx.sh,v 1.5 2008/05/03 01:09:23 tg Exp $
#-
# Copyright (c) 2005, 2017
#	mirabilos <m@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.

title="Bildchen vom LinuxTag 2005"
copy="Copyright &copy; 2005 Thorsten Glaser. All rights reserved. Copying strictly prohibited."
let ppp=3	# Bilder pro Seite
let maxw=700

function mkfn
{
	typeset -i8 x=num
	let x+=${1:-0}
	if (( x == 0 )); then
		print -n index.htm
	else
		let x+=8#1000
		print -n index${x#8#1}.htm
	fi
}

function header
{
	cat >$name <<EOF
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
 "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en"><head>
 <meta http-equiv="content-type" content="text/html; charset=utf-8" />
 <meta name="RCSId" content="$MirOS: contrib/code/Snippets/mkpicidx.sh,v 1.5 2008/05/03 01:09:23 tg Exp $" />
 <title>$title (Page $num)</title>
</head><body>
<h1>$title</h1>
EOF
}

function footer
{
	prev=
	(( num > 0 )) && prev="<a href=\"$(mkfn -1)\">Vorige</a>"
	next="<a href=\"$(mkfn 1)\">N&auml;chste</a>"
	cat >>$name <<EOF
<hr />
<table><tr>
 <td>$prev</td>
 <td></td>
 <td style="text-align:right;">$next</td>
</tr><tr><td colspan="3">
 <img src="index000.png" alt="" style="width:${nwm}px;height:1px;" />
</td></tr><tr><td colspan="3">
 $copy
</td></tr></table>
</body></html>
EOF
}

function addpic
{
	dim="$(rdjpgcom -verbose $1 2>/dev/null | fgrep 'w * ' \
	    | sed 's!JPEG image is \([0-9]*\)w . \([0-9]*\).*$!\1 \2!')"
	let w=${dim% *}
	let nw=w
	let h=${dim#* }
	let nh=h
	let f=1

	while (( nw > maxw )); do
		case $f {
		1)	let nw='w*2/3'
			let nh='h*2/3'
			;;
		*)	let nw=w/f
			let nh=h/f
			;;
		}
		let f++
	done
	(( nwm < nw )) && let nwm=nw

	com=
	if [[ -e ${1%JPG}dsc ]]; then
		com="$(<${1%JPG}dsc)"
	elif (( int == 1 )); then
		eval $v $1
		read com?"Comment: "
		[[ -n $com ]] && print -nr -- "$com" >${1%JPG}dsc
	fi
	[[ -n $com ]] || com="Some witty comment"

	print "<p></p><table><tr><td colspan=\"3\">" >>$name
	print " <a href=\"$1\">" >>$name
	print "  <img src=\"$1\" alt=\"[$1]\"" >>$name
	print "   style=\"border-style:none;width:${nw}px;height:${nh}px;\" />" >>$name
	print " </a>" >>$name
	print "</td></tr><tr><td>$pics. <a href=\"$1\">" >>$name
	print " $com" >>$name
	print "</a></td><td></td><td style=\"text-align:right;\">" >>$name
	print " <span style=\"color:#999999\">$1</span>" >>$name
	print "</td></tr></table>" >>$name
	print >>$name
}


let num=0
let pics=0
let nwm=0
let int=0
if [[ $1 = -i ]]; then
	let int=1
	v="$2"
	[[ -n $v ]] || v="xloadimage -global -shrink"
fi
name=index.htm

rm -f index*
header
let newf=0

for f in *JPG; do
	if (( newf == 1 )); then
		footer
		let num++
		name=$(mkfn)
		header
		let newf=0
	fi
	addpic $f
	let pics++
	((( pics % ppp ) == 0 )) && let newf=1
done

footer
print '/N.auml;chste/d\nwq' | ed -s $name
printf '\x89\x50\x4E\x47\x0D\x0A\x1A\x0A\x00\x00\x00\x0D\x49\x48\x44\x52\x00\x00\x00\x01\x00\x00\x00\x01\x01\x00\x00\x00\x00\x37\x6E\xF9\x24\x00\x00\x00\x02\x74\x52\x4E\x53\x00\x00\x76\x93\xCD\x38\x00\x00\x00\x0A\x49\x44\x41\x54\x08\xD7\x63\x60\x00\x00\x00\x02\x00\x01\xE2\x21\xBC\x33\x00\x00\x00\x00\x49\x45\x4E\x44\xAE\x42\x60\x82' >index000.png
exit 0
