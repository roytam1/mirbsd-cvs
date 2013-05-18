# $MirOS$

.include <bsd.own.mk>

.if ${OBJECT_FMT} == "ELF" && exists(${MACHINE}_elf)
  SUBDIR+= ${MACHINE}_elf
.elif ${OBJECT_FMT} == "ELF" && exists(${MACHINE_ARCH}_elf)
  SUBDIR+= ${MACHINE_ARCH}_elf
.elif exists(${MACHINE})
  SUBDIR+= ${MACHINE}
.elif exists(${MACHINE_ARCH})
  SUBDIR+= ${MACHINE_ARCH}
.else
.BEGIN:
	@echo no SUBDIR for ${MACHINE} / ${MACHINE_ARCH} nor \
	    ${MACHINE}_elf / ${MACHINE_ARCH}_elf
	@false
.endif

.include <bsd.subdir.mk>
