# $MirOS: www/Makefile,v 1.25 2008/03/22 20:38:16 tg Exp $
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

SRCS+=		ann-10.hts
SRCS+=		bt.hts
SRCS+=		clog11.hts
SRCS+=		danke.hts
SRCS+=		devel.hts
SRCS+=		errata10.hts
SRCS+=		getting.hts
SRCS+=		irc.hts
SRCS+=		jupp.hts
SRCS+=		main.hts
SRCS+=		mksh.hts mksh_old.hts
SRCS+=		oldnews.hts
SRCS+=		ports.hts
SRCS+=		projects.hts
WLOGS=		9 10

INCSRCS+=	news
news.cut: stamp_htm_news
CLEANFILES+=	news.cut

.PATH: ${TOP}/src

all:
install: site.tgz

OBJS+=		${SRCS:M*.hts:S/hts$/htm~/}
CLEANFILES+=	${SRCS:M*.hts:S/hts$/htm~/}

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

.for _i in ${WLOGS}
WLOG_LATEST:=${_i}
.endfor

_reinstall:
	-rm -rf dst
	mkdir dst dst/permalinks
	pax -rw -pe -dv ${OBJS:Nstamp_*:S/htm~$/htm/} dst/
.for _i in ${GENSRCS}
	pax -rw -pe -dv $$(<${_i}) dst/
.endfor
	cd ${TOP}/legacy && pax -rw -pe -v . ${DST}/dst/	# legacy
	cd ${TOP} && pax -rw -pe -v content ${DST}/dst/		# legacy
	cd ${TOP}/files && pax -rw -pe -v . ${DST}/dst/
	cd ${TOP} && pax -rw -pe -v pics ${DST}/dst/
	cd dst && \
	    ln -sf wlog-${WLOG_LATEST}.rss wlog.rss && \
	    rm -rf $$(find . -name CVS -o -name .cvsignore)
	chmod -R u=rwX,go=rX dst
	chmod a+x dst/cvs.cgi

.SUFFIXES: .htm~ .hts

.hts.htm~:
	@dstd='$@'; dstf=$${dstd%~}; rm -f $@; \
	 print '( . mk/htsconv; . $< ) >'$$dstf; \
	 if (export ${U_ENV}; cd ${DST}; . ${TOP}/mk/htsconv; . $<) \
	    >$@; then \
		(. ${TOP}/mk/htsconv; mws_moveifchange -k $$dstd $$dstf); \
	 else \
		rm -f $@; \
		exit 1; \
	fi

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
