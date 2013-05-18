#!/bin/mksh
print Content-type: image/png
print Entropy: $RANDOM
print RCSID: '$MirOS: contrib/hosted/tg/conninfo.cgi,v 1.2 2008/11/09 01:29:27 tg Exp $'
print
p=/usr/local/bin
[[ -d /apps/. ]] && p=/apps
if [[ -z $HTTPS ]]; then
	s="INSECURE (non-SSL)"
else
	s="SSL "
	[[ -z $SSL_PROTOCOL ]] || s="$s($SSL_PROTOCOL"
	[[ -z $SSL_CIPHER ]] || s="$s:$SSL_CIPHER"
	s="$s)"
fi
if [[ $REMOTE_ADDR = +([0-9]).+([0-9]).+([0-9]).+([0-9]) ]]; then
	s="$s IPv4"
elif [[ $REMOTE_ADDR = +([0-9a-fA-F:]):+([0-9a-fA-F:]) ]]; then
	s="$s IPv6"
else
	s="$s AF_UNKNOWN"
fi
s="$s connection from [$REMOTE_ADDR]:$REMOTE_PORT"
t="$SERVER_PROTOCOL request to [$SERVER_ADDR]:$SERVER_PORT ($SERVER_NAME)"
exec $p/asctopng "$s" "$t"
