/*GNU Pascal compiler option tables

  Copyright (C) 2000-2005, Free Software Foundation, Inc.

  Used by the preprocessor and the compiler in common.

  Authors: Frank Heckenbach <frank@pascal.gnu.de>
           Peter Gerwinski <peter@gerwinski.de>

  This file is part of GNU Pascal.

  GNU Pascal is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 1, or (at your
  option) any later version.

  GNU Pascal is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with GNU Pascal; see the file COPYING. If not, write to the
  Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
  02111-1307, USA. */

#ifndef _GPC_OPTIONS_H
#define _GPC_OPTIONS_H

/* `$W' means warnings in GPC, but something different in BP which
   GPC does not need, so we ignore it in BP mode. */
static const struct gpc_short_option
{
  char  short_name;
  int   bp_option;
  const char *long_name;
  const char *inverted_long_name;
} gpc_short_options[] =
  {
    { 'b', 1, "-fno-short-circuit", "-fshort-circuit"      },
    { 'c', 1, "-fassertions",       "-fno-assertions"      },
    { 'i', 1, "-fio-checking",      "-fno-io-checking"     },
    { 'r', 1, "-frange-checking",   "-fno-range-checking"  },
    { 's', 1, "-fstack-checking",   "-fno-stack-checking"  },
    { 't', 1, "-ftyped-address",    "-fno-typed-address"   },
    { 'w', 0, "-Wwarnings",         "-Wno-warnings"        },
    { 'x', 1, "-fextended-syntax",  "-fno-extended-syntax" },
    { 'h', 1, "-#h", "-#no-h" },  /* @@ BP short strings, not yet implemented */
    { 'p', 1, "-#p", "-#no-p" },  /* @@ BP open strings, not yet implemented */
    { 'q', 1, "-#q", "-#no-q" },  /* @@ BP overflow checking, not yet implemented */
    { 'v', 1, "-#v", "-#no-v" },  /* @@ BP open arrays, not yet implemented */
    /* The following options are ignored, but still listed here so `ifopt' can
       support them. The "long options" must be unique and start with `-!'. */
    { 'a', 1, "-!a", "-!no-a" },
    { 'd', 1, "-!d", "-!no-d" },
    { 'e', 1, "-!e", "-!no-e" },
    { 'f', 1, "-!f", "-!no-f" },
    { 'g', 1, "-!g", "-!no-g" },
    { 'k', 1, "-!k", "-!no-k" },
    { 'l', 1, "-!l", "-!no-l" },
    { 'n', 1, "-!n", "-!no-n" },
    { 'o', 1, "-!o", "-!no-o" },
    { 'w', 1, "-!w", "-!no-w" },  /* outside of BP mode, the `w' above takes precedence */
    { 'y', 1, "-!y", "-!no-y" },
    { 0, 0, 0, 0 }
  };

static const char *const default_options[] =
  {
    "-fgnu-pascal",
    "-fautolink",
    "-fno-extended-syntax",
    "-fno-nested-comments",
    "-fno-ignore-function-results",
    "-ftruncate-strings",
    "-fexact-compare-strings",
    "-fio-checking",
    "-frange-checking",
    "-fno-stack-checking",
    "-fwrite-real-blank",
    "-fno-transparent-file-names",
    "-fno-pedantic",
    "-ftyped-address",
    "-fassertions",
    "-Wwarnings",
    "-Wimplicit-abstract",
    "-Winherited-abstract",
    "-Wsemicolon",
    "-Wno-parentheses",
    0
  };

static const char *const dialect_options[] =
  {
    "-fclassic-pascal-level-0",
    "-fclassic-pascal",
    "-fstandard-pascal-level-0",
    "-fstandard-pascal",
    "-fextended-pascal",
    "-fobject-pascal",
    "-fucsd-pascal",
    "-fborland-pascal",
    "-fdelphi",
    "-fpascal-sc",
    "-fvax-pascal",
    "-fsun-pascal",
    "-fmac-pascal",
    "-fgnu-pascal",
    0
  };

static const struct lang_option_map
{
  /* The limits here are hard-coded because otherwise the
     initializer doesn't compile. The limits can be increased when
     necessary. */
  const char *src[7];
  const char *dest[23];
} lang_option_map[] =
  {
    {
      {
        "-fclassic-pascal-level-0",
        "-fclassic-pascal",
        "-fstandard-pascal-level-0",
        "-fstandard-pascal",
        "-fextended-pascal",
        "-fobject-pascal",
        0
      },
      {
        "-fno-ignore-packed",
        "-fno-ignore-garbage-after-dot",
        "-fno-macros",
        "-fmixed-comments",
        "-fno-delphi-comments",
        "-fcase-value-checking",
        "-fno-short-circuit",
        "-fread-base-specifier",
        "-fno-read-hex",
        "-fno-read-white-space",
        "-fwrite-clip-strings",
        "-fno-write-capital-exponent",
        "-fno-exact-compare-strings",
        "-fno-double-quoted-strings",
        "-ffield-widths",
        "-fno-propagate-units",
        "-Wcast-align",
        "-Wobject-assignment",
        "-Wtyped-const",
        "-Wnear-far",
        "-Wunderscore",
        0
      }
    },
    {
      {
        "-fclassic-pascal-level-0",
        "-fclassic-pascal",
        "-fstandard-pascal-level-0",
        "-fstandard-pascal",
        0
      },
      {
        "-fno-read-base-specifier",
        "-fno-read-white-space",
      }
    },
    {
      {
        "-fucsd-pascal",
        "-fborland-pascal",
        "-fdelphi",
        0
      },
      {
        "-fignore-garbage-after-dot",
        "-fno-macros",
        "-fno-mixed-comments",
        "-fno-case-value-checking",
        "-fshort-circuit",
        "-fno-read-base-specifier",
        "-fread-hex",
        "-fno-read-white-space",
        "-fno-write-clip-strings",
        "-fwrite-capital-exponent",
        "-fexact-compare-strings",
        "-fno-double-quoted-strings",
        "-fno-field-widths",
        "-fno-methods-always-virtual",
        "-fno-propagate-units",
        "-Wno-object-assignment",
        "-Wno-typed-const",
        "-Wno-near-far",
        "-Wno-underscore",
        0
      }
    },
    {
      {
        "-fucsd-pascal",
        0
      },
      {
        "-fno-ignore-packed",
        "-Wcast-align",
        0
      }
    },
    {
      {
        "-fborland-pascal",
        "-fdelphi",
        0
      },
      {
        "-fignore-packed",
        "-Wno-cast-align",
        0
      }
    },
    {
      {
        "-fucsd-pascal",
        "-fborland-pascal",
        0
      },
      {
        "-fno-delphi-comments",
        0
      }
    },
    {
      {
        "-fdelphi",
        0
      },
      {
        "-fdelphi-comments",
        0
      }
    },
    {
      {
        "-fmac-pascal",
        0
      },
      {
        "-fno-typed-address",
        "-fno-case-value-checking",
        "-fno-short-circuit",
        "-fignore-garbage-after-dot",
        "-fno-mixed-comments",
        "-fdelphi-comments",
        "-fdouble-quoted-strings",
        "-fno-field-widths",
        "-fmethods-always-virtual",
        "-fpropagate-units",
        "-Wno-typed-const",
        "-Wno-cast-align",
        "-Wno-underscore",
        "-Wobject-assignment",
        0
      }
    },
    {
      {
        "-fgnu-pascal",
        0
      },
      {
        "-fno-ignore-packed",
        "-fno-ignore-garbage-after-dot",
        "-fmacros",
        "-fno-mixed-comments",
        "-fdelphi-comments",
        "-fno-case-value-checking",
        "-fshort-circuit",
        "-fread-base-specifier",
        "-fread-hex",
        "-fno-read-white-space",
        "-fwrite-clip-strings",
        "-fno-write-capital-exponent",
        "-fexact-compare-strings",
        "-fdouble-quoted-strings",
        "-fno-field-widths",
        "-fno-methods-always-virtual",
        "-fno-propagate-units",
        "-Wcast-align",
        "-Wobject-assignment",
        "-Wtyped-const",
        "-Wnear-far",
        "-Wunderscore",
        0
      }
    },
    {
      {
        "-Wall",
        0
      },
      {
        "-Wcast-align",
        "-Wparentheses",
        "-Wswitch",
        "-Wunused",
        "-Wuninitialized",
        "-Wtyped-const",
        "-Wnear-far",
        "-Wlocal-external",
        "-Wunderscore",
        "-Widentifier-case",
        0
      }
    },
    {
      {
        "-Wunused",
        0
      },
      {
        "-Wunused-function",
        "-Wunused-parameter",
        "-Wunused-variable",
        "-Wunused-value",
        0
      }
    },
    {
      {
        "-fextended-syntax",
        0
      },
      {
        "-fignore-function-results",
        "-fpointer-arithmetic",
        "-fcstrings-as-strings",
        "-Wno-absolute",
        0
      }
    },
    {
      {
        "-fno-extended-syntax",
        0
      },
      {
        "-fno-ignore-function-results",
        "-fno-pointer-arithmetic",
        "-fno-cstrings-as-strings",
        "-Wabsolute",
        0
      }
    },
    { { 0 }, { 0 } }
  };

#endif
