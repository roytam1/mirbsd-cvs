/* $MirOS: ports/infrastructure/pkgtools/delete/delete.h,v 1.2 2005/11/19 02:05:28 bsiegert Exp $ */

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
