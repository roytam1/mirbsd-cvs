/*-
 * Copyright (c) 2006
 *	Thorsten "mirabile" Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a nontrivial bug.
 */

/* An ircII-like split-screen front end
   Copyright (C) 1995 Roger Espel Llima

   Started: 17 Feb 95 by orabidoo <roger.espel.llima@ens.fr>
   Latest modification: 7 June 97

   To compile: gcc ssfe.c -o ssfe -ltermcap

   If it doesn't work, try gcc ssfe.c -o ssfe -lcurses
   or try cc, acc or c89 instead of gcc, or -lncurses.

   Use: ssfe [options] program arguments

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation. See the file
   /usr/share/doc/legal/COPYING-2 for details.

   Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
   express, or implied, to the maximum extent permitted by applicable
   law, without malicious intent or gross negligence; in no event may
   licensor, an author or contributor be held liable for any indirect
   or other damage, or direct damage except proven a consequence of a
   direct error of said person and intended use of this work, loss or
   other issues arising in any way out of its use, even if advised of
   the possibility of such damage or existence of a nontrivial bug.
*/

#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#ifdef USE_SGTTY
#include <sgtty.h>
#elif defined(USE_TERM)
#include <term.h>
#else
#include <termios.h>
#endif

#include <sys/ioctl.h>

#ifdef _AIX
#include <sys/select.h>
#endif

#ifndef __RCSID
#define	__RCSID(x)	static const char __rcsid[] __attribute__((used)) = (x)
#endif

__RCSID("$MirOS: ports/comms/ssfe/dist/ssfe.c,v 1.5 2005/12/18 16:38:20 tg Exp $");

#define BUF_SIZE 4096
#define MAX_COLS 4096

unsigned char *statusline;
int ystatus, yinput;     /* line number of the status line, input line */

int ttyfd;
#ifdef TIOCGWINSZ
struct winsize wsz;
#endif

#ifdef USE_SGTTY
struct sgttyb term, term0;
struct tchars tch, tch0;
struct ltchars lch, lch0;
#else
struct termios term, term0;
#endif

int pid, mypid;
int i;
int Cols, Lines;
int readfd, writefd, errfd;

unsigned char *t, *w;
unsigned char tmpstr[BUF_SIZE], extrainput[BUF_SIZE+20], readbuf[2*BUF_SIZE],
	      *input, *writebuf, o_buffer[BUF_SIZE];
int bold=0, inv=0, under=0, wherex=0, wherey=0, donl=0;
int hold_mode=0, hold_Lines=0, ctrlx=0, beep=0, flow=0;

unsigned char defprompt[]="> ",
	 nullstring[]="",
	 *prompt;
int plen=0, specialprompt=0, modified=1, no_echo=0;

#define MAX_TAB_LINES 20
struct tabinfo {
  unsigned char string[BUF_SIZE];
  struct tabinfo *prev, *next;
};
int tabLines=0;
struct tabinfo *curtabt=NULL, *curtabr=NULL, *oldest=NULL;

#define MAX_HIST_LINES 128
struct histinfo {
  unsigned char string[BUF_SIZE+20];
  int len, plen;
  struct histinfo *prev, *next;
};
int histLines=0;
struct histinfo *histcurrent=NULL, *histoldest=NULL;

char ctrl_t[128] = "/next\n";

unsigned char id[]="`#ssfe#", *inid=id, protcmd[BUF_SIZE], *wpc=protcmd;
int idstatus=0;  /* 0 looking for/in the word, 1 in the arguments */
#define ID_BACK "@ssfe@"

int rc, rrc, inputcursor, inputlast, inputofs, inarrow=0, quote=0;
int cursorwhere;     /* 0 = up, 1 = down, 2 = undef */
int dispmode=1; /* 0=raw, 1=wordwrap, 2=process ^b^v^_ */
int printmode=0;
int cutline=0;

char *termtype, termcap[1024], *tc, capabilities[2048];
char *t_cm, *t_cl, *t_mr, *t_md, *t_me, *t_cs, *t_ce, *t_us;
int ansi_cs = 0;

fd_set ready, result;
extern int errno;

#ifndef USE_TERM
#ifdef __GNUC__
extern unsigned char *tgoto(unsigned char *cm, int col, int line);
#else
extern unsigned char *tgoto();
#endif
#endif

