/* $Xorg: xdmcp.c,v 1.4 2001/01/31 13:37:19 pookie Exp $ */
/*
 * Copyright 1989 Network Computing Devices, Inc., Mountain View, California.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of N.C.D. not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  N.C.D. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 */
/* $XFree86: xc/programs/Xserver/os/xdmcp.c,v 3.33 2004/06/24 02:21:16 tsi Exp $ */

#ifdef WIN32
/* avoid conflicting definitions */
#define BOOL wBOOL
#define ATOM wATOM
#define FreeResource wFreeResource
#include <winsock.h>
#undef BOOL
#undef ATOM
#undef FreeResource
#undef CreateWindowA
#undef RT_FONT
#undef RT_CURSOR
#endif

#include "Xos.h"

#if !defined(WIN32)
#ifndef Lynx
#include <sys/param.h>
#include <sys/socket.h>
#else
#include <socket.h>
#endif
#include <netinet/in.h>
#include <netdb.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "X.h"
#include "Xmd.h"
#include "misc.h"
#include "Xpoll.h"
#include "osdep.h"
#include "input.h"
#include "dixstruct.h"
#include "opaque.h"

#if defined(DGUX)
#include <net/net_ioctl.h>
#include <sys/ioctl.h>
#endif

#ifdef STREAMSCONN
#include <tiuser.h>
#include <netconfig.h>
#include <netdir.h>
#endif

#ifdef XDMCP
#undef REQUEST

#ifdef XDMCP_NO_IPV6
#undef IPv6
#endif

#include <X11/Xdmcp.h>

#define X_INCLUDE_NETDB_H
#include <X11/Xos_r.h>

extern char *defaultDisplayClass;

static int		    xdmcpSocket, sessionSocket;
static xdmcp_states	    state;
#if defined(IPv6) && defined(AF_INET6)
static int		    xdmcpSocket6;
static struct sockaddr_storage req_sockaddr;
#else
static struct sockaddr_in   req_sockaddr;
#endif
static int		    req_socklen;
static CARD32		    SessionID;
static CARD32		    timeOutTime;
static int		    timeOutRtx;
static CARD32		    defaultKeepaliveDormancy = XDM_DEF_DORMANCY;
static CARD32		    keepaliveDormancy = XDM_DEF_DORMANCY;
static CARD16		    DisplayNumber;
static xdmcp_states	    XDM_INIT_STATE = XDM_OFF;
#ifdef HASXDMAUTH
static char		    *xdmAuthCookie;
#endif

static XdmcpBuffer	    buffer;

#if defined(IPv6) && defined(AF_INET6)

static struct addrinfo *mgrAddr;
static struct addrinfo *mgrAddrFirst;

#define SOCKADDR_TYPE		struct sockaddr_storage
#define SOCKADDR_FAMILY(s)	((struct sockaddr *)&(s))->sa_family

#ifdef BSD44SOCKETS
#define SOCKLEN_FIELD(s)	((struct sockaddr *)&(s))->sa_len
#define SOCKLEN_TYPE 		unsigned char
#else
#define SOCKLEN_TYPE 		unsigned int
#endif

#else

#define SOCKADDR_TYPE		struct sockaddr_in
#define SOCKADDR_FAMILY(s)	(s).sin_family

#ifdef BSD44SOCKETS
#define SOCKLEN_FIELD(s)	(s).sin_len
#define SOCKLEN_TYPE		unsigned char
#else
#define SOCKLEN_TYPE		size_t
#endif

#endif

static SOCKADDR_TYPE		ManagerAddress;
static SOCKADDR_TYPE		FromAddress;

#ifdef SOCKLEN_FIELD
#define ManagerAddressLen	SOCKLEN_FIELD(ManagerAddress)
#define FromAddressLen		SOCKLEN_FIELD(FromAddress)
#else
static SOCKLEN_TYPE ManagerAddressLen, FromAddressLen;
#endif

#if defined(IPv6) && defined(AF_INET6)
static struct multicastinfo {
    struct multicastinfo	*next;
    struct addrinfo		*ai;
    int				 hops;
} *mcastlist;
#endif

static void XdmcpAddHost(
    struct sockaddr    *from,
    int			fromlen,
    ARRAY8Ptr		AuthenticationName,
    ARRAY8Ptr		hostname,
    ARRAY8Ptr		status);

static void XdmcpSelectHost(
    struct sockaddr	*host_sockaddr,
    int			host_len,
    ARRAY8Ptr		AuthenticationName);

static void get_xdmcp_sock(void);

static void send_query_msg(void);

static void recv_willing_msg(
    struct sockaddr */*from*/,
    int /*fromlen*/,
    unsigned /*length*/);

static void send_request_msg(void);

static void recv_accept_msg(unsigned /*length*/);

static void recv_decline_msg(unsigned /*length*/);

static void send_manage_msg(void);

static void recv_refuse_msg(unsigned /*length*/);

static void recv_failed_msg(unsigned /*length*/);

static void send_keepalive_msg(void);

static void recv_alive_msg(unsigned /*length*/);

static void XdmcpFatal(
    char */*type*/,
    ARRAY8Ptr /*status*/);
 
static void XdmcpWarning(char */*str*/);

static void get_manager_by_name(
    int /*argc*/,
    char **/*argv*/,
    int /*i*/);

static void get_fromaddr_by_name(int /*argc*/, char **/*argv*/, int /*i*/);

#if defined(IPv6) && defined(AF_INET6)
static int get_mcast_options(int /*argc*/, char **/*argv*/, int /*i*/);
#endif

static void receive_packet(int /*socketfd*/);

static void send_packet(void);

extern void XdmcpDeadSession(char */*reason*/);

static void timeout(void);

static void restart(void);

static void XdmcpBlockHandler(
    pointer /*data*/,
    struct timeval **/*wt*/,
    pointer /*LastSelectMask*/);

static void XdmcpWakeupHandler(
    pointer /*data*/,
    int /*i*/,
    pointer /*LastSelectMask*/);

void XdmcpRegisterManufacturerDisplayID(
    char    * /*name*/,
    int	    /*length*/);


static unsigned short	xdm_udp_port = XDM_UDP_PORT;
static Bool	OneSession = FALSE;
static const char 	*xdm_from = NULL;

void
XdmcpUseMsg (void)
{
    ErrorF("-query host-name       contact named host for XDMCP\n");
    ErrorF("-broadcast             broadcast for XDMCP\n");
#if defined(IPv6) && defined(AF_INET6)
    ErrorF("-multicast [addr [hops]] IPv6 multicast for XDMCP\n");
#endif
    ErrorF("-indirect host-name    contact named host for indirect XDMCP\n");
    ErrorF("-port port-num         UDP port number to send messages to\n");
    ErrorF("-from local-address    specify the local address to connect from\n");
    ErrorF("-once                  Terminate server after one session\n");
    ErrorF("-class display-class   specify display class to send in manage\n");
#ifdef HASXDMAUTH
    ErrorF("-cookie xdm-auth-bits  specify the magic cookie for XDMCP\n");
#endif
    ErrorF("-displayID display-id  manufacturer display ID for request\n");
}

int 
XdmcpOptions(int argc, char **argv, int i)
{
    if (strcmp(argv[i], "-query") == 0) {
	get_manager_by_name(argc, argv, i++);
	XDM_INIT_STATE = XDM_QUERY;
	AccessUsingXdmcp ();
	return (i + 1);
    }
    if (strcmp(argv[i], "-broadcast") == 0) {
	XDM_INIT_STATE = XDM_BROADCAST;
	AccessUsingXdmcp ();
	return (i + 1);
    }
#if defined(IPv6) && defined(AF_INET6)
    if (strcmp(argv[i], "-multicast") == 0) {
	i = get_mcast_options(argc, argv, ++i);
	XDM_INIT_STATE = XDM_MULTICAST;
	AccessUsingXdmcp ();
	return (i + 1);
    }
#endif
    if (strcmp(argv[i], "-indirect") == 0) {
	get_manager_by_name(argc, argv, i++);
	XDM_INIT_STATE = XDM_INDIRECT;
	AccessUsingXdmcp ();
	return (i + 1);
    }
    if (strcmp(argv[i], "-port") == 0) {
        if (++i == argc)  {
	    ErrorF("Xserver: missing port number in command line\n");
	    exit(1);
	}
	xdm_udp_port = (unsigned short) atoi(argv[i]);
	return (i + 1);
    }
    if (strcmp(argv[i], "-from") == 0) {
	get_fromaddr_by_name(argc, argv, ++i);
	return (i + 1);
    }
    if (strcmp(argv[i], "-once") == 0) {
	OneSession = TRUE;
	return (i + 1);
    }
    if (strcmp(argv[i], "-class") == 0) {
        if (++i == argc)  {
	    ErrorF("Xserver: missing class name in command line\n");
	    exit(1);
	}
	defaultDisplayClass = argv[i];
	return (i + 1);
    }
#ifdef HASXDMAUTH
    if (strcmp(argv[i], "-cookie") == 0) {
        if (++i == argc)  {
	    ErrorF("Xserver: missing cookie data in command line\n");
	    exit(1);
	}
	xdmAuthCookie = argv[i];
	return (i + 1);
    }
#endif
    if (strcmp(argv[i], "-displayID") == 0) {
        if (++i == argc)  {
	    ErrorF("Xserver: missing displayID in command line\n");
	    exit(1);
	}
	XdmcpRegisterManufacturerDisplayID (argv[i], strlen (argv[i]));
	return (i + 1);
    }
    return (i);
}

/*
 * This section is a collection of routines for
 * registering server-specific data with the XDMCP
 * state machine.
 */


/*
 * Save all broadcast addresses away so BroadcastQuery
 * packets get sent everywhere
 */

#define MAX_BROADCAST	10

/* This stays sockaddr_in since IPv6 doesn't support broadcast */
static struct sockaddr_in   BroadcastAddresses[MAX_BROADCAST];
static int		    NumBroadcastAddresses;

void
XdmcpRegisterBroadcastAddress (struct sockaddr_in *addr)
{
    struct sockaddr_in	*bcast;
    if (NumBroadcastAddresses >= MAX_BROADCAST)
	return;
    bcast = &BroadcastAddresses[NumBroadcastAddresses++];
    bzero (bcast, sizeof (struct sockaddr_in));
#ifdef BSD44SOCKETS
    bcast->sin_len = addr->sin_len;
#endif
    bcast->sin_family = addr->sin_family;
    bcast->sin_port = htons (xdm_udp_port);
    bcast->sin_addr = addr->sin_addr;
}

/*
 * Each authentication type is registered here; Validator
 * will be called to check all access attempts using
 * the specified authentication type
 */

static ARRAYofARRAY8	AuthenticationNames, AuthenticationDatas;
typedef struct _AuthenticationFuncs {
    ValidatorFunc    Validator;
    GeneratorFunc    Generator;
    AddAuthorFunc    AddAuth;
} AuthenticationFuncsRec, *AuthenticationFuncsPtr;

static AuthenticationFuncsPtr	AuthenticationFuncsList;

void
XdmcpRegisterAuthentication (
    char    *name,
    int	    namelen,
    char    *data,
    int	    datalen,
    ValidatorFunc Validator,
    GeneratorFunc Generator,
    AddAuthorFunc AddAuth)
{
    int	    i;
    ARRAY8  AuthenticationName, AuthenticationData;
    static AuthenticationFuncsPtr	newFuncs;

    if (!XdmcpAllocARRAY8 (&AuthenticationName, namelen))
	return;
    if (!XdmcpAllocARRAY8 (&AuthenticationData, datalen))
    {
	XdmcpDisposeARRAY8 (&AuthenticationName);
	return;
    }
    for (i = 0; i < namelen; i++)
	AuthenticationName.data[i] = name[i];
    for (i = 0; i < datalen; i++)
	AuthenticationData.data[i] = data[i];
    if (!(XdmcpReallocARRAYofARRAY8 (&AuthenticationNames,
				     AuthenticationNames.length + 1) &&
	  XdmcpReallocARRAYofARRAY8 (&AuthenticationDatas,
				     AuthenticationDatas.length + 1) &&
	  (newFuncs = (AuthenticationFuncsPtr) xalloc (
			(AuthenticationNames.length + 1) * sizeof (AuthenticationFuncsRec)))))
    {
	XdmcpDisposeARRAY8 (&AuthenticationName);
	XdmcpDisposeARRAY8 (&AuthenticationData);
	return;
    }
    for (i = 0; i < AuthenticationNames.length - 1; i++)
	newFuncs[i] = AuthenticationFuncsList[i];
    newFuncs[AuthenticationNames.length-1].Validator = Validator;
    newFuncs[AuthenticationNames.length-1].Generator = Generator;
    newFuncs[AuthenticationNames.length-1].AddAuth = AddAuth;
    xfree (AuthenticationFuncsList);
    AuthenticationFuncsList = newFuncs;
    AuthenticationNames.data[AuthenticationNames.length-1] = AuthenticationName;
    AuthenticationDatas.data[AuthenticationDatas.length-1] = AuthenticationData;
}

/*
 * Select the authentication type to be used; this is
 * set by the manager of the host to be connected to.
 */

ARRAY8		noAuthenticationName = {(CARD16) 0, (CARD8Ptr) 0};
ARRAY8		noAuthenticationData = {(CARD16) 0, (CARD8Ptr) 0};
ARRAY8Ptr	AuthenticationName = &noAuthenticationName;
ARRAY8Ptr	AuthenticationData = &noAuthenticationData;
AuthenticationFuncsPtr	AuthenticationFuncs;

void
XdmcpSetAuthentication (ARRAY8Ptr name)
{
    int	i;

    for (i = 0; i < AuthenticationNames.length; i++)
	if (XdmcpARRAY8Equal (&AuthenticationNames.data[i], name))
	{
	    AuthenticationName = &AuthenticationNames.data[i];
	    AuthenticationData = &AuthenticationDatas.data[i];
	    AuthenticationFuncs = &AuthenticationFuncsList[i];
	    break;
	}
}

