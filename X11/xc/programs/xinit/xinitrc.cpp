XCOMM!/bin/sh
XCOMM $MirOS: X11/xc/programs/xinit/xinitrc.cpp,v 1.8 2007/01/29 01:31:30 tg Exp $
XCOMM $Xorg: xinitrc.cpp,v 1.3 2000/08/17 19:54:30 cpqbld Exp $

userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=XINITDIR/.Xresources
sysmodmap=XINITDIR/.Xmodmap

XCOMM merge in defaults and keymaps

if [ -f $sysresources ]; then
	xrdb -merge $sysresources
fi

if [ -f $sysmodmap ]; then
	xmodmap $sysmodmap
fi

if [ -f $userresources ]; then
	xrdb -merge $userresources
fi

if [ -f $usermodmap ]; then
	xmodmap $usermodmap
fi

XCOMM start some nice programs

xclock -render -update 1 -geometry 50x50-1+1 &
xconsole -iconic &
xterm -geometry 80x24 &
sleep 1
exec twm
exec evilwm	# should not happen as default
exec xterm	# last resort
