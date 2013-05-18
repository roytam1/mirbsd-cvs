#define MKSH_COMPAT_H_ID "$MirOS$"

#ifdef NEED_COMPAT
/* Part I: extra headers */

#if defined(__sun__) || defined(__INTERIX)
#include <sys/mkdev.h>
#endif
#if !defined(__OpenBSD__) && !defined(__CYGWIN__)
#include <ulimit.h>
#endif
#if defined(__sun__) || defined(__gnu_linux__)
#include <values.h>
#endif


/* Part II: extra macros */

#ifndef timeradd
#define	timeradd(tvp, uvp, vvp)						\
	do {								\
		(vvp)->tv_sec = (tvp)->tv_sec + (uvp)->tv_sec;		\
		(vvp)->tv_usec = (tvp)->tv_usec + (uvp)->tv_usec;	\
		if ((vvp)->tv_usec >= 1000000) {			\
			(vvp)->tv_sec++;				\
			(vvp)->tv_usec -= 1000000;			\
		}							\
	} while (0)
#endif
#ifndef timersub
#define	timersub(tvp, uvp, vvp)						\
	do {								\
		(vvp)->tv_sec = (tvp)->tv_sec - (uvp)->tv_sec;		\
		(vvp)->tv_usec = (tvp)->tv_usec - (uvp)->tv_usec;	\
		if ((vvp)->tv_usec < 0) {				\
			(vvp)->tv_sec--;				\
			(vvp)->tv_usec += 1000000;			\
		}							\
	} while (0)
#endif

#ifndef S_ISTXT
#define S_ISTXT 0001000
#endif


/* Part III: OS-dependent additions */

#if defined(__gnu_linux__)
size_t strlcat(char *, const char *, size_t);
size_t strlcpy(char *, const char *, size_t);
#endif

#if defined(__sun__)
size_t confstr(int, char *, size_t);
#endif

#if defined(__gnu_linux__) || defined(__sun__) || defined(__CYGWIN__)
#define DEFFILEMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
mode_t getmode(const void *, mode_t);
void *setmode(const char *);
#endif

#ifdef __INTERIX
#define	makedev(x,y)	mkdev((x),(y))
extern int __cdecl seteuid(uid_t);
extern int __cdecl setegid(gid_t);
#endif

#endif
