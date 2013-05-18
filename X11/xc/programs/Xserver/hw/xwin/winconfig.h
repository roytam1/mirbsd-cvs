/*
 *Copyright (C) 1994-2000 The XFree86 Project, Inc. All Rights Reserved.
 *
 *Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 *"Software"), to deal in the Software without restriction, including
 *without limitation the rights to use, copy, modify, merge, publish,
 *distribute, sublicense, and/or sell copies of the Software, and to
 *permit persons to whom the Software is furnished to do so, subject to
 *the following conditions:
 *
 *The above copyright notice and this permission notice shall be
 *included in all copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *NONINFRINGEMENT. IN NO EVENT SHALL THE XFREE86 PROJECT BE LIABLE FOR
 *ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 *CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *Except as contained in this notice, the name of the XFree86 Project
 *shall not be used in advertising or otherwise to promote the sale, use
 *or other dealings in this Software without prior written authorization
 *from the XFree86 Project.
 *
 * Authors: Alexander Gottwald	
 */
/* $XFree86: xc/programs/Xserver/hw/xwin/winconfig.h,v 1.1 2002/10/17 08:18:22 alanh Exp $ */
#ifndef __WIN_CONFIG_H__
#define __WIN_CONFIG_H__

#include "win.h"
#include "../xfree86/parser/xf86Parser.h"


/* These are taken from hw/xfree86/common/xf86str.h */

typedef struct
{
  CARD32 red, green, blue;
}
rgb;


typedef struct
{
  float red, green, blue;
}
Gamma;


typedef struct
{
  char *identifier;
  char *vendor;
  char *board;
  char *chipset;
  char *ramdac;
  char *driver;
  struct _confscreenrec *myScreenSection;
  Bool claimed;
  Bool active;
  Bool inUse;
  int videoRam;
  int textClockFreq;
  pointer options;
  int screen;			/* For multi-CRTC cards */
}
GDevRec, *GDevPtr;


typedef struct
{
  char *identifier;
  char *driver;
  pointer commonOptions;
  pointer extraOptions;
}
IDevRec, *IDevPtr;


typedef struct
{
  int frameX0;
  int frameY0;
  int virtualX;
  int virtualY;
  int depth;
  int fbbpp;
  rgb weight;
  rgb blackColour;
  rgb whiteColour;
  int defaultVisual;
  char **modes;
  pointer options;
}
DispRec, *DispPtr;


typedef struct _confxvportrec
{
  char *identifier;
  pointer options;
}
confXvPortRec, *confXvPortPtr;


typedef struct _confxvadaptrec
{
  char *identifier;
  int numports;
  confXvPortPtr ports;
  pointer options;
}
confXvAdaptorRec, *confXvAdaptorPtr;


typedef struct _confscreenrec
{
  char *id;
  int screennum;
  int defaultdepth;
  int defaultbpp;
  int defaultfbbpp;
  GDevPtr device;
  int numdisplays;
  DispPtr displays;
  int numxvadaptors;
  confXvAdaptorPtr xvadaptors;
  pointer options;
}
confScreenRec, *confScreenPtr;


typedef enum
{
  PosObsolete = -1,
  PosAbsolute = 0,
  PosRightOf,
  PosLeftOf,
  PosAbove,
  PosBelow,
  PosRelative
}
PositionType;


typedef struct _screenlayoutrec
{
  confScreenPtr screen;
  char *topname;
  confScreenPtr top;
  char *bottomname;
  confScreenPtr bottom;
  char *leftname;
  confScreenPtr left;
  char *rightname;
  confScreenPtr right;
  PositionType where;
  int x;
  int y;
  char *refname;
  confScreenPtr refscreen;
}
screenLayoutRec, *screenLayoutPtr;


typedef struct _serverlayoutrec
{
  char *id;
  screenLayoutPtr screens;
  GDevPtr inactives;
  IDevPtr inputs;
  pointer options;
}
serverLayoutRec, *serverLayoutPtr;


/*
 * winconfig.c
 */

typedef struct
{
  /* Files */
  char *configFile;
  char *fontPath;
  char *rgbPath;
  /* input devices - keyboard */
  char *keyboard;
#ifdef XKB
  Bool noXkbExtension;
  char *xkbMap;
#endif
  /* layout */
  char *screenname;
  /* mouse settings */
  char *mouse;
  Bool emulate3buttons;
  long emulate3timeout;
}
WinCmdlineRec, *WinCmdlinePtr;


extern WinCmdlineRec g_cmdline;

extern XF86ConfigPtr g_xf86configptr;
extern serverLayoutRec g_winConfigLayout;


/*
 * Function prototypes
 */

Bool winReadConfigfile (void);
Bool winConfigFiles (void);
Bool winConfigOptions (void);
Bool winConfigScreens (void);
Bool winConfigKeyboard (DeviceIntPtr pDevice);
Bool winConfigMouse (DeviceIntPtr pDevice);


typedef struct
{
  double freq;
  int units;
}
OptFrequency;


typedef union
{
  unsigned long num;
  char *str;
  double realnum;
  Bool bool;
  OptFrequency freq;
}
ValueUnion;


typedef enum
{
  OPTV_NONE = 0,
  OPTV_INTEGER,
  OPTV_STRING,			/* a non-empty string */
  OPTV_ANYSTR,			/* Any string, including an empty one */
  OPTV_REAL,
  OPTV_BOOLEAN,
  OPTV_FREQ
}
OptionValueType;


typedef enum
{
  OPTUNITS_HZ = 1,
  OPTUNITS_KHZ,
  OPTUNITS_MHZ
}
OptFreqUnits;


typedef struct
{
  int token;
  const char *name;
  OptionValueType type;
  ValueUnion value;
  Bool found;
}
OptionInfoRec, *OptionInfoPtr;


/*
 * Function prototypes
 */

char *winSetStrOption (pointer optlist, const char *name, char *deflt);
int winSetBoolOption (pointer optlist, const char *name, int deflt);
int winSetIntOption (pointer optlist, const char *name, int deflt);
double winSetRealOption (pointer optlist, const char *name, double deflt);

XF86OptionPtr winFindOption (XF86OptionPtr list, const char *name);
char *winFindOptionValue (XF86OptionPtr list, const char *name);
int winNameCompare (const char *s1, const char *s2);
char *winNormalizeName (const char *s);


typedef struct
{
  struct
  {
    long leds;
    long delay;
    long rate;
  }
  keyboard;
#ifdef XKB
  struct
  {
    Bool disable;
    char *rules;
    char *model;
    char *layout;
    char *variant;
    char *options;
    char *initialMap;
    char *keymap;
    char *types;
    char *compat;
    char *keycodes;
    char *symbols;
    char *geometry;
  }
  xkb;
#endif
  struct
  {
    Bool emulate3Buttons;
    long emulate3Timeout;
  }
  pointer;
}
winInfoRec, *winInfoPtr;


extern winInfoRec g_winInfo;

#endif
