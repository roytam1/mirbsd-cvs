#!/bin/mksh
rcsid='$MirOS: src/sys/arch/sparc/stand/bootxx/mkbxinst.sh,v 1.18 2009/07/24 16:45:11 tg Exp $'
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
# Create a self-installing bootxx for sparc (32 bit).
# Arguments: $1 = a.out (sparc OpenBOOT) bootxx, linked
# Output: shell script to stdout

function die {
	rv=$1; shift
	print -u2 -- "$@"
	exit $rv
}

[[ -s $1 ]] || die 1 Cannot read input file "'$1'"

T=$(mktemp /tmp/bxinst.XXXXXXXXXX) || die 1 Cannot create temporary file
trap 'rm -f $T ; exit 0' 0
trap 'rm -f $T ; exit 1' 1 2 3 5 13 15

nm --target=a.out-sunos-big $1 |&
while read -p adr typ sym; do
	[[ $sym = @(_block_start|_start) ]] || continue
	eval typeset -i10 sym$sym=0x\$adr
done

set -A sect_text -- $(objdump -wh --target=a.out-sunos-big $1 | fgrep .text)
(( fofs_text = 0x${sect_text[5]} ))

typeset -Uui10 ofs tblsz
(( ofs = sym_block_start - sym_start + fofs_text ))
strip -F a.out-sunos-big -s -o $T $1
tblsz=$(dd if=$T bs=1 skip=$ofs count=4 2>/dev/null | \
    hexdump -ve '"0x" 4/1 "%02X"')
part1=$(dd if=$T bs=1 skip=8 count=$((ofs - 8)) 2>/dev/null | \
    hexdump -ve '1/1 "\\0%o"' | sed 's/\\00*/\\0/g')
part2=$(dd if=$T bs=1 skip=$((ofs + tblsz * 4 + 8)) 2>/dev/null | \
    hexdump -ve '1/1 "\\0%o"' | sed 's/\\00*/\\0/g')

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
# Self-installing 32-bit sun4m/sun4c boot blocks for MirOS BSD/sparc
# Reads a list of extents (firstblock lastblock) from standard input
# and writes bootxx to standard output, which can subsequentially be
# stored past the SunOS disklabel directly on the disc.

set -A pbs_thecode 0x66 0x31 0xC0 0x66 0x50 0x66 0x9D 0x05 0xA0 0x07 0x8E 0xD0 0xBC 0xFC 0xFF 0xFB 0x50 0x68 0x24 0x00 0x8E 0xD8 0x8E 0xC0 0x31 0xFF 0xBE 0x00 0x02 0xB9 0x80 0x00 0xF3 0x66 0xA5 0xCB 0xB8 0x01 0x02 0xBB 0x00 0x02 0xB9 0x19 0x00 0xB6 0x00 0x60 0xCD 0x13 0x61 0x73 0x08 0x60 0x31 0xC0 0xCD 0x13 0x61 0xEB 0xF2 0xEA 0x00 0x7C 0x00 0x00
typeset -Uui8 pbs_thecode
typeset -i pbs_ofs_sector=43 pbs_curptr=66

