#!/bin/mksh
# $MirOS: src/sys/arch/sparc/stand/bootxx/mkbxinst.sh,v 1.7 2008/10/20 23:15:39 tg Exp $
#-
# Copyright (c) 2007, 2008
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
# Create a self-installing bootxx for sparc.
# Arguments: $1 = a.out (sparc OpenBoot) bootxx, linked
# Output: shell script to stdout

rcsid='$MirOS: src/sys/arch/sparc/stand/bootxx/mkbxinst.sh,v 1.7 2008/10/20 23:15:39 tg Exp $'

function die {
	rv=$1; shift
	print -u2 -- "$@"
	exit $rv
}

[[ -s $1 ]] || die 1 Cannot read input file "'$1'"

T=$(mktemp /tmp/pine.smime.XXXXXXXXXX) || die 1 Cannot create temporary file
trap 'rm -f $T ; exit 0' 0
trap 'rm -f $T ; exit 1' 1 2 3 5 13 15

nm --target=a.out-sunos-big $1 |&
while read -p adr typ sym; do
	[[ $sym = @(_block_start|_start) ]] || continue
	eval typeset -i10 sym$sym=0x\$adr
done

typeset -Uui10 ofs tblsz
(( ofs = sym_block_start - sym_start + 32 ))
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
# Copyright (c) 2007, 2008
#	Thorsten Glaser <tg@mirbsd.de>
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
# Self-installing SPARC boot blocks for MirOS BSD (sun4m, sun4c)
# Reads a list of extents (firstblock lastblock) from standard input
# and writes bootxx to standard output, which can subsequentially be
# stored past the SunOS disklabel directly on the disc.

set -A pbs_thecode 0x66 0x31 0xC0 0x66 0x50 0x66 0x9D 0x05 0xA0 0x07 0x8E 0xD0 0xBC 0xFC 0xFF 0xFB 0x50 0x68 0x24 0x00 0x8E 0xD8 0x8E 0xC0 0x31 0xFF 0xBE 0x00 0x02 0xB9 0x80 0x00 0xF3 0x66 0xA5 0xCB 0xB8 0x01 0x02 0xBB 0x00 0x02 0xB9 0x19 0x00 0xB6 0x00 0x60 0xCD 0x13 0x61 0x73 0x08 0x60 0x31 0xC0 0xCD 0x13 0x61 0xEB 0xF2 0xEA 0x00 0x7C 0x00 0x00
typeset -i pbs_ofs_sector=43
typeset -i pbs_curptr=66

function pbs_output {
	typeset ostr=

	# fill the block table
	(( pbs_thecode[pbs_ofs_sector] = $1 + 1 ))
	while (( pbs_curptr < 126 )); do
		(( pbs_thecode[pbs_curptr++] = RANDOM & 0xFF ))
	done

	# fill in the hashes
	pbs_thecode[126]=0x8C
	pbs_thecode[127]=0xCA
	pbs_curptr=0
	while (( pbs_curptr < 126 )); do
		(( pbs_thecode[126] ^= pbs_thecode[pbs_curptr++] ))
		(( pbs_thecode[127] ^= pbs_thecode[pbs_curptr++] ))
	done

	# create the output string
	pbs_curptr=0
	typeset -Uui8 pbs_thecode
	while (( pbs_curptr < 128 )); do
		ostr=$ostr\\0${pbs_thecode[pbs_curptr++]#8#}
	done

	# the part after $ostr generated by:
	# $ dd if=<sparc cdrom with disklabel applied> bs=1 skip=128 | \
	#   hexdump -ve '1/1 "\\0%o"' | sed 's/\\00*/\\0/g'
	print -n "$ostr\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\01\0136\010\0\0\0\0\0\0\0\0\01\010\0\0\0\0\01\02\0200\0\0\0\0\0\0\0\0\0\024\0\0\0\0\0\0\0\024\0\0\0\0\0\0\0\024\0\0\0\0\0\0\0\024\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0332\0276\0125\0252"
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
typeset -i blktblnum=0 firstblock lastblock i=0 sscale=0

while getopts ":0:S:" ch; do
	case $ch {
	(0)	if (( OPTARG < 0 || OPTARG > 62 )); then
			print -u2 Error: invalid chain sector "'$OPTARG'"
			exit 1
		fi
		pbs_output $OPTARG ;;
	(S)	if (( (sscale = OPTARG) < 0 || OPTARG > 24 )); then
			print -u2 Error: invalid sector scale "'$OPTARG'"
			exit 1
		fi ;;
	(*)	print -u2 "Syntax: bxinst [-S scale] <blocklist >loader"
		exit 1 ;;
	}
done
shift $((OPTIND - 1))

# zero-initialise the block array
while (( i < blktblsz )); do
	typeset -i blktblent[i++]=0
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
