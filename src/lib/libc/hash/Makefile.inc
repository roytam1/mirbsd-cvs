# $MirOS: src/lib/libc/hash/Makefile.inc,v 1.8 2010/01/07 22:34:51 tg Exp $
# $OpenBSD: Makefile.inc,v 1.17 2004/05/03 17:30:14 millert Exp $

# hash functions
.PATH: ${LIBCSRCDIR}/hash

HELPER=	md4hl.c md5hl.c rmd160hl.c sha1hl.c sha256hl.c sha384hl.c sha512hl.c \
	adler32hl.c sfvhl.c sumahl.c tigerhl.c whirlpoolhl.c
SRCS+=	adh32.c md4.c md5.c rmd160.c sfv.c sha1.c sha2.c tiger.c whirlpool.c \
	${HELPER}
MAN+=	adler32.3 md4.3 md5.3 rmd160.3 sfv.3 sha1.3 sha2.3 suma.3 tiger.3 \
	whirlpool.3

.if exists(suma-${MACHINE_ARCH}.S)
SRCS+=	suma-${MACHINE_ARCH}.S
.else
SRCS+=	suma.c
.endif

MLINKS+=adler32.3 ADLER32Init.3    adler32.3 ADLER32Update.3
MLINKS+=adler32.3 ADLER32Data.3
MLINKS+=adler32.3 ADLER32Final.3   adler32.3 ADLER32End.3
MLINKS+=adler32.3 ADLER32File.3    adler32.3 ADLER32FileChunk.3
MLINKS+=md4.3 MD4Transform.3 md4.3 MD4Init.3 md4.3 MD4Final.3
MLINKS+=md4.3 MD4Update.3    md4.3 MD4End.3  md4.3 MD4File.3
MLINKS+=md4.3 MD4FileChunk.3 md4.3 MD4Pad.3  md4.3 MD4Data.3
MLINKS+=md5.3 MD5Transform.3 md5.3 MD5Init.3 md5.3 MD5Final.3
MLINKS+=md5.3 MD5Update.3    md5.3 MD5End.3  md5.3 MD5File.3
MLINKS+=md5.3 MD5FileChunk.3 md5.3 MD5Pad.3  md5.3 MD5Data.3
MLINKS+=rmd160.3 RMD160Transform.3 rmd160.3 RMD160Init.3 rmd160.3 RMD160Final.3
MLINKS+=rmd160.3 RMD160Update.3    rmd160.3 RMD160End.3  rmd160.3 RMD160File.3
MLINKS+=rmd160.3 RMD160FileChunk.3 rmd160.3 RMD160Pad.3  rmd160.3 RMD160Data.3
MLINKS+=sfv.3 SFVInit.3        sfv.3 SFVUpdate.3
MLINKS+=sfv.3 SFVPad.3         sfv.3 SFVData.3
MLINKS+=sfv.3 SFVFinal.3       sfv.3 SFVEnd.3
MLINKS+=sfv.3 SFVFile.3        sfv.3 SFVFileChunk.3
MLINKS+=sha1.3 SHA1Transform.3 sha1.3 SHA1Init.3 sha1.3 SHA1Final.3
MLINKS+=sha1.3 SHA1Update.3    sha1.3 SHA1End.3  sha1.3 SHA1File.3
MLINKS+=sha1.3 SHA1FileChunk.3 sha1.3 SHA1Pad.3  sha1.3 SHA1Data.3
MLINKS+=sha2.3 SHA256_Init.3 sha2.3 SHA256_Update.3 sha2.3 SHA256_Final.3
MLINKS+=sha2.3 SHA256_End.3  sha2.3 SHA256_File.3   sha2.3 SHA256_Data.3
MLINKS+=sha2.3 SHA256_Pad.3  sha2.3 SHA256_FileChunk.3
MLINKS+=sha2.3 SHA384_Init.3 sha2.3 SHA384_Update.3 sha2.3 SHA384_Final.3
MLINKS+=sha2.3 SHA384_End.3  sha2.3 SHA384_File.3   sha2.3 SHA384_Data.3
MLINKS+=sha2.3 SHA384_Pad.3  sha2.3 SHA384_FileChunk.3
MLINKS+=sha2.3 SHA512_Init.3 sha2.3 SHA512_Update.3 sha2.3 SHA512_Final.3
MLINKS+=sha2.3 SHA512_End.3  sha2.3 SHA512_File.3   sha2.3 SHA512_Data.3
MLINKS+=sha2.3 SHA512_Pad.3  sha2.3 SHA512_FileChunk.3
MLINKS+=suma.3 SUMAInit.3    suma.3 SUMAUpdate.3
MLINKS+=suma.3 SUMAPad.3     suma.3 SUMAData.3
MLINKS+=suma.3 SUMAFinal.3   suma.3 SUMAEnd.3
MLINKS+=suma.3 SUMAFile.3    suma.3 SUMAFileChunk.3
MLINKS+=tiger.3 TIGERInit.3  tiger.3 TIGERUpdate.3    tiger.3 TIGERPad.3
MLINKS+=tiger.3 TIGERFinal.3 tiger.3 TIGERTransform.3 tiger.3 TIGEREnd.3
MLINKS+=tiger.3 TIGERFile.3  tiger.3 TIGERFileChunk.3 tiger.3 TIGERData.3
MLINKS+=whirlpool.3 WHIRLPOOLInit.3  whirlpool.3 WHIRLPOOLUpdate.3
MLINKS+=whirlpool.3 WHIRLPOOLPad.3   whirlpool.3 WHIRLPOOLData.3
MLINKS+=whirlpool.3 WHIRLPOOLFinal.3 whirlpool.3 WHIRLPOOLEnd.3
MLINKS+=whirlpool.3 WHIRLPOOLFile.3  whirlpool.3 WHIRLPOOLFileChunk.3
CLEANFILES+= ${HELPER} md[45].3

