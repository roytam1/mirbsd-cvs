	.section .comment
	.ascii	"@(""#)rcsid: "
	.asciz	"$MirOS$"
#ifdef INCLUDE_CONFIG_FILE
	.section .config.gz
	.incbin	"config.gz"
#endif
