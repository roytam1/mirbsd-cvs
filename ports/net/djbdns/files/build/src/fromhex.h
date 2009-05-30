/* $MirOS: ports/net/djbdns/files/build/src/fromhex.h,v 1.1 2006/07/27 00:58:15 tg Exp $ */

static inline int fromhex(unsigned char);

static inline int
fromhex(unsigned char c)
{
	if ((c >= '0') && (c <= '9'))
		return (c - '0');
	if ((c >= 'a') && (c <= 'f'))
		return (c - 'a' + 10);
	if ((c >= 'A') && (c <= 'F'))
		return (c - 'A' + 10);
	return (-1);
}
