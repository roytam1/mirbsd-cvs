/* $MirOS: ports/infrastructure/pkgtools/delete/delete.h,v 1.3 2005/12/17 05:46:19 tg Exp $ */

#ifndef PKG_DELETE_H
#define PKG_DELETE_H

extern bool CheckMD5;
extern rm_cfg_t CleanConf;
extern bool CleanDirs;
extern bool NoDeInstall;
extern bool KeepFiles;

extern char *Directory;
extern char *PkgName;
extern char *Prefix;

#endif
