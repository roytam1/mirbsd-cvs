/* $MirOS: contrib/code/jupp/path.c,v 1.7 2012/06/07 22:18:23 tg Exp $ */
/* 
 *	Directory and path functions
 *	Copyright
 *		(C) 1992 Joseph H. Allen
 *
 *	This file is part of JOE (Joe's Own Editor)
 */
#include "config.h"
#include "types.h"

#include <stdio.h>
#include <sys/types.h>
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#ifdef HAVE_PATHS_H
#  include <paths.h>	/* for _PATH_TMP */
#endif
#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_BSD_STRING_H
#include <bsd/string.h>
#endif

#include "path.h"
#include "vs.h"
#include "va.h"

#ifdef TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# ifdef HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

#ifdef HAVE_DIRENT_H
#  include <dirent.h>
#  define NAMLEN(dirent) strlen((dirent)->d_name)
#else
#  ifdef HAVE_SYS_DIRENT_H
#    include <sys/dirent.h>
#    define NAMLEN(dirent) strlen((dirent)->d_name)
#  else
#    define direct dirent
#    define NAMLEN(dirent) (dirent)->d_namlen
#    ifdef HAVE_SYS_NDIR_H
#      include <sys/ndir.h>
#    else
#      ifdef HAVE_SYS_DIR_H
#        include <sys/dir.h>
#      else
#        ifdef HAVE_NDIR_H
#          include <ndir.h>
#        else
#          ifndef __MSDOS__
#            include "dir.c"
#          endif
#        endif
#      endif
#    endif
#  endif
#endif

#ifdef __MSDOS__	/* paths in MS-DOS can include a drive letter followed by semicolon */
#define	do_if_drive_letter(path, command) do { \
						if ((path)[0] && (path)[1] == ':') { \
							command; \
						} \
					} while(0)
#else
#define do_if_drive_letter(path, command)	do { } while(0)
#endif
#define skip_drive_letter(path)	do_if_drive_letter((path), (path) += 2)

#ifndef		_PATH_TMP
#  ifdef __MSDOS__
#    define	_PATH_TMP	""
#  else
#    define	_PATH_TMP	"/tmp/"
#  endif
#endif

#if !defined(PATH_MAX) && !defined(HAVE_GET_CURRENT_DIR_NAME)
#warning What should we include to have PATH_MAX defined?
#define PATH_MAX	4096
#endif

/********************************************************************/
unsigned char *joesep(unsigned char *path)
{
	int x;

	for (x = 0; path[x]; ++x)
		if (path[x] == '\\')
			path[x] = '/';
	return path;
}
/********************************************************************/
unsigned char *namprt(unsigned char *path)
{
	unsigned char *z;

	skip_drive_letter(path);
	z = path + slen(path);
	while ((z != path) && (z[-1] != '/'))
		--z;
	return vsncpy(NULL, 0, sz(z));
}
/********************************************************************/
unsigned char *namepart(unsigned char *tmp, unsigned char *path)
{
	unsigned char *z;

	skip_drive_letter(path);
	z = path + strlen((char *)path);
	while ((z != path) && (z[-1] != '/'))
		--z;
	strlcpy((char *)tmp, (char *)z, 1024);
	return (tmp);
}
/********************************************************************/
unsigned char *dirprt(unsigned char *path)
{
	unsigned char *b = path;
	unsigned char *z = path + slen(path);

	skip_drive_letter(b);
	while ((z != b) && (z[-1] != '/'))
		--z;
	return vsncpy(NULL, 0, path, z - path);
}
/********************************************************************/
unsigned char *begprt(unsigned char *path)
{
	unsigned char *z = path + slen(path);
	int drv = 0;

	do_if_drive_letter(path, drv = 2);
	while ((z != path + drv) && (z[-1] == '/'))
		--z;
	if (z == path + drv)
		return vsncpy(NULL, 0, sz(path));
	else {
		while ((z != path + drv) && (z[-1] != '/'))
			--z;
		return vsncpy(NULL, 0, path, z - path);
	}
}
/********************************************************************/
unsigned char *endprt(unsigned char *path)
{
	unsigned char *z = path + slen(path);
	int drv = 0;

	do_if_drive_letter(path, drv = 2);
	while ((z != path + drv) && (z[-1] == '/'))
		--z;
	if (z == path + drv)
		return vsncpy(NULL, 0, sc(""));
	else {
		while (z != path + drv && z[-1] != '/')
			--z;
		return vsncpy(NULL, 0, sz(z));
	}
}
/********************************************************************/
int mkpath(unsigned char *path)
{
	unsigned char *s;

	if (path[0] == '/') {
		if (chddir("/"))
			return 1;
		s = path;
		goto in;
	}

	while (path[0]) {
		int c;

		for (s = path; (*s) && (*s != '/'); s++) ;
		c = *s;
		*s = 0;
		if (chddir((char *)path)) {
			if (mkdir((char *)path, 0777))
				return 1;
			if (chddir((char *)path))
				return 1;
		}
		*s = c;
	      in:
		while (*s == '/')
			++s;
		path = s;
	}
	return 0;
}
/********************************************************************/
/* Create a temporary file */
/********************************************************************/
unsigned char *mktmp(unsigned char *where)
{
#ifndef HAVE_MKSTEMP
	static unsigned seq = 0;
#endif
	unsigned char *name;
	int fd;
	unsigned namesize;

	if (!where)
		where = (unsigned char *)getenv("TEMP");
	if (!where)
		where = US _PATH_TMP;

	namesize = strlen((char *)where) + 20;
	name = vsmk(namesize);	/* [G.Ghibo'] we need to use vsmk() and not malloc() as
				   area returned by mktmp() is destroyed later with
				   vsrm(); */
#ifdef HAVE_MKSTEMP
	joe_snprintf_1((char *)name, namesize, "%s/joe.tmp.XXXXXXXXXX", where);
	if((fd = mkstemp((char *)name)) == -1)
		return NULL;	/* FIXME: vflsh() and vflshf() */
				/* expect mktmp() always succeed!!! */

	fchmod(fd, 0600);       /* Linux glibc 2.0 mkstemp() creates it with */
				/* 0666 mode --> change it to 0600, so nobody */
				/* else sees content of temporary file */
	close(fd);

#else
      loop:
	seq = (seq + 1) % 10000;
	joe_snprintf_3(name, namesize, "%s/joe.tmp.%04u%05u", where, seq, (unsigned) time(NULL) % 100000);
	if ((fd = open(name, O_RDONLY)) != -1) {
		close(fd);
		goto loop;	/* FIXME: possible endless loop --> DoS attack */
	}
#warning "Waah, this is insecure! Consider getting mkstemp!"
	if ((fd = open(name, O_RDWR | O_CREAT | O_EXCL, 0600)) == -1)
		return NULL;	/* FIXME: see above */
	else
		close(fd);
#endif
	return name;
}
/********************************************************************/
int rmatch(unsigned char *a, unsigned char *b)
{
	int flag, inv, c;

	for (;;)
		switch (*a) {
		case '*':
			++a;
			do {
				if (rmatch(a, b))
					return 1;
			} while (*b++);
			return 0;
		case '[':
			++a;
			flag = 0;
			if (*a == '^') {
				++a;
				inv = 1;
			} else
				inv = 0;
			if (*a == ']')
				if (*b == *a++)
					flag = 1;
			while (*a && (c = *a++) != ']')
				if ((c == '-') && (a[-2] != '[') && (*a)) {
					if ((*b >= a[-2]) && (*b <= *a))
						flag = 1;
				} else if (*b == c)
					flag = 1;
			if ((!flag && !inv) || (flag && inv) || (!*b))
				return 0;
			++b;
			break;
		case '?':
			++a;
			if (!*b)
				return 0;
			++b;
			break;
		case 0:
			if (!*b)
				return 1;
			else
				return 0;
		default:
			if (*a++ != *b++)
				return 0;
		}
}
/********************************************************************/
int isreg(unsigned char *s)
{
	int x;

	for (x = 0; s[x]; ++x)
		if ((s[x] == '*') || (s[x] == '?') || (s[x] == '['))
			return 1;
	return 0;
}
/********************************************************************/
#ifdef __MSDOS__
#include <dos.h>
#include <dir.h>

