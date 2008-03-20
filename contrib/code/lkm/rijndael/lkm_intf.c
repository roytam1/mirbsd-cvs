/* $MirOS: contrib/code/lkm/rijndael/lkm_intf.c,v 1.1.1.1 2008/03/20 19:19:51 tg Exp $ */

/*-
 * Copyright (c) 2005, 2008
 *	Thorsten "mirabilos" Glaser <tg@66h.42h.de>
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

#include <sys/param.h>
#include <sys/conf.h>
#include <sys/errno.h>
#include <sys/exec.h>
#include <sys/ioctl.h>
#include <sys/systm.h>
#include <sys/lkm.h>
#include "rijndaellkm.h"

struct cdevsw rijndael_cdevsw = cdev_rijndael_init(NRIJNDAEL, rijndael);

MOD_DEV("rijndael", LM_DT_CHAR, -1, &rijndael_cdevsw)

static int rijndael_modload(struct lkm_table *, int);

int
rijndael_lkmentry(struct lkm_table *lkmtp, int cmd, int ver)
{
	DISPATCH(lkmtp, cmd, ver, rijndael_modload, rijndael_modload, lkm_nofunc)
}

static int
rijndael_modload(struct lkm_table *lkmtp, int cmd)
{
	switch (cmd) {
	case LKM_E_LOAD:
		_PD("rijndael: module loaded\n");
		break;
	case LKM_E_UNLOAD:
		_PD("rijndael: module unloaded\n");
		break;
	default:
		printf("rijndael: illegal modload operation %d\n", cmd);
		return (EINVAL);
	}
	return (0);
}

int
rijndaelopen(dev_t dev, int oflags, int devtype, struct proc *p)
{
	_PD("rijndael: device opened\n");
	return (0);
}

int
rijndaelclose(dev_t dev, int fflag, int devtype, struct proc *p)
{
	_PD("rijndael: device closed\n");
	return (0);
}

int
rijndaelread(dev_t dev, struct uio *uio, int ioflag)
{
	_PD("rijndael: device read from\n");
	return (ENOCOFFEE);
}

int
rijndaelwrite(dev_t dev, struct uio *uio, int ioflag)
{
	_PD("rijndael: device written to\n");
	return (ENOCOFFEE);
}

int
rijndaelioctl(dev_t dev, u_long cmd, caddr_t data, int fflag, struct proc *p)
{
	_PD("rijndael: device ioctl called\n");
	return (ENOCOFFEE);
}
