/* Text editing windows
   Copyright (C) 1992 Joseph H. Allen

This file is part of JOE (Joe's Own Editor)

JOE is free software; you can redistribute it and/or modify it under the 
terms of the GNU General Public License as published by the Free Software 
Foundation; either version 1, or (at your option) any later version.  

JOE is distributed in the hope that it will be useful, but WITHOUT ANY 
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more 
details.  

You should have received a copy of the GNU General Public License along with 
JOE; see the file COPYING.  If not, write to the Free Software Foundation, 
675 Mass Ave, Cambridge, MA 02139, USA.  */ 

#ifndef _Itw
#define _Itw 1

#include "config.h"
#include "main.h"
#include "bw.h"

typedef struct tw TW;

struct tw
 {
 /* Status line info */
 char *stalin;
 char *staright;
 int staon;				/* Set if status line was on */
 long prevline;				/* Previous cursor line number */
 int changed;				/* Previous changed value */
 };

#define TYPETW 0x100

/* BW *wmktw(SCREEN *t,B *b)
 */
BW *wmktw();

int usplitw();
int uduptw();
int utw0();
int utw1();
int uabortbuf();
int uabort();
void setline();

extern int staen;

#endif
