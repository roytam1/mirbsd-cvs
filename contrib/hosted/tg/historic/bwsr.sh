#!/bin/sh -
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
