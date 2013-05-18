/**	$MirOS: src/sys/stand/boot/cmd.c,v 1.23 2009/01/31 22:43:26 tg Exp $	*/
/*	$OpenBSD: cmd.c,v 1.59 2007/04/27 10:08:34 tom Exp $	*/

/*
 * Copyright (c) 2008-2009 Thorsten Glaser
 * Copyright (c) 1997-1999 Michael Shalayeff
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/reboot.h>
#include <libsa.h>
#include "cmd.h"

#define CTRL(c)	((c)&0x1f)

static int Xboot(void);
#ifndef SMALL_BOOT
static int Xcat(void);
#endif
static int Xecho(void);
static int Xhelp(void);
#ifndef SMALL_BOOT
static int Xls(void);
#endif
static int Xnop(void);
static int Xreboot(void);
static int Xstty(void);
#ifndef SMALL_BOOT
static int Xtime(void);
#endif
#ifdef MACHINE_CMD
static int Xmachine(void);
extern const struct cmd_table MACHINE_CMD[];
#endif
#ifndef SMALL_BOOT
static int Xmacro(void);
#endif
extern int Xset(void);
#ifndef SMALL_BOOT
extern int Xenv(void);
#endif

#ifdef CHECK_SKIP_CONF
extern int CHECK_SKIP_CONF(void);
#endif

extern const struct cmd_table cmd_set[];
struct cmd_table cmd_table[] = {
	{"#",      CMDT_CMD, Xnop},  /* XXX must be first */
	{"boot",   CMDT_CMD, Xboot},
#ifndef SMALL_BOOT
	{"cat",    CMDT_CMD, Xcat},
#endif
	{"echo",   CMDT_CMD, Xecho},
#ifndef SMALL_BOOT
	{"env",    CMDT_CMD, Xenv},
#endif
	{"help",   CMDT_CMD, Xhelp},
#ifndef SMALL_BOOT
	{"ls",     CMDT_CMD, Xls},
#endif
#ifdef MACHINE_CMD
	{"machine",CMDT_MDC, Xmachine},
#endif
#ifndef SMALL_BOOT
	{"macro",  CMDT_CMD, Xmacro},
#endif
	{"reboot", CMDT_CMD, Xreboot},
	{"set",    CMDT_SET, Xset},
	{"stty",   CMDT_CMD, Xstty},
#ifndef SMALL_BOOT
	{"time",   CMDT_CMD, Xtime},
	/* space for four macros */
	{NULL,     CMDT_MAC, NULL},
	{NULL,     CMDT_MAC, NULL},
	{NULL,     CMDT_MAC, NULL},
	{NULL,     CMDT_MAC, NULL},
#endif
	{NULL,     CMDT_EOL, NULL}
};

#ifndef SMALL_BOOT
static void ls(char *, struct stat *);
#endif
static int readline(char *, size_t, int);
char *nextword(char *);
static char *whatcmd(const struct cmd_table **ct, char *);

char cmd_buf[CMD_BUFF_SIZE];

int
getcmd(void)
{
	cmd.cmd = NULL;

	if (!readline(cmd_buf, sizeof(cmd_buf), cmd.timeout))
		cmd.cmd = cmd_table;

	return docmd();
}

int
read_conf(void)
{
#ifndef INSECURE
	struct stat sb;
#endif
	int fd, rc = 0;

#ifdef CHECK_SKIP_CONF
	if (CHECK_SKIP_CONF()) {
		printf("boot.cfg processing skipped at operator request\n");
		return -1;		/* Pretend file wasn't found */
	}
#endif

	if ((fd = open(qualify(cmd.conf), 0)) < 0) {
		if (errno != ENOENT && errno != ENXIO) {
			printf("open(%s): %s\n", cmd.path, strerror(errno));
			return 0;
		}
		return -1;
	}

#ifndef INSECURE
	(void) fstat(fd, &sb);
	if (sb.st_uid || (sb.st_mode & 2)) {
		printf("non-secure %s, will not proceed\n", cmd.path);
		close(fd);
		return -1;
	}
#endif

	do {
		char *p = cmd_buf;

		cmd.cmd = NULL;

		do {
			rc = read(fd, p, 1);
		} while (rc > 0 && *p++ != '\n' &&
		    (p-cmd_buf) < sizeof(cmd_buf));

		if (rc < 0) {			/* Error from read() */
			printf("%s: %s\n", cmd.path, strerror(errno));
			break;
		}

		if (rc == 0) {			/* eof from read() */
			if (p != cmd_buf) {	/* Line w/o trailing \n */
				*p = '\0';
				rc = docmd();
				break;
			}
		} else {			/* rc > 0, read a char */
			p--;			/* Get back to last character */

			if (*p != '\n') {	/* Line was too long */
				printf("%s: line too long\n", cmd.path);

				/* Don't want to run the truncated command */
				rc = -1;
			}

			*p = '\0';
		}

	} while (rc > 0 && !(rc = docmd()));

	close(fd);
	return rc;
}

