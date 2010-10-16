#!/usr/bin/env python
# coding: utf-8
# $MirOS: contrib/hosted/tg/grml/ecma119.py,v 1.2 2010/10/16 22:30:50 tg Exp $
#-
# Copyright © 2010
#	Thorsten Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un‐
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person’s immediate fault when using the work as intended.

__version__ = """
    $MirOS: contrib/hosted/tg/grml/ecma119.py,v 1.2 2010/10/16 22:30:50 tg Exp $
"""

from structid import *

__all__ = [
    "Ecma119_Date",         # §8.4.26.1 Date types
    "Ecma119_Integral",     # Integral single-endian types
    "Ecma119_BB_Integral",  # Integral both-endian types
    "Ecma119_StructId",     # Abstract base class as StructId
]


class Ecma119_Date(StructId_Type):
    u"""Type class for ECMA 119 §8.4.25.1 Date types.

    Maps into an attribute dictionary with the following slots:
    • year      [1; 9999]
    • month     [1; 12]
    • day       [1; 31]
    • hour      [0; 23]
    • minute    [0; 59]
    • second    [0; 59]
    • centi     [0; 99]     Hundredths of a second
    • offset    [-48; 52]   Offset from GMT by 15 minutes

    If all slots are zero, “the time and date are not specified.”

    """

    def get_fmt(self):
        u"""Return struct.unpack format specification."""
        return '4s2s2s2s2s2s2sb'

    def num_items(self):
        u"""Return how many items in the tuple this type uses."""
        return 8

    def do_import(self, t):
        u"""Convert from unpack tuple to internal representation."""
        rv = StructId_Container()
        rv.year = 0
        rv.month = 0
        rv.day = 0
        rv.hour = 0
        rv.minute = 0
        rv.second = 0
        rv.centi = 0
        rv.offset = 0
        if t is not None:
            if t[0] != '\0\0\0\0':
                rv.year = int(t[0])
            if t[1] != '\0\0':
                rv.month = int(t[1])
            if t[2] != '\0\0':
                rv.day = int(t[2])
            if t[3] != '\0\0':
                rv.hour = int(t[3])
            if t[4] != '\0\0':
                rv.minute = int(t[4])
            if t[5] != '\0\0':
                rv.second = int(t[5])
            if t[6] != '\0\0':
                rv.centi = int(t[6])
            rv.offset = t[7]
        return rv

    def do_export(self, v):
        u"""Convert from internal representation to pack tuple."""
        if v.year == 0 and v.month == 0 and v.day == 0 and \
          v.hour == 0 and v.minute == 0 and v.second == 0 and \
          v.centi == 0 and v.offset == 0:
            # the time and date are not specified.
            pass
        elif v.year < 1 or v.year > 9999:
            raise ValueError('year %d out of range [1; 9999]' % v.year)
        elif v.month < 1 or v.month > 12:
            raise ValueError('month %d out of range [1; 12]' % v.month)
        elif v.day < 1 or v.day > 31:
            raise ValueError('day %d out of range [1; 31]' % v.day)
        elif v.hour < 0 or v.hour > 23:
            raise ValueError('hour %d out of range [0; 23]' % v.hour)
        elif v.minute < 0 or v.minute > 59:
            raise ValueError('minute %d out of range [0; 59]' % v.minute)
        elif v.second < 0 or v.second > 59:
            raise ValueError('second %d out of range [0; 59]' % v.second)
        elif v.centi < 0 or v.centi > 99:
            raise ValueError('centi %d out of range [0; 99]' % v.centi)
        elif v.offset < -48 or v.offset > 52:
            raise ValueError('offset %d out of range [-48; 52]' % v.offset)
        return tuple(('%04u' % v.year, '%02u' % v.month, '%02u' % v.day, \
          '%02u' % v.hour, '%02u' % v.minute, '%02u' % v.second, \
          '%02u' % v.centi, v.offset))


class Ecma119_Integral(StructId_Integral):
    u"""Type class for ECMA 119 integral types."""

    def __init__(self, toplev, arg, vararg=None):
        u"""Initialise an ECMA 119 integral type instance.

        • arg: tuple(format, default value, is big endian?)

        """
        StructId_Type.__init__(self, toplev, arg, vararg)
        (self._fmt, self._defval, self._isbig) = arg
        if self._isbig == toplev._is_bigendian():
            self._swab = False
        else:
            self._swab = True

    def do_import(self, t):
        u"""Convert from unpack tuple to internal representation."""
        v = StructId_Integral.do_import(self, t)
        if self._swab:
            return StructId_bswap(self._fmt, v)
        return v

    def do_export(self, v):
        u"""Convert from internal representation to pack tuple."""
        if self._swab:
            v = StructId_bswap(self._fmt, v)
        return StructId_Integral.do_export(self, v)


class Ecma119_BB_Integral(StructId_Integral):
    u"""Type class for ECMA 119 both-byte order integral types."""

    def __init__(self, toplev, arg, vararg=None):
        u"""Initialise an ECMA 119 both-byte order integral type instance.

        • arg: tuple(format, default value)

        """
        StructId_Integral.__init__(self, toplev, arg, vararg)
        if toplev._is_bigendian():
            self._idx = 1
        else:
            self._idx = 0
        self._ofmt = self._fmt
        self._fmt = self._ofmt + self._ofmt

    def num_items(self):
        u"""Return how many items in the tuple this type uses."""
        return 2

    def do_import(self, t):
        u"""Convert from unpack tuple to internal representation."""
        if t is None:
            # set to default/uninitialised value
            return self._defval
        return t[self._idx]

    def do_export(self, v):
        u"""Convert from internal representation to pack tuple."""
        rv = [0, 0]
        rv[self._idx] = v
        rv[1 - self._idx] = StructId_bswap(self._ofmt, v)
        return tuple(rv)


class Ecma119_StructId(StructId):
    u"""Ordered dictionary of typed attributes with structure mapping.

    See StructId.__doc__ for more details. Additional types provided:
    • ecma711, ecma712              (unsigned, signed 8-bit)
    • ecma721, ecma722, ecma723     (unsigned 16-bit LE/BE/BiEndian)
    • ecma731, ecma732, ecma733     (unsigned 32-bit LE/BE/BiEndian)
    • ecma84261                     (8.4.26.1 date)

    § 7.{2,3}.{1,2,3} do not specify signedness, thus defaulting
    to unsigned for greater range of operation.

    """

    def _get_types(self):
        types = StructId._get_types(self)
        types['ecma711'] = tuple((StructId_Integral, ('B', 0x90)))
        types['ecma712'] = tuple((StructId_Integral, ('b', 0x3F)))
        types['ecma721'] = tuple((Ecma119_Integral, ('H', 0xFF0D, False)))
        types['ecma722'] = tuple((Ecma119_Integral, ('H', 0xD0FE, True)))
        types['ecma723'] = tuple((Ecma119_BB_Integral, ('H', 0xF00D)))
        types['ecma731'] = tuple((Ecma119_Integral, ('I', 0xFECAADDE, False)))
        types['ecma732'] = tuple((Ecma119_Integral, ('I', 0xDEADBEEF, True)))
        types['ecma733'] = tuple((Ecma119_BB_Integral, ('I', 0xBEBAADDE)))
        types['ecma84261'] = tuple((Ecma119_Date, None))
        return types
