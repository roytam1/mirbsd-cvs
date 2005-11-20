/*Definitions for specs for Pascal.

  Copyright (C) 1997-2005 Free Software Foundation, Inc.

  Authors: Peter Gerwinski <peter@gerwinski.de>
           Frank Heckenbach <frank@pascal.gnu.de>

  This file is part of GNU Pascal.

  GNU Pascal is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 2, or (at your
  option) any later version.

  GNU Pascal is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with GNU Pascal; see the file COPYING. If not, write to the
  Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
  02111-1307, USA. */

#include "p/p-version.h"

/* This is the contribution to the `default_compilers' array for Pascal. */
  {".pas", "@Pascal", 0},
  {".p", "@Pascal", 0},
  {".pp", "@Pascal", 0},
  {".dpr", "@Pascal", 0},
  {"@Pascal",
#if 0
   "gpcpp\
    %{fbig-endian:-D__BITS_BIG_ENDIAN__=1 -D__BYTES_BIG_ENDIAN__=1 -D__WORDS_BIG_ENDIAN__=1}\
    %{flittle-endian:-D__BITS_LITTLE_ENDIAN__=1 -D__BYTES_LITTLE_ENDIAN__=1 -D__WORDS_LITTLE_ENDIAN__=1}\
    %{!fbig-endian:%{!flittle-endian:"
#if BITS_BIG_ENDIAN
   "-D__BITS_BIG_ENDIAN__=1"
#else
   "-D__BITS_LITTLE_ENDIAN__=1"
#endif
#if BYTES_BIG_ENDIAN
   " -D__BYTES_BIG_ENDIAN__=1"
#else
   " -D__BYTES_LITTLE_ENDIAN__=1"
#endif
#if WORDS_BIG_ENDIAN
   " -D__WORDS_BIG_ENDIAN__=1"
#else
   " -D__WORDS_LITTLE_ENDIAN__=1"
#endif
   "}}"
#if STRICT_ALIGNMENT
   " -D__NEED_ALIGNMENT__=1"
#else
   " -D__NEED_NO_ALIGNMENT__=1"
#endif
   " %(cpp_unique_options) %{f*&W*&w} %{pedantic*} %{!M:%{!E:%{!pipe:%g.i}}} |\n\
    %{!M:%{!MM:%{!E:gpc1 %{!pipe:%g.i} %(cc1_options)\
    %{!famtmpfile*:%eInternal GPC problem: internal option `--amtmpfile' not given}\
    %{!fsyntax-only:%(invoke_as)} }}}", 0},
#endif
    "gpc1 %{E:-E %{!M:%(cpp_unique_options) %1 %{m*} %{f*&W*&pedantic*} %{w} "
    "%(cpp_debug_options) %{O*}}}"
    "%{M:%(cpp_unique_options) %1 %{m*} %{f*&W*&pedantic*} %{w}" 
    "%(cpp_debug_options) %{O*}}"
    "%{!E:%{!M:%{save-temps:-E %(cpp_unique_options) %1 %{m*} "
    "%{f*&W*&pedantic*} %{w}  %{O*} -o %b.i \n\
     gpc1 -fpreprocessed %b.i} %{!save-temps:%(cpp_unique_options)} \
     %(cc1_options)\
    %{!famtmpfile*:%eInternal GPC problem: internal option `--amtmpfile' not given}\
    %{!fsyntax-only:%(invoke_as)}}}", 0},
  {"@Preprocessed-Pascal",
   "%{!M:%{!MM:%{!E:gpc1 -fpreprocessed %i %(cc1_options)\
    %{!famtmpfile*:%eInternal GPC problem: internal option `--amtmpfile' not given}\
    %{!fsyntax-only:%(invoke_as)} }}}", 0},
