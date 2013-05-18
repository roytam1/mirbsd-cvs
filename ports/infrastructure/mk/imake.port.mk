# $MirOS: ports/infrastructure/mk/imake.port.mk,v 1.10 2008/10/04 18:37:32 tg Exp $
# $OpenBSD: imake.port.mk,v 1.3 2003/07/28 17:17:05 sturm Exp $

# XXX
#PREFIX=/usr/local

.if empty(CONFIGURE_STYLE:L:Mnoman)
INSTALL_TARGET+=	install.man
.endif

XMKMF?=			xmkmf -a
XMKMF+=			-DPorts
EXTRA_XAKE_FLAGS+=	CC=${_PASS_CC:T:Q} COPTS=${COPTS:Q} CPPFLAGS=${CPPFLAGS:Q}

.if ${USE_X11:L} != "yes"
IGNORE=			"uses imake, but USE_X11 not set"
.endif

.if !exists(${X11BASE})
IGNORE=			"uses imake, but ${X11BASE} not found"
.endif

MODIMAKE_configure= \
	if [ -e ${X11BASE}/lib/X11/config/ports.cf ] || \
		fgrep >/dev/null 2>/dev/null Ports \
			${X11BASE}/lib/X11/config/OpenBSD.cf; then \
		cd ${WRKSRC} && ${_SYSTRACE_CMD} ${SETENV} ${MAKE_ENV} ${XMKMF}; \
	else \
		echo >&2 "Error: your X installation is not recent enough"; \
		echo >&2 "Update to a more recent version, or use a ports tree"; \
		echo >&2 "that predates March 18, 2000"; \
		exit 1; \
	fi

# Kludge
.if ${CONFIGURE_STYLE:Mimake}
MODIMAKE_pre_install= \
	${SUDO} mkdir -p /usr/local/lib/X11; \
	if [ ! -e /usr/local/lib/X11/app-defaults ]; then \
		${SUDO} ln -sf /etc/X11/app-defaults /usr/local/lib/X11/app-defaults; \
	fi
.endif
