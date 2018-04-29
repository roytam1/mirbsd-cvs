#!/bin/mksh
# $MirOS: src/sys/arch/sparc/conf/chkbsdsz.sh,v 1.2 2018/04/28 00:34:48 tg Exp $
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
# Checks a MirBSD/sparc ELF kernel, optionally converted to bootable
# a.out format, to ensure bootability.

die() {
	[[ -n $T ]] && rm -f "$T"
	print -ru2 -- "E: $0: $*"
	exit 255
}

[[ $1 = 0x+([0-9A-F]) ]] || die RELOC2 not passed as \$1

typeset -Uui16 RELOC=$1		# really RELOC2
typeset -Uui16 LOADADDR=0x4000	# really LOADADDR from stand/common/promdev.h
typeset -Uui16 BOOTSTACK=0x2000	# amount of stack from boot_sparc(8) to ensure
kernel=$2
[[ -s $kernel ]] || die "kernel '$kernel' not found"
print -ru2 -- "I: $0: analysing kernel '$kernel'"
T=
if [[ $(<"$kernel" hexdump -vn 2 -e '1/1 "%02X"') = 1F8B ]]; then
	print -ru2 -- "I: $0: decompressing kernel for analysis"
	T=$(mktemp /tmp/chkbsdsz.XXXXXXXXXX)
	gzip -d <"$kernel" >"$T" || die decompression failed
fi
rv=2
typeset -Uui16 -Z11 addr maxaddr
((# maxaddr = RELOC - BOOTSTACK ))

check_stripped() {
	if ((# addr <= maxaddr )); then
		print -ru2 -- "I: $0: kernel would boot stripped, $((# maxaddr - addr)) bytes left"
		let --rv
	else
		print -ru2 -- "E: $0: kernel too big by $((# addr - maxaddr)) bytes"
	fi
	print -ru2 -- "N: $0: 0x${addr#16#} reached loading the kernel stripped"
	print -ru2 -- "N: $0: 0x${maxaddr#16#} limit: $((#BOOTSTACK/1024)) KiB stack, boot loader"
}

check_unstripped() {
	local has_syms=$1 has_override=$2

	if (( !has_syms )); then
		if (( --rv )); then
			print -ru2 -- "I: $0: kernel is stripped and will NOT boot"
		else
			print -ru2 -- "I: $0: kernel is stripped and will boot"
		fi
	elif ((# addr <= maxaddr )); then
		print -ru2 -- "I: $0: kernel would boot unstripped as well, $((# maxaddr - addr)) bytes left"
		(( has_override )) && print -ru2 -- "I: $0: kernel has disable-debugsyms flag set"
		let --rv
	elif (( has_override && rv == 1 )); then
		print -ru2 -- "W: $0: kernel will boot only due to disable-debugsyms flag"
		print -ru2 -- "N: $0: with debug symbols, too big by $((# addr - maxaddr)) bytes"
		let --rv
	else
		print -ru2 -- "E: $0: kernel too big by $((# addr - maxaddr)) bytes"
	fi
	print -ru2 -- "N: $0: 0x${addr#16#} reached loading the kernel unstripped"
}

and_out() {
	[[ -n $T ]] && rm -f "$T"
	exit $rv
}

set -A hdr -- $(<"$kernel" hexdump -vn 32 -e '8/4 "0x%08X " "\n"')
if (( hdr[0] == 0x01030107 )); then
	# MirBSD elf2aout creates OMAGIC only; 0103 is for bootable kernel
	# other / classical variants of a.out have no relevance in MirBSD
	print -ru2 -- "N: $0: assuming bootable a.out kernel"
	(( hdr[6] )) && die 'a.out text relocations found'
	(( hdr[7] )) && die 'a.out data relocations found'
	((# addr = LOADADDR ))
	#ZMAGIC: add 32 (= sizeof(struct exec))
	((# addr += hdr[1] ))
	#ZMAGIC,NMAGIC: align by __LDPGSZ (NMAGIC only in the kernel;
	# a.out(5) disagrees in its description with either, PITA…)
	((# addr += hdr[2] + hdr[3] ))
	check_stripped
	if (( hdr[4] )); then
		((# addr += hdr[4] ))
		((# addr2 = 32 + hdr[1] + hdr[2] + hdr[4] ))
		strtablen=0x$(<"$kernel" hexdump -vn 4 -s $((#addr2)) -e '1/4 "%08X"')
		if (( strtablen )); then
			((# strtablen < 4 )) && die "malformed a.out: strtablen $strtablen < 4"
			((# addr += strtablen ))
		fi
	fi
	check_unstripped $(( hdr[4] != 0 )) 0
	and_out
fi

print -ru2 -- "N: $0: assuming ELF kernel"
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
check_stripped

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
[[ $(<"$kernel" hexdump -vn 1 -s 7 -e '1/1 "%02X"') != 0C ]]; ovr=$?
check_unstripped $ph $ovr
and_out
