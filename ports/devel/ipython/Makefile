# $MirOS: ports/devel/ipython/Makefile,v 1.2 2008/08/26 16:35:29 tg Exp $

COMMENT=		enhanced interactive Python shell
MODPY_EGG_VERSION=	0.10
DISTNAME=		ipython-${MODPY_EGG_VERSION}
CATEGORIES=		devel
HOMEPAGE=		http://ipython.scipy.org/moin/
MODULES=		lang/python

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://ipython.scipy.org/dist/${MODPY_EGG_VERSION}/

# The file COPYING is actually missing from the distfile (although
# docs contains license_and_copyright.html), and the Debian guys
# as usual went anal and documented even the files NOT under BSDL…
SVN_DISTDIR1=		-
SVN_DISTFILE1=		ipython-debian-copyright
SVN_DISTPATH1=		svn://svn.debian.org/python-modules/packages/ipython/tags/0.10-2/debian/copyright
SVN_DISTREV1=		12743

NO_REGRESS=		Yes

post-install:
	mv ${PREFIX}/share/doc/ipython/examples ${PREFIX}/share/examples/ipython
	${INSTALL_DATA} ${WRKSRC}/docs/emacs/ipython.el \
	    ${PREFIX}/share/examples/ipython/
	mv ${PREFIX}/share/doc/ipython/manual/* ${PREFIX}/share/doc/ipython/
	rmdir ${PREFIX}/share/doc/ipython/manual
	${INSTALL_DATA} ${WRKDIR}/${SVN_DISTFILE1}-r${SVN_DISTREV1} \
	    ${PREFIX}/share/doc/ipython/COPYING
	gzip -d ${PREFIX}/share/man/man1/*.gz
	mv ${PREFIX}/share/man/man1/* ${PREFIX}/man/man1/
	find -d ${PREFIX}/share/man -type d | xargs rmdir

.include <bsd.port.mk>
