/**	$MirOS: src/sys/dev/vndioctl.h,v 1.7 2008/06/12 23:14:48 tg Exp $	*/
/*	$OpenBSD: vndioctl.h,v 1.6 2004/06/20 18:03:03 pedro Exp $	*/
/*	$NetBSD: vndioctl.h,v 1.5 1995/01/25 04:46:30 cgd Exp $	*/

/*
 * Copyright (c) 1988 University of Utah.
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * from: Utah $Hdr: fdioctl.h 1.1 90/07/09$
 *
 *	@(#)vnioctl.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _SYS_VNDIOCTL_H_
#define _SYS_VNDIOCTL_H_

#define VNDNLEN	90

/*
 * Ioctl definitions for file (vnode) disk pseudo-device.
 */
struct vnd_ioctl {
	char	*vnd_file;	/* pathname of file to mount */
	off_t	vnd_size;	/* (returned) size of disk */
	u_char	*vnd_key;
	int	vnd_keylen;
	u_int32_t vnd_options;	/* mount options (for configure) */
#define VNDIOC_OPT_RDONLY  1	/* don't write to the underlying file */
#define VNDIOC_ALGSHIFT	24	/* shift of algorithm in vnd_options */
#define VNDIOC_ALG_BLF		0x00	/* old Blowfish */
#ifdef notyet
/* do not use these yet:
 * 1) kernel implementation has not yet been tested
 * 2) user space is not ready yet
 * 3) the API will change for XTR support:
 *    http://marc.info/?m=121341266715025
 *    we will do it like them, one key per 2³⁰ blocks (sectors), for all algos
 */
#define VNDIOC_ALG_BF_CBC	0x01	/* new Blowfish-CBC */
#define VNDIOC_ALG_AES128_CBC	0x02	/* AES with 128-bit keys */
#define VNDIOC_ALG_AES192_CBC	0x03	/* AES with 192-bit keys */
#define VNDIOC_ALG_AES256_CBC	0x04	/* AES with 256-bit keys */
#endif
};

/*
 * Key sizes for the encrypton algorithms
 */
#define VNDIOC_KSZ_BLF		72	/* 576 bit (448 bit used) */
#ifdef notyet
#define VNDIOC_KSZ_BF_CBC	88	/* 16 bytes salt, 72 bytes key */
#define VNDIOC_KSZ_AES128_CBC	32	/* 16 bytes salt, 16 bytes key */
#define VNDIOC_KSZ_AES192_CBC	40	/* 16 bytes salt, 24 bytes key */
#define VNDIOC_KSZ_AES256_CBC	48	/* 16 bytes salt, 32 bytes key */
#define VNDIOC_MAXKSZ		88	/* largest of the above */
#else
#define VNDIOC_MAXKSZ		72
#endif

#define VNDIOC_BSZ_BLF		8	/* blowfish has 64 bit blocks */
#ifdef notyet
#define VNDIOC_BSZ_AES		16	/* rijndael has 128 bit blocks */
#define VNDIOC_MAXBSZ		16	/* largest of the above */

#define VNDIOC_IVSZ		16	/* size of the salt/IV */
#else
#define VNDIOC_MAXBSZ		8
#endif

/*
 * A simple structure used by userland to query about a specific vnd.
 */
struct vnd_user {
	char	vnu_file[VNDNLEN];	/* vnd file */
	int	vnu_unit;		/* vnd unit */
	dev_t	vnu_dev;		/* vnd device */
	ino_t	vnu_ino;		/* vnd inode */
};

/*
 * Before you can use a unit, it must be configured with VNDIOCSET.
 * The configuration persists across opens and closes of the device;
 * an VNDIOCCLR must be used to reset a configuration.  An attempt to
 * VNDIOCSET an already active unit will return EBUSY.
 */
#define VNDIOCSET	_IOWR('F', 0, struct vnd_ioctl)	/* enable disk */
#define VNDIOCCLR	_IOW('F', 1, struct vnd_ioctl)	/* disable disk */
#define VNDIOCGET	_IOWR('F', 2, struct vnd_user)	/* get disk info */

#endif /* !_SYS_VNDIOCTL_H_ */
