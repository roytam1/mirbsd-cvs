/* compile: gcc -O2 -Wall -ansi -o eccelogd eccelogd.c -lbsd */

/****************************************************************************
* The code beyond is material protected by the following Terms and Copyright:
* (c) 2000 Thorsten Glaser <DrSid86@hotmail.com>
* This code may freely be used, distributed, compiled, modified etc.  also as
* a part of commercial distribution. You must not remove  the visible comment
* "includes material provided by Th.Glaser"  (or more authors).  You must not
* use our code under  your name and/or copyright;  neither you are allowed to
* distribute modified code  without stating (beyond the second line above) it
* is modified. (Add your copyright beyond.) - You generally _must not_ damage
* the authors' mental ownership. Source code even of modificated work must be
* made available, also if the work is part of a  commercial distribution, and
* under no different  Terms and Conditions than above, under our names inclu-
* ding yours. If the work is included into another work or even just gave you
* the idea, solely the part standing under this copyright and License must be
* made available,  including your modifications.  The remainder parts of your
* work don't need to be free.
* Due to the authors being a human it is impossible to write errorless and/or
* error-tolerant code. Due to this code being marked "free", even not "public
* domain", I am not responsible for making update, bugfixes, documentation of
* any kind; neither I am responsible for anything  done (or not done) by this
* code. This also affects every people  that has modificated  the code beyond
* and put the name under my own one that resides in the second star-initiated
* line.  The code beyond is provided "AS IS" and with NO further restrictions
* and/or warranties than granted above, EVEN IF STATED OTHERWISE, e.g. by the
* law, even if done in writing. If you use this piece of code you are automa-
* tically accepting this Conditions. (This is signed by every author and con-
* tributor that wrote his name above.)
* I wish you can enjoy our hardly done work.                    Mirabilos(TM)
*****************************************************************************
* eccelogd Version 1.00 - the ecce!GNU/Linux system log daemon
* see also (not included in this distribution): syslogd(8)
*----------------------------------------------------------------------------
* This is a simple daemon that puts all the stuff to be logged to tty12.
* Now it seems to work... thanks to ISBN 3-446-21093-8 (german reference)
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
