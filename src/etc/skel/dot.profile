# $MirOS: src/etc/skel/dot.profile,v 1.4 2005/07/23 15:00:35 tg Exp $
# $OpenBSD: dot.profile,v 1.4 2005/02/16 06:56:57 matthieu Exp $
#
# sh/ksh/mksh/bash initialisation

if [ -z "$USER_ID" ]; then
	# Do this only if /etc/profile has _not_ yet run!
	PATH=$HOME/bin:/bin:/sbin:/usr/bin:/usr/sbin:/usr/X11R6/bin:/usr/local/bin:/usr/local/sbin:/usr/games:/usr/mpkg/bin
	export PATH HOME TERM
fi

# Add local stuff here:
