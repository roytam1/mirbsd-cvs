#!/bin/mksh
# $MirOS: src/share/misc/licence.template,v 1.6 2006/01/24 22:24:02 tg Rel $
#-
# Copyright (c) 2004
#	Thorsten Glaser <tg@mirbsd.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# All advertising materials mentioning features or use of this soft-
# ware must display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a nontrivial bug.
#-
# Generate "ipscript" to stdout

sent_hdr=no
cd "$(dirname "$0")"

for f in U-*.txt; do
	[[ -e $f ]] || exit 1
	if [[ $sent_hdr = no ]]; then
		sent_hdr=yes
		print -n 'sed'
	fi
	user=$(print $f | sed -e s/U-/@/ -e s/.txt/@/)
	if [[ -s $f ]]; then
		ip=$(head -1 $f)
		[[ $ip = +([0-9]).+([0-9]).+([0-9]).+([0-9]) ]] \
		    || ip=0.0.0.0
	else
		ip=0.0.0.0
	fi

	if [[ $ip = 0.0.0.0 ]]; then
		print -n " \\\\\n\\t-e '/${user}/d'"
	else
		print -n " \\\\\n\\t-e 's/${user}/${ip}/g'"
	fi
done

[[ $sent_hdr = no ]] && exit 1

print
exit 0
