%{
/* $MirOS$ */
/* $ekkoBSD: parse.y,v 1.12 2004/02/27 22:55:51 dave Exp $ */

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

#include <sys/queue.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <cdk/cdk.h>
#include <err.h>
#include <stdio.h>
#include <string.h>

#include "fdialog.h"

__RCSID("$MirOS$");

#define LINE_BREAK_STR '\\'

void not_yet(void);

extern int sleep_delay;
extern struct display display;

char * menu_choices[] = {"   ", "-->"};

%}

%union {
	int number;
	char * string;
	struct fdl_item * item;
	struct itemq_head * item_list;
	struct dims dims;
	struct viewer_content viewer_content;
}

/* display types */
%token FDL_CALENDAR
%token FDL_DIALOG
%token FDL_FSELECT
%token FDL_GAUGE
%token FDL_INFOBOX
%token FDL_INPUTBOX
%token FDL_INPUTMENU
%token FDL_MENU
%token FDL_MSGBOX
%token FDL_MENUBOX
%token FDL_PASSWORD
%token FDL_RADIO
%token FDL_TAILBOX
%token FDL_TAILBOXBG
%token FDL_TEXTBOX
%token FDL_TIMEBOX
%token FDL_VIEWER
%token FDL_YESNO

/* other object types */
%token FDL_BORDER
%token FDL_DESCRIPTION
%token FDL_DISPLAY 
%token FDL_FILE_DESCRIPTOR
%token FDL_ITEM 
%token FDL_ITEM_VALUE
%token FDL_LABEL
%token FDL_MAINTEXT
%token FDL_PTITLE 
%token FDL_SHADOW
%token FDL_SLEEP 

%token <number> NUMBER
%token <string> STRING

%type <item> item
%type <item_list> item_list
%type <string> item_value
%type <string> description
%type <string> ctitle
%type <string> directory
%type <dims> dimensions
%type <viewer_content> viewer_content
%%

display_types : 
	  calendar 	 options 	{ display.type = FDL_CALENDAR; }
	| fselect	 options	{ display.type = FDL_FSELECT; }
	| gauge		 options	{ display.type = FDL_GAUGE; }
	| infobox	 options	{ display.type = FDL_INFOBOX; }
	| inputbox	 options	{ display.type = FDL_INPUTBOX; }
	| inputmenu	 options	{ display.type = FDL_INPUTMENU; }
	| menu		 options	{ display.type = FDL_MENU; }
	| menubox	 options	{ display.type = FDL_MENUBOX; }
	| msgbox	 options	{ display.type = FDL_DIALOG; }
	| password	 options	{ display.type = FDL_PASSWORD; }
	| radio		 options	{ display.type = FDL_RADIO; }
	| textbox	 options	{ display.type = FDL_TEXTBOX; }
	| timebox	 options	{ display.type = FDL_TIMEBOX; }
	| tailbox 	 options	{ display.type = FDL_TAILBOX; }
	| tailboxbg	 options	{ display.type = FDL_TAILBOX; }
	| viewer	 options	{ display.type = FDL_VIEWER; }
	| yesno		 options	{ display.type = FDL_DIALOG; }
	;
options : 
	| options FDL_SLEEP NUMBER	{ sleep_delay = $3;
				  	DEBUG("sleep: %d", sleep_delay); }
	| options FDL_PTITLE STRING	{ strlcpy(display.ptitle, $3, PTITLE_MAX); }
	| options FDL_SHADOW		{ display.shadow = TRUE; }
	| options FDL_BORDER		{ display.box = TRUE; }
	| options main_text
	;
main_text : FDL_MAINTEXT STRING		{ char ** msg;
					  msg = CDKsplitString($2, LINE_BREAK_STR);

		  			  display.text = newCDKLabel(display.cdkscreen, CENTER, TOP,
						msg, CDKcountStrings(msg), display.box, display.shadow);

					  FDL_checkCDKError(display.text, "main text");
					}
	;
menu : 
	FDL_MENU ctitle item_list dimensions 
		{ struct fdl_str * items;

		  /* turn the list of items into a display-able list */
		  items = itemq_to_str(&itemq_head);
		  display.menu_items = &itemq_head;
		  display.obj.selection = newCDKSelection(display.cdkscreen, CENTER, CENTER,
			RIGHT, $4.h, $4.w, $2,
			items->str, items->size,
			menu_choices, 2, A_REVERSE, display.box, display.shadow);

		  FDL_checkCDKError(display.obj.selection, "selection");
		}
	;
