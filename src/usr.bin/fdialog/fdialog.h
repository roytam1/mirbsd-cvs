/* $MirOS$ */
/* $ekkoBSD: fdialog.h,v 1.17 2004/03/19 18:04:06 dave Exp $ */

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

#ifndef _FDIALOG_H
#define _FDIALOG_H

#include <cdk/cdk.h>
#include <stdio.h>
#include <sys/queue.h>

#define SLEEP_DELAY_INITIAL -1
#define PTITLE_MAX 256		/* a terminal will never be wider than this ... heh */

#define DEFAULT_OUTPUT_DESCRIPTOR 3

#define FDL_NOROOM -1

extern TAILQ_HEAD(itemq_head, fdl_item) itemq_head;

struct fdl_item {
	TAILQ_ENTRY(fdl_item) items;
	char * name;
	char * value;
	char * description;
	int flags;
};

struct fdl_str {
	char ** str;
	int size, free;
};

/* handy dimension struct */
struct dims {
	unsigned int h;
	unsigned int w;
};

/* stores data needed by the viewer object */
struct viewer_content {
	char * filename;
	struct fdl_str * str;
};

struct display {
	int type;
	char ptitle[PTITLE_MAX];
	CDKLABEL * text;
	char ** buttons;	/* text for buttons the user can hit */
	struct itemq_head * menu_items;
	union {
		CDKLABEL 	* label;
		CDKHISTOGRAM 	* histogram;
		CDKSELECTION 	* selection;	/* used for menu */
		CDKDIALOG 	* dialog;
		CDKRADIO	* radio;
		CDKENTRY	* entry;
		CDKFSELECT	* fselect;
		CDKVIEWER	* viewer;
	} obj;
	union {
		CDKBUTTONBOX	* buttonbox;
	} widget;
	CDKSCREEN * cdkscreen;
	WINDOW * cursesWin;
 	boolean box, shadow;
};

/* used w/ the --sleep <n> argument */
extern int sleep_delay;
extern struct display display;

void DEBUG(char *, ...);
void usage(char *);
void fdl_exit(int);

/* convenient structures for holding onto per-item data for menus, etc */
struct fdl_item * new_item(char *, char *, char *);
void destroy_item(struct fdl_item *);
char * toString_item(struct fdl_item *);
char * menuify_item(struct fdl_item *);
char * format_selected_item (struct fdl_item *);

struct fdl_str * itemq_to_str (struct itemq_head *);

struct fdl_str * str_new (unsigned int);
void str_destroy (struct fdl_str *);
int str_append (struct fdl_str *, const char *);

void FDL_checkCDKError(void *, char *);

char * stripCodes(char * str);
char * runDialog(CDKDIALOG *, char **);
char * processSelection(CDKSELECTION *, struct itemq_head *);
char * processRadio(CDKRADIO *, struct itemq_head *, int);
char * processInputbox(CDKBUTTONBOX *, int, char *);
char * processViewer(CDKVIEWER *, char **, int);

/* lex / yacc prototypes */
void yyerror(const char *);
int yylex(void);
int yyparse(void);

char * lookupDisplayType(int);

#endif	/* _FDIALOG_H */
