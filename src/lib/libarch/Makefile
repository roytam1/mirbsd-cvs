# $MirOS$

.if exists(${MACHINE})
  SUBDIR+= ${MACHINE}
.elif exists(${MACHINE_ARCH})
  SUBDIR+= ${MACHINE_ARCH}
.endif

.include <bsd.subdir.mk>