/*
 * Register the host address for the display
 */

static ARRAY16		ConnectionTypes;
static ARRAYofARRAY8	ConnectionAddresses;
static long		xdmcpGeneration;

void
XdmcpRegisterConnection (
    int	    type,
    char    *address,
    int	    addrlen)
{
    int	    i;
    CARD8   *newAddress;

    if (xdmcpGeneration != serverGeneration)
    {
	XdmcpDisposeARRAY16 (&ConnectionTypes);
	XdmcpDisposeARRAYofARRAY8 (&ConnectionAddresses);
	xdmcpGeneration = serverGeneration;
    }
    if (xdm_from != NULL) {	/* Only register the requested address */
	const void *regAddr = address;
	const void *fromAddr = NULL;
	int regAddrlen = addrlen;

	if (addrlen == sizeof(struct in_addr)) {
	    if (SOCKADDR_FAMILY(FromAddress) == AF_INET) {
		fromAddr = &((struct sockaddr_in *)&FromAddress)->sin_addr;
	    } 
#if defined(IPv6) && defined(AF_INET6)
	    else if ((SOCKADDR_FAMILY(FromAddress) == AF_INET6) &&
	      IN6_IS_ADDR_V4MAPPED(
		  &((struct sockaddr_in6 *)&FromAddress)->sin6_addr)) {
		fromAddr = &((struct sockaddr_in6 *)&FromAddress)->sin6_addr.s6_addr[12];
	    } 
#endif
	}
#if defined(IPv6) && defined(AF_INET6)
	else if (addrlen == sizeof(struct in6_addr)) {
	    if (SOCKADDR_FAMILY(FromAddress) == AF_INET6) {
		fromAddr = &((struct sockaddr_in6 *)&FromAddress)->sin6_addr;
	    } else if ((SOCKADDR_FAMILY(FromAddress) == AF_INET) &&
	      IN6_IS_ADDR_V4MAPPED((struct in6_addr *) address)) {
		fromAddr = &((struct sockaddr_in *)&FromAddress)->sin_addr;
		regAddr = &((struct sockaddr_in6 *)&address)->sin6_addr.s6_addr[12];
		regAddrlen = sizeof(struct in_addr);
	    }
	}
#endif
	if (fromAddr && memcmp(regAddr, fromAddr, regAddrlen) != 0) {
	    return;
	}
    }
    newAddress = (CARD8 *) xalloc (addrlen * sizeof (CARD8));
    if (!newAddress)
	return;
    if (!XdmcpReallocARRAY16 (&ConnectionTypes, ConnectionTypes.length + 1))
    {
	xfree (newAddress);
	return;
    }
    if (!XdmcpReallocARRAYofARRAY8 (&ConnectionAddresses,
				    ConnectionAddresses.length +  1))
    {
	xfree (newAddress);
	return;
    }
    ConnectionTypes.data[ConnectionTypes.length - 1] = (CARD16) type;
    for (i = 0; i < addrlen; i++)
	newAddress[i] = address[i];
    ConnectionAddresses.data[ConnectionAddresses.length-1].data = newAddress;
    ConnectionAddresses.data[ConnectionAddresses.length-1].length = addrlen;
}

/*
 * Register an Authorization Name.  XDMCP advertises this list
 * to the manager.
 */

static ARRAYofARRAY8	AuthorizationNames;

void
XdmcpRegisterAuthorizations (void)
{
    XdmcpDisposeARRAYofARRAY8 (&AuthorizationNames);
    RegisterAuthorizations ();
}

void
XdmcpRegisterAuthorization (char *name, int namelen)
{
    ARRAY8  authName;
    int	    i;

    authName.data = (CARD8 *) xalloc (namelen * sizeof (CARD8));
    if (!authName.data)
	return;
    if (!XdmcpReallocARRAYofARRAY8 (&AuthorizationNames, AuthorizationNames.length +1))
    {
	xfree (authName.data);
	return;
    }
    for (i = 0; i < namelen; i++)
	authName.data[i] = (CARD8) name[i];
    authName.length = namelen;
    AuthorizationNames.data[AuthorizationNames.length-1] = authName;
}

/*
 * Register the DisplayClass string
 */

ARRAY8	DisplayClass;

void
XdmcpRegisterDisplayClass (char *name, int length)
{
    int	    i;

    XdmcpDisposeARRAY8 (&DisplayClass);
    if (!XdmcpAllocARRAY8 (&DisplayClass, length))
	return;
    for (i = 0; i < length; i++)
	DisplayClass.data[i] = (CARD8) name[i];
}

/*
 * Register the Manufacturer display ID
 */

ARRAY8 ManufacturerDisplayID;

void
XdmcpRegisterManufacturerDisplayID (char *name, int length)
{
    int	    i;

    XdmcpDisposeARRAY8 (&ManufacturerDisplayID);
    if (!XdmcpAllocARRAY8 (&ManufacturerDisplayID, length))
	return;
    for (i = 0; i < length; i++)
	ManufacturerDisplayID.data[i] = (CARD8) name[i];
}

/* 
 * initialize XDMCP; create the socket, compute the display
 * number, set up the state machine
 */

void 
XdmcpInit(void)
{
    state = XDM_INIT_STATE;
#ifdef HASXDMAUTH
    if (xdmAuthCookie)
	XdmAuthenticationInit (xdmAuthCookie, strlen (xdmAuthCookie));
#endif
    if (state != XDM_OFF)
    {
	XdmcpRegisterAuthorizations();
	XdmcpRegisterDisplayClass (defaultDisplayClass, strlen (defaultDisplayClass));
	AccessUsingXdmcp();
	RegisterBlockAndWakeupHandlers (XdmcpBlockHandler, XdmcpWakeupHandler,
				        (pointer) 0);
    	timeOutRtx = 0;
    	DisplayNumber = (CARD16) atoi(display);
    	get_xdmcp_sock();
    	send_packet();
    }
}

void
XdmcpReset (void)
{
    state = XDM_INIT_STATE;
    if (state != XDM_OFF)
    {
	RegisterBlockAndWakeupHandlers (XdmcpBlockHandler, XdmcpWakeupHandler,
				        (pointer) 0);
    	timeOutRtx = 0;
    	send_packet();
    }
}

/*
 * Called whenever a new connection is created; notices the
 * first connection and saves it to terminate the session
 * when it is closed
 */

void
XdmcpOpenDisplay(int sock)
{
    if (state != XDM_AWAIT_MANAGE_RESPONSE)
	return;
    state = XDM_RUN_SESSION;
    sessionSocket = sock;
}

void 
XdmcpCloseDisplay(int sock)
{
    if ((state != XDM_RUN_SESSION && state != XDM_AWAIT_ALIVE_RESPONSE)
	|| sessionSocket != sock)
	    return;
    state = XDM_INIT_STATE;
    if (OneSession)
	dispatchException |= DE_TERMINATE;
    else
	dispatchException |= DE_RESET;
    isItTimeToYield = TRUE;
}

