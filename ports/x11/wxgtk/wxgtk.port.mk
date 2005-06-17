# $MirOS$

USE_CXX=		Yes

LIB_DEPENDS+=		wx_gtk_MirPorts-2.6.0.0::x11/wxgtk

# from Makefile
LIB_DEPENDS+=		gdk.,gtk.::x11/gtk+1 \
			glib.,gmodule.,gthread.::devel/glib1 \
			jpeg.62::graphics/jpeg \
			png.2::graphics/png \
			tiff.35::graphics/tiff \
			expat::textproc/expat
