/*
 * Copyright 1996 by Steven Lang <tiger@tyger.org>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Steven Lang not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.  Steven Lang makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * STEVEN LANG DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL STEVEN LANG BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTIONS, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * Steve Harris <steve@totl.net>, 2000-02-23
 * Southampton, UK
 *
 * Based on the xf86Summa driver, exensively hacked. Most of the bad
 * indenting is not my fault, dammit!
 *
 * Probably buggy as hell, no idea what the initialisation strings are,
 * no idea how to ack it. If the tablet stops responding power cycle it.
 */
/* $XFree86: xc/programs/Xserver/hw/xfree86/input/digitaledge/DigitalEdge.c,v 1.11 2004/10/23 15:29:30 dawes Exp $ */

#ifndef XFree86LOADER
#include <unistd.h>
#include <errno.h>
#endif

#include "misc.h"
#include "xf86.h"
#define NEED_XF86_TYPES
#if !defined(DGUX)
#include "xf86_ansic.h"
#include "xisb.h"
#endif
#include "xf86_OSproc.h"
#include "xf86Xinput.h"
#include "exevents.h"		/* Needed for InitValuator/Proximity stuff */
#include "keysym.h"
#include "mipointer.h"

#include "xf86Module.h"

#define wait_for_fd(fd) xf86WaitForInput((fd), 1000)
#define tcflush(fd, n) xf86FlushInput((fd))
#undef read
#define read(a,b,c) xf86ReadSerial((a),(b),(c))
#undef write
#define write(a,b,c) xf86WriteSerial((a),(char*)(b),(c))
#undef close
#define close(a) xf86CloseSerial((a))
#undef PRIVATE
#define PRIVATE(x) XI_PRIVATE(x)

/* 
 * Be sure to set vmin appropriately for your device's protocol. You want to
 * read a full packet before returning
 */

static const char *default_options[] =
{
        "BaudRate",     "9600",
        "DataBits",     "8",
        "StopBits",     "1",
        "Parity",       "Odd",
        "FlowControl",  "Xoff",
        "VTime",        "10",
        "VMin",         "1",
        NULL
};

static InputDriverPtr dedgeDrv;

/*
** Debugging macros
*/
#ifdef DBG
#undef DBG
#endif
#ifdef DEBUG
#undef DEBUG
#endif

static int debug_level = 10;
#define DEBUG	1
#if DEBUG
#define 	DBG(lvl, f) 	{if ((lvl) <= debug_level) f;}
#else
#define 	DBG(lvl, f)
#endif

/*
** Device records
*/
#define ABSOLUTE_FLAG		1
#define STYLUS_FLAG		2
#define COMPATIBLE_FLAG		4

typedef struct {
    char *dedgeDevice;		/* device file name */
    int dedgeInc;			/* increment between transmits */
    int dedgeButTrans;		/* button translation flags */
    int dedgeOldX;		/* previous X position */
    int dedgeOldY;		/* previous Y position */
    int dedgeOldProximity;	/* previous proximity */
    int dedgeOldPush;		/* previous buttons state */
    int dedgeOldBarrel;		/* previous buttons state */
    int dedgeOldPressure;		/* previous pen pressure */
    int dedgeMaxX;		/* max X value */
    int dedgeMaxY;		/* max Y value */
    int dedgeXSize;		/* active area X size */
    int dedgeXOffset;		/* active area X offset */
    int dedgeYSize;		/* active area Y size */
    int dedgeYOffset;		/* active area Y offset */
    int dedgeRes;			/* resolution in lines per inch */
	int dedgeClickThresh;	/* Click threshold in arbitary units */
    int flags;			/* various flags */
    int dedgeIndex;		/* number of bytes read */
    unsigned char dedgeData[5];	/* data read on the device */
} DigitalEdgeDeviceRec, *DigitalEdgeDevicePtr;

/*
** Configuration data
*/
#define DEDGE_SECTION_NAME "DigitalEdge"

/*
** Contants and macro
*/
#define BUFFER_SIZE	256	/* size of reception buffer */
#define XI_NAME 	"DIGITALEDGE"	/* X device name for the stylus */

#define SYSCALL(call) while(((call) == -1) && (errno == EINTR))

