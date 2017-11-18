#include <stddef.h>
#include <stdio.h>

#if defined(HAVE_STDIO_EXT_H) && (HAVE_STDIO_EXT_H)
# include <stdio_ext.h>
#endif

#ifndef HAVE_DECL___FPENDING
"this configure-time declaration test was not run"
#endif
#if !HAVE_DECL___FPENDING
size_t __fpending (FILE *);
#endif
