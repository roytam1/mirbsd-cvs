/* $MirOS: src/gnu/usr.bin/rcs/src/rcsbase.h,v 1.3 2005/06/05 16:08:49 tg Exp $ */

/* RCS common definitions and data structures */

#define RCSBASE "$MirOS: src/gnu/usr.bin/rcs/src/rcsbase.h,v 1.3 2005/06/05 16:08:49 tg Exp $"

/* Copyright 1982, 1988, 1989 Walter F. Tichy, Purdue CS
   Copyright 1990, 1991, 1992, 1993, 1994, 1995 Paul Eggert
   Distributed under license by the Free Software Foundation, Inc.

This file is part of RCS.

RCS is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

RCS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with RCS; see the file COPYING.
If not, write to the Free Software Foundation,
59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

Report problems and direct all questions to:

    rcs-bugs@cs.purdue.edu

*/

/*
 * $Log$
 * Revision 5.20  1995/06/16 06:19:24  eggert
 * Update FSF address.
 *
 * Revision 5.19  1995/06/01 16:23:43  eggert
 * (SIZEABLE_PATH): Don't depend on PATH_MAX: it's not worth configuring.
 * (Ioffset_type,BINARY_EXPAND,MIN_UNEXPAND,MIN_UNCHANGED_EXPAND): New macros.
 * (maps_memory): New macro; replaces many instances of `has_mmap'.
 * (cacheptr): Renamed from cachetell.
 * (struct RILE): New alternate name for RILE; the type is now recursive.
 * (deallocate): New member for RILE, used for generic buffer deallocation.
 * (cacheunget_): No longer take a failure arg; just call Ierror on failure.
 * (struct rcslock): Renamed from struct lock, to avoid collisions with
 * system headers on some hosts.  All users changed.
 * (basefilename): Renamed from basename, likewise.
 * (dirtpname): Remove; no longer external.
 * (dirlen, dateform): Remove; no longer used.
 * (cmpdate, fopenSafer, fdSafer, readAccessFilenameBuffer): New functions.
 * (zonelenmax): Increase to 9 for full ISO 8601 format.
 * (catchmmapints): Depend on has_NFS.
 *
 * Revision 5.18  1994/03/17 14:05:48  eggert
 * Add primitives for reading backwards from a RILE;
 * this is needed to go back and find the $Log prefix.
 * Specify subprocess input via file descriptor, not file name.  Remove lint.
 *
 * Revision 5.17  1993/11/09 17:40:15  eggert
 * Move RCS-specific time handling into rcstime.c.
 * printf_string now takes two arguments, alas.
 *
 * Revision 5.16  1993/11/03 17:42:27  eggert
 * Don't arbitrarily limit the number of joins.  Remove `nil'.
 * Add Name keyword.  Don't discard ignored phrases.
 * Add support for merge -A vs -E, and allow up to three labels.
 * Improve quality of diagnostics and prototypes.
 *
 * Revision 5.15  1992/07/28  16:12:44  eggert
 * Statement macro names now end in _.
 *
 * Revision 5.14  1992/02/17  23:02:22  eggert
 * Add -T support.  Work around NFS mmap SIGBUS problem.
 *
 * Revision 5.13  1992/01/24  18:44:19  eggert
 * Add support for bad_creat0.  lint -> RCS_lint
 *
 * Revision 5.12  1992/01/06  02:42:34  eggert
 * while (E) ; -> while (E) continue;
 *
 * Revision 5.11  1991/10/07  17:32:46  eggert
 * Support piece tables even if !has_mmap.
 *
 * Revision 5.10  1991/09/24  00:28:39  eggert
 * Remove unexported functions.
 *
 * Revision 5.9  1991/08/19  03:13:55  eggert
 * Add piece tables and other tuneups, and NFS workarounds.
 *
 * Revision 5.8  1991/04/21  11:58:20  eggert
 * Add -x, RCSINIT, MS-DOS support.
 *
 * Revision 5.7  1991/02/28  19:18:50  eggert
 * Try setuid() if seteuid() doesn't work.
 *
 * Revision 5.6  1991/02/26  17:48:37  eggert
 * Support new link behavior.  Move ANSI C / Posix declarations into conf.sh.
 *
 * Revision 5.5  1990/12/04  05:18:43  eggert
 * Use -I for prompts and -q for diagnostics.
 *
 * Revision 5.4  1990/11/01  05:03:35  eggert
 * Don't assume that builtins are functions; they may be macros.
 * Permit arbitrary data in logs.
 *
 * Revision 5.3  1990/09/26  23:36:58  eggert
 * Port wait() to non-Posix ANSI C hosts.
 *
 * Revision 5.2  1990/09/04  08:02:20  eggert
 * Don't redefine NAME_MAX, PATH_MAX.
 * Improve incomplete line handling.  Standardize yes-or-no procedure.
 *
 * Revision 5.1  1990/08/29  07:13:53  eggert
 * Add -kkvl.  Fix type typos exposed by porting.  Clean old log messages too.
 *
 * Revision 5.0  1990/08/22  08:12:44  eggert
 * Adjust ANSI C / Posix support.  Add -k, -V, setuid.  Don't call access().
 * Remove compile-time limits; use malloc instead.
 * Ansify and Posixate.  Add support for ISO 8859.
 * Remove snoop and v2 support.
 *
 * Revision 4.9  89/05/01  15:17:14  narten
 * botched previous USG fix 
 * 
 * Revision 4.8  89/05/01  14:53:05  narten
 * changed #include <strings.h> -> string.h for USG systems.
 * 
 * Revision 4.7  88/11/08  15:58:45  narten
 * removed defs for functions loaded from libraries
 * 
 * Revision 4.6  88/08/09  19:12:36  eggert
 * Shrink stdio code size; remove lint; permit -Dhshsize=nn.
 * 
 * Revision 4.5  87/12/18  17:06:41  narten
 * made removed BSD ifdef, now uses V4_2BSD
 * 
 * Revision 4.4  87/10/18  10:29:49  narten
 * Updating version numbers
 * Changes relative to 1.1 are actually relative to 4.2
 * 
 * Revision 1.3  87/09/24  14:02:25  narten
 * changes for lint
 * 
 * Revision 1.2  87/03/27  14:22:02  jenkins
 * Port to suns
 * 
 * Revision 4.2  83/12/20  16:04:20  wft
 * merged 3.6.1.1 and 4.1 (SMALLOG, logsize).
 * moved setting of STRICT_LOCKING to Makefile.
 * changed DOLLAR to UNKN (conflict with KDELIM).
 * 
 * Revision 4.1  83/05/04  09:12:41  wft
 * Added markers Id and RCSfile.
 * Added Dbranch for default branches.
 * 
 * Revision 3.6.1.1  83/12/02  21:56:22  wft
 * Increased logsize, added macro SMALLOG.
 * 
 * Revision 3.6  83/01/15  16:43:28  wft
 * 4.2 prerelease
 * 
 * Revision 3.6  83/01/15  16:43:28  wft
 * Replaced dbm.h with BYTESIZ, fixed definition of rindex().
 * Added variants of NCPFN and NCPPN for bsd 4.2, selected by defining V4_2BSD.
 * Added macro DELNUMFORM to have uniform format for printing delta text nodes.
 * Added macro DELETE to mark deleted deltas.
 *
 * Revision 3.5  82/12/10  12:16:56  wft
 * Added two forms of DATEFORM, one using %02d, the other %.2d.
 *
 * Revision 3.4  82/12/04  20:01:25  wft
 * added LOCKER, Locker, and USG (redefinition of rindex).
 *
 * Revision 3.3  82/12/03  12:22:04  wft
 * Added dbm.h, stdio.h, RCSBASE, RCSSEP, RCSSUF, WORKMODE, TMPFILE3,
 * PRINTDATE, PRINTTIME, map, and ctab; removed Suffix. Redefined keyvallength
 * using NCPPN. Changed putc() to abort on write error.
 *
 * Revision 3.2  82/10/18  15:03:52  wft
 * added macro STRICT_LOCKING, removed RCSUMASK.
 * renamed JOINFILE[1,2] to JOINFIL[1,2].
 *
 * Revision 3.1  82/10/11  19:41:17  wft
 * removed NBPW, NBPC, NCPW.
 * added typdef int void to aid compiling
 */


