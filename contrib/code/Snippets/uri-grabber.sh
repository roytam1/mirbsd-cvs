#!/usr/bin/env mksh
# $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $
#-
# Copyright (c) 2007
#	Thorsten Glaser <tg@mirbsd.de>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# Advertising materials mentioning features or use of this work must
# display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
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
# to code by Vutral.

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
		p2=${line%%@([!#0-9a-zA-Z;/?:@&=+$._!~*\'()%-])*}
		line=${line#${p2}?}
		print "$beg://$p2"
	done
done