radio :
	FDL_RADIO ctitle item_list dimensions 
		{ struct fdl_str * items;

		  items = itemq_to_str(&itemq_head);
		  display.menu_items = &itemq_head;
		  display.obj.radio = newCDKRadio(display.cdkscreen, CENTER, CENTER,
			RIGHT, $4.h, $4.w, $2,
			items->str, items->size,
			'#'|A_REVERSE, 1, A_REVERSE, display.box, display.shadow);

		  FDL_checkCDKError(display.obj.radio, "radio");
		}
	;
inputbox:
	FDL_INPUTBOX ctitle dimensions
		{ static char * buttons[] = {"Ok", "Cancel"};
		  /* XXX: the above probably shouldn't be static, but I am lazy and don't
		   * feel like encapsulating buttons in containers right now
		   */

		  display.buttons = buttons;
		  display.obj.entry = newCDKEntry(display.cdkscreen, CENTER, CENTER,
					$2, NULL, A_NORMAL, ' ', vMIXED,
					40, 0, 256, display.box, display.shadow);
		  display.widget.buttonbox = newCDKButtonbox(display.cdkscreen,
					getbegx(display.obj.entry->win), 
					getbegy(display.obj.entry->win) 
						+ display.obj.entry->boxHeight - 1,
					1, display.obj.entry->boxWidth - 1,
					0, 1, 2,
					display.buttons, 2, A_REVERSE,
					display.box, display.shadow);

		  /* set lower left / right characters of box
		   * XXX: refactor this
		   */
		  setCDKEntryLLChar(display.obj.entry, ACS_LTEE);
		  setCDKEntryLRChar(display.obj.entry, ACS_RTEE);
		  setCDKButtonboxULChar(display.widget.buttonbox, ACS_LTEE);
		  setCDKButtonboxURChar(display.widget.buttonbox, ACS_RTEE);

		  /* bind the tab key in the entry field and send the tab key
		   * to the button box widget.
		   */
		  bindCDKObject(vENTRY, display.obj.entry, KEY_TAB, 
			&entryCB, display.widget.buttonbox);

		  /* XXX use bindCDKObject, setCDKEntry to populate default values
		   * with parameters
		   */

		  FDL_checkCDKError(display.obj.entry, "entry");
		  /* XXX temp */
		  DEBUG("button0: %s ; button1: %s", 
			display.buttons[0], display.buttons[1]);
		}
	;
fselect : FDL_FSELECT directory ctitle dimensions
		{ DEBUG("fselect: %s", $2);

		  display.obj.fselect = newCDKFselect(display.cdkscreen, CENTER, CENTER,
			$4.h, $4.w, $3, "File: ", A_NORMAL, '_', A_REVERSE,
			"</5>", "</48>", "</N>", "</N>", display.box, display.shadow);
		  /* set the starting directory */
		  setCDKFselect(display.obj.fselect, $2, A_NORMAL, '.', A_REVERSE,
			"</5>", "</48>", "</N>", "</N>", ObjOf(display.obj.fselect)->box);

		  FDL_checkCDKError(display.obj.fselect, "fselect");
		}
	;
infobox : 
	FDL_INFOBOX ctitle dimensions
		{ char ** msg;

		  msg = CDKsplitString($2, LINE_BREAK_STR);
		  display.obj.label = newCDKLabel(display.cdkscreen, CENTER, CENTER,
			msg, CDKcountStrings(msg), display.box, display.shadow);

		  FDL_checkCDKError(display.obj.label, "label");

		}
	;
gauge : 
	FDL_GAUGE ctitle NUMBER dimensions 
		{ if ($3 < 0 || $3 > 100)
			usage("gauge percent must be between 0 and 100");

		  display.obj.histogram = newCDKHistogram(display.cdkscreen, CENTER, CENTER,
			$4.h, $4.w, HORIZONTAL, $2, 1, 1);

		  FDL_checkCDKError(display.obj.histogram, "gauge");

		  /* XXX we might like to tweak these later */
		  setCDKHistogram(display.obj.histogram, vPERCENT, CENTER, A_BOLD,
			0, 100, $3, ' '|A_REVERSE|COLOR_PAIR(3), TRUE);
		}
	;
