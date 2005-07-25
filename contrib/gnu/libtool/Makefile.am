## Process this file with automake to produce Makefile.in
# $MirOS: contrib/gnu/libtool/Makefile.am,v 1.5 2005/02/10 21:07:45 tg Exp $

AUTOMAKE_OPTIONS = 1.3e gnu

aclocal_macros = libtool.m4

EXTRA_DIST = $(aclocal_macros) ltmain.in
CLEANFILES = libtool ltmain.shT
bin_SCRIPTS = libtool

libtool: $(srcdir)/ltmain.sh $(top_builddir)/configure.ac
	$(SHELL) $(top_builddir)/config.status --recheck
	chmod +x $@

ltmain.sh: $(srcdir)/ltmain.in
	-rm -f ltmain.shT
	date=" (MirLibtool $$(date +'%Y/%m/%d %H:%M:%S'))" && \
	sed -e 's/@''PACKAGE@/@PACKAGE@/' -e 's/@''VERSION@/@VERSION@/' \
	    -e "s%@""TIMESTAMP@%$$date%" $(srcdir)/ltmain.in > ltmain.shT
	mv -f ltmain.shT $@ || \
	(rm -f $@ && cp ltmain.shT $@ && rm -f ltmain.shT)
