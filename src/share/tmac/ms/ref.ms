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
.\"	@(#)ref.ms	5.1 (Berkeley) 4/17/91
.\"
.	\" refer macros for citations
.de []
.][ \\$1
..
.de ][
.if \\$1>4 .tm %M undefined (Bell Labs)
.[\\$1
..
.if n .ds [o \&"
.if n .ds [c \&"
.if t .ds [o ``
.if t .ds [c ''
.ds <. .
.ds <, ,
.	\" [0 - other type of citation
.de [0
.FS
.nr [: 0
.if !\\*([F .FP \\*([F
.if !\\*([Q \{\
.nr [: 1
\\*([Q\c
.\}
.if !\\*([A \{\
.nr [: 1
\\*([A\c
.\}
.if !\\*([T \{\
.if \\n([:>0 ,
.nr [: 1
\f2\\*([T\f1\c
.\}
.if !\\*([S , \\*([S\c
.if !\\*([V , \\*([V\c
.if !\\*([P \{\
.ie \\n([P>0 , pp. \\*([P\c
.el , p. \\*([P\c
.\}
.if !\\*([C , \\*([C\c
.if !\\*([D , \\*([D\c
.if \\n([:>0 \&.
.if !\\*([O \\*([O
.FE
..
.	\" [1 - journal article
.de [1
.FS
.if !\\*([F .FP \\*([F
.if !\\*([Q \\*([Q,
.if !\\*([A \\*([A,
.if !\\*([T \\*([o\\*([T,\\*([c
\f2\\*([J\f1\c
.if !\\*([V , vol. \\*([V\c
.if !\\*([N , no. \\*([N\c
.if !\\*([P \{\
.ie \\n([P>0 , pp. \\*([P\c
.el , p. \\*([P\c
.\}
.if !\\*([I , \\*([I\c
.if !\\*([C , \\*([C\c
.if !\\*([D , \\*([D\c
\&.
.if !\\*([O \\*([O
.FE
..
.	\" [2 - book
.de [2
.FS
.if !\\*([F .FP \\*([F
.if !\\*([Q \\*([Q,
.if !\\*([A \\*([A,
.if !\\*([T \f2\\*([T,\f1
.if !\\*([S \\*([S,
.if !\\*([V \\*([V,
.if !\\*([P \{\
.ie \\n([P>0 pp. \\*([P,
.el p. \\*([P,
.\}
\\*([I\c
.if !\\*([C , \\*([C\c
.if !\\*([D , \\*([D\c
\&.
.if !\\*([O \\*([O
.FE
..
.	\" [3 - article in book
.de [3
.FS
.if !\\*([F .FP \\*([F
.if !\\*([Q \\*([Q,
.if !\\*([A \\*([A,
.if !\\*([T \\*([o\\*([T,\\*([c
in \f2\\*([B\f1\c
.if !\\*([E , ed. \\*([E\c
.if !\\*([S , \\*([S\c
.if !\\*([V , vol. \\*([V\c
.if !\\*([P \{\
.ie \\n([P>0 , pp. \\*([P\c
.el , p. \\*([P\c
.\}
.if !\\*([I , \\*([I\c
.if !\\*([C , \\*([C\c
.if !\\*([D , \\*([D\c
\&.
.if !\\*([O \\*([O
.FE
..
.	\" [4 - report
.de [4
.FS
.if !\\*([F .FP \\*([F
.if !\\*([Q \\*([Q,
.if !\\*([A \\*([A,
.if !\\*([T \\*([o\\*([T,\\*([c
.if !\\*([R \\*([R\c
.if !\\*([G \& (\\*([G)\c
.if !\\*([P \{\
.ie \\n([P>0 , pp. \\*([P\c
.el , p. \\*([P\c
.\}
.if !\\*([I , \\*([I\c
.if !\\*([C , \\*([C\c
.if !\\*([D , \\*([D\c
\&.
.if !\\*([O \\*([O
.FE
..
.de ]<
.[<
..
.de [<
.SH
References
.LP
.de FP
.IP \\\\$1.
\\..
.rm FS FE
..
.de [>
.]>
..
.de ]>
.sp
..
.de ]-
.[-
..
.de [-
.rm [Q [A [T [J [B [E [S [V
.rm [N [P [I [C [D [O [R [G
..
.de ]]
.\" circumvent EOF bug in troff
..
