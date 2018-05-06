# $MirOS: www/Makefile,v 1.118 2018/05/05 17:40:23 tg Exp $
#-
# This file is part of the MirBSD website; see LICENCE for details.

.ifndef TOP
TOP!=		realpath ${.CURDIR:Q}
DST!=		realpath ${.OBJDIR:Q}
.MAKEFLAGS:=	${.MAKEFLAGS} TOP=${TOP:Q} DST=${DST:Q}
.endif

all:

.include <bsd.own.mk>
BSDSRCDIR?=/nonexistant
.if exists(${DST}/.depend)
.  include "${DST}/.depend"
.endif

U_ENV+=		TOP=${TOP:Q} DST=${DST:Q} MKSH=${MKSH:Q} SHELL=${MKSH:Q} TZ=UTC

SRCS+=		FreeWRT.hts
SRCS+=		a4rcontrb.hts a4rp5bsd.hts
SRCS+=		about.hts
SRCS+=		anargeek.hts
SRCS+=		ann-10.hts
SRCS+=		bt.hts
SRCS+=		clog11.hts
SRCS+=		danke.hts
SRCS+=		devel.hts
SRCS+=		errata10.hts
SRCS+=		getting.hts
SRCS+=		imprint.hts
SRCS+=		irc.hts
SRCS+=		jupp.hts
SRCS+=		ksh-chan.hts
SRCS+=		kwalletcli.hts
SRCS+=		main.hts
SRCS+=		makefs.hts
SRCS+=		man.hts
SRCS+=		mksh-faq.hts
SRCS+=		mksh.hts mksh_bld.hts mksh_old.hts
SRCS+=		oldnews.hts
SRCS+=		pax.hts
SRCS+=		pkgsrc.hts
SRCS+=		ports.hts
SRCS+=		projects.hts
SRCS+=		randex.hts
SRCS+=		rss.hts
SRCS+=		tags.hts
SRCS+=		wptg.hts
SRCS+=		wtf.hts
CLEANFILES+=	tags.lst tags.out
TAGCLOUD+=	debian
TAGCLOUD+=	event
TAGCLOUD+=	geocache
TAGCLOUD+=	mksh
TAGCLOUD+=	pcli
USELINKED+=	acronyms
WLOGS=		-9 -10
WPS=		tg

# legacy content
SRCS+=		ann-7.hts ann-8.hts anoncvs.hts bsd-intro.hts clog-2004.hts \
		clog-2005.hts clog-2006.hts cvsweb.hts docs.hts errata8.hts \
		faq.es.hts faq.hts history.hts ipv6-sixxs.hts \
		isdn.hts mirrors.hts mirwarum.hts
SRCS+=		wlog-0.hts wlog-1.hts wlog-2.hts wlog-3.hts wlog-4.hts \
		wlog-5.hts wlog-6.hts wlog-7.hts wlog-8.hts

INCSRCS+=	datatest

INCSRCS+=	news
news.cut: stamp_htm_news
CLEANFILES+=	news.cut

.PATH: ${TOP}/src

_htm_2xhtml=	(tr '\n' '﷐' | \
		sed 's^.*<html'${_xhtmlbeg:Q}'' | \
		tr '﷐' '\n')
_xhtmldtd=	${TOP}/files/xhtml11.dtd
_xhtmlbeg=	<?xml version="1.0"?> \
		<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" \
		 "file://${_xhtmldtd}"> \
		<html

all:
install: site.tgz.stamp

FPSRCS+=	${SRCS:S,^,src/,}

OBJS+=		${FPSRCS:T:M*.hts:S/hts$/htm~/}
VOBJS+=		${FPSRCS:T:M*.hts:S/hts$/val/}
CLEANFILES+=	${FPSRCS:T:M*.hts:S/hts$/htm~/}

DEPSRCS+=	${FPSRCS}
INCSRCS+=	${WLOGS:S/^/wlog/}
INCSRCS+=	${TAGCLOUD:S/^/tag_/}

.for _i in ${INCSRCS}
DEPSRCS+=	data/${_i}.cfg
GENSRCS+=	stamp_htm_${_i} stamp_rss_${_i}
CLEANFILES+=	stamp_tag_${_i}

stamp_htm_${_i}: ${DEPS_mk_inc2htm} ${DEPS_data_${_i}_cfg}
	${U_ENV} ${MKSH} ${TOP}/mk/inc2htm ${_i} >$@~
	mv $@~ $@

stamp_rss_${_i}: ${DEPS_mk_inc2rss} ${DEPS_data_${_i}_cfg}
	${U_ENV} PATH=.:$$PATH ${MKSH} ${TOP}/mk/inc2rss ${_i} >$@~
	mv $@~ $@
.endfor

DEPSRCS+=	mk/WPmk
.for _i in ${WPS}
DEPSRCS+=	data/${_i}.gc
GENSRCS+=	stamp_wp_${_i}

stamp_wp_${_i}: ${DEPS_mk_WPmk} ${DEPS_data_${_i}_gc}
	${U_ENV} ${MKSH} ${TOP}/mk/WPmk ${_i} >$@~
	mv $@~ $@
.endfor

DEPSRCS+=	mk/inc2htm mk/inc2rss
OBJS+=		${GENSRCS}
CLEANFILES+=	${GENSRCS}

OBJS+=		acronyms.gz acronyms.ver
CLEANFILES+=	acronyms.gz acronyms.ver

acronyms.gz: ${TOP}/.linked/acronyms
	gzip -n9 <${.ALLSRC:Q} >$@~
	mv $@~ $@