#include "conf.h"


#define EXIT_TROUBLE DIFF_TROUBLE

#ifdef _POSIX_PATH_MAX
#	define SIZEABLE_PATH _POSIX_PATH_MAX
#else
#	define SIZEABLE_PATH 255 /* size of a large path; not a hard limit */
#endif

/* for traditional C hosts with unusual size arguments */
#define Fread(p,s,n,f)  fread(p, (size_t)(s), (size_t)(n), f)
#define Fwrite(p,s,n,f)  fwrite(p, (size_t)(s), (size_t)(n), f)


/*
 * Parameters
 */

/* backwards compatibility with old versions of RCS */
#define VERSION_min 3		/* old output RCS format supported */
#define VERSION_max 5		/* newest output RCS format supported */
#ifndef VERSION_DEFAULT		/* default RCS output format */
#	define VERSION_DEFAULT VERSION_max
#endif
#define VERSION(n) ((n) - VERSION_DEFAULT) /* internally, 0 is the default */

#ifndef STRICT_LOCKING
#define STRICT_LOCKING 1
#endif
			      /* 0 sets the default locking to non-strict;  */
                              /* used in experimental environments.         */
                              /* 1 sets the default locking to strict;      */
                              /* used in production environments.           */

#define yearlength	   16 /* (good through AD 9,999,999,999,999,999)    */
#define datesize (yearlength+16)	/* size of output of time2date */
#define RCSTMPPREFIX '_' /* prefix for temp files in working dir  */
#define KDELIM            '$' /* delimiter for keywords                     */
#define VDELIM            ':' /* separates keywords from values             */
#define DEFAULTSTATE    "Exp" /* default state of revisions                 */



