# $MirOS: ports/net/djbdns/files/build/bins/lib/Makefile,v 1.1.201.1 2005/05/14 23:21:07 tg Exp $

LIB=		djbdns
SRCS=		alloc.c alloc_re.c auto_home.c buffer.c buffer_1.c buffer_2.c \
		buffer_copy.c buffer_get.c buffer_put.c buffer_read.c \
		buffer_write.c byte_chr.c byte_copy.c byte_cr.c byte_diff.c \
		byte_zero.c case_diffb.c case_diffs.c case_lowerb.c cdb.c \
		cdb_hash.c cdb_make.c dd.c dns_dfd.c dns_domain.c dns_dtda.c \
		dns_ip.c dns_ip6.c dns_ipq.c dns_ipq6.c dns_mx.c dns_name.c \
		dns_nd.c dns_nd6.c dns_packet.c dns_random.c dns_rcip.c \
		dns_rcrw.c dns_resolve.c dns_sortip.c dns_sortip6.c \
		dns_transmit.c dns_txt.c droproot.c env.c error.c error_str.c \
		fmt_ulong.c fmt_xlong.c generic-conf.c getln.c getln2.c \
		iopause.c ip4_fmt.c ip4_scan.c ip6_fmt.c ip6_scan.c \
		ndelay_off.c ndelay_on.c open_read.c open_trunc.c \
		openreadclose.c parsetype.c printpacket.c printrecord.c \
		prot.c qlog.c qmerge.c readclose.c response.c scan_ulong.c \
		scan_xlong.c seek_set.c server.c sgetopt.c socket_accept.c \
		socket_accept6.o socket_bind.c socket_bind6.o socket_conn.c \
		socket_connect6.o socket_getifidx.o socket_listen.c \
		clientloc.c socket_recv.c socket_recv6.o socket_send.c \
		socket_send6.o socket_tcp.c socket_tcp6.o socket_udp.c \
		socket_udp6.o str_chr.c str_diff.c str_len.c str_rchr.c \
		str_start.c stralloc_cat.c stralloc_catb.c stralloc_cats.c \
		stralloc_copy.c stralloc_eady.c stralloc_num.c \
		stralloc_opyb.c stralloc_opys.c stralloc_pend.c strerr_die.c \
		strerr_sys.c subgetopt.c tai_add.c tai_now.c tai_pack.c \
		tai_sub.c tai_uint.c tai_unpack.c taia_add.c taia_approx.c \
		taia_frac.c taia_less.c taia_now.c taia_pack.c taia_sub.c \
		taia_tai.c taia_uint.c tdlookup.c timeoutread.c \
		timeoutwrite.c uint16_pack.c uint16_unpack.c uint32_pack.c \
		uint32_unpack.c

DEBUGLIBS=	no
NOPIC=		yes

auto_home.c:
	print "const char auto_home[] = \"${TRUEPREFIX}\";" >$@

install:

.include <bsd.lib.mk>
