# $MirOS: ports/math/maple/Makefile,v 1.5 2007/03/31 22:02:03 tg Exp $
# $OpenBSD: Makefile,v 1.22 2002/12/29 19:43:50 fgsch Exp $
# XXX This port installs in a somewhat unusual way.

.include <mirports.sys.mk>

# if someone wants to buy the sparc version and check it, be my guest...
ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

COMMENT=			algebraic and symbolic computations; commercial

# Directory where the maple CDROM was mounted
.if !defined(MAPLE_CDROM)
IGNORE="Commercial port, mount the maple cdrom and build with make MAPLE_CDROM=mount_point"
.endif

# where the basic distribution unpacks
MAPLE_DIR?=${PREFIX}/maple
TRUEMAPLE_DIR?=${TRUEPREFIX}/maple

DISTNAME=	maple-5.5
CATEGORIES=     math

RUN_DEPENDS+=		::emulators/fedora

PERMIT_DISTFILES_CDROM=	"commercial"
PERMIT_DISTFILES_FTP=	"commercial"
PERMIT_PACKAGE_FTP=	"commercial"
PERMIT_PACKAGE_CDROM=	"commercial"


WRKDIST=	${WRKDIR}

# we only use the CD-Rom files for markers
DIST_SUBDIR=maple5.5
DISTFILES=readme install \
install_base/base.tar install_base/bin.tar install_base/license.tar \
install_bins/bin_ibm_intel_linux.tar

# and so, we don't extract anything by ourselves
# better than NO_EXTRACT, as this builds WRKDIR correctly for us.
EXTRACT_ONLY=

COPY_MAPLE_DISTFILES?=No
.if ${COPY_MAPLE_DISTFILES:L} == "no"
COPY_CMD=ln -sf
.else
COPY_CMD=cp -f
.endif

post-extract:
	ln -sf ${FILESDIR}/resolv_display.c ${WRKSRC}
	echo "all: resolv_display" >${WRKSRC}/Makefile

ALL_TARGET=resolv_display

do-fetch:
	@mkdir -p ${FULLDISTDIR}
	@cd ${MAPLE_CDROM}; \
	for file in ${DISTFILES}; do\
		[ -f ${FULLDISTDIR}/$$file ] || \
		if [ -f $$file ]; \
		then\
			mkdir -p ${FULLDISTDIR}/`dirname $$file`;\
			${COPY_CMD} ${MAPLE_CDROM}/$$file ${FULLDISTDIR}/$$file;\
		else\
			echo "File $$file not found. Is your cdrom mounted as ${MAPLE_CDROM} ?";\
		fi\
	done

MAPLE_SCRIPTS=maple march mint updtsrc xmaple

do-install:
	@mkdir -p ${MAPLE_DIR} || echo "${MAPLE_DIR} already exists"
	@cd ${MAPLE_DIR} && yes | ${FULLDISTDIR}/install
	@echo "But this installation script does it for you"
	@for file in ${MAPLE_SCRIPTS}; do\
		sed -e 's,/usr/local/maple,${TRUEMAPLE_DIR},' ${MAPLE_DIR}/bin/$$file >${WRKDIST}/$$file; \
		cp ${WRKDIST}/$$file ${MAPLE_DIR}/bin; \
		ln -sf ${TRUEMAPLE_DIR}/bin/$$file ${PREFIX}/bin; \
	done
	@for file in ${MAPLE_DIR}/man/man1/*; do \
		ln -s ${TRUEMAPLE_DIR}/man/man1/`basename $$file` ${PREFIX}/man/man1; \
	done
	@cd ${MAPLE_DIR} && cat ${PATCHDIR}/install-*| patch -s && \
		rm ${MAPLE_DIR}/bin/*.orig
	@${INSTALL_PROGRAM} ${WRKBUILD}/resolv_display ${MAPLE_DIR}/bin

.include <bsd.port.mk>