#define true     1
#define false    0


/*
 * RILE - readonly file
 * declarecache; - declares local cache for RILE variable(s)
 * setupcache - sets up the local RILE cache, but does not initialize it
 * cache, uncache - caches and uncaches the local RILE;
 *	(uncache,cache) is needed around functions that advance the RILE pointer
 * Igeteof_(f,c,s) - get a char c from f, executing statement s at EOF
 * cachegeteof_(c,s) - Igeteof_ applied to the local RILE
 * Iget_(f,c) - like Igeteof_, except EOF is an error
 * cacheget_(c) - Iget_ applied to the local RILE
 * cacheunget_(f,c,s) - read c backwards from cached f, executing s at BOF
 * Ifileno, Ioffset_type, Irewind, Itell - analogs to stdio routines
 *
 * By conventions, macros whose names end in _ are statements, not expressions.
 * Following such macros with `; else' results in a syntax error.
 */

#define maps_memory (has_map_fd || has_mmap)

	typedef unsigned char const *Iptr_type;
	typedef struct RILE {
		Iptr_type ptr, lim;
		unsigned char *base; /* not Iptr_type for lint's sake */
		unsigned char *readlim;
		int fd;
			void (*deallocate)(struct RILE *);
	} RILE;
#		define declarecache register Iptr_type ptr, lim
#		define setupcache(f) (lim = (f)->lim)
#		define Igeteof_(f,c,s) if ((f)->ptr==(f)->lim) s else (c)= *(f)->ptr++;
#		define cachegeteof_(c,s) if (ptr==lim) s else (c)= *ptr++;
#	define uncache(f) ((f)->ptr = ptr)
#	define cache(f) (ptr = (f)->ptr)
#	define Iget_(f,c) Igeteof_(f,c,Ieof();)
#	define cacheget_(c) cachegeteof_(c,Ieof();)
#	define cacheunget_(f,c) (c)=(--ptr)[-1];
#	define Ioffset_type size_t
#	define Itell(f) ((f)->ptr - (f)->base)
#	define Irewind(f) ((f)->ptr = (f)->base)
#	define cacheptr() ptr
#	define Ifileno(f) ((f)->fd)

