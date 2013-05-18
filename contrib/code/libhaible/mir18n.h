/* $MirOS: contrib/code/libhaible/mir18n.h,v 1.6 2006/05/30 10:02:16 tg Exp $ */

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

#ifdef mir18n_attributes
/* from Bruno Haible's libutf8 */

/* How the 12 character attributes are encoded in 8 bits: Every attribute is
   represented by an "include bitmask" and an "exclude bitmask".
    Attribute	bit/formula		comment
     upper	bit			implies towlower(x) != x == towupper(x)
     lower	bit			implies towlower(x) == x != towupper(x)
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

#define wctype_upper  iswmask(0, upper, 0)
#define wctype_lower  iswmask(1, lower, 0)
#define wctype_alpha  iswmask(2, alpha, 0)
#define wctype_digit  iswmask(3, xdigit, alpha)
#define wctype_xdigit iswmask(4, xdigit, 0)
#define wctype_space  iswmask(5, space, 0)
#define wctype_print  iswmask(6, print, 0)
#define wctype_graph  iswmask(7, print, space)
#define wctype_blank  iswmask(8, blank, 0)
#define wctype_cntrl  iswmask(9, cntrl, 0)
#define wctype_punct  iswmask(10, print, alpha|xdigit|space)
#define wctype_alnum  iswmask(11, alpha|xdigit, 0)

#define attribute_table mir18n_attribute_table
__BEGIN_DECLS
extern const unsigned char * const attribute_table[0x100];
__END_DECLS
#endif

#ifdef mir18n_caseconv
/* for uint16_t */
#ifndef __BIT_TYPES_DEFINED__
#include <machine/types.h>
#endif

/* namespace definitions for the UCD tables */
#define nop_page mir18n_attribute_nop_page
#define tolower_page mir18n_caseconv_tolower
#define toupper_page mir18n_caseconv_toupper

__BEGIN_DECLS
extern const uint16_t nop_page[256];
extern const uint16_t * const tolower_table[0x100];
extern const uint16_t * const toupper_table[0x100];
__END_DECLS
#endif

#endif
