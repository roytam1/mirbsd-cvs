#!/bin/mksh
# $MirOS: src/distrib/baselive/dot.xsession,v 1.1 2006/08/19 01:29:14 tg Exp $
#-
# Copyright (c) 2006
#	Thorsten Glaser <tg@mirbsd.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# Advertising materials mentioning features or use of this work must
# display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a defect.

test x"$1" = x"failsafe" && exec xterm -geometry 80x24-0-0

test -n "$KSH_VERSION" || exec /bin/mksh "$0" "$@"

[[ -s $HOME/.Xresources ]] && xrdb -undef -load $HOME/.Xresources
[[ -s $HOME/.Xmodmap ]] && xmodmap $HOME/.Xmodmap

xclock -geometry 50x50-1+1 &

text=twm:0,evilwm-utf8:101,evilwm-latin1:102,failsafe:1
failsafe='xterm -geometry 80x24-0-0'
integer number=103
set -A wm
wm[0]=twm
wm[101]=evilwm-session
wm[102]=evilwm
wm[1]=$failsafe
if x=$(whence -p icewm-session); then
	text=$text,icewm:$number
	wm[number]=$x
	let number++
fi
if x=$(whence -p wm2); then
	text=$text,wm2:$number
	wm[number]=$x
	let number++
fi

xmessage -button $text -center -default twm -timeout 12 \
    "Choose window manager
Wait 12 seconds for default"
number=$?

WINDOWMANAGER=${wm[number]:-$failsafe}

eval exec $WINDOWMANAGER
# can't happen
eval exec $failsafe
exec /usr/X11R6/bin/xterm
