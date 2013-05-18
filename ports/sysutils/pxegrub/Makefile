# $MirOS: ports/sysutils/pxegrub/Makefile,v 1.9 2006/02/09 11:15:27 tg Exp $
#
# Although you can only netboot a kernel with this, it's still included.
# Maybe one day someone will include the correct parametres for disc kernels.
#
# Loading Linux kernels works and has been tested.
#
# PXE booting does not use UNDI network drivers. You can also boot ramdisk
# kernels (BSD) and foreign (Linux, HURD) kernels from a fixed disc with this.

.include <mirports.sys.mk>

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=		"GNU GRUB with support for booting bsd.rd and netboot"
DISTNAME=       	grub-0.96
PKGNAME=		${DISTNAME}-1
CATEGORIES=		sysutils
MASTER_SITES=		ftp://alpha.gnu.org/gnu/grub/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
HOMEPAGE=		http://www.gnu.org/software/grub/ \
			http://www.berger.to/openbsd/pxegrub.html

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	gnu
USE_GMAKE=		Yes
NO_REGRESS=		Yes
CONFIGURE_ARGS+=	--disable-dependency-tracking

GCC_VERSION!=		${CC} -v 2>&1 | fgrep "cc version" | sed 's!^.*cc version \([0-9\.]*\).*$!\1!'
DEBUGLIBS=		no		# -g breaks (ICE)
CPPFLAGS+=		-D_MIRMAKE_H	# do not include in freestanding code
COPTS+=			-fno-stack-protector
.if ${OStype} == "MirBSD"
.if ${GCC_VERSION:M3.4*}
COPTS+=			-ftrampolines
.endif
.elif ${OStype} == "OpenBSD"
.if ${GCC_VERSION:M3.3*}
COPTS+=			-ftrampolines
.endif
.endif

FILES=			stage1/stage1 stage2/e2fs_stage1_5 \
			stage2/fat_stage1_5 stage2/ffs_stage1_5 \
			stage2/iso9660_stage1_5 stage2/jfs_stage1_5 \
			stage2/minix_stage1_5 stage2/nbgrub stage2/pxegrub \
			stage2/reiserfs_stage1_5 stage2/stage2 \
			stage2/stage2_eltorito stage2/ufs2_stage1_5 \
			stage2/vstafs_stage1_5 stage2/xfs_stage1_5

FLAVORS=		x3c503 x3c503_aui x3c503_shmem x3c507 x3c509 x3c529 \
			x3c595 x3c90x cs89x0 davicom depca eepro eepro100 \
			epic100 exos205 lance natsemi ne ne2100 ni5010 \
			ni5210 ni6510 ns8390 otulip rtl8139 sis900 sk_g16 \
			smc9000 tiara tulip via_rhine w89c840 wd nopcibios
# The most common ones. The more you choose, the higher the
# probability that the generated binaries do not work.
FLAVOR?=		x3c90x eepro100 ne ns8390 via_rhine

.if ${FLAVOR:L:Mx3c503}
CONFIGURE_ARGS+=	--enable-3c503
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mx3c503_aui}
.  if ${FLAVOR:L:Mx3c503}
CONFIGURE_ARGS+=	--enable-3c503-aui
.  else
BROKEN=			"Flavour x3c503_aui depends on x3c503"
.  endif
.else
CONFIGURE_ARGS+=	--disable-3c503-aui
.endif

.if ${FLAVOR:L:Mx3c503_shmem}
.  if ${FLAVOR:L:Mx3c503}
CONFIGURE_ARGS+=	--enable-3c503-shmem
.  else
BROKEN=			"Flavour x3c503_shmem depends on x3c503"
.  endif
.else
CONFIGURE_ARGS+=	--disable-3c503-shmem
.endif

.if ${FLAVOR:L:Mx3c507}
CONFIGURE_ARGS+=	--enable-3c507
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mx3c509}
CONFIGURE_ARGS+=	--enable-3c509
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mx3c529}
CONFIGURE_ARGS+=	--enable-3c529
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mx3c595}
CONFIGURE_ARGS+=	--enable-3c595
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mx3c90x}
CONFIGURE_ARGS+=	--enable-3c90x
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mcs89x0}
CONFIGURE_ARGS+=	--enable-cs89x0
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mdavicom}
CONFIGURE_ARGS+=	--enable-davicom
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mdepca}
CONFIGURE_ARGS+=	--enable-depca
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Meepro}
CONFIGURE_ARGS+=	--enable-eepro
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Meepro100}
CONFIGURE_ARGS+=	--enable-eepro100
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mepic100}
CONFIGURE_ARGS+=	--enable-epic100
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mexos205}
CONFIGURE_ARGS+=	--enable-exos205
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mlance}
CONFIGURE_ARGS+=	--enable-lance
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mnatsemi}
CONFIGURE_ARGS+=	--enable-natsemi
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mne}
CONFIGURE_ARGS+=	--enable-ne
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mne2100}
CONFIGURE_ARGS+=	--enable-ne2100
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mni5010}
CONFIGURE_ARGS+=	--enable-ni5010
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mni5210}
CONFIGURE_ARGS+=	--enable-ni5210
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mni6510}
CONFIGURE_ARGS+=	--enable-ni6510
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mns8390}
CONFIGURE_ARGS+=	--enable-ns8390
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Motulip}
CONFIGURE_ARGS+=	--enable-otulip
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mrtl8139}
CONFIGURE_ARGS+=	--enable-rtl8139
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Msis900}
CONFIGURE_ARGS+=	--enable-sis900
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Msk_g16}
CONFIGURE_ARGS+=	--enable-sk-g16
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Msmc9000}
CONFIGURE_ARGS+=	--enable-smc9000
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mtiara}
CONFIGURE_ARGS+=	--enable-tiara
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mtulip}
CONFIGURE_ARGS+=	--enable-tulip
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mvia_rhine}
CONFIGURE_ARGS+=	--enable-via-rhine
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mw89c840}
CONFIGURE_ARGS+=	--enable-w89c840
HAVE_NETCARD=		defined
.endif

.if ${FLAVOR:L:Mwd}
CONFIGURE_ARGS+=	--enable-wd
HAVE_NETCARD=		defined
.endif

.ifdef HAVE_NETCARD
CONFIGURE_ARGS+=	--enable-diskless
CPPFLAGS+=		-DGRUB_OPENBSD_NETWORKED
.else
CONFIGURE_ARGS+=	--disable-diskless
CPPFLAGS+=		-DGRUB_OPENBSD_LOCAL
.endif

.if ${FLAVOR:L:Mnopcibios}
CONFIGURE_ARGS+=	--enable-pci-direct
.endif

post-patch:
	cp ${FILESDIR}/openbsd.c ${WRKSRC}/stage2/

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/grub
	cd ${WRKSRC} && ${INSTALL_DATA} ${FILES} ${PREFIX}/share/grub/
	${INSTALL_DATA} ${WRKSRC}/docs/{grub,multiboot}.info ${PREFIX}/info/

.include <bsd.port.mk>
