(* $MirOS: gcc/gcc/p/units/md5.pas,v 1.3 2005/03/29 00:07:08 tg Exp $
 *-
 * Copyright (c) 2005
 *	Free Software Foundation, Inc. <gpc@gnu.de>
 * written by:
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 *	Frank Heckenbach
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 *-
 * Replacement for the GNU md5 unit, which was licenced under the GNU
 * GPL, thus propagating the requirement to be GPL'd to any code that
 * used the old unit. The GNU md5 unit was the only one not under the
 * LGPL or GPL with library exception clause; this fixes it.
 *)

{$gnu-pascal,I-}
{$if __GPC_RELEASE__ < 20030303}
{$error This unit requires GPC release 20030303 or newer.}
{$endif}

unit MD5;

interface

uses GPC;

{ Representation of a MD5 value. It is always in little endian byte
  order and therefore portable. }
type
  Card8 = Cardinal attribute (Size = 8);
  TMD5 = array [1 .. 16] of Card8;

const
  MD5StrLength = 2 * High (TMD5);

type
  MD5String = String (MD5StrLength);

{ Computes MD5 message digest for Length bytes in Buffer. }
procedure MD5Buffer (const Buffer; Length: SizeType; var MD5: TMD5); attribute (name = '_p_MD5Buffer');

{ Computes MD5 message digest for the contents of the file f. }
procedure MD5File (var f: File; var MD5: TMD5); attribute (iocritical, name = '_p_MD5File');

{ Initializes a MD5 value with zeros. }
procedure MD5Clear (var MD5: TMD5); attribute (name = '_p_MD5Clear');

{ Compares two MD5 values for equality. }
function MD5Compare (const Value1, Value2: TMD5): Boolean; attribute (name = '_p_MD5Compare');

{ Converts an MD5 value to a string. }
function MD5Str (const MD5: TMD5) = s: MD5String; attribute (name = '_p_MD5Str');

{ Converts a string to an MD5 value. Returns True if successful. }
function MD5Val (const s: String; var MD5: TMD5): Boolean; attribute (name = '_p_MD5Val');

{ Composes two MD5 values to a single one. }
function MD5Compose (const Value1, Value2: TMD5) = Dest: TMD5; attribute (name = '_p_MD5Compose');


implementation

type
  Card32 = Cardinal attribute (Size = 32);
  Card64 = Cardinal attribute (Size = 64);
  TCtx = record { = MD5_CTX }
    state: array[0..3] of Card32;
    Count: Card64;
    Buffer: array[0..63] of Card8;
  end;

{$L c}
procedure cInit(var Ctx: TCtx);
  external name 'MD5Init';
procedure cUpdate(var Ctx: TCtx; protected var Buf; len: SizeType);
  external name 'MD5Update';
procedure cFinal(var Buf: TMD5; var Ctx: TCtx);
  external name 'MD5Final';


procedure MD5Buffer (const Buffer; Length: SizeType; var MD5: TMD5);
var Ctx: TCtx;
begin
  cInit (Ctx);
  cUpdate (Ctx, Buffer, Length);
  cFinal (MD5, Ctx);
end;

procedure MD5File (var f: File; var MD5: TMD5);
var
  Ctx: TCtx;
  Buffer: array [1 .. 4096] of Card8;
  BytesRead: SizeType;
begin
  cInit (Ctx);
  Reset (f, 1);
  repeat
    BlockRead (f, Buffer, SizeOf (Buffer), BytesRead);
    if InOutRes <> 0 then Exit;
    cUpdate (Ctx, Buffer, BytesRead);
  until EOF (f);
  cFinal (MD5, Ctx);
end;

procedure MD5Clear (var MD5: TMD5);
var i: Integer;
begin
  for i := Low (MD5) to High (MD5) do MD5[i] := 0
end;

function MD5Compare (const Value1, Value2: TMD5): Boolean;
var i: Integer;
begin
  MD5Compare := False;
  for i := Low (Value1) to High (Value1) do
    if Value1[i] <> Value2[i] then Exit;
  MD5Compare := True
end;

function MD5Str (const MD5: TMD5) = s: MD5String;
var i: Integer;
begin
  s := '';
  for i := Low (MD5) to High (MD5) do
    s := s + NumericBaseDigits[MD5[i] div $10] + NumericBaseDigits[MD5[i] mod $10]
end;

function MD5Val (const s: String; var MD5: TMD5): Boolean;
var i, d1, d2: Integer;

  function Char2Digit (ch: Char): Integer;
  begin
    case ch of
      '0' .. '9': Char2Digit := Ord (ch) - Ord ('0');
      'A' .. 'Z': Char2Digit := Ord (ch) - Ord ('A') + $a;
      'a' .. 'z': Char2Digit := Ord (ch) - Ord ('a') + $a;
      else        Char2Digit := -1
    end
  end;

begin
  MD5Val := False;
  if Length (s) <> 2 * (High (MD5) - Low (MD5) + 1) then Exit;
  for i := Low (MD5) to High (MD5) do
    begin
      d1 := Char2Digit (s[2 * (i - Low (MD5)) + 1]);
      d2 := Char2Digit (s[2 * (i - Low (MD5)) + 2]);
      if (d1 < 0) or (d1 >= $10) or (d2 < 0) or (d2 >= $10) then Exit;
      MD5[i] := $10 * d1 + d2
    end;
  MD5Val := True
end;

function MD5Compose (const Value1, Value2: TMD5) = Dest: TMD5;
var Buffer: array [1 .. 2] of TMD5;
begin
  Buffer[1] := Value1;
  Buffer[2] := Value2;
  MD5Buffer (Buffer, SizeOf (Buffer), Dest)
end;

end.
