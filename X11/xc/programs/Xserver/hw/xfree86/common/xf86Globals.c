/* $XFree86: xc/programs/Xserver/hw/xfree86/common/xf86Globals.c,v 1.45 2005/03/04 21:59:13 tsi Exp $ */

/*
 * Copyright (c) 1997-2005 by The XFree86 Project, Inc.
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

/*
 * Copyright � 2004, 2005 X-Oz Technologies.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions, and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 * 
 *  3. The end-user documentation included with the redistribution,
 *     if any, must include the following acknowledgment: "This product
 *     includes software developed by X-Oz Technologies
 *     (http://www.x-oz.com/)."  Alternately, this acknowledgment may
 *     appear in the software itself, if and wherever such third-party
 *     acknowledgments normally appear.
 *
 *  4. Except as contained in this notice, the name of X-Oz
 *     Technologies shall not be used in advertising or otherwise to
 *     promote the sale, use or other dealings in this Software without
 *     prior written authorization from X-Oz Technologies.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL X-OZ TECHNOLOGIES OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

/*
 * This file contains all the XFree86 global variables.
 */

#include "X.h"
#include "os.h"
#include "windowstr.h"
#include "propertyst.h"
#include "xf86.h"
#include "xf86Priv.h"
#include "xf86Parser.h"
#include "xf86Xinput.h"
#include "xf86InPriv.h"

/* Globals that video drivers may access */

int xf86ScreenIndex = -1;	/* Index of ScrnInfo in pScreen.devPrivates */
int xf86CreateRootWindowIndex = -1;	/* Index into pScreen.devPrivates */
ScrnInfoPtr *xf86Screens = NULL;	/* List of ScrnInfos */
int xf86PixmapIndex = 0;
const unsigned char byte_reversed[256] =
{
    0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
    0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
    0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
    0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
    0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
    0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
    0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
    0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
    0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
    0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
    0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
    0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
    0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
    0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
    0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
    0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
    0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
    0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
    0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
    0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
    0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
    0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
    0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
    0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
    0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
    0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
    0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
    0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
    0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
    0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
    0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
    0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
};

/* Globals that input drivers may access */
InputInfoPtr xf86InputDevs = NULL;


/* Globals that video drivers may not access */

