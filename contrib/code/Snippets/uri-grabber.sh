#!/usr/bin/env mksh
# $MirOS: contrib/code/Snippets/uri-grabber.sh,v 1.2 2008/05/03 01:09:24 tg Exp $
#-
# Copyright (c) 2007, 2011
#	Thorsten Glaser <tg@mirbsd.de>
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
#-
# Grab URIs (RFC 2396) from stdin and output them, one per line. May
# contain false positives / negatives but has been tested. Requested
# to code by Vutral. No support for mailto: at the moment.

while read line; do
	while [[ $line = *@(http|https|ftp)://* ]]; do
		beg=${line%%://*}
		case $beg {
		(*http)	 beg=http ;;
		(*https) beg=https ;;
		(*ftp)	 beg=ftp ;;
		(*)	 continue ;;
		}
		line=${line#*://}
		p2=${line%%@([!#0-9a-zA-Z;/?:@&=+$,_.!~*\'()%-])*}
		line=${line#${p2}?}
		print "$beg://$p2"
	done
done
