#!/bin/mksh
rcsid='$MirOS: src/sys/arch/sparc/stand/bootxx/mkbxinst.sh,v 1.22 2010/01/16 21:39:54 tg Exp $'
#-
# Copyright (c) 2007, 2008, 2009, 2010
#	mirabilos <m@mirbsd.org>
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
	[[ $sym = _@(_ustar_keep|block_start|start) ]] || continue
	eval typeset -i10 sym$sym=0x\$adr
done

set -A sect_text -- $(objdump -wh --target=a.out-sunos-big $1 | fgrep .text)
(( fofs_text = 0x${sect_text[5]} ))

(( fofs_text == 0x20 )) || die 1 Adjust fofs_text in srt0.S and here

typeset -Uui10 ofs tblsz
(( ofs = sym_block_start - sym_start + fofs_text ))
strip -F a.out-sunos-big -s -o $T $1
outsz=$(stat -f %z $T)
(( outsz <= (15 * 512) )) || die 1 bootxx too big
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
# Copyright (c) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009,
#		2010, 2011, 2012, 2013, 2014, 2015, 2017, 2018
#	mirabilos <m@mirbsd.org> (a.k.a. The MirOS Project)
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un‐
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# Advertising materials mentioning features or use of this work must
# display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person’s immediate fault when using the work as intended.
#
# Additional licences for the actual boot code below; these apply to
# this entire resulting generated file.
#-
# Self-installing 32-bit sun4m/sun4c boot blocks for MirOS BSD/sparc
# Reads a list of extents (firstblock lastblock) from standard input
# and writes bootxx to standard output, which can subsequentially be
# stored past the SunOS disklabel directly on the disc.
# Other mode creates ustarfs leader from self and /usr/mdec/boot.fd.
#-
# Copyright (c) 1989, 1990, 1991 Carnegie Mellon University
# All Rights Reserved.
#
# Author: Alessandro Forin
#
# Permission to use, copy, modify and distribute this software and its
# documentation is hereby granted, provided that both the copyright
# notice and this permission notice appear in all copies of the
# software, derivative works or modified versions, and any portions
# thereof, and that both notices appear in supporting documentation.
#-
# Copyright (c) 2002 Marc Espie.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE OPENBSD PROJECT AND CONTRIBUTORS
# ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OPENBSD
# PROJECT OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#-
# Copyright (C) 1985 Regents of the University of California
# Copyright (c) 1993 Adam Glass
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgement:
#	This product includes software developed by Adam Glass.
# 4. The name of the Author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY Adam Glass ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#-
# Copyright (c) 1993 John Brezak
# Copyright (c) 1993, 1994 Christopher G. Demetriou
# Copyright (c) 1993, 1994 Paul Kranenburg
# Copyright (c) 1995 Gordon W. Ross
# Copyright (c) 1997 Niklas Hallqvist
# Copyright (c) 1997 Theo de Raadt
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgement:
#	This product includes software developed by Paul Kranenburg.
#	This product includes software developed by Gordon Ross
#	This product includes software developed by Christopher G. Demetriou.
# 4. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#-
# Copyright (c) 1982, 1986, 1988, 1989, 1990, 1991, 1992, 1993, 1994
#	The Regents of the University of California
# (c) UNIX System Laboratories, Inc.
# Copyright (c) 1988 University of Utah
# Copyright (c) 1993 Adam Glass
# Copyright (c) 1993 Theo de Raadt
# Copyright (c) 1994 Allen Briggs
# Copyright (c) 1995, 1996
#	The President and Fellows of Harvard College
# Copyright (c) 1996 Matthias Drochner
# Copyright (c) 1994, 1997 Christopher G. Demetriou
# All rights reserved.
#
# All or some portions of this file are derived from material licensed
# to the University of California by American Telephone and Telegraph
# Co. or Unix System Laboratories, Inc. and are reproduced herein with
# the permission of UNIX System Laboratories, Inc.
#
# This code is derived from software contributed to Berkeley by
# Jan-Simon Pendry.
#
# This code is derived from software contributed to Berkeley by
# Berkeley Software Design, Inc.
#
# This code is derived from software contributed to Berkeley by
# The Mach Operating System project at Carnegie-Mellon University.
#
# Sun4m support by Aaron Brown, Harvard University.
#
# This software was developed by the Computer Systems Engineering group
# at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
# contributed to Berkeley.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgements:
#	This product includes software developed by Harvard University.
#	This product includes software developed by the University of
#	   California, Berkeley and its contributors.
#	This product includes software developed by the University of
#	   California, Lawrence Berkeley Laboratory.
# 4. Neither the name of the University nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.

