#!/bin/mksh
print Content-type: text/plain
print Entropy: $RANDOM
print RCSID: '$MirOS$'
print
if [[ -z $HTTPS ]]; then
	print -n "INSECURE (non-SSL) "
else
	print -n "SSL "
	[[ -z $SSL_PROTOCOL ]] || print -nr "($SSL_PROTOCOL"
	[[ -z $SSL_CIPHER ]] || print -nr ":$SSL_CIPHER"
	print -n ") "
fi
if [[ $REMOTE_ADDR = +([0-9]).+([0-9]).+([0-9]).+([0-9]) ]]; then
	print -n "IPv4 "
elif [[ $REMOTE_ADDR = +([0-9a-fA-F:]):+([0-9a-fA-F:]) ]]; then
	print -n "IPv6 "
else
	print -n "AF_UNKNOWN "
fi
print -r "connection from [$REMOTE_ADDR]:$REMOTE_PORT
$SERVER_PROTOCOL request to [$SERVER_ADDR]:$SERVER_PORT ($SERVER_NAME)"
exit 0
