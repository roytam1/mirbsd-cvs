#!/usr/bin/env python
# coding: utf-8
# $MirOS: contrib/hosted/tg/grml/structid.py,v 1.5 2010/10/16 21:01:15 tg Exp $
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
    $MirOS: contrib/hosted/tg/grml/structid.py,v 1.5 2010/10/16 21:01:15 tg Exp $
"""

import struct

__all__ = [
    "StructId_Type",        # Abstract base class for StructId types
    "StructId_Integral",    # Type class for standard integral types
    "StructId_String",      # Type class for a byte/octet C string
    "StructId_Unicode",     # Type class for a multibyte C string
    "StructId_Container",   # Dictionary accessing self.__dict__ for everything
    "StructId"              # Ordered dictionary of typed attributes with
                            # structure mapping (main class, abstract base)
]


class StructId_Type(object):
    u"""Abstract base class for StructId types."""

    def __init__(self, toplev, arg, vararg=None):
        u"""Initialise a type instance."""
        self._toplev = toplev
        self._arg = arg
        self._vararg = vararg

    def get_fmt(self):
        u"""Return struct.unpack format specification."""
        raise NotImplementedError('StructId_Type.get_fmt is abstract')

    def num_items(self):
        u"""Return how many items in the tuple this type uses."""
        raise NotImplementedError('StructId_Type.num_items is abstract')

    def do_import(self, t):
        u"""Convert from unpack tuple to internal representation."""
        raise NotImplementedError('StructId_Type.do_import is abstract')

    def do_export(self, v):
        u"""Convert from internal representation to pack tuple."""
        raise NotImplementedError('StructId_Type.do_export is abstract')


class StructId_Integral(StructId_Type):
    u"""Type class for standard integral types."""

    def __init__(self, toplev, arg, vararg=None):
        u"""Initialise a standard integral type instance."""
        StructId_Type.__init__(self, toplev, arg, vararg)
        (self._fmt, self._defval) = arg

    def get_fmt(self):
        u"""Return struct.unpack format specification."""
        return self._fmt

    def num_items(self):
        u"""Return how many items in the tuple this type uses."""
        return 1

    def do_import(self, t):
        u"""Convert from unpack tuple to internal representation."""
        if t is None:
            # set to default/uninitialised value
            return self._defval
        return t[0]

    def do_export(self, v):
        u"""Convert from internal representation to pack tuple."""
        return (v,)


class StructId_String(StructId_Integral):
    u"""Type class for a byte/octet C string."""

    def __init__(self, toplev, arg, vararg=None):
        u"""Initialise a C string with length argument."""
        StructId_Type.__init__(self, toplev, arg, vararg)
        if vararg is None:
            raise ValueError('Need varargs to go with a StructId_String')
        self._size = vararg
        self._fmt = '%ds' % vararg
        self._defval = '%*s' % (vararg, '')


class StructId_Unicode(StructId_String):
    u"""Type class for a multibyte encoded C string.

    The length argument to __init__ is the amount of bytes of storage
    space we have, not the amount of wide characters we can store, as
    the entire StructId module operates on octet strings / byte arrays.

    Default encoding, if None given, is UTF-8. The Python side of this
    type isn’t str but unicode.

    """

    def __init__(self, toplev, arg, vararg=None):
        u"""Initialise a multibyte string with buffer size argument."""
        StructId_String.__init__(self, toplev, arg, vararg)
        if arg is None:
            arg = 'UTF-8'
        self._encoding = arg

    def do_import(self, t):
        u"""Convert from unpack tuple to internal representation."""
        if t is None:
            # set to default/uninitialised value
            return self._defval
        return unicode(str(t[0]).decode(self._encoding))

    def do_export(self, v):
        u"""Convert from internal representation to pack tuple."""
        return (str(unicode(v).encode(self._encoding)),)


class StructId_Struct(StructId_Type):
    u"""Internal class for sub-structures in StructId."""

    def __init__(self, toplev, arg, vararg=None):
        self._toplev = toplev
        self._info = tuple(arg)
        self._fmt = ''.join([slottypi.get_fmt() \
          for (slotname, numents, slottypi) in self._info])
        self._nents = sum([numents \
          for (slotname, numents, slottypi) in self._info])

    def get_fmt(self):
        return self._fmt

    def num_items(self):
        return self._nents

    def do_import(self, t):
        rv = StructId_Container()
        self.importTo(t, rv)
        return rv

    def do_export(self, v):
        rv = []
        for (slotname, numents, slottypi) in self._info:
            rv.extend(slottypi.do_export(v[slotname]))
        return tuple(rv)

    def importTo(self, t, d):
        e = 0
        for (slotname, numents, slottypi) in self._info:
            if t is None:
                # set to default/uninitialised value
                d[slotname] = slottypi.do_import(None)
            else:
                d[slotname] = slottypi.do_import(t[e:(e + numents)])
            e += numents


class StructId_Array(StructId_Type):
    u"""Internal class for arrays in StructId."""

    def __init__(self, toplev, type, size):
        self._toplev = toplev
        self._size = size
        fmt = type.get_fmt()
        self._subnents = type.num_items()
        self._type = type
        self._fmt = ''.join([fmt for i in range(size)])
        self._nents = self._subnents * size

    def get_fmt(self):
        return self._fmt

    def num_items(self):
        return self._nents

    def do_import(self, t):
        if t is None:
            # set to default/uninitialised value
            return [self._type.do_import(None) for i in range(self._size)]
        return [self._type.do_import(t[(i*self._subnents):((i+1)*self._subnents)]) \
          for i in range(self._size)]

    def do_export(self, v):
        rv = []
        for i in range(self._size):
            rv.extend(self._type.do_export(v[i]))
        return tuple(rv)


class StructId_Container(dict, object):
    u"""Dictionary accessing self.__dict__ for everything."""

    def __init__(self, *args, **kwargs):
        dict.__init__(self, *args, **kwargs)
        self.__dict__ = self


class StructId(StructId_Container):
    u"""Ordered dictionary of typed attributes with structure mapping.

    Instances of this class behave like a dictionary with a constant
    amount and names of attributes. They are ordered. They are filled
    in from a string, which is treated as a byte/octet array, using
    the “struct” module, upon instantiation, or when using the _import
    method, and converted to one using the _export method or upon
    stringification. No padding will be provided automatically. Names
    of attributes must not start with an underscore. Unions are not
    supported.

    This is an abstract base class and must be subclassed to be used.


    Subclasses must fill out the following members:

    • _get_endianness: return 'LE', 'BE' or 'HE' for little, big or
      host endianness, respectively

    • _get_format: return a string with the structure definition

    • _get_nbytes: return how many bytes we’re supposed to read


    Subclasses may fill out the following members:

    • _dump: set this attribute to True to dump structure information

    • _get_types: call the inherited method to get a dictionary whose
      keys are names of types structure members can have, and whose
      values are classes handling them (see below) to extend it, if
      necessary – standard types are {s,u}{8,16,32,64}, string, utf8.


    The following methods provide the public API:

    • __init__ (constructor): it is not advisable to overwrite this

    • _import: convert byte/octet array from string into self

    • _export: convert self into byte/octet array returned as string


    Type handling classes are expected to provide these methods:

    • get_fmt(): return string suitable for the “struct” module

    • num_items(): return number of items struct.unpack will
      return when encountering self.get_fmt() in its format

    • do_import(tuple): convert from tuple to internal representation
      or set to default/uninitialised value if tuple is None

    • do_export(v): convert from internal representation to tuple


    Example use (with sub-structures, arrays and custom types):

    import sys
    reload(sys)
    sys.setdefaultencoding("utf-8")

    from structid import *

    class DentType(StructId_Type):
        def get_fmt(self):
            return 'B'
        def num_items(self):
            return 1
        # note we could return a dictionary here too
        def do_import(self, t):
            if t is None:
                # set to default/uninitialised value
                return 'u'
            if t[0] & 32:
                return 'dir'
            return 'file'
        def do_export(self, v):
            if v == 'u':
                return (63,)
            if v == 'dir':
                return (33,)
            return (64,)
    class SomeStructure(StructId):
        _dump = True
        def _get_endianness(self):
            return 'LE'
        def _get_format(self):
            return '''
                u32 cluster;            <this is a comment>
                utf8(16) comment;
                {
                    string(8) name;
                    cp437(3) ext;
                    denttype type;      <1 byte>
                } dent[3];
                ''';
            # comments are only valid outside the sequence of
            # type+vararg+identifier+array+semicolon but valid
            # inside type if it’s a struct (for its components,
            # the same rules are valid again, though)
        def _get_nbytes(self):
            return 56
        def _get_types(self):
            types = StructId._get_types(self)
            types['denttype'] = tuple((DentType, None))
            types['cp437'] = tuple((StructId_Unicode, 'cp437'))
            return types

    if __name__ == '__main__':
        s = SomeStructure('\x00\x01\x00\x00« comm€nt »\x00filenameext dir_nameext.filenameext ')
        print s['cluster']
        print '%s.%s (%s)' % (s['dent'][0]['name'], s['dent'][0]['ext'],
          s['dent'][0]['type'])
        print '%s.%s (%s)' % (s['dent'][1]['name'], s['dent'][1]['ext'],
          s['dent'][1]['type'])
        print s.comment
        s['dent'][0]['name'] = 'new_name'
        s.dent[0].ext = u'╓─í'
        print '%s.%s (%s)' % (s.dent[0].name, s.dent[0].ext,
          s.dent[0].type)
        s.cluster = 0x21212121
        print 'this is binary:', str(s)
        t = SomeStructure()
        print 'def', str(t).decode('cp437')     # decode to vis DEADCAFE
        t.cluster = 0x45464143
        t.comment = u'0123456789ABCDEF'
        t.dent[0].name = 'file1nam'
        t.dent[0].ext = 'ext'
        t.dent[0].type = 'dir'
        t.dent[1].name = 'file2nam'
        t.dent[1].ext = 'ext'
        t.dent[1].type = 'u'
        t.dent[2].name = 'file3nam'
        t.dent[2].ext = 'ext'
        t.dent[2].type = 'file'
        print 'new', str(t)

    """

    _dump = False

    def __init__(self, iv=None):
        u"""Initialise a StructId instance.

        Read the type specification from the derived class
        and import the iv argument into ourselves.

        """
        StructId_Container.__init__(self)
        self._types = self._get_types()
        endian = self._get_endianness()
        if endian == 'LE':
            self._endian = '<'
        elif endian == 'BE':
            self._endian = '>'
        elif endian == 'HE':
            self._endian = '='
        else:
            raise ValueError('%s does not specify endianness as LE/BE/HE' % \
              self.__class__.__name__)
        self._structure = self._parse(self._get_format())
        self._fmt = self._endian + self._structure.get_fmt()
        cs = struct.calcsize(self._fmt)
        self._nbytes = self._get_nbytes()
        if cs != self._nbytes:
            raise ValueError('%s wants %d bytes, struct calculates %d bytes' % \
              (self.__class__.__name__, self._nbytes, cs))
        self._import(iv)

    def _get_endianness(self):
        u"""Return endianness of this structure.

        Possible return values are 'LE', 'BE' and 'HE'.

        """
        raise NotImplementedError('StructId._get_endianness is abstract')

    def _get_format(self):
        u"""Return definition of this structure."""
        raise NotImplementedError('StructId._get_format is abstract')

    def _get_nbytes(self):
        u"""Return size of this structure."""
        raise NotImplementedError('StructId._get_nbytes is abstract')

    def _get_types(self):
        u"""Return dictionary of supported types.

        Each member is a tuple (class, argument).

        """
        types = {}
        types['s8'] = tuple((StructId_Integral, ('b', 0x3F)))
        types['u8'] = tuple((StructId_Integral, ('B', 0x90)))
        types['s16'] = tuple((StructId_Integral, ('h', 0x213F)))
        types['u16'] = tuple((StructId_Integral, ('H', 0xF00D)))
        types['s32'] = tuple((StructId_Integral, ('i', 0x3E213F3C)))
        types['u32'] = tuple((StructId_Integral, ('I', 0xFECAADDE)))
        types['s64'] = tuple((StructId_Integral, ('q', 0x3E7C213F213F7C3C)))
        types['u64'] = tuple((StructId_Integral, ('Q', 0xBEBAEFBEDEC0ADDE)))
        types['string'] = tuple((StructId_String, None))
        types['utf8'] = tuple((StructId_Unicode, 'UTF-8'))
        return types

    def _import(self, s):
        u"""Import (unpack) from string into self."""
        if s is None:
            # set to default/uninitialised value
            self._structure.importTo(None, self.__dict__)
            return
        if type(s) is not str:
            raise TypeError('want octet string to import from')
        if len(s) != self._nbytes:
            raise ValueError('want to import %d bytes but got %d bytes' % \
              (self._nbytes, len(s)))
        self._structure.importTo(struct.unpack(self._fmt, s), self.__dict__)

    def _export(self):
        u"""Export (pack) from self into string."""
        t = self._structure.do_export(self.__dict__)
        s = struct.pack(self._fmt, *t)
        if len(s) != self._nbytes:
            raise ValueError('want to export %d bytes but got %d bytes' % \
              (self._nbytes, len(s)))
        return s

    def _parse(self, fs):
        u"""Parse StructId format string into StructId_Struct instance."""
        if self._dump:
            print '@dumping structure for class %s()' % self.__class__.__name__
        (i, o) = parse_struct(self, fs + '}', 0, 0)
        if i != (len(fs) + 1):
            parse_error(fs, i, 'Leftovers', len(fs))
        return o

    def __str__(self):
        u"""Stringify self by exporting."""
        return self._export()

    def __repr__(self):
        u"""Stringify self by exporting."""
        return '%s(%s)' % (self.__class__.__name__, repr(str(self)))


def parse_error(s, i, what, max=None):
    if max is None:
        max = i + 1
    raise ValueError('%s at %d in "%s→%s←%s"' % (what, i, \
      s[0:i], s[i:max], s[max:]))


def parse_identifier(s, i, what):
    if not s[i:(i+1)].isalpha():
        parse_error(s, i, 'Expected identifier (%s)' % what)
    j = i + 1
    while (s[j:(j+1)].isalnum()) or (s[j:(j+1)] == '_'):
        j += 1
    return (j, s[i:j])


def parse_number(s, i, what):
    if not s[i:(i+1)].isdigit():
        parse_error(s, i, 'Expected number (%s)' % what)
    j = i + 1
    while s[j:(j+1)].isdigit():
        j += 1
    return (j, int(s[i:j]))


def skip_whitespace(s, i):
    while s[i:(i+1)].isspace():
        i += 1
    return i


def skip_comment(s, i, l):
    while s[i:(i+1)] != '>':
        if i == l:
            parse_error(s, i, 'Expected closing angle brace')
        i += 1
    return i + 1


def parse_struct(toplev, s, i, depth):
    l = len(s)
    ss = []
    if toplev._dump:
        dofs = 0
    while True:
        i = skip_whitespace(s, i)
        if i == l:
            parse_error(s, i, 'Expected closing curly brace')
        if s[i] == '}':
            break
        if s[i] == '<':
            i = skip_comment(s, i + 1, l)
            continue
        if s[i] == '{':
            (i, o) = parse_struct(toplev, s, i + 1, depth + 1)
        else:
            begline = i
            (j, idname) = parse_identifier(s, i, 'type name')
            if (s[j:(j+1)] != '(') and (not s[j:(j+1)].isspace()):
                parse_error(s, j, 'Expected whitespace or opening parenthesis')
            if not toplev._types.has_key(idname):
                parse_error(s, i, 'Type %s unknown' % idname)
            t = toplev._types[idname]
            i = skip_whitespace(s, j)
            if s[i:(i+1)] == '(':
                i = skip_whitespace(s, i + 1)
                (i, arrsz) = parse_number(s, i, 'type vararg')
                i = skip_whitespace(s, i)
                if s[i:(i+1)] != ')':
                    parse_error(s, i, 'Expected closing parenthesis')
                i = skip_whitespace(s, i + 1)
                try:
                    o = t[0](toplev, t[1], arrsz)
                except ValueError, e:
                    parse_error(s, begline, e.message, i)
            else:
                try:
                    o = t[0](toplev, t[1])
                except ValueError, e:
                    parse_error(s, begline, e.message, i)
        i = skip_whitespace(s, i)
        if i == l:
            parse_error(s, i, 'Expected attribute name')
        (i, idname) = parse_identifier(s, i, 'attribute name')
        i = skip_whitespace(s, i)
        arrsz = None
        if toplev._dump:
            dsz = struct.calcsize(o.get_fmt())
        if s[i:(i+1)] == '[':
            i = skip_whitespace(s, i + 1)
            (i, arrsz) = parse_number(s, i, 'array size')
            i = skip_whitespace(s, i)
            if s[i:(i+1)] != ']':
                parse_error(s, i, 'Expected closing square bracket')
            i = skip_whitespace(s, i + 1)
            if toplev._dump:
                print '%*s@%08X %08Xh * %-12d  ISODCL(%d,%d)' % (depth * 2,
                  '', dofs, dsz, arrsz, dofs + 1, dofs + dsz * arrsz)
                dofs += dsz * arrsz
            o = StructId_Array(toplev, o, arrsz)
        else:
            if toplev._dump:
                print '%*s@%08X %08Xh                 ISODCL(%d,%d)' % \
                  (depth * 2, '', dofs, dsz, dofs + 1, dofs + dsz)
                dofs += dsz
        if s[i:(i+1)] != ';':
            parse_error(s, i, 'Expected semicolon')
        i += 1
        ss.append((idname, o.num_items(), o))
    o = StructId_Struct(toplev, ss)
    if toplev._dump and (i == l - 1):
        print '@total %Xh bytes' % dofs
    return (i + 1, o)
