/* $Xorg: genauth.c,v 1.5 2001/02/09 02:05:40 xorgcvs Exp $ */
/*

Copyright 1988, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from The Open Group.

*/
/* $XFree86: xc/programs/xdm/genauth.c,v 3.25 2004/06/24 02:21:16 tsi Exp $ */

/*
 * xdm - display manager daemon
 * Author:  Keith Packard, MIT X Consortium
 */

# include   <X11/Xauth.h>
# include   <X11/Xos.h>

# include   "dm.h"
# include   "dm_auth.h"
# include   "dm_error.h"

#include <errno.h>

#include <time.h>
#define Time_t time_t

#ifdef HASXDMAUTH
static unsigned char	key[8];
#endif

#ifdef DEV_RANDOM
extern char	*randomDevice;
#endif

#ifdef HASXDMAUTH

typedef unsigned char auth_cblock[8];	/* block size */

typedef struct auth_ks_struct { auth_cblock _; } auth_wrapper_schedule[16];

extern int _XdmcpAuthSetup(unsigned char *, auth_wrapper_schedule);
extern int _XdmcpAuthDoIt(unsigned char *, unsigned char *, 
    auth_wrapper_schedule, int);
extern void _XdmcpWrapperToOddParity(unsigned char *, unsigned char *);

static void
longtochars (long l, unsigned char *c)
{
    c[0] = (l >> 24) & 0xff;
    c[1] = (l >> 16) & 0xff;
    c[2] = (l >> 8) & 0xff;
    c[3] = l & 0xff;
}

#endif

#ifdef POLL_DEV_RANDOM
#include <poll.h>
static int
pollRandomDevice (int fd)
{
    struct pollfd fds;

    fds.fd = fd;
    fds.events = POLLIN | POLLRDNORM;
    /* Wait up to 5 seconds for entropy to accumulate */
    return poll(&fds, 1, 5000);
}
#else
#define pollRandomDevice(fd) 1
#endif

#if !defined(ARC4_RANDOM)
#error ugly
#endif /* !ARC4_RANDOM && !DEV_RANDOM */


#ifdef HASXDMAUTH
static void
InitXdmcpWrapper (void)
{
    CARD32 sum[4];

#ifdef	ARC4_RANDOM
    sum[0] = arc4random();
    sum[1] = arc4random();
    *(u_char *)sum = 0;

    _XdmcpWrapperToOddParity((unsigned char *)sum, key);
#else
    unsigned char   tmpkey[8];

#ifdef DEV_RANDOM
    int fd;
    
    if ((fd = open(randomDevice, O_RDONLY)) >= 0) {
	if (pollRandomDevice(fd) && read(fd, tmpkey, 8) == 8) {
	    tmpkey[0] = 0;
	    _XdmcpWrapperToOddParity(tmpkey, key);
	    close(fd);
	    return;	
	} else {
	    close(fd);
	}
    } else {
	LogError("Cannot open randomDevice \"%s\", errno = %d\n", 
	  randomDevice, errno);
    }
#endif    
    /*  Try some pseudo-random number genrator daemon next */
    if (prngdSocket != NULL || prngdPort != 0) {
	    if (get_prngd_bytes((void *)tmpkey, sizeof(tmpkey), prngdPort, 
		    prngdSocket) == 0) {
		    tmpkey[0] = 0;
		    _XdmcpWrapperToOddParity(tmpkey, key);
		    return;
	    }
    }
    /* Fall back if no other source of random number was found */
    AddPreGetEntropy();
    pmd5_hash (sum, epool);
    add_entropy (sum, 1);
    pmd5_hash (sum, epool + 16);
    add_entropy (sum + 2, 1);

    longtochars (sum[0], tmpkey+0);
    longtochars (sum[1], tmpkey+4);
    tmpkey[0] = 0;
    _XdmcpWrapperToOddParity (tmpkey, key);
#endif
}

#endif


int
GenerateAuthData (char *auth, int len)
{
#ifdef HASXDMAUTH
    int		    i, bit;
    auth_wrapper_schedule    schedule;
    unsigned char	    data[8];
    static int	    xdmcpAuthInited;
    long	    ldata[2];

#ifdef ITIMER_REAL
    struct timeval  now;

    X_GETTIMEOFDAY (&now);
    ldata[0] = now.tv_usec;
    ldata[1] = now.tv_sec;
#else
    ldata[0] = time ((long *) 0);
    ldata[1] = getpid ();
#endif
    
    longtochars (ldata[0], data+0);
    longtochars (ldata[1], data+4);
    if (!xdmcpAuthInited)
    {
	InitXdmcpWrapper ();
	xdmcpAuthInited = 1;
    }
    _XdmcpAuthSetup (key, schedule);
    for (i = 0; i < len; i++) {
	auth[i] = 0;
	for (bit = 1; bit < 256; bit <<= 1) {
	    _XdmcpAuthDoIt (data, data, schedule, 1);
	    if ((data[0] + data[1]) & 0x4)
		auth[i] |= bit;
	}
    }
    return 1;
#else /* !XDMAUTH */
#ifdef ARC4_RANDOM
    arc4random_buf(auth, len);
    return 1;
#else /* !ARC4_RANDOM */
    CARD32 tmp[4] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };
#ifdef DEV_RANDOM
    int fd;
    
    if ((fd = open(randomDevice, O_RDONLY)) >= 0) {
	if (pollRandomDevice(fd) && 
	    read(fd, auth, len) == len) {
	    close(fd);
	    return 1;
	}
	close(fd);
	LogError("Cannot read randomDevice \"%s\", errno=%d\n",
		 randomDevice, errno);
    } else 
	LogError("Cannot open randomDevice \"%s\", errno = %d\n", 
		 randomDevice, errno);
#endif /* DEV_RANDOM */
    /*  Try some pseudo-random number genrator daemon next */
    if (prngdSocket != NULL || prngdPort != 0) {
	    if (get_prngd_bytes(auth, len, prngdPort, prngdSocket) == 0) {
		    return 1;
	    }
    }
    /* Fallback if not able to get from /dev/random */
    AddPreGetEntropy();
    pmd5_hash (tmp, epool);
    add_entropy (tmp, 1);
    pmd5_hash (tmp, epool + 16);
    add_entropy (tmp + 2, 1);
    memcpy (auth, tmp, len);
    return 1;
#endif /* !ARC4_RANDOM */
#endif /* !HASXDMAUTH */
}
