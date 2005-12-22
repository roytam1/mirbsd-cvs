/* $MirOS$ */
/* $ekkoBSD: process.c,v 1.11 2004/02/27 23:07:05 dave Exp $ */

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

#include <cdk/cdk.h>
#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "fdialog.h"

__RCSID("$MirOS$");

#define ESCAPE_HIT_STRING "Escape hit."

char *
stripCodes(char * str) {
	regex_t		rgx;
	char 		* regex = "([[:alnum:]]+$)";
	char 		* buf = NULL;
	char		ebuf[256];
	regmatch_t	* pmatch;
	int		retcode;

	if (str == NULL)
		return NULL;

	if ((retcode = regcomp(&rgx, regex, REG_EXTENDED)) != 0) {
		regerror(retcode, &rgx, ebuf, sizeof(ebuf));
		DEBUG("%s",ebuf);
		fdl_exit(1);
	} else {
		/* make sure we enough room to hold our matches */
		if ((pmatch = malloc(sizeof(regmatch_t) * rgx.re_nsub)) == NULL) {
			perror("malloc");
			fdl_exit(1);
		}
		if ((retcode = regexec(&rgx, str, rgx.re_nsub, pmatch, 0)) == 0) {
			/* matched, pmatch[0] has the matched substring */
			int start, end, len;
			start = pmatch[0].rm_so;
			end   = pmatch[0].rm_eo;
			len   = end - start;

			DEBUG("matched offsets start: %d end: %d len: %d", start, end, len);
			DEBUG("matched start: %s end: %s", str + start, str + end);

			/* extract the substring */
			buf = malloc(sizeof(char) * (len + 1));
			memcpy(buf, str + start, len);
			buf[len] = '\0';
			DEBUG("matched substring: %s", buf);
		} else {
			regerror(retcode, &rgx, ebuf, sizeof(ebuf));
			DEBUG("%s",ebuf);
		}
		free(pmatch);
	}

	regfree(&rgx);
	return buf;
}

char *
runDialog(CDKDIALOG * dlg, char ** buttons) {
	char * retval = NULL;
	int selection;

	selection = activateCDKDialog(dlg,0);

	if(dlg->exitType == vESCAPE_HIT) {
		(void) asprintf(&retval, ESCAPE_HIT_STRING);
	} else if (dlg->exitType == vNORMAL) {
		retval = buttons[selection];
	}

	DEBUG("trying to strip: %s", retval);
	retval = stripCodes(retval);
	DEBUG("after strip: %s", retval);

	return retval;
}

/* caller must free retval */
char *
processRadio(CDKRADIO * radio, struct itemq_head * item_list, int selected) {
	char * buf;
	
	if (radio->exitType == vESCAPE_HIT) {
		(void) asprintf(&buf, ESCAPE_HIT_STRING);
	} else if (radio->exitType == vNORMAL) {
		int i = 0;
		struct fdl_item * itemp;
		TAILQ_FOREACH(itemp, item_list, items) {
			if (i++ == selected)
				break;
		}

		buf = format_selected_item(itemp);
	} else {
		fprintf(stderr, "Um, what did you say?\n");
		fdl_exit(1);
	}
	return buf;
}

/* caller must free retval */
char *
processInputbox(CDKBUTTONBOX * bbox, int selected, char * text) {
	char * buf;

	asprintf(&buf, "Typed: %s\nButton: %s", text, display.buttons[selected]);
	return buf;
}

/* caller must free retval */
char *
processSelection(CDKSELECTION * sel, struct itemq_head * item_list) {
	char * retval = NULL;
	char * temp = NULL;
	
	if (sel->exitType == vESCAPE_HIT) {
		(void) asprintf(&retval, ESCAPE_HIT_STRING);
	} else if (sel->exitType == vNORMAL) {
		struct fdl_item * itemp;
		int i = 0;
		TAILQ_FOREACH(itemp, item_list, items) {
			if (sel->selections[i] == 1) {
				char * temp_item_val;
				/* XXX: this is inefficient, but both safe and readable.
				 * Though, all the same, these lists are short.
				 */
				temp_item_val = format_selected_item(itemp);
				if (retval == NULL) {
					(void) asprintf(&retval, "%s\n", temp_item_val);
				} else {
					(void) asprintf(&temp, "%s%s\n", retval, temp_item_val);
					free(retval);
					retval = temp;
				}
				free(temp_item_val);
			}
			i++;
		}

		/* XXX: chop off the last newline */
		i = strlen(retval);
		retval[i-1] = '\0';
	} else {
		fprintf(stderr, "Unknown selection status: %d\n", sel->exitType);
		fdl_exit(255);
	}	

	return retval;
}

char *
processViewer(CDKVIEWER * vw, char ** buttons, int selection) {
	char * retval = NULL;

	if(vw->exitType == vESCAPE_HIT) {
		(void) asprintf(&retval, ESCAPE_HIT_STRING);
	} else if (vw->exitType == vNORMAL) {
		retval = stripCodes(buttons[selection]);
	}
	return retval;
}
