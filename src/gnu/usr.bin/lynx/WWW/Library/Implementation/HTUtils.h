/*
 * $LynxId: HTUtils.h,v 1.77 2007/07/01 15:30:33 tom Exp $
 *
 * Utility macros for the W3 code library
 * MACROS FOR GENERAL USE
 * 
 * See also:  the system dependent file "www_tcp.h", which is included here.
 */

#ifndef NO_LYNX_TRACE
#define DEBUG			/* Turns on trace; turn off for smaller binary */
#endif

#ifndef HTUTILS_H
#define HTUTILS_H

#ifdef HAVE_CONFIG_H
#include <lynx_cfg.h>		/* generated by autoconf 'configure' script */

/* see AC_FUNC_ALLOCA macro */
#ifdef __GNUC__
# define alloca __builtin_alloca
#else
# ifdef _MSC_VER
#  include <malloc.h>
#  define alloca _alloca
# else
#  if HAVE_ALLOCA_H
#   include <alloca.h>
#  else
#   ifdef _AIX
#pragma alloca
#   else
#    ifndef alloca		/* predefined by HP cc +Olibcalls */
char *alloca();

#    endif
#   endif
#  endif
# endif
#endif

#include <sys/types.h>
#include <stdio.h>

#else /* HAVE_CONFIG_H */

#ifdef DJGPP
#include <sys/config.h>		/* pseudo-autoconf values for DJGPP libc/headers */
#define HAVE_TRUNCATE 1
#define HAVE_ALLOCA 1
#include <limits.h>
#endif /* DJGPP */

#include <stdio.h>

#define DONT_TRACK_INTERNAL_LINKS 1

/* Explicit system-configure */
#ifdef VMS
#define NO_SIZECHANGE

#if defined(VAXC) && !defined(__DECC)
#define NO_UNISTD_H		/* DEC C has unistd.h, but not VAX C */
#endif

#define NO_KEYPAD
#define NO_UTMP

#undef NO_FILIO_H
#define NO_FILIO_H

#define NOUSERS
#define DISP_PARTIAL		/* experimental */
#endif

/* since 2.8.6dev.1, Lynx requires an ANSI C (c89) compiler */
#define ANSI_VARARGS 1
#undef HAVE_STDARG_H
#define HAVE_STDARG_H 1

#if defined(VMS) || defined(_WINDOWS)
#define HAVE_STDLIB_H 1
#endif

/* Accommodate non-autoconf'd Makefile's (VMS, DJGPP, etc) */

#ifndef NO_ARPA_INET_H
#define HAVE_ARPA_INET_H 1
#endif

#ifndef NO_CBREAK
#define HAVE_CBREAK 1
#endif

#ifndef NO_CUSERID
#define HAVE_CUSERID 1
#endif

#ifndef NO_FILIO_H
#define HAVE_SYS_FILIO_H 1
#endif

#ifndef NO_GETCWD
#define HAVE_GETCWD 1
#endif

#ifndef USE_SLANG
#ifndef NO_KEYPAD
#define HAVE_KEYPAD 1
#endif
#ifndef NO_TTYTYPE
#define HAVE_TTYTYPE 1
#endif
#endif /* USE_SLANG */

#ifndef NO_PUTENV
#define HAVE_PUTENV 1
#endif

#ifndef NO_SIZECHANGE
#define HAVE_SIZECHANGE 1
#endif

#ifndef NO_UNISTD_H
#undef  HAVE_UNISTD_H
#define HAVE_UNISTD_H 1
#endif

#ifndef NO_UTMP
#define HAVE_UTMP 1
#endif

#endif /* HAVE_CONFIG_H */

/* suppress inadvertant use of gettext in makeuctb when cross-compiling */
#ifdef DONT_USE_GETTEXT
#undef HAVE_GETTEXT
#undef HAVE_LIBGETTEXT_H
#undef HAVE_LIBINTL_H
#endif

#ifndef lynx_srand
#define lynx_srand srand
#endif

#ifndef lynx_rand
#define lynx_rand rand
#endif

#if '0' != 48
#define NOT_ASCII
#endif

#if '0' == 240
#define EBCDIC
#endif

