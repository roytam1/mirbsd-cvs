# $MirOS$
# $OpenBSD: dot.profile,v 1.3 2002/06/09 06:15:15 todd Exp $
#
# sh/ksh initialization

if [ -z "$MIROS" ]; then
	# Do this only if /etc/profile has _not_ yet run!
PATH=$HOME/bin:/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:/usr/games:.
export PATH HOME TERM
fi

# Add local stuff here:
