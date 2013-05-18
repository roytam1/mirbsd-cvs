#include <machine/asm.h>

RCSID("$MirOS: src/usr.bin/crunchgen/data.S,v 1.3 2007/06/11 19:23:14 tg Exp $")

	.section .rodata

/* const unsigned char manpage[]; */
DENTRY(manpage)
#ifdef NOMAN
	.asciz	"no manual\n"
#else
	.incbin	"disklabel.cat8"
	.byte	0
#endif