#define SS_TABID0	"0"	/* Tablet ID 0 */
#define SS_FIRMID	"z?"	/* Request firmware ID string */
#define SS_CONFIG	"a"	/* Send configuration (max coords) */

#define SS_ABSOLUTE	'F'	/* Absolute mode */
#define SS_RELATIVE	'E'	/* Relative mode */

#define SS_UPPER_ORIGIN	"b"	/* Origin upper left */
#define SS_500LPI	"h"	/* 500 lines per inch */

#define SS_PROMPT_MODE	"B"	/* Prompt mode */
#define SS_STREAM_MODE	"@"	/* Stream mode */
#define SS_INCREMENT	'I'	/* Set increment */
#define SS_BINARY_FMT	"zb"	/* Binary reporting */

#define SS_PROMPT	"P"	/* Prompt for current position */

static const char *ss_initstr =
    SS_TABID0 SS_UPPER_ORIGIN SS_BINARY_FMT SS_STREAM_MODE;

#define PHASING_BIT	0x80
#define PROXIMITY_BIT	0x01
#define TABID_BIT	0x20
#define XSIGN_BIT	0x10
#define YSIGN_BIT	0x08
#define BUTTON_BITS	0x02
#define COORD_BITS	0x7f

/*
** xf86SumConvert
** Convert valuators to X and Y.
*/
static Bool
xf86SumConvert(LocalDevicePtr local,
	       int first,
	       int num,
	       int v0,
	       int v1, int v2, int v3, int v4, int v5, int *x, int *y)
{
    if (first != 0 || num == 1)
	return FALSE;

	*x = v0 * screenInfo.screens[0]->width / 2430;
	*y = v1 * screenInfo.screens[0]->height / 1950;

    DBG(6, ErrorF("Adjusted coords x=%d y=%d\n", *x, *y));

    return TRUE;
}

/*
** xf86SumReverseConvert
** Convert X and Y to valuators.
*/
static Bool
xf86SumReverseConvert(LocalDevicePtr local, int x, int y, int *valuators)
{
    DigitalEdgeDevicePtr	priv = (DigitalEdgeDevicePtr) local->private;

    valuators[0] = ((x * 2430) / screenInfo.screens[0]->width) + priv->dedgeXOffset;
    valuators[1] = ((y * 1950) / screenInfo.screens[0]->height) + priv->dedgeYOffset;


    DBG(6,
	ErrorF("Adjusted valuators v0=%d v1=%d\n", valuators[0],
	       valuators[1]));

    return TRUE;
}

