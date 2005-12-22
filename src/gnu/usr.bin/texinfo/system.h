/* $MirOS$ */

#ifndef	_SYSTEM_H
#define	_SYSTEM_H

#define	_GNU_SOURCE
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <config.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <stdarg.h>
#include <pwd.h>
#include "libiberty.h"

#define SET_BINARY(f)	(void)0
#define FOPEN_RBIN	"r"
#define FOPEN_WBIN	"w"
#define IS_SLASH(c)	((c) == '/')
#define HAVE_DRIVE(n)	(0)
#define IS_ABSOLUTE(n)	((n)[0] == '/')
#define FILENAME_CMP	strcmp
#define FILENAME_CMPN	strncmp
#define HAVE_LONG_FILENAMES(dir)   (1)
#define PATH_SEP	":"
#define STRIP_DOT_EXE	0
#define DEFAULT_TMPDIR "/tmp/"
#define NULL_DEVICE	"/dev/null"
#define PIPE_USE_FORK	1
#define	_(x)		(x)
#define	N_(x)		(x)
#define	O_BINARY	0
#define	STREQ(a,b)	(!strcmp((a),(b)))
#undef	VA_START
#define	VA_START	va_start
#define	VA_FPRINTF	vfprintf
#define	VA_SPRINTF	vsprintf
#undef	HAVE_SETLOCALE

char *substring(const char *, const char *);

#endif
