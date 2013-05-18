/* $MirOS: src/share/tmac/tab/tabitoh.c,v 1.2 2008/11/08 22:24:21 tg Exp $ */

/*-
 * Copyright (c) 1979, 1980, 1981, 1986, 1988, 1990, 1991, 1992
 *     The Regents of the University of California.
 * Copyright (C) Caldera International Inc.  2001-2002.
 * Copyright (c) 2003, 2004, 2012
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms,
 * with or without modification, are permitted provided
 * that the following conditions are met:
 *
 * Redistributions of source code and documentation must retain
 * the above copyright notice, this list of conditions and the
 * following disclaimer.  Redistributions in binary form must
 * reproduce the above copyright notice, this list of conditions
 * and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 *
 * All advertising materials mentioning features or use of this
 * software must display the following acknowledgement:
 *   This product includes software developed or owned by
 *   Caldera International, Inc.
 *
 * Neither the name of Caldera International, Inc. nor the names
 * of other contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * USE OF THE SOFTWARE PROVIDED FOR UNDER THIS LICENSE BY CALDERA
 * INTERNATIONAL, INC. AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL CALDERA INTERNATIONAL, INC. BE
 * LIABLE FOR ANY DIRECT, INDIRECT INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *	@(#)tabitoh.c	4.2 (Berkeley) 4/18/91
 */

#define INCH 240
/*
 * C:Itoh Prowriter (dot matrix) 10 pitch
 * nroff driving table
 * by G. Rochlin, 15feb83
 * Because the c:itoh will backspace only in incremental mode,
 * need to write a program to place commands Esc[ and Esc] around ^H.
 * If you want true underline mode instead of _^Hx_^Hy, etc.,
 * have the script first replace _^Hx with EscXxEscY, etc.
 * Further refinements are possible to clean up files and
 * minimize throughput (e.g., delete all EscYEscX pairs).
 * In the terminal initialization (twinit) and exit (twrest)
 * strings, EscN sets 10-pitch. Twrest clears by commanding
 * Esc Y, Esc", and Esc$ to clear ul, bold, and "greek",
 * Esc] to restore logic-seek print, Escf and EscT24 to restore
 * forward linefeed at 6 lines/inch, Esc< for bidirectional
 * print, EscN, and ^M (\015) to clear the print buffer.
 * Since the itoh has no keyboard, you have to run it through
 * a video terminal or micro printer port.
 * The first twinit code (Esc`) and the last twrest code
 * (Esca) set the (proper) "transparent" or "buffered" print
 * mode for tvi950 and tvi925 and Freedom 100. This mode
 * is necessary on intelligent terminals to keep all the Esc
 * codes in the driver tables from scrambling the terminal's
 * brains.  (If you have a dumb terminal, almost any print
 * mode should be safe. Smart terminals without buffered print,
 * such as the tvi920, present problems.)
 * If you have a different terminal,
 * the shell script should also replace these codes with those
 * appropriate for your machine.  If you are using an sed
 * stream for the script, make sure to use single quotes to
 * isolate the ` from the shell.
 */
struct {
	int bset;
	int breset;
	int Hor;
	int Vert;
	int Newline;
	int Char;
	int Em;
	int Halfline;
	int Adj;
	const char *twinit;
	const char *twrest;
	const char *twnl;
	const char *hlr;
	const char *hlf;
	const char *flr;
	const char *bdon;
	const char *bdoff;
	const char *ploton;
	const char *plotoff;
	const char *up;
	const char *down;
	const char *right;
	const char *left;
	const char *codetab[256-32];
	int zzz;
	} t = {
/*bset*/	0,
/*breset*/	0177420,
/*Hor*/		INCH/20,
/*Vert*/	INCH/48,
/*Newline*/	INCH/6,
/*Char*/	INCH/10,
/*Em*/		INCH/10,
/*Halfline*/	INCH/12,
/*Adj*/		INCH/10,
/*twinit*/	"\033`\015\033N",
/*twrest*/	"\033Y\033\042\033$\033]\033f\033T24\033<\033N\015\033a\n",
/*twnl*/	"\015\n",
/*hlr*/		"\033[\033T12\033r\n\033T24\033]\033f",
/*hlf*/		"\033[\033T12\n\033T24\033]",
/*flr*/         "\033[\033r\n\033f\033]",
/*bdon*/	"\033!",
/*bdoff*/	"\033\042",
/*ploton*/	"\033>\033T03",
/*plotoff*/	"\033<\033T24",
/*up*/		"\033[\033r\n\033f\033]",
/*down*/	"\033[\n\033]",
/*right*/	"\033P \033N",
/*left*/	"\b\033Q \033N",
/*codetab*/	{
#include "code.itoh"
		},
/*zzz*/		0
};