/*
** xf86SumReadInput
** Reads from the DigitalEdge and posts any new events to the server.
*/
static void xf86SumReadInput(LocalDevicePtr local)
{
    DigitalEdgeDevicePtr priv = (DigitalEdgeDevicePtr) local->private;
    int len, loop;
    int is_absolute;
    int x, y, push, barrel, prox, pressure;
    DeviceIntPtr device;
    unsigned char buffer[BUFFER_SIZE];

    DBG(7, ErrorF("xf86SumReadInput BEGIN device=%s fd=%d\n",
		  priv->dedgeDevice, local->fd));

    SYSCALL(len = read(local->fd, buffer, sizeof(buffer)));

    if (len <= 0) {
	Error("error reading DigitalEdge device");
	return;
    }

    for (loop = 0; loop < len; loop++) {

/* Format of 5 bytes data packet for DigitalEdge Tablets
       Byte 1
       bit 7  Phasing bit always 1
       bit 6  Proximity bit
       bit 5  Tablet ID
       bit 4  X sign (Always 1 for absolute)
       bit 3  Y sign (Always 1 for absolute)
       bit 2-0 Button status  

       Byte 2
       bit 7  Always 0
       bits 6-0 = X6 - X0

       Byte 3 (Absolute mode only)
       bit 7  Always 0
       bits 6-0 = X13 - X7

       Byte 4
       bit 7  Always 0
       bits 6-0 = Y6 - Y0

       Byte 5 (Absolute mode only)
       bit 7  Always 0
       bits 6-0 = Y13 - Y7
*/

	if ((priv->dedgeIndex == 0) && !(buffer[loop] & PHASING_BIT)) {	/* magic bit is not OK */
	    DBG(6,
		ErrorF("xf86SumReadInput bad magic number 0x%x\n",
		       buffer[loop]));;
	    continue;
	}

	priv->dedgeData[priv->dedgeIndex++] = buffer[loop];

	if (priv->dedgeIndex == 7) {
/* the packet is OK */
/* reset char count for next read */
	    priv->dedgeIndex = 0;

	    if (priv->flags & ABSOLUTE_FLAG) {
		x = (int) priv->dedgeData[1] + ((int) priv->dedgeData[2] << 7);
		y = 1950 - ((int) priv->dedgeData[3] + ((int) priv->dedgeData[4] << 7));
	    } else {
		x =
		    priv->dedgeData[0] & XSIGN_BIT ? priv->
		    dedgeData[1] : -priv->dedgeData[1];
		y =
		    priv->dedgeData[0] & YSIGN_BIT ? priv->
		    dedgeData[2] : -priv->dedgeData[2];
	    }
	    prox = (priv->dedgeData[0] & PROXIMITY_BIT) ? 1 : 0;

	    pressure = priv->dedgeData[6] + (priv->dedgeData[5] >> 4) * 128;
		push = pressure > priv->dedgeClickThresh?1:0;
		if ((priv->dedgeOldPressure) < priv->dedgeClickThresh && pressure == 1022) {
			push = 0;
		} else {
			priv->dedgeOldPressure = pressure;
		}
		if (priv->dedgeData[0] & BUTTON_BITS) {
			barrel = 1;
		} else {
			barrel = 0;
		}

	    device = local->dev;

	    DBG(6, ErrorF("prox=%s\tx=%d\ty=%d\tbarrel=%d\tpressure=%d\n",
			  prox ? "true" : "false", x, y, barrel,
			  pressure));

	    is_absolute = (priv->flags & ABSOLUTE_FLAG);

/* coordonates are ready we can send events */
	    if (prox) {
		if (!(priv->dedgeOldProximity))
		    xf86PostProximityEvent(device, 1, 0, 3, x, y, pressure);

		if (
		    (is_absolute
		     && ((priv->dedgeOldX != x) || (priv->dedgeOldY != y)))
		    || (!is_absolute && (x || y))) {
		    if (is_absolute || priv->dedgeOldProximity) {
			xf86PostMotionEvent(device, is_absolute, 0, 3, x,
					    y, pressure);
		    }
		}
		if (priv->dedgeOldPush != push) {
		    int delta;

		    delta = push - priv->dedgeOldPush;

		    if (priv->dedgeOldPush != push) {
			DBG(6,
			    ErrorF("xf86SumReadInput push delta=%d\n", delta)); 
			xf86PostButtonEvent(device, is_absolute, 1,
					    (delta > 0), 0, 3, x, y, pressure);
		    }
		}

		if (priv->dedgeOldBarrel != barrel) {
		    int delta;

		    delta = barrel - priv->dedgeOldBarrel;

		    if (priv->dedgeOldBarrel != barrel) {
			DBG(6,
			    ErrorF("xf86SumReadInput barrel delta=%d\n", delta)); 
			xf86PostButtonEvent(device, is_absolute, 2,
					    (delta > 0), 0, 3, x, y, pressure);
		    }
		}

		priv->dedgeOldPush = push;
		priv->dedgeOldBarrel = barrel;
		priv->dedgeOldX = x;
		priv->dedgeOldY = y;
		priv->dedgeOldProximity = prox;

	    } else {		/* !PROXIMITY */
/* Any changes in buttons are ignored when !proximity */
		if (priv->dedgeOldProximity)
		    xf86PostProximityEvent(device, 0, 0, 3, x, y, pressure);
		priv->dedgeOldProximity = 0;
	    }
	}
		}
		DBG(7, ErrorF("xf86Sum(priv->dedgeData[0] & BUTTON_BITS)iReadInput END   device=%p priv=%p\n",
		  (void *)local->dev, (void *)priv));
}

/*
** xf86SumControlProc
** It really does do something.  Honest!
*/
static void xf86SumControlProc(DeviceIntPtr device, PtrCtrl * ctrl)
{
    DBG(2, ErrorF("xf86SumControlProc\n"));
}