xf86InfoRec xf86Info = {
	NULL,		/* pKeyboard */
	NULL,		/* kbdProc */
	NULL,		/* kbdEvents */
	-1,		/* consoleFd */
	-1,		/* kbdFd */
	-1,		/* vtno */
	-1,		/* kbdType */
	-1,		/* kbdRate */
	-1, 		/* kbdDelay */
	-1,		/* bell_pitch */
	-1,		/* bell_duration */
	TRUE,		/* autoRepeat */
	0,		/* leds */
	0,		/* xleds */
	NULL,		/* vtinit */
	0,		/* scanPrefix */
	FALSE,		/* capsLock */
	FALSE,		/* numLock */
	FALSE,		/* scrollLock */
	FALSE,		/* modeSwitchLock */
	FALSE,		/* composeLock */
	FALSE,		/* vtSysreq */
	SKWhenNeeded,	/* ddxSpecialKeys */
	FALSE,		/* ActionKeyBindingsSet */
#if defined(SVR4) && defined(i386)
	FALSE,		/* panix106 */
#endif
#if defined(__OpenBSD__) || defined(__NetBSD__)
	0,		/* wskbdType */
#endif
	NULL,		/* pMouse */
#ifdef XINPUT
	NULL,		/* mouseLocal */
#endif
	-1,		/* lastEventTime */
	FALSE,		/* vtRequestsPending */
	FALSE,		/* inputPending */
	FALSE,		/* dontVTSwitch */
	FALSE,		/* dontZap */
	FALSE,		/* dontZoom */
	FALSE,		/* notrapSignals */
	FALSE,		/* caughtSignal */
	FALSE,		/* sharedMonitor */
	NULL,		/* currentScreen */
#ifdef CSRG_BASED
	-1,		/* screenFd */
	-1,		/* consType */
#endif
#ifdef XKB
	NULL,		/* xkbkeymap */
	NULL,		/* xkbkeycodes */
	NULL,		/* xkbtypes */
	NULL,		/* xkbcompat */
	NULL,		/* xkbsymbols */
	NULL,		/* xkbgeometry */
	FALSE,		/* xkbcomponents_specified */
	NULL,		/* xkbrules */
	NULL,		/* xkbmodel */
	NULL,		/* xkblayout */
	NULL,		/* xkbvariant */
	NULL,		/* xkboptions */
#endif
	FALSE,		/* allowMouseOpenFail */
	TRUE,		/* vidModeEnabled */
	FALSE,		/* vidModeAllowNonLocal */
	TRUE,		/* miscModInDevEnabled */
	FALSE,		/* miscModInDevAllowNonLocal */
	PCIProbe1,	/* pciFlags */
	Pix24DontCare,	/* pixmap24 */
	X_DEFAULT,	/* pix24From */
#if defined(i386) || defined(__i386__)
	FALSE,		/* pc98 */
#endif
	TRUE,		/* pmFlag */
	0,		/* estimateSizesAggressively */
	FALSE,		/* kbdCustomKeycodes */
	FALSE,		/* disableRandR */
	X_DEFAULT,	/* randRFrom */
	{ FALSE, NULL, FALSE, FALSE, },	/* grabInfo */
	NULL,		/* config */
	NULL,		/* serverLayout */
	NULL,		/* configFiles */
	NULL,		/* configFlags */
	NULL		/* configModules */
};
const char *xf86ConfigFile = NULL;
Bool xf86LogFileWasOpened = FALSE;
confDRIRec xf86ConfigDRI = {0, };
confFilesRec xf86FileDefaults = {
	NULL, "<defaults>",
	DEFAULT_LOGPREFIX, X_DEFAULT,
	NULL, X_NONE,
	DEFAULT_MODULE_PATH, X_DEFAULT,
	NULL, X_NONE,
	NULL, X_NONE,
	NULL
};
confFilesRec xf86FileCmdline = {
	NULL, "<commandline>",
	NULL, X_NONE,
	NULL, X_NONE,
	NULL, X_NONE,
	NULL, X_NONE,
	NULL, X_NONE,
	NULL
};
confFilesPtr xf86FilePaths = NULL;
Bool xf86Resetting = FALSE;
Bool xf86Initialising = FALSE;
Bool xf86ProbeFailed = FALSE;
Bool xf86DoProbe = FALSE;
Bool xf86DoConfigure = FALSE;
#ifdef XFree86LOADER
DriverPtr *xf86DriverList = NULL;
int xf86NumDrivers = 0;
InputDriverPtr *xf86InputDriverList = NULL;
int xf86NumInputDrivers = 0;
ModuleInfoPtr *xf86ModuleInfoList = NULL;
int xf86NumModuleInfos = 0;
#endif
int xf86NumScreens = 0;

const char *xf86VisualNames[] = {
	"StaticGray",
	"GrayScale",
	"StaticColor",
	"PseudoColor",
	"TrueColor",
	"DirectColor"
};

/* Parameters set only from the command line */
char *xf86ServerName = "no-name";
Bool xf86sFlag = FALSE;
Bool xf86bsEnableFlag = FALSE;
Bool xf86bsDisableFlag = FALSE;
Bool xf86silkenMouseDisableFlag = FALSE;
char *xf86LayoutName = NULL;
char *xf86ScreenName = NULL;
char *xf86PointerName = NULL;
char *xf86KeyboardName = NULL;
Bool xf86ProbeOnly = FALSE;
int xf86Verbose = DEFAULT_VERBOSE;
int xf86LogVerbose = DEFAULT_LOG_VERBOSE;
int xf86FbBpp = -1;
Pix24Flags xf86Pix24 = Pix24DontCare;
int xf86Depth = -1;
rgb xf86Weight = {0, 0, 0};
Bool xf86FlipPixels = FALSE;
Gamma xf86Gamma = {0.0, 0.0, 0.0};
Bool xf86ShowUnresolved = DEFAULT_UNRESOLVED;
Bool xf86BestRefresh = DEFAULT_BEST_REFRESH;
Bool xf86AllowMouseOpenFail = FALSE;
#ifdef XF86VIDMODE
Bool xf86VidModeDisabled = FALSE;
Bool xf86VidModeAllowNonLocal = FALSE;
#endif
#ifdef XF86MISC
Bool xf86MiscModInDevDisabled = FALSE;
Bool xf86MiscModInDevAllowNonLocal = FALSE;
#endif
RootWinPropPtr *xf86RegisteredPropertiesTable = NULL;
Bool xf86inSuspend = FALSE;

#ifdef DLOPEN_HACK
/*
 * This stuff is a hack to allow dlopen() modules to work.  It is intended
 * only to be used when using dlopen() modules for debugging purposes.
 */
#endif
