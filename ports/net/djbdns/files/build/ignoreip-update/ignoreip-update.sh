#!/bin/sh
# $MirOS: ports/net/djbdns/files/ignoreip-update,v 1.1.7.1 2005/03/18 15:48:07 tg Exp $
#-
# update-ignoreip version 0.1
# Written by J.P. Larocque, <piranha@thoughtcrime.us>, OpenPGP 0x0c14cdda
# This software is in the public domain.
#
# This script is intended for djbdns users that have applied Russell
# Nelson's patch to circumvent wildcard A records in TLDs:
#
#     http://tinydns.org/djbdns-1.05-ignoreip2.patch
#
# This script will try the wildcard name for each TLD in the
# 'stupid_tlds' variable (eg, '*.com', '*.cx', etc.).  For those
# addresses that resolve, they get added to your dnscache
# 'root/ignoreip' file, and dnscache is restarted.
#
# Run this script from your dnscache directory.  This script depends
# on a proper PATH.  Old 'root/ignoreips' entries are kept (and dups
# removed), so you can add this program to a cron job to keep ahead
# of new bogus redirection addresses added by Verisign and other TLD
# operators.
#
# Adding this script to a cron job was its intended purpose, but
# please don't do so without understanding how it works and what could
# happen if it breaks.
#
# The latest version of this program can be found at the URL:
#       http://ely.ath.cx/~piranha/software/ignoreip-update/

if [ x"$1" = x"-v" ]; then
	verbose=1
	shift
  else
	verbose=''
	[ -z "$1" -a ! -z "$2" ] && shift
fi

if [ -z "$1" ]; then
	stupid_tlds='ac cc com cx museum net nu ph sh tm ws'
  else
	stupid_tlds="$@"
fi
ignoreip='root/ignoreip'

set -e

me="$(basename "$0")"

if [ ! -d 'root' ]; then
	echo "${me}: run me from the dnscache directory" >&2
	exit 1
fi

# I originally implemented this with random names, then realized all
# the current $stupid_tlds answer to "*.$stupid_tld" just like any
# other random name.  This code may be useful in the future, if an
# arms race of sorts develops.  (Sigh.)

#if which md5sum >/dev/null 2>&1; then
#	hash_prog=md5sum
#  elif which md5 >/dev/null 2>&1; then
#	hash_prog=md5
#  else
#	echo "${me}: can't find a suitable hash program" >&2
#	exit 1
#fi

temp1="$(mktemp "ignoreip-update-$$-1-XXXXXXXXXX")" || exit 1
temp2="$(mktemp "ignoreip-update-$$-2-XXXXXXXXXX")" || { rm -f $temp1; exit 1; }
trap 'rm -f "$temp1" "$temp2"' EXIT

## Generate random name
#rand="$(dd if=/dev/arandom bs=16 count=1 2> /dev/null | "$hash_prog")"

# Do lookups on random addresses; break into one addres/line; remove
# empty lines
for stupid_tld in $stupid_tlds; do
	#dnsip "${rand}.${stupid_tld}"
	dnsip "*.${stupid_tld}"
done | xargs -n 1 echo | fgrep '.' > "$temp1"

# Abort if there were no new bogus addresses
[ ! -s "$temp1" ] && exit

# Remove duplicates (from old list and, eg, .sh/.tm)
touch "$ignoreip"
sort "$ignoreip" "$temp1" | uniq > "$temp2"

if [ "$verbose" ]; then
	diff -u "$ignoreip" "$temp2" || true
fi

# Update list and restart dnscache
chmod 644 "$temp2"
rm -f "$ignoreip"
mv "$temp2" "$ignoreip"
svc -t .
