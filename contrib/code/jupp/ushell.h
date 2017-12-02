/*
 * 	Shell-window functions
 *	Copyright (C) 1992 Joseph H. Allen
 *
 *	This file is part of JOE (Joe's Own Editor)
 */
#ifndef _JOE_USHELL_H
#define _JOE_USHELL_H 1

#ifdef EXTERN_CMD_C
__RCSID("$MirOS$");
#endif

int ubknd PARAMS((BW *bw));
int ukillpid PARAMS((BW *bw));
int urun PARAMS((BW *bw));
int ubuild PARAMS((BW *bw));

const void *getushell PARAMS((void));

#endif
