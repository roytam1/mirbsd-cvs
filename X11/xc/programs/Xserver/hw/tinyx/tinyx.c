/*
 * $XFree86: xc/programs/Xserver/hw/tinyx/tinyx.c,v 1.1 2004/06/02 22:43:00 dawes Exp $ 
 *
 * Copyright � 1999 Keith Packard
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Keith Packard not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Keith Packard makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * KEITH PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL KEITH PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
/*
 * Copyright (c) 2004 by The XFree86 Project, Inc.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 *   1.  Redistributions of source code must retain the above copyright
 *       notice, this list of conditions, and the following disclaimer.
 *
 *   2.  Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer
 *       in the documentation and/or other materials provided with the
 *       distribution, and in the same place and form as other copyright,
 *       license and disclaimer information.
 *
 *   3.  The end-user documentation included with the redistribution,
 *       if any, must include the following acknowledgment: "This product
 *       includes software developed by The XFree86 Project, Inc
 *       (http://www.xfree86.org/) and its contributors", in the same
 *       place and form as other third-party acknowledgments.  Alternately,
 *       this acknowledgment may appear in the software itself, in the
 *       same form and location as other such third-party acknowledgments.
 *
 *   4.  Except as contained in this notice, the name of The XFree86
 *       Project, Inc shall not be used in advertising or otherwise to
 *       promote the sale, use or other dealings in this Software without
 *       prior written authorization from The XFree86 Project, Inc.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE XFREE86 PROJECT, INC OR ITS CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "tinyx.h"
#ifdef PSEUDO8
#include "pseudo8/pseudo8.h"
#endif
#include <mivalidate.h>
#include <dixstruct.h>
#ifdef RANDR
#include <randrstr.h>
#endif

#ifdef XV
#include "txxv.h"
#endif

#ifdef DPMSExtension
#include "dpmsproc.h"
#endif

CARD8	kdBpp[] = { 1, 4, 8, 16, 24, 32 };

#define NUM_KD_BPP (sizeof (kdBpp) / sizeof (kdBpp[0]))

int                 kdScreenPrivateIndex;
unsigned long       kdGeneration;

Bool                kdVideoTest;
unsigned long       kdVideoTestTime;
Bool		    kdEmulateMiddleButton;
Bool		    kdDisableZaphod;
Bool		    kdEnabled;
int		    kdSubpixelOrder;
int		    kdVirtualTerminal = -1;
Bool		    kdSwitchPending;
DDXPointRec	    kdOrigin;

/*
 * Carry arguments from InitOutput through driver initialization
 * to KdScreenInit
 */

KdOsFuncs	*kdOsFuncs;

void
KdSetRootClip (ScreenPtr pScreen, BOOL enable)
{
#ifndef FB_OLD_SCREEN
    WindowPtr	pWin = WindowTable[pScreen->myNum];
    WindowPtr	pChild;
    Bool	WasViewable;
    Bool	anyMarked = FALSE;
    RegionPtr	pOldClip = NULL, bsExposed;
#ifdef DO_SAVE_UNDERS
    Bool	dosave = FALSE;
#endif
    WindowPtr   pLayerWin;
    BoxRec	box;

    if (!pWin)
	return;
    WasViewable = (Bool)(pWin->viewable);
    if (WasViewable)
    {
	for (pChild = pWin->firstChild; pChild; pChild = pChild->nextSib)
	{
	    (void) (*pScreen->MarkOverlappedWindows)(pChild,
						     pChild,
						     &pLayerWin);
	}
	(*pScreen->MarkWindow) (pWin);
	anyMarked = TRUE;
	if (pWin->valdata)
	{
	    if (HasBorder (pWin))
	    {
		RegionPtr	borderVisible;

		borderVisible = REGION_CREATE(pScreen, NullBox, 1);
		REGION_SUBTRACT(pScreen, borderVisible,
				&pWin->borderClip, &pWin->winSize);
		pWin->valdata->before.borderVisible = borderVisible;
	    }
	    pWin->valdata->before.resized = TRUE;
	}
    }

    if (enable)
    {
	box.x1 = 0;
	box.y1 = 0;
	box.x2 = pScreen->width;
	box.y2 = pScreen->height;
	pWin->drawable.width = pScreen->width;
	pWin->drawable.height = pScreen->height;
	REGION_INIT (pScreen, &pWin->winSize, &box, 1);
	REGION_INIT (pScreen, &pWin->borderSize, &box, 1);
	REGION_RESET(pScreen, &pWin->borderClip, &box);
	REGION_BREAK (pWin->drawable.pScreen, &pWin->clipList);
    }
    else
    {
	REGION_EMPTY(pScreen, &pWin->borderClip);
	REGION_BREAK (pWin->drawable.pScreen, &pWin->clipList);
    }
    
    ResizeChildrenWinSize (pWin, 0, 0, 0, 0);
    
    if (WasViewable)
    {
	if (pWin->backStorage)
	{
	    pOldClip = REGION_CREATE(pScreen, NullBox, 1);
	    REGION_COPY(pScreen, pOldClip, &pWin->clipList);
	}

	if (pWin->firstChild)
	{
	    anyMarked |= (*pScreen->MarkOverlappedWindows)(pWin->firstChild,
							   pWin->firstChild,
							   (WindowPtr *)NULL);
	}
	else
	{
	    (*pScreen->MarkWindow) (pWin);
	    anyMarked = TRUE;
	}

#ifdef DO_SAVE_UNDERS
	if (DO_SAVE_UNDERS(pWin))
	{
	    dosave = (*pScreen->ChangeSaveUnder)(pLayerWin, pLayerWin);
	}
#endif /* DO_SAVE_UNDERS */

	if (anyMarked)
	    (*pScreen->ValidateTree)(pWin, NullWindow, VTOther);
    }

    if (pWin->backStorage &&
	((pWin->backingStore == Always) || WasViewable))
    {
	if (!WasViewable)
	    pOldClip = &pWin->clipList; /* a convenient empty region */
	bsExposed = (*pScreen->TranslateBackingStore)
			     (pWin, 0, 0, pOldClip,
			      pWin->drawable.x, pWin->drawable.y);
	if (WasViewable)
	    REGION_DESTROY(pScreen, pOldClip);
	if (bsExposed)
	{
	    RegionPtr	valExposed = NullRegion;
    
	    if (pWin->valdata)
		valExposed = &pWin->valdata->after.exposed;
	    (*pScreen->WindowExposures) (pWin, valExposed, bsExposed);
	    if (valExposed)
		REGION_EMPTY(pScreen, valExposed);
	    REGION_DESTROY(pScreen, bsExposed);
	}
    }
    if (WasViewable)
    {
	if (anyMarked)
	    (*pScreen->HandleExposures)(pWin);
#ifdef DO_SAVE_UNDERS
	if (dosave)
	    (*pScreen->PostChangeSaveUnder)(pLayerWin, pLayerWin);
#endif /* DO_SAVE_UNDERS */
	if (anyMarked && pScreen->PostValidateTree)
	    (*pScreen->PostValidateTree)(pWin, NullWindow, VTOther);
    }
    if (pWin->realized)
	WindowsRestructured ();
#endif	/* !FB_OLD_SCREEN */
}