msgbox :
	FDL_MSGBOX ctitle dimensions
		{ static char * buttons[] = {"</B/24>Ok"};
		  char ** msg;

		  msg = CDKsplitString($2, LINE_BREAK_STR);
		  display.buttons = buttons;

		  display.obj.dialog = newCDKDialog(display.cdkscreen, CENTER, CENTER,
			msg, CDKcountStrings(msg), buttons, 1,
			COLOR_PAIR(2)|A_REVERSE, TRUE, display.box, display.shadow);
		  FDL_checkCDKError(display.obj.dialog, "msgbox");
		}
	;
yesno :
	FDL_YESNO ctitle dimensions
		{ static char * buttons[] = {"</B/24>Yes", "</B16>No"};
		  char ** msg;

		  msg = CDKsplitString($2, LINE_BREAK_STR);
		  display.buttons = buttons;

		  display.obj.dialog = newCDKDialog(display.cdkscreen, CENTER, CENTER,
			msg, CDKcountStrings(msg), buttons, 2,
			COLOR_PAIR(2)|A_REVERSE, TRUE, display.box, display.shadow);
		  FDL_checkCDKError(display.obj.dialog, "msgbox");
		}
	;
viewer :
	FDL_VIEWER viewer_content ctitle dimensions
		{ static char * buttons[] = {"</B/24>Ok", "</B16>Cancel"};
		  char * title = NULL;	/* provide a default title */

		  if ($3 == NULL)
			(void) asprintf(&title,  "<C></B/21>Filename:<!21></22>%20s<!22!B>", $2.filename);
		  else
			title = $3;

		  display.buttons = buttons;
		  display.obj.viewer = newCDKViewer(display.cdkscreen, CENTER, CENTER,
			$4.h, $4.w, buttons, 2, A_REVERSE, display.box, display.shadow);
		  setCDKViewer(display.obj.viewer, title, $2.str->str, $2.str->size,
			A_REVERSE, TRUE, display.box, display.shadow);

		  FDL_checkCDKError(display.obj.viewer, "viewer");
		}
	;
viewer_content :
	STRING				{ /* a plain filename */
					  struct stat sb;

					  if (stat($1, &sb) != 0) {
						perror("stat");
						fdl_exit(255);
					  }
					  if (! (sb.st_mode & (S_IFREG|S_IFLNK))) 
						usage("File is not a link / regular file");
					
					  $$.filename = $1;
					  $$.str = str_new(0);	/* make with size 0, since its just a placeholder */
					  $$.str->size = CDKreadFile($$.filename, &$$.str->str);
					}
	| FDL_FILE_DESCRIPTOR NUMBER 	{ /* reading from a file descriptor */
					  /* asprintf(&$$.filename, "File Descriptor %d", $2); */
					  not_yet();
					}
	;
inputmenu :
	FDL_INPUTMENU	{ not_yet(); }
	;
calendar :		
	FDL_CALENDAR	{ not_yet(); }
	;
menubox :
	FDL_MENUBOX	{ not_yet(); }
	;
password :
	FDL_PASSWORD ctitle dimensions
		{ static char * buttons[] = {"</B/24>Ok", "</B16>Cancel"};

		  /* need to refactor the stuff above from entry and use it here */
		  display.buttons = buttons;

		  /* make an entry type, but hide all input (vHMIXED) */
		  display.obj.entry = newCDKEntry(display.cdkscreen, CENTER, CENTER,
				$2, ">", A_NORMAL, ' ', vHMIXED,
				40, 0, 32, display.box, display.shadow);
		
		  FDL_checkCDKError(display.obj.entry, "entry");
		}		
	;
textbox :
	FDL_TEXTBOX	{ not_yet(); }
	;
timebox :
	FDL_TIMEBOX	{ not_yet(); }
	;
tailbox :
	FDL_TAILBOX	{ not_yet(); }
	;
tailboxbg:
	FDL_TAILBOXBG	{ not_yet(); }

ctitle : 
				{ $$ = NULL; }
	| STRING		{ DEBUG("ctitle: %s", $1); 
				  $$ = $1; }
	;
