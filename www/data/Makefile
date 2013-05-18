# $MirOS: www/data/Makefile,v 1.3 2009/11/12 22:41:31 tg Exp $
#-
# This file is part of the website of The MirOS Project, which is
# copyrighted material, please read the LICENCE file for details.

.ifndef TOP
TOP!=		realpath ${.CURDIR:Q}/..
DST!=		realpath ${.OBJDIR:Q}/..
.MAKEFLAGS:=	${.MAKEFLAGS} TOP=${TOP:Q} DST=${DST:Q}
.endif

FILES!=		cd ${.CURDIR} && print -r -- *.inc
_inc2xhtml=	( (print '\n----'; cat) | tr '\n' '﷐' | \
		sed -e 's﷐﷐g' \
		    -e 's﷐----﷐[^]*</div><div>g' \
		    -e 's^</div>'${_xhtmlbeg:Q}'' \
		    -e 's﷐----﷐$$</div>'${_xhtmlend:Q}'﷐' \
		    -e 's﷐﷐g' | \
		tr '﷐' '\n')
_xhtmldtd=	${TOP}/mk/xhtml11.dtd
_xhtmlbeg=	<?xml version="1.0"?> \
		<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" \
		 "file://${_xhtmldtd}"> \
		<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en"> \
		<head> \
		 <title>XHTML page</title> \
		</head><body>
_xhtmlend=	</body></html>

all: validation

.SUFFIXES: .xml .inc

.inc.xml:
	@print -r Creating ${@:Q} from ${<:Q} ...
	@${_inc2xhtml} <$< >$@

validation: .PHONY ${FILES:.inc=.xml}
	@print -r Validating ${FILES:Q} ...
	@xmlstarlet val -d ${_xhtmldtd} ${.ALLSRC}
	@print '\nValidation complete.'

.include <bsd.obj.mk>