#if 0
/*
** xf86SumWriteAndRead
** Write data, and get the response.
*/
static char *xf86SumWriteAndRead(int fd, char *data, char *buffer, int len,
				 int cr_term)
{
    int err, numread = 0;

    SYSCALL(err = write(fd, data, strlen(data)));
    if (err == -1) {
	Error("DigitalEdge write");
	return NULL;
    }
    while (numread < len) {
	err = xf86WaitForInput(fd, 1000);
	if (err == -1) {
	    Error("DigitalEdge select");
	    return NULL;
	}
	if (!err) {
	    ErrorF
		("Timeout while reading DigitalEdge tablet. No tablet connected ???\n");
	    return NULL;
	}

	SYSCALL(err = read(fd, buffer + numread++, 1));
	if (err == -1) {
	    Error("DigitalEdge read");
	    return NULL;
	}
	if (!err) {
	    --numread;
	    break;
	}
	if (cr_term && buffer[numread - 1] == '\r') {
	    buffer[numread - 1] = 0;
	    break;
	}
    }
    buffer[numread] = 0;
    return buffer;
}
#endif

/*
** xf86SumOpen
** Open and initialize the tablet, as well as probe for any needed data.
*/
static Bool xf86SumOpen(LocalDevicePtr local)
{
    char buffer[256];
    int err, idx;
    DigitalEdgeDevicePtr priv = (DigitalEdgeDevicePtr) local->private;

    DBG(1, ErrorF("opening %s\n", priv->dedgeDevice));

    local->fd = xf86OpenSerial(local->options);
    if (local->fd == -1) {
	Error(priv->dedgeDevice);
	return !Success;
    }
    DBG(2, ErrorF("%s opened as fd %d\n", priv->dedgeDevice, local->fd));

    DBG(1, ErrorF("initializing DigitalEdge tablet\n"));

/* Send reset (NULL) to the tablet */
    SYSCALL(err = write(local->fd, "", 1));
    if (err == -1) {
	Error("DigitalEdge write");
	return !Success;
    }

/* wait 200 mSecs, just in case */
    err = xf86WaitForInput(-1, 200);
    if (err == -1) {
	Error("DigitalEdge select");
	return !Success;
    }

/* Put it in prompt mode so it doens't say anything before we're ready */
    SYSCALL(err =
	    write(local->fd, SS_PROMPT_MODE, strlen(SS_PROMPT_MODE)));
    if (err == -1) {
	Error("DigitalEdge write");
	return !Success;
    }
/* Clear any pending input */
    xf86FlushInput(local->fd);

    if (priv->dedgeXOffset > 0 && priv->dedgeYOffset > 0) {
	if (priv->dedgeXSize * 50 < priv->dedgeMaxX - priv->dedgeXOffset &&
	    priv->dedgeYSize * 50 < priv->dedgeMaxY - priv->dedgeYOffset) {
	    priv->dedgeXOffset *= 50;
	    priv->dedgeYOffset *= 50;
	} else {
	    xf86Msg(X_PROBED,
		    "%s: DigitalEdge offset sets active area off tablet, "
		   "centering\n", local->name);
	    priv->dedgeXOffset = (priv->dedgeMaxX - priv->dedgeXSize) / 2;
	    priv->dedgeYOffset = (priv->dedgeMaxY - priv->dedgeYSize) / 2;
	}
    } else {
	priv->dedgeXOffset = (priv->dedgeMaxX - priv->dedgeXSize) / 2;
	priv->dedgeYOffset = (priv->dedgeMaxY - priv->dedgeYSize) / 2;
    }

    if (priv->dedgeInc > 95)
	priv->dedgeInc = 95;
    if (priv->dedgeInc < 1) {
/* Make a guess as to the best increment value given video mode */
	if (priv->dedgeXSize / screenInfo.screens[0]->width <
	    priv->dedgeYSize / screenInfo.screens[0]->height)
	    priv->dedgeInc = priv->dedgeXSize / screenInfo.screens[0]->width;
	else
	    priv->dedgeInc = priv->dedgeYSize / screenInfo.screens[0]->height;
	if (priv->dedgeInc < 1)
	    priv->dedgeInc = 1;
	xf86Msg(X_PROBED, "%s: Using increment value of %d\n", local->name,
		   priv->dedgeInc);
    }

/* Sets up the tablet mode to increment, stream, and such */
    for (idx = 0; ss_initstr[idx]; idx++) {
	buffer[idx] = ss_initstr[idx];
    }
    buffer[idx++] = SS_INCREMENT;
    buffer[idx++] = 32 + priv->dedgeInc;
    buffer[idx++] =
	(priv->flags & ABSOLUTE_FLAG) ? SS_ABSOLUTE : SS_RELATIVE;
    buffer[idx] = 0;

    SYSCALL(err = write(local->fd, buffer, idx));
    if (err == -1) {
	Error("DigitalEdge write");
	return !Success;
    }

    if (err <= 0) {
	SYSCALL(close(local->fd));
	return !Success;
    }

	if (priv->dedgeClickThresh <= 0) {
		/* Make up a value */
		priv->dedgeClickThresh = 700;
	}

    return Success;
}