void
KdDisableScreen (ScreenPtr pScreen)
{
    KdScreenPriv(pScreen);
    
    if (!pScreenPriv->enabled)
	return;
    KdCheckSync (pScreen);
    if (!pScreenPriv->closed)
	KdSetRootClip (pScreen, FALSE);
    KdDisableColormap (pScreen);
    if (!pScreenPriv->screen->dumb)
	(*pScreenPriv->card->cfuncs->disableAccel) (pScreen);
    if (!pScreenPriv->screen->softCursor)
	(*pScreenPriv->card->cfuncs->disableCursor) (pScreen);
    if (pScreenPriv->card->cfuncs->dpms)
	(*pScreenPriv->card->cfuncs->dpms) (pScreen, KD_DPMS_NORMAL);
    pScreenPriv->enabled = FALSE;
    (*pScreenPriv->card->cfuncs->disable) (pScreen);
}

void
KdSuspend (void)
{
    KdCardInfo	    *card;
    KdScreenInfo    *screen;

    if (kdEnabled)
    {
	for (card = kdCardInfo; card; card = card->next)
	{
	    for (screen = card->screenList; screen; screen = screen->next)
		if (screen->mynum == card->selected && screen->pScreen)
		    KdDisableScreen (screen->pScreen);
	    if (card->driver)
		(*card->cfuncs->restore) (card);
	}
	KdDisableInput ();
    }
}

void
KdDisableScreens (void)
{
    KdSuspend ();
    if (kdEnabled)
    {
	(*kdOsFuncs->Disable) ();
	kdEnabled = FALSE;
    }
}

Bool
KdEnableScreen (ScreenPtr pScreen)
{
    KdScreenPriv (pScreen);

    if (pScreenPriv->enabled)
	return TRUE;
    if (!(*pScreenPriv->card->cfuncs->enable) (pScreen))
	return FALSE;
    pScreenPriv->enabled = TRUE;
    pScreenPriv->card->selected = pScreenPriv->screen->mynum;
    if (!pScreenPriv->screen->softCursor)
	(*pScreenPriv->card->cfuncs->enableCursor) (pScreen);
    if (!pScreenPriv->screen->dumb)
	(*pScreenPriv->card->cfuncs->enableAccel) (pScreen);
    KdEnableColormap (pScreen);
    KdSetRootClip (pScreen, TRUE);
    if (pScreenPriv->card->cfuncs->dpms)
	(*pScreenPriv->card->cfuncs->dpms) (pScreen, pScreenPriv->dpmsState);
    return TRUE;
}

void
KdResume (void)
{
    KdCardInfo	    *card;
    KdScreenInfo    *screen;

    if (kdEnabled)
    {
	for (card = kdCardInfo; card; card = card->next)
	{
	    (*card->cfuncs->preserve) (card);
	    for (screen = card->screenList; screen; screen = screen->next)
		if (screen->mynum == card->selected && screen->pScreen)
		    KdEnableScreen (screen->pScreen);
	}
	KdEnableInput ();
	KdReleaseAllKeys ();
    }
}

void
KdEnableScreens (void)
{
    if (!kdEnabled)
    {
	kdEnabled = TRUE;
	(*kdOsFuncs->Enable) ();
    }
    KdResume ();
}

