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
 * Redistributors of this work may choose to use the GNU LGPL (Libra-
 * ry General Public License), Version 2, instead of the terms above.
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
#include "qvm86lkm.h"

struct cdevsw qvm86_cdevsw = cdev_qvm86_init(NQVM86, qvm86);

MOD_DEV("qvm86", LM_DT_CHAR, -1, &qvm86_cdevsw)

static int qvm86_modload(struct lkm_table *, int);

int
qvm86_lkmentry(struct lkm_table *lkmtp, int cmd, int ver)
{
	DISPATCH(lkmtp, cmd, ver, qvm86_modload, qvm86_modload, lkm_nofunc)
}

static int
qvm86_modload(struct lkm_table *lkmtp, int cmd)
{
	switch (cmd) {
	case LKM_E_LOAD:
		_QD("qvm86: module loaded\n");
		break;
	case LKM_E_UNLOAD:
		_QD("qvm86: module unloaded\n");
		break;
	default:
		printf("qvm86: illegal modload operation %d\n", cmd);
		return (EINVAL);
	}
	return (0);
}

int
qvm86open(dev_t dev, int oflags, int devtype, struct proc *p)
{
	_QD("qvm86: device opened\n");
	return (0);
}

int
qvm86close(dev_t dev, int fflag, int devtype, struct proc *p)
{
	_QD("qvm86: device closed\n");
	return (0);
}

int
qvm86read(dev_t dev, struct uio *uio, int ioflag)
{
	_QD("qvm86: device read from\n");
	return (ENOSYS);
}

int
qvm86write(dev_t dev, struct uio *uio, int ioflag)
{
	_QD("qvm86: device written to\n");
	return (ENOSYS);
}

int
qvm86ioctl(dev_t dev, u_long cmd, caddr_t data, int fflag, struct proc *p)
{
	_QD("qvm86: device ioctl called\n");
	return (ENOSYS);
}