#ifndef LY_MAXPATH
#define LY_MAXPATH 256
#endif

#ifndef	GCC_NORETURN
#define	GCC_NORETURN		/* nothing */
#endif

#ifndef	GCC_UNUSED
#define	GCC_UNUSED		/* nothing */
#endif

#if defined(__CYGWIN32__) && ! defined(__CYGWIN__)
#define __CYGWIN__ 1
#endif

#if defined(__CYGWIN__)		/* 1998/12/31 (Thu) 16:13:46 */
#include <windows.h>		/* #include "windef.h" */
#define BOOLEAN_DEFINED
#undef HAVE_POPEN		/* FIXME: does this not work, or is it missing */
#undef small			/* see <w32api/rpcndr.h> */
#endif

/* cygwin, mingw32, etc. */
#ifdef FILE_DOES_NOT_EXIST
#undef FILE_DOES_NOT_EXIST	/* see <w32api/winnt.h> */
#endif

/*
 * VS .NET 2003 includes winsock.h unconditionally from windows.h,
 * so we do not want to include windows.h if we want winsock2.h
 */
#if defined(_WINDOWS) && !defined(__CYGWIN__)

#if defined(USE_WINSOCK2_H) && (_MSC_VER >= 1300) && (_MSC_VER < 1400)
#include <winsock2.h>		/* includes windows.h, in turn windef.h */
#else
#include <windows.h>		/* #include "windef.h" */
#endif

#define BOOLEAN_DEFINED

#if !_WIN_CC			/* 1999/09/29 (Wed) 22:00:53 */
#include <dos.h>
#endif

#undef sleep			/* 1998/06/23 (Tue) 16:54:53 */
extern void sleep(unsigned __seconds);

#define popen _popen
#define pclose _pclose

#if defined(_MSC_VER)
typedef unsigned short mode_t;
#endif

#endif /* _WINDOWS */

#if defined(USE_DEFAULT_COLORS) && !defined(HAVE_USE_DEFAULT_COLORS)
    /* if we don't have use_default_colors() */
#  undef USE_DEFAULT_COLORS
#endif

#ifndef USE_COLOR_STYLE
    /* it's useless for such setup */
#  define NO_EMPTY_HREFLESS_A
#endif

#if  defined(__EMX__) || defined(WIN_EX) || defined(HAVE_POPEN)
#  define CAN_CUT_AND_PASTE
#endif

#if defined(USE_SLANG) || (defined(USE_COLOR_STYLE) && defined(__EMX__))
#  define USE_BLINK
#endif

#if defined(DOSPATH) || defined(__EMX__)
#  define USE_DOS_DRIVES	/* we allow things like "c:" in paths */
#endif

#if defined(UNIX)
#  if (defined(__BEOS__) || defined(__CYGWIN__) || defined(__DJGPP__) || defined(__EMX__) || defined(__MINGW32__))
#    define SINGLE_USER_UNIX	/* well, at least they try */
#  else
#    define MULTI_USER_UNIX
#  endif
#endif

/*

  ERROR TYPE

   This is passed back when streams are aborted. It might be nice to have some structure
   of error messages, numbers, and recursive pointers to reasons.  Curently this is a
   placeholder for something more sophisticated.

 */
typedef void *HTError;		/* Unused at present -- best definition? */

/*

Standard C library for malloc() etc

 */
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

#ifdef __EMX__
#include <unistd.h>		/* should be re-include protected under EMX */
#define getcwd _getcwd2
#define chdir _chdir2
#endif

#ifdef vax
#ifdef unix
#define ultrix			/* Assume vax+unix=ultrix */
#endif /* unix */
#endif /* vax */

#ifndef VMS
#ifndef ultrix

#ifdef NeXT
#include <libc.h>		/* NeXT */
#endif /* NeXT */

#else /* ultrix: */

#include <malloc.h>
#include <memory.h>

#endif /* !ultrix */
#else /* VMS: */

#include <unixlib.h>
#if defined(VAXC) && !defined(__DECC)
#define malloc	VAXC$MALLOC_OPT
#define calloc	VAXC$CALLOC_OPT
#define free	VAXC$FREE_OPT
#define cfree	VAXC$CFREE_OPT
#define realloc	VAXC$REALLOC_OPT
#endif /* VAXC && !__DECC */

