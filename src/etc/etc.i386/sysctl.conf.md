# $MirOS: src/etc/etc.i386/sysctl.conf,v 1.4 2006/10/18 00:59:49 tg Exp $
#machdep.allowaperture=2	# See xf86(4)
#machdep.apmwarn=10		# battery % when apm status messages enabled
#machdep.apmhalt=1		# 1=powerdown hack, try if halt -p doesn't work
#machdep.kbdreset=1		# permit console CTRL-ALT-DEL to do a nice halt
#machdep.userldt=0		# disallow userland programs to play with ldt,
				# required to be enabled by some ports
#machdep.apvreset=0		# if the vga reset (X11+ddb) wrecks your DFP
#kern.emul.linux=1		# enable running Linux binaries
#kern.emul.openbsd=1		# enable running OpenBSD binaries