function pbs_output {
	typeset ostr=
	typeset -i psz cylno

	# fill the block table
	(( pbs_thecode[pbs_ofs_sector] = $1 + 1 ))
	while (( pbs_curptr < 126 )); do
		(( pbs_thecode[pbs_curptr++] = RANDOM & 0xFF ))
	done

	# create the Sun disklabel
	while (( pbs_curptr < 512 )); do
		pbs_thecode[pbs_curptr++]=0
	done

	# rpm
	pbs_thecode[420]=0x01
	pbs_thecode[421]=0x2C
	# pcyl
	(( pbs_thecode[422] = (g_code[0] >> 8) & 0xFF ))
	(( pbs_thecode[423] = g_code[0] & 0xFF ))
	# interleave
	pbs_thecode[431]=1
	# ncyl
	(( pbs_thecode[432] = (g_code[0] >> 8) & 0xFF ))
	(( pbs_thecode[433] = g_code[0] & 0xFF ))
	# ntrk
	(( pbs_thecode[436] = (g_code[1] >> 8) & 0xFF ))
	(( pbs_thecode[437] = g_code[1] & 0xFF ))
	# nsec
	(( pbs_thecode[438] = (g_code[2] >> 8) & 0xFF ))
	(( pbs_thecode[439] = g_code[2] & 0xFF ))
	# sectors per drive
	(( psz = g_code[0] * g_code[1] * g_code[2] ))
	# sparc partitions
	print -u2 geometry is $psz sectors in ${g_code[0]} cylinders, \
	    ${g_code[1]} heads, ${g_code[2]} sectors per track
	(( pbs_thecode[448] = pbs_thecode[456] = pbs_thecode[464] = \
	    pbs_thecode[472] = (psz >> 24) & 0xFF ))
	(( pbs_thecode[449] = pbs_thecode[457] = pbs_thecode[465] = \
	    pbs_thecode[473] = (psz >> 16) & 0xFF ))
	(( pbs_thecode[450] = pbs_thecode[458] = pbs_thecode[466] = \
	    pbs_thecode[474] = (psz >> 8) & 0xFF ))
	(( pbs_thecode[451] = pbs_thecode[459] = pbs_thecode[467] = \
	    pbs_thecode[475] = psz & 0xFF ))
	# i386 partition
	pbs_thecode[478]=0x80
	pbs_thecode[480]=1
	pbs_thecode[482]=0x96
	(( pbs_thecode[483] = g_code[1] - 1 ))
	(( cylno = g_code[0] > 1024 ? 1023 : g_code[0] - 1 ))
	(( pbs_thecode[484] = g_code[2] | ((cylno & 0x0300) >> 2) ))
	(( pbs_thecode[485] = cylno & 0x00FF ))
	(( pbs_thecode[490] = psz & 0xFF ))
	(( pbs_thecode[491] = (psz >> 8) & 0xFF ))
	(( pbs_thecode[492] = (psz >> 16) & 0xFF ))
	(( pbs_thecode[493] = (psz >> 24) & 0xFF ))
	# magic
	pbs_thecode[508]=0xDA
	pbs_thecode[509]=0xBE
	pbs_thecode[510]=0x55
	pbs_thecode[511]=0xAA

	# fill in the hashes
	pbs_curptr=0
	while (( pbs_curptr < 126 )); do
		(( pbs_thecode[126] ^= pbs_thecode[pbs_curptr++] ))
		(( pbs_thecode[127] ^= pbs_thecode[pbs_curptr++] ))
	done
	pbs_curptr=128
	while (( pbs_curptr < 512 )); do
		(( pbs_thecode[126] ^= pbs_thecode[pbs_curptr++] ))
		(( pbs_thecode[127] ^= pbs_thecode[pbs_curptr++] ))
	done

	# create the output string
	pbs_curptr=0
	while (( pbs_curptr < 512 )); do
		ostr=$ostr\\0${pbs_thecode[pbs_curptr++]#8#}
	done
	print -n "$ostr"
}

function out_int32 {
	typeset -Uui16 value=$1
	typeset -Uui8 ba bb bc bd

	(( ba = (value >> 24) & 0xFF ))
	(( bb = (value >> 16) & 0xFF ))
	(( bc = (value >> 8) & 0xFF ))
	(( bd = value & 0xFF ))
	print -n "\\0${ba#8#}\\0${bb#8#}\\0${bc#8#}\\0${bd#8#}"
}

EOF
print typeset -i blktblsz=$tblsz
cat <<'EOF'
set -A blktblent
typeset -i blktblent blktblnum=0 firstblock lastblock i=0 sscale=0 chainsec=-1
set -A g_code 2048 1 640

while getopts ":0:g:N:S:" ch; do
	case $ch {
	(0)	if (( (chainsec = OPTARG) < 0 || OPTARG > 62 )); then
			print -u2 Error: invalid chain sector "'$OPTARG'"
			exit 1
		fi ;;
	(g)	if [[ $OPTARG != +([0-9]):+([0-9]):+([0-9]) ]]; then
			print -u2 Error: invalid geometry code "'$OPTARG'"
			exit 1
		fi
		saveIFS=$IFS
		IFS=:
		set -A g_code -- $OPTARG
		IFS=$saveIFS ;;
	(N)	;;
	(S)	if (( (sscale = OPTARG) < 0 || OPTARG > 24 )); then
			print -u2 Error: invalid sector scale "'$OPTARG'"
			exit 1
		fi ;;
	(*)	print -u2 'Syntax:
	bxinst [-0 secno [-g C:H:S]] [-S scale] <blocklist >loader
Default scale=0, geometry: 2048 cyls 1 head 640 secs, suggest secno=24'
		exit 1 ;;
	}
done
shift $((OPTIND - 1))

# if desired, output chain sector (MBR) including partition and Sun disklabel
(( chainsec >= 0 )) && pbs_output $chainsec

# zero-initialise the block array
while (( i < blktblsz )); do
	blktblent[i++]=0
done

# read in the extents
while read firstblock lastblock junk; do
	while (( firstblock <= lastblock )); do
		(( blktblent[blktblnum++] = firstblock++ << sscale ))
	done
	if (( blktblnum > blktblsz )); then
		print -u2 Error: too many blocks, maximum $blktblsz
		exit 1
	fi
done

# verbose output
i=0
print -nu2 "using $blktblnum blocks of size $((512 << sscale)):"
while (( i < blktblnum )); do
	print -nu2 " ${blktblent[i++]}"
done
print -u2 .

# Part 1
EOF
print -r "print -n '\01\03\01\07\060\0200\0\07$part1'"
cat <<'EOF'

# The Block Table
out_int32 $blktblnum
out_int32 $((512 << sscale))
i=0
while (( i < blktblsz )); do
	out_int32 ${blktblent[i++]}
done

# Part 2
EOF
print -r "print -n '$part2'"
print exit 0
exit 0
