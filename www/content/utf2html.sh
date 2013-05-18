#!/bin/mksh
# $MirOS: www/content/utf2html.sh,v 1.1 2006/03/23 23:30:34 tg Exp $
#-
# Copyright (c) 2006
#	Thorsten Glaser <tg@mirbsd.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and below disclaimer are retai-
# ned in all redistributions, or reproduced in accompanying documen-
# tation or other materials provided with binary redistributions.
#
# Advertising materials mentioning features or use of this work must
# display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# a licensor, author or contributor be held liable for any indirect,
# direct (unless proven consequence of a direct fault of said person
# and intended use of this work), other damage, loss, or other issu-
# es, arising in any way out of dealing with the work, even if advi-
# sed of the possibility of such damage or existence of a defect.
#-
# bsiegert@ helper

cat "$@" \
    | iconv -f utf-8 -t ucs-2le \
    | hexdump -ve '/2 "%04x" "\n"' \
    | while read x; do
	let i=16#$x
	if (( i < 0x7f )); then
		typeset -i8 o=i
		print -n \\0${o#8#}
	else
		print -n "&#${i};"
	fi
done
