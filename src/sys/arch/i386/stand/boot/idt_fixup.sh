#!/bin/mksh
# $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $
#-
# Copyright (c) 2009
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

function die {
	rv=$1; shift
	print -u2 -- "$@"
	exit $rv
}

[[ -s $1 ]] || die 1 Cannot read input file "'$1'"

nm $1 |&
while read -p adr typ sym; do
	[[ $sym = @(_start|idt_fixup_end|idt_for_fixup) ]] || continue
	eval typeset -i10 sym_$sym=0x\$adr
done

T=$(mktemp /tmp/idt_fixup.XXXXXXXXXX) || die 255 Cannot create temporary file
objcopy -O binary $1 $T
dd if=$T bs=1 count=$((sym_idt_fixup_end - sym_idt_for_fixup)) \
    skip=$((sym_idt_for_fixup - sym__start)) 2>/dev/null | \
    hexdump -ve '8/1 "%02X " "\n"' | \
    while read b1 b2 b3 b4 b5 b6 b7 b8; do
	print -n "\\x$b1\\x$b2\\x$b7\\x$b8\\x$b5\\x$b6\\x$b3\\x$b4"
    done | dd of=$T bs=1 count=$((sym_idt_fixup_end - sym_idt_for_fixup)) \
    seek=$((sym_idt_for_fixup - sym__start)) conv=notrunc 2>/dev/null
mv -f $T $2
