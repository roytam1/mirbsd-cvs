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
 * Authors:	Harold L Hunt II
 */
/* $XFree86: xc/programs/Xserver/hw/xwin/winclipboardtextconv.c,v 1.2 2003/07/29 21:25:16 dawes Exp $ */

#include "win.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * Convert \r\n to \n
 *
 * NOTE: This was heavily inspired by, if not down right stolen from,
 *       Cygwin's winsup/cygwin/fhandler.cc/fhandler_base::read ()
 */

void
winClipboardDOStoUNIX (char *pszSrc, int iLength)
{
  char			*pszDest = pszSrc;
  char			*pszEnd = pszSrc + iLength;

  /* Loop until the last character */
  while (pszSrc < pszEnd)
    {
      /* Copy the current source character to current destination character */
      *pszDest = *pszSrc;

      /* Advance to the next source character */
      pszSrc++;

      /* Don't advance the destination character if we need to drop an \r */
      if (*pszDest != '\r' || *pszSrc != '\n')
	pszDest++;
    }

  /* Move the terminating null */
  *pszDest = '\0';
}


/*
 * Convert \n to \r\n
 */

void
winClipboardUNIXtoDOS (unsigned char **ppszData, int iLength)
{
  int			iNewlineCount = 0;
  unsigned char		*pszSrc = *ppszData;
  unsigned char		*pszEnd = pszSrc + iLength;
  unsigned char		*pszDest = NULL, *pszDestBegin = NULL;

#if 0
  ErrorF ("UNIXtoDOS () - Original data:\n%s\n", *ppszData);
#endif

  /* Count \n characters without leading \r */
  while (pszSrc < pszEnd)
    {
      /* Skip ahead two character if found set of \r\n */
      if (*pszSrc == '\r' && pszSrc + 1 < pszEnd && *(pszSrc + 1) == '\n')
	{
	  pszSrc += 2;
	  continue;
	} 

      /* Increment the count if found naked \n */
      if (*pszSrc == '\n')
	{
	  iNewlineCount++;
	}

      pszSrc++;
    }
  
  /* Return if no naked \n's */
  if (iNewlineCount == 0)
    return;

  /* Allocate a new string */
  pszDestBegin = pszDest = malloc (iLength + iNewlineCount + 1);

  /* Set source pointer to beginning of data string */
  pszSrc = *ppszData;

  /* Loop through all characters in source string */
  while (pszSrc < pszEnd)
    {
      /* Copy line endings that are already valid */
      if (*pszSrc == '\r' && pszSrc + 1 < pszEnd && *(pszSrc + 1) == '\n')
	{
	  *pszDest = *pszSrc;
	  *(pszDest + 1) = *(pszSrc + 1);
	  pszDest += 2;
	  pszSrc += 2;
	  continue;
	}

      /* Add \r to naked \n's */
      if (*pszSrc == '\n')
	{
	  *pszDest = '\r';
	  *(pszDest + 1) = *pszSrc;
	  pszDest += 2;
	  pszSrc += 1;
	  continue;
	}

      /* Copy normal characters */
      *pszDest = *pszSrc;
      pszSrc++;
      pszDest++;
    }

  /* Put terminating null at end of new string */
  *pszDest = '\0';

  /* Swap string pointers */
  free (*ppszData);
  *ppszData = pszDestBegin;

#if 0
  ErrorF ("UNIXtoDOS () - Final string:\n%s\n", pszDestBegin);
#endif
}
