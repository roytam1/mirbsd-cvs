#!/bin/mksh
# $MirOS: src/sbin/route/route_print.sh,v 1.4 2008/11/08 23:04:01 tg Exp $
#-
# Copyright (c) 2005, 2009
#	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
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
# Display a list of all manually added (static) routes which are not
# set on the loopback interface, for IPv4 and IPv6.

#-- Functions

function reverse_route
{
	local proto=$1
	if [[ $2 = */* ]]; then
		local dest=${2%/*}
		local cidr=${2##*/}
	else
		local dest=$2
		local cidr=-
	fi
	local gw=$3
	local flags=$4
	local mtu=$5
	local iface=$6

	local cmd="/sbin/route -n add -$proto"
	if [[ $flags = *H* ]]; then
		cmd="$cmd -host"
	else
		cmd="$cmd -net"
	fi
	cmd="$cmd $dest"
	[[ $cidr = - ]] || cmd="$cmd -prefixlen $cidr"
	[[ $flags = *1* ]] && cmd="$cmd -proto1"
	[[ $flags = *2* ]] && cmd="$cmd -proto3"
	[[ $flags = *3* ]] && cmd="$cmd -proto3"
	[[ $flags = *B* ]] && cmd="$cmd -blackhole"
	[[ $flags = *C* ]] && cmd="$cmd -cloning"
	[[ $flags = *G* ]] || cmd="$cmd -iface"
	[[ $flags = *L* ]] && cmd="$cmd -llinfo"
	[[ $flags = *R* ]] && cmd="$cmd -reject"
	[[ $flags = *X* ]] && cmd="$cmd -xresolve"
	[[ $mtu = - ]] || cmd="$cmd -mtu $mtu"
	[[ $gw = - && $flags != *L* ]] \
	    && cmd="#error: $cmd"
	if [[ $flags = *L* ]]; then
		cmd="$cmd -link ${iface}:"
	else
		cmd="$cmd $gw"
	fi
	print -- $cmd
}

#-- Entry Point

tab=$(print \\t)
disp=h
imode=n
q=0
dynrt=0

while getopts "dho:rq" opt; do
	case $opt {
	d)	dynrt=1
		;;
	# h = help, *) case
	o)	imode=o
		proto=$OPTARG
		;;
	r)	disp=r
		;;
	q)	q=1
		;;
	*)	print "Usage:\tmksh route_print [-d] | column -t"
		print "\tmksh route_print -[d]r"
		print "\tnetstat -rnvf inet[6] | fgrep ..." \
		    "| mksh route_print -[dr]o inet[6]"
		exit 1
		;;
	}
done
shift $((OPTIND - 1))

[[ $disp = h && $q = 0 ]] && print Destination Gateway Flags MTU Interface
case $imode {
o)	/usr/bin/sed -e "s/^/$proto /"
	;;
n)	for proto in inet inet6; do
		/usr/bin/netstat -rnvf $proto \
		    | /usr/bin/tail +5 \
		    | /usr/bin/sed -e "s/^/$proto /"
	done
	;;
} \
    | /usr/bin/fgrep -v "${tab}expire" \
    | while read proto dest gw flags refs use mtu iface rn_dupedkey; do
	if [[ $gw = U* ]]; then
		# no gw (yet) in routing table
		rn_dupedkey="$iface $rn_dupedkey"
		iface=$mtu
		mtu=$use
		use=$refs
		refs=$flags
		flags=$gw
		gw=-
	fi
	[[ $iface = lo0 ]] && continue
	[[ $dynrt == 1 || $flags = *S* ]] || continue
	case $disp {
	h)	print -- $dest $gw $flags $mtu $iface
		;;
	r)	reverse_route $proto $dest $gw $flags $mtu $iface
		;;
	}
done
exit 0
