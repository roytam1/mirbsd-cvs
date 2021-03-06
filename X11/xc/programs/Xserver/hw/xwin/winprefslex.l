%{ # -*- C -*-
/*
 * Copyright (C) 1994-2000 The XFree86 Project, Inc. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE XFREE86 PROJECT BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of the XFree86 Project
 * shall not be used in advertising or otherwise to promote the sale, use
 * or other dealings in this Software without prior written authorization
 * from the XFree86 Project.
 *
 * Authors:     Earle F. Philhower, III
 */
/* $XFree86: xc/programs/Xserver/hw/xwin/winprefslex.l,v 1.1 2003/10/02 13:30:11 eich Exp $ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "winprefsyacc.h"

extern YYSTYPE yylval;
extern char *yytext;
extern int yyparse();

extern void ErrorF (const char* /*f*/, ...);

int yylineno;

/* Copy the parsed string, must be free()d in yacc parser */
static char *makestr(char *str)
{
  char *ptr;
  ptr = (char*)malloc (strlen(str)+1);
  if (!ptr)
    {
      ErrorF ("winMultiWindowLex:makestr() out of memory\n");
      exit (-1);
    }
  strcpy(ptr, str);
  return ptr;
}

%}

%option yylineno

%%
\#.*[\r\n]                                               { /* comment */ return NEWLINE; }
\/\/.*[\r\n]                                             { /* comment */ return NEWLINE; }
[\r\n]	                                             	 { return NEWLINE; }
[ \t]+	                                             	 { /* ignore whitespace */ }
[mM][eE][nN][uU]                                         { return MENU; }
[iI][cC][oO][nN][dD][iI][rR][eE][cC][tT][oO][rR][yY]	 { return ICONDIRECTORY; }
[dD][eE][fF][aA][uU][lL][tT][iI][cC][oO][nN]             { return DEFAULTICON; }
[iI][cC][oO][nN][sS]                              	 { return ICONS; }
[rR][oO][oO][tT][mM][eE][nN][uU]                         { return ROOTMENU; }
[dD][eE][fF][aA][uU][lL][tT][sS][yY][sS][mM][eE][nN][uU] { return DEFAULTSYSMENU; }
[sS][yY][sS][mM][eE][nN][uU]                             { return SYSMENU; }
[sS][eE][pP][aA][rR][aA][tT][oO][rR]                     { return SEPARATOR; }
[aA][tT][sS][tT][aA][rR][tT]                             { return ATSTART; }
[aA][tT][eE][nN][dD]                                     { return ATEND; }
[eE][xX][eE][cC]                                         { return EXEC; }
[aA][lL][wW][aA][yY][sS][oO][nN][tT][oO][pP]             { return ALWAYSONTOP; }
[dD][eE][bB][uU][gG]                                     { return DEBUG; }
[rR][eE][lL][oO][aA][dD]                                 { return RELOAD; }
"{"		                                         { return LB; }
"}"		                                         { return RB; }
"\""[^\"\r\n]+"\""                                       { yylval.sVal = makestr(yytext+1); \
                                                           yylval.sVal[strlen(yylval.sVal)-1] = 0; \
                                                           return STRING; }
[^ \t\r\n]+                                              { yylval.sVal = makestr(yytext); \
                                                           return STRING; }
%%

/*
 * Run-of-the mill requirement for yacc
 */
int
yywrap ()
{
  return 1;
}

/*
 * Run a file through the yacc parser
 */
void
parse_file (FILE *file)
{
  if (!file)
    return; 
  
  yylineno = 1;
  yyin = file;
  yyparse ();
}
