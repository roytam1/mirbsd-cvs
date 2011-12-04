/* $MirOS: gcc/gcc/version.c,v 1.8 2005/04/17 03:17:48 tg Exp $ */

#include "version.h"

/* This is the string reported as the version number by all components
   of the compiler.  If you distribute a modified version of GCC,
   please modify this string to indicate that, e.g. by putting your
   organization's name in parentheses at the end of the string.  */

/* Must be one line.  */
const char real_version_string[] = "3.4.4 20050415 (propolice; MirOS 0828)", *version_string = real_version_string;

/* This is the location of the online document giving instructions for
   reporting bugs.  If you distribute a modified version of GCC,
   please change this to refer to a document giving instructions for
   reporting bugs to you, not us.  (You are of course welcome to
   forward us bugs reported to you, if you determine that they are
   not bugs in your modifications.)  */

#ifdef GPC
const char bug_report_url[] = "<URL:http://www.gnu-pascal.de/todo.html>";
#else
const char bug_report_url[] = "<URL:http://MirBSD.org/>";
#endif
