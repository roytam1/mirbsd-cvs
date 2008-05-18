#!/usr/bin/env mksh
# $MirOS: src/share/misc/licence.template,v 1.24 2008/04/22 11:43:31 tg Rel $
#-
# Copyright (c) 2008
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
#-
# Generates a libotr private key into the current directory.

function usage {
	print -ru2 "syntax: $0 [-r <randfiles>] <jid>"
	exit 1
}

if [[ $# -eq 3 ]]; then
	[[ $1 = -r ]] || usage
	rndf=$2
	jid=$3
elif [[ $# -eq 1 ]]; then
	rndf=
	jid=$1
else
	usage
fi

if [[ $jid != +([a-zA-Z0-9!#\$%&\'*+/=?^_{\|}~-])*(.+([a-zA-Z0-9!#\$%&\'*+/=?^_{\|}~-]))@*([a-zA-Z0-9]?(*([a-zA-Z0-9-])[a-zA-Z0-9]).)[a-zA-Z0-9]?(*([a-zA-Z0-9-])[a-zA-Z0-9]) ]]; then
	print -ru2 "not a valid RFC2822 address: '$jid'"
	usage
fi

integer curline=0
set -A lines

if [[ -z $rndf ]]; then
	openssl dsaparam -noout -genkey 1024
else
	openssl dsaparam -noout -rand "$rndf" -genkey 1024
fi | openssl asn1parse |&

while read -p line; do
	[[ $line = *INTEGER* ]] || continue
	if [[ ${line##*INTEGER*:} != +([0-9A-F]) ]]; then
		print -ru2 "invalid input line: '$line'"
		exit 1
	fi
	lines[curline++]=${line##*INTEGER*:}
done

if (( curline != 6 )); then
	print -u2 invalid number of input lines: $curline
	exit 1
fi

print -n >"$jid.key" || exit 255
chmod 600 "$jid.key" || exit 255
cat >"$jid.key" <<-EOF
	(privkeys
	 (account
	(name "${jid}")
	(protocol jabber)
	(private-key 
	 (dsa 
	  (p #${lines[1]}#)
	  (q #${lines[2]}#)
	  (g #${lines[3]}#)
	  (y #${lines[4]}#)
	  (x #${lines[5]}#)
	  )
	 )
	 )
	)
EOF

print -u2 "keyfile $jid.key generated successfully"
exit 0
