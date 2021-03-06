/*	$OpenBSD: clnt_udp.c,v 1.23 2005/08/08 08:05:35 espie Exp $ */
/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user.
 * 
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 * 
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 * 
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 * 
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 * 
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 */

/*
 * clnt_udp.c, Implements a UDP/IP based, client side RPC.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <rpc/rpc.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <errno.h>
#include <rpc/pmap_clnt.h>

__RCSID("$MirOS: src/lib/libc/rpc/clnt_udp.c,v 1.3 2009/11/09 21:30:53 tg Exp $");

/*
 * UDP bases client side rpc operations
 */
static enum clnt_stat	clntudp_call(CLIENT *, u_long, xdrproc_t, caddr_t,
			    xdrproc_t, caddr_t, struct timeval);
static void		clntudp_abort(CLIENT *);
static void		clntudp_geterr(CLIENT *, struct rpc_err *);
static bool_t		clntudp_freeres(CLIENT *, xdrproc_t, caddr_t);
static bool_t           clntudp_control(CLIENT *, u_int, void *);
static void		clntudp_destroy(CLIENT *);

static struct clnt_ops udp_ops = {
	clntudp_call,
	clntudp_abort,
	clntudp_geterr,
	clntudp_freeres,
	clntudp_destroy,
	clntudp_control
};

/* 
 * Private data kept per client handle
 */
struct cu_data {
	int		   cu_sock;
	bool_t		   cu_closeit;
	struct sockaddr_in cu_raddr;
	int		   cu_rlen;
	struct timeval	   cu_wait;
	struct timeval     cu_total;
	struct rpc_err	   cu_error;
	XDR		   cu_outxdrs;
	u_int		   cu_xdrpos;
	u_int		   cu_sendsz;
	char		   *cu_outbuf;
	u_int		   cu_recvsz;
	char		   cu_inbuf[1];
};

/*
 * Create a UDP based client handle.
 * If *sockp<0, *sockp is set to a newly created UPD socket.
 * If raddr->sin_port is 0 a binder on the remote machine
 * is consulted for the correct port number.
 * NB: It is the clients responsibility to close *sockp.
 * NB: The rpch->cl_auth is initialized to null authentication.
 *     Caller may wish to set this something more useful.
 *
 * wait is the amount of time used between retransmitting a call if
 * no response has been heard;  retransmission occurs until the actual
 * rpc call times out.
 *
 * sendsz and recvsz are the maximum allowable packet sizes that can be
 * sent and received.
 */
CLIENT *
clntudp_bufcreate(struct sockaddr_in *raddr, u_long program, u_long version,
    struct timeval wait_, int *sockp, u_int sendsz, u_int recvsz)
{
	CLIENT *cl;
	struct cu_data *cu = NULL;
	struct timeval now;
	struct rpc_msg call_msg;

	cl = (CLIENT *)mem_alloc(sizeof(CLIENT));
	if (cl == NULL) {
		(void) fprintf(stderr, "clntudp_create: out of memory\n");
		rpc_createerr.cf_stat = RPC_SYSTEMERROR;
		rpc_createerr.cf_error.re_errno = errno;
		goto fooy;
	}
	sendsz = ((sendsz + 3) / 4) * 4;
	recvsz = ((recvsz + 3) / 4) * 4;
	cu = (struct cu_data *)mem_alloc(sizeof(*cu) + sendsz + recvsz);
	if (cu == NULL) {
		(void) fprintf(stderr, "clntudp_create: out of memory\n");
		rpc_createerr.cf_stat = RPC_SYSTEMERROR;
		rpc_createerr.cf_error.re_errno = errno;
		goto fooy;
	}
	cu->cu_outbuf = &cu->cu_inbuf[recvsz];

	(void)gettimeofday(&now, NULL);
	if (raddr->sin_port == 0) {
		u_short port;
		if ((port =
		    pmap_getport(raddr, program, version, IPPROTO_UDP)) == 0) {
			goto fooy;
		}
		raddr->sin_port = htons(port);
	}
	cl->cl_ops = &udp_ops;
	cl->cl_private = (caddr_t)cu;
	cu->cu_raddr = *raddr;
	cu->cu_rlen = sizeof (cu->cu_raddr);
	cu->cu_wait = wait_;
	cu->cu_total.tv_sec = -1;
	cu->cu_total.tv_usec = -1;
	cu->cu_sendsz = sendsz;
	cu->cu_recvsz = recvsz;
	call_msg.rm_xid = arc4random();
	call_msg.rm_direction = CALL;
	call_msg.rm_call.cb_rpcvers = RPC_MSG_VERSION;
	call_msg.rm_call.cb_prog = program;
	call_msg.rm_call.cb_vers = version;
	xdrmem_create(&(cu->cu_outxdrs), cu->cu_outbuf,
	    sendsz, XDR_ENCODE);
	if (!xdr_callhdr(&(cu->cu_outxdrs), &call_msg)) {
		goto fooy;
	}
	cu->cu_xdrpos = XDR_GETPOS(&(cu->cu_outxdrs));
	if (*sockp < 0) {
		int dontblock = 1;

		*sockp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (*sockp < 0) {
			rpc_createerr.cf_stat = RPC_SYSTEMERROR;
			rpc_createerr.cf_error.re_errno = errno;
			goto fooy;
		}
		/* attempt to bind to priv port */
		(void)bindresvport(*sockp, NULL);
		/* the sockets rpc controls are non-blocking */
		(void)ioctl(*sockp, FIONBIO, (char *) &dontblock);
		cu->cu_closeit = TRUE;
	} else {
		cu->cu_closeit = FALSE;
	}
	cu->cu_sock = *sockp;
	cl->cl_auth = authnone_create();
	return (cl);
fooy:
	if (cu)
		mem_free((caddr_t)cu, sizeof(*cu) + sendsz + recvsz);
	if (cl)
		mem_free((caddr_t)cl, sizeof(CLIENT));
	return (NULL);
}

