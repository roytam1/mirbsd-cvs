#!/bin/mksh
# $MirOS: contrib/code/Snippets/mkseed.ksh,v 1.5 2010/07/11 11:56:02 tg Exp $
#-
# Copyright (c) 2007, 2008, 2010
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
# create a random seed file for uses on other systems by compressing
# entropy from strong sources, different sources, etc., and concate-
# nating different randomness sources including srandom(4) – this is
# MirOS specific in several aspects
# use the files created by “-o «fname»” with “openssl -rand «fname»”

me=${0##*/}
integer i=$RANDOM

function usage {
	print -u2 "Usage: $me [-ru] [-o ofile] [-s size]"
	exit 1
}

integer dsiz=1024	# output file size
integer ssiz=32		# number of bytes to pull from srandom directly
ifile=/dev/srandom
ofile=/dev/stdout

while getopts ":o:rs:u" ch; do
	case $ch {
	(o)	ofile=$OPTARG ;;
	(r)	ssiz=256 ;;		# hardware RNG: use more bytes
	(s)	if [[ $OPTARG -lt 1024 || $OPTARG -gt 65536 ]]; then
			print -u2 "$me: -s $OPTARG out of bounds"
			exit 1
		fi
		dsiz=$OPTARG ;;
	(u)	ifile=/dev/urandom ;;	# unsafe mode
	(*)	usage ;;
	}
done
shift $((OPTIND - 1))

if ! T1=$(mktemp /tmp/mkseed.XXXXXXXXXX); then
	print -u2 $me: cannot create temporary file
	exit 1
fi
if ! T2=$(mktemp /tmp/mkseed.XXXXXXXXXX); then
	rm -f $T1
	print -u2 $me: cannot create temporary file
	exit 1
fi
if ! T3=$(mktemp /tmp/mkseed.XXXXXXXXXX); then
	rm -f $T1 $T2
	print -u2 $me: cannot create temporary file
	exit 1
fi
trap 'rm -Pf $T1 $T2 $T3; rm -f $T1 $T2 $T3; exit 0' 0
trap 'rm -Pf $T1 $T2 $T3; rm -f $T1 $T2 $T3; exit 1' 1 2 3 5 13 15

print -n >$T1
integer fsiz=0; print -n "0 ..."
while (( fsiz < dsiz )); do
	for algorithm in md4 md5 rmd160 sha1 sha512 tiger whirlpool; do
		x=$( (
			dd if=/dev/prandom count=1 bs=4
			dd if=/dev/arandom count=1 bs=28
			dd if=$ifile count=1 bs=36
			[[ -x /usr/libexec/cprng ]] && \
			    time /usr/libexec/cprng -pr12
			sleep $((RANDOM % 3 + 1))
		) 2>&1 >$T2 | cksum)
		RANDOM=${x%% *}
		x=$( ( (
			print $RANDOM $SECONDS $fsiz
			gzip -n9 <$T2
			sleep $((RANDOM % 3 + 1))
			date +%J+%s
		) | \
		    cksum -b -a adler32 -a sfv -a suma -a sha256 | \
		    tee /dev/stderr | \
		    dd of=$T3 bs=40 count=1 ) 2>&1 | cksum -a sysvsum)
		RANDOM=${x%% *}
		x=$( ( (
			print $RANDOM $SECONDS $fsiz
			cat $T2
			sleep $((RANDOM % 3 + 1))
			date +%J+%s
		) | \
		    openssl enc -aes-256-cbc -pass file:$T3 -salt -e -nopad | \
		    tee /dev/stderr | \
		    cksum -b -a $algorithm >>$T1 ) 2>&1 | cksum -a sum)
		RANDOM=${x%% *}
		fsiz=$(stat -f '%z' $T1); print -n "\r$fsiz ..."
	done
	( (
		print $RANDOM $SECONDS $fsiz
		dd if=$ifile bs=$ssiz count=1 >>$T1
		[[ -x /usr/libexec/cprng ]] && \
		    time /usr/libexec/cprng -pr3 >>$T1
		sleep $((RANDOM % 3 + 1))
		date +%J+%s
	) | \
		tee /dev/stderr | \
		( print $RANDOM; cat ) | \
		gzip -n9 | \
		cksum -b -a sha384 | \
		dd bs=1 count=1 >>$T1 ) >/dev/wrandom 2>&1
	fsiz=$(stat -f '%z' $T1); print -n "\r$fsiz ..."
done
(
	print $RANDOM $SECONDS $fsiz
	sync
	dd if=/dev/arandom of=$T2 count=16
	dd if=/dev/arandom of=$T3 count=16
	dd if=$T1 of=$ofile bs=$dsiz count=1
	dd if=$T1 bs=$dsiz skip=1
	dd if=/dev/arandom of=$T1 count=160
	sync
	date +%J+%s
	print $RANDOM
) >/dev/wrandom 2>&1
print "\r$dsiz ... done"
exit 0
