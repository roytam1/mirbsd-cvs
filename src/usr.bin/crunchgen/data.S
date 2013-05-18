#include <machine/asm.h>

RCSID("$MirOS: src/usr.bin/crunchgen/data.S,v 1.2 2007/02/18 16:51:43 tg Exp $")

	.section .rodata

/* const char crunched_skel[]; */
DENTRY(crunched_skel)
	.incbin	"crunched_main.c"