/*
** xf86SumOpenDevice
** Opens and initializes the device driver stuff or dedgepthin.
*/
static int xf86SumOpenDevice(DeviceIntPtr pSum)
{
    LocalDevicePtr local = (LocalDevicePtr) pSum->public.devicePrivate;
    DigitalEdgeDevicePtr priv = (DigitalEdgeDevicePtr) PRIVATE(pSum);

    if (xf86SumOpen(local) != Success) {
	if (local->fd >= 0) {
	    SYSCALL(close(local->fd));
	}
	local->fd = -1;
    }

/* Set the real values */
    InitValuatorAxisStruct(pSum, 0, 0,	/* min val */
			   2430,	/* max val */
			   500,	/* resolution */
			   0,	/* min_res */
			   500);	/* max_res */
    InitValuatorAxisStruct(pSum, 1, 0,	/* min val */
			   1950,	/* max val */
			   500,	/* resolution */
			   0,	/* min_res */
			   500);	/* max_res */
    InitValuatorAxisStruct(pSum, 2, priv->dedgeClickThresh,	/* min val */
			   1022,	/* max val */
			   500,	/* resolution */
			   0,	/* min_res */
			   500);	/* max_res */
    return (local->fd != -1);
}

/*
** xf86SumProc
** Handle requests to do stuff to the driver.
*/
static int xf86SumProc(DeviceIntPtr pSum, int what)
{
    CARD8 map[25];
    int nbaxes;
    int nbbuttons;
    int loop;
    LocalDevicePtr local = (LocalDevicePtr) pSum->public.devicePrivate;
    DigitalEdgeDevicePtr priv = (DigitalEdgeDevicePtr) PRIVATE(pSum);

    DBG(2,
	ErrorF("BEGIN xf86SumProc dev=%p priv=%p what=%d\n", (void *)pSum,
	       (void *)priv, what));

    switch (what) {
    case DEVICE_INIT:
	DBG(1, ErrorF("xf86SumProc pSum=%p what=INIT\n", (void *)pSum));

	nbaxes = 3;		/* X, Y, pressure */
	nbbuttons = (priv->flags & STYLUS_FLAG) ? 2 : 4;

	for (loop = 1; loop <= nbbuttons; loop++)
	    map[loop] = loop;

	if (InitButtonClassDeviceStruct(pSum, nbbuttons, map) == FALSE) {
	    ErrorF("unable to allocate Button class device\n");
	    return !Success;
	}

	if (InitFocusClassDeviceStruct(pSum) == FALSE) {
	    ErrorF("unable to init Focus class device\n");
	    return !Success;
	}

	if (InitPtrFeedbackClassDeviceStruct(pSum, xf86SumControlProc) ==
	    FALSE) {
	    ErrorF("unable to init ptr feedback\n");
	    return !Success;
	}

	if (InitProximityClassDeviceStruct(pSum) == FALSE) {
	    ErrorF("unable to init proximity class device\n");
	    return !Success;
	}

	if (InitValuatorClassDeviceStruct(pSum,
					  nbaxes,
					  xf86GetMotionEvents,
					  local->history_size,
					  (priv->flags & ABSOLUTE_FLAG) ?
					  Absolute : Relative) == FALSE) {
	    ErrorF("unable to allocate Valuator class device\n");
	    return !Success;
	}
/* allocate the motion history buffer if needed */
	xf86MotionHistoryAllocate(local);

/* open the device to gather informations */
	xf86SumOpenDevice(pSum);
	break;

    case DEVICE_ON:
	DBG(1, ErrorF("xf86SumProc pSum=%p what=ON\n", (void *)pSum));

	if ((local->fd < 0) && (!xf86SumOpenDevice(pSum))) {
	    return !Success;
	}
	SYSCALL(write(local->fd, SS_PROMPT, strlen(SS_PROMPT)));
	    xf86AddEnabledDevice(local);
	pSum->public.on = TRUE;
	break;

    case DEVICE_OFF:
	DBG(1, ErrorF("xf86SumProc  pSum=%p what=%s\n", (void *)pSum,
		      (what == DEVICE_CLOSE) ? "CLOSE" : "OFF"));
	if (local->fd >= 0)
		    xf86RemoveEnabledDevice(local);
	pSum->public.on = FALSE;
	break;

    case DEVICE_CLOSE:
	DBG(1, ErrorF("xf86SumProc  pSum=%p what=%s\n", (void *)pSum,
		      (what == DEVICE_CLOSE) ? "CLOSE" : "OFF"));
	SYSCALL(close(local->fd));
	local->fd = -1;
	break;

    default:
	ErrorF("unsupported mode=%d\n", what);
	return !Success;
    }
    DBG(2, ErrorF("END   xf86SumProc Success what=%d dev=%p priv=%p\n",
		  what, (void *)pSum, (void *)priv));
    return Success;
}

