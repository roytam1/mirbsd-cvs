/* $MirOS: src/sys/arch/i386/stand/pbr/ffs/pbr.S,v 1.7 2005/12/04 23:14:40 tg Exp $ */

/*-
 * Copyright (c) 2003, 2004, 2005
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * All advertising materials mentioning features or use of this soft-
 * ware must display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 *-
 * Derived from the original OpenBSD first stage boot loader code,
 * written by (c) 1997 Michael Shalayeff, Tobias Weingartner, as spec.
 *
 * Checks if LBA, if not available, uses CHS. If LBA load fails, fall
 * back to CHS. If everything fails or bad magic, redo from start but
 * using CHS-single-sector transfers. Ugly but size-optimized code.
 */

	.intel_syntax noprefix
	.text
	.code16
	.globl	_start
	.globl	blkcnt		/** block count in hint table	*/
	.globl	bpbspt		/** used to convert LBA -> CHS	*/
	.globl	bpbtpc		/** used to convert LBA -> CHS	*/
	.globl	blktbl		/** hint table start (at EOF)	*/
	.globl	partp		/** user defined partition type */
	.type	blkcnt, @function
	.type	bpbspt, @function
	.type	bpbtpc, @function
	.type	blktbl, @function
	.type	partp,  @function

/* Parameter block for LBA, gets constructed here:
 * this is ALWAYS offset 0 into the file!
	word	0x0010		(+0,2) length, reserved
	word	0x0001		(+2,2) num. of sectors
	long	0x00007C00	(+4,4) transfer buffer
	long	0,0		(+8,8) LBA block number
 */

	/* INITIALIZATION routine */
_start:	xor	eax,eax
	push	ax
	popf
	mov	ss,ax
	mov	sp,0xFFFC
	sti
	add	ax,0x07C0	/* not MOV - eases debugging... */
	mov	ds,ax
	mov	gs,ax
	push	ax
	push	offset Lrun
	lret			/* should read retf according to GNU docs */

Lmsg:	.ascii	__BOOT_VER
	.asciz	" Loading "

#define	BLKCNT	(blkend - blktbl)
blkcnt:	.byte	BLKCNT
Lldp:	.word	LsLBA
	.word	LsCHS
Ldrv:	.byte	0x80
partp:	.byte	0	/* must be Ldrv + 1 */
bpbspt:	.word	18
bpbtpc:	.word	2

	/* MAIN routine */
Lrun:	mov	[Ldrv],dl	/* boot device */
	/* say hello */
	mov	si,offset Lmsg
	call	Lotxt
	/* check for LBA */
	mov	di,offset Lldp
	mov	ah,0x41
	mov	bx,0x55AA
	int	0x13
	jc	Lr_chs		/* carry -> error */
	cmp	bx,0xAA55
	jne	Lr_chs		/* magic -> command known? */
	and	cl,1
	jne	Lr_lba		/* bitmask: supports LBA? */
Lr_chs:	inc	di
	inc	di

Lr_lba:	/* start the first stage boot loader code */
	mov	ax,SA_LINKSEG	/* libsa constant */
	mov	fs,ax		/* for magic check and booting */
	push	ax		/* for load address and incrementing */
	mov	ax,0x0010
	mov	ds:[0],eax	/* high 16 bits have already been cleared */
	/* initialize counters */
	mov	si,offset blktbl
	xor	cx,cx
	mov	cl,[blkcnt]

	/* --- main loop --- */
Lmlp1:	lodsb
	/*
	 * al contains bitmasked:
	 * aaabbbbb
	 * -> a=number of bytes-1 that follow	(-> dl)
	 * -> b=number of sectors-1 to load	(-> al)
	 * si, cx contain what is to be processed
	 */

	/* decode */
	mov	dl,al
	shr	dl,5
	and	ax,31		/* sectors */
	inc	ax
	inc	dx
	mov	ds:[2],al
	pop	bx
	mov	es,bx		/* load segment */
	mov	ds:[6],bx
	shl	ax,(9-4)	/* number of sectors, times their size,
				   divided by size of one paragraph */
	add	bx,ax		/* increment load addr. segment accordingly */
	push	bx		/* and save for next round */
	push	cx		/* save blkcnt */
	push	di		/* loader offset */
	mov	di,8
	xor	ebp,ebp
	mov	[di],ebp	/* zero out the LBA sector number */
	mov	[di+4],ebp
	mov	[di-4],bp	/* load offset within segment, always zero */