/* Print a char, but abort on write error.  */
#define aputc_(c,o) { if (putc(c,o)==EOF) testOerror(o); }

/* Get a character from an RCS file, perhaps copying to a new RCS file.  */
#define GETCeof_(o,c,s) { cachegeteof_(c,s) if (o) aputc_(c,o) }
#define GETC_(o,c) { cacheget_(c) if (o) aputc_(c,o) }


#define WORKMODE(RCSmode, writable) (((RCSmode)&(mode_t)~(S_IWUSR|S_IWGRP|S_IWOTH)) | ((writable)?S_IWUSR:0))
/* computes mode of working file: same as RCSmode, but write permission     */
/* determined by writable */


/* character classes and token codes */
enum tokens {
/* classes */	DELIM,	DIGIT,	IDCHAR,	NEWLN,	LETTER,	Letter,
		PERIOD,	SBEGIN,	SPACE,	UNKN,
/* tokens */	COLON,	ID,	NUM,	SEMI,	STRING
};

#define SDELIM  '@'     /* the actual character is needed for string handling*/
/* SDELIM must be consistent with ctab[], so that ctab[SDELIM]==SBEGIN.
 * there should be no overlap among SDELIM, KDELIM, and VDELIM
 */

#define isdigit(c) (((unsigned)(c)-'0') <= 9) /* faster than ctab[c]==DIGIT */





/***************************************
 * Data structures for the symbol table
 ***************************************/

/* Buffer of arbitrary data */
struct buf {
	char *string;
	size_t size;
};
struct cbuf {
	char const *string;
	size_t size;
};

/* Hash table entry */
struct hshentry {
	char const	  * num;      /* pointer to revision number (ASCIZ) */
	char const	  * date;     /* pointer to date of checkin	    */
	char const	  * author;   /* login of person checking in	    */
	char const	  * lockedby; /* who locks the revision		    */
	char const	  * state;    /* state of revision (Exp by default) */
	char const	  * name;     /* name (if any) by which retrieved   */
	char const	  * commitid; /* unique commit ID (CVS extension)   */
	struct cbuf	    log;      /* log message requested at checkin   */
        struct branchhead * branches; /* list of first revisions on branches*/
	struct cbuf	    ig;	      /* ignored phrases in admin part	    */
	struct cbuf	    igtext;   /* ignored phrases in deltatext part  */
        struct hshentry   * next;     /* next revision on same branch       */
	struct hshentry   * nexthsh;  /* next revision with same hash value */
	long		    insertlns;/* lines inserted (computed by rlog)  */
	long		    deletelns;/* lines deleted  (computed by rlog)  */
	char		    selector; /* true if selected, false if deleted */
};

/* list of hash entries */
struct hshentries {
	struct hshentries *rest;
	struct hshentry *first;
};

/* list element for branch lists */
struct branchhead {
        struct hshentry   * hsh;
        struct branchhead * nextbranch;
};

/* accesslist element */
struct access {
	char const	  * login;
        struct access     * nextaccess;
};

/* list element for locks  */
struct rcslock {
	char const	  * login;
        struct hshentry   * delta;
	struct rcslock    * nextlock;
};

/* list element for symbolic names */
struct assoc {
	char const	  * symbol;
	char const	  * num;
        struct assoc      * nextassoc;
};

