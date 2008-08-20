# $MirOS$

CATEGORIES=		databases python
COMMENT=		PostgreSQL database adapter for Python
MODPY_EGG_VERSION=	2.0.7
DISTNAME=		psycopg2-${MODPY_EGG_VERSION}
PKGNAME=		py-${DISTNAME}-${DASH_VER}
HOMEPAGE=		http://initd.org/projects/psycopg2

# GNU GPLv2+
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://initd.org/pub/software/psycopg/

MODULES+=		lang/python
LIB_DEPENDS+=		pq::databases/postgresql
RUN_DEPENDS+=		:postgresql-client-*:databases/postgresql
REGRESS_DEPENDS+=	:postgresql-client-*:databases/postgresql

# To run the tests, create and start a test database as follows:
#	createdb psycopg2_test
# The regress target will use the PSYCOPG2_TESTDB environment
# variable to connect to the database; see below for defaults. The
# user running the regress test will be used to make the connection
# and should own the database:
#	echo "ALTER DATABASE psycopg2_test OWNER TO ${USER};" | \
#	    psql -U postgres
REGRESS_IS_INTERACTIVE=	Yes
PSYCOPG2_TESTDB?=	psycopg2_test

#XXX What the F…?
LDFLAGS+=		-L${MODPY_LIBDIR:Q}/config

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/{doc,examples}/py-psycopg2
	cd ${WRKSRC}/doc && pax -rw . ${PREFIX}/share/doc/py-psycopg2/
	${INSTALL_DATA} ${WRKSRC}/examples/* \
	    ${PREFIX}/share/examples/py-psycopg2/

do-regress: fake
	cd ${WRKSRC}/tests && ${SETENV} \
	    PYTHONPATH=${WRKINST:Q}${MODPY_SITEPKG:Q}:../ \
	    ${MODPY_BIN} ./runtests.py

.include <bsd.port.mk>
