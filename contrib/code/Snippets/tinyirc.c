/* $MirOS: contrib/code/Snippets/tinyirc.c,v 1.1.7.1 2005/02/05 02:36:15 tg Exp $ */

/* Configuration options */
static char *DEFAULTSERVER = "217.160.142.142";
/*			reads: irc6.oftc.net         */
/* please change the default server to one near you. */
#define DEFAULTPORT	6667
#define COMMANDCHAR	'/'
/* each line of history adds 512 bytes to resident size */
#define HISTLEN		8
#define RELEASE_L	"TinyIRC pre1.0-mirabile-MirOS-contrib"
#define RELEASE_S	"TinyIRC MirOS"
/* tinyirc 1.0

   TinyIRC Alpha Release
   Copyright (C) 1994 Nathan I. Laredo
   Copyright (c) 1999-2004 Thorsten Glaser

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License Version 1
   as published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   Send your comments and all your spare pocket change to
   laredo@gnu.ai.mit.edu (Nathan Laredo) or to 1604 Lilac Lane,
   Plano, TX 75074, USA.  Any donations are welcome.


   Please do not forget to donate to the OpenBSD project
   at http://www.OpenBSD.org/ - the daemons will thank you.
   While you're at it, visit the MirBSD project pages
   at http://mirbsd.de/ or http://mirbsd.org/

   Missing features:
    * KNF - man 9 style
    * Security auditing
   Added:
    * /quote command (shortcut: Q)
    * command re-ordering for shortcuts
    * ^C command for instant exiting
 */

#include <stdio.h>
#ifndef USETERMIOS
#include <sgtty.h>
#define	USE_OLD_TTY
#include <sys/ioctl.h>
#if !defined(sun) && !defined(sequent) && !defined(hpux) && \
	!defined(_AIX_)
#include <strings.h>
#define strchr index
#else
#include <string.h>
#endif
#else
#include <string.h>
#include <termios.h>
#endif
#include <sys/types.h>
#include <pwd.h>
#include <sys/time.h>
#include <sys/file.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <ctype.h>
#include <curses.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <term.h>
#include <unistd.h>

#ifndef __RCSID
#define __RCSID(x)	static const char _rcsid[] = (x)
#endif

__RCSID("$MirOS: contrib/code/Snippets/tinyirc.c,v 1.1.7.1 2005/02/05 02:36:15 tg Exp $");

struct dlist {
    char name[64];
    struct dlist *next;
};
struct dlist *object = NULL, *objlist = NULL, *newobj;
u_short IRCPORT = DEFAULTPORT;
#define LINELEN 512
int sockfd, sok = 1, stdinfd, stdoutfd, histline, dumb = 0, CO, LI, column;
char *CM, *CS, *CE, *linein, lineout[LINELEN], *history[HISTLEN], localhost[64],
*SO, *SE, *tok_in[256], *tok_out[256], *tmp, serverdata[512], termcap[1024],
*DC, *ptr, *term, *fromhost, IRCNAME[10], inputbuf[512], beenden = 0;
char bp[4096];
int cursd = 0, curli = 0, curx = 0;
fd_set readfs;
struct timeval time_out;
struct tm *timenow;
static time_t idletimer, datenow, wasdate;
struct passwd *userinfo;

#ifdef	USETERMIOS
struct termios _tty;
tcflag_t _res_iflg, _res_lflg;
#define raw() (_tty.c_lflag &= ~(ICANON | ECHO | ISIG), \
	tcsetattr(stdinfd, TCSANOW, &_tty))
#define savetty() ((void) tcgetattr(stdinfd, &_tty), \
	_res_iflg = _tty.c_iflag, _res_lflg = _tty.c_lflag)
#define resetty() (_tty.c_iflag = _res_iflg, _tty.c_lflag = _res_lflg,\
	(void) tcsetattr(stdinfd, TCSADRAIN, &_tty))
