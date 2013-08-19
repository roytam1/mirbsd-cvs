/* $MirOS: contrib/code/jupp/ushell.h,v 1.2 2008/05/13 13:08:30 tg Exp $ */
/*
 * 	Shell-window functions
 *	Copyright (C) 1992 Joseph H. Allen
 *
 *	This file is part of JOE (Joe's Own Editor)
 */
#ifndef _JOE_USHELL_H
#define _JOE_USHELL_H 1

#include "config.h"
#include "types.h"

int ubknd PARAMS((BW *bw));
int ukillpid PARAMS((BW *bw));
int urun PARAMS((BW *bw));
int ubuild PARAMS((BW *bw));

const void *getushell PARAMS((void));

#endif