void
KdProcessSwitch (void)
{
    if (kdEnabled)
	KdDisableScreens ();
    else
    {
	KdEnableScreens ();
    }
}

void
AbortDDX(void)
{
    KdDisableScreens ();
    if (kdOsFuncs)
    {
	if (kdEnabled)
	    (*kdOsFuncs->Disable) ();
	(*kdOsFuncs->Fini) ();
    }
}

void
KdUseMsg()
{
  ErrorF("\nTinyX Device Dependent Usage:\n");
  ErrorF("-card pcmcia	Use PCMCIA card as additional screen\n");
  ErrorF("-screen WIDTH[/WIDTHMM]xHEIGHT[/HEIGHTMM][@ROTATION][X][Y][xDEPTH/BPP{,DEPTH/BPP}[xFREQ]]	Specify screen characteristics\n");
  ErrorF("-zaphod		Disable cursor screen switching\n");
  ErrorF("-2button	Emulate 3 button mouse\n");
  ErrorF("-3button	Disable 3 button mouse emulation\n");
  ErrorF("-dumb 		Disable hardware acceleration\n");
  ErrorF("-softCursor	Force software cursor\n");
  ErrorF("-videoTest	Start the server, pause momentarily and exit\n");
  ErrorF("-origin X,Y	Locates the next screen in the the virtual screen (Xinerama)\n");
  ErrorF("-mouse path[,n]	Filename of mouse device, n is number of buttons\n");
  ErrorF("vtxx		Use virtual terminal xx instead of the next available\n");
  ErrorF("\n");
}

void
ddxGiveUp ()
{
    AbortDDX ();
}

Bool	kdDumbDriver;
Bool	kdSoftCursor;

static char *
KdParseFindNext (char *cur, char *delim, char *save, char *last)
{
    while (*cur && !strchr (delim, *cur))
    {
	*save++ = *cur++;
    }
    *save = 0;
    *last = *cur;
    if (*cur)
	cur++;
    return cur;
}

Rotation
KdAddRotation (Rotation a, Rotation b)
{
    Rotation	rotate = (a & RR_Rotate_All) * (b & RR_Rotate_All);
    Rotation	reflect = (a & RR_Reflect_All) ^ (b & RR_Reflect_All);

    if (rotate > RR_Rotate_270)
	rotate /= (RR_Rotate_270 * RR_Rotate_90);
    return reflect | rotate;
}

Rotation
KdSubRotation (Rotation a, Rotation b)
{
    Rotation	rotate = (a & RR_Rotate_All) * 16 / (b & RR_Rotate_All);
    Rotation	reflect = (a & RR_Reflect_All) ^ (b & RR_Reflect_All);

    if (rotate > RR_Rotate_270)
	rotate /= (RR_Rotate_270 * RR_Rotate_90);
    return reflect | rotate;
}

void
KdParseScreen (KdScreenInfo *screen,
	       char	    *arg)
{
    char    delim;
    char    save[1024];
    int	    fb;
    int	    i;
    int	    pixels, mm;
    
    screen->dumb = kdDumbDriver;
    screen->softCursor = kdSoftCursor;
    screen->origin = kdOrigin;
    screen->randr = RR_Rotate_0;
    screen->width = 0;
    screen->height = 0;
    screen->width_mm = 0;
    screen->height_mm = 0;
    screen->subpixel_order = kdSubpixelOrder;
    screen->rate = 0;
    for (fb = 0; fb < KD_MAX_FB; fb++)
	screen->fb[fb].depth = 0;
    if (!arg)
	return;
    if (strlen (arg) >= sizeof (save))
	return;
    
    for (i = 0; i < 2; i++)
    {
	arg = KdParseFindNext (arg, "x/@XY", save, &delim);
	if (!save[0])
	    return;
	
	pixels = atoi(save);
	mm = 0;
	
	if (delim == '/')
	{
	    arg = KdParseFindNext (arg, "x@XY", save, &delim);
	    if (!save[0])
		return;
	    mm = atoi(save);
	}
	
	if (i == 0)
	{
	    screen->width = pixels;
	    screen->width_mm = mm;
	}
	else
	{
	    screen->height = pixels;
	    screen->height_mm = mm;
	}
	if (delim != 'x' && delim != '@' && delim != 'X' && delim != 'Y')
	    return;
    }

    kdOrigin.x += screen->width;
    kdOrigin.y = 0;
    kdDumbDriver = FALSE;
    kdSoftCursor = FALSE;
    kdSubpixelOrder = SubPixelUnknown;

    if (delim == '@')
    {
	arg = KdParseFindNext (arg, "xXY", save, &delim);
	if (save[0])
	{
	    int	    rotate = atoi (save);
	    if (rotate < 45)
		screen->randr = RR_Rotate_0;
	    else if (rotate < 135)
		screen->randr = RR_Rotate_90;
	    else if (rotate < 225)
		screen->randr = RR_Rotate_180;
	    else if (rotate < 315)
		screen->randr = RR_Rotate_270;
	    else
		screen->randr = RR_Rotate_0;
	}
    }
    if (delim == 'X')
    {
	arg = KdParseFindNext (arg, "xY", save, &delim);
	screen->randr |= RR_Reflect_X;
    }

    if (delim == 'Y')
    {
	arg = KdParseFindNext (arg, "xY", save, &delim);
	screen->randr |= RR_Reflect_Y;
    }
    
    fb = 0;
    while (fb < KD_MAX_FB)
    {
	arg = KdParseFindNext (arg, "x/,", save, &delim);
	if (!save[0])
	    break;
	screen->fb[fb].depth = atoi(save);
	if (delim == '/')
	{
	    arg = KdParseFindNext (arg, "x,", save, &delim);
	    if (!save[0])
		break;
	    screen->fb[fb].bitsPerPixel = atoi (save);
	}
	else
	    screen->fb[fb].bitsPerPixel = 0;
	if (delim != ',')
	    break;
	fb++;
    }

    if (delim == 'x')
    {
	arg = KdParseFindNext (arg, "x", save, &delim);
	if (save[0])
	    screen->rate = atoi(save);
    }
}

