/* $MirOS: src/share/tmac/tab/tabqume12.c,v 1.2 2008/11/08 22:24:22 tg Exp $ */

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
 *	@(#)tabqume12.c	4.3 (Berkeley) 4/18/91
 */

#define INCH 240
/*
 * QUME 12 Pitch
 * nroff driving table
 * ASCII Prestige Elite 12 M2167
 * by Albert Einstein College of Medicine
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
/*Hor*/		INCH/120,
/*Vert*/	INCH/48,
/*Newline*/	INCH/6,
/*Char*/	INCH/12,
/*Em*/		INCH/12,
/*Halfline*/	INCH/12,
/*Adj*/		INCH/12,
/*twinit*/	"\0334\033\037\013",/*plot off, horiz. motion = 10/120 inch*/
/*twrest*/	"\0334\033\037\013",
/*twnl*/	"\r\n",
/*hlr*/		"\033D",
/*hlf*/		"\033U",
/*flr*/		"\033\n",
/*bdon*/	"",
/*bdoff*/	"",
/*ploton*/	"\033G",
/*plotoff*/	"\0334",
/*up*/		"\033\n",
/*down*/	"\n",
/*right*/	" ",
/*left*/	"\b",
/*codetab*/	{
"\001 ",	/*space*/
"\001!",	/*!*/
"\001\"",	/*"*/
"\001#",	/*#*/
"\001$",	/*$*/
"\001%",	/*%*/
"\001&",	/*&*/
"\001'",	/*' close*/
"\001(",	/*(*/
"\001)",	/*)*/
"\001*",	/***/
"\001+",	/*+*/
"\001,",	/*,*/
"\001-",	/*- hyphen*/
"\001.",	/*.*/
"\001/",	/*/*/
"\2010",	/*0*/
"\2011",	/*1*/
"\2012",	/*2*/
"\2013",	/*3*/
"\2014",	/*4*/
"\2015",	/*5*/
"\2016",	/*6*/
"\2017",	/*7*/
"\2018",	/*8*/
"\2019",	/*9*/
"\001:",	/*:*/
"\001;",	/*;*/
"\001<",	/*<*/
"\001=",	/*=*/
"\001>",	/*>*/
"\001?",	/*?*/
"\001@",	/*@*/
"\201A",	/*A*/
"\201B",	/*B*/
"\201C",	/*C*/
"\201D",	/*D*/
"\201E",	/*E*/
"\201F",	/*F*/
"\201G",	/*G*/
"\201H",	/*H*/
"\201I",	/*I*/
"\201J",	/*J*/
"\201K",	/*K*/
"\201L",	/*L*/
"\201M",	/*M*/
"\201N",	/*N*/
"\201O",	/*O*/
"\201P",	/*P*/
"\201Q",	/*Q*/
"\201R",	/*R*/
"\201S",	/*S*/
"\201T",	/*T*/
"\201U",	/*U*/
"\201V",	/*V*/
"\201W",	/*W*/
"\201X",	/*X*/
"\201Y",	/*Y*/
"\201Z",	/*Z*/
"\001[",	/*[*/
"\001\\",	/*\*/
"\001]",	/*]*/
"\001^",	/*^*/
"\001_",	/*_ dash*/
"\001`",	/*` open*/
"\201a",	/*a*/
"\201b",	/*b*/
"\201c",	/*c*/
"\201d",	/*d*/
"\201e",	/*e*/
"\201f",	/*f*/
"\201g",	/*g*/
"\201h",	/*h*/
"\201i",	/*i*/
"\201j",	/*j*/
"\201k",	/*k*/
"\201l",	/*l*/
"\201m",	/*m*/
"\201n",	/*n*/
"\201o",	/*o*/
"\201p",	/*p*/
"\201q",	/*q*/
"\201r",	/*r*/
"\201s",	/*s*/
"\201t",	/*t*/
"\201u",	/*u*/
"\201v",	/*v*/
"\201w",	/*w*/
"\201x",	/*x*/
"\201y",	/*y*/
"\201z",	/*z*/
"\001{",	/*{*/
"\001|",	/*|*/
"\001}",	/*}*/
"\001~",	/*~*/
"\000\0",	/*narrow sp*/
"\001-",	/*hyphen*/
"\0010\b+",	/*bullet*/
"\000\0",	/*square*/
"\001-",	/*3/4 em*/
"\001_",	/*rule*/
"\000\0",	/*1/4*/
"\000\0",	/*1/2*/
"\000\0",	/*3/4*/
"\001-",	/*minus*/
"\202fi",	/*fi*/
"\202fl",	/*fl*/
"\202ff",	/*ff*/
"\203ffi",	/*ffi*/
"\203ffl",	/*ffl*/
"\000\0",	/*degree*/
"\000\0",	/*dagger*/
"\000\0",	/*section*/
"\001'",	/*foot mark*/
"\001'",	/*acute accent*/
"\001`",	/*grave accent*/
"\001_",	/*underrule*/
"\001/",	/*slash (longer)*/
"\000\0",	/*half narrow space*/
"\001 ",	/*unpaddable space*/
"\000\0",	/*alpha*/
"\000\0",	/*beta*/
"\000\0",	/*gamma*/
"\000\0",	/*delta*/
"\000\0",	/*epsilon*/
"\000\0",	/*zeta*/
"\000\0",	/*eta*/
"\000\0",	/*theta*/
"\000\0",	/*iota*/
"\000\0",	/*kappa*/
"\000\0",	/*lambda*/
"\000\0",	/*mu*/
"\000\0",	/*nu*/
"\000\0",	/*xi*/
"\000\0",	/*omicron*/
"\000\0",	/*pi*/
"\000\0",	/*rho*/
"\000\0",	/*sigma*/
"\000\0",	/*tau*/
"\000\0",	/*upsilon*/
"\000\0",	/*phi*/
"\000\0",	/*chi*/
"\000\0",	/*psi*/
"\000\0",	/*omega*/
"\000\0",	/*Gamma*/
"\000\0",	/*Delta*/
"\000\0",	/*Theta*/
"\000\0",	/*Lambda*/
"\000\0",	/*Xi*/
"\000\0",	/*Pi*/
"\000\0",	/*Sigma*/
"\000\0",	/**/
"\000\0",	/*Upsilon*/
"\000\0",	/*Phi*/
"\000\0",	/*Psi*/
"\000\0",	/*Omega*/
"\000\0",	/*square root*/
"\000\0",	/*terminal sigma*/
"\000\0",	/*root en*/
"\001>\b_",	/*>=*/
"\001<\b_",	/*<=*/
"\000\0",	/*identically equal*/
"\001-",	/*equation minus*/
"\001~\b_",	/*approx =*/
"\001~",	/*approximates*/
"\001=\b/",	/*not equal*/
"\002->",	/*right arrow*/
"\002<-",	/*left arrow*/
"\000\0",	/*up arrow*/
"\000\0",	/*down arrow*/
"\001=",	/*equation equal*/
"\001*",	/*multiply*/
"\001/",	/*divide*/
"\001+\b_",	/*plus-minus*/
"\001U",	/*cup (union)*/
"\000\0",	/*cap (intersection)*/
"\000\0",	/*subset of*/
"\000\0",	/*superset of*/
"\000\0",	/*improper subset*/
"\000\0",	/* improper superset*/
"\000\0",	/*infinity*/
"\000\0",	/*partial derivative*/
"\000\0",	/*gradient*/
"\000\0",	/*not*/
"\000\0",	/*integral sign*/
"\000\0",	/*proportional to*/
"\0010\b/",	/*empty set*/
"\001<\b-",	/*member of*/
"\001+",	/*equation plus*/
"\000\0",	/*registered*/
"\000\0",	/*copyright*/
"\001|",	/*box rule */
"\001\033 ",	/*cent sign*/
"\000\0",	/*dbl dagger*/
"\000\0",	/*right hand*/
"\000\0",	/*left hand*/
"\001*",	/*math * */
"\000\0",	/*bell system sign*/
"\001|",	/*or (was star)*/
"\000\0",	/*circle*/
"\000\0",	/*left top (of big curly)*/
"\000\0",	/*left bottom*/
"\000\0",	/*right top*/
"\000\0",	/*right bot*/
"\000\0",	/*left center of big curly bracket*/
"\000\0",	/*right center of big curly bracket*/
"\000\0",	/*bold vertical*/
"\000\0",	/*left floor (left bot of big sq bract)*/
"\000\0",	/*right floor (rb of ")*/
"\000\0",	/*left ceiling (lt of ")*/
"\000\0",	/*right ceiling (rt of ")*/
"\000\0",	/*superscript 0	 */
"\000\0",	/*superscript 1	 */
"\000\0",	/*superscript 2	 */
"\000\0",	/*superscript 3	 */
"\000\0",	/*superscript 4	 */
"\000\0",	/*superscript 5	 */
"\000\0",	/*superscript 6	 */
"\000\0",	/*superscript 7	 */
"\000\0",	/*superscript 8	 */
0,0,0,		/*0374, 0375, 0376 cannot be accessed */
"\000\0",	/*superscript 9	 */
/*"\001\016;\017",		umlaut	dotdot	*/
 },
 0
};
