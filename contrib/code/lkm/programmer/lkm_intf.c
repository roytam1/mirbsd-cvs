/* $MirOS: src/share/misc/licence.template,v 1.2 2005/03/03 19:43:30 tg Rel $ */

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
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
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
#include "programmerlkm.h"

struct cdevsw programmer_cdevsw = cdev_programmer_init(NPROGRAMMER, programmer);

MOD_DEV("programmer", LM_DT_CHAR, -1, &programmer_cdevsw)

static int programmer_modload(struct lkm_table *, int);

int
programmer_lkmentry(struct lkm_table *lkmtp, int cmd, int ver)
{
	DISPATCH(lkmtp, cmd, ver, programmer_modload, programmer_modload, lkm_nofunc)
}

static int
programmer_modload(struct lkm_table *lkmtp, int cmd)
{
	switch (cmd) {
	case LKM_E_LOAD:
		_PD("programmer: module loaded\n");
		break;
	case LKM_E_UNLOAD:
		_PD("programmer: module unloaded\n");
		break;
	default:
		printf("programmer: illegal modload operation %d\n", cmd);
		return (EINVAL);
	}
	return (0);
}

int
programmeropen(dev_t dev, int oflags, int devtype, struct proc *p)
{
	_PD("programmer: device opened\n");
	return (0);
}

int
programmerclose(dev_t dev, int fflag, int devtype, struct proc *p)
{
	_PD("programmer: device closed\n");
	return (0);
}

int
programmerread(dev_t dev, struct uio *uio, int ioflag)
{
	_PD("programmer: device read from\n");
	return (ENOCOFFEE);
}

int
programmerwrite(dev_t dev, struct uio *uio, int ioflag)
{
	_PD("programmer: device written to\n");
	return (ENOCOFFEE);
}

int
programmerioctl(dev_t dev, u_long cmd, caddr_t data, int fflag, struct proc *p)
{
	_PD("programmer: device ioctl called\n");
	return (ENOCOFFEE);
}
