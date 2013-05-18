#!/bin/sh
# $MirOS: contrib/samples/dot.xinitrc,v 1.1.7.1 2005/02/05 01:59:40 tg Exp $
#-
# Copyright (c) 2003, 2004, 2005
#	Thorsten "mirabile" Glaser <tg@66h.42h.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.
#-
# xinit rc file for evilwm (sample)


userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/usr/X11R6/lib/X11/xinit/.Xresources
sysmodmap=/usr/X11R6/lib/X11/xinit/.Xmodmap

# Set the CapsLock LED to show group toggle status
setxkbmap -option "grp_led:caps"

# merge in defaults and keymaps

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

# Start two status xterms
if [ -e /usr/local/lib/X11/fonts/terminus ]; then
	/usr/X11R6/bin/xterm -class TXTerm -fg black -geom 78x10+1+664 \
	    -bg slateblue -fn 6x10 -e top &
	/usr/X11R6/bin/xterm -class TXTerm -fg black -geom 90x11+475+648 \
	    -bg cornflowerblue -fn 6x10 -e tail -f /var/log/messages &
  else
	/usr/X11R6/bin/xterm +sb -fg black -geom 78x10+1+637 \
	    -bg slateblue -e top &
	/usr/X11R6/bin/xterm +sb -fg black -geom 90x11+475+637 \
	    -bg cornflowerblue -e tail -f /var/log/messages &
fi

# Screen saver off
xset s off

[ -s $HOME/.xinitrc.local ] && . $HOME/.xinitrc.local

USETERM=/usr/X11R6/bin/xterm
[ -x $HOME/.etc/bin/xtm ] && USETERM=$HOME/.etc/bin/xtm

[ -n "$WINDOWMANAGER" ] && exec $WINDOWMANAGER $WMOPTS
WMOPTS="-term $USETERM -snap 3 $WMOPTS"
[ -x /usr/X11R6/bin/evilwm ] && exec /usr/X11R6/bin/evilwm $WMOPTS
[ -x /usr/local/bin/evilwm ] && exec /usr/local/bin/evilwm $WMOPTS
exec $USETERM
