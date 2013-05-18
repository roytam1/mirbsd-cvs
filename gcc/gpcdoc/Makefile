# $MirOS: gcc/gpcdoc/Makefile,v 1.4 2009/12/27 16:43:05 tg Exp $

MAN=		gpc.1 gpc-run.1

.PATH: ${.CURDIR}/../gcc/p/doc/en
.PATH: ${.CURDIR}/../gcc/p/doc/generated

# texinfo file generation
INFOFILES=	gpc.info gpcs.info gpcs-de.info gpc-hr.info gpcs-hr.info
HTMLFILES=	${INFOFILES:.info=.html}

# aiding the GNU Make-lang.in copied part
srcdir=		${.CURDIR}/../gcc
MAKEINFO=	makeinfo
MAKEINFOFLAGS=	--no-split --enable-encoding

# copied from gpc p/Make-lang.in {{{
GPC_GENERATED_TEXI=\
  $(srcdir)/p/doc/generated/version.texi \
  $(srcdir)/p/doc/generated/lang-options.texi \
  $(srcdir)/p/doc/generated/keyword.texi \
  $(srcdir)/p/doc/generated/gpcpas.texi \
  $(srcdir)/p/doc/generated/crt.texi \
  $(srcdir)/p/doc/generated/dos.texi \
  $(srcdir)/p/doc/generated/dosunix.texi \
  $(srcdir)/p/doc/generated/fileutils.texi \
  $(srcdir)/p/doc/generated/gmp.texi \
  $(srcdir)/p/doc/generated/gpcutil.texi \
  $(srcdir)/p/doc/generated/heapmon.texi \
  $(srcdir)/p/doc/generated/intl.texi \
  $(srcdir)/p/doc/generated/md5.texi \
  $(srcdir)/p/doc/generated/overlay.texi \
  $(srcdir)/p/doc/generated/pipes.texi \
  $(srcdir)/p/doc/generated/ports.texi \
  $(srcdir)/p/doc/generated/printer.texi \
  $(srcdir)/p/doc/generated/regex.texi \
  $(srcdir)/p/doc/generated/strings.texi \
  $(srcdir)/p/doc/generated/stringutils.texi \
  $(srcdir)/p/doc/generated/system.texi \
  $(srcdir)/p/doc/generated/tfdd.texi \
  $(srcdir)/p/doc/generated/trap.texi \
  $(srcdir)/p/doc/generated/turbo3.texi \
  $(srcdir)/p/doc/generated/windos.texi

GPC_COMMON_TEXI=\
  $(srcdir)/p/doc/macros.texi \
  $(srcdir)/p/doc/contributors.texi \
  $(GPC_GENERATED_TEXI)

GPC_TEXI_EN=\
  $(GPC_COMMON_TEXI) \
  $(srcdir)/p/doc/en/gpc.texi \
  $(srcdir)/p/doc/en/welcome.texi \
  $(srcdir)/p/doc/en/purpose.texi \
  $(srcdir)/p/doc/en/about.texi \
  $(srcdir)/p/doc/en/news.texi \
  $(srcdir)/p/doc/en/faq.texi \
  $(srcdir)/p/doc/en/libs.texi \
  $(srcdir)/p/doc/en/install.texi \
  $(srcdir)/p/doc/en/bpqstart.texi \
  $(srcdir)/p/doc/en/invoke.texi \
  $(srcdir)/p/doc/en/programming.texi \
  $(srcdir)/p/doc/en/reference.texi \
  $(srcdir)/p/doc/en/keywords.texi \
  $(srcdir)/p/doc/en/support.texi \
  $(srcdir)/p/doc/en/todo.texi \
  $(srcdir)/p/doc/en/internals.texi \
  $(srcdir)/p/doc/en/resources.texi \
  $(srcdir)/p/doc/en/authors.texi \
  $(srcdir)/p/doc/en/copying.texi \
  $(srcdir)/p/doc/en/copying-lib.texi \
  $(srcdir)/p/doc/en/copying-demo.texi \
  $(srcdir)/p/doc/en/gnu.texi \
  $(srcdir)/p/doc/en/gpcs.texi

GPC_TEXI_DE=\
  $(GPC_COMMON_TEXI) \
  $(srcdir)/p/doc/de/gpcs.texi