/*
 * Mouse argument syntax:
 *
 *  device,protocol,options...
 *
 *  Options are any of:
 *	1-5	    n button mouse
 *	2button	    emulate middle button
 *	{NMO}	    Reorder buttons
 */

char *
KdSaveString (char *str)
{
    char    *n = (char *) xalloc (strlen (str) + 1);

    if (!n)
	return 0;
    strcpy (n, str);
    return n;
}

/*
 * Parse mouse information.  Syntax:
 *
 *  <device>,<nbutton>,<protocol>{,<option>}...
 *
 * options: {nmo}   pointer mapping (e.g. {321})
 *	    2button emulate middle button
 *	    3button dont emulate middle button
 */

void
KdParseMouse (char *arg)
{
    char	save[1024];
    char	delim;
    KdMouseInfo	*mi;
    int		i;
    
    mi = KdMouseInfoAdd ();
    if (!mi)
	return;
    mi->name = 0;
    mi->prot = 0;
    mi->emulateMiddleButton = kdEmulateMiddleButton;
    mi->nbutton = 3;
    for (i = 0; i < KD_MAX_BUTTON; i++)
	mi->map[i] = i + 1;
    
    if (!arg)
	return;
    if (strlen (arg) >= sizeof (save))
	return;
    arg = KdParseFindNext (arg, ",", save, &delim);
    if (!save[0])
	return;
    mi->name = KdSaveString (save);
    if (delim != ',')
	return;
    
    arg = KdParseFindNext (arg, ",", save, &delim);
    if (!save[0])
	return;
    
    if ('1' <= save[0] && save[0] <= '0' + KD_MAX_BUTTON && save[1] == '\0')
    {
        mi->nbutton = save[0] - '0';
	if (mi->nbutton > KD_MAX_BUTTON)
	{
	    UseMsg ();
	    return;
	}
    }
    
    if (!delim != ',')
	return;
    
    arg = KdParseFindNext (arg, ",", save, &delim);
    
    if (save[0])
	mi->prot = KdSaveString (save);
    
    while (delim == ',')
    {
	arg = KdParseFindNext (arg, ",", save, &delim);
	if (save[0] == '{')
	{
	    char	*s = save + 1;
	    i = 0;
	    while (*s && *s != '}')
	    {
		if ('1' <= *s && *s <= '0' + mi->nbutton)
		    mi->map[i] = *s - '0';
		else
		    UseMsg ();
		s++;
	    }
	}
	else if (!strcmp (save, "2button"))
	    mi->emulateMiddleButton = TRUE;
	else if (!strcmp (save, "3button"))
	    mi->emulateMiddleButton = FALSE;
	else
	    UseMsg ();
    }
}

static void
KdParseRgba (char *rgba)
{
    if (!strcmp (rgba, "rgb"))
	kdSubpixelOrder = SubPixelHorizontalRGB;
    else if (!strcmp (rgba, "bgr"))
	kdSubpixelOrder = SubPixelHorizontalBGR;
    else if (!strcmp (rgba, "vrgb"))
	kdSubpixelOrder = SubPixelVerticalRGB;
    else if (!strcmp (rgba, "vbgr"))
	kdSubpixelOrder = SubPixelVerticalBGR;
    else if (!strcmp (rgba, "none"))
	kdSubpixelOrder = SubPixelNone;
    else
	kdSubpixelOrder = SubPixelUnknown;
}