int
docmd(void)
{
	char *p = NULL, *cp = NULL;
	const struct cmd_table *ct = cmd_table, *cs;
	int rv;

	cmd.argc = 1;
	if (cmd.cmd == NULL) {

		/* command */
		p = cmd_buf;
 cmdparse_loop:
		while (*p == ' ' || *p == '\t')
			++p;
		if (*p == '#' || *p == '\0') { /* comment or empty string */
#ifdef DEBUG
			printf("rem\n");
#endif
			return 0;
		}
		cp = p;
		while (*cp && *cp != '`')
			++cp;
		if (*cp == '`')
			*cp++ = '\0';
		else
			cp = NULL;
		ct = cmd_table;
		cs = NULL;
		cmd.argv[cmd.argc] = p; /* in case it's shortcut boot */
		p = whatcmd(&ct, p);
		if (ct == NULL) {
			cmd.argc++;
			ct = cmd_table;
#ifndef SMALL_BOOT
		} else if (ct->cmd_type == CMDT_MAC) {
			memcpy((p = cmd_buf), (void *)ct->cmd_exec,
			    strlen((char *)ct->cmd_exec) + 1);
			cmd.argc = 1;
			goto cmdparse_loop;
#endif
		} else if (ct->cmd_type == CMDT_SET && p != NULL) {
			cs = cmd_set;
#ifdef MACHINE_CMD
		} else if (ct->cmd_type == CMDT_MDC && p != NULL) {
			cs = MACHINE_CMD;
#endif
		}

		if (cs != NULL) {
			p = whatcmd(&cs, p);
			if (cs == NULL) {
				printf("%s: syntax error\n", ct->cmd_name);
				rv = 0;
				goto cmdparse_next;
			}
			ct = cs;
		}
		cmd.cmd = ct;
	}

	cmd.argv[0] = ct->cmd_name;
	while (p && cmd.argc+1 < sizeof(cmd.argv) / sizeof(cmd.argv[0])) {
		cmd.argv[cmd.argc++] = p;
		p = nextword(p);
	}
	cmd.argv[cmd.argc] = NULL;

	rv = (*cmd.cmd->cmd_exec)();
 cmdparse_next:
	if (rv == 0 && cp != NULL && *cp != '\0') {
		ct = cmd_table;
		cmd.argc = 1;
		p = cp;
		goto cmdparse_loop;
	}
	return (rv);
}

static char *
whatcmd(const struct cmd_table **ct, char *p)
{
	char *q;
	int l;

	q = nextword(p);

	for (l = 0; p[l]; l++)
		;

	while ((*ct)->cmd_type != CMDT_EOL)
		if ((*ct)->cmd_name != NULL && !strncmp(p, (*ct)->cmd_name, l))
			break;
		else
			(*ct)++;

	if ((*ct)->cmd_type == CMDT_EOL)
		*ct = NULL;

	return q;
}

static int
readline(char *buf, size_t n, int to)
{
#ifdef DEBUG
	extern int debug;
#endif
	char *p = buf, ch;

	/* Only do timeout if greater than 0 */
	if (to > 0) {
		u_long i = 0;
		time_t tt = getsecs() + to;
#ifdef DEBUG
		if (debug > 2)
			printf ("readline: timeout(%d) at %u\n", to, tt);
#endif
		/* check for timeout expiration less often
		   (for some very constrained archs) */
		while (!cnischar())
			if (!(i++ % 1000) && (getsecs() >= tt))
				break;

		if (!cnischar()) {
			memcpy(buf, "boot", 5);
			putchar('\n');
			return strlen(buf);
		}
	} else
		while (!cnischar())
			;

	/* User has typed something.  Turn off timeouts. */
	cmd.timeout = 0;

	while (1) {
		switch ((ch = getchar())) {
		case CTRL('u'):
			while (p > buf) {
				putchar('\177');
				p--;
			}
			continue;
		case '\n':
		case '\r':
			p[1] = *p = '\0';
			break;
		case '\b':
		case '\177':
			if (p > buf) {
				putchar('\177');
				p--;
			}
			continue;
		default:
			if (ch >= ' ' && ch < '\177') {
				if (p - buf < n-1)
					*p++ = ch;
				else {
					putchar('\007');
					putchar('\177');
				}
			}
			continue;
		}
		break;
	}

	return p - buf;
}

