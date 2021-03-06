#!/bin/mksh
# $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $
#-
# Copyright (c) 2003
#	Thorsten Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.

function loadimage	# call xloadimage by URI
{
	for fi in "$@"; do
		if [ -e "$fi" ]; then
			xloadimage "$fi"
		  else	ftp -o - "$fi" | xloadimage stdin
		fi
	done
}
PROG=/usr/local/bin/nlynx
[ ! -x $PROG ] && PROG=$(which lynx)
[ -n "$DISPLAY" ] || exec $PROG "$@"
echo 'Browser Lynx? (N)etscape (D)illo (L)inks+ load(I)mage'
read a
if [ "$a" = "i" ]; then
	loadimage "$@"
	exit 0
fi
[ "$a" = "n" ] && PROG=netscape
[ "$a" = "l" ] && exec links -g "$@"
[ "$a" = "d" ] && PROG=dillo
exec $PROG "$@"
