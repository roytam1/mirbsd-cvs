/* $MirOS$ */

/*-
 * Copyright (c) 1979, 1980, 1981, 1986, 1988, 1990, 1991, 1992
 *     The Regents of the University of California.
 * Copyright (C) Caldera International Inc.  2001-2002.
 * Copyright (c) 2003, 2004
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
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
 */

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#define MAXENT 50

__SCCSID("@(#)addbib.c	4.3 (Berkeley) 4/18/91");
__RCSID("$MirOS$");

struct skeleton {
	char prompt[20];	/* prompt user for entry */
	char keylet[5]; 	/* key letter for database */
} bibskel[MAXENT] = {
	"   Author:",	"%A",
	"    Title:",	"%T",
	"  Journal:",	"%J",
	"   Volume:", 	"%V",
	"    Pages:",	"%P",
	"Publisher:",	"%I",
	"     City:", 	"%C",
	"     Date:", 	"%D",
	"    Other:",	"%O",
	" Keywords:",	"%K",	};

int entries = 10;	/* total number of entries in bibskel */
int abstract = 1;	/* asking for abstracts is the default */

usage()			/* print proper usage and exit */
{
	puts("Usage:  addbib [-p promptfile] [-a] database");
	puts("\t-p: the promptfile defines alternate fields");
	puts("\t-a: don't include prompting for the abstract");
	exit(1);
}

main(argc, argv)	/* addbib: bibliography entry program */
int argc;
char *argv[];
{
	FILE *fp, *fopen();
	int i;

	if (argc == 1)
	{
		puts("You must specify a bibliography file (database).");
		usage();
	}
	for (i = 1; argv[i][0] == '-'; i++)
	{
		if (argv[i][1] == 'p')
		{
			if (i >= argc - 2)
			{
				puts("Not enough arguments for -p option.");
				usage();
			}
			rd_skel(argv[++i]);
		}
		else if (argv[i][1] == 'a')
		{
			if (i >= argc - 1)
			{
				puts("No bibliofile specified after -a.");
				usage();
			}
			abstract = 0;
		}
		else  /* neither -p nor -a */
		{
			printf("Invalid command line flag: %s\n", argv[i]);
			usage();
		}
	}
	if (i < argc - 1)
	{
		puts("Too many arguments with no options.");
		usage();
	}
	if ((fp = fopen(argv[i], "a")) == NULL)
	{
		perror(argv[i]);
		exit(1);
	}
	addbib(fp, argv[i]);	/* loop for input */
	exit(0);
}

addbib(fp, argv)	/* add entries to a bibliographic database */
FILE *fp;
char *argv;
{
	char line[BUFSIZ];
	int i = 0, firstln, repeat = 0, escape = 0;

	printf("Instructions? ");
	fgets(line, BUFSIZ, stdin);
	if (line[0] == 'y' || line[0] == 'Y')
		instruct();
	while (1)
	{
		putchar('\n');
		putc('\n', fp);
		for (i = 0; i < entries; i++)
		{
			printf("%s\t", bibskel[i].prompt);
			if (fgets(line, BUFSIZ, stdin) == NULL)
			{
				clearerr(stdin);
				break;
			}
			if (line[0] == '-' && line[1] == '\n')
			{
				i -= 2;
				if (i < -1)
				{
					printf("Too far back.\n");
					i++;
				}
				continue;
			}
			else if (line[strlen(line)-2] == '\\')
			{
				if (line[0] != '\\')
				{
					line[strlen(line)-2] = '\n';
					line[strlen(line)-1] = 0;
					trim(line);
					fprintf(fp, "%s %s",
						bibskel[i].keylet, line);
				}
				printf("> ");
				again:
				fgets(line, BUFSIZ, stdin);
				if (line[strlen(line)-2] == '\\')
				{
					line[strlen(line)-2] = '\n';
					line[strlen(line)-1] = 0;
					trim(line);
					fputs(line, fp);
					printf("> ");
					goto again;
				}
				trim(line);
				fputs(line, fp);
			}
			else if (line[0] != '\n')
			{
				trim(line);
				fprintf(fp, "%s %s", bibskel[i].keylet, line);
			}
		}
		if (abstract)
		{
			puts(" Abstract: (ctrl-d to end)");
			firstln = 1;
			while (fgets(line, BUFSIZ, stdin))
			{
				if (firstln && line[0] != '%')
				{
					fprintf(fp, "%%X ");
					firstln = 0;
				}
				fputs(line, fp);
			}
			clearerr(stdin);
		}
		fflush(fp);	/* write to file at end of each cycle */
		if (ferror(fp))
		{
			perror(argv);
			exit(1);
		}
		editloop:
		printf("\nContinue? ");
			fgets(line, BUFSIZ, stdin);
		if (line[0] == 'e' || line[0] == 'v')
		{
			bibedit(fp, line, argv);
			goto editloop;
		}
		if (line[0] == 'q' || line[0] == 'n')
			return;
	}
}