#ifdef __GNUC__
int myputchar(int c) {
#else
int myputchar(c) {
#endif
  unsigned char cc=(unsigned char)c;
  return(write(1, &cc, 1));
}

#ifdef __GNUC__
int addchar(int c) {
#else
int addchar(c) {
#endif
  return (*w++)=(unsigned char)c;
}

#ifdef __GNUC__
void putcap(unsigned char *s) {
#else
void putcap(s)
unsigned char *s; {
#endif
  tputs(s, 0, myputchar);
}

#ifdef __GNUC__
void do_cs(int y1, int y2) {
#else
int do_cs(y1, y2) {
#endif
  static char temp[16];
  if (ansi_cs) {
    snprintf(temp, 16, "\e[%d;%dr", y1, y2);
    write(1, temp, strlen(temp));
  } else putcap((char *)tgoto(t_cs, y2-1, y1-1));
}

#ifdef __GNUC__
void writecap(unsigned char *s) {
#else
void writecap(s)
unsigned char *s; {
#endif
  tputs(s, 0, addchar);
}

#ifdef __GNUC__
void gotoxy(int x, int y) {
#else
void gotoxy(x, y) {
#endif
/* left upper = 0, 0 */
  putcap(tgoto(t_cm, x, y));
}

#define clearscreen() (putcap(t_cl))
#define cleareol() (putcap(t_ce))
#define fullscroll() (do_cs(0, 0))
#define winscroll() (do_cs(1, Lines-2))
#define setbold() (putcap(t_md))
#define setunder() (putcap(t_us))
#define setinv() (putcap(t_mr))
#define normal() (putcap(t_me))

#ifdef __GNUC__
void ofsredisplay(int x);
void inschar(unsigned char t);
void dokbdchar(unsigned char t);
#else
void ofsredisplay();
void inschar();
void dokbdchar();
#endif
void displaystatus();

#ifdef __GNUC__
void cleanupexit(int n, unsigned char *error) {
#else
void cleanupexit(n, error)
int n;
unsigned char *error; {
#endif
  normal();
  fullscroll();
  gotoxy(0, Lines-1);
  cleareol();
#ifdef USE_SGTTY
  ioctl(ttyfd, TIOCSETP, &term0);
  ioctl(ttyfd, TIOCSETC, &tch0);
  ioctl(ttyfd, TIOCSLTC, &lch0);
#else
  tcsetattr(ttyfd, TCSADRAIN, &term0);
#endif
  close(ttyfd);
  if (error!=NULL)
    fprintf(stderr, "%s\n", error);
  exit(n);
}

void allsigs();

void interrupted() {
  cleanupexit(1, "interrupted");
}

void sigpipe() {
  cleanupexit(1, "program died");
}

void sigcont() {
  allsigs();
#ifdef USE_SGTTY
  ioctl(ttyfd, TIOCSETP, &term);
  ioctl(ttyfd, TIOCSETC, &tch);
  ioctl(ttyfd, TIOCSLTC, &lch);
#else
  tcsetattr(ttyfd, TCSANOW, &term);
#endif
  wherex=0;
  wherey=ystatus-1;
  displaystatus();
  ofsredisplay(0);
}

void suspend() {
  normal();
  fullscroll();
  gotoxy(0, ystatus);
  cleareol();
#ifdef USE_SGTTY
  ioctl(ttyfd, TIOCSETP, &term0);
  ioctl(ttyfd, TIOCSETC, &tch0);
  ioctl(ttyfd, TIOCSLTC, &lch0);
#else
  tcsetattr(ttyfd, TCSANOW, &term0);
#endif
  kill(pid, SIGCONT);
  signal(SIGTSTP, SIG_DFL);
  signal(SIGCONT, sigcont);
  kill(mypid, SIGTSTP);
}

void sigwinch() {
#ifdef TIOCGWINSZ
  signal(SIGWINCH, sigwinch);
  if (ioctl(ttyfd, TIOCGWINSZ, &wsz)>=0 && wsz.ws_row>0 && wsz.ws_col>0) {
    Lines=wsz.ws_row;
    Cols=wsz.ws_col;
    cursorwhere=2;
    ystatus=Lines-2;
    yinput=Lines-1;
    wherex=0;
    wherey=ystatus-1;
    displaystatus();
    if (inputlast>Cols-8) {
      inputcursor=Cols-9;
      inputofs=inputlast-Cols+9;
    } else {
      inputofs=0;
      inputcursor=inputlast;
    }
    ofsredisplay(0);
  }
#endif
}

void allsigs() {
  signal(SIGHUP, interrupted);
  signal(SIGINT, interrupted);
  signal(SIGQUIT, SIG_IGN);
  signal(SIGPIPE, sigpipe);
  signal(SIGTSTP, suspend);
  signal(SIGCONT, sigcont);
#ifdef TIOCGWINSZ
  signal(SIGWINCH, sigwinch);
#endif
}

#ifdef __GNUC__
void setstatus(unsigned char *title) {
#else
void setstatus(title)
unsigned char *title; {
#endif
  unsigned char *t=title;
  for (;*t;t++) if (*t<' ') (*t)+='@';
  memset(statusline, ' ', MAX_COLS-1);
  memcpy(statusline, title, strlen(title)<MAX_COLS ? strlen(title) : MAX_COLS);
}

void displaystatus() {
  normal();
  fullscroll();
  gotoxy(0, ystatus);
  setinv();
  write(1, statusline, Cols-1);
  if (hold_mode) {
    gotoxy(Cols-4, ystatus);
    write(1, "(h)", 3);
  }
  cursorwhere=2;
  normal();
  cleareol();
}

#ifdef __GNUC__
int casecmp(unsigned char *s, unsigned char *t) {
#else
int casecmp(s, t)
unsigned char *s, *t; {
#endif
  while (((*s>='a' && *s<='z')?(*s)-32:*s)==
         ((*t>='a' && *t<='z')?(*t)-32:*t)) {
    if (*s=='\0') return 1;
    s++; t++;
  }
  return 0;
}

void addtab(unsigned char *line) {
  struct tabinfo *nt;

  nt=oldest;
  if (tabLines) do {
    if (casecmp(nt->string, line)) {
      strlcpy(nt->string, line, BUF_SIZE);
      if (nt==oldest) oldest=nt->prev;
      else {
	nt->prev->next=nt->next;
	nt->next->prev=nt->prev;
	nt->prev=oldest;
	nt->next=oldest->next;
	oldest->next=nt;
	nt->next->prev=nt;
      }
      curtabt=oldest->next;
      curtabr=oldest;
      return;
    }
    nt=nt->next;
  } while (nt!=oldest);

  if (!tabLines) {
    nt=(struct tabinfo *)malloc(sizeof (struct tabinfo));
    nt->prev=nt->next=curtabt=curtabr=oldest=nt;
    tabLines++;
  } else if (tabLines<MAX_TAB_LINES) {
    nt=(struct tabinfo *)malloc(sizeof (struct tabinfo));
    nt->prev=oldest;
    nt->next=oldest->next;
    oldest->next=nt;
    nt->next->prev=nt;
    tabLines++;
  } else {
    nt=oldest;
    oldest=nt->prev;
  }
  strlcpy(nt->string, line, BUF_SIZE);
  oldest=nt->prev;
  curtabt=oldest->next;
  curtabr=oldest;
}

void doprotcommand() {
  unsigned char *tmp;

  switch (protcmd[0]) {
    case 'i' : dispmode=2;	/* set irc mode, ack */
    	       bold=inv=under=0;
	       write(writefd, "@ssfe@i\n", 8);
	       break;
    case 'c' : dispmode=1;	/* set cooked mode, ack */
	       write(writefd, "@ssfe@c\n", 8);
    	       break;
    case 's' : setstatus(protcmd+1); /* set status */
    	       displaystatus();
    	       break;
    case 'T' : strncpy(ctrl_t, protcmd+1, 127); /* set ^t's text */
	       ctrl_t[126] = '\n';
	       ctrl_t[127] = '\0';
	       break;
    case 't' : addtab(protcmd+1); /* add tabkey entry */
    	       break;
    case 'l' : fullscroll(); /* clear screen */
	       normal();
	       clearscreen();
	       bold=inv=under=wherex=wherey=donl=0;
	       displaystatus();
	       ofsredisplay(0);
	       break;

    case 'P' : no_echo = 1;		    /* password prompt */
    case 'p' : if (strlen(protcmd+1)<=8) {  /* prompt something */
		 fullscroll();
		 if (!specialprompt) {
		   histcurrent->len=inputlast;
		   histcurrent->plen=plen;
		 }
		 input=extrainput;
		 strlcpy(input, protcmd+1, BUF_SIZE+20);
		 plen=strlen(input);
		 inputofs=0;
		 modified=specialprompt=1;
		 inputlast=inputcursor=plen;
		 ofsredisplay(0);
	       }
	       break;
    case 'n' : if (cursorwhere!=1) { /* type text */
		 normal();
		 fullscroll();
		 gotoxy(inputcursor, yinput);
		 cursorwhere=1;
	       }
	       for (tmp=protcmd+1; *tmp; tmp++) {
		 inschar(*tmp);
	       }
	       break;
    case 'o' : strlcpy(o_buffer, protcmd+1, BUF_SIZE);
    	       break;
  }
}

void Newline() {
  unsigned char t;
  hold_Lines++;
  if (hold_mode && hold_Lines>Lines-4) {
    normal();
    fullscroll();
    gotoxy(Cols-4, ystatus);
    setinv();
    write(1, "(H)", 3);
    while(1) {
      read(0, &t, 1);
      if (t==9) break;
      dokbdchar(t);
    }
    normal();
    fullscroll();
    gotoxy(Cols-4, ystatus);
    setinv();
    write(1, "(h)", 3);
    hold_Lines=0;
    normal();
    winscroll();
    gotoxy(Cols-1, wherey);
    if (bold) setbold();
    if (under) setunder();
    if (inv) setinv();
  }
}

#ifdef __GNUC__
void formatter(unsigned char *readbuf, int rc) {
#else
void formatter(readbuf, rc)
unsigned char *readbuf;
int rc; {
#endif

  unsigned char t, *r, *lwr, *lww, dtsc[255];
  int lwrc, lwbold = 0, lwunder = 0, lwinv = 0, lwx, dts;

  if ((readbuf[2] == ':') && (readbuf[5] > 0x7E)) {
    int i = 5, j;
    memset(dtsc, 0, sizeof (dtsc));
    strlcpy(dtsc, "\r\n     ", sizeof (dtsc));
    j = strlen(dtsc);
    while ((readbuf[i] > 0x7E) && (j < sizeof (dtsc)))
      dtsc[j++] = readbuf[i++];
    strlcat(dtsc, "    ", sizeof (dtsc));
  } else if ((readbuf[2] == ':') && (readbuf[5] == '|')) {
    strlcpy(dtsc, "\r\n     |    ", sizeof (dtsc));
  } else {
    strlcpy(dtsc, "\r\n          ", sizeof (dtsc));
  }
  if (cursorwhere!=0) {
    winscroll();
    gotoxy(wherex, wherey);
    cursorwhere=0;
  }
  if (donl) {
    Newline();
    write(1, "\r\n", 2);
    normal();
    wherex=0;
    bold=inv=under=lwbold=lwinv=lwunder=0;
    if (wherey<ystatus-1) wherey++;
  } else if (dispmode>1) {
    if (bold) setbold();
    if (under) setunder();
    if (inv) setinv();
    lwbold=bold;
    lwinv=inv;
    lwunder=under;
  }
  if (rc && readbuf[rc-1]=='\n') {
    rc--;
    donl=1; cutline=0;
  } else {
    donl=0;
    if (dispmode==0) cutline=1;
  }
  if (dispmode==0) {
    if (rc) write(1, readbuf, rc);
    normal();
    return;
  }
  lww=w=writebuf;
  lwr=r=readbuf;
  lwrc=rc;
  lwx=wherex;
  dts = strlen(dtsc) + 1;
  while(rc-->0) {
    t=(*r++);
    if (t=='\r') continue;
    if ((wherex>Cols-2) || ((t==9) && (wherex>((Cols-2)&0xfff8)))) {
      if (t==' ' || t==9) ;
      else if (lww>writebuf+Cols/2) {
	wherex=lwx; r=lwr; w=lww; rc=lwrc;
	bold=lwbold; inv=lwinv; under=lwunder; wherex=lwx;
      } else {
	rc++; r--;
      }
      write(1, writebuf, w-writebuf);
      Newline();
      write(1, dtsc, dts);
      w=writebuf;
      lwr=r; lww=w; lwrc=rc;
      lwbold=bold; lwinv=inv; lwunder=under;
      lwx=wherex=11;
      if (wherey<ystatus-1) wherey++;
      rc--; t=(*r++);
    }
    if (t=='\n') {
      if (w!=writebuf) write(1, writebuf, w-writebuf);
      Newline();
      write(1, "\r\n", 2);
      normal();
      w=writebuf;
      lwr=r; lww=w; lwrc=rc;
      lwbold=bold=lwinv=inv=lwunder=under=lwx=wherex=0;
      if (wherey<ystatus-1) wherey++;
    } else if (dispmode>1 &&
               ((t==2 && bold) || (t==22 && inv) || (t==31 && under))) {
      writecap(t_me);
      bold=under=inv=0;
    } else if (dispmode>1 && t==2) {
      writecap(t_md);
      bold=1;
    } else if (dispmode>1 && t==22) {
      writecap(t_mr);
      inv=1;
    } else if (dispmode>1 && t==31) {
      writecap(t_us);
      under=1;
    } else if (dispmode>1 && t==15) {
      if (bold || inv || under) writecap(t_me);
      bold=under=inv=0;
    } else if (t==9) {
      (*w++)=t;
      wherex=(wherex & 0xfff8)+8;
    } else if (t<' ' && (t!=7 || !beep)) {
      wherex++;
      if (inv) {
	writecap(t_me);
	(*w++)=(t+'@');
      } else {
	writecap(t_mr);
	(*w++)=(t+'@');
	writecap(t_me);
      }
      if (bold) writecap(t_md);
      if (inv) writecap(t_mr);
      if (under) writecap(t_us);
    } else {
      if (t!=7) wherex++;
      (*w++)=t;
    }
    if (t==' ' || t==9) {
      lwr=r; lww=w; lwrc=rc;
      lwbold=bold; lwinv=inv; lwunder=under;
      lwx=wherex;
    }
  }
  if (w!=writebuf) write(1, writebuf, w-writebuf);
}

#ifdef __GNUC__
void doprogramline(unsigned char *readbuf, int rc) {
#else
void doprogramline(readbuf, rc)
unsigned char *readbuf;
int rc; {
#endif

  unsigned char *w, *r, *r2, t;
  if (dispmode==0) {
    formatter(readbuf, rc);
    return;
  }
  w=r=readbuf;
  while(rc-->0) {
    t=(*r++);
    if (!idstatus) {
      if (*inid=='\0') {
	idstatus=1;
	wpc=protcmd;
	inid=id;
      } else if (*inid==t && (inid!=id || r==(readbuf+1) || *(r-2)=='\n')) {
	inid++;
	(*wpc++)=t;
      } else {
        r2=protcmd;
        while (r2!=wpc) (*w++)=(*r2++);
	(*w++)=t;
	wpc=protcmd;
	inid=id;
      }
    }
    if (idstatus==1) {
      if (t=='\n')  {
        *wpc='\0';
        doprotcommand();
	inid=id;
	wpc=protcmd;
	idstatus=0;
      } else (*wpc++)=t;
    }
  }
  if (w!=readbuf) formatter(readbuf, w-readbuf);
}

#ifdef __GNUC__
void write1(unsigned char t, int pos) {
#else
void write1(t, pos)
unsigned char t;
int pos; {
#endif
  if (no_echo && pos>=plen) {
    write(1, "*", 1);
  } else if (t>=' ')
      write(1, &t, 1);
  else {
      setinv();
      t+='@';
      write(1, &t, 1);
      normal();
  }
}

#ifdef __GNUC__
void ofsredisplay(int x) {
#else
void ofsredisplay(x) {
#endif
/* redisplays starting at x */
  unsigned char *w;
  int i;
  gotoxy(x, yinput);
  if (inputlast-inputofs>=x) {
    i=((inputlast-inputofs>Cols-1 ? Cols-1-x : inputlast-inputofs-x));
    for (w=input+inputofs+x; i--; w++) write1(*w, w-input);
  }
  cleareol();
  gotoxy(inputcursor, yinput);
  cursorwhere=1;
}

#ifdef __GNUC__
void delempty(struct histinfo *leavealone) {
#else
void delempty(leavealone)
struct histinfo *leavealone; {
#endif
  struct histinfo *h, *h2;
  int cont=0;
  h=histoldest;
  do {
    cont=0;
    if ((h->len<=h->plen) && (h!=leavealone)) {
      histLines--;
      h->next->prev=h->prev;
      h->prev->next=h->next;
      h2=h->prev;
      free(h);
      if (h==histoldest) {
        histoldest=h2;
	cont=1;
      }
      h=h2;
    } else h=h->prev;
  } while ((h!=histoldest || cont) && histLines>0);
  if (!histLines) {
    histoldest=NULL;
    return;
  }
}

struct histinfo *makenew() {
  struct histinfo *nh;
  if (!histLines) {
    nh=(struct histinfo *)malloc(sizeof (struct histinfo));
    nh->prev=nh->next=histoldest=nh;
    histLines++;
  } else if (histLines<MAX_HIST_LINES) {
    nh=(struct histinfo *)malloc(sizeof (struct histinfo));
    nh->prev=histoldest;
    nh->next=histoldest->next;
    histoldest->next=nh;
    nh->next->prev=nh;
    histLines++;
  } else {
    nh=histoldest;
    histoldest=nh->prev;
  }
  return nh;
}

#ifdef __GNUC__
void sendline(int yank) {
#else
void sendline(yank) {
#endif
  if (!specialprompt) {
    histcurrent->len=inputlast;
    histcurrent->plen=plen;
  }
  if (!yank) {
    input[inputlast]='\n';
    if (printmode) formatter(input, inputlast+1);
    if (write(writefd, input+plen, inputlast+1-plen)<inputlast+1-plen)
      cleanupexit(1, "write error");
  }
  input[inputlast]='\0';
  delempty(NULL);
  histcurrent=makenew();
  input=histcurrent->string;
  strlcpy(input, prompt, BUF_SIZE+20);
  plen=strlen(prompt);
  inputofs=specialprompt=0;
  modified=1;
  inputcursor=inputlast=plen;
  ofsredisplay(0);
  no_echo=0;
}

void modify() {
  struct histinfo *h;
  if (!modified) {
    if (inputlast>plen) {
      h=histcurrent;
      delempty(h);
      histcurrent=makenew();
      strlcpy(histcurrent->string, h->string, BUF_SIZE+20);
      input=histcurrent->string;
    }
    modified=1;
  }
}

void fixpos() {
  if (inputcursor<8 && inputofs>0) {
    inputofs-=Cols-16;
    inputcursor+=Cols-16;
    if (inputofs<0) {
      inputcursor+=inputofs;
      inputofs=0;
    }
    ofsredisplay(0);
  } else if (inputcursor>Cols-8) {
    inputofs+=Cols-16;
    inputcursor-=Cols-16;
    ofsredisplay(0);
  }
}

void reshow() {
  if (inputlast>Cols-8) {
    inputcursor=Cols-9;
    inputofs=inputlast-Cols+9;
  } else {
    inputofs=0;
    inputcursor=inputlast;
  }
  ofsredisplay(0);
}

#ifdef __GNUC__
void inschar(unsigned char t) {
#else
void inschar(t)
unsigned char t; {
#endif

  unsigned char *tmp;

  if (inputlast<BUF_SIZE-4) {
    modify();
    if (inputofs+inputcursor==inputlast) {
      write1(t, inputlast);
      input[inputlast++]=t;
      input[inputlast]='\0';
      inputcursor++;
    } else {
      tmp=input+inputlast;
      while (tmp>=input+inputofs+inputcursor) {
	*(tmp+1) = *tmp;
	--tmp;
      }
      input[inputofs+(inputcursor++)]=t;
      inputlast++;
      ofsredisplay(inputcursor-1);
    }
    fixpos();
  }
}

#ifdef __GNUC__
void dokbdchar(unsigned char t) {
#else
void dokbdchar(t)
unsigned char t; {
#endif

  unsigned char *tmp;

  if (inarrow==1) {
    if (t=='[' || t=='O') {
      inarrow++;
      return;
    }
    inarrow=0;
  } else if (inarrow==2) {
    inarrow=0;
    if (t=='D') t=2;
    else if (t=='C') t=6;
    else if (t=='A') t=16;
    else if (t=='B') t=14;
    else return;
  }
  if (ctrlx && !quote) {
    ctrlx=0;
    t|=0x20;
    if (dispmode>0 && ((t=='h' && !hold_mode) || t=='y')) {
      hold_mode=1;
      hold_Lines=0;
      if (cursorwhere!=1) fullscroll();
      cursorwhere=2;
      normal();
      gotoxy(Cols-4, ystatus);
      setinv();
      write(1, "(h)", 3);
      normal();
    } else if (dispmode>0 && ((t=='h' && hold_mode) || t=='n')) {
      hold_mode=0;
      if (cursorwhere!=1) fullscroll();
      cursorwhere=2;
      normal();
      gotoxy(Cols-4, ystatus);
      setinv();
      write(1, "   ", 3);
      normal();
    } else if (dispmode>0 && t=='i') {
      dispmode=3-dispmode;
      bold=inv=under=0;
    } else if (dispmode>0 && t=='b') {
      beep=!beep;
    } else if (t=='c') cleanupexit(1, "exiting");
    return;
  }
  if (cutline) donl=1;
  if (cursorwhere!=1) {
    normal();
    fullscroll();
    gotoxy(inputcursor, yinput);
    cursorwhere=1;
  }
  if (t==24 && !quote) {
    ctrlx=1;
    return;
  } else ctrlx=0;
  if (t==27 && !quote) {
    inarrow=1;
  } else if ((t==10 || t==13) && !quote) {  /* return, newline */
    sendline(0);
    if (tabLines) {
      curtabr=oldest;
      curtabt=oldest->next;
    }
  } else if (t==25 && !quote) {	  /* ^y */
    if (!specialprompt) {
      sendline(1);
      if (tabLines) {
	curtabr=oldest;
	curtabt=oldest->next;
      }
    }
  } else if (t==21 && !quote) {   /* ^u */
    modify();
    input[plen]='\0';
    inputcursor=inputlast=plen;
    inputofs=0;
    ofsredisplay(0);
  } else if ((t==8 || t==0x7f) && !quote) {  /* ^h, ^? */
    if (inputcursor>plen) {
      modify();
      tmp=input+inputcursor+inputofs;
      while (tmp<input+inputlast) {
	*(tmp-1) = *tmp;
	++tmp;
      }
      input[--inputlast]='\0';
      gotoxy(--inputcursor, yinput);
      ofsredisplay(inputcursor);
      fixpos();
    }
  } else if (t==4 && !quote) {  /* ^d */
    if (inputcursor+inputofs<inputlast) {
      modify();
      tmp=input+inputcursor+inputofs+1;
      while (tmp<input+inputlast) {
	*(tmp-1) = *tmp;
	++tmp;
      }
      input[--inputlast]='\0';
      gotoxy(inputcursor, yinput);
      ofsredisplay(inputcursor);
    }
  } else if (t==11 && !quote) {  /* ^k */
    if (inputcursor+inputofs<inputlast) {
      modify();
      input[inputlast=inputofs+inputcursor]='\0';
      ofsredisplay(inputcursor);
    }
  } else if (t==2 && !quote) {  /* ^b */
    if (inputcursor>0 && (inputcursor>plen || inputofs>0)) {
      gotoxy(--inputcursor, yinput);
      fixpos();
    }
  } else if (t==6 && !quote) {  /* ^f */
    if (inputcursor+inputofs<inputlast) {
      gotoxy(++inputcursor, yinput);
      fixpos();
    }
  } else if (t==1 && !quote) { /* ^a */
    if (inputcursor+inputofs>plen) {
      if (inputofs==0)
	gotoxy((inputcursor=plen), yinput);
      else {
	inputofs=0;
	inputcursor=plen;
	ofsredisplay(0);
      }
    }
  } else if (t==5 && !quote) { /* ^e */
    if (inputcursor+inputofs<inputlast) {
      if (inputlast-inputofs<Cols-3) {
	gotoxy((inputcursor=inputlast-inputofs), yinput);
      } else if (inputlast>Cols-8) {
	inputcursor=Cols-9;
	inputofs=inputlast-Cols+9;
	ofsredisplay(0);
      } else {
	inputofs=0;
	inputcursor=inputlast;
	ofsredisplay(0);
      }
    }
  } else if (t==12 && !quote) { /* ^l */
    displaystatus();
    ofsredisplay(0);
  } else if (t==9 && !quote) { /* TAB */
    if (tabLines) {
      modify();
      strlcpy(input+plen, curtabt->string, BUF_SIZE+20-plen);
      curtabr=curtabt->prev;
      curtabt=curtabt->next;
      inputlast=strlen(input);
      reshow();
    }
  } else if (t==18 && !quote) { /* ^r */
    if (tabLines) {
      modify();
      strlcpy(input+plen, curtabr->string, BUF_SIZE+20-plen);
      curtabt=curtabr->next;
      curtabr=curtabr->prev;
      inputlast=strlen(input);
      reshow();
    }
  } else if (t==16 && !quote) { /* ^p */
    if (histLines>1 && !specialprompt) {
      histcurrent->plen=plen;
      histcurrent->len=inputlast;
      histcurrent=histcurrent->next;
      plen=histcurrent->plen;
      inputlast=histcurrent->len;
      input=histcurrent->string;
      modified=0;
      reshow();
    }
  } else if (t==14 && !quote) { /* ^n */
    if (histLines>1 && !specialprompt) {
      histcurrent->plen=plen;
      histcurrent->len=inputlast;
      histcurrent=histcurrent->prev;
      plen=histcurrent->plen;
      inputlast=histcurrent->len;
      input=histcurrent->string;
      modified=0;
      reshow();
    }
  } else if (t==15 &&!quote) { /* ^o */
    if (strlen(o_buffer)) modify();
    for (tmp=o_buffer; *tmp; tmp++) inschar(*tmp);
  } else if (t==20 && !quote) { /* ^t */
    write(writefd, ctrl_t, strlen(ctrl_t));
  } else if (t==22 && !quote) { /* ^v */
    quote++;
    return;
#ifdef CONTROL_W
  } else if (t==23 && !quote) { /* ^w */
    fullscroll();
    normal();
    clearscreen();
    bold=inv=under=wherex=wherey=donl=0;
    displaystatus();
    ofsredisplay(0);
#endif
  } else inschar(t);
  quote=0;
}

#ifdef __GNUC__
void barf(unsigned char *m) {
#else
void barf(m)
unsigned char *m; {
#endif
  fprintf(stderr, "%s\n", m);
  exit(1);
}

char *myname;

void use() {
  fprintf(stderr, "Use: %s [options] program [program's options]\n", myname);
  fprintf(stderr, "Options are:\n");
  fprintf(stderr, "   -raw, -cooked, -irc  : set display mode\n");
  fprintf(stderr, "   -print               : print your input Lines\n");
  fprintf(stderr, "   -prompt <prompt>     : specify a command-line prompt\n");
  fprintf(stderr, "   -hold                : pause after each full screen (for cooked/irc mode)\n");
  fprintf(stderr, "   -beep                : let beeps through (for cooked/irc mode)\n");
  fprintf(stderr, "   -flow                : leave ^S/^Q alone for flow control\n");
  exit(1);
}

#ifdef __GNUC__
int main(int argc, char *argv[]) {
#else
int main(argc, argv)
int argc;
char *argv[]; {
#endif

  char *vr;
  int pfds0[2], pfds1[2], pfds2[2];
  struct timeval timeout;

  myname=(*argv);
  prompt=nullstring;
  while (argc>1) {
    if (strcmp(argv[1], "-raw")==0) {
      dispmode=0;
      argv++; argc--;
    } else if (strcmp(argv[1], "-cooked")==0) {
      dispmode=1;
      argv++; argc--;
    } else if (strcmp(argv[1], "-irc")==0) {
      dispmode=2;
      argv++; argc--;
    } else if (strcmp(argv[1], "-hold")==0) {
      hold_mode=1;
      argv++; argc--;
    } else if (strcmp(argv[1], "-print")==0) {
      argv++; argc--;
      if (prompt==nullstring) prompt=defprompt;
      printmode=1;
    } else if (strcmp(argv[1], "-beep")==0) {
      beep=1;
      argv++; argc--;
    } else if (strcmp(argv[1], "-flow")==0) {
      flow=1;
      argv++; argc--;
    } else if (strcmp(argv[1], "-prompt")==0) {
      if (argc>2) prompt=(unsigned char *)argv[2];
      if (strlen(prompt)>8) barf("Prompt too long");
      argv+=2; argc-=2;
    } else break;
  }
  if (argc<2) use();
  if (!isatty(0)) barf("I can only run on a tty, sorry");
  if ((termtype=getenv("TERM"))==NULL) barf("No terminal type set");
  if (tgetent(termcap, termtype)<1) barf("No termcap info for your terminal");
  tc=capabilities;
  if ((t_cm=(char *)tgetstr("cm", &tc))==NULL)
    barf("Can't find a way to move the cursor around with your terminal");
  if ((t_cl=(char *)tgetstr("cl", &tc))==NULL)
    barf("Can't find a way to clear the screen with your terminal");
  if ((t_ce=(char *)tgetstr("ce", &tc))==NULL)
    barf("Can't find a way to clear to end of line with your terminal");
  if ((t_cs=(char *)tgetstr("cs", &tc))==NULL) {
    if (strncmp(termtype, "xterm", 5)==0 || strncmp(termtype, "vt100", 5)==0)
      ansi_cs=1;
    else
      barf("Can't find a way to set the scrolling region with your terminal");
  }
  if ((t_me=(char *)tgetstr("me", &tc))!=NULL) {
    if ((t_mr=(char *)tgetstr("mr", &tc))==NULL) t_mr=t_me;
    if ((t_md=(char *)tgetstr("md", &tc))==NULL) t_md=t_me;
    if ((t_us=(char *)tgetstr("us", &tc))==NULL) t_us=t_me;
  } else if ((t_me=(char *)tgetstr("se", &tc))!=NULL &&
	     (t_mr=(char *)tgetstr("so", &tc))!=NULL) {
    t_md=t_mr;
    t_us=tc;
    (*tc++)='\0';
  } else {
    t_me=t_md=t_mr=t_us=tc;
    (*tc++)='\0';
  }

/*
  if ((ttyfd=open("/dev/tty", O_RDWR))<0 &&
      (ttyfd=open("/dev/tty", O_RDONLY))<0) barf("Can't open terminal!");
    */
    ttyfd = 0;

#ifdef TIOCGWINSZ
  if (ioctl(ttyfd, TIOCGWINSZ, &wsz)<0 || wsz.ws_row<1 || wsz.ws_col<1) {
#endif
    Lines=((vr=getenv("LINES"))?atoi(vr):0);
    Cols=((vr=getenv("COLUMNS"))?atoi(vr):0);
    if (Lines<1 || Cols<1) {
      if ((Lines=tgetnum("li"))<1 || (Cols=tgetnum("co"))<1) {
	Lines=24; Cols=80;
      }
    }
#ifdef TIOCGWINSZ
  } else {
    Lines=wsz.ws_row;
    Cols=wsz.ws_col;
  }
#endif

  if (pipe(pfds0)<0 || pipe(pfds1)<0 || pipe(pfds2)<0) {
    perror("pipe");
    exit(1);
  }
  mypid=getpid();
  switch (pid=fork()) {
    case -1:
      perror("fork");
      exit(1);
    case 0:
      if (pfds0[0]!=0) dup2(pfds0[0], 0);
      if (pfds1[1]!=1) dup2(pfds1[1], 1);
      if (pfds2[1]!=2) dup2(pfds2[1], 2);
      if (pfds0[0]>2) close(pfds0[0]);
      if (pfds0[1]>2) close(pfds0[1]);
      if (pfds1[0]>2) close(pfds1[0]);
      if (pfds1[1]>2) close(pfds1[1]);
      if (pfds2[0]>2) close(pfds2[0]);
      if (pfds2[1]>2) close(pfds2[1]);
      /* okay we can read from 0 and write to 1 and 2, now.. it seems */
      execvp(argv[1], argv+1);
      perror("exec");
      sleep(1);
      exit(1);
    default:
      close(pfds0[0]);
      close(pfds1[1]);
      close(pfds2[1]);
      readfd=pfds1[0];
      writefd=pfds0[1];
      errfd=pfds2[0];
  }

#ifdef USE_SGTTY

  if (ioctl(ttyfd, TIOCGETP, &term)<0 || ioctl(ttyfd, TIOCGETC, &tch)<0 ||
      ioctl(ttyfd, TIOCGLTC, &lch)<0) {
    perror("sgtty get ioctl");
    exit(1);
  }
  term0=term;
  tch0=tch;
  lch0=lch;
  term.sg_flags|=CBREAK;
  term.sg_flags&= ~ECHO & ~CRMOD;

  memset(&tch, -1, sizeof(tch));
  memset(&lch, -1, sizeof(lch));
  tch.t_intrc=(char)28;
  tch.t_quitc=(char)3;
  if (flow) {
    tch.t_startc=(char)17;
    tch.t_stopc=(char)19;
  }
  lch.t_suspc=(char)26;

  if (ioctl(ttyfd, TIOCSETP, &term)<0 || ioctl(ttyfd, TIOCSETC, &tch)<0 ||
      ioctl(ttyfd, TIOCSLTC, &lch)<0) {
    perror("sgtty set ioctl");
    exit(1);
  }

#else
  if (tcgetattr(ttyfd, &term)<0) {
    perror("tcgetattr");
    exit(1);
  }
  term0=term;

  term.c_lflag &= ~ECHO & ~ICANON;
  term.c_cc[VTIME]=(char)0;
  term.c_cc[VMIN]=(char)1;
  if (!flow) {
    term.c_cc[VSTOP]=(char)0;
    term.c_cc[VSTART]=(char)0;
  }
  term.c_cc[VQUIT]=(char)3;
  term.c_cc[VINTR]=(char)28; /* reverse ^c and ^\ */
  term.c_cc[VSUSP]=(char)26;
#ifdef VREPRINT
  term.c_cc[VREPRINT]=(char)0;
#endif
#ifdef VDISCARD
  term.c_cc[VDISCARD]=(char)0;
#endif
#ifdef VLNEXT
  term.c_cc[VLNEXT]=(char)0;
#endif
#ifdef VDSUSP
  term.c_cc[VDSUSP]=(char)0;
#endif

  if (tcsetattr(ttyfd, TCSANOW, &term)<0) {
    perror("tcsetattr");
    exit(1);
  }
#endif

  allsigs();

  ystatus=Lines-2;
  yinput=Lines-1;

  if (Lines>255) barf("Screen too big");
  if (ystatus<=2 || Cols<20) barf("Screen too small");

  statusline=(unsigned char *)malloc(MAX_COLS);
  writebuf=(unsigned char *)malloc(20*BUF_SIZE);
  strlcpy(tmpstr, " ", BUF_SIZE);
  for (i=1; i<argc; i++)
    if (strlen(tmpstr)+strlen(argv[i])<Cols-1) {
      strlcat(tmpstr, argv[i], BUF_SIZE);
      strlcat(tmpstr, " ", BUF_SIZE);
    }
  setstatus(tmpstr);

  if (dispmode==0) wherey=ystatus-1;
  clearscreen();
  displaystatus();

  histoldest=histcurrent=(struct histinfo *)malloc(sizeof (struct histinfo));
  input=histcurrent->string;
  histcurrent->prev=histcurrent->next=histcurrent;
  histLines=1;
  plen=strlen(prompt);
  inputlast=inputcursor=plen;
  strlcpy(input, prompt, BUF_SIZE+20);
  ofsredisplay(0);
  *protcmd='\0';
  *o_buffer='\0';
  cursorwhere=1;

  FD_ZERO(&ready);
  FD_SET(ttyfd, &ready);
  FD_SET(readfd, &ready);
  FD_SET(errfd, &ready);

  timeout.tv_sec=0;
  timeout.tv_usec=500000;

  while(1) {
    int r;
    result=ready;
    r=select(64, &result, NULL, NULL, (cursorwhere==1) ? NULL : &timeout);
    if (r<0) {
      if (errno==EINTR) continue;
      else cleanupexit(1, "select error");
    } else if (r==0) {
      if (cursorwhere!=1) {
	normal();
	fullscroll();
	gotoxy(inputcursor, yinput);
	cursorwhere=1;
      }
      continue;
    }

    if (FD_ISSET(readfd, &result)) {
      if ((rc=read(readfd, readbuf, BUF_SIZE))>0)
        doprogramline(readbuf, rc);
      else
        cleanupexit(1, "program terminated");
    }
    if (FD_ISSET(errfd, &result)) {
      if ((rc=read(errfd, readbuf, BUF_SIZE))>0)
        doprogramline(readbuf, rc);
      else
        cleanupexit(1, "program terminated");
    }
    if (FD_ISSET(ttyfd, &result)) {
      if ((rrc=read(0, readbuf, BUF_SIZE))>0)
        for (t=readbuf; rrc>0; rrc--) dokbdchar(*(t++));
      else
	cleanupexit(1, "read error from keyboard");
  }
}
}