CLIENT *
clntudp_create(struct sockaddr_in *raddr, u_long program, u_long version,
    struct timeval wait_, int *sockp)
{

	return(clntudp_bufcreate(raddr, program, version, wait_, sockp,
	    UDPMSGSIZE, UDPMSGSIZE));
}

static enum clnt_stat 
clntudp_call(CLIENT *cl,	/* client handle */
    u_long proc,		/* procedure number */
    xdrproc_t xargs,		/* xdr routine for args */
    caddr_t argsp,		/* pointer to args */
    xdrproc_t xresults,		/* xdr routine for results */
    caddr_t resultsp,		/* pointer to results */
    struct timeval utimeout)	/* seconds to wait before giving up */
{
	struct cu_data *cu = (struct cu_data *)cl->cl_private;
	XDR *xdrs;
	int outlen;
	int inlen;
	socklen_t fromlen;
	struct pollfd pfd[1];
	struct sockaddr_in from;
	struct rpc_msg reply_msg;
	XDR reply_xdrs;
	struct timeval time_waited, start, after, tmp1, tmp2;
	bool_t ok;
	int nrefreshes = 2;	/* number of times to refresh cred */
	struct timeval timeout;

	if (cu->cu_total.tv_usec == -1)
		timeout = utimeout;     /* use supplied timeout */
	else
		timeout = cu->cu_total; /* use default timeout */

	pfd[0].fd = cu->cu_sock;
	pfd[0].events = POLLIN;
	timerclear(&time_waited);
call_again:
	xdrs = &(cu->cu_outxdrs);
	xdrs->x_op = XDR_ENCODE;
	XDR_SETPOS(xdrs, cu->cu_xdrpos);
	/*
	 * the transaction is the first thing in the out buffer
	 */
	(*(u_short *)(cu->cu_outbuf))++;
	if (!XDR_PUTLONG(xdrs, (long *)&proc) ||
	    !AUTH_MARSHALL(cl->cl_auth, xdrs) ||
	    !(*xargs)(xdrs, argsp)) {
		return (cu->cu_error.re_status = RPC_CANTENCODEARGS);
	}
	outlen = (int)XDR_GETPOS(xdrs);

send_again:
	if (sendto(cu->cu_sock, cu->cu_outbuf, outlen, 0,
	    (struct sockaddr *)&(cu->cu_raddr), cu->cu_rlen) != outlen) {
		cu->cu_error.re_errno = errno;
		return (cu->cu_error.re_status = RPC_CANTSEND);
	}

	/*
	 * Hack to provide rpc-based message passing
	 */
	if (!timerisset(&timeout))
		return (cu->cu_error.re_status = RPC_TIMEDOUT);

	/*
	 * sub-optimal code appears here because we have
	 * some clock time to spare while the packets are in flight.
	 * (We assume that this is actually only executed once.)
	 */
	reply_msg.acpted_rply.ar_verf = _null_auth;
	reply_msg.acpted_rply.ar_results.where = resultsp;
	reply_msg.acpted_rply.ar_results.proc = xresults;