struct direct {
	unsigned char d_name[16];
} direc;
int dirstate = 0;
struct ffblk ffblk;
unsigned char *dirpath = NULL;

void *opendir(unsigned char *path)
{
	dirstate = 0;
	return &direc;
}

void closedir()
{
}

struct direct *readdir()
{
	int x;

	if (dirstate) {
		if (findnext(&ffblk))
			return NULL;
	} else {
		if (findfirst("*.*", &ffblk, FA_DIREC))
			return NULL;
		dirstate = 1;
	}

	strcpy(direc.d_name, ffblk.ff_name);
	for (x = 0; direc.d_name[x]; ++x)
		direc.d_name[x] = tolower(direc.d_name[x]);
	return &direc;
}
#endif
/********************************************************************/
unsigned char **rexpnd(unsigned char *word)
{
	void *dir;
	unsigned char **lst = NULL;

	struct dirent *de;
	dir = opendir(".");
	if (dir) {
		while ((de = readdir(dir)) != NULL)
			if (strcmp(".", de->d_name))
				if (rmatch(word, (unsigned char *)de->d_name))
					lst = vaadd(lst, vsncpy(NULL, 0, sz((unsigned char *)de->d_name)));
		closedir(dir);
	}
	return lst;
}
/********************************************************************/
int chpwd(unsigned char *path)
{
#ifdef __MSDOS__
	unsigned char buf[256];
	int x;

	if (!path)
		return 0;
	if ((path[0]) && (path[1] == ':')) {
		if (_chdrive(path[0] & 0x1F))
			return -1;
		path += 2;
	}
	if (!path[0])
		return 0;
	strcpy(buf, path);
	x = strlen(buf);
	while (x > 1) {
		--x;
		if ((buf[x] == '/') || (buf[x] == '\\'))
			buf[x] = 0;
		else
			break;
	}
	return chdir(buf);
#else
	if ((!path) || (!path[0]))
		return 0;
	return chdir((char *)path);
#endif
}

/* The pwd function */
unsigned char *pwd(void)
{
#if defined(PATH_MAX) || !defined(HAVE_GET_CURRENT_DIR_NAME)
	static unsigned char buf[PATH_MAX];
	unsigned char	*ret;

#ifdef HAVE_GETCWD
	ret = (unsigned char *)getcwd((char *)buf, PATH_MAX - 1);
#else
	ret = (unsigned char *)getwd((char *)buf);
#endif
	buf[PATH_MAX - 1] = '\0';

	return ret;
#else
	/* Hurd */
	static char *wd = NULL;

	free(wd);
	wd = get_current_dir_name();
	return ((void *)wd);
#endif
}