/*
 * Search for spaces/tabs after the current word. If found, \0 the
 * first one.  Then pass a pointer to the first character of the
 * next word, or NULL if there is no next word.
 */
char *
nextword(char *p)
{
	/* skip blanks */
	while (*p && *p != '\t' && *p != ' ')
		p++;
	if (*p) {
		*p++ = '\0';
		while (*p == '\t' || *p == ' ')
			p++;
	}
	if (*p == '\0')
		p = NULL;
	return p;
}

static void
print_help(const struct cmd_table *ct)
{
	for (; ct->cmd_name != NULL; ct++)
		printf(" %s", ct->cmd_name);
	putchar('\n');
}

static int
Xhelp(void)
{
	printf("commands:");
	print_help(cmd_table);
#ifdef MACHINE_CMD
	return Xmachine();
#else
	return 0;
#endif
}

#ifdef MACHINE_CMD
static int
Xmachine(void)
{
	printf("machine:");
	print_help(MACHINE_CMD);
	return 0;
}
#endif

static int
Xecho(void)
{
	int i;

	for (i = 1; i < cmd.argc; i++)
		printf("%s ", cmd.argv[i]);
	putchar('\n');
	return 0;
}

static int
Xstty(void)
{
	int sp;
	char *cp;
	dev_t dev;

	if (cmd.argc == 1)
		printf("%s speed is %d\n", ttyname(0), cnspeed(0, -1));
	else {
		dev = ttydev(cmd.argv[1]);
		if (dev == NODEV)
			printf("%s not a console device\n", cmd.argv[1]);
		else {
			if (cmd.argc == 2)
				printf("%s speed is %d\n", cmd.argv[1],
				       cnspeed(dev, -1));
			else {
				sp = 0;
				for (cp = cmd.argv[2]; *cp && isdigit(*cp); cp++)
					sp = sp * 10 + (*cp - '0');
				cnspeed(dev, sp);
			}
		}
	}

	return 0;
}

#ifndef SMALL_BOOT
static int
Xtime(void)
{
	time_t tt = getsecs();

	if (cmd.argc == 1)
		printf(ctime(&tt));
	else {
	}

	return 0;
}

static int
Xls(void)
{
	struct stat sb;
	char *p;
	int fd, nlin = 0;

	if (stat(qualify((cmd.argv[1]? cmd.argv[1]: "/.")), &sb) < 0) {
		printf("stat(%s): %s\n", cmd.path, strerror(errno));
		return 0;
	}

	if ((sb.st_mode & S_IFMT) != S_IFDIR)
		ls(cmd.path, &sb);
	else {
		if ((fd = opendir(cmd.path)) < 0) {
			printf ("opendir(%s): %s\n", cmd.path,
				strerror(errno));
			return 0;
		}

		p = cmd.path + strlen(cmd.path);
		*p++ = '/';
		*p = '\0';

		while(readdir(fd, p) >= 0) {
			if (++nlin >= 23) {
				printf("%s\n", "-- more --");
				if ((cngetc() | 0x20) == 'q')
					goto out;
				nlin = 0;
			}
			if (stat(cmd.path, &sb) < 0)
				printf("stat(%s): %s\n", cmd.path,
				       strerror(errno));
			else
				ls(p, &sb);
		}
 out:
		closedir (fd);
	}
	return 0;
}

#define lsrwx(mode,s) \
	putchar ((mode) & S_IROTH? 'r' : '-'); \
	putchar ((mode) & S_IWOTH? 'w' : '-'); \
	putchar ((mode) & S_IXOTH? *(s): (s)[1]);

static void
ls(char *name, struct stat *sb)
{
	putchar("-fc-d-b---l-s-w-"[(sb->st_mode & S_IFMT) >> 12]);
	lsrwx(sb->st_mode >> 6, (sb->st_mode & S_ISUID? "sS" : "x-"));
	lsrwx(sb->st_mode >> 3, (sb->st_mode & S_ISGID? "sS" : "x-"));
	lsrwx(sb->st_mode     , (sb->st_mode & S_ISTXT? "tT" : "x-"));

	printf (" %u,%u\t%lu\t%s\n", sb->st_uid, sb->st_gid,
	    (u_long)sb->st_size, name);
}
#undef lsrwx
#endif