/*
** xf86SumClose
** It...  Uh...  Closes the physical device?
*/
static void xf86SumClose(LocalDevicePtr local)
{
    if (local->fd >= 0) {
	SYSCALL(close(local->fd));
    }
    local->fd = -1;
}

/*
** xf86SumChangeControl
** When I figure out what it does, it will do it.
*/
static int xf86SumChangeControl(LocalDevicePtr local, xDeviceCtl * control)
{
    xDeviceResolutionCtl *res;

    res = (xDeviceResolutionCtl *) control;

    if ((control->control != DEVICE_RESOLUTION)
	|| (res->num_valuators < 1)) return (BadMatch);

    return (Success);
}

/*
** xf86SumSwitchMode
** Switches the mode.  For now just absolute or relative, hopefully
** more on the way.
*/
static int xf86SumSwitchMode(ClientPtr client, DeviceIntPtr dev, int mode)
{
    LocalDevicePtr local = (LocalDevicePtr) dev->public.devicePrivate;
    DigitalEdgeDevicePtr priv = (DigitalEdgeDevicePtr) (local->private);
    char newmode;

    DBG(3, ErrorF("xf86SumSwitchMode dev=%p mode=%d\n", (void *)dev, mode));

    switch (mode) {
    case Absolute:
	priv->flags |= ABSOLUTE_FLAG;
	newmode = SS_ABSOLUTE;
	break;

    case Relative:
	priv->flags &= ~ABSOLUTE_FLAG;
	newmode = SS_RELATIVE;
	break;

    default:
	DBG(1, ErrorF("xf86SumSwitchMode dev=%p invalid mode=%d\n",
		      (void *)dev, mode));
	return BadMatch;
    }
    SYSCALL(write(local->fd, &newmode, 1));
    return Success;
}