EOF
sed -e '/\$Mir''OS: /s/MirOS/miros/p' \
    -e '/^function tarcksum/,/^}/p' \
    -n $BSDSRCDIR/sys/arch/i386/stand/bootxx_ustarfs/tarcksum
print
typeset -i ustar_keep=$((sym__ustar_keep - sym_start + fofs_text ))
(( ustar_keep < 100 )) || die 1 ustar_keep is too large
print typeset -i  outsz=$outsz ustar_keep=$ustar_keep
cat <<'EOF'

# $miros: src/distrib/tools/i386_chain.S,v 1.7 2007/10/20 22:05:13 tg Exp $
set -A pbs_thecode 0x66 0x31 0xC0 0x66 0x50 0x66 0x9D 0x05 0xA0 0x07 0x8E 0xD0 0xBC 0xFC 0xFF 0xFB 0x50 0x68 0x24 0x00 0x8E 0xD8 0x8E 0xC0 0x31 0xFF 0xBE 0x00 0x02 0xB9 0x80 0x00 0xF3 0x66 0xA5 0xCB 0xB8 0x01 0x02 0xBB 0x00 0x02 0xB9 0x19 0x00 0xB6 0x00 0x60 0xCD 0x13 0x61 0x73 0x08 0x60 0x31 0xC0 0xCD 0x13 0x61 0xEB 0xF2 0xEA 0x00 0x7C 0x00 0x00
typeset -Uui8 pbs_thecode
typeset -i pbs_ofs_sector=43 pbs_curptr=66 ustarmode=0

