/**	$MirOS: src/lib/libc/gen/tolower_.c,v 1.2 2006/11/01 19:49:33 tg Exp $ */
/*	$OpenBSD: tolower_.c,v 1.9 2005/08/08 08:05:34 espie Exp $ */
/*
 * Originally written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 */

#define _ANSI_LIBRARY
#include <ctype.h>

__RCSID("$MirOS: src/lib/libc/gen/tolower_.c,v 1.2 2006/11/01 19:49:33 tg Exp $");

static const unsigned char _C_tolower_[128] = {
	0x00,	0x01,	0x02,	0x03,	0x04,	0x05,	0x06,	0x07,
	0x08,	0x09,	0x0a,	0x0b,	0x0c,	0x0d,	0x0e,	0x0f,
	0x10,	0x11,	0x12,	0x13,	0x14,	0x15,	0x16,	0x17,
	0x18,	0x19,	0x1a,	0x1b,	0x1c,	0x1d,	0x1e,	0x1f,
	0x20,	0x21,	0x22,	0x23,	0x24,	0x25,	0x26,	0x27,
	0x28,	0x29,	0x2a,	0x2b,	0x2c,	0x2d,	0x2e,	0x2f,
	0x30,	0x31,	0x32,	0x33,	0x34,	0x35,	0x36,	0x37,
	0x38,	0x39,	0x3a,	0x3b,	0x3c,	0x3d,	0x3e,	0x3f,
	0x40,	'a',	'b',	'c',	'd',	'e',	'f',	'g',
	'h',	'i',	'j',	'k',	'l',	'm',	'n',	'o',
	'p',	'q',	'r',	's',	't',	'u',	'v',	'w',
	'x',	'y',	'z',	0x5b,	0x5c,	0x5d,	0x5e,	0x5f,
	0x60,	0x61,	0x62,	0x63,	0x64,	0x65,	0x66,	0x67,
	0x68,	0x69,	0x6a,	0x6b,	0x6c,	0x6d,	0x6e,	0x6f,
	0x70,	0x71,	0x72,	0x73,	0x74,	0x75,	0x76,	0x77,
	0x78,	0x79,	0x7a,	0x7b,	0x7c,	0x7d,	0x7e,	0x7f
};

int
tolower(int c)
{
	return (((unsigned)c >= 128) ? c : _C_tolower_[c]);
}
