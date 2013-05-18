/* $MirOS: src/lib/libc/include/mir18n.h,v 1.2 2006/05/30 10:02:30 tg Exp $ */

#ifndef _LIBC_MIR18N_H
#define _LIBC_MIR18N_H

/* highest allowed character in 'C' locale */
#define MIR18N_SB_MAX	0xFF
/* set to 0xFF to allow conversion from/to latin1 for historical reasons */
#define MIR18N_SB_CVT	0xFF
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
