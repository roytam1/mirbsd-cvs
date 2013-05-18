#!/usr/bin/env mksh
# $MirOS: src/sys/arch/sparc/stand/bootxx/bxinst.sh,v 1.8 2007/10/16 22:28:21 tg Exp $
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
# This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.
#-
# Self-installing SPARC boot blocks for MirOS BSD (sun4m, sun4c)
# Reads a list of extents (firstblock lastblock) from standard input
# and writes bootxx to standard output, which can subsequentially be
# stored past the SunOS disklabel directly on the disc.

function out_int32 {
	typeset -Uui16 value=$1
	typeset -Uui8 ba bb bc bd

	(( ba = (value >> 24) & 0xFF ))
	(( bb = (value >> 16) & 0xFF ))
	(( bc = (value >> 8) & 0xFF ))
	(( bd = value & 0xFF ))
	print -n "\\0${ba#8#}\\0${bb#8#}\\0${bc#8#}\\0${bd#8#}"
}

integer blktblsz=@@TBLSZ@@
set -A blktblent
integer blktblnum=0 firstblock lastblock i=0

# zero-initialise the block array
while (( i < blktblsz )); do
	integer blktblent[i++]=0
done

# read in the extents
while read firstblock lastblock junk; do
	while (( firstblock <= lastblock )); do
		let blktblent[blktblnum++]=firstblock++
	done
	if (( blktblnum > blktblsz )); then
		print -u2 Error: too many blocks, maximum $blktblsz
		exit 1
	fi
done

# verbose output
let i=0
print -nu2 "using $blktblnum blocks: "
while (( i < blktblnum )); do
	print -nu2 "${blktblent[i++]} "
done
print -u2 .

# Part 1
print -n '\01\03\01\07\060\0200\0\07@@PARTONE@@'

# The Block Table
# note: currently, MI installboot(8) assumes 512-byte blocks, maybe
#       do an optimisation similar to the i386 first-stage bootloader
out_int32 $blktblnum
out_int32 512		# XXX size of filesystem blocks
let i=0
while (( i < blktblsz )); do
	out_int32 ${blktblent[i++]}
done

# Part 2
print -n '@@PARTTWO@@'
exit 0
