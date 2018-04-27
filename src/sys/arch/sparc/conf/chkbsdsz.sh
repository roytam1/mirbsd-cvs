#!/bin/mksh
# $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $
#-
# Copyright © 2018
#	mirabilos <m@mirbsd.org>
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
# Checks a MirBSD/sparc ELF kernel to ensure bootability.

die() {
	[[ -n $T ]] && rm -f "$T"
	print -ru2 -- "E: $0: $*"
	exit 255
}

typeset -Uui16 RELOC=$1		# really RELOC2
typeset -Uui16 LOADADDR=0x4000	# really LOADADDR from stand/common/promdev.h
typeset -Uui16 BOOTSTACK=0x4000	# amount of stack from boot_sparc(8) to ensure
kernel=$2
[[ -s $kernel ]] || die "kernel '$kernel' not found"
print -ru2 -- "I: $0: analysing kernel '$kernel'"
T=
if [[ $(dd if="$kernel" bs=2 count=1 2>/dev/null) = $'\x1F\x8B' ]]; then
	print -ru2 -- "I: $0: decompressing kernel for analysis"
	T=$(mktemp /tmp/chkbsdsz.XXXXXXXXXX)
	gzip -d <"$kernel" >"$T" || die decompression failed
fi
rv=2
typeset -Uui16 -Z11 addr maxaddr
((# maxaddr = RELOC - BOOTSTACK ))

readelf -l "${T:-$kernel}" |&
entryp=z
ph=0
while IFS= read -pr line; do
	[[ $line = 'Entry point 0x'* ]] && \
	    typeset -Uui16 -Z11 entryp=${line#Entry point }
	[[ $line = 'Program Headers:' ]] || continue
	ph=1
	break
done
[[ $entryp = z ]] && die no entry point found in readelf output
(( ph )) || die no program headers found in readelf output, 1
IFS= read -pr line || die no program headers found in readelf output, 2
addr=0
while read -pr Type Offset VirtAddr PhysAddr FileSiz MemSiz Flg Align; do
	[[ -n $Type ]] || break
	[[ $Type = LOAD ]] || continue
	[[ $Flg = *[WE]* ]] || continue
	((# $VirtAddr == entryp )) && ph=2
	((# addr2 = $VirtAddr + $MemSiz ))
	((# addr = addr2 > addr ? addr2 : addr ))
done
while IFS= read -pr line; do :; done
(( ph == 2 )) || die entry point not found
print -ru2 -- "I: $0: entry point ${entryp#16#}"
((# addr = (addr - entryp + LOADADDR + 3) & 0xFFFFFFFC ))

if ((# addr > maxaddr )); then
	print -ru2 -- "E: $0: kernel too big by $((# addr - maxaddr)) bytes"
else
	print -ru2 -- "I: $0: kernel would boot stripped"
	let --rv
fi
print -ru2 -- "N: $0: 0x${addr#16#} reached loading the kernel stripped"
print -ru2 -- "N: $0: 0x${maxaddr#16#} limit: $((#BOOTSTACK/1024)) KiB stack, boot loader"

readelf -S "${T:-$kernel}" | tr -d '][' |&
while IFS= read -pr line; do
	[[ $line = 'Section Headers:' ]] || continue
	ph=0
	break
done
(( ph )) && die no section headers found in readelf output, 1
IFS= read -pr line || die no section headers found in readelf output, 2
while read -pr Nr Name Type Addr Off Size ES Flg Lk Inf Al; do
	[[ $Nr = +([0-9]) ]] || break
	if [[ $Type = SYMTAB ]]; then
		ph=1
	elif [[ $Type != STRTAB ]]; then
		continue
	fi
	((# addr += (0x$Size + 3) & 0xFFFFFFFC ))
done
while IFS= read -pr line; do :; done
if (( !ph )); then
	print -ru2 -- "I: $0: kernel is stripped and will boot"
	let --rv
elif ((# addr > maxaddr )); then
	print -ru2 -- "E: $0: kernel too big by $((# addr - maxaddr)) bytes"
else
	print -ru2 -- "I: $0: kernel would boot unstripped as well"
	let --rv
fi
print -ru2 -- "N: $0: 0x${addr#16#} reached loading the kernel unstripped"
[[ -n $T ]] && rm -f "$T"
exit $rv
