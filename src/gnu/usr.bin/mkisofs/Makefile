# $MirOS: src/gnu/usr.bin/mkisofs/Makefile,v 1.1.7.1 2005/03/06 16:46:49 tg Exp $

PROG=		mkisofs
MAN=		mkisofs.8tbl

.include <bsd.own.mk>
COPTS+=		-Wall
CPPFLAGS+=	-DUSE_LARGEFILES -DABORT_DEEP_ISO_ONLY -DAPPLE_HYB -DUSE_SCG \
		-DDVD_VIDEO -DSORTING -DSYSTEM_ID_DEFAULT=\"MirOS\" -DUDF \
		-DUSE_LIBSCHILY -DVANILLA_AUTOCONF -DUSE_STATIC_CONF -Dlint \
		-DAPPID_DEFAULT=\"MirOS\ mkisofs\" -DHOST_VENDOR=\"MirOS\" \
		-DHOST_CPU=\"${MACHINE}\" -DHOST_OS=\"Mir${MACHINE_OS}\"

SRCS=		apple.c apprentice.c astoi.c astoll.c block.c boot.c \
		breakline.c btree.c cd_misc.c cmpbytes.c cmpnullbytes.c \
		comerr.c cvmod.c dat.c data.c desktop.c dvd_file.c \
		dvd_reader.c eltorito.c error.c exclude.c fcons.c fcons64.c \
		fconv.c fdown.c fdup.c fdup64.c fexec.c ffileread.c \
		ffilewrite.c fgetline.c fgetstr.c file.c file_raise.c \
		fileclose.c fileluopen.c fileluopen64.c fileopen.c \
		fileopen64.c filepos.c filepos64.c fileread.c filereopen.c \
		filereopen64.c files.c fileseek.c fileseek64.c filesize.c \
		filesize64.c filestat.c filestat64.c filewrite.c fillbytes.c \
		findbytes.c findline.c flag.c flush.c fnmatch.c format.c \
		fpipe.c gdata.c getargs.c getav0.c getdomainname.c geterrno.c \
		getfp.c gethostid.c gethostname.c getpagesize.c handlecond.c \
		hash.c hfs.c ifo_read.c joliet.c jsprintf.c jssnprintf.c \
		jssprintf.c libfile_file.c low.c mac_label.c match.c \
		mkisofs.c modes.c movebytes.c multi.c name.c niread.c \
		niwrite.c nixread.c nixwrite.c nls_base.c nls_config.c \
		nls_cp10000.c nls_cp10006.c nls_cp10007.c nls_cp10029.c \
		nls_cp10079.c nls_cp10081.c nls_cp1250.c nls_cp1251.c \
		nls_cp437.c nls_cp737.c nls_cp775.c nls_cp850.c nls_cp852.c \
		nls_cp855.c nls_cp857.c nls_cp860.c nls_cp861.c nls_cp862.c \
		nls_cp863.c nls_cp864.c nls_cp865.c nls_cp866.c nls_cp869.c \
		nls_cp874.c nls_file.c nls_iso8859-1.c nls_iso8859-14.c \
		nls_iso8859-15.c nls_iso8859-2.c nls_iso8859-3.c \
		nls_iso8859-4.c nls_iso8859-5.c nls_iso8859-6.c \
		nls_iso8859-7.c nls_iso8859-8.c nls_iso8859-9.c nls_koi8-r.c \
		nls_koi8-u.c node.c openfd64.c peekc.c printf.c raisecond.c \
		record.c rename.c rock.c saveargs.c scgsettarget.c scgtimes.c \
		scsi.c scsi_cdr.c scsierrs.c scsihack.c scsihelp.c scsiopen.c \
		scsitransp.c serrmsg.c seterrno.c setfp.c snprintf.c \
		softmagic.c spawn.c sprintf.c strcatl.c strdup.c stream.c \
		streql.c swabbytes.c tree.c udf.c usleep.c volume.c \
		volume_libhfs_iso.c write.c

# Someone to send an extermination mission to Jörg Schily?

.include <bsd.prog.mk>
