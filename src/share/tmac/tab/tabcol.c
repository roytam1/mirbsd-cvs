/* $MirOS: src/share/tmac/tab/tabcol.c,v 1.5 2012/05/22 00:06:46 tg Exp $ */

/*-
 * Copyright (c) 1979, 1980, 1981, 1986, 1988, 1990, 1991, 1992
 *     The Regents of the University of California.
 * Copyright (C) Caldera International Inc.  2001-2002.
 * Copyright (c) 2003, 2004, 2006, 2012, 2016
 *	mirabilos <m@mirbsd.org>
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
 *	@(#)tablpr.c	4.2 (Berkeley) 4/18/91
 */

#define INCH 240
/*
 * LPR or CRT 10 Pitch
 * nroff driving table
 * reverse line feeds by means of col(1)
 * by UCB Computer Center
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
/*breset*/	0,
/*Hor*/		INCH/10,
/*Vert*/	INCH/6,
/*Newline*/	INCH/6,
/*Char*/	INCH/10,
/*Em*/		INCH/10,
/*Halfline*/	INCH/12,
/*Adj*/		INCH/10,
/*twinit*/	"",		/* invoke elite */
/*twrest*/	"",		/* reset printer to defaults */
/*twnl*/	"\n",
#ifdef col_halflines
/*hlr*/		"\033\012",	/* half line forward (???) */
/*hlf*/		"\033\013",	/* half line reverse (???) */
#else
/*hlr*/		"",
/*hlf*/		"",
#endif
/*flr*/		"\013",		/* full line reverse (???) */
#ifdef col_altbold
/*bdon*/	"\016",		/* Alternate chars.  '\fB' to invoke */
/*bdoff*/	"\017",		/* Standard chars. '\fP' to invoke */
#else
/*bdon*/	"",
/*bdoff*/	"",
#endif
/*ploton*/	"",
/*plotoff*/	"",
/*up*/		"",
/*down*/	"",
/*right*/	"",
/*left*/	"",
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
"\001-",	/*-*/
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
"\001_",	/*_*/
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
"\000",		/*nar sp*/
"\001-",	/*hyphen*/
"\001o\b+",	/*bullet*/
"\002[]",	/*square*/
"\001-",	/*3/4 em*/
"\001_",	/*rule*/
"\0031/4",	/*1/4*/
"\0031/2",	/*1/2*/
"\0033/4",	/*3/4*/
"\001-",	/*minus*/
"\202fi",	/*fi*/
"\202fl",	/*fl*/
"\202ff",	/*ff*/
"\203ffi",	/*ffi*/
"\203ffl",	/*ffl*/
"\000\0",	/*degree*/
"\001|\b-",	/*dagger*/
"\001s\bS",	/*section*/
"\001'",	/*foot mark*/
"\001'",	/*acute accent*/
"\001`",	/*grave accent*/
"\001_",	/*underrule*/
"\001/",	/*slash (longer)*/
"\000",		/*half narrow space*/
"\001 ",	/*unpaddable space*/
"\201o\b(", 	/*alpha*/
"\2018\b|", 	/*beta*/
"\201>\b/", 	/*gamma*/
"\201d\b`", 	/*delta*/
"\201C\b-", 	/*epsilon*/
"\000\0", 	/*zeta*/
"\201n",	/*eta*/
"\201o\b-", 	/*theta*/
"\201i",	/*iota*/
"\201k",	/*kappa*/
"\201,\b\\", 	/*lambda*/
"\201u",	/*mu*/
"\201v",	/*nu*/
"\000\0", 	/*xi*/
"\201o",	/*omicron*/
"\202i\b~i\b~",	/*pi*/
"\201p",	/*rho*/
"\201o\b~", 	/*sigma*/
"\201i\b~", 	/*tau*/
"\201u",	/*upsilon*/
"\201o\b|", 	/*phi*/
"\201x",	/*chi*/
"\201u\b|", 	/*psi*/
"\201w", 	/*omega*/
"\201I\b~", 	/*Gamma*/
"\202/\b_\\\b_", /*Delta*/
"\201O\b-",	/*Theta*/
"\202/\\",	/*Lambda*/
"\201=\b_",	/*Xi*/
"\202TT",	/*Pi*/
"\201>\b_\b~", 	/*Sigma*/
"\000",		/**/
"\201Y",	/*Upsilon*/
"\201O\b|",	/*Phi*/
"\201U\b|",	/*Psi*/
"\201O\b_",	/*Omega*/
"\001v\b/",	/*square root*/
"\000\0",	/*terminal sigma*/
"\001~",	/*root en*/
"\001>\b_",	/*>=*/
"\001<\b_",	/*<=*/
"\001=\b_",	/*identically equal*/
"\001-",	/*equation minus*/
"\001~\b_",	/*approx =*/
"\001~",	/*approximates*/
"\001=\b/",	/*not equal*/
"\002->",	/*right arrow*/
"\002<-",	/*left arrow*/
"\001|\b^",	/*up arrow*/
"\001|\bv",	/*down arrow*/
"\001=",	/*equation equal*/
"\001x",	/*multiply*/
"\001:\b-",	/*divide*/
"\001+\b_",	/*plus-minus*/
"\002(\b~)\b~",	/*cup (union)*/
"\002(\b_)\b_",	/*cap (intersection)*/
"\002(=",	/*subset of*/
"\002=)",	/*superset of*/
"\002(=\b_",	/*improper subset*/
"\002=\b_)",	/*improper superset*/
"\002oo",	/*infinity*/
"\001o\b`",	/*partial derivative*/
"\002\\\b~/\b~", /*gradient*/
"\000\0",	/*not*/
"\000\0",	/*integral sign*/
"\002oc",	/*proportional to*/
"\001O\b/",	/*empty set*/
"\001<\b-",	/*member of*/
"\001+",	/*equation plus*/
"\003(R)",	/*registered*/
"\003(C)",	/*copyright*/
"\001|",	/*box rule */
"\001c\b/",	/*cent sign*/
"\001|\b=",	/*dbl dagger*/
"\002=>",	/*right hand*/
"\002<=",	/*left hand*/
"\001*",	/*math * */
"\000\0",	/*bell system sign*/
"\001|",	/*or (was star)*/
"\001O",	/*circle*/
"\001|",	/*left top of big brace*/
"\001|",	/*left bot of big brace*/
"\001|",	/*right top of big brace*/
"\001|",	/*right bot of big brace*/
"\001|",	/*left center of big brace*/
"\001|",	/*right center of big brace*/
"\001|",	/*bold vertical*/
"\001|",	/*left floor (lb of big bracket)*/
"\001|",	/*right floor (rb of big bracket)*/
"\001|",	/*left ceiling (lt of big bracket)*/
"\001|",	/*right ceiling (rt of big bracket)*/
"\201\241",	/*(a1) activate 8 bit passing*/
"\000\253",	/*(ab) 8bit: bit is 0*/
"\000\273",	/*(bb) 8bit: bit is 1*/
 },
 0
};
