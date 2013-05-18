#include "sh.h"

__RCSID("$MirOS: src/bin/mksh/compat.c,v 1.1.2.7 2005/11/19 23:51:01 tg Exp $");

#if defined(__gnu_linux__) || defined(__sun__) || defined(__CYGWIN__)
#include "setmode.c"
#endif
