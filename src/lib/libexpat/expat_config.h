/* $MirOS: src/lib/libexpat/expat_config.h,v 1.1 2005/03/06 16:33:39 tg Exp $ */
/* $OpenBSD: expat_config.h,v 1.1 2004/09/22 21:36:54 espie Exp $ */

/* quick and dirty conf for OpenBSD */

#define HAVE_MEMMOVE 1
#define HAVE_MMAP 1
#define HAVE_UNISTD_H 1
#define BYTEORDER BYTE_ORDER
#define XML_CONTEXT_BYTES 1024
#define XML_DTD 1
#define XML_NS 1

#if BYTE_ORDER == BIG_ENDIAN
#define WORDS_BIGENDIAN 1
#endif
