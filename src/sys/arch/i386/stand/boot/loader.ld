/* $MirOS$ */

OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)
SECTIONS
{
	. = 0x30000;
	__bss_start = .;
	.bss : { *(.bss) *(COMMON) }
	. = ALIGN(32 / 8);
	__bss_end = .;

	. = 0x40000;
	.text : { *(.text) *(.rodata) }
	.data : { *(.data) }
	. = ALIGN(32 / 8);
	PROVIDE (end = .);
}