.if !defined(NOMAN) || ${NOMAN:L} == "no"
all:	md4.3 md5.3

md4.3:  mdX.3
	sed -e 's/mdX/md4/g' -e 's/mdY/md5/g' -e 's/MDX/MD4/g' $> > $@

md5.3:  mdX.3
	sed -e 's/mdX/md5/g' -e 's/mdY/md4/g' -e 's/MDX/MD5/g' $> > $@
.endif

adler32hl.c:	helper.c
	sed -e 's/hashinc/adler32.h/g' -e 's/HASH/ADLER32/g' $> > $@

md4hl.c:	helper.c
	sed -e 's/hashinc/md4.h/g' -e 's/HASH/MD4/g' $> > $@

md5hl.c:	helper.c
	sed -e 's/hashinc/md5.h/g' -e 's/HASH/MD5/g' $> > $@

rmd160hl.c:	helper.c
	sed -e 's/hashinc/rmd160.h/g' -e 's/HASH/RMD160/g' $> > $@

sfvhl.c:	helper.c
	sed -e 's/hashinc/sfv.h/g' -e 's/HASH/SFV/g' $> > $@

sha1hl.c:	helper.c
	sed -e 's/hashinc/sha1.h/g' -e 's/HASH/SHA1/g' $> > $@

sha256hl.c:	helper.c
	sed -e 's/hashinc/sha2.h/g' -e 's/HASH_\{0,1\}/SHA256_/g' $> > $@

sha384hl.c:	helper.c
	sed -e 's/hashinc/sha2.h/g' -e 's/HASH_\{0,1\}/SHA384_/g' $> > $@

sha512hl.c:	helper.c
	sed -e 's/hashinc/sha2.h/g' -e 's/HASH_\{0,1\}/SHA512_/g' $> > $@

sumahl.c:	helper.c
	sed -e 's/hashinc/suma.h/g' -e 's/HASH/SUMA/g' $> > $@

tigerhl.c:	helper.c
	sed -e 's/hashinc/tiger.h/g' -e 's/HASH/TIGER/g' $> > $@

whirlpoolhl.c:	helper.c
	sed -e 's/hashinc/whirlpool.h/g' -e 's/HASH/WHIRLPOOL/g' $> > $@

beforedepend: ${HELPER}
