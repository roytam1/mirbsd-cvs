# $MirOS: www/Makefile,v 1.3 2007/06/10 00:02:35 tg Exp $
#-
# This file is part of the website of The MirOS Project, which is
# copyrighted material, please read the LICENCE file for details.

.ifndef TOP
TOP!=		readlink -nf ${.CURDIR:Q}
DST!=		readlink -nf ${.OBJDIR:Q}
MAKEFLAGS+=	TOP=${TOP:Q} DST=${DST:Q}
.endif

all:

.include <bsd.own.mk>
BSDSRCDIR?=/nonexistant
.if exists(${DST}/.depend)
.  include "${DST}/.depend"
.endif

U_ENV+=		TOP=${TOP:Q} DST=${DST:Q} MKSH=${MKSH:Q} SHELL=${MKSH:Q}

SRCS+=		main.hts mksh.hts
WLOGS=		9

INCSRCS+=	news
news.cut: stamp_news
CLEANFILES+=	news.cut

.PATH: ${TOP}/src

all:
install: site.tgz

OBJS+=		${SRCS:M*.hts:S/hts$/htm/}
CLEANFILES+=	${SRCS:M*.hts:S/hts$/htm/}

DEPSRCS+=	${SRCS:S,^,src/,}
INCSRCS+=	${WLOGS:S/^/wlog-/}

.for _i in ${INCSRCS}
GENSRCS+=	stamp_${_i}

stamp_${_i}: getdate ${DEPS_mk_inc2htm} \
    ${TOP}/data/${_i}.inc ${TOP}/data/${_i}.cfg
	${U_ENV} ${MKSH} ${TOP}/mk/inc2htm ${_i} >$@
.endfor
DEPSRCS+=	mk/inc2htm
OBJS+=		${GENSRCS}
CLEANFILES+=	${GENSRCS}

clean:
.for _i in ${GENSRCS}
	-rm -rf $$(<${_i})
.endfor
	-rm -rf dst permalinks
	-rm -f ${CLEANFILES} site.tgz *.tmp

cleandir: clean
	-rm -f .depend

deinstall:
	-rm -rf dst site.tgz

reinstall: deinstall .WAIT install

all: ${OBJS}

CLEANFILES+=	getdate
getdate: ${TOP}/mk/getdate.c
	${LINK.c} ${COPTS} -I${TOP}/mk -DTEST -DIN_RCS -o $@ ${.ALLSRC}

site.tgz:
	-rm -rf dst $@
	mkdir dst dst/permalinks
	cp ${OBJS:Nstamp_*} dst/
.for _i in ${GENSRCS}
	pax -rw -pe -dv $$(<${_i}) dst/
.endfor
	cd ${TOP}/legacy && pax -rw -pe -v . ${DST}/dst/	# legacy
	cd ${TOP} && pax -rw -pe -v content ${DST}/dst/		# legacy
	cd ${TOP}/files && pax -rw -pe -v . ${DST}/dst/
	cd ${TOP} && pax -rw -pe -v pics ${DST}/dst/
	cd dst && rm -rf $$(find . -name CVS -o -name .cvsignore)
	chmod -R u=rwX,go=rX dst
	chmod a+x dst/cvs.cgi
	find dst | sort | sed -e '/^dst$$/d' -e 's,^dst/,,' | \
	    (cd dst && cpio -voC512 -Hustar -Mdist) | gzip -n9 >$@.tmp
	mv $@.tmp $@

.SUFFIXES: .htm .hts

.hts.htm:
	@rm -f $@{,.tmp}
	@print '( . mk/htsconv; . $< ) >$@'
	@(export ${U_ENV}; cd ${DST}; . ${TOP}/mk/htsconv; . $<) >$@.tmp || \
	    (rm -f $@.tmp; exit 1)
	@mv -f $@.tmp $@

.PHONY: clean cleandir depend install deinstall reinstall cp-herc cp-heph rs-heph

cp-herc: site.tgz
	ssh hercs 'cd /var/www/oldsite; tar xzvf -' <site.tgz

cp-heph: site.tgz
	ssh hephaistos 'cd Web; tar xzvpf -' <site.tgz

rs-heph: site.tgz
	rsync -rxlztpgavPHK dst/ hephaistos:Web/

depend: .depend

.depend: ${TOP}/mk/mkdepend ${DEPSRCS}
	${U_ENV} ${MKSH} ${TOP}/mk/mkdepend ${DEPSRCS}

lazy: .PHONY
	make obj && make depend && make && make reinstall && exec make cp-heph

.include <bsd.obj.mk>