Lmlp2:	lodsb			/* copy over as many bytes as needed */
	mov	[di],al
	inc	di		/* stos? segment override forbidden */
	dec	dl
	jne	Lmlp2		/* faster/easier than loop */
	pop	di
	/*
	 * at this point, we have the following:
	 * si points to the _next_ entry to load
	 * on top of stack, there is the number of
	 *    entries to load, including the current one
	 * the _next_ load address is below that on the stack
	 * the LBA parameter block is filled in.
	 * ES is set up to the load segment (offset = const. 0000)
	 */

	/* call subroutine that does the actual loading */
	mov	dl,[Ldrv]
	call	[di]
	/* progress meter */
	mov	ax,0x0E2E
	mov	bx,7
	int	0x10			/* output a dot */
	/* --- main loop --- */
	pop	cx
	dec	cx
	jne	Lmlp1

	/* finally /boot is loaded. compare (E)LFmagic (CX=zero!)*/
	push	fs			/* SA_LINKSEG; old 4000, new 4012 */
	push	cx			/* offset (used to be 120, now 0) */
	mov	eax,fs:[0x50]		/* some "random" ASCII string, ie */
	cmp	eax,0x6A6D4F00		/* boot magic */
	mov	si,offset Lerr		/* "bad magic" */
	jne	Lbarf			/* no it isn't, barf out */
	/* new line, for the fine look */
	mov	si,offset Lcrlf
	call	Lotxt
	/* set up and jump into /boot */
	mov	dx,[Ldrv]
	mov	fs:[0x50],dh
	lret

Lotxt0:	int	0x10
Lotxt:	mov	bx,7
	mov	ah,0x0E
	lodsb
	or	al,al
	jne	Lotxt0
	ret

	/* If something went wrong, but we didn't yet try the subrouting
	 * to cope with broken BIOSes and Soekris, redo from start.
	 */
Lbarf:	call	Lotxt			/* something went wrong */
	mov	ax,offset LsBRK		/* offset of broken-BIOS load sub */
	xchg	ax,[di]			/* if di is still Lldp, God help */
	cmp	ax,[di]			/* broken BIOS sub already tried? */
	jne	Lr_lba
	xor	ah,ah
	int	0x16
	jmp	0xF000,0xFFF0

	/* LBA boot routine */
LsLBA:	push	si			/* save blktbl offset */
	mov	ah,0x42			/* BIOS routine loadLBA */
	xor	si,si			/* offset parblk */
	call	LsINT			/* call BIOS subroutine */
	pop	si
Lretn:	ret

	/* CHS boot routine */
LsCHS:	push	dx
	/* LBA -> CHS */
	mov	edx,ds:[8]
	mov	ax,dx
	shr	edx,16
	div	word ptr [bpbspt]
	inc	dx			/* quotient AX, remainder DX */
	push	dx			/* sector */
	xor	dx,dx
	div	word ptr [bpbtpc]
	pop	cx			/* cylinder AX, head DX */
	shl	ah,6
	xchg	ah,al
	or	cx,ax
	mov	dh,dl
	pop	ax
	mov	dl,al
	/* call the BIOS */
	mov	ah,2
	mov	al,ds:[2]
	xor	bx,bx

	/* called from LBA routine, too */
LsINT:	mov	bp,7			/* number of retries */
LsIN0:	pusha
	int	0x13
	popa
	jnc	Lretn
	dec	bp
	pusha
	mov	si,offset Lldf
	jz	Lbarf
	xor	ax,ax
	int	0x13
	mov	ax,0x0E40		/* say it fails */
	add	ax,bp
	mov	bx,7
	int	0x10
	popa
Lnchk:	cmp	bp,3			/* after some failed LBA, try CHS */
LsBR9:	jne	LsIN0
	mov	di,2+offset Lldp
	jmp	LsIN0

Lerr:	.ascii	"bad magic"
Lldf:	.ascii	" ERR"
Lcrlf:	.asciz	"\r\n"

	/* some broken BIOSes don't allow multi-sector transfers... */
LsBRK:	mov	dh,1
	xchg	dh,ds:[2]		/* number of sectors to load */
LsBR0:	push	dx
	call	LsCHS			/* chain to default CHS loader */
	pop	dx
	dec	dh
	je	Lretn			/* loop one by one over the sectors */
	mov	ax,es
	add	ax,32			/* size of a sector in paragraphs */
	mov	es,ax
	inc	dword ptr ds:[8]
	jmp	LsBR0
	/* --- end of code --- */

blktbl:	/* free space for block table */

	/* --- end of sector --- */
	. = 0x1FE
blkend:	.word	0xAA55
