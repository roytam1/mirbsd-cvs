#include "sh.h"

__RCSID("$MirOS: src/bin/mksh/compat.c,v 1.1.2.6 2005/10/26 08:45:32 tg Exp $");

#ifndef __SCCSID
#define	__SCCSID(x)	static const char __sccsid[] __attribute__((used)) = (x)
#endif

#undef __RCSID
#undef __RCSID2
#define	__RCSID2(x,y)	static const char __rcsid_ ## _y[] __attribute__((used)) = (x)

#if defined(__gnu_linux__) || defined(__sun__) || defined(__CYGWIN__)
#define	__RCSID(x)	__RCSID2((x),setmode)
#include "setmode.c"
#undef __RCSID
#endif
