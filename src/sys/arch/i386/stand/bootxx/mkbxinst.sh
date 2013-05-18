#!/bin/mksh
# $MirOS: src/sys/arch/i386/stand/bootxx/mkbxinst.sh,v 1.3 2007/10/20 22:40:18 tg Exp $
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
# Create a self-installing bootxx for i386.
# Arguments: $1 = ELF bootxx, linked
# Output: shell script to stdout

rcsid='$MirOS: src/sys/arch/i386/stand/bootxx/mkbxinst.sh,v 1.3 2007/10/20 22:40:18 tg Exp $'

function die {
	rv=$1; shift
	print -u2 -- "$@"
	exit $rv
}

[[ -s $1 ]] || die 1 Cannot read input file "'$1'"

nm $1 |&
while read -p adr typ sym; do
	[[ $sym = @(_start|blkcnt|blktbl|bpbspt|bpbtpc|partp) ]] || continue
	eval typeset -i10 sym_$sym=0x\$adr
done

thecode=$(objcopy -O binary $1 /dev/stdout | \
    dd bs=1 skip=$sym__start count=$((sym_blktbl - sym__start)) 2>/dev/null | \
    hexdump -ve '1/1 "0x%02X "')

print '#!/usr/bin/env mksh'
print "# $rcsid"
print "# \$miros:${rcsid#*:}"
cat <<'EOF'
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
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.
#-
# Self-installing i386 boot blocks for MirOS BSD
# Reads a list of extents (firstblock lastblock) from standard input
# and writes bootxx to standard output, which can subsequentially be
# stored as partition boot record (or floppy boot sector) on disc.

EOF
print set -A thecode $thecode
print typeset -i ofs_blkcnt=$((sym_blkcnt - sym__start))
print typeset -i ofs_numheads=$((sym_bpbtpc - sym__start))
print typeset -i ofs_numsecs=$((sym_bpbspt - sym__start))
print typeset -i ofs_partp=$((sym_partp - sym__start))
print typeset -i begptr=$((sym_blktbl - sym__start))
cat <<'EOF'

typeset -Uui16 curptr=begptr
typeset -i wnum=0 wofs=0 wrec=0

function do_record {
	typeset -i blk=$1 cnt=$2
	typeset -i n=cnt+100
	typeset -Uui16 x=blk y

	(( blk && cnt )) || return

	print -u2 "$wrec @0x${curptr#16#}: ${n#1} @$blk (0x${x#16#})"

	while (( cnt )); do
		let wrec++
		(( n = blk < 0x00000100 ? 0 :
		    blk < 0x00010000 ? 1 :
		    blk < 0x01000000 ? 2 : 3 ))
		(( x = cnt < 33 ? cnt : 32 ))
		(( thecode[curptr++] = (n << 5) | (x - 1) ))
		(( y = blk ))
		(( blk += x ))
		(( cnt -= x ))
		(( n++ ))
		while (( n-- )); do
			(( thecode[curptr++] = y & 0xFF ))
			(( y >>= 8 ))
		done
	done
}

function record_block {
	typeset -i sv blk=$1

	if (( !blk || (wofs && blk != (wofs + wnum)) )); then
		# flush the blocks from the cache
		if (( wnum )); then
			if (( (sv = wofs % numsecs) < (numsecs - 1) )); then
				(( sv = numsecs - sv ))
				(( sv = sv > wnum ? wnum : sv ))
				do_record $wofs $sv
				let wofs+=sv wnum-=sv
			fi

			while (( wnum > numsecs )); do
				do_record $wofs $numsecs
				let wofs+=numsecs wnum-=numsecs
			done

			(( wnum )) && do_record $wofs $wnum
		fi
		let wofs=0 wnum=0
	fi
	if (( blk )); then
		# record some new block into the cache
		(( wofs )) || let wofs=blk
		(( wnum += 1 << sscale ))
	fi
}

typeset -i flag_one=0 partp=0 numheads=0 numsecs=0 sscale=0

while getopts ":0:1h:p:S:s:" ch; do
	case $ch {
	(0)	;;
	(1)	flag_one=1 ;;
	(h)	if (( (numheads = OPTARG) < 1 || OPTARG > 256 )); then
			print -u2 warning: invalid head count "'$OPTARG'"
			numheads=0
		fi ;;
	(p)	if (( (partp = OPTARG) < 1 || OPTARG > 255 )); then
			print -u2 warning: invalid partition type "'$OPTARG'"
			partp=0
		fi ;;
	(S)	if (( (sscale = OPTARG) < 0 || OPTARG > 24 )); then
			print -u2 error: invalid input scale "'$OPTARG'"
			exit 1
		fi ;;
	(s)	if (( (numsecs = OPTARG) < 1 || OPTARG > 63 )); then
			print -u2 warning: invalid sector count "'$OPTARG'"
			numsecs=0
		fi ;;
	(*)	cat >&2 <<'EOD'
Syntax:
	bxinst [-1] [-h heads] [-p partitiontype] [-S scale]
	    [-s sectors] <sectorlist | dd of=image conv=notrunc
Default values: heads=16 sectors=63 partitiontype=0x27 scale=0
EOD
		exit 1 ;;
	}
done
shift $((OPTIND - 1))

if (( !numheads )); then
	print -u2 warning: using default value of 16 heads
	numheads=16
fi

if (( !numsecs )); then
	print -u2 warning: using default value of 63 sectors
	numsecs=63
fi

# read in the extents
while read firstblock lastblock junk; do
	while (( firstblock <= lastblock )); do
		record_block $((firstblock++ << sscale))
	done
done
record_block 0	# just flush
print -u2 "using $wrec blocks, $((curptr-begptr)) bytes ($((510-curptr)) free)"

# fill the block table
if (( curptr > 510 )); then
	print -u2 error: too many blocks
	exit 1
fi
while (( curptr < 510 )); do
	if (( (curptr & 0xFCF) == 0x1C2 )); then
		(( thecode[curptr++] = 0 ))
	else
		(( thecode[curptr++] = RANDOM & 0xFF ))
	fi
done
(( thecode[curptr++] = 0x55 ))
(( thecode[curptr++] = 0xAA ))

# fill in other data
(( thecode[ofs_blkcnt] = wrec ))
(( thecode[ofs_numheads] = numheads & 0xFF ))
(( thecode[ofs_numheads + 1] = numheads >> 8 ))
(( thecode[ofs_numsecs] = numsecs ))
(( flag_one )) && (( thecode[ofs_numsecs + 1] = 0x80 ))
(( thecode[ofs_partp] = partp ))

# create the output string
ostr=
curptr=0
typeset -Uui8 vo
while (( curptr < 512 )); do
	(( vo = thecode[curptr++] ))
	ostr="$ostr\\0${vo#8#}"
done

# over and out
print -n "$ostr"
exit 0
EOF
exit 0