item_list : 
	item			{ DEBUG("list of 1 item");
				  TAILQ_INSERT_TAIL(&itemq_head, $1, items);
				  $$ = &itemq_head;
				}
	| item_list item	{ DEBUG("list of >1 item");
				  TAILQ_INSERT_TAIL(&itemq_head, $2, items);
				  $$ = &itemq_head;
				}
	;
item : 
	FDL_ITEM STRING			
				{ DEBUG("single item (no descr): %s", $2); 
				  $$ = new_item($2, NULL, NULL); 
				}
	| FDL_ITEM STRING description	
				{ DEBUG("single item: %s %s", $2, $3);
				  $$ = new_item($2, $3, NULL); 
				}
	| FDL_ITEM STRING item_value
				{ DEBUG("single item (val/no descr): %s %d", $2, $3);
				  $$ = new_item($2, NULL, $3);
				}
	| FDL_ITEM STRING item_value description
				{ DEBUG("item (val/descr): %s %d %s", $2, $3, $4);
				  $$ = new_item($2, $4, $3);
				}
	| FDL_ITEM STRING description item_value
				{ DEBUG("item (descr/val): %s %d %s", $2, $4, $3);
				  $$ = new_item($2, $3, $4);
				}
	;
directory :
	STRING			{ struct stat sb;
				  DEBUG("directory: %s", $1);

				  if (stat($1, &sb) != 0) {
					perror("stat");
					fdl_exit(255);
				  }
				  if ((sb.st_mode & S_IFDIR) != S_IFDIR) {
					warnx("%s is not a directory\n", $1);
					fdl_exit(255);
				  }

				  /* if we got here, the path is a directory */
				  $$ = $1;
				}
	;
dimensions : 
				{ /* since unspecified, setup a default widget size */
				  unsigned int max_y, max_x, beg_y, beg_x = 0;

				  getmaxyx(display.cursesWin, max_y, max_x);
				  getbegyx(display.cursesWin, beg_y, beg_x);

				  $$.h = ((max_y - beg_y) * 3 / 4);
				  $$.w = ((max_x - beg_x) * 3 / 4);
				}
	| NUMBER NUMBER 	{  $$.h = $1;
				   $$.w = $2; }
	;
description : 
	FDL_DESCRIPTION STRING		
				{ DEBUG("description: %s", $2);
				  $$ = $2; }
	;
item_value :
	FDL_ITEM_VALUE NUMBER	{ DEBUG("item_value: %d", $2);
				  (void) asprintf(&$$, "%d", $2); }
	| FDL_ITEM_VALUE STRING { DEBUG("item_value: %s", $2);
				  $$ = $2; }
	;
%%

static int entryCB(EObjectType cdktype GCC_UNUSED,
			void * object GCC_UNUSED,
			void * clientData, chtype key) {
	CDKBUTTONBOX * bbox = (CDKBUTTONBOX *) clientData;
	injectCDKButtonbox(bbox, key);
	return(TRUE);
}

void
not_yet(void) {
	fprintf(stdout, "Sorry, this widget hasn't been implemented yet.\n");
	fdl_exit(1);
}	

char *
lookupDisplayType(int type) {
	int i;
	static struct display_type_map {
		int	type;
		char *	text;
	} dt_map[] = {
		{ FDL_CALENDAR, "CALENDAR" },
		{ FDL_DIALOG, "DIALOG" },
		{ FDL_FSELECT, "FSELECT" },
		{ FDL_GAUGE, "GAUGE" },
		{ FDL_INFOBOX, "INFOBOX" },
		{ FDL_INPUTBOX, "INPUTBOX" },
		{ FDL_INPUTMENU, "INPUTMENU" },
		{ FDL_MENU, "MENU" },
		{ FDL_MSGBOX, "MSGBOX" },
		{ FDL_MENUBOX, "MENUBOX" },
		{ FDL_PASSWORD, "PASSWORD" },
		{ FDL_RADIO, "RADIO" },
		{ FDL_TAILBOX, "TAILBOX" },
		{ FDL_TAILBOXBG, "TAILBOXBG" },
		{ FDL_TEXTBOX, "TEXTBOX" },
		{ FDL_TIMEBOX, "TIMEBOX" },
		{ FDL_VIEWER, "VIEWER" },
		{ FDL_YESNO, "YESNO" },
		{ 0, 0 }
	};

	for (i=0; dt_map[i].type != 0; i++)
		if (dt_map[i].type == type)
			return dt_map[i].text;

	return NULL;
}
