# $MirOS: src/etc/root/dot.profile,v 1.2 2005/03/06 19:05:59 tg Exp $
# $OpenBSD: dot.profile,v 1.4 2004/05/10 16:04:07 peter Exp $
#
# sh/ksh/mksh/bash initialisation

if [ -z "$USER_ID" ]; then
	# Do this only if /etc/profile has _not_ yet run!
	PATH=/sbin:/usr/sbin:/bin:/usr/bin:/usr/X11R6/bin:/usr/local/sbin:/usr/local/bin
	export PATH
	HOME=/root
	export HOME
	umask 022

	if [ -x /usr/bin/tset ]; then
		eval $(/usr/bin/tset -sQ \?$TERM)
	fi
	# End of /etc/profile replacement
fi

# Add local stuff here:
