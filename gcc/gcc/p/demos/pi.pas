{ GPC demo program for the GMP unit.
  Computing pi with arbitrary precision.

  Copyright (C) 1998-2006 Free Software Foundation, Inc.

  Author: Frank Heckenbach <frank@pascal.gnu.de>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation, version 2.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; see the file COPYING. If not, write to
  the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
  Boston, MA 02111-1307, USA.

  As a special exception, if you incorporate even large parts of the
  code of this demo program into another program with substantially
  different functionality, this does not cause the other program to
  be covered by the GNU General Public License. This exception does
  not however invalidate any other reasons why it might be covered
  by the GNU General Public License. }

program Pi;

uses GPC, GMP;

var
  d: MedCard;
  f: mpf_t;
  s: CString;
  ex: mp_exp_t;

begin
  case ParamCount of
    0: begin
         WriteLn ('Pi computation.');
         Write ('Enter the number of digits: ');
         ReadLn (d);
       end;
    1: ReadStr (ParamStr (1), d);
    else
      WriteLn (StdErr, 'Pi computation.');
      WriteLn (StdErr, 'Usage: ', ParamStr (0), ' [number_of_digits]');
      Halt (1)
  end;
  mpf_set_default_prec (Round (d * Ln (10) / Ln (2)) + 16);
  mpf_init (f);
  mpf_pi (f);
  s := mpf_get_str (nil, ex, 10, d, f);
  if ex = 0 then
    {$local cstrings-as-strings} WriteLn ('Pi ~ 0.', s) {$endlocal}
  else
    {$local cstrings-as-strings,pointer-arithmetic} WriteLn ('Pi ~ ', PChars (s)^[1 .. ex], '.', s + ex); {$endlocal}
  Dispose (s);
  mpf_clear (f)
end.
