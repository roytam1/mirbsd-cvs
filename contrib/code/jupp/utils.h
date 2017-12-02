/*
 *	Various utilities
 *
 *	Copyright
 *		(C) 1992 Joseph H. Allen
 *		(C) 2001 Marek 'Marx' Grac
 *
 *	This file is part of JOE (Joe's Own Editor)
 */
#ifndef _JOE_UTILS_H
#define _JOE_UTILS_H 1

#ifdef EXTERN_B_C
__IDSTRING(rcsid_utils_h, "$MirOS: contrib/code/jupp/utils.h,v 1.7 2017/12/02 03:52:35 tg Exp $");
#endif

#ifdef HAVE_SIGNAL_H
#include <signal.h>
#endif

/*
 * Functions which return minimum/maximum of two numbers
 */
unsigned int uns_min PARAMS((unsigned int a, unsigned int b));
signed int int_min PARAMS((signed int a, int signed b));
signed long long_max PARAMS((signed long a, signed long b));
signed long long_min PARAMS((signed long a, signed long b));

/* Versions of 'read' and 'write' which automatically retry when interrupted */
ssize_t joe_read PARAMS((int fd, void *buf, size_t siz));
ssize_t joe_write PARAMS((int fd, void *buf, size_t siz));

/* wrappers to *alloc routines */
#define joe_malloc malloc
#define joe_calloc calloc
#define joe_realloc realloc
#define joe_free free

#ifndef HAVE_SIGHANDLER_T
typedef RETSIGTYPE (*sighandler_t)(int);
#endif

#ifdef NEED_TO_REINSTALL_SIGNAL
#define REINSTALL_SIGHANDLER(sig, handler) joe_set_signal(sig, handler)
#else
#define REINSTALL_SIGHANDLER(sig, handler) do {} while(0)
#endif

/* wrapper to hide signal interface differrencies */
int joe_set_signal PARAMS((int signum, sighandler_t handler));

int parse_ws PARAMS((unsigned char **p,int cmt));
int parse_ident PARAMS((unsigned char **p,unsigned char *buf,int len));
int parse_kw PARAMS((unsigned char **p,unsigned char *kw));
int parse_tows PARAMS((unsigned char **p,unsigned char *buf));
int parse_field PARAMS((unsigned char **p,unsigned char *field));
int parse_char PARAMS((unsigned char  **p,unsigned char c));
int parse_string PARAMS((unsigned char **p,unsigned char *buf,int len));
int parse_range PARAMS((unsigned char **p,int *first,int *second));

void tty_xonoffbaudrst(void);

/* from compat.c */

#define USTOL_AUTO	0x00
#define USTOL_DEC	0x01
#define USTOL_HEX	0x02
#define USTOL_OCT	0x03
#define USTOL_LTRIM	0x04
#define USTOL_RTRIM	0x08
#define USTOL_TRIM	0x0C
#define USTOL_EOS	0x10

long ustol(void *, void **, int);
long ustolb(void *, void **, long, long, int);

#define USTOC_MAX	4 /* arbitrary, but at least 4 */

size_t ustoc_hex(const void *, int *, size_t);
size_t ustoc_oct(const void *, int *, size_t);

#endif
