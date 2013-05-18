/* $MirOS: src/usr.bin/oldroff/tbl/t2.c,v 1.1.7.1 2005/03/06 16:56:02 tg Exp $ */

/*-
 * Copyright (c) 1979, 1980, 1981, 1986, 1988, 1990, 1991, 1992
 *     The Regents of the University of California.
 * Copyright (C) Caldera International Inc.  2001-2002.
 * Copyright (c) 2003, 2004
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms,
 * with or without modification, are permitted provided
 * that the following conditions are met:
 *
 * Redistributions of source code and documentation must retain
 * the above copyright notice, this list of conditions and the
 * following disclaimer.  Redistributions in binary form must
 * reproduce the above copyright notice, this list of conditions
 * and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 *
 * All advertising materials mentioning features or use of this
 * software must display the following acknowledgement:
 *   This product includes software developed or owned by
 *   Caldera International, Inc.
 *
 * Neither the name of Caldera International, Inc. nor the names
 * of other contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * USE OF THE SOFTWARE PROVIDED FOR UNDER THIS LICENSE BY CALDERA
 * INTERNATIONAL, INC. AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL CALDERA INTERNATIONAL, INC. BE
 * LIABLE FOR ANY DIRECT, INDIRECT INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* t2.c:  subroutine sequencing for one table */

# include "t..c"
__SCCSID("@(#)t2.c	4.3 (Berkeley) 4/18/91");
__RCSID("$MirOS$");

tableput()
{
saveline();
savefill();
ifdivert();
cleanfc();
getcomm();
getspec();
gettbl();
getstop();
checkuse();
choochar();
maktab();
runout();
release();
rstofill();
endoff();
restline();
}