/*
 * Markers for keyword expansion (used in co and ident)
 *	Every byte must have class LETTER or Letter.
 */
#define AUTHOR          "Author"
#define DATE            "Date"
#define HEADER          "Header"
#define IDH             "Id"
#define LOCKER          "Locker"
#define LOG             "Log"
#define NAME		"Name"
#define RCSFILE         "RCSfile"
#define REVISION        "Revision"
#define SOURCE          "Source"
#define STATE           "State"
#define keylength	12	/* max length of any of the above keywords */

enum markers { Nomatch, Author, Date, Header, Id,
	       Locker, Log, Name, RCSfile, Revision, Source, State, LocalId };
	/* This must be in the same order as rcskeys.c's Keyword[] array. */

#define DELNUMFORM      "\n\n%s\n%s\n"
/* used by putdtext and scanlogtext */

#define EMPTYLOG "*** empty log message ***" /* used by ci and rlog */

/* main program */
extern char const cmdid[];
__dead void exiterr(void);

/* merge */
int merge(int,char const*,char const*const[3],char const*const[3]);

/* rcsedit */
#define ciklogsize 23 /* sizeof("checked in with -k by ") */
extern FILE *fcopy;
extern char const *resultname;
extern char const ciklog[ciklogsize];
extern int locker_expansion;
RILE *rcswriteopen(struct buf*,struct stat*,int);
char const *makedirtemp(int);
char const *getcaller(void);
int addlock(struct hshentry*,int);
int addsymbol(char const*,char const*,int);
int checkaccesslist(void);
int chnamemod(FILE**,char const*,char const*,int,mode_t,time_t);
int donerewrite(int,time_t);
int dorewrite(int,int);
int expandline(RILE*,FILE*,struct hshentry const*,int,FILE*,int);
int findlock(int,struct hshentry**);
int setmtime(char const*,time_t);
void ORCSclose(void);
void ORCSerror(void);
void copystring(void);
void dirtempunlink(void);
void enterstring(void);
void finishedit(struct hshentry const*,FILE*,int);
void keepdirtemp(char const*);
void openfcopy(FILE*);
void snapshotedit(FILE*);
void xpandstring(struct hshentry const*);
#if has_NFS || bad_unlink
	int un_link(char const*);
#else
#	define un_link(s) unlink(s)
#endif
	void edit_string(void);
#	define editstring(delta) edit_string()

/* rcsfcmp */
int rcsfcmp(RILE*,struct stat const*,char const*,struct hshentry const*);

/* rcsfnms */
#define bufautobegin(b) clear_buf(b)
#define clear_buf(b) (((b)->string = 0, (b)->size = 0))
extern FILE *workstdout;
extern char *workname;
extern char const *RCSname;
extern char const *suffixes;
extern int fdlock;
extern struct stat RCSstat;
RILE *rcsreadopen(struct buf*,struct stat*,int);
char *bufenlarge(struct buf*,char const**);
char const *basefilename(char const*);
char const *getfullRCSname(void);
char const *maketemp(int);
char const *rcssuffix(char const*);
int pairnames(int,char**,RILE*(*)(struct buf*,struct stat*,int),int,int);
struct cbuf bufremember(struct buf*,size_t);
void bufalloc(struct buf*,size_t);
void bufautoend(struct buf*);
void bufrealloc(struct buf*,size_t);
void bufscat(struct buf*,char const*);
void bufscpy(struct buf*,char const*);
void tempunlink(void);

/* rcsgen */
extern int interactiveflag;
extern struct buf curlogbuf;
char const *buildrevision(struct hshentries const*,struct hshentry*,FILE*,int);
int getcstdin(void);
int putdtext(struct hshentry const*,char const*,FILE*,int);
int ttystdin(void);
int yesorno(int,char const*,...) __attribute__((format(printf, 2, 3)));
struct cbuf cleanlogmsg(char*,size_t);
struct cbuf getsstdin(char const*,char const*,char const*,struct buf*);
void putdesc(int,char*);
void putdftext(struct hshentry const*,RILE*,FILE*,int);

