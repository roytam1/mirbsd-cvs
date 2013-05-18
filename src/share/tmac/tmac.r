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
.\"	@(#)tmac.r	5.2 (Berkeley) 4/20/91
.\"
.de HD
.ps 10
.ft 1
.if t .tl '\(rn'''
.if t 'sp  \\n(m1-1
.if n 'sp \\n(m1
.if e .1e
.if o .1o
.ps
.ft
'sp \\n(m2
.if \\n(:n .nm 1 1 2
.ns
..
.wh 0 HD
.de FT
'sp \\n(m3
.ps 10
.ft 1
.if e .2e
.if o .2o
.ps
.ft
'bp
..
.wh -1i FT
.de m1
.nr m1 \\$1
..
.de m2
.nr m2 \\$1
..
.de m3
.nr m3 \\$1
.ch FT -\\n(m3-\\n(m4
..
.de m4
.nr m4 \\$1
.ch FT -\\n(m3-\\n(m4
..
.m1 3
.m2 2
.m3 2
.m4 3
.de he
.de 1e
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
.de 1o
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
..
.de fo
.de 2e
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
.de 2o
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
..
.de eh
.de 1e
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
..
.de oh
.de 1o
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
..
.de ef
.de 2e
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
..
.de of
.de 2o
.tl \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
\\..
..
.he ''''
.fo ''''
.de bl
.rs
.sp \\$1
..
.de n1
.n2 \\$1
.nr :n 0
.if \\n(.$ .nr :n 1
..
.de n2
.if \\n(.$ .if \\$1=0 .nm
.if \\n(.$ .if !\\$1=0 .nm \\$1 1 2
.if !\\n(.$ .nm 1 1 2
..
.rn ds :d
.de ds
.if \\n(.$ .:d \\$1 "\\$2\\$3\\$4\\$5\\$6\\$7\\$8\\$9
.if !\\n(.$ .ls 2
..
.de ss
.ls 1
..
.de EQ
.nf
.sp
..
.de EN
.sp
.fi
..
