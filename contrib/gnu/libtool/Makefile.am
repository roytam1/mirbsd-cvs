## Process this file with automake to produce Makefile.in
# $MirOS$

AUTOMAKE_OPTIONS = 1.3e gnu

BUILD_SUBDIRS = .
CONF_SUBDIRS = @CONF_SUBDIRS@
SUBDIRS = $(BUILD_SUBDIRS)
DIST_SUBDIRS = $(BUILD_SUBDIRS) $(CONF_SUBDIRS)

# We need to export these variables
CFLAGS = @CFLAGS@
CPPLAGS = @CPPFLAGS@
LDFLAGS = @LDFLAGS@
LIBS= @LIBS@
FFLAGS = @FFLAGS@
FLIBS = @FLIBS@

aclocal_macros = libtool.m4

EXTRA_DIST = $(aclocal_macros) bootstrap libtoolize.in ltmain.in
CLEANFILES = libtool libtoolize ltmain.shT

# These are required by libtoolize and must be executable when installed.
# Since _SCRIPTS gets the program transform applied we make them
# executable by hand
pkgdata_DATA = config.guess config.sub ltmain.sh

# The standalone libtool script, and the libtool distributor.
bin_SCRIPTS = libtool libtoolize

libtool: $(srcdir)/ltmain.sh $(top_builddir)/configure.ac
	$(SHELL) $(top_builddir)/config.status --recheck
	chmod +x $@

libtoolize: $(srcdir)/libtoolize.in $(top_builddir)/config.status
	CONFIG_FILES=$@ CONFIG_HEADERS= $(SHELL) $(top_builddir)/config.status
	chmod +x $@

$(srcdir)/ltmain.sh: $(srcdir)/ltmain.in $(TSDEPS)
	-rm -f ltmain.shT
	date=" (MirLibtool-1.5 $$(date '+%Y/%m/%d %H:%M:%S'))" && \
	sed -e 's/@''PACKAGE@/@PACKAGE@/' -e 's/@''VERSION@/@VERSION@/' \
	    -e "s%@""TIMESTAMP@%$$date%" $(srcdir)/ltmain.in > ltmain.shT
	mv -f ltmain.shT $@ || \
	(rm -f $@ && cp ltmain.shT $@ && rm -f ltmain.shT)

# All our rules should depend on these demo files.
all-recursive: $(ACINCLUDE_M4_LIST)

@ACINCLUDE_M4_LIST@: $(srcdir)/libtool.m4
	-rm -f $@ $@T
	cat $(srcdir)/libtool.m4 > $@T
	mv $@T $@
