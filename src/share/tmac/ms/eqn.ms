.\" $MirOS$
.\"
.\" Copyright (c) 1979, 1980, 1981, 1986, 1988, 1990, 1991, 1992
.\"     The Regents of the University of California.
.\" Copyright (C) Caldera International Inc.  2001-2002.
.\" Copyright (c) 2003, 2004
.\"	Thorsten "mirabile" Glaser <tg@66h.42h.de>
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
.\"	@(#)eqn.ms	5.1 (Berkeley) 4/17/91
.\"
.bd S B 3
.	\" EQ - equation, breakout and display
.de EQ
.nr UR \\n(.u
.rm EE
.nr LE 1	\" default centered
.ds EL \f1\\$1\fP
.if \\$1C .ds EL \f1\\$2\fP
.if \\$1L \{\
.	ds EL \f1\\$2\fP
.	nr LE 0
.\}
.if \\$1I \{\
.	ds EL \f1\\$2\fP
.	nr LE 0
.	ds EE \\h'|10n'
.	if !\\$3 .ds EE \\h'\\$3'
.\}
.if \\n(YE>0 .nf
.di EZ
..
.	\" EN - end of a displayed equation
.de EN
.if !\\*(10 .br
.di
.rm EZ
.nr ZN \\n(dn
.if \\n(ZN>0 .if \\n(YE=0 .LP
.if \\n(ZN=0 .if !\\*(EL .nr ZN 1
.if \\n(.z .if \\n(ZN>0 .if !\\n(nl=\\n(PE .sp \\n(DDu
.if !\\n(.z .if \\n(ZN>0 .if !\\n(.d=\\n(PE .sp \\n(DDu
.pc
.if \\n(BD>0 .nr LE 0	\" can't mean centering in this case.
.if \\n(MK>0 .if \\n(LE=1 .ds EE \\h'|10n'
.if \\n(MK>0 .nr LE 0	\" don't center if mark/lineup
.lt \\n(.lu
.if \\n(EP=0 .if \\n(ZN>0 \{\
.	if \\n(LE>0 .tl \\*(10\\*(EL
.	if \\n(LE=0 .if \\n(BD=0 .tl \\*(EE\\*(10\\*(EL
.	if \\n(LE=0 .if \\n(BD>0 .if \\n(BD<\\w\\*(10 .nr BD \\w\\*(10
.	if \\n(LE=0 .if \\n(BD>0 \!\\*(10\\t\\*(EL
.\}
.if \\n(EP>0 .if \\n(ZN>0 \{\
.	if \\n(LE>0 .tl \\*(EL\\*(10
.	if \\n(LE=0 .if \\n(BD=0 .tl \\*(EL\\*(EE\\*(10
.	if \\n(LE=0 .if \\n(BD>0 .if \\n(BD<\\w\\*(10 .nr BD \\w\\*(10
.	if \\n(LE=0 .if \\n(BD>0 \!\\h'-\\\\n(.iu'\\*(EL\\h'|0'\\*(10
.\}
.lt \\n(LLu
.pc %
.if \\n(YE>0 .if \\n(UR>0 .fi
.rm 10 11 12 13 14 15 16 17 18 19 20 21 22 23 EL
.rr 10 11 12 13 14 15 16 17 18 19 20 21 22 23
.if \\n(ZN>0 .if t .sp \\n(DDu
.if \\n(.z .nr PE \\n(nl
.if !\\n(.z .nr PE \\n(.d
..
