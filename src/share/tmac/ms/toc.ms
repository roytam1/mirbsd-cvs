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
.\"	@(#)toc.ms	5.1 (Berkeley) 4/17/91
.\"
.	\" XS - begin index entry
.de XS
.if !\\n(1T .BG
.ds XL \\n(PN
.if \\n(.$ .ds XL \\$1
.nr SJ \\n(.j
.nr PF \\n(.f
.nr PX \\n(.s
.nr SL \\n(.l
.ls 1
.br
.da XT
.if \\n(.$-1 \{\
.	nr XI 1
.	in \\$2n
.\}
.ft 1
.ps \\n(PS
.ll \\n(LLu-8n
.na
.sp \\n(PDu
..
.	\" XA - add index entry
.de XA
.if !\\*(XLno \\a\\t\\*(XL
.if \\n(.$ .ds XL \\$1
.sp \\n(PDu
.if \\n(.$-1 \{\
.	nr XI 1
.	in \\$2n
.\}
..
.	\" XE - end index entry
.de XE
.if !\\*(XLno \\a\\t\\*(XL
.br
.da
.ls
.ad \\n(SJ
.ft \\n(PF
.ps \\n(PX
.ll \\n(SLu
.if \\n(XI \{\
.	nr XI 0
.	in 0
.\}
..
.	\" PX - print index (table of contents)
.de PX
.if \\n(VS>=40 .vs \\n(VSu
.if \\n(VS<=39 .vs \\n(VSp
.ll \\n(LLu
.lt \\n(LTu
.ta \\n(LLu-5n \\n(LLuR
.in 0
.nf
.rs
.if !\\$1no \{\
.	sp .5i
.	tl ''\f3\s+2Table of Contents\s-2\f1''
.	sp .5i
.\}
.XT
..
.	\" TC - table of contents at end of paper
.de TC
.af PN i
.bp 1
.PX \\$1
..
.	\" NH - numbered section header
.de NH
.RT
.if \\n(1T .sp
.if !\\n(1T .BG
.RT
.ne 3.1
.ft 3
.if n .ul 1000
.nr NS \\$1
.if !\\n(.$ .nr NS 1
.if !\\n(NS .nr NS 1
.nr H\\n(NS +1
.if !\\n(NS-4 .nr H5 0
.if !\\n(NS-3 .nr H4 0
.if !\\n(NS-2 .nr H3 0
.if !\\n(NS-1 .nr H2 0
.if !\\$1 .if \\n(.$ .nr H1 1
.if \\$1S \{\
.	nr NS \\n(.$-1
.	nr H1 \\$2
.	nr H2 \\$3
.	nr H3 \\$4
.	nr H4 \\$5
.	nr H5 \\$6
.\}
.ds SN \\n(H1.
.ti \\n(.iu
.if \\n(NS-1 .as SN \\n(H2.
.if \\n(NS-2 .as SN \\n(H3.
.if \\n(NS-3 .as SN \\n(H4.
.if \\n(NS-4 .as SN \\n(H5.
\\*(SN
..
