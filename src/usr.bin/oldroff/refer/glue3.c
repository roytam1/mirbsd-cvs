/* $MirOS$ */
/*-
 * Copyright (c) 1979, 1980, 1981, 1986, 1988, 1990, 1991, 1992
 *     The Regents of the University of California.
 * Copyright (C) Caldera International Inc.  2001-2002.
 * Copyright (c) 2003, 2004
 *	Thorsten Glaser <tg@66h.42h.de>
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

#include <sys/cdefs.h>
__SCCSID("@(#)glue3.c	4.4 (Berkeley) 4/18/91");
__RCSID("$MirOS$");

#include "refer..c"
#include "pathnames.h"

#define move(x, y) close(y); dup(x); close(x);

corout(in, out, rprog, arg, outlen)
char *in, *out, *rprog;
{
	int pipev[2], fr1, fr2, fw1, fw2, n;

	if (strcmp (rprog, "hunt") ==0)
		return(callhunt(in, out, arg, outlen));
	if (strcmp (rprog, "deliv")==0)
		return(dodeliv(in, out, arg, outlen));
	pipe (pipev); 
	fr1= pipev[0]; 
	fw1 = pipev[1];
	pipe (pipev); 
	fr2= pipev[0]; 
	fw2 = pipev[1];
	if (fork()==0)
	{
		close (fw1); 
		close (fr2);
		move (fr1, 0);
		move (fw2, 1);
		if (rprog[0]!= '/')
			chdir(_PATH_LIB);
		execl(rprog, rprog, arg, NULL);
		err ("Can't run %s", rprog);
	}
	close(fw2); 
	close(fr1);
	write (fw1, in , strlen(in));
	close(fw1);
	wait(0);
	n = read (fr2, out, outlen);
	out[n]=0;
	close(fr2);
}

# define ALEN 50

callhunt(in, out, arg, outlen)
char *in, *out, *arg;
{
	char *argv[20], abuff[ALEN];
	extern int typeindex;
	int argc;
	extern char one[];
	extern int onelen;
	argv[0] = "hunt";
	argv[1] = "-i";
	argv[2] = in;
	argv[3] = "-t";
	argv[4] = out;
	argv[5] = (char *)outlen;	/* Horrid kludge, see option parsing
					   in huntmain() in glue1.c. */
	argv[6] = "-T";
	argv[7] = "-F1";
	argv[8] = "-o";
	argv[9] = one;
	argv[10] = (char *)onelen;		/* Horrid kludge again */
	argv[11] = abuff; 
	strcpy (abuff,arg);
	if (strlen(abuff) > ALEN)
		err("abuff not big enough %d", strlen(abuff));
	argc = 6;
	huntmain (argc,argv);
	return(0);
}

dodeliv(in, out, arg, outlen)
char *in, *out, *arg;
{
# if D1
	fprintf(stderr, "in dodeliv, arg /%s/\n", arg?arg:"");
# endif
	if (arg && arg[0])
		chdir(arg);
	findline(in, out, outlen, 0L);
	restodir();
}
