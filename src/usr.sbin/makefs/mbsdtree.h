/* $MirOS$ */

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


__END_DECLS

#endif