trim(line)		/* trim line of trailing white space */
char line[];
{
	int n;

	n = strlen(line);
	while (--n >= 0)
	{
		if (!isspace(line[n]))
			break;
	}
	line[++n] = '\n';
	line[++n] = 0;
}

bibedit(fp, cmd, arg)	/* edit database with edit, ex, or vi */
FILE *fp;
char *cmd, *arg;
{
	int i = 0, status;

	fclose(fp);
	while (!isspace(cmd[i]))
		i++;
	cmd[i] = 0;
	if (fork() == 0)
	{
		if (cmd[0] == 'v' && cmd[1] == 'i')
			execlp(cmd, cmd, "+$", arg, NULL);
		else /* either ed, ex, or edit */
			execlp(cmd, cmd, arg, NULL);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait(&status);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if ((fp = fopen(arg, "a")) == NULL)
	{
		perror(arg);
		exit(1);
	}
}

instruct()		/* give user elementary directions */
{
	putchar('\n');
	puts("Addbib will prompt you for various bibliographic fields.");
	puts("If you don't need a particular field, just hit RETURN,");
	puts("\tand that field will not appear in the output file.");
	puts("If you want to return to previous fields in the skeleton,");
	puts("\ta single minus sign will go back a field at a time.");
	puts("\t(This is the best way to input multiple authors.)");
	puts("If you have to continue a field or add an unusual field,");
	puts("\ta trailing backslash will allow a temporary escape.");
	puts("Finally, (without -a) you will be prompted for an abstract.");
	puts("Type in as many lines as you need, and end with a ctrl-d.");
	puts("To quit, type `q' or `n' when asked if you want to continue.");
	puts("To edit the database, type `edit', `vi', or `ex' instead.");
}

rd_skel(arg)		/* redo bibskel from user-supplied file */
char *arg;
{
	FILE *pfp, *fopen();
	char str[BUFSIZ];
	int entry, i, j;

	if ((pfp = fopen(arg, "r")) == NULL)
	{
		fprintf(stderr, "Promptfile ");
		perror(arg);
		exit(1);
	}
	for (entry = 0; fgets(str, BUFSIZ, pfp); entry++)
	{
		for (i = 0; str[i] != '\t' && str[i] != '\n'; i++)
			bibskel[entry].prompt[i] = str[i];
		bibskel[entry].prompt[i] = 0;
		if (str[i] == '\n')
		{
			fprintf(stderr, "No tabs between promptfile fields.\n");
			fprintf(stderr, "Format: prompt-string <TAB> %%key\n");
			exit(1);
		}
		for (i++, j = 0; str[i] != '\n'; i++, j++)
			bibskel[entry].keylet[j] = str[i];
		bibskel[entry].keylet[j] = 0;

		if (entry >= MAXENT)
		{
			fprintf(stderr, "Too many entries in promptfile.\n");
			exit(1);
		}
	}
	entries = entry;
	fclose(pfp);
}
