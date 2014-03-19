/* $MirOS: src/include/inttypes.h,v 1.5 2008/04/22 12:37:39 tg Exp $ */

#ifndef	_INTTYPES_H_
#define	_INTTYPES_H_

#include <stdint.h>

/* imaxdiv_t missing */

/* formatting macros */

#define PRId8		"d"
#define PRIi8		"i"
#define PRIo8		"o"
#define PRIu8		"u"
#define PRIx8		"x"
#define PRIX8		"X"

#define PRId16		"d"
#define PRIi16		"i"
#define PRIo16		"o"
#define PRIu16		"u"
#define PRIx16		"x"
#define PRIX16		"X"

#define PRId32		"d"
#define PRIi32		"i"
#define PRIo32		"o"
#define PRIu32		"u"
#define PRIx32		"x"
#define PRIX32		"X"

#define PRId64		"lld"
#define PRIi64		"lli"
#define PRIo64		"llo"
#define PRIu64		"llu"
#define PRIx64		"llx"
#define PRIX64		"llX"

#define PRIdLEAST8	"d"
#define PRIiLEAST8	"i"
#define PRIoLEAST8	"o"
#define PRIuLEAST8	"u"
#define PRIxLEAST8	"x"
#define PRIXLEAST8	"X"

#define PRIdLEAST16	"d"
#define PRIiLEAST16	"i"
#define PRIoLEAST16	"o"
#define PRIuLEAST16	"u"
#define PRIxLEAST16	"x"
#define PRIXLEAST16	"X"

#define PRIdLEAST32	"d"
#define PRIiLEAST32	"i"
#define PRIoLEAST32	"o"
#define PRIuLEAST32	"u"
#define PRIxLEAST32	"x"
#define PRIXLEAST32	"X"

#define PRIdLEAST64	"lld"
#define PRIiLEAST64	"lli"
#define PRIoLEAST64	"llo"
#define PRIuLEAST64	"llu"
#define PRIxLEAST64	"llx"
#define PRIXLEAST64	"llX"

#define PRIdFAST8	"d"
#define PRIiFAST8	"i"
#define PRIoFAST8	"o"
#define PRIuFAST8	"u"
#define PRIxFAST8	"x"
#define PRIXFAST8	"X"

#define PRIdFAST16	"d"
#define PRIiFAST16	"i"
#define PRIoFAST16	"o"
#define PRIuFAST16	"u"
#define PRIxFAST16	"x"
#define PRIXFAST16	"X"

#define PRIdFAST32	"d"
#define PRIiFAST32	"i"
#define PRIoFAST32	"o"
#define PRIuFAST32	"u"
#define PRIxFAST32	"x"
#define PRIXFAST32	"X"

#define PRIdFAST64	"lld"
#define PRIiFAST64	"lli"
#define PRIoFAST64	"llo"
#define PRIuFAST64	"llu"
#define PRIxFAST64	"llx"
#define PRIXFAST64	"llX"

#define PRIdMAX		"jd"
#define PRIiMAX		"ji"
#define PRIoMAX		"jo"
#define PRIuMAX		"ju"
#define PRIxMAX		"jx"
#define PRIXMAX		"jX"

#define PRIdPTR		"td"
#define PRIiPTR		"ti"
#define PRIoPTR		"to"
#define PRIuPTR		"tu"
#define PRIxPTR		"tx"
#define PRIXPTR		"tX"

/* scanning macros */

#define SCNd8		"hhd"
#define SCNi8		"hhi"
#define SCNo8		"hho"
#define SCNu8		"hhu"
#define SCNx8		"hhx"

#define SCNd16		"hd"
#define SCNi16		"hi"
#define SCNo16		"ho"
#define SCNu16		"hu"
#define SCNx16		"hx"

#define SCNd32		"d"
#define SCNi32		"i"
#define SCNo32		"o"
#define SCNu32		"u"
#define SCNx32		"x"

#define SCNd64		"lld"
#define SCNi64		"lli"
#define SCNo64		"llo"
#define SCNu64		"llu"
#define SCNx64		"llx"

#define SCNdLEAST8	"hhd"
#define SCNiLEAST8	"hhi"
#define SCNoLEAST8	"hho"
#define SCNuLEAST8	"hhu"
#define SCNxLEAST8	"hhx"

#define SCNdLEAST16	"hd"
#define SCNiLEAST16	"hi"
#define SCNoLEAST16	"ho"
#define SCNuLEAST16	"hu"
#define SCNxLEAST16	"hx"

#define SCNdLEAST32	"d"
#define SCNiLEAST32	"i"
#define SCNoLEAST32	"o"
#define SCNuLEAST32	"u"
#define SCNxLEAST32	"x"

#define SCNdLEAST64	"lld"
#define SCNiLEAST64	"lli"
#define SCNoLEAST64	"llo"
#define SCNuLEAST64	"llu"
#define SCNxLEAST64	"llx"

#define SCNdFAST8	"hhd"
#define SCNiFAST8	"hhi"
#define SCNoFAST8	"hho"
#define SCNuFAST8	"hhu"
#define SCNxFAST8	"hhx"

#define SCNdFAST16	"hd"
#define SCNiFAST16	"hi"
#define SCNoFAST16	"ho"
#define SCNuFAST16	"hu"
#define SCNxFAST16	"hx"

#define SCNdFAST32	"d"
#define SCNiFAST32	"i"
#define SCNoFAST32	"o"
#define SCNuFAST32	"u"
#define SCNxFAST32	"x"

#define SCNdFAST64	"lld"
#define SCNiFAST64	"lli"
#define SCNoFAST64	"llo"
#define SCNuFAST64	"llu"
#define SCNxFAST64	"llx"

#define SCNdMAX		"jd"
#define SCNiMAX		"ji"
#define SCNoMAX		"jo"
#define SCNuMAX		"ju"
#define SCNxMAX		"jx"

#define SCNdPTR		"td"
#define SCNiPTR		"ti"
#define SCNoPTR		"to"
#define SCNuPTR		"tu"
#define SCNxPTR		"tx"

/* functions */

__BEGIN_DECLS
intmax_t strtoimax(const char *, char **, int);
uintmax_t strtoumax(const char *, char **, int);
__END_DECLS

#endif /* ndef _INTTYPES_H_ */