/*
 * called before going to sleep, this routine
 * may modify the timeout value about to be sent
 * to select; in this way XDMCP can do appropriate things
 * dynamically while starting up
 */

/*ARGSUSED*/
static void
XdmcpBlockHandler(
    pointer	    data,   /* unused */
    struct timeval  **wt,
    pointer	    pReadmask)
{
    fd_set *LastSelectMask = (fd_set*)pReadmask;
    CARD32 millisToGo;

    if (state == XDM_OFF)
	return;
    FD_SET(xdmcpSocket, LastSelectMask);
#if defined(IPv6) && defined(AF_INET6)
    if (xdmcpSocket6 >= 0)
	FD_SET(xdmcpSocket6, LastSelectMask);
#endif
    if (timeOutTime == 0)
	return;
    millisToGo = timeOutTime - GetTimeInMillis();
    if ((int) millisToGo < 0)
	millisToGo = 0;
    AdjustWaitForDelay (wt, millisToGo);
}

/*
 * called after select returns; this routine will
 * recognise when XDMCP packets await and
 * process them appropriately
 */

/*ARGSUSED*/
static void
XdmcpWakeupHandler(
    pointer data,   /* unused */
    int	    i,
    pointer pReadmask)
{
    fd_set* LastSelectMask = (fd_set*)pReadmask;
    fd_set   devicesReadable;

    if (state == XDM_OFF)
	return;
    if (i > 0)
    {
	if (FD_ISSET(xdmcpSocket, LastSelectMask))
	{
	    receive_packet(xdmcpSocket);
	    FD_CLR(xdmcpSocket, LastSelectMask);
	} 
#if defined(IPv6) && defined(AF_INET6)
	if (xdmcpSocket6 >= 0 && FD_ISSET(xdmcpSocket6, LastSelectMask))
	{
	    receive_packet(xdmcpSocket6);
	    FD_CLR(xdmcpSocket6, LastSelectMask);
	} 
#endif
	XFD_ANDSET(&devicesReadable, LastSelectMask, &EnabledDevices);
	if (XFD_ANYSET(&devicesReadable))
	{
	    if (state == XDM_AWAIT_USER_INPUT)
		restart();
	    else if (state == XDM_RUN_SESSION)
		keepaliveDormancy = defaultKeepaliveDormancy;
	}
	if (XFD_ANYSET(&AllClients) && state == XDM_RUN_SESSION)
	    timeOutTime = GetTimeInMillis() +  keepaliveDormancy * 1000;
    }
    else if (timeOutTime && (int) (GetTimeInMillis() - timeOutTime) >= 0)
    {
    	if (state == XDM_RUN_SESSION)
    	{
	    state = XDM_KEEPALIVE;
	    send_packet();
    	}
    	else
	    timeout();
    }
}

/*
 * This routine should be called from the routine that drives the
 * user's host menu when the user selects a host
 */

static void
XdmcpSelectHost(
    struct sockaddr	*host_sockaddr,
    int			host_len,
    ARRAY8Ptr		AuthenticationName)
{
    state = XDM_START_CONNECTION;
    memmove(&req_sockaddr, host_sockaddr, host_len);
    req_socklen = host_len;
    XdmcpSetAuthentication (AuthenticationName);
    send_packet();
}

/*
 * !!! this routine should be replaced by a routine that adds
 * the host to the user's host menu. the current version just
 * selects the first host to respond with willing message.
 */

/*ARGSUSED*/
static void
XdmcpAddHost(
    struct sockaddr    *from,
    int			fromlen,
    ARRAY8Ptr		AuthenticationName,
    ARRAY8Ptr		hostname,
    ARRAY8Ptr		status)
{
    XdmcpSelectHost(from, fromlen, AuthenticationName);
}

/*
 * A message is queued on the socket; read it and
 * do the appropriate thing
 */

ARRAY8	UnwillingMessage = { (CARD8) 14, (CARD8 *) "Host unwilling" };

static void
receive_packet(int socketfd)
{
#if defined(IPv6) && defined(AF_INET6)
    struct sockaddr_storage from;
#else
    struct sockaddr_in from;
#endif
    int fromlen = sizeof(from);
    XdmcpHeader	header;

    /* read message off socket */
    if (!XdmcpFill (socketfd, &buffer, (XdmcpNetaddr) &from, &fromlen))
	return;

    /* reset retransmission backoff */
    timeOutRtx = 0;

    if (!XdmcpReadHeader (&buffer, &header))
	return;

    if (header.version != XDM_PROTOCOL_VERSION)
	return;

    switch (header.opcode) {
    case WILLING:
	recv_willing_msg((struct sockaddr *) &from, fromlen, header.length);
	break;
    case UNWILLING:
	XdmcpFatal("Manager unwilling", &UnwillingMessage);
	break;
    case ACCEPT:
	recv_accept_msg(header.length);
	break;
    case DECLINE:
	recv_decline_msg(header.length);
	break;
    case REFUSE:
	recv_refuse_msg(header.length);
	break;
    case FAILED:
	recv_failed_msg(header.length);
	break;
    case ALIVE:
	recv_alive_msg(header.length);
	break;
    }
}

/*
 * send the appropriate message given the current state
 */

static void
send_packet(void)
{
    int rtx;
    switch (state) {
    case XDM_QUERY:
    case XDM_BROADCAST:
    case XDM_INDIRECT:
#if defined(IPv6)  && defined(AF_INET6)
    case XDM_MULTICAST:
#endif
	send_query_msg();
	break;
    case XDM_START_CONNECTION:
	send_request_msg();
	break;
    case XDM_MANAGE:
	send_manage_msg();
	break;
    case XDM_KEEPALIVE:
	send_keepalive_msg();
	break;
    default:
	break;
    }
    rtx = (XDM_MIN_RTX << timeOutRtx);
    if (rtx > XDM_MAX_RTX)
	rtx = XDM_MAX_RTX;
    timeOutTime = GetTimeInMillis() + rtx * 1000;
}

/*
 * The session is declared dead for some reason; too many
 * timeouts, or Keepalive failure.
 */

void
XdmcpDeadSession (char *reason)
{
    ErrorF ("XDM: %s, declaring session dead\n", reason);
    state = XDM_INIT_STATE;
    isItTimeToYield = TRUE;
    dispatchException |= DE_RESET;
    timeOutTime = 0;
    timeOutRtx = 0;
    send_packet();
}

/*
 * Timeout waiting for an XDMCP response.
 */

