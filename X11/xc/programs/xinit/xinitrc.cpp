XCOMM!/bin/sh
XCOMM $MirOS: X11/xc/programs/xinit/xinitrc.cpp,v 1.9 2007/02/19 05:30:40 tg Exp $
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
#xterm -geometry 80x24+0+0 &
whence -p twm && exec twm		# standard window manager
whence -p evilwm && exec evilwm		# shouldn't be the default
exec xterm				# last resort
