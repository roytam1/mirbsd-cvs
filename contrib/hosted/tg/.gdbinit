# $MirOS: contrib/hosted/tg/.gdbinit,v 1.1 2009/01/01 20:53:28 tg Exp $
#-
# Copyright (c) 2009
#	Thorsten Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.

define y
end

define c16
y
 set architecture i8086
 set language asm
 set $user_csz = 16
 echo \nSet to 16 bit assembly debugging.\n
 u
end

define c32
y
 set architecture i386
 set language asm
 set $user_csz = 32
 echo \nSet to 32 bit assembly debugging.\n
 u
end

define u
y
 if $user_csz == 16
  x/i (($cs<<4)+$eip)
 else
  x/i $eip
 end
end

define uu
y
 if $user_csz == 16
  x/$arg0i (($cs<<4)+$eip)
 else
  x/$arg0i $eip
 end
end

define d
y
 x/$arg2 (($arg0<<4)+$arg1)
end

define t
y
 u
 echo \n
 si
 info r
 echo \n
 uu 3
end

define qemu
y
 target remote :1234
 c32
end

set disassembly-flavor intel
set $user_csz = 32

# Following content is © Konrad Rosenbaum <konrad@silmor.de>
# From: http://silmor.de/qtstuff.printqstring.php

define printqs5static
  set $d=$arg0.d
  printf "(Qt5 QString)0x%x length=%i: \"",&$arg0,$d->size
  set $i=0
  set $ca=(const ushort*)(((const char*)$d)+$d->offset)
  while $i < $d->size
    set $c=$ca[$i++]
    if $c < 32 || $c > 127
      printf "\\u%04x", $c
    else
      printf "%c" , (char)$c
    end
  end
  printf "\"\n"
end

define printqs5dynamic
  set $d=(QStringData*)$arg0.d
  printf "(Qt5 QString)0x%x length=%i: \"",&$arg0,$d->size
  set $i=0
  while $i < $d->size
    set $c=$d->data()[$i++]
    if $c < 32 || $c > 127
      printf "\\u%04x", $c
    else
      printf "%c" , (char)$c
    end
  end
  printf "\"\n"
end