static void
timeout(void)
{
    timeOutRtx++;
    if (state == XDM_AWAIT_ALIVE_RESPONSE && timeOutRtx >= XDM_KA_RTX_LIMIT )
    {
	XdmcpDeadSession ("too many keepalive retransmissions");
	return;
    }
    else if (timeOutRtx >= XDM_RTX_LIMIT)
    {
	/* Quit if "-once" specified, otherwise reset and try again. */
        if (OneSession) {
	    dispatchException |= DE_TERMINATE;
	    ErrorF("XDM: too many retransmissions\n");
	} else { 
	    XdmcpDeadSession("too many retransmissions");
	}
	return;
    }

#if defined(IPv6) && defined(AF_INET6)
    if (state == XDM_COLLECT_QUERY || state == XDM_COLLECT_INDIRECT_QUERY) {
	/* Try next address */
	for (mgrAddr = mgrAddr->ai_next; ; mgrAddr = mgrAddr->ai_next) {
	    if (mgrAddr == NULL) {
		mgrAddr = mgrAddrFirst;
	    }
	    if (mgrAddr->ai_family == AF_INET 
	      || mgrAddr->ai_family == AF_INET6)
		break;
	}
#ifndef SIN6_LEN
	ManagerAddressLen = mgrAddr->ai_addrlen;
#endif
	memcpy(&ManagerAddress, mgrAddr->ai_addr, mgrAddr->ai_addrlen);
    }
#endif

    switch (state) {
    case XDM_COLLECT_QUERY:
	state = XDM_QUERY;
	break;
    case XDM_COLLECT_BROADCAST_QUERY:
	state = XDM_BROADCAST;
	break;
#if defined(IPv6) && defined(AF_INET6)
    case XDM_COLLECT_MULTICAST_QUERY:
	state = XDM_MULTICAST;
	break;
#endif
    case XDM_COLLECT_INDIRECT_QUERY:
	state = XDM_INDIRECT;
	break;
    case XDM_AWAIT_REQUEST_RESPONSE:
	state = XDM_START_CONNECTION;
	break;
    case XDM_AWAIT_MANAGE_RESPONSE:
	state = XDM_MANAGE;
	break;
    case XDM_AWAIT_ALIVE_RESPONSE:
	state = XDM_KEEPALIVE;
	break;
    default:
	break;
    }
    send_packet();
}

static void
restart(void)
{
    state = XDM_INIT_STATE;
    timeOutRtx = 0;
    send_packet();
}

int
XdmcpCheckAuthentication (
    ARRAY8Ptr	Name,
    ARRAY8Ptr	Data,
    xdmOpCode	packet_type)
{
    return (XdmcpARRAY8Equal (Name, AuthenticationName) &&
	    (AuthenticationName->length == 0 ||
	     (*AuthenticationFuncs->Validator) (AuthenticationData, Data, packet_type)));
}

int
XdmcpAddAuthorization (
    ARRAY8Ptr	name,
    ARRAY8Ptr	data)
{
    AddAuthorFunc AddAuth;

    if (AuthenticationFuncs && AuthenticationFuncs->AddAuth)
	AddAuth = AuthenticationFuncs->AddAuth;
    else
	AddAuth = AddAuthorization;
    return (*AddAuth) ((unsigned short)name->length,
		       (char *)name->data,
		       (unsigned short)data->length,
		       (char *)data->data);
}

/*
 * from here to the end of this file are routines private
 * to the state machine.
 */

