# $MirOS: src/lib/libusbhid/Makefile,v 1.4 2007/05/17 18:38:35 tg Exp $
# $OpenBSD: Makefile,v 1.3 2004/06/04 00:47:32 deraadt Exp $
# $NetBSD: Makefile,v 1.5 1999/07/23 09:44:38 mrg Exp $

SHLIB_VERSION?=	6.0
LIB=		usbhid
MAN=		usbhid.3
HDRS=		usbhid.h

MLINKS=	usbhid.3 hid_dispose_report_desc.3 \
	usbhid.3 hid_end_parse.3 \
	usbhid.3 hid_get_data.3 \
	usbhid.3 hid_get_item.3 \
	usbhid.3 hid_get_report_desc.3 \
	usbhid.3 hid_init.3 \
	usbhid.3 hid_start.3 \
	usbhid.3 hid_locate.3 \
	usbhid.3 hid_parse_usage_in_page.3 \
	usbhid.3 hid_parse_usage_page.3 \
	usbhid.3 hid_report_size.3 \
	usbhid.3 hid_set_data.3 \
	usbhid.3 hid_start_parse.3 \
	usbhid.3 hid_usage_in_page.3 \
	usbhid.3 hid_usage_page.3 \
	usbhid.3 hid_use_report_desc.3

SRCS=	descr.c parse.c usage.c data.c

.include <bsd.lib.mk>
