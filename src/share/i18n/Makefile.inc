# $MirOS: src/share/i18n/Makefile.inc,v 1.2 2006/01/31 16:26:48 tg Exp $

.ifndef _MODSRC_SHARE_I18N_MAKEFILE_INC
_MODSRC_SHARE_I18N_MAKEFILE_INC=1

_MKTARGET_CREATE?=@:

# $NetBSD: bsd.files.mk,v 1.37 2004/05/17 12:58:17 lukem Exp $

##### Basic targets
realinstall:	filesinstalldirs .WAIT filesinstall

##### Default values
FILESDIR?=	${BINDIR}
FILESOWN?=	${BINOWN}
FILESGRP?=	${BINGRP}
FILESMODE?=	${NONBINMODE}

.for F in ${FILES}
FILESOWN_${F:T}?=${FILESOWN}
FILESGRP_${F:T}?=${FILESGRP}
FILESMODE_${F:T}?=${FILESMODE}
FILESDIR_${F:T}?=${FILESDIR}
FILESNAME_${F:T}?=${FILESNAME}

_FDIR:=		${FILESDIR_${F}}			# dir override
_FNAME:=	${FILESNAME_${F}}			# name override
_F:=		${DESTDIR}${_FDIR}/${_FNAME}		# installed path

${_F}!		${F}					# install rule
	${INSTALL} ${INSTALL_COPY} \
	    -o ${FILESOWN_${F:T}} \
	    -g ${FILESGRP_${F:T}} \
	    -m ${FILESMODE_${F:T}} \
	    ${SYSPKGTAG} $> ${.TARGET}
.if !defined(BUILD) && !make(all) && !make(${F})
${_F}!		.MADE					# no build at install
.endif

filesinstall::	${_F}
.PRECIOUS: 	${_F}					# keep if install fails
.endfor

filesinstalldirs:
.if defined(_ALLFDIRS) && !empty(_ALLFDIRS)
.  for _i in ${_ALLFDIRS}
	mkdir -p ${DESTDIR}${_i}
.  endfor
.endif

.endif