	gettimeofday(&start, NULL);
	for (;;) {
		switch (poll(pfd, 1,
		    cu->cu_wait.tv_sec * 1000 + cu->cu_wait.tv_usec / 1000)) {
		case 0:
			timeradd(&time_waited, &cu->cu_wait, &tmp1);
			time_waited = tmp1;
			if (timercmp(&time_waited, &timeout, <))
				goto send_again;
			return (cu->cu_error.re_status = RPC_TIMEDOUT);
		case 1:
			if (pfd[0].revents & POLLNVAL)
				errno = EBADF;
			else if (pfd[0].revents & POLLERR)
				errno = EIO;
			else
				break;
			/* FALLTHROUGH */
		case -1:
			if (errno == EINTR) {
				gettimeofday(&after, NULL);
				timersub(&after, &start, &tmp1);
				timeradd(&time_waited, &tmp1, &tmp2);
				time_waited = tmp2;
				if (timercmp(&time_waited, &timeout, <))
					continue;
				return (cu->cu_error.re_status = RPC_TIMEDOUT);
			}
			cu->cu_error.re_errno = errno;
			return (cu->cu_error.re_status = RPC_CANTRECV);
		}

		do {
			fromlen = sizeof(struct sockaddr);
			inlen = recvfrom(cu->cu_sock, cu->cu_inbuf, 
			    (int) cu->cu_recvsz, 0,
			    (struct sockaddr *)&from, &fromlen);
		} while (inlen < 0 && errno == EINTR);
		if (inlen < 0) {
			if (errno == EWOULDBLOCK)
				continue;
			cu->cu_error.re_errno = errno;
			return (cu->cu_error.re_status = RPC_CANTRECV);
		}
		if ((size_t)inlen < sizeof(u_int32_t))
			continue;	
		/* see if reply transaction id matches sent id */
		if (((struct rpc_msg *)(cu->cu_inbuf))->rm_xid !=
		    ((struct rpc_msg *)(cu->cu_outbuf))->rm_xid)
			continue;
		/* we now assume we have the proper reply */
		break;
	}

	/*
	 * now decode and validate the response
	 */
	xdrmem_create(&reply_xdrs, cu->cu_inbuf, (u_int)inlen, XDR_DECODE);
	ok = xdr_replymsg(&reply_xdrs, &reply_msg);
	/* XDR_DESTROY(&reply_xdrs);  save a few cycles on noop destroy */
	if (ok) {
#if 0
		/*
		 * XXX Would like to check these, but call_msg is not
		 * around.
		 */
		if (reply_msg.rm_call.cb_prog != call_msg.rm_call.cb_prog ||
		    reply_msg.rm_call.cb_vers != call_msg.rm_call.cb_vers ||
		    reply_msg.rm_call.cb_proc != call_msg.rm_call.cb_proc) {
			goto call_again;	/* XXX spin? */
		}
#endif

		_seterr_reply(&reply_msg, &(cu->cu_error));
		if (cu->cu_error.re_status == RPC_SUCCESS) {
			if (!AUTH_VALIDATE(cl->cl_auth,
			    &reply_msg.acpted_rply.ar_verf)) {
				cu->cu_error.re_status = RPC_AUTHERROR;
				cu->cu_error.re_why = AUTH_INVALIDRESP;
			}
			if (reply_msg.acpted_rply.ar_verf.oa_base != NULL) {
				xdrs->x_op = XDR_FREE;
				(void)xdr_opaque_auth(xdrs,
				    &(reply_msg.acpted_rply.ar_verf));
			} 
		} else {
			/* maybe our credentials need to be refreshed ... */
			if (nrefreshes > 0 && AUTH_REFRESH(cl->cl_auth)) {
				nrefreshes--;
				goto call_again;
			}
		}
	} else {
		/* xdr_replymsg() may have left some things allocated */
		int op = reply_xdrs.x_op;
		reply_xdrs.x_op = XDR_FREE;
		xdr_replymsg(&reply_xdrs, &reply_msg);
		reply_xdrs.x_op = op;
		cu->cu_error.re_status = RPC_CANTDECODERES;
	}

	return (cu->cu_error.re_status);
}

static void
clntudp_geterr(CLIENT *cl, struct rpc_err *errp)
{
	struct cu_data *cu = (struct cu_data *)cl->cl_private;

	*errp = cu->cu_error;
}


static bool_t
clntudp_freeres(CLIENT *cl, xdrproc_t xdr_res, caddr_t res_ptr)
{
	struct cu_data *cu = (struct cu_data *)cl->cl_private;
	XDR *xdrs = &(cu->cu_outxdrs);

	xdrs->x_op = XDR_FREE;
	return ((*xdr_res)(xdrs, res_ptr));
}

static void 
clntudp_abort(CLIENT *clnt __unused)
{
}

static bool_t
clntudp_control(CLIENT *cl, u_int request, void *info)
{
	struct cu_data *cu = (struct cu_data *)cl->cl_private;

	switch (request) {
	case CLSET_TIMEOUT:
		cu->cu_total = *(struct timeval *)info;
		break;
	case CLGET_TIMEOUT:
		*(struct timeval *)info = cu->cu_total;
		break;
	case CLSET_RETRY_TIMEOUT:
		cu->cu_wait = *(struct timeval *)info;
		break;
	case CLGET_RETRY_TIMEOUT:
		*(struct timeval *)info = cu->cu_wait;
		break;
	case CLGET_SERVER_ADDR:
		*(struct sockaddr_in *)info = cu->cu_raddr;
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}
	
static void
clntudp_destroy(CLIENT *cl)
{
	struct cu_data *cu = (struct cu_data *)cl->cl_private;

	if (cu->cu_closeit) {
		(void)close(cu->cu_sock);
	}
	XDR_DESTROY(&(cu->cu_outxdrs));
	mem_free((caddr_t)cu, (sizeof(*cu) + cu->cu_sendsz + cu->cu_recvsz));
	mem_free((caddr_t)cl, sizeof(CLIENT));
}
