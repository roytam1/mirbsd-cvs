# $MirOS: src/etc/skel/dot.profile,v 1.2 2005/03/06 19:06:00 tg Exp $
# $OpenBSD: dot.profile,v 1.3 2002/06/09 06:15:15 todd Exp $
#
# sh/ksh/mksh/bash initialisation

if [ -z "$USER_ID" ]; then
	# Do this only if /etc/profile has _not_ yet run!
	PATH=$HOME/bin:/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:/usr/games:.
	export PATH HOME TERM
fi

# Add local stuff here:
