#!/bin/mksh
rcsid='$MirOS: src/sys/arch/i386/stand/bootxx/mkbxinst.sh,v 1.20 2009/06/07 18:00:43 tg Exp $'
#-
# Copyright (c) 2007, 2008, 2009
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
# Create a self-installing bootxx for i386 (32 bit).
# Arguments: $1 = ELF (i386) bootxx, linked
# Output: shell script to stdout

function die {
	rv=$1; shift
	print -u2 -- "$@"
	exit $rv
}

[[ -s $1 ]] || die 1 Cannot read input file "'$1'"

nm $1 |&
while read -p adr typ sym; do
	[[ $sym = @(_start|bkcnt|bktbl|geomh|geoms|partp|secsz) ]] || continue
	eval typeset -i10 sym_$sym=0x\$adr
done

T=$(mktemp /tmp/bxinst.XXXXXXXXXX) || die 255 Cannot create temporary file
objcopy -O binary $1 $T
thecode=$(dd if=$T bs=1 count=$((sym_bktbl - sym__start)) 2>/dev/null | \
    hexdump -ve '1/1 "0x%02X "')
rm -f $T

print '#!/usr/bin/env mksh'
print "# $rcsid"
print "# \$miros:${rcsid#*:}"
cat <<'EOF'
#-
# Copyright (c) 2007, 2008, 2009
#	Thorsten Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un‐
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person’s immediate fault when using the work as intended.
#-
# Self-installing 32-bit x86 boot blocks for MirOS BSD/i386
# Reads a list of extents (firstblock lastblock) from standard input
# and writes bootxx to standard output, which can subsequentially be
# stored as partition boot record (or floppy boot sector) on disc.

EOF
print set -A thecode $thecode
print typeset -i ofs_bkcnt=$((sym_bkcnt - sym__start))
print typeset -i ofs_geomh=$((sym_geomh - sym__start))
print typeset -i ofs_geoms=$((sym_geoms - sym__start))
print typeset -i ofs_partp=$((sym_partp - sym__start))
print typeset -i ofs_secsz=$((sym_secsz - sym__start))
print typeset -i begptr=$((sym_bktbl - sym__start))
cat <<'EOF'
typeset -Uui8 thecode

typeset -Uui16 curptr=begptr
typeset -i wnum=0 wofs=0 wrec=0 bkend=0x1FE

function do_record {
	typeset -i blk=$1 cnt=$2 n
	typeset -Uui16 x=blk y

	(( blk && cnt )) || return

	print -u2 "$wrec @0x${curptr#16#}: $cnt @$blk (0x${x#16#})"

	while (( cnt )); do
		let wrec++
		(( n = blk < 0x00000100 ? 0 :
		    blk < 0x00010000 ? 1 :
		    blk < 0x01000000 ? 2 : 3 ))
		(( x = cnt < 33 ? cnt : 32 ))
		(( y = blk ))
		print -u2 " - 0x${curptr#16#}: $((x)) (0x${x#16#}) @ $blk" \
		    "(0x${y#16#})"
		(( thecode[curptr++] = (n++ << 5) | (x - 1) ))
		(( blk += x ))
		(( cnt -= x ))
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
		(( wnum )) && do_record $wofs $wnum
		wofs=0
		wnum=0
	fi
	if (( blk )); then
		# record some new block into the cache
		(( wofs )) || let wofs=blk
		(( wnum += 1 << sscale ))
	fi
}

typeset -i partp=0 numheads=0 numsecs=0 sscale=0 bsh=9 mbrpno=0 mbrptp=0
set -A g_code 0 0 0

while getopts ":0:1AB:g:h:M:p:S:s:" ch; do
	case $ch {
	(0)	;;
	(1)	;;
	(A)	numheads=0
		numsecs=99
		;;
	(B)	if (( (bsh = OPTARG) < 9 || OPTARG > 15 )); then
			print -u2 error: invalid block size "2^'$OPTARG'"
			exit 1
		fi
		;;
	(g)	if [[ $OPTARG != +([0-9]):+([0-9]):+([0-9]) ]]; then
			print -u2 Error: invalid geometry code "'$OPTARG'"
			exit 1
		fi
		saveIFS=$IFS
		IFS=:
		set -A g_code -- $OPTARG
		IFS=$saveIFS ;;
	(h)	if (( (numheads = OPTARG) < 1 || OPTARG > 256 )); then
			print -u2 warning: invalid head count "'$OPTARG'"
			numheads=0
		fi ;;
	(M)	if [[ $OPTARG != +([0-9])?(:?(0[Xx])+([0-9])) ]]; then
			print -u2 warning: invalid partition info "'$OPTARG'"
			mbrpno=0
			mbrptp=0
		fi
		saveIFS=$IFS
		IFS=:
		set -A mbr_code -- $OPTARG
		IFS=$saveIFS
		(( mbrpno = mbr_code[0] ))
		(( mbrptp = mbr_code[1] ))
		if (( mbrpno < 1 || mbrpno > 4 )); then
			print -u2 warning: invalid partition number "'$OPTARG'"
			mbrpno=0
		fi
		if (( mbrptp < 1 || mbrptp > 255 )); then
			print -u2 warning: invalid partition type "'$OPTARG'"
			mbrptp=0
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
	(*)	print -u2 'Syntax:
	bxinst [-1A] [-B blocksize] [-g C:H:S] [-h heads] [-M partno(1..4)]
	    [-p partitiontype] [-S scale] [-s sectors] <sectorlist | \\
	    dd of=image conv=notrunc
Default values: blocksize=9 heads=16 sectors=63 partitiontype=0x27 scale=0
    partno=4 if -g (create MBR partition) is given; -A = auto boot geometry'
		exit 1 ;;
	}
