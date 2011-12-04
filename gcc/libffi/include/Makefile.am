# $MirOS: gcc/libffi/include/Makefile.am,v 1.2 2005/04/26 17:29:40 tg Exp $
## Process this with automake to create Makefile.in

AUTOMAKE_OPTIONS=foreign

DISTCLEANFILES=ffitarget.h
EXTRA_DIST=ffi.h.in ffi_common.h

hackdir=$(includedir)

hack_DATA= ffi.h

toollibffidir = @tool_include_dir@/libffi
toollibffi_HEADERS = ffitarget.h

ffitarget.h: $(top_srcdir)/src/@TARGETDIR@/ffitarget.h
	cp $> $@
