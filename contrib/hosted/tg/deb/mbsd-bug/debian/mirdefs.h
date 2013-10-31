/* $MirOS$ */
/* from mksh’s "sh.h" (also in Debian) */

#undef __IDSTRING
#undef __IDSTRING_CONCAT
#undef __IDSTRING_EXPAND
#undef __RCSID
#undef __SCCSID
#define __IDSTRING_CONCAT(l,p)		__LINTED__ ## l ## _ ## p
#define __IDSTRING_EXPAND(l,p)		__IDSTRING_CONCAT(l,p)
#define __IDSTRING(prefix, string)				\
	static const char __IDSTRING_EXPAND(__LINE__,prefix) []	\
	    __attribute__((__used__)) = "@(""#)" #prefix ": " string
#define __RCSID(x)	__IDSTRING(rcsid,x)
#define __SCCSID(x)	__IDSTRING(sccsid,x)
