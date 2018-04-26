# $MirOS: www/users/tg/Makefile,v 1.4 2014/08/16 20:19:54 tg Exp $
#-
# This file is part of the website of The MirOS Project, which is
# copyrighted material, please read the LICENCE file for details.

.ifndef TOP
TOP!=		realpath ${.CURDIR:Q}/../..
DST!=		realpath ${.OBJDIR:Q}/../..
.MAKEFLAGS:=	${.MAKEFLAGS} TOP=${TOP:Q} DST=${DST:Q}
.endif

U_ENV+=		TOP=${TOP:Q} DST=${DST:Q} MKSH=${MKSH:Q} SHELL=${MKSH:Q} TZ=UTC

FILES!=		cd ${.CURDIR} && print -r -- *.inc
_inc2xhtml=	( (print '\n----'; sed -e '/^\#/d' -e '/^RCSID: \$$/d') | \
		    tr '\n' '' | sed \
		    -e 'sg' \
		    -e 's----g' \
		    -e 's\([^]*\)\1g' \
		    -e 's\([^]*\)\1g' \
		    -e 's\([^]*\)*[Tt][Ii][Tt][Ll][Ee]:[	 ]*\([^]*\)\([^]*\)\{0,1\}</div><h2><a href="/">\2</a></h2><div>g' \
		    -e 's[^]*</div><div>g' \
		    -e 's^</div>'${_xhtmlbeg:Q}'' \
		    -e 's$$</div>'${_xhtmlend:Q}'' \
		    -e 's<><error><>g' \
		    -e 'sg' \
		    | \
		tr '' '\n')
_xhtmldtd=	${TOP}/files/xhtml11.dtd
_xhtmlbeg=	<?xml version="1.0"?> \
		<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" \
		 "file://${_xhtmldtd}"> \
		<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en"> \
		<head> \
		 <title>XHTML page</title> \
		</head><body>
_xhtmlend=	</body></html>

all: validations

.SUFFIXES: .xml .inc

.inc.xml:
	@print -r Creating ${@:Q} from ${<:Q} ...
	@${_inc2xhtml} <$< >$@

validations: xmlcheck wpcheck validation

xmlcheck: .PHONY
	cd ${TOP} && ${MAKE} validate="$$(cd ${.CURDIR:Q} && \
	    for x in *.hts; do \
		[[ -e $$x ]] && print -r -- "$${x%%.hts}"; \
	done)"

wpcheck:
	@cd ${TOP}/data && ${MAKE} $@ WPS=tg.gc

validation: .PHONY ${FILES:.inc=.xml}
	@print -r Validating ${FILES:Q} ...
	@xmlstarlet val -d ${_xhtmldtd} -e ${.ALLSRC}
	@print '\nValidation complete.'

.ifdef validate
root_validation:
	@cd ${TOP} && ${MAKE} validate=${validate:Q}
.MAIN: root_validation
.endif

.include <bsd.obj.mk>