function pbs_output {
	typeset ostr=
	typeset -i psz cylno

	# fill the block table
	(( pbs_thecode[pbs_ofs_sector] = $1 + 1 ))
	if (( ustarmode )); then
		pbs_curptr=0
		pbs_thecode[pbs_curptr++]=1#u
		pbs_thecode[pbs_curptr++]=1#s
		pbs_thecode[pbs_curptr++]=1#t
		pbs_thecode[pbs_curptr++]=1#a
		pbs_thecode[pbs_curptr++]=1#r
		pbs_thecode[pbs_curptr++]=1#f
		pbs_thecode[pbs_curptr++]=1#s
		pbs_thecode[pbs_curptr++]=0
	fi
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
	# sparc partition h (for ustarfs)
	let psz--
	pbs_thecode[503]=1
	(( pbs_thecode[504] = (psz >> 24) & 0xFF ))
	(( pbs_thecode[505] = (psz >> 16) & 0xFF ))
	(( pbs_thecode[506] = (psz >> 8) & 0xFF ))
	(( pbs_thecode[507] = psz & 0xFF ))
	let psz++
	# i386 partition
	pbs_thecode[478]=0x80
	(( pbs_thecode[480] = ustarmode ? 2 : 1 ))
	pbs_thecode[482]=0x96
	(( pbs_thecode[483] = g_code[1] - 1 ))
	(( cylno = g_code[0] > 1024 ? 1023 : g_code[0] - 1 ))
	(( pbs_thecode[484] = g_code[2] | ((cylno & 0x0300) >> 2) ))
	(( pbs_thecode[485] = cylno & 0x00FF ))
	(( ustarmode )) && pbs_thecode[486]=1
	(( ustarmode )) && let psz--
	(( pbs_thecode[490] = psz & 0xFF ))
	(( pbs_thecode[491] = (psz >> 8) & 0xFF ))
	(( pbs_thecode[492] = (psz >> 16) & 0xFF ))
	(( pbs_thecode[493] = (psz >> 24) & 0xFF ))
	(( ustarmode )) && let psz++
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

function out_int8 {
	typeset -Uui8 b

	(( b = $1 & 0xFF ))
	print -n "\\0${b#8#}"
}

# Output the following:
# • 512 bytes: Sun disklabel
# • outsz bytes: bootxx (where first 512 bytes is ustar header)
# • pad until end of sector: random bytes
# • variable number of bytes: second stage bootloader
# • pad until end of sector: undefined
# A real ustar archive containing the kernel can be appended.
# Layout on disc (only 0‥k are written):
# • 0: Sun disklabel
# • 1: ustar header 1‥k
# • 2‥i: first stage bootloader
# • j‥k: second stage bootloader
# • k+1: next ustar header or 1024 NUL-bytes
# i = 1 + (outsz_padded / 512) - 1
# j = i + 1
# k = j + (stage2size_padded / 512) - 1
function do_ustar {
	typeset me=$1 mdecboot=$2

	# round up to whole of 512 bytes
	(( outsz = (outsz + 511) & ~511 ))

	# we need this later
	if ! T=$(mktemp -d /tmp/bootxx.XXXXXXXXXX); then
		print -u2 Error: cannot create temporary directory
		exit 1
	fi
	cd "$T"

	# output modified Sun disklabel
	pbs_output 0 >label

	# copy over second stage bootloader
	dd if="$mdecboot" of=stage2 2>/dev/null
	stage2size=$(stat -f %z stage2)
	(( stage2size = (stage2size + 511) & ~511 ))

	(( i = 1 + (outsz / 512) - 1 ))
	(( j = i + 1 ))
	(( k = j + (stage2size / 512) - 1 ))

	# create bootxx by using myself and calculated values
	print $j $k | mksh "$me" >stage1

	# copy tarball content (stage1 + stage2) together
	dd if=stage1 of=content obs=512 conv=osync 2>/dev/null
	if (( $(stat -f %z content) != outsz )); then
		print -u2 Internal error
		cd /
		rm -rf "$T"
		exit 255
	fi
	cat stage2 >>content

	# split content into file (f) and ustar header (h)
	dd if=content of=f bs=512 skip=1 2>/dev/null
	x=0
	while (( x++ < 100 )); do
		out_int8 $RANDOM
	done >h
	dd if=content bs=$ustar_keep count=1 conv=notrunc of=h 2>/dev/null

	# create an ustar archive
	tarprog=$(whence -p mirtar || whence -p tar)
	$tarprog -b 1 -M dist -cf a.tar f
	tarsize=$(stat -f %z a.tar)
	if (( tarsize != (outsz + stage2size + 1024) )); then
		print -u2 Error: tar output size $tarsize wrong, want \
		    $((outsz + stage2size + 1024))
		cd /
		rm -rf "$T"
		exit 1
	fi

	# patch its header
	dd if=h bs=100 count=1 conv=notrunc of=a.tar 2>/dev/null
	print -n "$(tarcksum a.tar)\\0" | \
	    dd of=a.tar bs=1 seek=148 conv=notrunc 2>/dev/null

	# output the result
	print -u2 created $((tarsize - 512)) bytes of ustarfs/sparc lead
	dd if=a.tar bs=512 count=$(((tarsize - 1024)/512)) 2>/dev/null | \
	    cat label -

	# clean up
	cd /
	rm -rf "$T"
}

EOF
print typeset -i blktblsz=$tblsz
cat <<'EOF'
set -A blktblent
typeset -i blktblent blktblnum=0 firstblock lastblock i=0 sscale=0 chainsec=-1
set -A g_code 2048 1 640

while getopts ":0:g:N:S:T:" ch; do
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
	(T)	if [[ ! -s $OPTARG ]]; then
			print -u2 Error: "'$OPTARG'" not found
			exit 1
		fi
		ustarfile=$OPTARG
		ustarmode=1 ;;
	(*)	print -u2 'Syntax:
	bxinst [-0 secno [-g C:H:S]] [-S scale] <blocklist >loader
	(bxinst -g C:H:S -T .../boot; tar -b 1 -M dist -cf - bsd) >floppy.tar
Default scale=0, geometry: 2048 cyls 1 head 640 secs, suggest secno=24'
		exit 1 ;;
	}
done
shift $((OPTIND - 1))

if (( ustarmode )); then
	if [[ ${g_code[*]} = "2048 1 640" ]]; then
		print -u2 Error: Use option -g C:H:S as well
		exit 1
	fi
	do_ustar "$(realpath "$0")" "$(realpath "$ustarfile")"
	exit 0
fi

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
cat <<'EOF'

# Pad with random octets until end of sector
while (( outsz++ & 511 )); do
	out_int8 $RANDOM
done
#let outsz--

exit 0
EOF
exit 0