# @@ Some files are not translated yet -- use the English versions for now
GPC_TEXI_HR=\
  $(GPC_COMMON_TEXI) \
  $(srcdir)/p/doc/hr/gpc.texi \
  $(srcdir)/p/doc/hr/welcome.texi \
  $(srcdir)/p/doc/hr/purpose.texi \
  $(srcdir)/p/doc/hr/about.texi \
  $(srcdir)/p/doc/en/news.texi \
  $(srcdir)/p/doc/hr/faq.texi \
  $(srcdir)/p/doc/hr/libs.texi \
  $(srcdir)/p/doc/en/install.texi \
  $(srcdir)/p/doc/en/bpqstart.texi \
  $(srcdir)/p/doc/hr/invoke.texi \
  $(srcdir)/p/doc/en/programming.texi \
  $(srcdir)/p/doc/en/reference.texi \
  $(srcdir)/p/doc/hr/keywords.texi \
  $(srcdir)/p/doc/hr/support.texi \
  $(srcdir)/p/doc/en/todo.texi \
  $(srcdir)/p/doc/en/internals.texi \
  $(srcdir)/p/doc/hr/resources.texi \
  $(srcdir)/p/doc/hr/authors.texi \
  $(srcdir)/p/doc/en/copying.texi \
  $(srcdir)/p/doc/en/copying-lib.texi \
  $(srcdir)/p/doc/en/copying-demo.texi \
  $(srcdir)/p/doc/en/gnu.texi \
  $(srcdir)/p/doc/hr/gpcs.texi

GPC_DOC_DIRS_EN=-I $(srcdir)/p/doc -I $(srcdir)/p/doc/en -I $(srcdir)/p/doc/generated
GPC_DOC_DIRS_DE=-I $(srcdir)/p/doc -I $(srcdir)/p/doc/de -I $(srcdir)/p/doc/generated
GPC_DOC_DIRS_HR=-I $(srcdir)/p/doc -I $(srcdir)/p/doc/hr -I $(srcdir)/p/doc/generated -I $(srcdir)/p/doc/en
MAKEINFO_EN=LANG=en_GB LC_ALL=en_GB $(MAKEINFO) $(MAKEINFOFLAGS) $(GPC_DOC_DIRS_EN)
MAKEINFO_DE=LANG=de_DE LC_ALL=de_DE $(MAKEINFO) $(MAKEINFOFLAGS) $(GPC_DOC_DIRS_DE)
MAKEINFO_HR=LANG=hr_HR LC_ALL=hr_HR $(MAKEINFO) $(MAKEINFOFLAGS) $(GPC_DOC_DIRS_HR)
# copied from gpc p/Make-lang.in }}}

# adapted from gpc p/Make-lang.in
gpc.info: $(GPC_TEXI_EN)
	$(MAKEINFO_EN) -o $@ gpc.texi

gpcs.info: $(GPC_TEXI_EN)
	$(MAKEINFO_EN) -o $@ gpcs.texi

gpcs-de.info: $(GPC_TEXI_DE)
	$(MAKEINFO_DE) -o $@ gpcs.texi

gpc-hr.info: $(GPC_TEXI_HR)
	$(MAKEINFO_HR) -o $@ gpc.texi

gpcs-hr.info: $(GPC_TEXI_HR)
	$(MAKEINFO_HR) -o $@ gpcs.texi

# and once again, for HTML output
gpc.html: $(GPC_TEXI_EN)
	$(MAKEINFO_EN) --html -o $@ gpc.texi

gpcs.html: $(GPC_TEXI_EN)
	$(MAKEINFO_EN) --html -o $@ gpcs.texi

gpcs-de.html: $(GPC_TEXI_DE)
	$(MAKEINFO_DE) --html -o $@ gpcs.texi

gpc-hr.html: $(GPC_TEXI_HR)
	$(MAKEINFO_HR) --html -o $@ gpc.texi

gpcs-hr.html: $(GPC_TEXI_HR)
	$(MAKEINFO_HR) --html -o $@ gpcs.texi

all: ${INFOFILES} ${HTMLFILES}
CLEANFILES+=	${INFOFILES} ${HTMLFILES}

afterinstall:
.for _i in ${INFOFILES}
	${INSTALL} ${INSTALL_COPY} -o ${MANOWN} -g ${MANGRP} -m ${MANMODE} \
	    ${_i} ${DESTDIR}${GCC_INFODIR}/
.endfor

.include <bsd.prog.mk>
