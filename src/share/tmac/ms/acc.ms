.\" $MirOS: src/share/tmac/ms/acc.ms,v 1.2 2008/11/08 22:24:18 tg Exp $
.\"
.\" Copyright (c) 1979, 1980, 1981, 1986, 1988, 1990, 1991, 1992
.\"     The Regents of the University of California.
.\" Copyright (C) Caldera International Inc.  2001-2002.
.\" Copyright (c) 2003, 2004, 2012
.\"	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
.\" All rights reserved.
.\"
.\" Redistribution and use in source and binary forms,
.\" with or without modification, are permitted provided
.\" that the following conditions are met:
.\"
.\" Redistributions of source code and documentation must retain
.\" the above copyright notice, this list of conditions and the
.\" following disclaimer.  Redistributions in binary form must
.\" reproduce the above copyright notice, this list of conditions
.\" and the following disclaimer in the documentation and/or other
.\" materials provided with the distribution.
.\"
.\" All advertising materials mentioning features or use of this
.\" software must display the following acknowledgement:
.\"   This product includes software developed or owned by
.\"   Caldera International, Inc.
.\"
.\" Neither the name of Caldera International, Inc. nor the names
.\" of other contributors may be used to endorse or promote products
.\" derived from this software without specific prior written permission.
.\"
.\" USE OF THE SOFTWARE PROVIDED FOR UNDER THIS LICENSE BY CALDERA
.\" INTERNATIONAL, INC. AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
.\" OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
.\" WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
.\" ARE DISCLAIMED.  IN NO EVENT SHALL CALDERA INTERNATIONAL, INC. BE
.\" LIABLE FOR ANY DIRECT, INDIRECT INCIDENTAL, SPECIAL, EXEMPLARY, OR
.\" CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
.\" SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
.\" BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
.\" WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
.\" OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
.\" EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
.\"
.\"	@(#)acc.ms	5.1 (Berkeley) 4/17/91
.\"
.	\" AM - accent mark definitions
.bd S B 3
.	\" fudge factors for nroff and troff
.if n \{\
.	ds #H 0
.	ds #V .8m
.	ds #F .3m
.	ds #[ \f1
.	ds #] \fP
.\}
.if t \{\
.	ds #H ((1u-(\\\\n(.fu%2u))*.13m)
.	ds #V .6m
.	ds #F 0
.	ds #[ \&
.	ds #] \&
.\}
.	\" simple accents for nroff and troff
.if n \{\
.	ds ' \h'-1'\'
.	ds ` \h'-1'\`
.	ds ^ \h'-1'^
.	ds , \h'-1',
.	ds ~ \h'-1'~
.	ds ? ?
.	ds ! !
.	ds / \h'-1'\(sl
.	ds q o\h'-1',
.\}
.if t \{\
.	ds ' \\k:\h'-(\\n(.wu*8/10-\*(#H)'\'\h"|\\n:u"
.	ds ` \\k:\h'-(\\n(.wu*8/10-\*(#H)'\`\h'|\\n:u'
.	ds ^ \\k:\h'-(\\n(.wu*10/11-\*(#H)'^\h'|\\n:u'
.	ds , \\k:\h'-(\\n(.wu*8/10)',\h'|\\n:u'
.	ds ~ \\k:\h'-(\\n(.wu-\*(#H-.1m)'~\h'|\\n:u'
.	ds ? \s-2c\h'-\wcu*7/10'\u\h'\*(#H'\zi\d\s+2\h'\wcu*8/10'
.	ds ! \s-2\(or\s+2\h'-\w\(oru'\v'-.8m'.\v'.8m'
.	ds / \\k:\h'-(\\n(.wu*8/10-\*(#H)'\z\(sl\h'|\\n:u'
.	ds q o\h'-\wou*8/10'\s-4\v'.4m'\z\(*i\v'-.4m'\s+4\h'\wou*8/10'
.\}
.	\" troff and (daisy-wheel) nroff accents
.ds : \\k:\h'-(\\n(.wu*8/10-\*(#H+.1m+\*(#F)'\v'-\*(#V'\z.\h'.2m+\*(#F'.\h'|\\n:u'\v'\*(#V'
.ds 8 \h'\*(#H'\(*b\h'-\*(#H'
.ds v \\k:\h'-(\\n(.wu*9/10-\*(#H)'\v'-\*(#V'\*(#[\s-4v\s0\v'\*(#V'\h'|\\n:u'\*(#]
.ds _ \\k:\h'-(\\n(.wu*9/10-\*(#H+(\*(#F*2/3))'\v'-.4m'\z\(hy\v'.4m'\h'|\\n:u'
.ds . \\k:\h'-(\\n(.wu*8/10)'\v'\*(#V*4/10'\z.\v'-\*(#V*4/10'\h'|\\n:u'
.ds 3 \*(#[\v'.2m'\s-2\&3\s0\v'-.2m'\*(#]
.ds o \\k:\h'-(\\n(.wu+\w\(deu-\*(#H)/2u'\v'-.3n'\*(#[\z\(de\v'.3n'\h'|\\n:u'\*(#]
.ds d- \h'\*(#H'\(pd\h'-\w~u'\v'-.25m'\f2\(hy\fP\v'.25m'\h'-\*(#H'
.ds D- D\\k:\h'-\wDu'\v'-.11m'\z\(hy\v'.11m'\h'|\\n:u'
.ds th \*(#[\v'.3m'\s+1I\s-1\v'-.3m'\h'-(\wIu*2/3)'\s-1o\s+1\*(#]
.ds Th \*(#[\s+2I\s-2\h'-\wIu*3/5'\v'-.3m'o\v'.3m'\*(#]
.ds ae a\h'-(\wau*4/10)'e
.ds Ae A\h'-(\wAu*4/10)'E
.ds oe o\h'-(\wou*4/10)'e
.ds Oe O\h'-(\wOu*4/10)'E
.	\" corrections for vroff
.if v .ds ~ \\k:\h'-(\\n(.wu*9/10-\*(#H)'\s-2\u~\d\s+2\h'|\\n:u'
.if v .ds ^ \\k:\h'-(\\n(.wu*10/11-\*(#H)'\v'-.4m'^\v'.4m'\h'|\\n:u'
.	\" for low resolution devices (crt and lpr)
.if \n(.H>23 .if \n(.V>19 \
\{\
.	ds : \h'-1'"
.	ds 8 B
.	ds v \h'-1'\o'\(aa\(ga'
.	ds _ \h'-1'^
.	ds . \h'-1'.
.	ds 3 3
.	ds o a
.	ds d- d\h'-1'\(ga
.	ds D- D\h'-1'\(hy
.	ds th \o'bp'
.	ds Th \o'LP'
.	ds ae ae
.	ds Ae AE
.	ds oe oe
.	ds Oe OE
.\}
.rm #[ #] #H #V #F C
