#include <stdio.h>

struct NSSdoof {
	const char *text;
#define PRUint32 size_t
	size_t length;
};

struct NSSdoof foo[2] = {
  { (void *)"@(#) $MirOS: ports/security/nss/files/certdata.c,v 1.1+1 2010/03/23 20:44:19 tg x $""; @(#) $miros: ports/security/nss/files/certdata.txt,v 1.2 2010/07/22 14:21:10 tg Exp $""; @(#) $RCSfile: certdata.perl,v $ $Revision: 1.12 $ $Date: 2008/01/23 07:34:49 $", (PRUint32)252 }
,
  { (void *)"@(#) $MirOS: ports/security/nss/files/certdata.txt,v 1.2 2010/07/22 14:21:10 tg Exp $""; @(#) $RCSfile: certdata.perl,v $ $Revision: 1.12 $ $Date: 2008/01/23 07:34:49 $", (PRUint32)167 }
};

int
main(void)
{
	printf("old { %zu -> %zu }  new { %zu -> %zu }\n",
	    foo[1].length, strlen(foo[1].text) + 1,
	    foo[0].length, strlen(foo[0].text) + 1);
	return (0);
}
