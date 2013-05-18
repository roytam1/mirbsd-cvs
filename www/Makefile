# $MirOS: www/Makefile,v 1.19 2008/02/22 21:49:30 tg Exp $
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

SRCS+=		danke.hts devel.hts
SRCS+=		getting.hts
SRCS+=		irc.hts
SRCS+=		jupp.hts
SRCS+=		main.hts
SRCS+=		mksh.hts mksh_old.hts
SRCS+=		projects.hts
WLOGS=		9

INCSRCS+=	news
news.cut: stamp_htm_news
CLEANFILES+=	news.cut

.PATH: ${TOP}/src

all:
install: site.tgz

OBJS+=		${SRCS:M*.hts:S/hts$/htm/}
CLEANFILES+=	${SRCS:M*.hts:S/hts$/htm/}

DEPSRCS+=	${SRCS:S,^,src/,}
INCSRCS+=	${WLOGS:S/^/wlog-/}

.for _i in ${INCSRCS}
GENSRCS+=	stamp_htm_${_i} stamp_rss_${_i}

stamp_htm_${_i}: getdate ${DEPS_mk_inc2htm} \
    ${TOP}/data/${_i}.inc ${TOP}/data/${_i}.cfg
	${U_ENV} ${MKSH} ${TOP}/mk/inc2htm ${_i} >$@

stamp_rss_${_i}: getdate ${DEPS_mk_inc2rss} \
    ${TOP}/data/${_i}.inc ${TOP}/data/${_i}.cfg
	${U_ENV} ${MKSH} ${TOP}/mk/inc2rss ${_i} >$@
.endfor
DEPSRCS+=	mk/inc2htm mk/inc2rss
OBJS+=		${GENSRCS}
CLEANFILES+=	${GENSRCS}

clean:
.for _i in ${GENSRCS}
	-rm -rf $$(<${_i})
.endfor
	-rm -rf dst permalinks
	-rm -f ${CLEANFILES} site.tgz *.tmp *~

cleandir: clean
	-rm -f .depend

deinstall:
	-rm -rf dst site.tgz

reinstall: deinstall .WAIT install

all: ${OBJS}

CLEANFILES+=	getdate
getdate: ${TOP}/mk/getdate.c ${TOP}/mk/getdate.h ${TOP}/mk/gettime.c
	${LINK.c} ${COPTS} -I${TOP}/mk -DTEST -DIN_RCS -o $@ ${.ALLSRC:N*.h}

site.tgz: _reinstall
	find dst | sort | sed -e '/^dst$$/d' -e 's,^dst/,,' | \
	    (cd dst && cpio -voC512 -Hustar -Mdist) | gzip -n9 >$@.tmp
	mv $@.tmp $@

_reinstall:
	-rm -rf dst
	mkdir dst dst/permalinks
	pax -rw -pe -dv ${OBJS:Nstamp_*} dst/
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

.SUFFIXES: .htm .hts

.hts.htm:
	@rm -f $@.tmp
	@print '( . mk/htsconv; . $< ) >$@'
	@(export ${U_ENV}; cd ${DST}; . ${TOP}/mk/htsconv; . $<) >$@.tmp || \
	    (rm -f $@.tmp; exit 1)
	@(. ${TOP}/mk/htsconv; mws_moveifchange $@.tmp $@)

.PHONY: clean cleandir depend install deinstall reinstall _reinstall \
	cp-herc cp-heph rs-heph

cp-herc: site.tgz
	ssh hercs 'cd /var/www/oldsite; tar xzvf -' <site.tgz

cp-heph: site.tgz
	ssh hephaistos 'cd Web; tar xzvpf -' <site.tgz

rs-heph:
	rsync -rxlztpgavPHK dst/ hephaistos:Web/

depend: .depend

.depend: ${TOP}/mk/mkdepend ${DEPSRCS}
	${U_ENV} ${MKSH} ${TOP}/mk/mkdepend ${DEPSRCS}

lazy: .PHONY
	cd ${.CURDIR} && make obj && make depend && \
	    make && make _reinstall && exec make rs-heph

.include <bsd.obj.mk>