#else
struct sgttyb _tty;
int _res_flg;
#define raw() (_tty.sg_flags |= RAW, _tty.sg_flags &= ~ECHO, \
	ioctl(stdinfd, TIOCSETP, &_tty))
#define savetty() ((void) ioctl(stdinfd, TIOCGETP, &_tty), \
	_res_flg = _tty.sg_flags)
#define resetty() (_tty.sg_flags = _res_flg, \
	(void) ioctl(stdinfd, TIOCSETP, &_tty))
#endif

int putchar_x(c)
int c;
{
    return putchar(c);
}

#define	tputs_x(s) (tputs(s,0,putchar_x))

int my_stricmp(str1, str2)
char *str1, *str2;
{
    int compare;

    while (*str1 != 0 && str2 != 0) {
	if (isalpha(*str1) && isalpha(*str2)) {
	    compare = *str1 ^ *str2;
	    if ((compare != 32) && (compare != 0))
		return (*str1 - *str2);
	} else {
	    if (*str1 != *str2)
		return (*str1 - *str2);
	}
	str1++;
	str2++;
    }
    return (*str1 - *str2);
}

struct dlist *additem(item, ptr)
char *item;
struct dlist *ptr;
{
    newobj = (struct dlist *) malloc(sizeof(struct dlist));
    strlcpy(newobj->name, item, 64);
    newobj->next = ptr;
    return newobj;
}
struct dlist *finditem(item, ptr)
char *item;
struct dlist *ptr;
{
    while (ptr != NULL)
	if (my_stricmp(item, ptr->name) == 0)
	    break;
	else
	    ptr = ptr->next;
    return ptr;
}
struct dlist *removeitem(item, ptr)
char *item;
struct dlist *ptr;
{
    struct dlist *prev = NULL, *start = ptr;
    while (ptr != NULL) 
	if (my_stricmp(item, ptr->name) == 0) {
	    newobj = ptr->next;
	    if (object == ptr)
		object = NULL;
	    free (ptr);
	    if (prev == NULL)
		return newobj;
	    else {
		prev->next = newobj;
		return start;
	    }
	} else {
	    prev = ptr;
	    ptr = ptr->next;
	}
    return start;
}
int makeconnect(hostname)
char *hostname;
{
    struct sockaddr_in sa;
    struct hostent *hp;
    int s;

    if ((hp = gethostbyname(hostname)) == NULL)
	return -1;
    bzero(&sa, sizeof(sa));
    memmove((char *) &sa.sin_addr, hp->h_addr, hp->h_length);
    sa.sin_family = hp->h_addrtype;
    sa.sin_port = htons((u_short) IRCPORT);
    if ((s = socket(hp->h_addrtype, SOCK_STREAM, 0)) < 0)
	return -1;
    if (connect(s, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
	close(s);
	return -1;
    }
    fcntl(s, F_SETFL, O_NDELAY);
    return s;
}

int sendline()
{
    if (write(sockfd, lineout, strlen(lineout)) < 1)
	return 0;
    return 1;
}

void updatestatus()
{
    int n;
    if (!dumb) {
	if (60 < (datenow = time(NULL)) - wasdate) {
	    wasdate = datenow;
	    timenow = localtime(&datenow);
	    tputs_x(tgoto(CM, 0, LI - 2));
	    tputs_x(SO);
	    n = printf("[%02d:%02d] %s on %s : %s", timenow->tm_hour,
			timenow->tm_min, IRCNAME, (object->name == NULL ?
			"*" : object->name), RELEASE_S);
	    for (; n < CO; n++)
		putchar(' ');
	    tputs_x(SE);
	}
    }
}

static int nop()
{
    return 1;
}
static int doerror()
{
    column = printf("*** ERROR:");
    return 2;
}
static int doinvite()
{
    printf("*** %s (%s) invites you to join %s.",
	   tok_in[0], fromhost, &tok_in[2][1]);
    return 0;
}
static int dojoin()
{
    if (strcmp(tok_in[0], IRCNAME) == 0) {
	object = objlist = additem(tok_in[2], objlist);
	wasdate = 0;
	printf("*** Now talking in %s", object->name);
    } else
	printf("*** %s (%s) joined %s", tok_in[0], fromhost, tok_in[2]);
    return 0;
}
static int dokick()
{
    printf("*** %s was kicked from %s by %s (%s)",
	   tok_in[3], tok_in[2], tok_in[0], tok_in[4]);
    if (strcmp(tok_in[3], IRCNAME) == 0) {
	objlist = removeitem(tok_in[2], objlist);
	if (object == NULL)
	    object = objlist;
	if (object != NULL)
	    printf("\n\r*** Now talking in %s", object->name);
	wasdate = 0;
    }
    return 0;
}
static int dokill()
{
    printf("*** %s killed by %s (%s)", tok_in[3], tok_in[0], tok_in[4]);
    return 0;
}
static int domode()
{
    printf("*** %s changed %s to:", tok_in[0], tok_in[2]);
    return 3;
}
static int donick()
{
    if (strcmp(tok_in[0], IRCNAME) == 0) {
	wasdate = 0;
	strlcpy(IRCNAME, tok_in[2], 10);
    }
    printf("*** %s is now known as %s", tok_in[0], tok_in[2]);
    return 0;
}
static int donotice()
{
    if (*tok_in[2] != '#')
	column = printf("-%s-", tok_in[0]);
    else 
	column = printf("-%s:%s-", tok_in[0], tok_in[2]);
    return 3;
}
static int dopart()
{
    printf("*** %s (%s) left %s", tok_in[0], fromhost,
	   tok_in[2]);
    if (strcmp(tok_in[0], IRCNAME) == 0) {
	objlist = removeitem(tok_in[2], objlist);
	if (object == NULL)
	    object = objlist;
	if (object != NULL)
	    printf("\n\r*** Now talking in %s", object->name);
	wasdate = 0;
    }
    return 0;
}
static int dopong()
{
    column = printf("*** Got PONG from %s:", tok_in[0]);
    return 3;
}
static int doprivmsg()
{
    if (*tok_in[2] != '#')
	column = printf("*%s*", tok_in[0]);
    else if (object != NULL && my_stricmp(object->name, tok_in[2]))
	column = printf("<%s:%s>", tok_in[0], tok_in[2]);
    else
	column = printf("<%s>", tok_in[0]);
    return 3;
}
static int doquit()
{
    printf("*** %s (%s) Quit (%s)", tok_in[0], fromhost, tok_in[2]);
    return 0;
}
static int dosquit()
{
    return 1;
}
static int dotime()
{
    return 1;
}
static int dotopic()
{
    printf("*** %s set %s topic to \"%s\"", tok_in[0], tok_in[2],
	   tok_in[3]);
    return 0;
}

int donumeric(num)
int num;
{
    if (num == 352) {		/* rpl_whoreply */
	column = printf("%-14s %-10s %-3s %s@%s :", tok_in[3], tok_in[7],
			tok_in[8], tok_in[4], tok_in[5]);
	return 9;
    } else if (num == 432 || num == 433) {
	char ch;
	printf("*** You've chosen an invalid nick.  Choose again.");
	tputs_x(tgoto(CM, 0, LI - 1));
	tputs_x(CE);
	printf("New Nick? ");
	fflush(stdout);
	resetty();
	tmp = IRCNAME;
	while ((ch = getchar()) != '\n')
	    if (strlen(IRCNAME) < 9)
		*(tmp++) = ch;
        *tmp = '\0';
	wasdate = 0;
	raw();
	snprintf(lineout, LINELEN, "NICK :%s\n", IRCNAME);
	sendline();
	tputs_x(tgoto(CM, 0, LI - 1));
	tputs_x(CE);
    } else {			/* all remaining numerics */
	column = printf("%s", tok_in[1]);
	return 3;
    }
    return (0);
}

#define	LISTSIZE	51
#define	DO_JOIN		12
#define	DO_MSG		18
#define	DO_PRIVMSG	30
#define	DO_QUIT		32
#define	DO_QUOTE	31
#define	DO_W		46
#define	DO_WHOIS	49
static char *cmdlist[LISTSIZE] =
{"AWAY", "ADMIN", "CONNECT", "CLOSE", "DIE", "DNS", "ERROR", "HELP",
 "HASH", "INVITE", "INFO", "ISON", "JOIN", "KICK", "KILL", "LIST", "LINKS",
 "LUSERS", "MSG", "MODE", "MOTD", "NOTICE", "NICK", "NAMES", "NOTE", "OPER",
 "PART", "PASS", "PING", "PONG", "PRIVMSG", "QUOTE", "QUIT", "REHASH", "RESTART",
 "SERVER", "SQUIT", "STATS", "SUMMON", "TIME", "TOPIC", "TRACE", "USER",
 "USERHOST", "USERS", "VERSION", "W", "WALLOPS", "WHO", "WHOIS", "WHOWAS"};
static int numargs[LISTSIZE] =
{1, 1, 3, 1, 1, 1, 1, 1,
 1, 2, 1, 1, 1, 3, 2, 1, 1,
 2, 2, 2, 1, 2, 1, 1, 1, 2,
 1, 1, 1, 1, 2, 0, 1, 1, 1,
 3, 2, 1, 3, 1, 2, 2, 4,
 1, 1, 1, 1, 1, 1, 1, 1
};
static int (*docommand[LISTSIZE]) () =
{nop, nop, nop, nop, nop, nop, doerror, nop,
 nop, doinvite, nop, nop, dojoin, dokick, dokill, nop, nop,
 nop, nop, domode, nop, donotice, donick, nop, nop, nop,
 dopart, nop, nop, dopong, doprivmsg, nop, doquit, nop, nop,
 nop, dosquit, nop, nop, dotime, dotopic, nop, nop,
 nop, nop, nop, nop, nop, nop, nop, nop
};

int wordwrapout(ptr, count)
char *ptr;
int count;
{
    while(ptr != NULL) {
	if ((tmp = strchr(ptr, ' ')) != NULL)
	    *(tmp++) = '\0';
	if (strlen(ptr) < CO - count)
	    count += printf(" %s", ptr);
	else
	    count = printf("\n\r   %s", ptr);
	ptr = tmp;
    }
    return count;
}
int parsedata()
{
    int i, found = 0;

/* take care of ping silently */
    if (serverdata[0] == 'P') {
	snprintf(lineout, LINELEN, "PONG :%s\n", &serverdata[6]);
	return sendline();
    }
    if (!dumb)
	tputs_x(tgoto(CM, 0, LI - 3));

    tok_in[i = 0] = serverdata;
    tok_in[i]++;
    while (tok_in[i] != NULL)
	if (*tok_in[i] == ':')
	    break;
	else {
	    if ((tmp = strchr(tok_in[i], ' ')) != NULL) {
		tok_in[++i] = &tmp[1];
		*tmp = '\0';
	   } else
		tok_in[++i] = NULL;
	}
    if (tok_in[i] != NULL)
	tok_in[i]++;
    tok_in[++i] = NULL;

    if (!dumb)
	putchar('\n');
    if ((tmp = strchr(tok_in[0], '!')) != NULL) {
	fromhost = &tmp[1];
	*tmp = '\0';
    } else
	fromhost = NULL;

    column = 0;
    if ((i = atoi(tok_in[1])))
	i = donumeric(i);
    else {
	for (i = 0; i < LISTSIZE && !found; i++)
	    found = (strcmp(cmdlist[i], tok_in[1]) == 0);
	if (found)
	    i = (*docommand[i - 1]) ();
	else
	    i = nop();
    }

    if (i)
	while (tok_in[i])	/* output remainder with word wrap */
	    column = wordwrapout(tok_in[i++], column);
    if (dumb)
	putchar('\n');
    if (strncmp(tok_in[1], "Closing", 7) == 0)
	return 0;
    return 1;
}

int serverinput()
{   char ich;
    while (read(sockfd, &ich, 1) > 0)
	if (ich != '\n' && ich != '\r')
	    serverdata[cursd++] = ich;
	else {
	    serverdata[cursd] = 0;
	    if (cursd) {
		cursd = 0;
		return parsedata();
	    }
	}
    return 1;
}

void parseinput()
{
    int i, j, outcol, found = 0;

    if (*linein == '\0')
	return;

    strlcpy(inputbuf, linein, 512);
    tok_out[i = 0] = strtok(inputbuf," ");
    while((tok_out[++i] = strtok(NULL, " ")) != NULL);
    if (!dumb) {
	tputs_x(tgoto(CM, 0, LI - 3));
	putchar('\n');
    }
    if (*tok_out[0] == COMMANDCHAR) {
	tok_out[0]++;
	for (i = 0; i < strlen(tok_out[0]) && isalpha(tok_out[0][i]); i++)
	    tok_out[0][i] = toupper(tok_out[0][i]);
	for (i = 0; i < LISTSIZE && !found; i++)
	    found = (strncmp(cmdlist[i], tok_out[0], strlen(tok_out[0])) == 0);
	i--;
	if (!found) {
	    printf("*** Invalid command");
	    return;
	}
	if (i == DO_JOIN)
	    if ((newobj = finditem(tok_out[1], objlist)) != NULL) {
		object = newobj;
		wasdate = 0;
		printf("*** Now talking in %s", object->name);
		return;
	    }
	if (i == DO_MSG)
	    i = DO_PRIVMSG;
	if (i == DO_W)
	    i = DO_WHOIS;

	strlcpy(lineout, (i == DO_QUOTE) ? "" : cmdlist[i], LINELEN);
	j = 0;
	if (i == DO_QUIT)
	    snprintf(&lineout[strlen(lineout)], LINELEN - strlen(lineout),
		" :using %s ", RELEASE_L);
	outcol = printf("= %s", lineout);
	while (tok_out[++j]) {
	   snprintf(&lineout[strlen(lineout)], LINELEN - strlen(lineout),
		   "%s%s", ((j == numargs[i] &&
		   tok_out[j + 1] != NULL) ? " :" : " "), tok_out[j]);
	   outcol = wordwrapout(tok_out[j], outcol);
	}
	strlcat(lineout, "\n", LINELEN);
    } else {
	if (object == NULL) {
	    printf ("*** Nowhere to send");
	    return;
	}
	snprintf(lineout, LINELEN, "PRIVMSG %s :%s\n", object->name, linein);
	outcol = printf("> %s", tok_out[j = 0]);
	while(tok_out[++j])
	   outcol = wordwrapout(tok_out[j], outcol);
    }
    sendline();
    idletimer = time(NULL);
}

void histupdate()
{
    linein = history[histline];
    curx = curli = strlen(linein);
    tputs_x(tgoto(CM, 0, LI - 1));
    printf("%s", &linein[(curli / CO) * CO]);
    tputs_x(CE);
}

void printpartial(fromx)
int fromx;
{
    int i;
    tputs_x(tgoto(CM, 0, LI - 1));
    for(i = fromx; i < fromx + CO && i < curli; i++)
	putchar(linein[i]);
    tputs_x(CE);
    tputs_x(tgoto(CM, curx % CO, LI - 1));
}
void userinput()
{
    int i, z;
    char ch;
    if (dumb) {
	fgets(linein, 500, stdin);
	tmp = strchr(linein, '\n');
	if (tmp != NULL)	/* get rid of newline */
	    *tmp = '\0';
	parseinput();
	putchar('\n');
    } else {
	read(stdinfd, &ch, 1);
	if (ch == '\177')
	    ch = '\10';
	switch (ch) {
	case '\1':		/* C-a */
	    if (curx >= CO)
	        printpartial(curx = 0);
	    else
		tputs_x(tgoto(CM, curx = 0, LI - 1));
	    break;
	case '\4':		/* C-d */
	case '\10':		/* C-h */
	    if (curx) {
		if (ch == '\4' && curx < curli)
		    curx++;
		if (curli == curx)
		    linein[(--curx)] = '\0';
		else		/* delete somewhere in the middle */
		    for (i = (--curx); i < curli; i++)
			linein[i] = linein[i + 1];
		curli--;
		if (DC != NULL && curx % CO != CO - 1) {
		    tputs_x(tgoto(CM, curx % CO, LI - 1));
		    tputs_x(DC);
		} else
		    printpartial((curx / CO) * CO);
	    }
	    break;
	case '\2':		/* C-b */
	    if (curx > 0)
		curx--;
	    if (curx % CO == CO - 1)
		printpartial((curx / CO) * CO);
	    else
		tputs_x(tgoto(CM, curx % CO, LI - 1));
	    break;
	case '\3':		/* C-c */
	    beenden = 1;
	    break;
	case '\5':		/* C-e */
	    curx = curli;
	case '\14':		/* C-l */
	    printpartial((curx / CO) * CO);
	    break;
	case '\6':		/* C-f */
	    if (curx < curli)
		curx++;
	    tputs_x(tgoto(CM, curx % CO, LI - 1));
	    break;
	case '\16':		/* C-n */
	    if ((++histline) >= HISTLEN)
		histline = 0;
	    histupdate();
	    break;
	case '\20':		/* C-p */
	    if ((--histline) < 0)
		histline = HISTLEN - 1;
	    histupdate();
	    break;
	case '\r':
	case '\n':
	    if (!curli)
		return;
	    tputs_x(tgoto(CM, 0, LI - 1));
	    tputs_x(CE);
	    parseinput();
	    if ((++histline) >= HISTLEN)
		histline = 0;
	    curx = curli = 0;
	    linein = history[histline];
	    break;
	case '\27':
	    if (object == NULL)
		break;
	    object = object->next;
	    if (object == NULL)
		object = objlist;
	    wasdate = 0;
	    break;
	default:
	    if (curli < 499) {
		if (curli == curx) {	/* append character */
		    linein[++curli] = '\0';
		    linein[curx++] = ch;
		    putchar(ch);
		    tputs_x(CE);
		} else {	/* insert somewhere in the middle */
		    for (i = (++curli); i >= curx; i--)
			linein[i + 1] = linein[i];
		    linein[curx] = ch;
		    for (i = (curx % CO); i < CO &&
			(z = (curx / CO) * CO + i) < curli; i++)
			putchar(linein[z]);
		    tputs_x(CE);
		    curx++;
		}
	    }
	    break;
	}
    }
}

void cleanup(sig)
int sig;
{
    tputs_x(tgoto(CS, -1, -1));
    tputs_x(tgoto(CM, 0, LI - 1));
    resetty();
    printf("\ngot signal %d\n", sig);
    exit(128 + sig);
}

int
main(argc, argv)
int argc;
char **argv;
{
    char hostname[64];
    int i;

    stdinfd = fileno(stdin);
    stdoutfd = fileno(stdout);
    userinfo = getpwuid(getuid());
    strlcpy(hostname, DEFAULTSERVER, 64);
    if (!getenv("IRCNICK"))
	strncpy(IRCNAME, userinfo->pw_name, sizeof(IRCNAME));
    else
	strncpy(IRCNAME, (char *) getenv("IRCNICK"), sizeof(IRCNAME));
    if (argc > 1) {
	for (i = 1; i < argc; i++)
	    if (argv[i][0] == '-') {
		if (argv[i][1] == 'd')
		    dumb = 1;
		else {
		    fprintf(stderr, "usage: %s %s\n", argv[0],
			    "[nick] [server] [port] [-dumb]");
		    exit(1);
		}
	    } else if (strchr(argv[i], '.')) {
		strlcpy(hostname, argv[i], 64);
	    } else if (atoi(argv[i]) > 255) {
		IRCPORT = atoi(argv[i]);
	    } else
		strncpy(IRCNAME, argv[i], sizeof(IRCNAME));
    }
    printf("*** trying port %d of %s\n\n", IRCPORT, hostname);
    if ((sockfd = makeconnect(hostname)) < 0) {
	fprintf(stderr, "*** %s connection refused, aborting\n", hostname);
	exit(0);
    }
    gethostname(localhost, 64);
    if (!getenv("IRCNAME"))
	snprintf(lineout, LINELEN, "USER %s %s %s :%s\n", userinfo->pw_name,
		localhost, hostname, userinfo->pw_gecos);
    else
	snprintf(lineout, LINELEN, "USER %s %s %s :%s\n", userinfo->pw_name, localhost,
		hostname, (char *)getenv("IRCNAME"));
    sendline();
    snprintf(lineout, LINELEN, "NICK :%s\n", IRCNAME);
    sendline();
    idletimer = time(NULL);
    if (!dumb) {
	ptr = termcap;
	if ((term = (char *) getenv("TERM")) == NULL) {
	    fprintf(stderr, "tinyirc: TERM not set\n");
	    exit(1);
	}
	if (tgetent(bp, term) < 1) {
	    fprintf(stderr, "tinyirc: no termcap entry for %s\n", term);
	    exit(1);
	}
	if ((CO = tgetnum("co") - 2) < 1)
	    CO = 78;
	if ((LI = tgetnum("li")) == -1)
	    LI = 24;
	if ((CM = (char *) tgetstr("cm", &ptr)) == NULL)
	    CM = (char *) tgetstr("CM", &ptr);
	if ((SO = (char *) tgetstr("so", &ptr)) == NULL)
	    SO = "";
	if ((SE = (char *) tgetstr("se", &ptr)) == NULL)
	    SE = "";
	if (!CM || !(CS = (char *) tgetstr("cs", &ptr)) ||
	    !(CE = (char *) tgetstr("ce", &ptr))) {
	    printf("tinyirc: sorry, no termcap cm,cs,ce: dumb mode set\n");
	    dumb = 1;
	}
	if (!dumb) {
	    DC = (char *) tgetstr("dc", &ptr);
	    wasdate = 0;
	    signal(SIGINT, cleanup);
	    signal(SIGHUP, cleanup);
	    signal(SIGKILL, cleanup);
	    signal(SIGQUIT, cleanup);
	    signal(SIGSTOP, cleanup);
	    signal(SIGSEGV, cleanup);
	    savetty();
	    raw();
	    tputs_x(tgoto(CS, LI - 3, 0));
	    updatestatus();
	}
    }
    for (i = 0; i < HISTLEN; i++)
	history[i] = (char *) calloc(512, sizeof(char));
    linein = history[histline = 0];
    while (sok && !beenden) {
	FD_ZERO(&readfs);
	FD_SET(sockfd, &readfs);
	FD_SET(stdinfd, &readfs);
	if (!dumb) {
	    time_out.tv_sec = 61;
	    time_out.tv_usec = 0;
	}
	if (select(FD_SETSIZE, &readfs, NULL, NULL, (dumb ? NULL : &time_out))) {
	    if (FD_ISSET(stdinfd, &readfs))
		userinput();
	    if (FD_ISSET(sockfd, &readfs))
		sok = serverinput();
	    if (!wasdate)
		updatestatus();
	} else
	    updatestatus();
	if (!dumb) {
	    tputs_x(tgoto(CM, curx % CO, LI - 1));
	    fflush(stdout);
	}
    }
    if (!dumb) {
	tputs_x(tgoto(CS, -1, -1));
	tputs_x(tgoto(CM, 0, LI - 1));
	resetty();
    }
    exit(0);
}
