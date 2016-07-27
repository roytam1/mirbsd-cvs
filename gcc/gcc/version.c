/* $MirOS: gcc/gcc/version.c,v 1.56 2015/01/23 19:17:58 tg Exp $ */

#include "version.h"

/* This is the string reported as the version number by all components
   of the compiler.  If you distribute a modified version of GCC,
   please modify this string to indicate that, e.g. by putting your
   organization's name in parentheses at the end of the string.  */

const char version_string[] = "3.4.6 (propolice; gpc; MirOS 0AB7)";

/* This is the location of the online document giving instructions for
   reporting bugs.  If you distribute a modified version of GCC,
   please change this to refer to a document giving instructions for
   reporting bugs to you, not us.  (You are of course welcome to
   forward us bugs reported to you, if you determine that they are
   not bugs in your modifications.)  */

#ifdef GPC
const char bug_report_url[] = "<URL:http://www.gnu-pascal.de/todo.html>";
#else
const char bug_report_url[] = "<URL:https://www.mirbsd.org/>";
#endif

/* This is for mbsd_bug (binutils-and-gcc cross build package) */
#ifdef MBSD_BUG
/* get this from libmirmake or similar */
#include "md5.c"
#endif