#endif /* !VMS */

#ifndef NULL
#define NULL ((void *)0)
#endif

#define isEmpty(s)   ((s) == 0 || *(s) == 0)

#define NonNull(s) (((s) != 0) ? s : "")
#define NONNULL(s) (((s) != 0) ? s : "(null)")

/* array/table size */
#define	TABLESIZE(v)	(sizeof(v)/sizeof(v[0]))

#define	typecalloc(cast)		(cast *)calloc(1,sizeof(cast))
#define	typecallocn(cast,ntypes)	(cast *)calloc(ntypes,sizeof(cast))

#define typeRealloc(cast,ptr,ntypes)    (cast *)realloc(ptr, (ntypes)*sizeof(cast))

#define typeMalloc(cast)                (cast *)malloc(sizeof(cast))
#define typeMallocn(cast,ntypes)        (cast *)malloc((ntypes)*sizeof(cast))

/*

OFTEN USED INTEGER MACROS

  Min and Max functions

 */
#ifndef HTMIN
#define HTMIN(a,b) ((a) <= (b) ? (a) : (b))
#define HTMAX(a,b) ((a) >= (b) ? (a) : (b))
#endif
/*

Booleans

 */
/* Note: GOOD and BAD are already defined (differently) on RS6000 aix */
/* #define GOOD(status) ((status)38;1)   VMS style status: test bit 0         */
/* #define BAD(status)  (!GOOD(status))  Bit 0 set if OK, otherwise clear   */

#ifndef _WINDOWS
#ifndef BOOLEAN_DEFINED
typedef char BOOLEAN;		/* Logical value */

#ifndef CURSES
#ifndef TRUE
#define TRUE    (BOOLEAN)1
#define FALSE   (BOOLEAN)0
#endif
#endif /*  CURSES  */
#endif /*  BOOLEAN_DEFINED */
#define BOOLEAN_DEFINED
#endif /* _WINDOWS */

#if defined(_MSC_VER) && (_MSC_VER >= 1300)
/* it declares BOOL/BOOLEAN as BYTE/int */
#else
#ifndef BOOL
#define BOOL BOOLEAN
#endif
#endif

#ifndef YES
#define YES (BOOLEAN)1
#define NO (BOOLEAN)0
#endif

extern BOOL LYOutOfMemory;	/* Declared in LYexit.c - FM */

#define TCP_PORT 80		/* Allocated to http by Jon Postel/ISI 24-Jan-92 */
#define OLD_TCP_PORT 2784	/* Try the old one if no answer on 80 */
#define DNP_OBJ 80		/* This one doesn't look busy, but we must check */
			/* That one was for decnet */

/*      Inline Function WHITE: Is character c white space? */
/*      For speed, include all control characters */

#define WHITE(c) ((UCH(TOASCII(c))) <= 32)

/*     Inline Function LYIsASCII: Is character c a traditional ASCII
 *     character (i.e. <128) after converting from host character set.  */

#define LYIsASCII(c) (TOASCII(UCH(c)) < 128)

/*

Success (>=0) and failure (<0) codes

Some of the values are chosen to be HTTP-like, but status return values
are generally not the response status from any specific protocol.

 */

#define HT_PARSER_OTHER_CONTENT  701	/* tells SGML to change content model */
#define HT_PARSER_REOPEN_ELT     700	/* tells SGML parser to keep tag open */
#define HT_REDIRECTING           399
#define HT_PARTIAL_CONTENT       206	/* Partial Content */
#define HT_LOADED                200	/* Instead of a socket */

#define HT_OK                      0	/* Generic success */

#define HT_ERROR                  -1	/* Generic failure */
#define HT_CANNOT_TRANSLATE       -4
#define HT_BAD_EOF               -12	/* Premature EOF */
#define HT_NO_CONNECTION         -99	/* ERR no connection available - */
#define HT_NO_DATA              -204	/* OK but no data was loaded - */
					/* possibly other app started or forked */
