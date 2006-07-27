/* $MirOS$ */

#if 0 /* XXX doesn't work, why? */
#define	fromhex(c)	\
	(((c >= '0') && (c <= '9')) ? (c - '0') : \
	(((c >= 'a') && (c <= 'f')) ? (c - 'a' + 10) : \
	(((c >= 'A') && (c <= 'F')) ? (c - 'A' + 10) : (-1))))
#else
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
#endif
