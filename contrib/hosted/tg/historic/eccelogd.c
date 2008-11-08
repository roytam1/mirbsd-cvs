/* compile: gcc -O2 -Wall -ansi -o eccelogd eccelogd.c -lbsd */

/* $MirOS: src/share/misc/licence.template,v 1.24 2008/04/22 11:43:31 tg Rel $ */

/*-
 * Copyright (c) 2000
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

/****************************************************************************
* eccelogd Version 1.00 - the ecce!GNU/Linux system log daemon
* see also (not included in this distribution): syslogd(8)
*----------------------------------------------------------------------------
* This is a simple daemon that puts all the stuff to be logged to tty12.
* Now it seems to work... thanks to ISBN 3-446-21093-8 (german reference)
* Remember that the root filesystem has to be mounted read-write first!
*****************************************************************************/

#include <fcntl.h>
#include <linux/kdev_t.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

void main(void);
int daemon(int,int); /* from libbsd */

static const char nl='\n';
char *buf="error: must be root to do this!\n";

void main(void)
{
	struct sockaddr_un s1un,s2un;
	int pid,term,s1,s2,gr;

	if(getuid()) {
		write(2,&buf,strlen(buf));
		exit(-1);
	}
	buf=(char*)malloc(1200);

	unlink("/dev/log");   /* just in case... */
	unlink("/dev/tty12"); /* dito. thats why linux specific... */
	if(mknod("/dev/tty12",((S_IFCHR)|(S_IWUSR)),MKDEV(4,12)))
		exit(-1);
	if(daemon(0,0))
		exit(-1);

	sprintf(buf,"%u\n",getpid());

	if((pid=open("/var/run/eccelogd.pid",
	    ((O_RDWR)|(O_CREAT)|(O_EXCL)),00644)) <0)
		exit(-1);
	write(pid,&buf,strlen(buf));
	close(pid);

	s1un.sun_family=AF_UNIX;
	strcpy(s1un.sun_path,"/dev/log");

	if((s1=socket(AF_UNIX,SOCK_STREAM,0)) <0)
		exit(-1);
	if((bind(s1,(struct sockaddr*)&s1un,sizeof(s1un))) <0) {
		close(s1);
		exit(-1);
	}
	if((chmod("/dev/log",0666)) <0) {
		close(s1);
		exit(-1);
	}
	if((listen(s1,3)) <0) {
		close(s1);
		exit(-1);
	}

	if((term=open("/dev/tty12",((O_WRONLY)|(O_NOCTTY)))) <0) {
		close(s1);
		exit(-1);
	}

	sprintf(buf,"eccelogd [%u]: started by sysop.\n",getpid());
	write(term,buf,strlen(buf));

	gr=sizeof(s2un);
	while(1)
		if((s2=accept(s1,(struct sockaddr*)&s2un,&gr)) < 0) {
			close(s1);close(term);
			exit(-1);
		} else if((pid=fork()) <0) {
			close(s1);close(s2);close(term);
			exit(-1);
		} else if(!pid) { /** CHILD - actually does the work **/
			close(s1); /* does not belong to us */
			write(term,buf,read(s2,buf,1200));
			write(term,&nl,1);
			close(term);close(s2);
			exit(0);
		} else	close(s2); /** PARENT - close child's socket **/
}
