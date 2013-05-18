/* $XFree86: xc/programs/Xserver/hw/dmx/examples/dmxaddinput.c,v 1.1 2004/06/30 20:21:43 martin Exp $ */
/*
 * Copyright 2003,2004 Red Hat Inc., Durham, North Carolina.
 *
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation on the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT.  IN NO EVENT SHALL RED HAT AND/OR THEIR SUPPLIERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * Authors:
 *   Rickard E. (Rik) Faith <faith@redhat.com>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include "dmxext.h"

int main(int argc, char **argv)
{
    Display              *display = NULL;
    int                  event_base;
    int                  error_base;
    int                  major_version, minor_version, patch_version;
    int                  id = -1;
    int                  status;

    if (argc != 5) {
        printf("Usage: %s display c|b name|screen isCore\n", argv[0]);
        return -1;
    }

    if (!(display = XOpenDisplay(argv[1]))) {
        printf("Cannot open display %s\n", argv[1]);
        return -1;
    }

    if (!DMXQueryExtension(display, &event_base, &error_base)) {
        printf("DMX extension not present\n");
        return -1;
    }
    printf("DMX extension present: event_base = %d, error_base = %d\n",
           event_base, error_base);

    if (!DMXQueryVersion(display,
                         &major_version, &minor_version, &patch_version)) {
        printf("Could not get extension version\n");
        return -1;
    }
    printf("Extension version: %d.%d patch %d\n",
           major_version, minor_version, patch_version);

    if (argv[2][0] == 'c') {
        status = DMXAddConsoleInput(display, argv[3], atoi(argv[4]), &id);
    } else {
        status = DMXAddBackendInput(display, atoi(argv[3]), atoi(argv[4]),&id);
    }

    printf("status = %d, id = %d\n", status, id);

    XCloseDisplay(display);
    return 0;
}
