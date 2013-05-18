#!/bin/mksh
# $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $
#-
# Copyright (c) 2006, 2007
#	Thorsten Glaser <tg@mirbsd.de>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# Advertising materials mentioning features or use of this work must
# display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
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

test -n "$KSH_VERSION" || exec /bin/mksh "$0" "$@"

export PATH=/usr/bin:/bin:/usr/X11R6/bin:/usr/sbin:/sbin
for i in /usr/mpkg/bin /usr/local/bin ~/.etc/bin; do
	[[ -d $i/. ]] && PATH=$i:$PATH
done

[[ -s $HOME/.Xresources ]] && xrdb -undef -load $HOME/.Xresources
[[ -s $HOME/.Xmodmap ]] && xmodmap $HOME/.Xmodmap

xclock -render -update 1 -geometry 50x50-1+1 &

text=twm:0,evilwm-session:101,evilwm-bare:102,failsafe:1
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