int
KdProcessArgument (int argc, char **argv, int i)
{
    KdCardInfo	    *card;
    KdScreenInfo    *screen;

    if (!strcmp (argv[i], "-card"))
    {
	if ((i+1) < argc)
	    InitCard (argv[i+1]);
	else
	    UseMsg ();
	return 2;
    }
    if (!strcmp (argv[i], "-screen"))
    {
	if ((i+1) < argc)
	{
	    card = KdCardInfoLast ();
	    if (!card)
	    {
		InitCard (0);
		card = KdCardInfoLast ();
	    }
	    if (card) {
		screen = KdScreenInfoAdd (card);
		KdParseScreen (screen, argv[i+1]);
	    } else
		ErrorF("No matching card found!\n");
	}
	else
	    UseMsg ();
	return 2;
    }
    if (!strcmp (argv[i], "-zaphod"))
    {
	kdDisableZaphod = TRUE;
	return 1;
    }
    if (!strcmp (argv[i], "-3button"))
    {
	kdEmulateMiddleButton = FALSE;
	return 1;
    }
    if (!strcmp (argv[i], "-2button"))
    {
	kdEmulateMiddleButton = TRUE;
	return 1;
    }
    if (!strcmp (argv[i], "-dumb"))
    {
	kdDumbDriver = TRUE;
	return 1;
    }
    if (!strcmp (argv[i], "-softCursor"))
    {
	kdSoftCursor = TRUE;
	return 1;
    }
    if (!strcmp (argv[i], "-videoTest"))
    {
	kdVideoTest = TRUE;
	return 1;
    }
    if (!strcmp (argv[i], "-origin"))
    {
	if ((i+1) < argc)
	{
	    char    *x = argv[i+1];
	    char    *y = strchr (x, ',');
	    if (x)
		kdOrigin.x = atoi (x);
	    else
		kdOrigin.x = 0;
	    if (y)
		kdOrigin.y = atoi(y+1);
	    else
		kdOrigin.y = 0;
	}
	else
	    UseMsg ();
	return 2;
    }
    if (!strcmp (argv[i], "-mouse"))
    {
	if ((i+1) < argc)
	    KdParseMouse (argv[i+1]);
	else
	    UseMsg ();
	return 2;
    }
    if (!strcmp (argv[i], "-rgba"))
    {
	if ((i+1) < argc)
	    KdParseRgba (argv[i+1]);
	else
	    UseMsg ();
	return 2;
    }
    if (!strncmp (argv[i], "vt", 2) &&
	sscanf (argv[i], "vt%2d", &kdVirtualTerminal) == 1)
    {
	return 1;
    }
#ifdef PSEUDO8
    return p8ProcessArgument (argc, argv, i);
#else
    return 0;
#endif
}

/*
 * These are getting tossed in here until I can think of where
 * they really belong
 */

void
KdOsInit (KdOsFuncs *pOsFuncs)
{
    kdOsFuncs = pOsFuncs;
    if (pOsFuncs)
    {
	if (serverGeneration == 1) 
	    (*pOsFuncs->Init) ();
    }
}

Bool
KdAllocatePrivates (ScreenPtr pScreen)
{
    KdPrivScreenPtr	pScreenPriv;
    
    if (kdGeneration != serverGeneration)
    {
	kdScreenPrivateIndex = AllocateScreenPrivateIndex();
	kdGeneration         = serverGeneration;
    }
    pScreenPriv = (KdPrivScreenPtr) xalloc(sizeof (*pScreenPriv));
    if (!pScreenPriv)
	return FALSE;
    memset (pScreenPriv, '\0', sizeof (KdPrivScreenRec));
    KdSetScreenPriv (pScreen, pScreenPriv);
    return TRUE;
}

Bool
KdCloseScreen (int index, ScreenPtr pScreen)
{
    KdScreenPriv(pScreen);
    KdScreenInfo    *screen = pScreenPriv->screen;
    KdCardInfo	    *card = pScreenPriv->card;
    Bool	    ret;
    
    pScreenPriv->closed = TRUE;
    pScreen->CloseScreen = pScreenPriv->CloseScreen;
    ret = (*pScreen->CloseScreen) (index, pScreen);
    
    if (pScreenPriv->dpmsState != KD_DPMS_NORMAL)
	(*card->cfuncs->dpms) (pScreen, KD_DPMS_NORMAL);
    
    if (screen->mynum == card->selected)
	KdDisableScreen (pScreen);
    
    /*
     * Restore video hardware when last screen is closed
     */
    if (screen == card->screenList)
    {
	if (kdEnabled)
	    (*card->cfuncs->restore) (card);
    }
	
    if (!pScreenPriv->screen->dumb)
	(*card->cfuncs->finiAccel) (pScreen);

    if (!pScreenPriv->screen->softCursor)
	(*card->cfuncs->finiCursor) (pScreen);

    (*card->cfuncs->scrfini) (screen);

    /*
     * Clean up card when last screen is closed, DIX closes them in
     * reverse order, thus we check for when the first in the list is closed
     */
    if (screen == card->screenList)
    {
	(*card->cfuncs->cardfini) (card);
	/*
	 * Clean up OS when last card is closed
	 */
	if (card == kdCardInfo)
	{
	    if (kdEnabled)
	    {
		kdEnabled = FALSE;
		(*kdOsFuncs->Disable) ();
	    }
	}
    }
    
    pScreenPriv->screen->pScreen = 0;
    
    xfree ((pointer) pScreenPriv);
    return ret;
}

Bool
KdSaveScreen (ScreenPtr pScreen, int on)
{
    KdScreenPriv(pScreen);
    int	    dpmsState;
    
    if (!pScreenPriv->card->cfuncs->dpms)
	return FALSE;
    
    dpmsState = pScreenPriv->dpmsState;
    switch (on) {
    case SCREEN_SAVER_OFF:
	dpmsState = KD_DPMS_NORMAL;
	break;
    case SCREEN_SAVER_ON:
	if (dpmsState == KD_DPMS_NORMAL)
	    dpmsState = KD_DPMS_NORMAL+1;
	break;
    case SCREEN_SAVER_CYCLE:
	if (dpmsState < KD_DPMS_MAX)
	    dpmsState++;
	break;
    case SCREEN_SAVER_FORCER:
	break;
    }
    if (dpmsState != pScreenPriv->dpmsState)
    {
	if (pScreenPriv->enabled)
	    (*pScreenPriv->card->cfuncs->dpms) (pScreen, dpmsState);
	pScreenPriv->dpmsState = dpmsState;
    }
    return TRUE;
}

