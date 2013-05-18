#!/bin/mksh
# $MirOS: src/distrib/baselive/dot.xsession,v 1.12 2009/03/29 13:04:12 tg Exp $
#-
# Copyright (c) 2006, 2007, 2008, 2009
#	Thorsten Glaser <tg@mirbsd.org>
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

test x"$1" = x"failsafe" && exec /usr/X11R6/bin/xterm -geometry 80x24-0-0

PATH=/usr/bin:/bin:/usr/X11R6/bin:/usr/sbin:/sbin
export PATH
test -n "$KSH_VERSION" || exec mksh "$0" "$@"

for i in /usr/mpkg/bin /usr/local/bin ~/.etc/bin; do
	[[ -d $i/. ]] && PATH=$i:$PATH
done

[[ -s $HOME/.Xresources ]] && xrdb -undef -load $HOME/.Xresources
[[ -s $HOME/.Xmodmap ]] && xmodmap $HOME/.Xmodmap

xclock -render -update 1 -geometry 50x50-1+1 &

text=twm:0,evilwm-session:101,evilwm-bare:102,failsafe:1
failsafe='xterm -geometry 80x24-0-0'
typeset -i number=103
set -A wm
defwm=twm
wm[0]=twm
wm[101]=evilwm-session
wm[102]=evilwm
wm[1]=$failsafe
if x=$(whence -p icewm-session); then
	defwm=icewm
	text=$text,icewm:$number
	wm[number]=$x
	let number++
fi
if x=$(whence -p wm2); then
	text=$text,wm2:$number
	wm[number]=$x
	let number++
fi

xmessage -button $text -center -default $defwm -timeout 12 \
    "Choose window manager
Wait 12 seconds for default"
number=$?

WINDOWMANAGER=${wm[number]:-$failsafe}

eval exec $WINDOWMANAGER
# can't happen
eval exec $failsafe
exec /usr/X11R6/bin/xterm
