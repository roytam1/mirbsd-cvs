#!/usr/bin/env mksh
# $MirOS: src/share/misc/licence.template,v 1.20 2006/12/11 21:04:56 tg Rel $
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
# Reads a list of extents (blockno numblocks LF) from standard input
# and writes bootxx to standard output, which can subsequentially be
# stored past the SunOS disklabel directly on the disc.

function out_int32 {
	typeset -Uui16 value=$1
	typeset -Uui8 ba bb bc bd

	print -u2 debug: writing value 0x${value#16#}
	(( ba = (value >> 24) & 0xFF ))
	(( bb = (value >> 16) & 0xFF ))
	(( bc = (value >> 8) & 0xFF ))
	(( bd = value & 0xFF ))
	print -n "\\0${ba#8#}\\0${bb#8#}\\0${bc#8#}\\0${bd#8#}"
}

integer blktblsz=@@TBLSZ@@

exit 1
#XXX TODO

# Part 1
print -n '@@PARTONE@@'

# The Block Table
# note: currently, MI installboot(8) assumes 512-byte blocks, maybe
#       do an optimisation similar to the i386 first-stage bootloader
out_int32 $blktblsz	#XXX
out_int32 512
integer i=0
while (( i < blktblsz )); do
	out_int32 0
	let i++
done

# Part 2
print -n '@@PARTTWO@@'
exit 0
