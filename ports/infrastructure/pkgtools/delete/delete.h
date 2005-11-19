/* $MirOS: ports/infrastructure/pkgtools/delete/delete.h,v 1.1.7.1 2005/03/18 15:47:16 tg Exp $ */

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
 * Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
 * any kind, expressed or implied, to the maximum extent permitted by
 * applicable law, but with the warranty of being written without ma-
 * licious intent or gross negligence; in no event shall licensor, an
 * author or contributor be held liable for any damage, direct, indi-
 * rect or other, however caused, arising in any way out of the usage
 * of this work, even if advised of the possibility of such damage.
 *-
 * globals for pkg_delete
 */

#ifndef PKG_DELETE_H
#define PKG_DELETE_H

extern bool CheckMD5;
extern bool CleanConf;
extern bool CleanDirs;
extern bool NoDeInstall;
extern bool KeepFiles;

extern char *Directory;
extern char *PkgName;
extern char *Prefix;

#endif
