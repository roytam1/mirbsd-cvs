/**	$MirOS: src/sys/arch/sparc/stand/bootxx/btable.S,v 1.1 2007/10/16 20:29:33 tg Exp $ */
/*	$OpenBSD: bootxx.c,v 1.5 2003/11/14 19:05:36 miod Exp $	*/

/*-
 * Copyright (c) 2007
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

#include <machine/param.h>
#include <machine/psl.h>
#include <machine/asm.h>

	.file	"btable.S"

	.data
	.balign	4

/*
 * The contents of the block_* variables below is set by installboot(8)
 * to hold the filesystem data of the second-stage boot program
 * (typically '/boot'): filesystem block size, # of filesystem blocks and
 * the block numbers themselves.
 */
#define MAXBLOCKNUM	256	/* enough for a 2MB boot program (bs 8K) */

/*
 * For new-style installboot, we expect a block, concatenating the former
 * variables block_count, block_size, and block_table (in that order),
 * starting at block_start
 * To retain compatibility to old-style installboot and boot loaders, we
 * also export the previous names as parts of the data structure.
 */

	.globl	_C_LABEL(block_start)
block_start:

/* extern int32_t block_count = MAXBLOCKNUM; */
	.globl	_C_LABEL(block_count)
block_count:
	.long	MAXBLOCKNUM
/* extern int32_t block_size = 0; */
	.globl	_C_LABEL(block_size)
block_size:
	.long	0
/* extern int32_t block_table[MAXBLOCKNUM] = { 0 }; */
	.globl	_C_LABEL(block_table)
block_table:
	.rept	MAXBLOCKNUM
	.long	0
	.endr
