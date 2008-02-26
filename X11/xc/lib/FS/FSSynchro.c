/* $Xorg: FSSynchro.c,v 1.4 2001/02/09 02:03:25 xorgcvs Exp $ */

/* @(#)FSSynchro.c	4.1	91/05/02
 * Copyright 1990 Network Computing Devices;
 * Portions Copyright 1987 by Digital Equipment Corporation
 *
 * Permission to use, copy, modify, distribute, and sell this software 
 * and its documentation for any purpose is hereby granted without fee, 
 * provided that the above copyright notice appear in all copies and 
 * that both that copyright notice and this permission notice appear 
 * in supporting documentation, and that the names of Network Computing 
 * Devices or Digital not be used in advertising or publicity pertaining 
 * to distribution of the software without specific, written prior 
 * permission. Network Computing Devices or Digital make no representations 
 * about the suitability of this software for any purpose.  It is provided 
 * "as is" without express or implied warranty.
 *
 * NETWORK COMPUTING DEVICES AND  DIGITAL DISCLAIM ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL NETWORK COMPUTING DEVICES
 * OR DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES 
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, 
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, 
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS 
 * SOFTWARE.
 */
/* $XFree86: xc/lib/FS/FSSynchro.c,v 1.5 2001/12/14 19:53:33 dawes Exp $ */

/*

Copyright 1987, 1994, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/

#include	"FSlib.h"
#include	"FSlibint.h"

static int
_FSSyncFunction(FSServer *svr)
{

    return FSSync(svr, 0);
}

FSSyncHandler 
FSSynchronize(FSServer *svr, int onoff)
{
    FSSyncHandler temp;

    temp = svr->synchandler;
    if (onoff)
	svr->synchandler = _FSSyncFunction;
    else
	svr->synchandler = NULL;
    return temp;
}

FSSyncHandler 
FSSetAfterFunction(svr, func)
    FSServer     *svr;
    FSSyncHandler func;
{
    FSSyncHandler temp;

    temp = svr->synchandler;
    svr->synchandler = func;
    return temp;
}