Bool
KdCreateWindow (WindowPtr pWin)
{
#ifndef PHOENIX
    if (!pWin->parent)
    {
	KdScreenPriv(pWin->drawable.pScreen);

	if (!pScreenPriv->enabled)
	{
	    REGION_EMPTY (pWin->drawable.pScreen, &pWin->borderClip);
	    REGION_BREAK (pWin->drawable.pScreen, &pWin->clipList);
	}
    }
#endif
    return fbCreateWindow (pWin);
}

void
KdSetSubpixelOrder (ScreenPtr pScreen, Rotation randr)
{
    KdScreenPriv(pScreen);
    KdScreenInfo	*screen = pScreenPriv->screen;
    int			subpixel_order = screen->subpixel_order;
    Rotation		subpixel_dir;
    int			i;
    
    static struct {
	int	    subpixel_order;
	Rotation    direction;
    } orders[] = {
	{ SubPixelHorizontalRGB, 	RR_Rotate_0 },
	{ SubPixelHorizontalBGR,	RR_Rotate_180 },
	{ SubPixelVerticalRGB,		RR_Rotate_270 },
	{ SubPixelVerticalBGR,		RR_Rotate_90 },
    };

    static struct {
	int	bit;
	int	normal; 
	int	reflect;
    } reflects[] = {
	{ RR_Reflect_X, SubPixelHorizontalRGB,	SubPixelHorizontalBGR },
	{ RR_Reflect_X, SubPixelHorizontalBGR,	SubPixelHorizontalRGB },
	{ RR_Reflect_Y, SubPixelVerticalRGB,	SubPixelVerticalBGR },
	{ RR_Reflect_Y, SubPixelVerticalRGB,	SubPixelVerticalRGB },
    };
    
    /* map subpixel to direction */
    for (i = 0; i < 4; i++)
	if (orders[i].subpixel_order == subpixel_order)
	    break;
    if (i < 4)
    {
	subpixel_dir = KdAddRotation (randr & RR_Rotate_All, orders[i].direction);
	
	/* map back to subpixel order */
	for (i = 0; i < 4; i++)
	    if (orders[i].direction & subpixel_dir)
	    {
		subpixel_order = orders[i].subpixel_order;
		break;
	    }
	/* reflect */
	for (i = 0; i < 4; i++)
	    if ((randr & reflects[i].bit) &&
		reflects[i].normal == subpixel_order)
	    {
		subpixel_order = reflects[i].reflect;
		break;
	    }
    }
    PictureSetSubpixelOrder (pScreen, subpixel_order);
}

/* Pass through AddScreen, which doesn't take any closure */
static KdScreenInfo *kdCurrentScreen;