static void
get_xdmcp_sock(void)
{
#ifdef STREAMSCONN
    struct netconfig *nconf;

    if ((xdmcpSocket = t_open("/dev/udp", O_RDWR, 0)) < 0) {
	XdmcpWarning("t_open() of /dev/udp failed");
	return;
    }

    if( t_bind(xdmcpSocket,NULL,NULL) < 0 ) {
	XdmcpWarning("UDP socket creation failed");
	t_error("t_bind(xdmcpSocket) failed" );
	t_close(xdmcpSocket);
	return;
    }

    /*
     * This part of the code looks contrived. It will actually fit in nicely
     * when the CLTS part of Xtrans is implemented.
     */
 
    if( (nconf=getnetconfigent("udp")) == NULL ) {
	XdmcpWarning("UDP socket creation failed: getnetconfigent()");
	t_unbind(xdmcpSocket);
	t_close(xdmcpSocket);
	return;
    }
 
    if( netdir_options(nconf, ND_SET_BROADCAST, xdmcpSocket, NULL) ) {
	XdmcpWarning("UDP set broadcast option failed: netdir_options()");
	freenetconfigent(nconf);
	t_unbind(xdmcpSocket);
	t_close(xdmcpSocket);
	return;
    }
 
    freenetconfigent(nconf);
#else
    int soopts = 1;

#if defined(IPv6) && defined(AF_INET6)
    if ((xdmcpSocket6 = socket(AF_INET6, SOCK_DGRAM, 0)) < 0)
	XdmcpWarning("INET6 UDP socket creation failed");
#endif
    if ((xdmcpSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	XdmcpWarning("UDP socket creation failed");
#ifdef SO_BROADCAST
    else if (setsockopt(xdmcpSocket, SOL_SOCKET, SO_BROADCAST, (char *)&soopts,
	sizeof(soopts)) < 0)
	    XdmcpWarning("UDP set broadcast socket-option failed");
#endif /* SO_BROADCAST */
    if (xdmcpSocket >= 0 && xdm_from != NULL) {
	if (bind(xdmcpSocket, (struct sockaddr *)&FromAddress, 
		 FromAddressLen) < 0) {
	    ErrorF("Xserver: failed to bind to -from address: %s\n", xdm_from);
	    exit(1);
	}
    }
#endif /* STREAMSCONN */
}

static void
send_query_msg(void)
{
    XdmcpHeader	header;
    Bool	broadcast = FALSE;
#if defined(IPv6) && defined(AF_INET6)
    Bool	multicast = FALSE;
#endif
    int		i;
    int 	socketfd = xdmcpSocket;

    header.version = XDM_PROTOCOL_VERSION;
    switch(state){
    case XDM_QUERY:
	header.opcode = (CARD16) QUERY; 
	state = XDM_COLLECT_QUERY;
	break;
    case XDM_BROADCAST:
	header.opcode = (CARD16) BROADCAST_QUERY;
	state = XDM_COLLECT_BROADCAST_QUERY;
	broadcast = TRUE;
	break;
#if defined(IPv6) && defined(AF_INET6)
    case XDM_MULTICAST:
	header.opcode = (CARD16) BROADCAST_QUERY;
	state = XDM_COLLECT_MULTICAST_QUERY;
	multicast = TRUE;
	break;
#endif
    case XDM_INDIRECT:
	header.opcode = (CARD16) INDIRECT_QUERY;
	state = XDM_COLLECT_INDIRECT_QUERY;
	break;
    default:
	break;
    }
    header.length = 1;
    for (i = 0; i < AuthenticationNames.length; i++)
	header.length += 2 + AuthenticationNames.data[i].length;

    XdmcpWriteHeader (&buffer, &header);
    XdmcpWriteARRAYofARRAY8 (&buffer, &AuthenticationNames);
    if (broadcast)
    {
	int i;

	for (i = 0; i < NumBroadcastAddresses; i++)
	    XdmcpFlush (xdmcpSocket, &buffer, (XdmcpNetaddr) &BroadcastAddresses[i],
			sizeof (struct sockaddr_in));
    }
#if defined(IPv6) && defined(AF_INET6)
    else if (multicast)
    {
	struct multicastinfo *mcl;
	struct addrinfo *ai;

	for (mcl = mcastlist; mcl != NULL; mcl = mcl->next) {
	    for (ai = mcl->ai ; ai != NULL; ai = ai->ai_next) {
		if (ai->ai_family == AF_INET) {
		    unsigned char hopflag = (unsigned char) mcl->hops;
		    socketfd = xdmcpSocket;
		    setsockopt(socketfd, IPPROTO_IP, IP_MULTICAST_TTL,
		      &hopflag, sizeof(hopflag));
		} else if (ai->ai_family == AF_INET6) {
		    int hopflag6 = mcl->hops;
		    socketfd = xdmcpSocket6;
		    setsockopt(socketfd, IPPROTO_IPV6, IPV6_MULTICAST_HOPS,
		      &hopflag6, sizeof(hopflag6));
		} else {
		    continue;
		}
		XdmcpFlush (socketfd, &buffer, 
		  	    (XdmcpNetaddr) ai->ai_addr, ai->ai_addrlen);
		break;
	    }
	}
    }
#endif
    else
    {
#if defined(IPv6) && defined(AF_INET6)
	if (SOCKADDR_FAMILY(ManagerAddress) == AF_INET6)
	    socketfd = xdmcpSocket6;
#endif	
	XdmcpFlush (socketfd, &buffer, (XdmcpNetaddr) &ManagerAddress,
		    ManagerAddressLen);
    }
}

static void
recv_willing_msg(
    struct sockaddr	*from,
    int			fromlen,
    unsigned		length)
{
    ARRAY8	authenticationName;
    ARRAY8	hostname;
    ARRAY8	status;

    authenticationName.data = 0;
    hostname.data = 0;
    status.data = 0;
    if (XdmcpReadARRAY8 (&buffer, &authenticationName) &&
	XdmcpReadARRAY8 (&buffer, &hostname) &&
	XdmcpReadARRAY8 (&buffer, &status))
    {
    	if (length == 6 + authenticationName.length +
		      hostname.length + status.length)
    	{
	    switch (state)
	    {
	    case XDM_COLLECT_QUERY:
	    	XdmcpSelectHost(from, fromlen, &authenticationName);
	    	break;
	    case XDM_COLLECT_BROADCAST_QUERY:
#if defined(IPv6) && defined(AF_INET6)
	    case XDM_COLLECT_MULTICAST_QUERY:
#endif
	    case XDM_COLLECT_INDIRECT_QUERY:
	    	XdmcpAddHost(from, fromlen, &authenticationName, &hostname, &status);
	    	break;
	    default:
		break;
    	    }
    	}
    }
    XdmcpDisposeARRAY8 (&authenticationName);
    XdmcpDisposeARRAY8 (&hostname);
    XdmcpDisposeARRAY8 (&status);
}

static void
send_request_msg(void)
{
    XdmcpHeader	    header;
    int		    length;
    int		    i;
    CARD16	    XdmcpConnectionType;
    ARRAY8	    authenticationData;
    int		    socketfd = xdmcpSocket;

    switch (SOCKADDR_FAMILY(ManagerAddress))
    {
    case AF_INET:	XdmcpConnectionType=FamilyInternet; break;
#if defined(IPv6) && defined(AF_INET6)
    case AF_INET6:	XdmcpConnectionType=FamilyInternet6; break;
#endif
    default:		XdmcpConnectionType=0xffff; break;
    }

    header.version = XDM_PROTOCOL_VERSION;
    header.opcode = (CARD16) REQUEST;

    length = 2;					    /* display number */
    length += 1 + 2 * ConnectionTypes.length;	    /* connection types */
    length += 1;				    /* connection addresses */
    for (i = 0; i < ConnectionAddresses.length; i++)
	length += 2 + ConnectionAddresses.data[i].length;
    authenticationData.length = 0;
    authenticationData.data = 0;
    if (AuthenticationFuncs)
    {
	(*AuthenticationFuncs->Generator) (AuthenticationData,
					   &authenticationData,
 					   REQUEST);
    }
    length += 2 + AuthenticationName->length;	    /* authentication name */
    length += 2 + authenticationData.length;	    /* authentication data */
    length += 1;				    /* authorization names */
    for (i = 0; i < AuthorizationNames.length; i++)
	length += 2 + AuthorizationNames.data[i].length;
    length += 2 + ManufacturerDisplayID.length;	    /* display ID */
    header.length = length;

    if (!XdmcpWriteHeader (&buffer, &header))
    {
	XdmcpDisposeARRAY8 (&authenticationData);
	return;
    }
    XdmcpWriteCARD16 (&buffer, DisplayNumber);
    XdmcpWriteCARD8 (&buffer, ConnectionTypes.length);

    /* The connection array is send reordered, so that connections of	*/
    /* the same address type as the XDMCP manager connection are send	*/
    /* first. This works around a bug in xdm. mario@klebsch.de 		*/
    for (i = 0; i < (int)ConnectionTypes.length; i++)
	if (ConnectionTypes.data[i]==XdmcpConnectionType)
	    XdmcpWriteCARD16 (&buffer, ConnectionTypes.data[i]);
    for (i = 0; i < (int)ConnectionTypes.length; i++)
	if (ConnectionTypes.data[i]!=XdmcpConnectionType)
	    XdmcpWriteCARD16 (&buffer, ConnectionTypes.data[i]);

    XdmcpWriteCARD8 (&buffer, ConnectionAddresses.length);
    for (i = 0; i < (int)ConnectionAddresses.length; i++)
	if ( (i<ConnectionTypes.length) && 
	     (ConnectionTypes.data[i]==XdmcpConnectionType) )
	    XdmcpWriteARRAY8 (&buffer, &ConnectionAddresses.data[i]);
    for (i = 0; i < (int)ConnectionAddresses.length; i++)
	if ( (i>=ConnectionTypes.length) ||
	     (ConnectionTypes.data[i]!=XdmcpConnectionType) )
	    XdmcpWriteARRAY8 (&buffer, &ConnectionAddresses.data[i]);

    XdmcpWriteARRAY8 (&buffer, AuthenticationName);
    XdmcpWriteARRAY8 (&buffer, &authenticationData);
    XdmcpDisposeARRAY8 (&authenticationData);
    XdmcpWriteARRAYofARRAY8 (&buffer, &AuthorizationNames);
    XdmcpWriteARRAY8 (&buffer, &ManufacturerDisplayID);
#if defined(IPv6) && defined(AF_INET6)
    if (SOCKADDR_FAMILY(req_sockaddr) == AF_INET6)
	socketfd = xdmcpSocket6;
#endif
    if (XdmcpFlush (socketfd, &buffer, 
			(XdmcpNetaddr) &req_sockaddr, req_socklen))
	state = XDM_AWAIT_REQUEST_RESPONSE;
}

static void
recv_accept_msg(unsigned length)
{
    CARD32  AcceptSessionID;
    ARRAY8  AcceptAuthenticationName, AcceptAuthenticationData;
    ARRAY8  AcceptAuthorizationName, AcceptAuthorizationData;

    if (state != XDM_AWAIT_REQUEST_RESPONSE)
	return;
    AcceptAuthenticationName.data = 0;
    AcceptAuthenticationData.data = 0;
    AcceptAuthorizationName.data = 0;
    AcceptAuthorizationData.data = 0;
    if (XdmcpReadCARD32 (&buffer, &AcceptSessionID) &&
	XdmcpReadARRAY8 (&buffer, &AcceptAuthenticationName) &&
	XdmcpReadARRAY8 (&buffer, &AcceptAuthenticationData) &&
	XdmcpReadARRAY8 (&buffer, &AcceptAuthorizationName) &&
	XdmcpReadARRAY8 (&buffer, &AcceptAuthorizationData))
    {
    	if (length == 12 + AcceptAuthenticationName.length +
		      	   AcceptAuthenticationData.length +
		      	   AcceptAuthorizationName.length +
 		      	   AcceptAuthorizationData.length)
    	{
	    if (!XdmcpCheckAuthentication (&AcceptAuthenticationName,
				      &AcceptAuthenticationData, ACCEPT))
	    {
		XdmcpFatal ("Authentication Failure", &AcceptAuthenticationName);
	    }
	    /* permit access control manipulations from this host */
	    AugmentSelf (&req_sockaddr, req_socklen);
	    /* if the authorization specified in the packet fails
	     * to be acceptable, enable the local addresses
	     */
	    if (!XdmcpAddAuthorization (&AcceptAuthorizationName,
					&AcceptAuthorizationData))
	    {
		AddLocalHosts ();
	    }
	    SessionID = AcceptSessionID;
    	    state = XDM_MANAGE;
    	    send_packet();
    	}
    }
    XdmcpDisposeARRAY8 (&AcceptAuthenticationName);
    XdmcpDisposeARRAY8 (&AcceptAuthenticationData);
    XdmcpDisposeARRAY8 (&AcceptAuthorizationName);
    XdmcpDisposeARRAY8 (&AcceptAuthorizationData);
}

static void
recv_decline_msg(unsigned length)
{
    ARRAY8  status, DeclineAuthenticationName, DeclineAuthenticationData;

    status.data = 0;
    DeclineAuthenticationName.data = 0;
    DeclineAuthenticationData.data = 0;
    if (XdmcpReadARRAY8 (&buffer, &status) &&
	XdmcpReadARRAY8 (&buffer, &DeclineAuthenticationName) &&
	XdmcpReadARRAY8 (&buffer, &DeclineAuthenticationData))
    {
    	if (length == 6 + status.length +
		      	  DeclineAuthenticationName.length +
 		      	  DeclineAuthenticationData.length &&
	    XdmcpCheckAuthentication (&DeclineAuthenticationName,
				      &DeclineAuthenticationData, DECLINE))
    	{
	    XdmcpFatal ("Session declined", &status);
    	}
    }
    XdmcpDisposeARRAY8 (&status);
    XdmcpDisposeARRAY8 (&DeclineAuthenticationName);
    XdmcpDisposeARRAY8 (&DeclineAuthenticationData);
}

static void
send_manage_msg(void)
{
    XdmcpHeader	header;
    int socketfd = xdmcpSocket;

    header.version = XDM_PROTOCOL_VERSION;
    header.opcode = (CARD16) MANAGE;
    header.length = 8 + DisplayClass.length;

    if (!XdmcpWriteHeader (&buffer, &header))
	return;
    XdmcpWriteCARD32 (&buffer, SessionID);
    XdmcpWriteCARD16 (&buffer, DisplayNumber);
    XdmcpWriteARRAY8 (&buffer, &DisplayClass);
    state = XDM_AWAIT_MANAGE_RESPONSE;
#if defined(IPv6) && defined(AF_INET6)
    if (SOCKADDR_FAMILY(req_sockaddr) == AF_INET6)
	socketfd = xdmcpSocket6;
#endif
    XdmcpFlush (socketfd, &buffer, (XdmcpNetaddr) &req_sockaddr, req_socklen);
}

static void
recv_refuse_msg(unsigned length)
{
    CARD32  RefusedSessionID;

    if (state != XDM_AWAIT_MANAGE_RESPONSE)
	return;
    if (length != 4)
	return;
    if (XdmcpReadCARD32 (&buffer, &RefusedSessionID))
    {
	if (RefusedSessionID == SessionID)
	{
    	    state = XDM_START_CONNECTION;
    	    send_packet();
	}
    }
}

static void
recv_failed_msg(unsigned length)
{
    CARD32  FailedSessionID;
    ARRAY8  status;

    if (state != XDM_AWAIT_MANAGE_RESPONSE)
	return;
    status.data = 0;
    if (XdmcpReadCARD32 (&buffer, &FailedSessionID) &&
	XdmcpReadARRAY8 (&buffer, &status))
    {
    	if (length == 6 + status.length &&
	    SessionID == FailedSessionID)
	{
	    XdmcpFatal ("Session failed", &status);
	}
    }
    XdmcpDisposeARRAY8 (&status);
}

static void
send_keepalive_msg(void)
{
    XdmcpHeader	header;
    int socketfd = xdmcpSocket;

    header.version = XDM_PROTOCOL_VERSION;
    header.opcode = (CARD16) KEEPALIVE;
    header.length = 6;

    XdmcpWriteHeader (&buffer, &header);
    XdmcpWriteCARD16 (&buffer, DisplayNumber);
    XdmcpWriteCARD32 (&buffer, SessionID);

    state = XDM_AWAIT_ALIVE_RESPONSE;
#if defined(IPv6) && defined(AF_INET6)
    if (SOCKADDR_FAMILY(req_sockaddr) == AF_INET6)
	socketfd = xdmcpSocket6;
#endif
    XdmcpFlush (socketfd, &buffer, (XdmcpNetaddr) &req_sockaddr, req_socklen);
}

static void
recv_alive_msg (unsigned length)
{
    CARD8   SessionRunning;
    CARD32  AliveSessionID;

    if (state != XDM_AWAIT_ALIVE_RESPONSE)
	return;
    if (length != 5)
	return;
    if (XdmcpReadCARD8 (&buffer, &SessionRunning) &&
	XdmcpReadCARD32 (&buffer, &AliveSessionID))
    {
    	if (SessionRunning && AliveSessionID == SessionID)
    	{
	    /* backoff dormancy period */
	    state = XDM_RUN_SESSION;
	    if ((GetTimeInMillis() - lastDeviceEventTime.milliseconds) >
		keepaliveDormancy * 1000)
	    {
		keepaliveDormancy <<= 1;
		if (keepaliveDormancy > XDM_MAX_DORMANCY)
		    keepaliveDormancy = XDM_MAX_DORMANCY;
	    }
	    timeOutTime = GetTimeInMillis() + keepaliveDormancy * 1000;
    	}
	else
    	{
	    XdmcpDeadSession ("Alive respose indicates session dead");
    	}
    }
}

static  void
XdmcpFatal (
    char	*type,
    ARRAY8Ptr	status)
{
    FatalError ("XDMCP fatal error: %s %*.*s\n", type,
	   status->length, status->length, status->data);
}

static  void
XdmcpWarning(char *str)
{
    ErrorF("XDMCP warning: %s\n", str);
}

static void
get_addr_by_name(
    char *	argtype,
    char *	namestr,
    int		port,
    int		socktype,
    SOCKADDR_TYPE *addr,
    SOCKLEN_TYPE *addrlen
#if defined(IPv6) && defined(AF_INET6)
      ,
    struct addrinfo **aip,
    struct addrinfo **aifirstp
#endif
    )
{
#if defined(IPv6) && defined(AF_INET6)
    struct addrinfo *ai;
    struct addrinfo hints;
    char portstr[6];
    char *pport = portstr;
    int gaierr;

    bzero(&hints, sizeof(hints));
    hints.ai_socktype = socktype;

    if (port == 0) {
	pport = NULL;
    } else if (port > 0 && port < 65535) {
	sprintf(portstr, "%d", port);
    } else {
	ErrorF("Xserver: port out of range: %d\n", port);
	exit(1);
    }

    if (*aifirstp != NULL) {
	freeaddrinfo(*aifirstp);	
	*aifirstp = NULL;
    }

    if ((gaierr = getaddrinfo(namestr, pport, &hints, aifirstp)) == 0) {
	for (ai = *aifirstp; ai != NULL; ai = ai->ai_next) {
	    if (ai->ai_family == AF_INET || ai->ai_family == AF_INET6)
		break;
	}
	if ((ai == NULL) || (ai->ai_addrlen > sizeof(SOCKADDR_TYPE))) {
	    ErrorF ("Xserver: %s host %s not on supported network type\n", 
	      argtype, namestr);
	    exit (1);
	} else {
	    *aip = ai;
	    *addrlen = ai->ai_addrlen;
	    memcpy(addr, ai->ai_addr, ai->ai_addrlen);
	}
    } else {
	ErrorF("Xserver: %s: %s %s\n", gai_strerror(gaierr), argtype, namestr);
	exit(1);
    }    
#else
    struct hostent *hep;
#ifdef XTHREADS_NEEDS_BYNAMEPARAMS
    _Xgethostbynameparams hparams;
#endif

    if (!(hep = _XGethostbyname(namestr, hparams)))
    {
	ErrorF("Xserver: %s unknown host: %s\n", argtype, namestr);
	exit(1);
    }
    if (hep->h_length == sizeof (struct in_addr))
    {
	memmove(&addr->sin_addr, hep->h_addr, hep->h_length);
	*addrlen = sizeof(struct sockaddr_in);
	addr->sin_family = AF_INET;
	addr->sin_port = htons (xdm_udp_port);
    }
    else
    {
	ErrorF ("Xserver: %s host on strange network %s\n", argtype, namestr);
	exit (1);
    }
#endif
}

static void
get_manager_by_name(
    int	    argc,
    char    **argv,
    int	    i)
{

    if ((i + 1) == argc)
    {
	ErrorF("Xserver: missing %s host name in command line\n", argv[i]);
	exit(1);
    }

    get_addr_by_name(argv[i], argv[i+1], xdm_udp_port, SOCK_DGRAM, 
      &ManagerAddress, &ManagerAddressLen
#if defined(IPv6) && defined(AF_INET6)
      , &mgrAddr, &mgrAddrFirst
#endif
	);
}


static void
get_fromaddr_by_name(
    int	    argc,
    char    **argv,
    int	    i)
{
#if defined(IPv6) && defined(AF_INET6)
    struct addrinfo *ai = NULL;
    struct addrinfo *aifirst = NULL;
#endif
    if (i == argc)
    {
	ErrorF("Xserver: missing -from host name in command line\n");
	exit(1);
    }
    get_addr_by_name("-from", argv[i], 0, 0, &FromAddress, &FromAddressLen
#if defined(IPv6) && defined(AF_INET6)
      , &ai, &aifirst
#endif
	);
    xdm_from = argv[i];
}


#if defined(IPv6) && defined(AF_INET6)
static int
get_mcast_options(argc, argv, i)
    int	    argc, i;
    char    **argv;
{
    char *address = XDM_DEFAULT_MCAST_ADDR6;
    int hopcount = 1;
    struct addrinfo hints;
    char portstr[6];
    int gaierr;
    struct addrinfo *ai, *firstai;

    if ((i < argc) && (argv[i][0] != '-') && (argv[i][0] != '+')) {
	address = argv[i++];
	if ((i < argc) && (argv[i][0] != '-') && (argv[i][0] != '+')) {
	    hopcount = strtol(argv[i++], NULL, 10);
	    if ((hopcount < 1) || (hopcount > 255)) {
		ErrorF("Xserver: multicast hop count out of range: %d\n",
		  hopcount);
		exit(1);
	    }
	}
    }

    if (xdm_udp_port > 0 && xdm_udp_port < 65535) {
	sprintf(portstr, "%d", xdm_udp_port);
    } else {
	ErrorF("Xserver: port out of range: %d\n", xdm_udp_port);
	exit(1);
    }
    bzero(&hints, sizeof(hints));
    hints.ai_socktype = SOCK_DGRAM;

    if ((gaierr = getaddrinfo(address, portstr, &hints, &firstai)) == 0) {
	for (ai = firstai; ai != NULL; ai = ai->ai_next) {
	    if (((ai->ai_family == AF_INET) && 
	      	IN_MULTICAST(((struct sockaddr_in *) ai->ai_addr)
							  ->sin_addr.s_addr))
		|| ((ai->ai_family == AF_INET6) && 
		  IN6_IS_ADDR_MULTICAST(&((struct sockaddr_in6 *) ai->ai_addr)
							    ->sin6_addr)))
		break;
	}
	if (ai == NULL) {
	    ErrorF ("Xserver: address not supported multicast type %s\n", 
	      address);
	    exit (1);
	} else {
	    struct multicastinfo	*mcastinfo, *mcl;
	    
	    mcastinfo = malloc(sizeof(struct multicastinfo));
	    mcastinfo->next = NULL;
	    mcastinfo->ai = firstai;
	    mcastinfo->hops = hopcount;

	    if (mcastlist == NULL) {
		mcastlist = mcastinfo;
	    } else {
		for (mcl = mcastlist; mcl->next != NULL; mcl = mcl->next) {
		    /* Do nothing  - just find end of list */
		}
		mcl->next = mcastinfo;
	    }
	}
    } else {
	ErrorF("Xserver: %s: %s\n", gai_strerror(gaierr), address);
	exit(1);
    }    
    return i;
}
#endif

#else
static int xdmcp_non_empty; /* avoid complaint by ranlib */
#endif /* XDMCP */