/* rcskeep */
extern int prevkeys;
extern struct buf prevauthor, prevdate, prevname, prevrev, prevstate;
int getoldkeys(RILE*);

/* rcskeys */
extern char const *Keyword[];
extern int onlyRCSlocalId;
void setRCSlocalId(char const *);
enum markers trymatch(char const*);

/* rcslex */
extern FILE *foutptr;
extern FILE *frewrite;
extern RILE *finptr;
extern char const *NextString;
extern enum tokens nexttok;
extern int hshenter;
extern int nerror;
extern int nextc;
extern int quietflag;
extern long rcsline;
char const *getid(void);
__dead void efaterror(char const*);
__dead void enfaterror(int,char const*);
__dead void fatcleanup(int);
__dead void faterror(char const*,...) __attribute__((format(printf, 1, 2)));
__dead void fatserror(char const*,...) __attribute__((format(printf, 1, 2)));
__dead void rcsfaterror(char const*,...) __attribute__((format(printf, 1, 2)));
__dead void Ieof(void);
__dead void Ierror(void);
__dead void Oerror(void);
char *checkid(char*,int);
char *checksym(char*,int);
int eoflex(void);
int getkeyopt(char const*);
int getlex(enum tokens);
struct cbuf getphrases(char const*);
struct cbuf savestring(struct buf*);
struct hshentry *getnum(void);
void Ifclose(RILE*);
void Izclose(RILE**);
void Lexinit(void);
void Ofclose(FILE*);
void Orewind(FILE*);
void Ozclose(FILE**);
void aflush(FILE*);
void afputc(int,FILE*);
void aprintf(FILE*,char const*,...) __attribute__((format(printf, 2, 3)));
void aputs(char const*,FILE*);
void checksid(char*);
void checkssym(char*);
void diagnose(char const*,...) __attribute__((format(printf, 1, 2)));
void eerror(char const*);
void eflush(void);
void enerror(int,char const*);
void error(char const*,...) __attribute__((format(printf, 1, 2)));
void fvfprintf(FILE*,char const*,va_list);
void getkey(char const*);
void getkeystring(char const*);
void nextlex(void);
void oflush(void);
void printstring(void);
void readstring(void);
void redefined(int);
void rcserror(char const*,...) __attribute__((format(printf, 1, 2)));
void rcswarn(char const*,...) __attribute__((format(printf, 1, 2)));
void testIerror(FILE*);
void testOerror(FILE*);
void warn(char const*,...) __attribute__((format(printf, 1, 2)));
void warnignore(void);
void workerror(char const*,...) __attribute__((format(printf, 1, 2)));
void workwarn(char const*,...) __attribute__((format(printf, 1, 2)));
	void advise_access(RILE*,int);
#	define if_advise_access(p,f,advice) if (p) advise_access(f,advice)
	RILE *I_open(char const*,struct stat*);
#	define Iopen(f,m,s) I_open(f,s)

/* rcsmap */
extern enum tokens const ctab[];

/* rcsrev */
char *partialno(struct buf*,char const*,int);
char const *namedrev(char const*,struct hshentry*);
char const *tiprev(void);
int cmpdate(char const*,char const*);
int cmpnum(char const*,char const*);
int cmpnumfld(char const*,char const*,int);
int compartial(char const*,char const*,int);
int expandsym(char const*,struct buf*);
int fexpandsym(char const*,struct buf*,RILE*);
struct hshentry *genrevs(char const*,char const*,char const*,char const*,struct hshentries**);
int countnumflds(char const*);
void getbranchno(char const*,struct buf*);

