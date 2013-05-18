# $MirOS: www/Makefile,v 1.79 2012/05/15 20:10:09 tg Exp $
#-
# This file is part of the website of The MirOS Project, which is
# copyrighted material, please read the LICENCE file for details.

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
SRCS+=		mksh.hts mksh_bld.hts mksh_old.hts
SRCS+=		oldnews.hts
SRCS+=		pkgsrc.hts
SRCS+=		ports.hts
SRCS+=		projects.hts
SRCS+=		randex.hts
SRCS+=		rss.hts
SRCS+=		tags.hts
SRCS+=		wtf.hts
CLEANFILES+=	tags.lst tags.out
TAGCLOUD+=	debian
TAGCLOUD+=	mksh
TAGCLOUD+=	pcli
USELINKED+=	acronyms
WLOGS=		9 10

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
_xhtmldtd=	${TOP}/mk/xhtml11.dtd
_xhtmlbeg=	<?xml version="1.0"?> \
		<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" \
		 "file://${_xhtmldtd}"> \
		<html

all:
install: site.tgz.stamp

STRFTM_MAKE=	cd ${.CURDIR:Q} && ${MAKE} -f ${.SYSMK}/bsd.prog.mk NOMAN=Yes \
		    VPATH=${.CURDIR:Q}/mk PROG=strftm

OBJS+=		${SRCS:M*.hts:S/hts$/htm~/}
VOBJS+=		${SRCS:M*.hts:S/hts$/val/}
CLEANFILES+=	${SRCS:M*.hts:S/hts$/htm~/}

DEPSRCS+=	${SRCS:S,^,src/,}
INCSRCS+=	${WLOGS:S/^/wlog-/}
INCSRCS+=	${TAGCLOUD:S/^/tag_/}

.for _i in ${INCSRCS}
DEPSRCS+=	data/${_i}.cfg
GENSRCS+=	stamp_htm_${_i} stamp_rss_${_i}
CLEANFILES+=	stamp_tag_${_i}

stamp_htm_${_i}: ${DEPS_mk_inc2htm} ${DEPS_data_${_i}_cfg}
	${U_ENV} ${MKSH} ${TOP}/mk/inc2htm ${_i} >$@ || (rm -f $@; exit 1)

stamp_rss_${_i}: ${DEPS_mk_inc2rss} strftm ${DEPS_data_${_i}_cfg}
	${U_ENV} PATH=.:$$PATH ${MKSH} ${TOP}/mk/inc2rss ${_i} >$@ || \
	    (rm -f $@; exit 1)
.endfor

DEPSRCS+=	mk/inc2htm mk/inc2rss
OBJS+=		${GENSRCS}
CLEANFILES+=	${GENSRCS}

clean:
	-${STRFTM_MAKE} clean
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

strftm: mk/strftm.c
	${STRFTM_MAKE} $@

site.tgz.stamp: _reinstall
#	find dst | sort | sed -e '/^dst$$/d' -e 's,^dst/,,' | \
#	    (cd dst && cpio -voC512 -Hustar -Mdist) | gzip -n9 >site.tgz.tmp
#	mv site.tgz.tmp site.tgz
	:>$@

.for _i in ${WLOGS}
WLOG_LATEST:=${_i}
.endfor

_reinstall:
	-rm -rf dst
	mkdir dst dst/permalinks
	pax -rw -pe -v hashed dst/
	pax -rw -pe -dv ${OBJS:Nstamp_*:S/htm~$/htm/} dst/
.for _i in ${GENSRCS}
	pax -rw -pe -dv $$(<${_i}) dst/
.endfor
	cd ${TOP}/.linked && pax -rw -pe -v ${USELINKED} ${DST}/dst/
	cd ${TOP}/files && pax -rw -pe -v . ${DST}/dst/
	cd ${TOP} && pax -rw -pe -v pics ${DST}/dst/
	cd dst && \
	    ln -sf wlog-${WLOG_LATEST}.htm wlog.htm && \
	    ln -sf wlog-${WLOG_LATEST}.rss wlog.rss && \
	    rm -rf $$(find . -name CVS -o -name .cvsignore)
	chgrp -R miros-cvswww dst
	chmod -R ug=rwX,o=rX dst
	chmod a+x dst/cvs.cgi dst/wtf.cgi

.SUFFIXES: .val .htm~ .hts

.hts.htm~:
	@dstd='$@'; dstf=$${dstd%~}; rm -f $@; \
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

.ifdef validate
VOBJS:=		${validate:=.val}

.MAIN: validation
.endif

validation: .PHONY ${VOBJS}
	@print -r Validating ${.ALLSRC:Q} ...
	@xmlstarlet val -d ${_xhtmldtd} ${.ALLSRC}
	@print '\nValidation complete.'

.PHONY: clean cleandir depend install deinstall reinstall _reinstall \
	cp-herc cp-heph rs-heph rs-eurynome rs-pfau

#cp-herc: site.tgz.stamp
#	ssh hercs 'cd /var/www/oldsite; tar xzvf -' <site.tgz
#
#cp-heph: site.tgz.stamp
#	ssh hephaistos 'cd Web; tar xzvpf -' <site.tgz

rs-heph:
	rsync -rxlztpgavPHK dst/ hephaistos:Web/

rs-eurynome:
	rsync -rxlztpgavPHK --rsh='ssh -4' dst/ eurynome:/var/anoncvs/anoncvs/www/

rs-pfau:
	rsync -rxlztpgavPHK --rsh='ssh -4' dst/ pfau:/Web/

depend: .depend

.depend: ${TOP}/mk/mkdepend ${DEPSRCS}
	-rm -f $@
	${STRFTM_MAKE} depend
	${U_ENV} ${MKSH} ${TOP}/mk/mkdepend ${DEPSRCS}

lazy: .PHONY
	cd ${.CURDIR} && make depend && make && \
	    make _reinstall && exec make rs-eurynome rs-heph rs-pfau tagslst

tagslst: .PHONY
	@(echo === TAGS USED/UNUSED/ACCOUNTED FOR ==; cat stamp_tag_* | \
	    sort -u | comm - tags.out) | tee tags.lst

.include <bsd.obj.mk>