/*
** xf86SumAllocate
** Allocates the device structures for the DigitalEdge.
*/
static LocalDevicePtr xf86SumAllocate(void)
{
    LocalDevicePtr	local = xf86AllocateInput(dedgeDrv, 0);
    DigitalEdgeDevicePtr priv = (DigitalEdgeDevicePtr) xalloc(sizeof(DigitalEdgeDeviceRec));
#if defined (sun) && !defined(i386)
    char *dev_name = getenv("DEDGESKETCH_DEV");
#endif

    local->name = XI_NAME;
    local->type_name = "DigitalEdge Tablet";
    local->flags = 0;		/*XI86_NO_OPEN_ON_INIT; */
    local->device_control = xf86SumProc;
    local->read_input = xf86SumReadInput;
    local->control_proc = xf86SumChangeControl;
    local->close_proc = xf86SumClose;
    local->switch_mode = xf86SumSwitchMode;
    local->conversion_proc = xf86SumConvert;
    local->reverse_conversion_proc = xf86SumReverseConvert;
    local->fd = -1;
    local->atom = 0;
    local->dev = NULL;
    local->private = priv;
    local->private_flags = 0;
    local->history_size = 0;

#if defined(sun) && !defined(i386)
    if (dev_name) {
	priv->dedgeDevice = (char *) xalloc(strlen(dev_name) + 1);
	strcpy(priv->dedgeDevice, dev_name);
	ErrorF("xf86SumOpen port changed to '%s'\n", priv->dedgeDevice);
    } else {
	priv->dedgeDevice = "";
    }
#else
    priv->dedgeDevice = "";	/* device file name */
#endif
    priv->dedgeInc = -1;		/* re-transmit position on increment */
    priv->dedgeOldX = -1;		/* previous X position */
    priv->dedgeOldY = -1;		/* previous Y position */
    priv->dedgeOldProximity = 0;	/* previous proximity */
    priv->dedgeOldPush = 0;	/* previous buttons state */
    priv->dedgeOldBarrel = 0;	/* previous buttons state */
    priv->dedgeMaxX = -1;		/* max X value */
    priv->dedgeMaxY = -1;		/* max Y value */
    priv->dedgeXSize = -1;	/* active area X */
    priv->dedgeXOffset = -1;	/* active area X offset */
    priv->dedgeYSize = -1;	/* active area Y */
    priv->dedgeYOffset = -1;	/* active area U offset */
    priv->flags = 0;		/* various flags */
    priv->dedgeIndex = 0;		/* number of bytes read */

    return local;
}

/*
 * xf86SumUninit --
 *
 * called when the driver is unloaded.
 */
static void
xf86SumUninit(InputDriverPtr	drv,
	      LocalDevicePtr	local,
	      int flags)
{
    DigitalEdgeDevicePtr	priv = (DigitalEdgeDevicePtr) local->private;
    
    DBG(1, ErrorF("xf86DedgeUninit\n"));
    
    xf86SumProc(local->dev, DEVICE_OFF);
    
    xfree (priv);
    xf86DeleteInput(local, 0);    
}


/*
 * xf86SumInit --
 *
 * called when the module subsection is found in XF86Config
 */
