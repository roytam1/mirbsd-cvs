/* $Xorg: AuDispose.c,v 1.4 2001/02/09 02:03:42 xorgcvs Exp $ */

/*

Copyright 1988, 1998  The Open Group

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
/* $XFree86: xc/lib/Xau/AuDispose.c,v 1.5 2001/12/14 19:54:36 dawes Exp $ */

#include <X11/Xauth.h>
#include <stdlib.h>

void
XauDisposeAuth (auth)
Xauth	*auth;
{
    if (auth) {
	if (auth->address) (void) free (auth->address);
	if (auth->number) (void) free (auth->number);
	if (auth->name) (void) free (auth->name);
	if (auth->data) {
	    (void) bzero (auth->data, auth->data_length);
	    (void) free (auth->data);
	}
	free ((char *) auth);
    }
    return;
}