acronyms.ver: ${TOP}/.linked/acronyms
	sed -n '2s/^ ....//p' <${.ALLSRC:Q} >$@~
	mv $@~ $@

clean:
.for _i in ${GENSRCS}
	-rm -rf $$(<${_i})
.endfor
	-rm -rf dst permalinks
	-rm -f ${CLEANFILES} site.tgz* *.tmp *~

cleandir: clean
	-rm -rf hashed
	-rm -f .depend ${CLEANFILES:M*~:S/~$//}

deinstall:
	-rm -rf dst site.tgz*

reinstall: deinstall .WAIT install

all: ${OBJS}

site.tgz.stamp: _reinstall
#	find dst | sort | sed -e '/^dst$$/d' -e 's,^dst/,,' | \
#	    (cd dst && cpio -ovC512 -Hustar -Mdist) | gzip -n9 >site.tgz.tmp
#	mv site.tgz.tmp site.tgz
	:>$@

.for _i in ${WLOGS}
WLOG_LATEST:=${_i}
.endfor

_reinstall:
	-rm -rf dst
	mkdir dst dst/permalinks
	ln -s ../LICENCE dst/permalinks/
	pax -rw -pe -v hashed dst/
	pax -rw -pe -v -d ${OBJS:Nstamp_*:S/htm~$/htm/} dst/
.for _i in ${GENSRCS}
	[[ -s ${_i} ]]
	pax -rw -pe -v -d $$(<${_i}) dst/
.endfor
	cd ${TOP}/.linked && pax -rw -pe -v ${USELINKED} ${DST}/dst/
	cd ${TOP}/files && pax -rw -pe -v . ${DST}/dst/
	print '/MirOS:/s!www/files/MirOS-Licence.asc,v!src/share/misc/licence.template,v!\nwq' | \
	    ed -s ${DST}/dst/MirOS-Licence.asc
	touch -r ${TOP}/files/MirOS-Licence.asc ${DST}/dst/MirOS-Licence.asc
	cd ${TOP} && pax -rw -pe -v pics ${DST}/dst/
	cd dst && \
	    ln -sf wlog${WLOG_LATEST}.htm wlog.htm && \
	    ln -sf wlog${WLOG_LATEST}.rss wlog.rss && \
	    rm -rf $$(find . -name CVS -o -name .cvsignore)
	chgrp -R miros-cvswww dst
	chmod -R ug=rwX,o=rX dst
	chmod a+x dst/cvs.cgi dst/man.cgi dst/raw.cgi dst/wp.cgi dst/wtf.cgi

.SUFFIXES: .val .htm~ .hts

.hts.htm~:
	@dstd='$@'; dstf=$${dstd%\~}; rm -f $@; \
	 print -r "(. mk/htsconv; mws_basepath $$dstf; mws__do $<) >$$dstf"; \
	 export ${U_ENV}; if (cd ${DST}; . ${TOP}/mk/htsconv; \
	    mws_basepath $$dstf; mws__do $<) >$@; then \
		(. ${TOP}/mk/htsconv; mws_moveifchange -k $$dstd $$dstf); \
	 else \
		rm -f $@; \
		exit 1; \
	fi

.htm~.val:
	@print -r Creating ${@:Q} from ${<:Q} ...
	@${_htm_2xhtml} <$< >$@

.for _i in ${WPS}
WP${_i}.val: stamp_wp_${_i}
	@${_htm_2xhtml} <WP${_i}.htm >$@
.endfor

.ifdef validate
VOBJS:=		${validate:=.val}

HTM_FILES!=	cd ${.CURDIR}/files; echo *.htm
.  for _i in ${HTM_FILES}
${_i:R}.val: files/${_i}
	@print -r Creating ${@:Q} from ${.ALLSRC:Q} ...
	@${_htm_2xhtml} <${.ALLSRC} >$@
.  endfor

.MAIN: validation
.endif

validation: .PHONY ${VOBJS}
	@print -r Validating ${.ALLSRC:Q} ...
	@xmlstarlet val -d ${_xhtmldtd} -e ${.ALLSRC}
	@print '\nValidation complete.'

.PHONY: clean cleandir depend install deinstall reinstall _reinstall \
	cp-herc rs-gecko2 rs-fish

#cp-herc: site.tgz.stamp
#	ssh hercs 'cd /var/www/oldsite; tar xzvf -' <site.tgz

rs-gecko2:
	rsync -rxlztpgavPHK dst/ tglaser@www.ig42.org:/var/www/miros.unixforge.de/htdocs/

rs-fish:
	@if [[ $$(hostname) = fish.mirbsd.org ]]; then hn=; else hn=fish:; fi; \
	 set -x; rsync -rxlztpgavPHK --rsh='ssh -4' dst/ $${hn}/var/anoncvs/www/

depend: .depend

.depend: ${TOP}/mk/mkdepend ${DEPSRCS} ${.CURDIR}/Makefile
	-rm -f $@
	${U_ENV} ${MKSH} ${TOP}/mk/mkdepend ${DEPSRCS}

lazy: .PHONY
	cd ${.CURDIR} && make depend && make && \
	    make _reinstall && exec make rs-fish rs-gecko2 tagslst

tagslst: .PHONY
	@(echo === TAGS USED/UNUSED/ACCOUNTED FOR ==; cat stamp_tag_* | \
	    sort -u | comm - tags.out) | tee tags.lst

.include <bsd.obj.mk>
