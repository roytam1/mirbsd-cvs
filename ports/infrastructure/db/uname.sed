#!/bin/sh
# $MirOS$
#-
# Copyright (c) 2004
#	Thorsten "mirabile" Glaser <x86@ePost.de>
#
# Subject to these terms, everybody who obtained a copy of this work
# is hereby permitted to deal in the work without restriction inclu-
# ding without limitation the rights to use, distribute, sell, modi-
# fy, publically perform, give away, merge or sublicence it provided
# this notice is kept and the authors and contributors are given due
# credit in derivates or accompanying documents.
#
# This work is provided "as is" with no explicit or implicit warran-
# ties whatsoever to the maximum extent permitted by applicable law;
# in no event may an author or contributor be held liable for damage
# that is, directly or indirectly, caused by the work, even if advi-
# sed of the possibility of such damage.
#-
# uname faking OpenBSD 3.4 for MirBSD #7 (eg. for schily, mozilla)

if [ -z "$1" -o x"$1" = x"-s" ]; then
	echo OpenBSD
  elif [ x"$1" = x"-r" ]; then
	echo @@OScompat@@
  else
	exec /usr/bin/uname "$@"
fi
exit 0
