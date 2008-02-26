/* $Xorg: globals.h,v 1.4 2001/02/09 02:03:26 xorgcvs Exp $ */
/******************************************************************************


Copyright 1993, 1998  The Open Group

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

Author: Ralph Mor, X Consortium
******************************************************************************/
/* $XFree86: xc/lib/ICE/globals.h,v 1.5 2002/05/31 18:45:41 dawes Exp $ */

extern void _IceDefaultErrorHandler ();
extern void _IceDefaultIOErrorHandler ();

extern IcePoAuthStatus _IcePoMagicCookie1Proc ();
extern IcePaAuthStatus _IcePaMagicCookie1Proc ();

extern void _IceProcessCoreMessage ();

#ifndef __UNIXOS2__
IceConn     	_IceConnectionObjs[256];
char	    	*_IceConnectionStrings[256];
_IceProtocol 	_IceProtocols[255];
#else
IceConn     	_IceConnectionObjs[256] = {0};
char	    	*_IceConnectionStrings[256] = {0};
_IceProtocol 	_IceProtocols[255] = {0};
#endif
int     	_IceConnectionCount = 0;

int         	_IceLastMajorOpcode = 0;

int		_IceAuthCount = 1;
char		*_IceAuthNames[] = {"MIT-MAGIC-COOKIE-1"};
IcePoAuthProc	_IcePoAuthProcs[] = {_IcePoMagicCookie1Proc};
IcePaAuthProc	_IcePaAuthProcs[] = {_IcePaMagicCookie1Proc};

int		_IceVersionCount = 1;
_IceVersion	_IceVersions[] = {
	  	    {IceProtoMajor, IceProtoMinor, _IceProcessCoreMessage}};

_IceWatchProc	*_IceWatchProcs = NULL;

IceErrorHandler   _IceErrorHandler   = _IceDefaultErrorHandler;
IceIOErrorHandler _IceIOErrorHandler = _IceDefaultIOErrorHandler;
