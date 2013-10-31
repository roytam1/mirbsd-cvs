/* $MirOS: src/include/nl_types.h,v 1.7 2007/02/02 21:22:43 tg Exp $ */

#ifndef _NL_TYPES_H_
#define _NL_TYPES_H_

#include <sys/cdefs.h>

#define NL_SETD		1
#define NL_CAT_LOCALE	1

typedef int nl_catd;
typedef int nl_item;

__BEGIN_DECLS
nl_catd catopen(const char *, int);
char *catgets(nl_catd, int, int, const char *)
    __attribute__((__format_arg__(4)));
int catclose(nl_catd);
__END_DECLS

#define catopen(s,f)		(0)
#define catgets(cid,sid,mid,s)	(s)
#define catclose(n)		(0)

#endif
