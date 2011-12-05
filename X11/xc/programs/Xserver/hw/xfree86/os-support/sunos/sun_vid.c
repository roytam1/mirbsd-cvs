/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/sunos/sun_vid.c,v 1.4 2004/03/08 15:37:12 tsi Exp $ */
/*
 * Copyright 1990,91 by Thomas Roell, Dinkelscherben, Germany
 * Copyright 1993 by David Wexelblat <dwex@goblin.org>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the names of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 *
 */

#ifdef i386
#define _NEED_SYSI86
#endif
#include "xf86.h"
#include "xf86Priv.h"
#include "xf86_OSlib.h"

#ifndef MAP_FAILED
#define MAP_FAILED ((void *)-1)
#endif

/***************************************************************************/
/* Video Memory Mapping section 					   */
/***************************************************************************/

char *apertureDevName = NULL;

Bool
xf86LinearVidMem(void)
{
	int	mmapFd;

	if (apertureDevName)
	    return TRUE;

	apertureDevName = "/dev/xsvc";
	if ((mmapFd = open(apertureDevName, O_RDWR)) < 0)
	{
	    apertureDevName = "/dev/fbs/aperture";
	    if((mmapFd = open(apertureDevName, O_RDWR)) < 0)
	    {
		xf86MsgVerb(X_WARNING, 0,
		    "xf86LinearVidMem: failed to open %s (%s)\n",
		    apertureDevName, strerror(errno));
		xf86MsgVerb(X_WARNING, 0,
		    "xf86LinearVidMem: either /dev/fbs/aperture or /dev/xsvc"
		    " device driver required\n");
		xf86MsgVerb(X_WARNING, 0,
		    "xf86LinearVidMem: linear memory access disabled\n");
		apertureDevName = NULL;
		return FALSE;
	    }
	}
	close(mmapFd);
	return TRUE;
}

pointer
xf86MapVidMem(int ScreenNum, int Flags, unsigned long Base, unsigned long Size)
{
	pointer base;
	int fd;

	if (!xf86LinearVidMem())
		FatalError("xf86MapVidMem:  no aperture device\n");

	fd = open(apertureDevName,
		  (Flags & VIDMEM_READONLY) ? O_RDONLY : O_RDWR);
	if (fd < 0)
		FatalError("xf86MapVidMem: failed to open %s (%s)\n",
			   apertureDevName, strerror(errno));

	base = mmap(NULL, Size,
		    (Flags & VIDMEM_READONLY) ?
			PROT_READ : (PROT_READ | PROT_WRITE),
		     MAP_SHARED, fd, (off_t)Base);
	close(fd);
	if (base == MAP_FAILED)
		FatalError("xf86MapVidMem:  mmap failure:  %s\n",
			   strerror(errno));

	return(base);
}

/* ARGSUSED */
void
xf86UnMapVidMem(int ScreenNum, pointer Base, unsigned long Size)
{
	munmap(Base, Size);
}

/***************************************************************************/
/* I/O Permissions section						   */
/***************************************************************************/

#ifdef i386
static Bool ExtendedEnabled = FALSE;
#endif

void
xf86EnableIO(void)
{
#ifdef i386
	if (ExtendedEnabled)
		return;

	if (sysi86(SI86V86, V86SC_IOPL, PS_IOPL) < 0)
		FatalError("xf86EnableIOPorts: Failed to set IOPL for I/O\n");

	ExtendedEnabled = TRUE;
#endif /* i386 */
}

void
xf86DisableIO(void)
{
#ifdef i386
	if(!ExtendedEnabled)
		return;

	sysi86(SI86V86, V86SC_IOPL, 0);

	ExtendedEnabled = FALSE;
#endif /* i386 */
}


/***************************************************************************/
/* Interrupt Handling section						   */
/***************************************************************************/

Bool xf86DisableInterrupts(void)
{
#ifdef i386
	if (!ExtendedEnabled && (sysi86(SI86V86, V86SC_IOPL, PS_IOPL) < 0))
		return FALSE;

#ifdef __GNUC__
	__asm__ __volatile__("cli");
#else
	asm("cli");
#endif /* __GNUC__ */

	if (!ExtendedEnabled)
		sysi86(SI86V86, V86SC_IOPL, 0);
#endif /* i386 */

	return TRUE;
}

void xf86EnableInterrupts(void)
{
#ifdef i386
	if (!ExtendedEnabled && (sysi86(SI86V86, V86SC_IOPL, PS_IOPL) < 0))
		return;

#ifdef __GNUC__
	__asm__ __volatile__("sti");
#else
	asm("sti");
#endif /* __GNUC__ */

	if (!ExtendedEnabled)
		sysi86(SI86V86, V86SC_IOPL, 0);
#endif /* i386 */
}

void
xf86MapReadSideEffects(int ScreenNum, int Flags, pointer Base,
	unsigned long Size)
{
}

Bool
xf86CheckMTRR(int ScreenNum)
{
	return FALSE;
}

