# $MirOS: src/gnu/usr.sbin/sendmail/Makefile.inc,v 1.7 2008/05/07 13:15:14 tg Exp $
# $OpenBSD: Makefile.inc,v 1.17 2006/02/04 09:46:23 mbalmer Exp $

.ifndef _MODSRC_GNU_USR_SBIN_SENDMAIL_MAKEFILE_INC
_MODSRC_GNU_USR_SBIN_SENDMAIL_MAKEFILE_INC=1

.include <bsd.own.mk>
SENDMAIL_WANT_LDAP?=	No
LOCALBASE?=		/usr/mpkg

.include <bsd.obj.mk>

.if (${MACHINE_ARCH} != "vax")
ENVDEF+=-DSM_OMIT_BOGUS_WARNINGS
.endif
ENVDEF+= -DNEWDB -DMAP_REGEX
ENVDEF+= -DNETINET6 -DNEEDSGETIPNODE -DSM_CONF_SHM
ENVDEF+=	-D_FFR_QUEUERETURN_DSN

.if defined(WANT_LIBSMDB)
LDADD+= -lsmdb
.if exists(${.CURDIR}/../libsmdb/${__objdir})
DPADD+= ${.CURDIR}/../libsmdb/${__objdir}/libsmdb.a
LDFLAGS+=-L${.CURDIR}/../libsmdb/${__objdir}
.else
DPADD+= ${.CURDIR}/../libsmdb/libsmdb.a
LDFLAGS+=-L${.CURDIR}/../libsmdb
.endif
.endif

.if defined(WANT_LIBSMUTIL)
LDADD+= -lsmutil
.if exists(${.CURDIR}/../libsmutil/${__objdir})
DPADD+= ${.CURDIR}/../libsmutil/${__objdir}/libsmutil.a
LDFLAGS+=-L${.CURDIR}/../libsmutil/${__objdir}
.else
DPADD+= ${.CURDIR}/../libsmutil/libsmutil.a
LDFLAGS+=-L${.CURDIR}/../libsmutil
.endif
.endif

.if defined(WANT_LIBSM)
LDADD+= -lsm
.if exists(${.CURDIR}/../libsm/${__objdir})
DPADD+= ${.CURDIR}/../libsm/${__objdir}/libsm.a
LDFLAGS+=-L${.CURDIR}/../libsm/${__objdir}
.else
DPADD+= ${.CURDIR}/../libsm/libsm.a
LDFLAGS+=-L${.CURDIR}/../libsm
.endif
.endif

.if ${SENDMAIL_WANT_LDAP:L} == "yes"
.if !defined(LIB) || (${LIB} != "milter")
ENVDEF+= -DLDAPMAP
LDADD+=-lldap -llber
CPPFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib
.endif
.endif

CPPFLAGS+=	${ENVDEF} -I${.CURDIR}/../sendmail -I${.CURDIR}/../include
COPTS+=		-Wall

.endif
