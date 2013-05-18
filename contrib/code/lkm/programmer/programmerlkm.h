/* $MirOS: contrib/code/lkm/programmer/programmerlkm.h,v 1.1 2005/11/17 12:31:01 tg Exp $ */

/*-
 * Copyright (c) 2005
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
 * Interface to the Terry Lambert LKM system (MirOS BSD, OpenBSD)
 */

#ifndef _PROGRAMMERLKM_H
#define _PROGRAMMERLKM_H

#ifndef NPROGRAMMER
#define	NPROGRAMMER	1
#endif

#ifndef PLKM_DEBUG
#define PLKM_DEBUG 1
#endif

#if PLKM_DEBUG == 0
#define	_PD(format, ...)	/* nothing */
#else
#define	_PD(format, ...)	printf(format, ## __VA_ARGS__)
#endif

#define cdev_programmer_init(c,n)			\
	{					\
		dev_init(c,n,open),		\
		dev_init(c,n,close),		\
		dev_init(c,n,read),		\
		dev_init(c,n,write),		\
		dev_init(c,n,ioctl),		\
		(dev_type_stop((*))) enodev,	\
		0,				\
		seltrue,			\
		(dev_type_mmap((*))) enodev,	\
		0,				\
		(dev_type_kqfilter((*))) enodev	\
	}

__BEGIN_DECLS
cdev_decl(programmer);

int programmer_lkmentry(struct lkm_table *, int, int);
__END_DECLS

#endif
