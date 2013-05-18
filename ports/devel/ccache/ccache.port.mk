CCACHE_DEPENDS?=	::devel/ccache
BUILD_DEPENDS+=		${CCACHE_DEPENDS}
CCACHE_DIR?=		${HOME}/.etc/ccache

MAKE_ENV+=		CCACHE_DIR=${CCACHE_DIR:Q}
CONFIGURE_ENV+=		CCACHE_DIR=${CCACHE_DIR:Q}

#CC:=			env CCACHE_DIR=${CCACHE_DIR:Q} ccache ${CC}
#.  if ${NO_CXX:L} == "no"
#CXX:=			env CCACHE_DIR=${CCACHE_DIR:Q} ccache ${CXX}
#.  endif

MODDEVEL/CCACHE_post-patch= ln -s ${LOCALBASE}/bin/ccache ${WRKDIR}/bin/${CC:T}
.if ${NO_CXX:L} == "no"
MODDEVEL/CCACHE_post-patch+= \
	ln -s ${LOCALBASE}/bin/ccache ${WRKDIR}/bin/${CXX:T}
.endif