static InputInfoPtr
xf86SumInit(InputDriverPtr	drv,
	    IDevPtr		dev,
	    int			flags)
{
    LocalDevicePtr	local = NULL;
    DigitalEdgeDevicePtr	priv = NULL;
    char		*s;

    dedgeDrv = drv;

    local = xf86SumAllocate();
    local->conf_idev = dev;

    xf86CollectInputOptions(local, default_options, NULL);   
    xf86OptionListReport( local->options );

    if (local)
	priv = (DigitalEdgeDevicePtr) local->private;

    if (!local || !priv) {
	goto SetupProc_fail;
    }
    
    local->name = dev->identifier;
    
    /* Serial Device is mandatory */
    priv->dedgeDevice = xf86FindOptionValue(local->options, "Device");

    if (!priv->dedgeDevice) {
	xf86Msg (X_ERROR, "%s: No Device specified.\n", dev->identifier);
	goto SetupProc_fail;
    }

    /* Process the common options. */
    xf86ProcessCommonOptions(local, local->options);

    /* Optional configuration */

    xf86Msg(X_CONFIG, "%s serial device is %s\n", dev->identifier,
	    priv->dedgeDevice);

    debug_level = xf86SetIntOption(local->options, "DebugLevel", 0);
    if (debug_level > 0) {
	xf86Msg(X_CONFIG, "Summa: debug level set to %d\n", debug_level);
    }



    s = xf86FindOptionValue(local->options, "Mode");

    if (s && (xf86NameCmp(s, "absolute") == 0)) {
	priv->flags = priv->flags | ABSOLUTE_FLAG;
    }
    else if (s && (xf86NameCmp(s, "relative") == 0)) {
	priv->flags = priv->flags & ~ABSOLUTE_FLAG;
    }
    else if (s) {
	xf86Msg(X_ERROR, "%s: invalid Mode (should be absolute or relative). "
		"Using default.\n", dev->identifier);
    }
    xf86Msg(X_CONFIG, "%s is in %s mode\n", local->name,
	    (priv->flags & ABSOLUTE_FLAG) ? "absolute" : "relative");	    


    s = xf86FindOptionValue(local->options, "Cursor");

    if (s && (xf86NameCmp(s, "stylus") == 0)) {
	priv->flags = priv->flags | STYLUS_FLAG;
    }
    else if (s && (xf86NameCmp(s, "puck") == 0)) {
	priv->flags = priv->flags & ~STYLUS_FLAG;
    }
    else if (s) {
	xf86Msg(X_ERROR, "%s: invalid Cursor (should be stylus or puck). "
		"Using default.\n", dev->identifier);
    }
    xf86Msg(X_CONFIG, "%s is in cursor-mode %s\n", local->name,
	    (priv->flags & STYLUS_FLAG) ? "cursor" : "puck");	    

    priv->dedgeInc = xf86SetIntOption(local->options, "increment", 0);
    if (priv->dedgeInc != 0) {
	    xf86Msg(X_CONFIG, "%s: Increment = %d\n",
		    dev->identifier, priv->dedgeInc);
    }

    priv->dedgeClickThresh = xf86SetIntOption(local->options, 
					      "clickthreshold", 0);
    if (priv->dedgeClickThresh != 0) {
	    xf86Msg(X_CONFIG, "%s: click threshold is %d\n",
		    dev->identifier, priv->dedgeClickThresh);
    }

    priv->dedgeXSize = xf86SetIntOption(local->options, "XSize", 0);
    if (priv->dedgeXSize != 0) {
	    xf86Msg(X_CONFIG, "%s: XSize = %d\n", 
		    dev->identifier, priv->dedgeXSize);
    }

    priv->dedgeYSize = xf86SetIntOption(local->options, "YSize", 0);
    if (priv->dedgeYSize != 0) {
	    xf86Msg(X_CONFIG, "%s: YSize = %d\n", 
		    dev->identifier, priv->dedgeYSize);
    }

    priv->dedgeXOffset = xf86SetIntOption(local->options, "XOffset", 0);
    if (priv->dedgeXOffset != 0) {
	    xf86Msg(X_CONFIG, "%s: XOffset = %d\n", 
		    dev->identifier, priv->dedgeXOffset);
    }

    priv->dedgeYOffset = xf86SetIntOption(local->options, "YOffset", 0);
    if (priv->dedgeYOffset != 0) {
	    xf86Msg(X_CONFIG, "%s: YOffset = %d\n", 
		    dev->identifier, priv->dedgeYOffset);
    }



    /* mark the device configured */
    local->flags |= XI86_POINTER_CAPABLE | XI86_CONFIGURED;

    /* return the LocalDevice */
    return local;

  SetupProc_fail:
    if (priv)
	xfree(priv);
    return local;
}

#ifdef XFree86LOADER
static
#endif
InputDriverRec DIGITALEDGE = {
    1,				/* driver version */
    "digitaledge",		/* driver name */
    NULL,			/* identify */
    xf86SumInit,		/* pre-init */
    xf86SumUninit,		/* un-init */
    NULL,			/* module */
    0				/* ref count */
};


/*
 ***************************************************************************
 *
 * Dynamic loading functions
 *
 ***************************************************************************
 */
#ifdef XFree86LOADER
/*
 * xf86SumUnplug --
 *
 * called when the module subsection is found in XF86Config
 */
static void
xf86SumUnplug(pointer	p)
{
}

/*
 * xf86SumPlug --
 *
 * called when the module subsection is found in XF86Config
 */
static pointer
xf86SumPlug(pointer	module,
	    pointer	options,
	    int		*errmaj,
	    int		*errmin)
{
    xf86AddInputDriver(&DIGITALEDGE, module, 0);

    return module;
}

static XF86ModuleVersionInfo xf86SumVersionRec =
{
    "digitaledge",
    MODULEVENDORSTRING,
    MODINFOSTRING1,
    MODINFOSTRING2,
    XF86_VERSION_CURRENT,
    1, 0, 0,
    ABI_CLASS_XINPUT,
    ABI_XINPUT_VERSION,
    MOD_CLASS_XINPUT,
    {0, 0, 0, 0}		/* signature, to be patched into the file by */
				/* a tool */
};

XF86ModuleData digitaledgeModuleData = {&xf86SumVersionRec,
					xf86SumPlug,
					xf86SumUnplug};

#endif /* XFree86LOADER */

/* end of xf86DigitalEdge.c */
