/* $MirOS: src/lib/libc/include/mir18n.h,v 1.17 2007/02/07 17:34:07 tg Exp $ */

#ifndef _LIBC_MIR18N_H
#define _LIBC_MIR18N_H

#if !defined(WCHAR_MAX)
#error Include <wchar.h> first
#elif WCHAR_MAX != 0xFFFD
#error This code assumes that wchar_t is UCS-2HE
#endif

#ifdef mir18n_attributes
/* from Bruno Haible's libutf8 */

/* How the 12 character attributes are encoded in 8 bits: Every attribute is
   represented by an "include bitmask" and an "exclude bitmask".
    Attribute	bit/formula		comment
     upper	upper && !lower		implies towlower(x) != x == towupper(x)
     lower	!upper && lower		implies towlower(x) == x != towupper(x)
     title	upper && lower		implies towlower(x) != x != towupper(x)
     alpha	bit			superset of upper || lower
     digit	xdigit && !alpha	'0'..'9' and more
     xdigit	bit			'0'..'9','a'..'f','A'..'F' and more
     space	bit			' ', '\f', '\n', '\r', '\t', '\v'
     print	bit
     graph	print && !space
     blank	bit			' ', '\t'
     cntrl	bit			0x00..0x1F,0x7F
     punct	print && !(alpha || xdigit || space)
     alnum	alpha || xdigit
*/

#define iswmask(number,incl,excl)  ((incl) | ((excl) << 8) | ((number) << 16))
#define wmask_incl(mask)	(mask) & 0xFF
#define wmask_excl(mask)	((mask) >> 8) & 0xFF
#define wmask_number(mask)	((mask) >> 16)

#define upper	  1
#define lower	  2
#define alpha	  4
#define digit	  0
#define xdigit	  8
#define space	 16
#define print	 32
#define graph	  0
#define blank	 64
#define cntrl	128
#define punct	  0
#define alnum	  0

/* XXX these are copied in src/include/ctype.h */
#define wctype_alnum  iswmask(11, alpha|xdigit, 0)
#define wctype_alpha  iswmask(2, alpha, 0)
#define wctype_blank  iswmask(8, blank, 0)
#define wctype_cntrl  iswmask(9, cntrl, 0)
#define wctype_digit  iswmask(3, xdigit, alpha)
#define wctype_graph  iswmask(7, print, space)
#define wctype_lower  iswmask(1, lower, upper)
#define wctype_print  iswmask(6, print, 0)
#define wctype_punct  iswmask(10, print, alpha|xdigit|space)
#define wctype_space  iswmask(5, space, 0)
#define wctype_title  iswmask(12, upper|lower, 0)
#define wctype_upper  iswmask(0, upper, lower)
#define wctype_xdigit iswmask(4, xdigit, 0)

#define attribute_table mir18n_attribute_table
__BEGIN_DECLS
extern const unsigned char * const attribute_table[0x100];
__END_DECLS
#endif

#ifdef mir18n_caseconv
/* namespace definitions for the UCD tables */
#define nop_page	mir18n_attribute_nop_page
#define tolower_table	mir18n_caseconv_tolower
#define totitle_table	mir18n_caseconv_totitle
#define toupper_table	mir18n_caseconv_toupper

__BEGIN_DECLS
extern const uint16_t nop_page[256];
__END_DECLS
#endif

#endif