int doboot = 1;

static int
Xnop(void)
{
	if (doboot) {
		doboot = 0;
		return (Xboot());
	}

	return 0;
}

static int
Xboot(void)
{
	if (cmd.argc > 1 && cmd.argv[1][0] != '-') {
		qualify((cmd.argv[1]? cmd.argv[1]: cmd.image));
		if (bootparse(2))
			return 0;
	} else {
		if (bootparse(1))
			return 0;
		snprintf(cmd.path, sizeof cmd.path, "%s:%s",
		    cmd.bootdev, cmd.image);
	}

	return 1;
}

/*
 * Qualifies the path adding necessary dev
 */

char *
qualify(char *name)
{
	char *p;

	for (p = name; *p; p++)
		if (*p == ':')
			break;
	if (*p == ':')
		memcpy(cmd.path, name, strlen(name) + 1);
	else
		snprintf(cmd.path, sizeof cmd.path, "%s:%s",
		    cmd.bootdev, name);
	return cmd.path;
}

static int
Xreboot(void)
{
	/* compile-time safeguard, fix cmd.h if this fails */
	char sizetest[sizeof(struct cmd_state) < CMD_STRUCT_SIZE ? 1 : -1]
	    __attribute__((unused));

	printf("Rebooting...\n");
	exit();
	return 0; /* just in case */
}

#ifndef SMALL_BOOT
static int
Xcat(void)
{
	int fd, rc = 0, i, nlin = 0;
	char abuf[80], *cp;

	if (!cmd.argv[1])
		return (0);
	if ((fd = open(qualify(cmd.argv[1]), 0)) < 0) {
		printf("open(%s): %s\n", cmd.argv[1], strerror(errno));
		return (0);
	}

	while ((rc = read(fd, abuf, 79)) > 0) {
		abuf[rc] = 0;
		cp = abuf;
		for (i = 0; i < rc; ++i) {
			if (abuf[i] != '\n')
				continue;
			if (++nlin < 23)
				continue;
			abuf[i] = 0;
			printf("%s\n%s", cp, "-- more --");
			if ((cngetc() | 0x20) == 'q')
				goto out;
			putchar('\n');
			cp = abuf + i + 1;
			nlin = 0;
		}
		printf("%s", cp);
	}
 out:
	putchar('\n');

	close(fd);
	return (0);
}

static int
Xmacro(void)
{
	struct cmd_table *ct = cmd_table, *ft;
	char ch, *cp, *s;
	int i;

	if (cmd.argc == 1) {
		printf("macros:");
		while (ct->cmd_type != CMDT_EOL) {
			if (ct->cmd_type == CMDT_MAC && ct->cmd_name)
				printf(" %s", ct->cmd_name);
			++ct;
		}
		putchar('\n');
	} else {
		ft = NULL;
		while (ct->cmd_type != CMDT_EOL) {
			if (ct->cmd_type == CMDT_MAC) {
				if (ct->cmd_name == NULL)
					ft = ct;
				else if (!strcmp(ct->cmd_name, cmd.argv[1]))
					break;
			}
			++ct;
		}
		if (cmd.argc == 2) {
			if (ct->cmd_type != CMDT_EOL) {
				free(ct->cmd_name, 0);
				free(ct->cmd_exec, CMD_BUFF_SIZE);
				ct->cmd_name = NULL;
			}
			return (0);
		}
		if (ct->cmd_type == CMDT_EOL && (ct = ft) == NULL) {
			printf("macro: no free entries\n");
			return (0);
		}
		ct->cmd_name = alloc((i = strlen(cmd.argv[1]) + 1));
		memcpy(ct->cmd_name, cmd.argv[1], i);
		ct->cmd_exec = alloc(CMD_BUFF_SIZE);
		i = 2;
		cp = (char *)ct->cmd_exec;
		while ((s = cmd.argv[i])) {
			if (i > 2)
				*cp++ = ' ';
			while ((ch = *s++))
				/* macro text ~ is a newline */
				*cp++ = ch == '~' ? '`' : ch;
			++i;
		}
		*cp = '\0';
	}
	return (0);
}
#endif
