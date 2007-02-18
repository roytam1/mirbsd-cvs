#include <machine/asm.h>

RCSID("$MirOS$")

	.intel_syntax noprefix

	.section .rodata

	/* const char crunched_skel[]; */
	.globl	_C_LABEL(crunched_skel)
_C_LABEL(crunched_skel):
	.incbin	"crunched_main.c"
