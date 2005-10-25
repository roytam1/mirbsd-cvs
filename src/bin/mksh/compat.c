#include "sh.h"

__RCSID("$MirOS$");

#ifndef __SCCSID
#define	__SCCSID(x)	static const char __sccsid[] __attribute__((used)) = (x)
#endif

#if defined(__gnu_linux__) || defined(__sun__)
#include "setmode.c"
#endif
