#define COMMENT(X)

COMMENT((
Common definitions for the GNU Pascal Compiler and the Run Time System

Each group of flags must consist of distinct bits.

This file is also included in some source files of the compiler to
keep the definitions unique. It defines only numeric macros and
uses #-directives, so it can be included in both C and Pascal files.

Copyright (C) 1991-2005 Free Software Foundation, Inc.

This file is part of GNU Pascal.

GNU Pascal is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Pascal is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Pascal; see the file COPYING. If not, write to the
Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.

As a special exception, if you link this file with files compiled
with a GNU compiler to produce an executable, this does not cause
the resulting executable to be covered by the GNU General Public
License. This exception does not however invalidate any other
reasons why the executable file might be covered by the GNU General
Public License.))

COMMENT (RTS options)
#define ro_SP_EOLn 1

COMMENT (File kind: fourth parameter to InitFDR)
#define fkind_TEXT      1
#define fkind_UNTYPED   2
#define fkind_EXTERN    4
#define fkind_FILENAME  8
#define fkind_BINDABLE 16

COMMENT (Input masks.)
#define READ_STRING_MASK           1 COMMENT ((ReadStr))
#define VAL_MASK                   2 COMMENT ((Val))
#define INT_READ_BASE_SPEC_MASK    4 COMMENT ((allow the base specifier (n#) (integer)))
#define INT_READ_HEX_MASK          8 COMMENT ((allow the hex specifier ($) (integer)))
#define NUM_READ_CHK_WHITE_MASK   16 COMMENT ((require whitespace after the number (integer, real)))
#define REAL_READ_SP_ONLY_MASK    32 COMMENT ((do not accept Extended Pascal real number format extension (real)))

COMMENT (Output masks.)
#define WRITE_STRING_MASK          1 COMMENT ((WriteStr or FormatString))
#define FORMAT_STRING_MASK         2 COMMENT ((FormatString))
#define WRITE_FIXED_STRING_MASK    4 COMMENT ((array of Char as target, blank pad))
#define NEG_ZERO_WIDTH_ERROR_MASK  8 COMMENT ((give an error when field width <= 0))
#define NEG_WIDTH_ERROR_MASK      16 COMMENT ((give an error when field width < 0))
#define NEG_WIDTH_LEFT_MASK       32 COMMENT ((left adjusted output when the field width < 0))
#define NEG_WIDTH_CENTER_MASK     64 COMMENT ((centered output when field width < 0))
#define REAL_NOBLANK_MASK        128 COMMENT ((output without a leading blank (real)))
#define REAL_CAPITAL_EXP_MASK    256 COMMENT ((write a capital `E' rather than `e' for the exponent (real)))
#define CLIP_STRING_MASK         512 COMMENT ((clip strings that exceed the given width))
#define TRUNCATE_STRING_MASK    1024 COMMENT ((truncate output that exceeds capacity rather than generating an error (for WriteStr)))