Bool
KdScreenInit(int index, ScreenPtr pScreen, int argc, char **argv)
{
    KdScreenInfo	*screen = kdCurrentScreen;
    KdCardInfo		*card = screen->card;
    KdPrivScreenPtr	pScreenPriv;
    int			fb;

    KdAllocatePrivates (pScreen);

    pScreenPriv = KdGetScreenPriv(pScreen);
    
    screen->pScreen = pScreen;
    pScreenPriv->screen = screen;
    pScreenPriv->card = card;
    for (fb = 0; fb < KD_MAX_FB && screen->fb[fb].depth; fb++)
	pScreenPriv->bytesPerPixel[fb] = screen->fb[fb].bitsPerPixel >> 3;
    pScreenPriv->dpmsState = KD_DPMS_NORMAL;
#ifdef PANORAMIX
    dixScreenOrigins[pScreen->myNum] = screen->origin;
#endif

    if (!monitorResolution)
	monitorResolution = 75;
    /*
     * This is done in this order so that backing store wraps
     * our GC functions; fbFinishScreenInit initializes MI
     * backing store
     */
    if (!fbSetupScreen (pScreen, 
			screen->fb[0].frameBuffer, 
			screen->width, screen->height, 
			monitorResolution, monitorResolution, 
			screen->fb[0].pixelStride,
			screen->fb[0].bitsPerPixel))
    {
	return FALSE;
    }

    /*
     * Set colormap functions
     */
    pScreen->InstallColormap	= KdInstallColormap;
    pScreen->UninstallColormap	= KdUninstallColormap;
    pScreen->ListInstalledColormaps = KdListInstalledColormaps;
    pScreen->StoreColors	= KdStoreColors;
     
    pScreen->SaveScreen		= KdSaveScreen;
    pScreen->CreateWindow	= KdCreateWindow;

#ifdef FB_OLD_SCREEN
    pScreenPriv->BackingStoreFuncs.SaveAreas = fbSaveAreas;
    pScreenPriv->BackingStoreFuncs.RestoreAreas = fbSaveAreas;
    pScreenPriv->BackingStoreFuncs.SetClipmaskRgn = 0;
    pScreenPriv->BackingStoreFuncs.GetImagePixmap = 0;
    pScreenPriv->BackingStoreFuncs.GetSpansPixmap = 0;
#endif

#if KD_MAX_FB > 1
    if (screen->fb[1].depth)
    {
	if (!fbOverlayFinishScreenInit (pScreen, 
					screen->fb[0].frameBuffer, 
					screen->fb[1].frameBuffer, 
					screen->width, screen->height, 
					monitorResolution, monitorResolution,
					screen->fb[0].pixelStride,
					screen->fb[1].pixelStride,
					screen->fb[0].bitsPerPixel,
					screen->fb[1].bitsPerPixel,
					screen->fb[0].depth,
					screen->fb[1].depth))
	{
	    return FALSE;
	}
    }
    else
#endif
    {
	if (!fbFinishScreenInit (pScreen, 
				 screen->fb[0].frameBuffer, 
				 screen->width, screen->height,
				 monitorResolution, monitorResolution,
				 screen->fb[0].pixelStride,
				 screen->fb[0].bitsPerPixel))
	{
	    return FALSE;
	}
    }
    
    /*
     * Fix screen sizes; for some reason mi takes dpi instead of mm.
     * Rounding errors are annoying
     */
    if (screen->width_mm)
	pScreen->mmWidth = screen->width_mm;
    else
	screen->width_mm = pScreen->mmWidth;
    if (screen->height_mm)
	pScreen->mmHeight = screen->height_mm;
    else
	screen->height_mm = pScreen->mmHeight;
    
    /*
     * Plug in our own block/wakeup handlers.
     * miScreenInit installs NoopDDA in both places
     */
    pScreen->BlockHandler	= KdBlockHandler;
    pScreen->WakeupHandler	= KdWakeupHandler;
    
#ifdef RENDER
    if (!fbPictureInit (pScreen, 0, 0))
	return FALSE;
#endif
    if (card->cfuncs->initScreen)
	if (!(*card->cfuncs->initScreen) (pScreen))
	    return FALSE;
	    
    if (!screen->dumb && card->cfuncs->initAccel)
	if (!(*card->cfuncs->initAccel) (pScreen))
	    screen->dumb = TRUE;

#ifdef PSEUDO8
    (void) p8Init (pScreen, PSEUDO8_USE_DEFAULT);
#endif
    
    if (card->cfuncs->finishInitScreen)
	if (!(*card->cfuncs->finishInitScreen) (pScreen))
	    return FALSE;
	    
#if 0
    fbInitValidateTree (pScreen);
#endif
    
#if 0
    pScreen->backingStoreSupport = Always;
#ifdef FB_OLD_SCREEN
    miInitializeBackingStore (pScreen, &pScreenPriv->BackingStoreFuncs);
#else
    miInitializeBackingStore (pScreen);
#endif
#endif


    /* 
     * Wrap CloseScreen, the order now is:
     *	KdCloseScreen
     *	miBSCloseScreen
     *	fbCloseScreen
     */
    pScreenPriv->CloseScreen = pScreen->CloseScreen;
    pScreen->CloseScreen = KdCloseScreen;
    
    if (screen->softCursor ||
	!card->cfuncs->initCursor || 
	!(*card->cfuncs->initCursor) (pScreen))
    {
	/* Use MI for cursor display and event queueing. */
	screen->softCursor = TRUE;
	miDCInitialize(pScreen, &kdPointerScreenFuncs);
    }

    
    if (!fbCreateDefColormap (pScreen))
    {
	return FALSE;
    }

    KdSetSubpixelOrder (pScreen, screen->randr);

    /*
     * Enable the hardware
     */
    if (!kdEnabled)
    {
	kdEnabled = TRUE;
	(*kdOsFuncs->Enable) ();
    }
    
    if (screen->mynum == card->selected)
    {
	(*card->cfuncs->preserve) (card);
	if (!(*card->cfuncs->enable) (pScreen))
	    return FALSE;
	pScreenPriv->enabled = TRUE;
	if (!screen->softCursor)
	    (*card->cfuncs->enableCursor) (pScreen);
	KdEnableColormap (pScreen);
	if (!screen->dumb)
	    (*card->cfuncs->enableAccel) (pScreen);
    }
    
    return TRUE;
}

void
KdInitScreen (ScreenInfo    *pScreenInfo,
	      KdScreenInfo  *screen,
	      int	    argc,
	      char	    **argv)
{
    KdCardInfo	*card = screen->card;
    
    (*card->cfuncs->scrinit) (screen);
    
    if (!card->cfuncs->initAccel)
	screen->dumb = TRUE;
    if (!card->cfuncs->initCursor)
	screen->softCursor = TRUE;
	
}

