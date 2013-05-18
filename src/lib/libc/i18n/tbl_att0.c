/* $MirOS: src/lib/libc/i18n/tbl_attr.c,v 1.1 2006/06/01 22:03:16 tg Exp $ */

#include <sys/cdefs.h>

#define mir18n_attributes
#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/i18n/tbl_attr.c,v 1.1 2006/06/01 22:03:16 tg Exp $");

/* generated automatically from UnicodeData-5.0.0d10.txt (BMP) */

const unsigned char __C_attribute_table_pg[256] = {
	/* 0x0000 */ cntrl,
	/* 0x0001 */ cntrl,
	/* 0x0002 */ cntrl,
	/* 0x0003 */ cntrl,
	/* 0x0004 */ cntrl,
	/* 0x0005 */ cntrl,
	/* 0x0006 */ cntrl,
	/* 0x0007 */ cntrl,
	/* 0x0008 */ cntrl,
	/* 0x0009 */ space | blank | cntrl,
	/* 0x000a */ space | cntrl,
	/* 0x000b */ space | cntrl,
	/* 0x000c */ space | cntrl,
	/* 0x000d */ space | cntrl,
	/* 0x000e */ cntrl,
	/* 0x000f */ cntrl,
	/* 0x0010 */ cntrl,
	/* 0x0011 */ cntrl,
	/* 0x0012 */ cntrl,
	/* 0x0013 */ cntrl,
	/* 0x0014 */ cntrl,
	/* 0x0015 */ cntrl,
	/* 0x0016 */ cntrl,
	/* 0x0017 */ cntrl,
	/* 0x0018 */ cntrl,
	/* 0x0019 */ cntrl,
	/* 0x001a */ cntrl,
	/* 0x001b */ cntrl,
	/* 0x001c */ cntrl,
	/* 0x001d */ cntrl,
	/* 0x001e */ cntrl,
	/* 0x001f */ cntrl,
	/* 0x0020 */ space | print | blank,
	/* 0x0021 */ print | graph | punct,
	/* 0x0022 */ print | graph | punct,
	/* 0x0023 */ print | graph | punct,
	/* 0x0024 */ print | graph | punct,
	/* 0x0025 */ print | graph | punct,
	/* 0x0026 */ print | graph | punct,
	/* 0x0027 */ print | graph | punct,
	/* 0x0028 */ print | graph | punct,
	/* 0x0029 */ print | graph | punct,
	/* 0x002a */ print | graph | punct,
	/* 0x002b */ print | graph | punct,
	/* 0x002c */ print | graph | punct,
	/* 0x002d */ print | graph | punct,
	/* 0x002e */ print | graph | punct,
	/* 0x002f */ print | graph | punct,
	/* 0x0030 */ digit | xdigit | print | graph | alnum,
	/* 0x0031 */ digit | xdigit | print | graph | alnum,
	/* 0x0032 */ digit | xdigit | print | graph | alnum,
	/* 0x0033 */ digit | xdigit | print | graph | alnum,
	/* 0x0034 */ digit | xdigit | print | graph | alnum,
	/* 0x0035 */ digit | xdigit | print | graph | alnum,
	/* 0x0036 */ digit | xdigit | print | graph | alnum,
	/* 0x0037 */ digit | xdigit | print | graph | alnum,
	/* 0x0038 */ digit | xdigit | print | graph | alnum,
	/* 0x0039 */ digit | xdigit | print | graph | alnum,
	/* 0x003a */ print | graph | punct,
	/* 0x003b */ print | graph | punct,
	/* 0x003c */ print | graph | punct,
	/* 0x003d */ print | graph | punct,
	/* 0x003e */ print | graph | punct,
	/* 0x003f */ print | graph | punct,
	/* 0x0040 */ print | graph | punct,
	/* 0x0041 */ upper | alpha | xdigit | print | graph | alnum,
	/* 0x0042 */ upper | alpha | xdigit | print | graph | alnum,
	/* 0x0043 */ upper | alpha | xdigit | print | graph | alnum,
	/* 0x0044 */ upper | alpha | xdigit | print | graph | alnum,
	/* 0x0045 */ upper | alpha | xdigit | print | graph | alnum,
	/* 0x0046 */ upper | alpha | xdigit | print | graph | alnum,
	/* 0x0047 */ upper | alpha | print | graph | alnum,
	/* 0x0048 */ upper | alpha | print | graph | alnum,
	/* 0x0049 */ upper | alpha | print | graph | alnum,
	/* 0x004a */ upper | alpha | print | graph | alnum,
	/* 0x004b */ upper | alpha | print | graph | alnum,
	/* 0x004c */ upper | alpha | print | graph | alnum,
	/* 0x004d */ upper | alpha | print | graph | alnum,
	/* 0x004e */ upper | alpha | print | graph | alnum,
	/* 0x004f */ upper | alpha | print | graph | alnum,
	/* 0x0050 */ upper | alpha | print | graph | alnum,
	/* 0x0051 */ upper | alpha | print | graph | alnum,
	/* 0x0052 */ upper | alpha | print | graph | alnum,
	/* 0x0053 */ upper | alpha | print | graph | alnum,
	/* 0x0054 */ upper | alpha | print | graph | alnum,
	/* 0x0055 */ upper | alpha | print | graph | alnum,
	/* 0x0056 */ upper | alpha | print | graph | alnum,
	/* 0x0057 */ upper | alpha | print | graph | alnum,
	/* 0x0058 */ upper | alpha | print | graph | alnum,
	/* 0x0059 */ upper | alpha | print | graph | alnum,
	/* 0x005a */ upper | alpha | print | graph | alnum,
	/* 0x005b */ print | graph | punct,
	/* 0x005c */ print | graph | punct,
	/* 0x005d */ print | graph | punct,
	/* 0x005e */ print | graph | punct,
	/* 0x005f */ print | graph | punct,
	/* 0x0060 */ print | graph | punct,
	/* 0x0061 */ lower | alpha | xdigit | print | graph | alnum,
	/* 0x0062 */ lower | alpha | xdigit | print | graph | alnum,
	/* 0x0063 */ lower | alpha | xdigit | print | graph | alnum,
	/* 0x0064 */ lower | alpha | xdigit | print | graph | alnum,
	/* 0x0065 */ lower | alpha | xdigit | print | graph | alnum,
	/* 0x0066 */ lower | alpha | xdigit | print | graph | alnum,
	/* 0x0067 */ lower | alpha | print | graph | alnum,
	/* 0x0068 */ lower | alpha | print | graph | alnum,
	/* 0x0069 */ lower | alpha | print | graph | alnum,
	/* 0x006a */ lower | alpha | print | graph | alnum,
	/* 0x006b */ lower | alpha | print | graph | alnum,
	/* 0x006c */ lower | alpha | print | graph | alnum,
	/* 0x006d */ lower | alpha | print | graph | alnum,
	/* 0x006e */ lower | alpha | print | graph | alnum,
	/* 0x006f */ lower | alpha | print | graph | alnum,
	/* 0x0070 */ lower | alpha | print | graph | alnum,
	/* 0x0071 */ lower | alpha | print | graph | alnum,
	/* 0x0072 */ lower | alpha | print | graph | alnum,
	/* 0x0073 */ lower | alpha | print | graph | alnum,
	/* 0x0074 */ lower | alpha | print | graph | alnum,
	/* 0x0075 */ lower | alpha | print | graph | alnum,
	/* 0x0076 */ lower | alpha | print | graph | alnum,
	/* 0x0077 */ lower | alpha | print | graph | alnum,
	/* 0x0078 */ lower | alpha | print | graph | alnum,
	/* 0x0079 */ lower | alpha | print | graph | alnum,
	/* 0x007a */ lower | alpha | print | graph | alnum,
	/* 0x007b */ print | graph | punct,
	/* 0x007c */ print | graph | punct,
	/* 0x007d */ print | graph | punct,
	/* 0x007e */ print | graph | punct,
	/* 0x007f */ cntrl,
	/* 0x0080 */ cntrl,
	/* 0x0081 */ cntrl,
	/* 0x0082 */ cntrl,
	/* 0x0083 */ cntrl,
	/* 0x0084 */ cntrl,
	/* 0x0085 */ cntrl,
	/* 0x0086 */ cntrl,
	/* 0x0087 */ cntrl,
	/* 0x0088 */ cntrl,
	/* 0x0089 */ cntrl,
	/* 0x008a */ cntrl,
	/* 0x008b */ cntrl,
	/* 0x008c */ cntrl,
	/* 0x008d */ cntrl,
	/* 0x008e */ cntrl,
	/* 0x008f */ cntrl,
	/* 0x0090 */ cntrl,
	/* 0x0091 */ cntrl,
	/* 0x0092 */ cntrl,
	/* 0x0093 */ cntrl,
	/* 0x0094 */ cntrl,
	/* 0x0095 */ cntrl,
	/* 0x0096 */ cntrl,
	/* 0x0097 */ cntrl,
	/* 0x0098 */ cntrl,
	/* 0x0099 */ cntrl,
	/* 0x009a */ cntrl,
	/* 0x009b */ cntrl,
	/* 0x009c */ cntrl,
	/* 0x009d */ cntrl,
	/* 0x009e */ cntrl,
	/* 0x009f */ cntrl,
	/* 0x00a0 */ print | graph | punct,
	/* 0x00a1 */ print | graph | punct,
	/* 0x00a2 */ print | graph | punct,
	/* 0x00a3 */ print | graph | punct,
	/* 0x00a4 */ print | graph | punct,
	/* 0x00a5 */ print | graph | punct,
	/* 0x00a6 */ print | graph | punct,
	/* 0x00a7 */ print | graph | punct,
	/* 0x00a8 */ print | graph | punct,
	/* 0x00a9 */ print | graph | punct,
	/* 0x00aa */ alpha | print | graph | alnum,
	/* 0x00ab */ print | graph | punct,
	/* 0x00ac */ print | graph | punct,
	/* 0x00ad */ print | graph | punct,
	/* 0x00ae */ print | graph | punct,
	/* 0x00af */ print | graph | punct,
	/* 0x00b0 */ print | graph | punct,
	/* 0x00b1 */ print | graph | punct,
	/* 0x00b2 */ print | graph | punct,
	/* 0x00b3 */ print | graph | punct,
	/* 0x00b4 */ print | graph | punct,
	/* 0x00b5 */ lower | alpha | print | graph | alnum,
	/* 0x00b6 */ print | graph | punct,
	/* 0x00b7 */ print | graph | punct,
	/* 0x00b8 */ print | graph | punct,
	/* 0x00b9 */ print | graph | punct,
	/* 0x00ba */ alpha | print | graph | alnum,
	/* 0x00bb */ print | graph | punct,
	/* 0x00bc */ print | graph | punct,
	/* 0x00bd */ print | graph | punct,
	/* 0x00be */ print | graph | punct,
	/* 0x00bf */ print | graph | punct,
	/* 0x00c0 */ upper | alpha | print | graph | alnum,
	/* 0x00c1 */ upper | alpha | print | graph | alnum,
	/* 0x00c2 */ upper | alpha | print | graph | alnum,
	/* 0x00c3 */ upper | alpha | print | graph | alnum,
	/* 0x00c4 */ upper | alpha | print | graph | alnum,
	/* 0x00c5 */ upper | alpha | print | graph | alnum,
	/* 0x00c6 */ upper | alpha | print | graph | alnum,
	/* 0x00c7 */ upper | alpha | print | graph | alnum,
	/* 0x00c8 */ upper | alpha | print | graph | alnum,
	/* 0x00c9 */ upper | alpha | print | graph | alnum,
	/* 0x00ca */ upper | alpha | print | graph | alnum,
	/* 0x00cb */ upper | alpha | print | graph | alnum,
	/* 0x00cc */ upper | alpha | print | graph | alnum,
	/* 0x00cd */ upper | alpha | print | graph | alnum,
	/* 0x00ce */ upper | alpha | print | graph | alnum,
	/* 0x00cf */ upper | alpha | print | graph | alnum,
	/* 0x00d0 */ upper | alpha | print | graph | alnum,
	/* 0x00d1 */ upper | alpha | print | graph | alnum,
	/* 0x00d2 */ upper | alpha | print | graph | alnum,
	/* 0x00d3 */ upper | alpha | print | graph | alnum,
	/* 0x00d4 */ upper | alpha | print | graph | alnum,
	/* 0x00d5 */ upper | alpha | print | graph | alnum,
	/* 0x00d6 */ upper | alpha | print | graph | alnum,
	/* 0x00d7 */ print | graph | punct,
	/* 0x00d8 */ upper | alpha | print | graph | alnum,
	/* 0x00d9 */ upper | alpha | print | graph | alnum,
	/* 0x00da */ upper | alpha | print | graph | alnum,
	/* 0x00db */ upper | alpha | print | graph | alnum,
	/* 0x00dc */ upper | alpha | print | graph | alnum,
	/* 0x00dd */ upper | alpha | print | graph | alnum,
	/* 0x00de */ upper | alpha | print | graph | alnum,
	/* 0x00df */ alpha | print | graph | alnum,
	/* 0x00e0 */ lower | alpha | print | graph | alnum,
	/* 0x00e1 */ lower | alpha | print | graph | alnum,
	/* 0x00e2 */ lower | alpha | print | graph | alnum,
	/* 0x00e3 */ lower | alpha | print | graph | alnum,
	/* 0x00e4 */ lower | alpha | print | graph | alnum,
	/* 0x00e5 */ lower | alpha | print | graph | alnum,
	/* 0x00e6 */ lower | alpha | print | graph | alnum,
	/* 0x00e7 */ lower | alpha | print | graph | alnum,
	/* 0x00e8 */ lower | alpha | print | graph | alnum,
	/* 0x00e9 */ lower | alpha | print | graph | alnum,
	/* 0x00ea */ lower | alpha | print | graph | alnum,
	/* 0x00eb */ lower | alpha | print | graph | alnum,
	/* 0x00ec */ lower | alpha | print | graph | alnum,
	/* 0x00ed */ lower | alpha | print | graph | alnum,
	/* 0x00ee */ lower | alpha | print | graph | alnum,
	/* 0x00ef */ lower | alpha | print | graph | alnum,
	/* 0x00f0 */ lower | alpha | print | graph | alnum,
	/* 0x00f1 */ lower | alpha | print | graph | alnum,
	/* 0x00f2 */ lower | alpha | print | graph | alnum,
	/* 0x00f3 */ lower | alpha | print | graph | alnum,
	/* 0x00f4 */ lower | alpha | print | graph | alnum,
	/* 0x00f5 */ lower | alpha | print | graph | alnum,
	/* 0x00f6 */ lower | alpha | print | graph | alnum,
	/* 0x00f7 */ print | graph | punct,
	/* 0x00f8 */ lower | alpha | print | graph | alnum,
	/* 0x00f9 */ lower | alpha | print | graph | alnum,
	/* 0x00fa */ lower | alpha | print | graph | alnum,
	/* 0x00fb */ lower | alpha | print | graph | alnum,
	/* 0x00fc */ lower | alpha | print | graph | alnum,
	/* 0x00fd */ lower | alpha | print | graph | alnum,
	/* 0x00fe */ lower | alpha | print | graph | alnum,
	/* 0x00ff */ lower | alpha | print | graph | alnum
};