#define HT_NO_ACCESS            -401	/* Access not available */
#define HT_FORBIDDEN            -403	/* Access forbidden */
#define HT_NOT_ACCEPTABLE       -406	/* Not Acceptable */
#define HT_H_ERRNO_VALID        -800	/* see h_errno for resolver error */
#define HT_INTERNAL             -900	/* Weird -- should never happen. */
#define HT_INTERRUPTED        -29998
#define HT_NOT_LOADED         -29999

#ifndef va_arg
# if defined(HAVE_STDARG_H) && defined(ANSI_VARARGS)
#  include <stdarg.h>
# else
#  if HAVE_VARARGS_H
#   include <varargs.h>
#  endif
# endif
#endif

#if defined(ANSI_VARARGS)
#define LYva_start(ap,format) va_start(ap,format)
#else
#define LYva_start(ap,format) va_start(ap)
#endif

/*
 * GCC can be told that some functions are like printf (and do type-checking on
 * their parameters).
 */
#ifndef GCC_PRINTFLIKE
#if defined(GCC_PRINTF) && !defined(printf) && !defined(HAVE_LIBUTF8_H)
#define GCC_PRINTFLIKE(fmt,var) __attribute__((format(printf,fmt,var)))
#else
#define GCC_PRINTFLIKE(fmt,var)	/*nothing */
#endif
#endif

#include <HTString.h>		/* String utilities */

/*

Out Of Memory checking for malloc() return:

 */
#ifndef __FILE__
#define __FILE__ ""
#define __LINE__ ""
#endif

#include <LYexit.h>

/*
 * Upper- and Lowercase macros
 *
 * The problem here is that toupper(x) is not defined officially unless
 * isupper(x) is.  These macros are CERTAINLY needed on #if defined(pyr) ||
 * define(mips) or BDSI platforms.  For safefy, we make them mandatory.
 *
 * Note: Pyramid and Mips can't uppercase non-alpha.
 */
#include <ctype.h>
#include <string.h>

#ifndef TOLOWER

#ifdef EXP_ASCII_CTYPES

#define TOLOWER(c) ascii_tolower(UCH(c))
#define TOUPPER(c) ascii_toupper(UCH(c))
#define ISUPPER(c) ascii_isupper(UCH(c))

#else

#define TOLOWER(c) (isupper(UCH(c)) ? tolower(UCH(c)) : UCH(c))
#define TOUPPER(c) (islower(UCH(c)) ? toupper(UCH(c)) : UCH(c))
#define ISUPPER(c) (isupper(UCH(c)))

#endif

#endif /* TOLOWER */

#define FREE(x)    {if (x != 0) {free((char *)x); x = NULL;}}

/*

The local equivalents of CR and LF

   We can check for these after net ascii text has been converted to the local
   representation.  Similarly, we include them in strings to be sent as net ascii after
   translation.

 */
#define LF   FROMASCII('\012')	/* ASCII line feed LOCAL EQUIVALENT */
#define CR   FROMASCII('\015')	/* Will be converted to ^M for transmission */

/*
 * Debug message control.
 */
#ifdef NO_LYNX_TRACE
#define WWW_TraceFlag   0
#define WWW_TraceMask   0
#define LYTraceLogFP    0
#else
extern BOOLEAN WWW_TraceFlag;
extern int WWW_TraceMask;
#endif

#define TRACE           (WWW_TraceFlag)
#define TRACE_bit(n)    (TRACE && (WWW_TraceMask & (1 << n)) != 0)
#define TRACE_SGML      (TRACE_bit(0))
#define TRACE_STYLE     (TRACE_bit(1))
#define TRACE_TRST      (TRACE_bit(2))
#define TRACE_CFG       (TRACE_bit(3))
#define TRACE_BSTRING   (TRACE_bit(4))
#define TRACE_COOKIES   (TRACE_bit(5))
#define TRACE_CHARSETS  (TRACE_bit(6))
#define TRACE_GRIDTEXT  (TRACE_bit(7))
#define TRACE_TIMING    (TRACE_bit(8))

#if defined(USE_VERTRACE) && !defined(LY_TRACELINE)
#define LY_TRACELINE __LINE__
#endif