static Bool
KdSetPixmapFormats (ScreenInfo	*pScreenInfo)
{
    CARD8	    depthToBpp[33];	/* depth -> bpp map */
    KdCardInfo	    *card;
    KdScreenInfo    *screen;
    int		    i;
    int		    bpp;
    int		    fb;
    PixmapFormatRec *format;

    for (i = 1; i <= 32; i++)
	depthToBpp[i] = 0;

    /*
     * Generate mappings between bitsPerPixel and depth,
     * also ensure that all screens comply with protocol
     * restrictions on equivalent formats for the same
     * depth on different screens
     */
    for (card = kdCardInfo; card; card = card->next)
    {
	for (screen = card->screenList; screen; screen = screen->next)
	{
	    for (fb = 0; fb < KD_MAX_FB && screen->fb[fb].depth; fb++)
	    {
		bpp = screen->fb[fb].bitsPerPixel;
		if (bpp == 24)
		    bpp = 32;
		if (!depthToBpp[screen->fb[fb].depth])
		    depthToBpp[screen->fb[fb].depth] = bpp;
		else if (depthToBpp[screen->fb[fb].depth] != bpp) 
		    return FALSE;
	    }
	}
    }
    
    /*
     * Fill in additional formats
     */
    for (i = 0; i < NUM_KD_BPP; i++)
	if (!depthToBpp[kdBpp[i]])
	    depthToBpp[kdBpp[i]] = kdBpp[i];
	
    pScreenInfo->imageByteOrder     = IMAGE_BYTE_ORDER;
    pScreenInfo->bitmapScanlineUnit = BITMAP_SCANLINE_UNIT;
    pScreenInfo->bitmapScanlinePad  = BITMAP_SCANLINE_PAD;
    pScreenInfo->bitmapBitOrder     = BITMAP_BIT_ORDER;
    
    pScreenInfo->numPixmapFormats = 0;
    
    for (i = 1; i <= 32; i++)
    {
	if (depthToBpp[i])
	{
	    format = &pScreenInfo->formats[pScreenInfo->numPixmapFormats++];
	    format->depth = i;
	    format->bitsPerPixel = depthToBpp[i];
	    format->scanlinePad = BITMAP_SCANLINE_PAD;
	}
    }
    
    return TRUE;
}

static void
KdAddScreen (ScreenInfo	    *pScreenInfo,
	     KdScreenInfo   *screen,
	     int	    argc,
	     char	    **argv)
{
    int	    i;
    /*
     * Fill in fb visual type masks for this screen
     */
    for (i = 0; i < pScreenInfo->numPixmapFormats; i++)
    {
	unsigned long	visuals;
	Pixel		rm, gm, bm;
	int		fb;
	
	visuals = 0;
	rm = gm = bm = 0;
	for (fb = 0; fb < KD_MAX_FB && screen->fb[fb].depth; fb++)
	{
	    if (pScreenInfo->formats[i].depth == screen->fb[fb].depth)
	    {
		visuals = screen->fb[fb].visuals;
		rm = screen->fb[fb].redMask;
		gm = screen->fb[fb].greenMask;
		bm = screen->fb[fb].blueMask;
		break;
	    }
	}
	fbSetVisualTypesAndMasks (pScreenInfo->formats[i].depth,
				  visuals,
				  8,
				  rm, gm, bm);
    }

    kdCurrentScreen = screen;
    
    AddScreen (KdScreenInit, argc, argv);
}

#if 0 /* This function is not used currently */

int
KdDepthToFb (ScreenPtr	pScreen, int depth)
{
    KdScreenPriv(pScreen);
    int	    fb;

    for (fb = 0; fb <= KD_MAX_FB && pScreenPriv->screen->fb[fb].frameBuffer; fb++)
	if (pScreenPriv->screen->fb[fb].depth == depth)
	    return fb;
}

#endif

void
KdInitOutput (ScreenInfo    *pScreenInfo,
	      int	    argc,
	      char	    **argv)
{
    KdCardInfo	    *card;
    KdScreenInfo    *screen;
    
    if (!kdCardInfo)
    {
	InitCard (0);
	if (!(card = KdCardInfoLast ()))
	    FatalError("No matching cards found!\n");
	screen = KdScreenInfoAdd (card);
	KdParseScreen (screen, 0);
    }
    /*
     * Initialize all of the screens for all of the cards
     */
    for (card = kdCardInfo; card; card = card->next)
    {
	if ((*card->cfuncs->cardinit) (card))
	{
	    for (screen = card->screenList; screen; screen = screen->next)
		KdInitScreen (pScreenInfo, screen, argc, argv);
	}
    }
    
    /*
     * Merge the various pixmap formats together, this can fail
     * when two screens share depth but not bitsPerPixel
     */
    if (!KdSetPixmapFormats (pScreenInfo))
	return;
    
    /*
     * Add all of the screens
     */
    for (card = kdCardInfo; card; card = card->next)
	for (screen = card->screenList; screen; screen = screen->next)
	    KdAddScreen (pScreenInfo, screen, argc, argv);
}

void
OsVendorFatalError()
{
}

#ifdef XTESTEXT1
void
XTestGenerateEvent(dev_type, keycode, keystate, mousex, mousey)
	int	dev_type;
	int	keycode;
	int	keystate;
	int	mousex;
	int	mousey;
{
}

void
XTestGetPointerPos(fmousex, fmousey)
	short *fmousex, *fmousey;
{
}

void
XTestJumpPointer(jx, jy, dev_type)
	int	jx;
	int	jy;
	int	dev_type;
{
}
#endif

#ifdef DPMSExtension
void
DPMSSet(int level)
{
}

int
DPMSGet (int *level)
{
    return -1;
}

Bool
DPMSSupported (void)
{
    return FALSE;
}
#endif
