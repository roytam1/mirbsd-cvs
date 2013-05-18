/* $MirOS: src/share/tmac/tab/tabnec-t.c,v 1.2 2008/11/08 22:24:22 tg Exp $ */

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
 *	@(#)tabnec-t.c	4.3 (Berkeley) 4/18/91
 */

#define INCH 240
/*
 * NEC Spinwriter 5500 or 7700 12 Pitch
 * nroff driving table
 * Technical-Math/Times-Roman thimble
 * by Skip Walker, ucbvax!c:bodega, 21nov82
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
/*Hor*/		INCH/120,
/*Vert*/	INCH/48,
/*Newline*/	INCH/6,
/*Char*/	INCH/12,
/*Em*/		INCH/12,
/*Halfline*/	INCH/12,
/*Adj*/		INCH/12,
/*twinit*/	"",
/*twrest*/	"",
/*twnl*/	"\n",
/*hlr*/		"\033]S\0339\033]W",
/*hlf*/		"\033]S\033ZA\033]W",
/*flr*/		"\0339",
/*bdon*/	"\033+",
/*bdoff*/	"\033,",
/*ploton*/	"\033]A\033]P",
/*plotoff*/	"\033]J\033]W",
/*up*/		"\0339",
/*down*/	"\033ZA",
/*right*/	" ",
/*left*/	"\b",
/*codetab*/	{
"\001 ",	/*space*/
"\001!",	/*!*/
"\001\242'\b\204'\b\242", /*"*/
"\001#",	/*#*/
"\001S\b|",	/*$*/
"\001%",	/*%*/
"\001\016N\017\b|", /*&*/
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
"\001:\b,",	/*;*/
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
"\001\016J\017", /*\*/
"\001]",	/*]*/
"\001^",	/*^*/
"\001_",	/*_ dash*/
"\001'",	/*` open*/
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
"\001\344\246\016<\017\304\246",	/* ~ */
"\000\0",	/*nar sp*/
"\001-",	/*hyphen*/
"\001o\b+",	/*bullet*/
"\002\200[\302\204-\344\241-\302\204]\201",	 /*square*/
"\001-",	/*3/4 em*/
"\001_",	/*rule*/
"\0031/4",	/*1/4*/
"\0031/2",	/*1/2*/
"\0033/4",	/*3/4*/
"\001-",	/*minus*/
"\202fi",	/*fi*/
"\202fl",	/*fl*/
"\202ff", 	/*ff*/
"\203ffi",	/*ffi*/
"\203ffl",	/*ffl*/
"\001\200\016\120\017\241",	/*degree*/
"\001\200|\342\241-\302\241",	/*dagger*/
"\001\200s\342s\302\242",	/* section*/
"\001'",	/*foot mark*/
"\001'",	/*acute accent*/
"\001'",	/*grave accent*/
"\001_",	/*underrule*/
"\001/",	/*slash (longer)*/
"\000\0",	/*half narrow space*/
"\001 ",	/*unpaddable space*/
"\001\016S\017",			/*alpha*/
"\001\016\046\017",			/*beta*/
"\001\016\107\017",			/*gamma*/
"\001\016\113\017",			/*delta*/
"\001\016N\017",			/*epsilon*/
"\001\200(\302\241c\342\241",		/*zeta*/
"\001\016L\017",			/*eta*/
"\001O\b-",				/*theta*/
"\001i",				/*iota*/
"\001k",				/*kappa*/
"\001\016B\017",			/*lambda*/
"\001;",				/*mu*/
"\001\200(\203/\245",			/*nu*/
"\001\016D\017",			/*xi*/
"\001o",				/*omicron*/
"\001\"",				/*pi*/
"\001\016F\017",			/*rho*/
"\001\016V\017",			/*sigma*/
"\001\016C\017",			/*tau*/
"\001v",				/*upsilon*/
"\001\200/\341\241o\301\241",		/*phi*/
"\001x",				/*chi*/
"\001\200/\241--\343\247,\213,\303\250", /*psi*/
"\001\016X\017",			/*omega*/
"\001\200\140\346_\306\205'\250",	/*Gamma*/
"\001\016A\017",			/*Delta*/
"\001O\b=",				/*Theta*/
"\001\243/\b\205\016J\017\b\242",	/*Lambda*/
"\001\201-\341\242___\345\243___\306\243", /*Xi*/
"\001\200I\203I\347\243_\307\243",	/*Pi*/
"\001\200>\341_\345\241_\306\242",	/*Sigma*/
"\000\0",				/**/
"\001Y",				/*Upsilon*/
"\001\200|\341\241O\241_\347\241_\310\241", /*Phi*/
"\001\200-\202][\202-\254'\215'\253",	/*Psi*/
"\001\134",				/*Omega*/
"\001\200v\341\203/\301\245",		/*square root*/
"\000\0",				/*terminal sigma*/
"\001\347_\307\241",			/*root en*/
"\001>\b_",				/*>=*/
"\001<\b_",				/*<=*/
"\001\341_\342\241_\342\241_\306\241",	/*identically equal*/
"\001-",				/*equation minus*/
"\001\200=\241\343\016<\017\303\241",	/*approx =*/
"\001~",				/*approximates*/
"\001=\b/",				/*not equal*/
"\002\200-\204-\202>\204",		/*right arrow*/
"\002\200<\202-\204-\204",		/*left arrow*/
"\001\016\132\017",			/*up arrow*/
"\001\016\136\017",			/*down arrow*/
"\001=",				/*equation equal*/
"\001x",				/*multiply*/
"\001\345.\301\241_\304\241.\241",	/*divide*/
"\001+\b_",				/*plus-minus*/
"\001U",				/*cup (union)*/
"\001\200\140\203\136\245",		/*cap (intersection)*/
#if 0
"\001\200(\341\206_\345\241_\306\250",		/*subset of*/
"\001\341_\345\241_\306\207)\251",		/*superset of*/
"\001\200(\341\206_\345\241_\307\241_\341\250",	/*improper subset*/
"\001\301_\342\241_\345\241_\306\207)\251",	/*improper superset*/
#endif
"\001\200<\341\207_\344\241_\305\251",		/*subset of*/
"\001\341_\344\241_\305\207>\251",		/*superset of*/
"\001\200<\341\206_\344\241_\306\241_\341\250",	/*improper subset*/
"\001\301_\342\241_\344\241_\305\207>\251",	/*improper superset*/
"\001\016_\017",			/*infinity*/
"\001\016M\017",			/*partial derivative*/
"\001\200\016J\017\205/\347\245_\307\243", /*gradient*/
"\001\346_\306\204'\246",		/*not*/
"\001$",				/*integral sign*/
"\001\016\135\017",			/*proportional to*/
"\001\200O\241/\241",			/*empty set*/
"\001\016N\017",			/*member of*/
"\001+",				/*equation plus*/
"\003(R)",				/*registered*/
"\003(C)",				/*copyright*/
"\001|",				/*box rule */
"\001\342C|\302\241|\242",		/*cent sign*/
"\001\302+\344\241+\302\241",		/*dbl dagger*/
"\002=>",				/*right hand*/
"\002<=",				/*left hand*/
"\001*",				/*math star*/
"\000\0",				/*bell system sign*/
"\001|",				/*or (was star)*/
"\001O",				/*circle*/
"\001\016\110\017",			/*left top of big brace*/
"\001|",				/*left bot of big brace*/
"\001|",				/*right top of big brace*/
"\001\100",				/*right bot of big brace*/
"\001|",				/*left center of big brace*/
"\001|",				/*right center of big brace*/
"\001\016\174\017",			/*bold vertical*/
"\001\202\016>\017\243",		/*left floor (lb of big bracket)*/
"\001\242\016@\017\201",		/*right	floor (rb of big bracket)*/
"\001\202`\243",			/*left ceiling (lt of big bracket)*/
"\001\242^\201",			/*right	ceiling (rt of big bracket)*/
 },
 0
};
