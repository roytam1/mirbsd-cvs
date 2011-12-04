# $MirOS: src/gnu/usr.sbin/sendmail/Makefile.inc,v 1.2 2005/03/13 15:11:40 tg Exp $
# $OpenBSD: Makefile.inc,v 1.16 2004/06/24 03:59:23 millert Exp $

.ifndef _MODSRC_GNU_USR_SBIN_SENDMAIL_MAKEFILE_INC
_MODSRC_GNU_USR_SBIN_SENDMAIL_MAKEFILE_INC=1

.include <bsd.own.mk>
SENDMAIL_WANT_LDAP?=	No

.include <bsd.obj.mk>

.if ${MACHINE_ARCH} != "vax"
ENVDEF+=	-DSM_OMIT_BOGUS_WARNINGS
.endif
ENVDEF+=	-DNEWDB -DMAP_REGEX
ENVDEF+=	-DNETINET6 -DNEEDSGETIPNODE -DSM_CONF_SHM
ENVDEF+=	-D_FFR_QUEUERETURN_DSN

.if defined(WANT_LIBSMDB)
LDADD+=		-lsmdb
.  if exists(${.CURDIR}/../libsmdb/${__objdir})
DPADD+=		${.CURDIR}/../libsmdb/${__objdir}/libsmdb.a
LDFLAGS+=	-L${.CURDIR}/../libsmdb/${__objdir}
.  else
DPADD+=		${.CURDIR}/../libsmdb/libsmdb.a
LDFLAGS+=	-L${.CURDIR}/../libsmdb
.  endif
.endif

.if defined(WANT_LIBSMUTIL)
LDADD+=		-lsmutil
.  if exists(${.CURDIR}/../libsmutil/${__objdir})
DPADD+=		${.CURDIR}/../libsmutil/${__objdir}/libsmutil.a
LDFLAGS+=	-L${.CURDIR}/../libsmutil/${__objdir}
.  else
DPADD+=		${.CURDIR}/../libsmutil/libsmutil.a
LDFLAGS+=	-L${.CURDIR}/../libsmutil
.  endif
.endif

.if defined(WANT_LIBSM)
LDADD+=		-lsm
.  if exists(${.CURDIR}/../libsm/${__objdir})
DPADD+=		${.CURDIR}/../libsm/${__objdir}/libsm.a
LDFLAGS+=	-L${.CURDIR}/../libsm/${__objdir}
.  else
DPADD+=		${.CURDIR}/../libsm/libsm.a
LDFLAGS+=	-L${.CURDIR}/../libsm
.  endif
.endif

.if ${SENDMAIL_WANT_LDAP:L} == "yes"
ENVDEF+=	-DLDAPMAP
LDADD+=		-lldap -llber
CFLAGS+=	-I/usr/local/include
LDFLAGS+=	-L/usr/local/lib
.endif

CPPFLAGS+=	${ENVDEF} -I${.CURDIR}/../sendmail -I${.CURDIR}/../include
CFLAGS+=	-Wall

.endif
