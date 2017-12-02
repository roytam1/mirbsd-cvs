/*
 * 	User text formatting functions
 * 	Copyright
 *		(C) 1992 Joseph H. Allen
 * 
 *	This file is part of JOE (Joe's Own Editor)
 */
#ifndef _JOE_UFORMAT_H
#define _JOE_UFORMAT_H 1

#ifdef EXTERN_CMD_C
__RCSID("$MirOS$");
#endif

int ucenter PARAMS((BW *bw));
P *pbop PARAMS((P *p));
P *peop PARAMS((P *p));
int ubop PARAMS((BW *bw));
int ueop PARAMS((BW *bw));
void wrapword PARAMS((P *p, long int indent, int french, unsigned char *indents));
int uformat PARAMS((BW *bw));
int ufmtblk PARAMS((BW *bw));

#endif
