/* $MirOS$ */
/* $ekkoBSD: fdialog.c,v 1.14 2004/03/19 18:12:07 dave Exp $ */

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

#include <sys/types.h>
#include <curses.h>
#include <fcntl.h>
#include <err.h>
#include <paths.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>

#include "fdialog.h"
#include "y.tab.h"

__RCSID("$MirOS$");

/* should be YY_BUFFER_STATE but discard */
void *yy_scan_string(const char *yy_str);

/* program globals, fdialog.h exports these */
int sleep_delay = SLEEP_DELAY_INITIAL;
struct display display;

/* initialize our tailq of fdl_items */
struct itemq_head itemq_head = TAILQ_HEAD_INITIALIZER(itemq_head);

#define START_ARG 1
int cur_arg = START_ARG;
int g_argc;
char ** g_argv;

int
main (int argc, char ** argv) {
	FILE 		* output, * input = NULL;
	char		* retval = NULL;
	int 		selected = 0;
	int		error = 0;
	char 		* errtext = NULL;
	SCREEN		* scr = NULL;
	WINDOW 		* mainWin = NULL;

	/* send output directly to the user's term, so we can write output to stdout */
	if ((input = output = fopen(_PATH_TTY, "r+")) == NULL) {
		perror("fdopen");
		exit(1);
	}

	/* for lex / yy_scan_string to read from the command line */
	g_argc = argc;
	g_argv = argv;
	if (argc > 1)
		yy_scan_string(argv[START_ARG]);
	else
		usage(NULL);

	/*
	 * XXX: Ideally, CDK mode should begin after parsing all the arguments.
	 * Maybe there's some way we can queue all the different work that needs to
	 * be done and run through it all in one shot later.  This would allow us
	 * to have a normal screen when reporting errors in the parser.  Now just
	 * clear the screen every time, so if there's an error it'll be obvious.
	 */

	/* we're writing to the tty, so we need to wire this through newterm instead of stdscr */
	if ((scr = newterm(NULL, output, input)) == NULL) {
		perror("newterm");
		exit(1);
	}

	/* try and make the cursor invisible */
	curs_set(0);

	/* some defaults */
	display.box = TRUE;
	display.shadow = FALSE;

	/* setup our working window */
	mainWin = stdscr;
   	display.cursesWin = newwin(LINES-2, COLS-4, 1, 2);
	display.cdkscreen = initCDKScreen (display.cursesWin);

	refreshCDKScreen(display.cdkscreen);
	box (display.cursesWin, ACS_VLINE, ACS_HLINE);
	initCDKColor();

	DEBUG("starting to parse");
	yyparse();
	DEBUG("done parsing");

	mvwprintw(display.cursesWin, 1, 1, "%s", display.ptitle);

	refreshCDKScreen(display.cdkscreen);

	switch(display.type) {
		case FDL_INFOBOX:
			waitCDKLabel(display.obj.label, ' ');
			destroyCDKLabel(display.obj.label);
			break;
		case FDL_GAUGE:
			destroyCDKHistogram(display.obj.histogram);
			break;
		case FDL_MENU:
			selected = activateCDKSelection(display.obj.selection, 0);
			/* need to get which ones the user picked */
			retval = processSelection(display.obj.selection, display.menu_items);
			destroyCDKSelection(display.obj.selection);
			break;
		/* a msgbox is really just a degenerate dialog widget */
		case FDL_DIALOG:
			retval = runDialog(display.obj.dialog, display.buttons);
			destroyCDKDialog(display.obj.dialog);
			break;
		case FDL_RADIO:
			selected = activateCDKRadio(display.obj.radio, 0);
			retval = processRadio(display.obj.radio, display.menu_items, selected);
			destroyCDKRadio(display.obj.radio);
			break;
		case FDL_INPUTBOX:
			drawCDKButtonbox(display.widget.buttonbox, TRUE);
			retval = activateCDKEntry(display.obj.entry, 0);
			selected = display.widget.buttonbox->currentButton;

			DEBUG("retval: %s ; selected: %d", retval, selected);
			DEBUG("button0: %s ; button1: %s", display.buttons[0], display.buttons[1]);

			retval = processInputbox(display.widget.buttonbox, selected, retval);
			destroyCDKEntry(display.obj.entry);
			destroyCDKButtonbox(display.widget.buttonbox);
			break;
		case FDL_FSELECT:
			retval = activateCDKFselect(display.obj.fselect, 0);
			if (display.obj.fselect->exitType == vESCAPE_HIT)
				error++;
			break;
		case FDL_PASSWORD:
			/* need to refactor FDL_INPUTBOX b/c this really the same thing */
			retval = strdup(activateCDKEntry(display.obj.entry, 0));
			destroyCDKEntry(display.obj.entry);
			break;
		case FDL_VIEWER:
			selected = activateCDKViewer(display.obj.viewer, 0);
			retval = processViewer(display.obj.viewer, display.buttons, selected);
			destroyCDKViewer(display.obj.viewer);
			break;
		default:
			asprintf(&errtext, "Unknown display type: %d\n", display.type);
			error++;
			break;
	}

	/* do any post-display actions here, like pausing */
	if (sleep_delay != SLEEP_DELAY_INITIAL) {
		sleep(sleep_delay);
	}

	destroyCDKScreen(display.cdkscreen);
	delwin(display.cursesWin);
	delwin(mainWin);
	endCDK();

	if (error)
		errx(error, "%s", errtext);

	/* and finally do something with what we've learned */
	DEBUG("retval: '%s'", retval);
	if (retval != NULL)
		printf("%s\n", retval);

	return error;
}

void usage (char * str) {
	extern char * __progname;
	printf("Usage: %s <options> <widget> <widget specific options>\n", __progname);
	if (str)
		printf("%s\n", str);
	fdl_exit(1);
}

void fdl_exit(int ev) {
	if (display.cdkscreen) {
		destroyCDKScreen(display.cdkscreen);
		delwin(display.cursesWin);
		endCDK();
	}
	exit(ev);
}

void
DEBUG (char *fmt, ...) {
#ifdef FDL_DEBUG
	va_list argp;

	fprintf(stderr, "DEBUG: ");
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	fprintf(stderr, "\n");
#endif
}

void
FDL_checkCDKError(void * obj, char * msg) {
	if (obj == NULL) {
		destroyCDKScreen(display.cdkscreen);
		delwin(display.cursesWin);
		endCDK();
		err(5,"Failed to create %s, is the window big enough?", msg);
	}
}
