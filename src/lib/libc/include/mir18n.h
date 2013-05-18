/* $MirOS: src/lib/libc/include/mir18n.h,v 1.1 2006/05/21 12:12:30 tg Exp $ */

#ifndef _LIBC_MIR18N_H
#define _LIBC_MIR18N_H

/* highest allowed character in 'C' locale */
#define MIR18N_SB_MAX	0xFF
/* highest allowed character in 'UTF-8' locale */
#define MIR18N_MB_MAX	0xFFFD

#ifndef __BEGIN_DECLS
#include <sys/cdefs.h>
#endif

#ifndef __bool_true_false_are_defined
#include <stdbool.h>
#endif

__BEGIN_DECLS
extern bool __locale_is_utf8;
__END_DECLS

#endif
