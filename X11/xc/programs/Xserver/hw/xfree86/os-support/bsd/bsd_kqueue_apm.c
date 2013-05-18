/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/bsd/bsd_kqueue_apm.c,v 1.6 2004/02/13 23:58:46 dawes Exp $ */
/*
 * Copyright (C) 2001 The XFree86 Project, Inc.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 *   1.  Redistributions of source code must retain the above copyright
 *       notice, this list of conditions, and the following disclaimer.
 *
 *   2.  Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer
 *       in the documentation and/or other materials provided with the
 *       distribution, and in the same place and form as other copyright,
 *       license and disclaimer information.
 *
 *   3.  The end-user documentation included with the redistribution,
 *       if any, must include the following acknowledgment: "This product
 *       includes software developed by The XFree86 Project, Inc
 *       (http://www.xfree86.org/) and its contributors", in the same
 *       place and form as other third-party acknowledgments.  Alternately,
 *       this acknowledgment may appear in the software itself, in the
 *       same form and location as other such third-party acknowledgments.
 *
 *   4.  Except as contained in this notice, the name of The XFree86
 *       Project, Inc shall not be used in advertising or otherwise to
 *       promote the sale, use or other dealings in this Software without
 *       prior written authorization from The XFree86 Project, Inc.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE XFREE86 PROJECT, INC OR ITS CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* $OpenBSD: bsd_kqueue_apm.c,v 1.5 2002/07/30 23:07:42 matthieu Exp $ */

#include "X.h"
#include "os.h"
#include "xf86.h"
#include "xf86Priv.h"
#define XF86_OS_PRIVS
#include "xf86_OSproc.h"
#include "xf86_OSlib.h"

#include <sys/event.h>
#include <machine/apmvar.h>

#define _PATH_APM_SOCKET	"/var/run/apmdev"
#define _PATH_APM_DEV		"/dev/apm"
#define _PATH_APM_CTLDEV	"/dev/apmctl"

static pointer APMihPtr = NULL;
static int devFd = -1;
static int ctlFd = -1;
static void bsdCloseAPM(void);

static struct {
    u_int apmBsd;
    pmEvent xf86;
} bsdToXF86Array [] = {
    { APM_STANDBY_REQ, XF86_APM_SYS_STANDBY },
    { APM_SUSPEND_REQ, XF86_APM_SYS_SUSPEND },
    { APM_NORMAL_RESUME, XF86_APM_NORMAL_RESUME },
    { APM_CRIT_RESUME, XF86_APM_CRITICAL_RESUME },
    { APM_BATTERY_LOW, XF86_APM_LOW_BATTERY },
    { APM_POWER_CHANGE, XF86_APM_POWER_STATUS_CHANGE },
    { APM_UPDATE_TIME, XF86_APM_UPDATE_TIME },
    { APM_CRIT_SUSPEND_REQ, XF86_APM_CRITICAL_SUSPEND },
    { APM_USER_STANDBY_REQ, XF86_APM_USER_STANDBY },
    { APM_USER_SUSPEND_REQ, XF86_APM_USER_SUSPEND },
    { APM_SYS_STANDBY_RESUME, XF86_APM_STANDBY_RESUME },
#ifdef APM_CAPABILITY_CHANGE
    { APM_CAPABILITY_CHANGE, XF86_APM_CAPABILITY_CHANGED },
#endif
};

#define numApmEvents (sizeof(bsdToXF86Array) / sizeof(bsdToXF86Array[0]))

static pmEvent
bsdToXF86(int type)
{
    int i;

    for (i = 0; i < numApmEvents; i++) {
	if (type == bsdToXF86Array[i].apmBsd) {
	    return bsdToXF86Array[i].xf86;
	}
    }
    return XF86_APM_UNKNOWN;
}

/*
 * APM events can be requested direclty from /dev/apm 
 */
static int 
bsdPMGetEventFromOS(int kq, pmEvent *events, int num)
{
    struct kevent ev;
    int i, result;
    struct timespec ts = { 0, 0 };
    
    for (i = 0; i < num; i++) {
	result = kevent(kq, NULL, 0, &ev, 1, &ts);
	if (result == 0 || APM_EVENT_TYPE(ev.data) == APM_NOEVENT) {
	    /* no event */
	    break;
	} else if (result < 0) {
	    xf86Msg(X_WARNING, "bsdPMGetEventFromOS: kevent returns"
		    " errno = %d\n", errno);
	    break;
	}
	events[i] = bsdToXF86(APM_EVENT_TYPE(ev.data));
    }
    return i;
}

/*
 * If apmd(8) is running, he will get the events and handle them,
 * so, we've nothing to do here. 
 * Otherwise, opening /dev/apmctl will succeed and we have to send the 
 * confirmations to /dev/apmctl. 
 */
static pmWait
bsdPMConfirmEventToOs(int dummyfd, pmEvent event)
{
    if (ctlFd < 0) {
	if ((ctlFd = open(_PATH_APM_CTLDEV, O_RDWR)) < 0) {
	    return PM_NONE;
	}
    }
    /* apmctl open succeedeed */
    switch (event) {
      case XF86_APM_SYS_STANDBY:
      case XF86_APM_USER_STANDBY:
        if (ioctl( ctlFd, APM_IOC_STANDBY, NULL ) == 0)
            return PM_WAIT;  /* should we stop the Xserver in standby, too? */
        else
            return PM_NONE;

      case XF86_APM_SYS_SUSPEND:
      case XF86_APM_CRITICAL_SUSPEND:
      case XF86_APM_USER_SUSPEND:
        if (ioctl( ctlFd, APM_IOC_SUSPEND, NULL ) == 0)
            return PM_WAIT;
        else
            return PM_NONE;
	break;
      case XF86_APM_STANDBY_RESUME:
      case XF86_APM_NORMAL_RESUME:
      case XF86_APM_CRITICAL_RESUME:
      case XF86_APM_STANDBY_FAILED:
      case XF86_APM_SUSPEND_FAILED:
        return PM_CONTINUE;
	break;
      default:
	return PM_NONE;
    }
}

PMClose
xf86OSPMOpen(void)
{
    int kq;
    struct kevent ev;

    if (APMihPtr || !xf86Info.pmFlag) {
	return NULL;
    }
    if ((devFd = open(_PATH_APM_DEV, O_RDONLY)) == -1) {
	return NULL;
    }
    if ((kq = kqueue()) <= 0) {
	close(devFd);
	return NULL;
    }
    EV_SET(&ev, devFd, EVFILT_READ, EV_ADD | EV_ENABLE | EV_CLEAR,
	   0, 0, NULL);
    if (kevent(kq, &ev, 1, NULL, 0, NULL) < 0) {
	close(devFd);
	return NULL;
    }

    xf86PMGetEventFromOs = bsdPMGetEventFromOS;
    xf86PMConfirmEventToOs = bsdPMConfirmEventToOs;
    APMihPtr = xf86AddInputHandler(kq, xf86HandlePMEvents, NULL);
    return bsdCloseAPM;
}

static void
bsdCloseAPM(void)
{
    int kq;

    if (APMihPtr) {
	kq = xf86RemoveInputHandler(APMihPtr);
	close(devFd);
	devFd = -1;
	close(kq);
	if (ctlFd >= 0) {
	    close(ctlFd);
	    ctlFd = -1;
	}
	APMihPtr = NULL;
    }
}