#if defined(LY_TRACELINE)
#define LY_SHOWWHERE fprintf( tfp, "%s: %d: ", __FILE__, LY_TRACELINE ),
#else
#define LY_SHOWWHERE		/* nothing */
#endif

#define CTRACE(p)         ((void)((TRACE) && ( LY_SHOWWHERE fprintf p )))
#define CTRACE2(m,p)      ((void)((m)     && ( LY_SHOWWHERE fprintf p )))
#define tfp TraceFP()
#define CTRACE_SLEEP(secs) if (TRACE && LYTraceLogFP == 0) sleep(secs)
#define CTRACE_FLUSH(fp)   if (TRACE) fflush(fp)

#include <www_tcp.h>

/*
 * We force this include-ordering since socks.h contains redefinitions of
 * functions that probably are prototyped via other includes.  The socks.h
 * definitions have to be included everywhere, since they're making wrappers
 * for the stdio functions as well as the network functions.
 */
#if defined(USE_SOCKS5) && !defined(DONT_USE_SOCKS5)
#define SOCKS4TO5		/* turn on the Rxxxx definitions used in Lynx */
#include <socks.h>

/*
 * The AIX- and SOCKS4-specific definitions in socks.h are inconsistent.
 * Repair them so they're consistent (and usable).
 */
#if defined(_AIX) && !defined(USE_SOCKS4_PREFIX)
#undef  Raccept
#define Raccept       accept
#undef  Rgetsockname
#define Rgetsockname  getsockname
#undef  Rgetpeername
#define Rgetpeername  getpeername
#endif

/*
 * Workaround for order-of-evaluation problem with gcc and socks5 headers
 * which breaks the Rxxxx names by attaching the prefix twice:
 */
#ifdef INCLUDE_PROTOTYPES
#undef  Raccept
#undef  Rbind
#undef  Rconnect
#undef  Rlisten
#undef  Rselect
#undef  Rgetpeername
#undef  Rgetsockname
#define Raccept       accept
#define Rbind         bind
#define Rconnect      connect
#define Rgetpeername  getpeername
#define Rgetsockname  getsockname
#define Rlisten       listen
#define Rselect       select
#endif

#endif /* USE_SOCKS5 */

#define SHORTENED_RBIND		/* FIXME: do this in configure-script */

#ifdef USE_SSL
#define free_func free__func

#ifdef USE_OPENSSL_INCL
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <openssl/err.h>

#else

#ifdef USE_GNUTLS_INCL
#include <gnutls/openssl.h>
/*
 * GNUTLS's implementation of OpenSSL is very incomplete and rudimentary.
 * For a start, let's make it compile (TD - 2003/4/13).
 */
#ifndef SSL_VERIFY_PEER
#define SSL_VERIFY_PEER			0x01
#endif

#else /* assume SSLeay */
#include <ssl.h>
#include <crypto.h>
#include <rand.h>
#include <err.h>
#endif
#endif /* USE_OPENSSL_INCL */

#undef free_func

#endif /* USE_SSL */

#ifdef HAVE_LIBDMALLOC
#include <dmalloc.h>		/* Gray Watson's library */
#define show_alloc() dmalloc_log_unfreed()
#endif

#ifdef HAVE_LIBDBMALLOC
#include <dbmalloc.h>		/* Conor Cahill's library */
#define show_alloc() malloc_dump(fileno(stderr))
#endif

#ifndef show_alloc
#define show_alloc()		/* nothing */
#endif

#include <userdefs.h>

#ifdef __cplusplus
extern "C" {
#endif
#ifndef TOLOWER
#ifdef EXP_ASCII_CTYPES
    extern int ascii_toupper(int);
    extern int ascii_tolower(int);
    extern int ascii_isupper(int);
#endif
#endif

    extern FILE *TraceFP(void);

#ifdef USE_SSL
    extern SSL *HTGetSSLHandle(void);
    extern void HTSSLInitPRNG(void);
    extern char HTGetSSLCharacter(void *handle);
#endif				/* USE_SSL */

#ifdef __cplusplus
}
#endif
#endif				/* HTUTILS_H */
