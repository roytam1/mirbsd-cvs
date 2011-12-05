/* @(#)nls_iso8859-14.c	1.1 00/03/25 2000 J. Schilling */
#include <sys/cdefs.h>
__SCCSID("@(#)nls_iso8859-14.c	1.1 00/03/25 2000 J. Schilling");
__RCSID("$MirOS$");
/*
 *	Modifications to make the code portable Copyright (c) 2000 J. Schilling
 *
 *	Code taken from the Linux kernel.
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */
/*
 * linux/fs/nls_iso8859-14.c
 *
 * Charset iso8859-14 translation tables.
 *
 * Generated automatically from the Unicode and charset table
 * provided by the Unicode Organisation at
 * http://www.unicode.org/
 * The Unicode to charset table has only exact mappings.
 *
 * Rhys Jones, Swansea University Computer Society
 * rhys@sucs.swan.ac.uk
 */

#include <mconfig.h>
#include "nls.h"

static void	inc_use_count	__PR((void));
static void	dec_use_count	__PR((void));

static struct nls_unicode charset2uni[256] = {
	/* 0x00*/
	{0x00, 0x00}, {0x01, 0x00}, {0x02, 0x00}, {0x03, 0x00}, 
	{0x04, 0x00}, {0x05, 0x00}, {0x06, 0x00}, {0x07, 0x00}, 
	{0x08, 0x00}, {0x09, 0x00}, {0x0a, 0x00}, {0x0b, 0x00}, 
	{0x0c, 0x00}, {0x0d, 0x00}, {0x0e, 0x00}, {0x0f, 0x00}, 
	/* 0x10*/
	{0x10, 0x00}, {0x11, 0x00}, {0x12, 0x00}, {0x13, 0x00}, 
	{0x14, 0x00}, {0x15, 0x00}, {0x16, 0x00}, {0x17, 0x00}, 
	{0x18, 0x00}, {0x19, 0x00}, {0x1a, 0x00}, {0x1b, 0x00}, 
	{0x1c, 0x00}, {0x1d, 0x00}, {0x1e, 0x00}, {0x1f, 0x00}, 
	/* 0x20*/
	{0x20, 0x00}, {0x21, 0x00}, {0x22, 0x00}, {0x23, 0x00}, 
	{0x24, 0x00}, {0x25, 0x00}, {0x26, 0x00}, {0x27, 0x00}, 
	{0x28, 0x00}, {0x29, 0x00}, {0x2a, 0x00}, {0x2b, 0x00}, 
	{0x2c, 0x00}, {0x2d, 0x00}, {0x2e, 0x00}, {0x2f, 0x00}, 
	/* 0x30*/
	{0x30, 0x00}, {0x31, 0x00}, {0x32, 0x00}, {0x33, 0x00}, 
	{0x34, 0x00}, {0x35, 0x00}, {0x36, 0x00}, {0x37, 0x00}, 
	{0x38, 0x00}, {0x39, 0x00}, {0x3a, 0x00}, {0x3b, 0x00}, 
	{0x3c, 0x00}, {0x3d, 0x00}, {0x3e, 0x00}, {0x3f, 0x00}, 
	/* 0x40*/
	{0x40, 0x00}, {0x41, 0x00}, {0x42, 0x00}, {0x43, 0x00}, 
	{0x44, 0x00}, {0x45, 0x00}, {0x46, 0x00}, {0x47, 0x00}, 
	{0x48, 0x00}, {0x49, 0x00}, {0x4a, 0x00}, {0x4b, 0x00}, 
	{0x4c, 0x00}, {0x4d, 0x00}, {0x4e, 0x00}, {0x4f, 0x00}, 
	/* 0x50*/
	{0x50, 0x00}, {0x51, 0x00}, {0x52, 0x00}, {0x53, 0x00}, 
	{0x54, 0x00}, {0x55, 0x00}, {0x56, 0x00}, {0x57, 0x00}, 
	{0x58, 0x00}, {0x59, 0x00}, {0x5a, 0x00}, {0x5b, 0x00}, 
	{0x5c, 0x00}, {0x5d, 0x00}, {0x5e, 0x00}, {0x5f, 0x00}, 
	/* 0x60*/
	{0x60, 0x00}, {0x61, 0x00}, {0x62, 0x00}, {0x63, 0x00}, 
	{0x64, 0x00}, {0x65, 0x00}, {0x66, 0x00}, {0x67, 0x00}, 
	{0x68, 0x00}, {0x69, 0x00}, {0x6a, 0x00}, {0x6b, 0x00}, 
	{0x6c, 0x00}, {0x6d, 0x00}, {0x6e, 0x00}, {0x6f, 0x00}, 
	/* 0x70*/
	{0x70, 0x00}, {0x71, 0x00}, {0x72, 0x00}, {0x73, 0x00}, 
	{0x74, 0x00}, {0x75, 0x00}, {0x76, 0x00}, {0x77, 0x00}, 
	{0x78, 0x00}, {0x79, 0x00}, {0x7a, 0x00}, {0x7b, 0x00}, 
	{0x7c, 0x00}, {0x7d, 0x00}, {0x7e, 0x00}, {0x7f, 0x00}, 
	/* 0x80*/
	{0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, 
	{0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, 
	{0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, 
	{0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, 
	/* 0x90*/
	{0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, 
	{0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, 
	{0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, 
	{0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, {0x00, 0x00}, 
	/* 0xa0*/
	{0xa0, 0x00}, {0x02, 0x1e}, {0x03, 0x1e}, {0xa3, 0x00}, 
	{0x0a, 0x01}, {0x0b, 0x01}, {0x0a, 0x1e}, {0xa7, 0x00}, 
	{0x80, 0x1e}, {0xa9, 0x00}, {0x82, 0x1e}, {0x0b, 0x1e}, 
	{0xf2, 0x1e}, {0xad, 0x00}, {0xae, 0x00}, {0x78, 0x01}, 
	/* 0xb0*/
	{0x1e, 0x1e}, {0x1f, 0x1e}, {0x20, 0x01}, {0x21, 0x01}, 
	{0x40, 0x1e}, {0x41, 0x1e}, {0xb6, 0x00}, {0x56, 0x1e}, 
	{0x81, 0x1e}, {0x57, 0x1e}, {0x83, 0x1e}, {0x60, 0x1e}, 
	{0xf3, 0x1e}, {0x84, 0x1e}, {0x85, 0x1e}, {0x61, 0x1e}, 
	/* 0xc0*/
	{0xc0, 0x00}, {0xc1, 0x00}, {0xc2, 0x00}, {0xc3, 0x00}, 
	{0xc4, 0x00}, {0xc5, 0x00}, {0xc6, 0x00}, {0xc7, 0x00}, 
	{0xc8, 0x00}, {0xc9, 0x00}, {0xca, 0x00}, {0xcb, 0x00}, 
	{0xcc, 0x00}, {0xcd, 0x00}, {0xce, 0x00}, {0xcf, 0x00}, 
	/* 0xd0*/
	{0x74, 0x01}, {0xd1, 0x00}, {0xd2, 0x00}, {0xd3, 0x00}, 
	{0xd4, 0x00}, {0xd5, 0x00}, {0xd6, 0x00}, {0x6a, 0x1e}, 
	{0xd8, 0x00}, {0xd9, 0x00}, {0xda, 0x00}, {0xdb, 0x00}, 
	{0xdc, 0x00}, {0xdd, 0x00}, {0x76, 0x01}, {0xdf, 0x00}, 
	/* 0xe0*/
	{0xe0, 0x00}, {0xe1, 0x00}, {0xe2, 0x00}, {0xe3, 0x00}, 
	{0xe4, 0x00}, {0xe5, 0x00}, {0xe6, 0x00}, {0xe7, 0x00}, 
	{0xe8, 0x00}, {0xe9, 0x00}, {0xea, 0x00}, {0xeb, 0x00}, 
	{0xec, 0x00}, {0xed, 0x00}, {0xee, 0x00}, {0xef, 0x00}, 
	/* 0xf0*/
	{0x75, 0x01}, {0xf1, 0x00}, {0xf2, 0x00}, {0xf3, 0x00}, 
	{0xf4, 0x00}, {0xf5, 0x00}, {0xf6, 0x00}, {0x6b, 0x1e}, 
	{0xf8, 0x00}, {0xf9, 0x00}, {0xfa, 0x00}, {0xfb, 0x00}, 
	{0xfc, 0x00}, {0xfd, 0x00}, {0x77, 0x01}, {0xff, 0x00}, 
};

static unsigned char page00[256] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, /* 0x00-0x07 */
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, /* 0x08-0x0f */
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, /* 0x10-0x17 */
	0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, /* 0x18-0x1f */
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, /* 0x20-0x27 */
	0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, /* 0x28-0x2f */
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, /* 0x30-0x37 */
	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, /* 0x38-0x3f */
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, /* 0x40-0x47 */
	0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, /* 0x48-0x4f */
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, /* 0x50-0x57 */
	0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, /* 0x58-0x5f */
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, /* 0x60-0x67 */
	0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, /* 0x68-0x6f */
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, /* 0x70-0x77 */
	0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, /* 0x78-0x7f */

	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x80-0x87 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x88-0x8f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x90-0x97 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x98-0x9f */
	0xa0, 0x00, 0x00, 0xa3, 0x00, 0x00, 0x00, 0xa7, /* 0xa0-0xa7 */
	0x00, 0xa9, 0x00, 0x00, 0x00, 0xad, 0xae, 0x00, /* 0xa8-0xaf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb6, 0x00, /* 0xb0-0xb7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xb8-0xbf */
	0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, /* 0xc0-0xc7 */
	0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, /* 0xc8-0xcf */
	0x00, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0x00, /* 0xd0-0xd7 */
	0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0x00, 0xdf, /* 0xd8-0xdf */
	0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, /* 0xe0-0xe7 */
	0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, /* 0xe8-0xef */
	0x00, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0x00, /* 0xf0-0xf7 */
	0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0x00, 0xff, /* 0xf8-0xff */
};

static unsigned char page01[256] = {
	0x00, 0x00, 0xa1, 0xa2, 0x00, 0x00, 0x00, 0x00, /* 0x00-0x07 */
	0x00, 0x00, 0xa6, 0xab, 0x00, 0x00, 0x00, 0x00, /* 0x08-0x0f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10-0x17 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0xb1, /* 0x18-0x1f */
	0xb2, 0xb3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x20-0x27 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x28-0x2f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x30-0x37 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x38-0x3f */
	0xb4, 0xb5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x40-0x47 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x48-0x4f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb7, 0xb9, /* 0x50-0x57 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x58-0x5f */
	0xbb, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x60-0x67 */
	0x00, 0x00, 0xd7, 0xf7, 0x00, 0x00, 0x00, 0x00, /* 0x68-0x6f */
	0x00, 0x00, 0x00, 0x00, 0xd0, 0xf0, 0xde, 0xfe, /* 0x70-0x77 */
	0xaf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x78-0x7f */
	
	0xa8, 0xb8, 0xaa, 0xba, 0xbd, 0xbe, 0x00, 0x00, /* 0x80-0x87 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x88-0x8f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x90-0x97 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x98-0x9f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa0-0xa7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa8-0xaf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xb0-0xb7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xb8-0xbf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xc0-0xc7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xc8-0xcf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xd0-0xd7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xd8-0xdf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xe0-0xe7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xe8-0xef */
	0x00, 0x00, 0xac, 0xbc, 0x00, 0x00, 0x00, 0x00, /* 0xf0-0xf7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xf8-0xff */
};

static unsigned char page1e[256] = {
	0x00, 0x00, 0xa1, 0xa2, 0x00, 0x00, 0x00, 0x00, /* 0x00-0x07 */
	0x00, 0x00, 0xa6, 0xab, 0x00, 0x00, 0x00, 0x00, /* 0x08-0x0f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x10-0x17 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0xb1, /* 0x18-0x1f */
	0xb2, 0xb3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x20-0x27 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x28-0x2f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x30-0x37 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x38-0x3f */
	0xb4, 0xb5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x40-0x47 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x48-0x4f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb7, 0xb9, /* 0x50-0x57 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x58-0x5f */
	0xbb, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x60-0x67 */
	0x00, 0x00, 0xd7, 0xf7, 0x00, 0x00, 0x00, 0x00, /* 0x68-0x6f */
	0x00, 0x00, 0x00, 0x00, 0xd0, 0xf0, 0xde, 0xfe, /* 0x70-0x77 */
	0xaf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x78-0x7f */

	0xa8, 0xb8, 0xaa, 0xba, 0xbd, 0xbe, 0x00, 0x00, /* 0x80-0x87 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x88-0x8f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x90-0x97 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0x98-0x9f */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa0-0xa7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xa8-0xaf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xb0-0xb7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xb8-0xbf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xc0-0xc7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xc8-0xcf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xd0-0xd7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xd8-0xdf */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xe0-0xe7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xe8-0xef */
	0x00, 0x00, 0xac, 0xbc, 0x00, 0x00, 0x00, 0x00, /* 0xf0-0xf7 */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 0xf8-0xff */
};

static unsigned char *page_uni2charset[256] = {
	page00,	page01, NULL,   NULL,   NULL,   NULL,   NULL,   NULL,   
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,

	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	page1e,	NULL,

	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,	NULL,
};

static void
inc_use_count()
{
	MOD_INC_USE_COUNT;
}

static void
dec_use_count()
{
	MOD_DEC_USE_COUNT;
}

static struct nls_table table = {
	"iso8859-14",
	page_uni2charset,
	charset2uni,
	inc_use_count,
	dec_use_count,
	NULL
};

int
init_nls_iso8859_14()
{
	return register_nls(&table);
}

#ifdef MODULE
int init_module(void)
{
	return init_nls_iso8859_14();
}


void cleanup_module(void)
{	
	unregister_nls(&table);
	return;
}
#endif

/*
 * Overrides for Emacs so that we follow Linus's tabbing style.
 * Emacs will notice this stuff at the end of the file and automatically
 * adjust the settings for this buffer only.  This must remain at the end
 * of the file.
 * ---------------------------------------------------------------------------
 * Local variables:
 * c-indent-level: 8
 * c-brace-imaginary-offset: 0
 * c-brace-offset: -8
 * c-argdecl-indent: 8
 * c-label-offset: -8
 * c-continued-statement-offset: 8
 * c-continued-brace-offset: 0
 * End:
 */
