#include <machine/asm.h>

RCSID("$MirOS: src/usr.bin/crunchgen/data.S,v 1.1 2007/02/18 12:54:05 tg Exp $")

	.intel_syntax noprefix
	.section .rodata

/* const char crunched_skel[]; */
DENTRY(crunched_skel)
	.incbin	"crunched_main.c"
