/* $MirOS: src/usr.sbin/makefs/mbsdtree.h,v 1.1 2008/10/31 19:38:19 tg Exp $ */

#ifndef MBSDTREE_H
#define MBSDTREE_H

#include <sys/types.h>

__BEGIN_DECLS


/* lib/libc/stdlib/strsuftoll.c */

long long strsuftoll(const char *, const char *,
    long long, long long);
long long strsuftollx(const char *, const char *,
    long long, long long, char *, size_t)
    __attribute__((bounded (string, 5, 6)));

/* lib/libutil/stat_flags.c */

char *flags_to_string(u_long, const char *);
int string_to_flags(char **, u_long *, u_long *);


__END_DECLS

#endif
