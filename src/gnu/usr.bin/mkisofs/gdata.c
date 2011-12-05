/* @(#)gdata.c	1.1 01/01/21 Copyright 2001 J. Schilling */
#include <sys/cdefs.h>
__SCCSID("@(#)gdata.c	1.1 01/01/21 Copyright 2001 J. Schilling");
__RCSID("$MirOS$");

#include <mconfig.h>
#include "internal.h"

char *hfs_error = "no error";	/* static error string */
hfsvol *hfs_mounts;		/* linked list of mounted volumes */
hfsvol *hfs_curvol;		/* current volume */