done
shift $((OPTIND - 1))

typeset -Ui psz=0	# must be unsigned
if (( g_code[0] )); then
	# bounds check partition table values, calculate total sectors
	if (( g_code[0] < 1 || g_code[1] < 1 || g_code[1] > 256 ||
	    g_code[2] < 1 || g_code[2] > 63 )); then
		print -u2 Invalid geometry, values out of bounds.
	elif [[ $(print "(${g_code[0]} * ${g_code[1]} * ${g_code[2]})" \
	    "> 4294967295" | bc) = 1 ]]; then
		print -u2 Invalid geometry, more than 2 TiB of data.
	else
		# we know it's <= 2^32-1
		(( psz = g_code[0] * g_code[1] * g_code[2] ))
	fi
fi
if (( psz )); then
	print -u2 geometry is $psz sectors \($(print \
	    "$psz * $((1 << bsh))" | bc) bytes\) in ${g_code[0]} cylinders, \
	    ${g_code[1]} heads, ${g_code[2]} sectors per track
	if (( numsecs == 0 || (numsecs != 99 && numheads == 0) )); then
		print -u2 warning: using these values for C/H/S boot
		numheads=${g_code[1]}
		numsecs=${g_code[2]}
	fi
	(( mbrpno )) || mbrpno=4	# default partition number
fi
if (( mbrpno )); then
	bkend=0x1BE
	(( psz )) || print -u2 warning: no geometry given, will not \
	    create an MBR partition table entry
fi

if (( numsecs == 99 )); then
	numheads=0
	numsecs=0
else
	if (( !numheads )); then
		print -u2 warning: using default value of 16 heads
		numheads=16
	fi

	if (( !numsecs )); then
		print -u2 warning: using default value of 63 sectors
		numsecs=63
	fi
fi

# read in the extents
while read firstblock lastblock junk; do
	while (( firstblock <= lastblock )); do
		record_block $((firstblock++ << sscale))
	done
done
record_block 0	# just flush
print -u2 "using $wrec blocks, $((curptr-begptr)) bytes ($((bkend-curptr)) free)"

# fill the block table
if (( curptr-- > bkend )); then
	print -u2 error: too many blocks
	exit 1
fi
while (( ++curptr < bkend )); do
	(( thecode[curptr] = (curptr & 0xFCF) == 0x1C2 ? 0 : RANDOM & 0xFF ))
	# ensure the “active” flag is never set to 0x00 or 0x80
	if (( ((curptr + 2) & 0xFCF) == 0x01C0 )); then
		(( thecode[curptr] & 0x7F )) || let --curptr
	fi
done
thecode[510]=0x55
thecode[511]=0xAA

# fill in other data
(( thecode[ofs_bkcnt] = wrec ))
(( thecode[ofs_geomh] = numheads & 0xFF ))
(( thecode[ofs_geomh + 1] = numheads >> 8 ))
(( thecode[ofs_geoms] = numsecs ))
(( thecode[ofs_partp] = partp ))
print -u2 "using sectors of 2^$bsh = $((1 << bsh)) bytes"
(( thecode[ofs_secsz] = (1 << (bsh - 8)) ))

# create an MBR partition if desired
if (( psz )); then
	(( mbrpno = 0x1BE + ((mbrpno - 1) * 16) ))
	thecode[mbrpno++]=0x80
	thecode[mbrpno++]=0
	thecode[mbrpno++]=1
	thecode[mbrpno++]=0
	(( thecode[mbrpno++] = (mbrptp ? mbrptp : partp ? partp : 0x27) ))
	(( thecode[mbrpno++] = g_code[1] - 1 ))
	(( cylno = g_code[0] > 1024 ? 1023 : g_code[0] - 1 ))
	(( thecode[mbrpno++] = g_code[2] | ((cylno & 0x0300) >> 2) ))
	(( thecode[mbrpno++] = cylno & 0x00FF ))
	thecode[mbrpno++]=0
	thecode[mbrpno++]=0
	thecode[mbrpno++]=0
	thecode[mbrpno++]=0
	(( thecode[mbrpno++] = psz & 0xFF ))
	(( thecode[mbrpno++] = (psz >> 8) & 0xFF ))
	(( thecode[mbrpno++] = (psz >> 16) & 0xFF ))
	(( thecode[mbrpno++] = (psz >> 24) & 0xFF ))
fi

# create the output string
ostr=
curptr=0
while (( curptr < 512 )); do
	ostr=$ostr\\0${thecode[curptr++]#8#}
done

# over and out
print -n "$ostr"
exit 0
EOF
exit 0
