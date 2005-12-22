%option nounput
%{
/* $MirOS$ */
/* $ekkoBSD: lexer.l,v 1.11 2004/02/27 23:40:58 dave Exp $ */

/*-
 * Copyright (c) 2003 David Steinberg <dave@redterror.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF MIND, USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "fdialog.h"
#include "y.tab.h"

__RCSID("$MirOS$");

static int lineno = 0;
static int pos = 0;
static char * strbuf = NULL;

int yylex(void);

%}

num		[0-9]+

%%

(-|--)?border				{ return FDL_BORDER; }
(-|--)?calendar				{ return FDL_CALENDAR; }
(-|--)?(description|descr)		{ return FDL_DESCRIPTION; }
(-|--)?gauge				{ return FDL_GAUGE; }
(-|--)?(fd|file-descriptor|file-desc) 	{ return FDL_FILE_DESCRIPTOR; }
(-|--)?fselect				{ return FDL_FSELECT; }
(-|--)?(info|infobox)			{ return FDL_INFOBOX; }
(-|--)?inputbox				{ return FDL_INPUTBOX; }
(-|--)?inputmenu			{ return FDL_INPUTMENU; }
(-|--)?(ival|item-value)		{ return FDL_ITEM_VALUE; }
(-|--)?item				{ return FDL_ITEM; }
(-|--)?menu				{ return FDL_MENU; }
(-|--)?menubox				{ return FDL_MENUBOX; }
(-|--)?msgbox				{ return FDL_MSGBOX; }
(-|--)?password				{ return FDL_PASSWORD; }
(-|--)?ptitle				{ return FDL_PTITLE; }
(-|--)?radio				{ return FDL_RADIO; }
(-|--)?shadow				{ return FDL_SHADOW; }
(-|--)?sleep				{ return FDL_SLEEP; }
(-|--)?text				{ return FDL_MAINTEXT; }
(-|--)?textbox				{ return FDL_TEXTBOX; }
(-|--)?timebox				{ return FDL_TIMEBOX; }
(-|--)?tailbox				{ return FDL_TAILBOX; }
(-|--)?viewer				{ return FDL_VIEWER; }
(-|--)?yesno				{ return FDL_YESNO; }


-h|--h|--help	{ usage(NULL); }

{num}		{ pos += yyleng;
		  yylval.number = (int)strtol(yytext, (char **)NULL, 10);
		  return NUMBER;
		}

.+		{ pos += yyleng;
		  yylval.string = strdup(yytext); 
		  return STRING;
		}
%%

void
yyerror(const char * s) {
	fprintf(stderr, "%s at '%s' on line %d char %d\n",
		s, yytext, lineno, pos+1);
	if (strbuf)
		fprintf(stderr, "%s\n%*s\n", strbuf, pos + 1, "^");
}

/* move to the next argument in g_argv */
int
yywrap (void) {
	extern int cur_arg;
	extern int g_argc;
	extern char ** g_argv;

	if (cur_arg == (g_argc - 1))
		return 1;	/* indicate no more data */

	cur_arg++;
	yy_scan_string(g_argv[cur_arg]);
	return 0;
}