/* rcssyn */
/* These expand modes must agree with Expand_names[] in rcssyn.c.  */
#define KEYVAL_EXPAND 0 /* -kkv `$Keyword: value $' */
#define KEYVALLOCK_EXPAND 1 /* -kkvl `$Keyword: value locker $' */
#define KEY_EXPAND 2 /* -kk `$Keyword$' */
#define VAL_EXPAND 3 /* -kv `value' */
#define OLD_EXPAND 4 /* -ko use old string, omitting expansion */
#define BINARY_EXPAND 5 /* -kb like -ko, but use binary mode I/O */
#define MIN_UNEXPAND OLD_EXPAND /* min value for no logical expansion */
#define MIN_UNCHANGED_EXPAND OLD_EXPAND
			/* min value guaranteed to yield an identical file */
struct diffcmd {
	long
		line1, /* number of first line */
		nlines, /* number of lines affected */
		adprev, /* previous 'a' line1+1 or 'd' line1 */
		dafter; /* sum of previous 'd' line1 and previous 'd' nlines */
};
extern char const      * Dbranch;
extern struct access   * AccessList;
extern struct assoc    * Symbols;
extern struct cbuf Comment;
extern struct cbuf Ignored;
extern struct rcslock *Locks;
extern struct hshentry * Head;
extern int		 Expand;
extern int               StrictLocks;
extern int               TotalDeltas;
extern char const *const expand_names[];
extern char const
	Kaccess[], Kauthor[], Kbranch[], Kcomment[], Kcommitid[],
	Kdate[], Kdesc[], Kexpand[], Khead[], Klocks[], Klog[],
	Knext[], Kstate[], Kstrict[], Ksymbols[], Ktext[];
__dead void unexpected_EOF(void);
int getdiffcmd(RILE*,int,FILE*,struct diffcmd*);
int str2expmode(char const*);
void getadmin(void);
void getdesc(int);
void gettree(void);
void ignorephrases(char const*);
void initdiffcmd(struct diffcmd*);
void putadmin(void);
void putstring(FILE*,int,struct cbuf,int);
void puttree(struct hshentry const*,FILE*);

/* rcstime */
#define zonelenmax 9 /* maxiumum length of time zone string, e.g. "+12:34:56" */
char const *date2str(char const[datesize],char[datesize + zonelenmax]);
time_t date2time(char const[datesize]);
void str2date(char const*,char[datesize]);
void time2date(time_t,char[datesize]);
#define zone_set(x) /* nothing */

/* rcsutil */
extern int RCSversion;
FILE *fopenSafer(char const*,char const*);
char *cgetenv(char const*);
char *fstr_save(char const*);
char *str_save(char const*);
char const *getusername(int);
int fdSafer(int);
int getRCSINIT(int,char**,char***);
int run(int,char const*,...);
int runv(int,char const*,char const**);
void *fremember(void *);
void *ftestalloc(size_t);
void *testalloc(size_t);
void *testrealloc(void *,size_t);
#define ftalloc(T) ftnalloc(T,1)
#define talloc(T) tnalloc(T,1)
#define ftnalloc(T,n) ((T*) ftestalloc(sizeof(T)*(n)))
#define tnalloc(T,n) ((T*) testalloc(sizeof(T)*(n)))
#define trealloc(T,p,n) ((T*) testrealloc((void *)(p), sizeof(T)*(n)))
#define tfree(p) free((void *)(p))
time_t now(void);
void awrite(char const*,size_t,FILE*);
void fastcopy(RILE*,FILE*);
void ffree(void);
void ffree1(char const*);
void setRCSversion(char const*);
#if has_signal
	void catchints(void);
	void ignoreints(void);
	void restoreints(void);
#else
#	define catchints()
#	define ignoreints()
#	define restoreints()
#endif
	void catchmmapints(void);
	void readAccessFilenameBuffer(char const*,unsigned char const*);
	uid_t ruid(void);
#	define myself(u) ((u) == ruid())
	uid_t euid(void);
	void nosetid(void);
	void seteid(void);
	void setrid(void);

/* version */
extern char const RCS_version_string[];
