XCOMM!/bin/mksh
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

XCOMM if we have private ssh key(s), start ssh-agent and add the key(s)
id1=$HOME/.ssh/identity
if [ -x /usr/bin/ssh-agent ] && [ -f $id1 -o -f $id2 -o -f $id3 ]; then
	eval $(ssh-agent -s)
	ssh-add $id1 </dev/null
fi

XCOMM start some nice programs

xclock -geometry 50x50-1+1 &
xconsole -iconic &
xterm -geometry 80x24 &
twm || evilwm || xterm

if [ "$SSH_AGENT_PID" ]; then
	ssh-add -D </dev/null
	eval $(ssh-agent -s -k)
fi
