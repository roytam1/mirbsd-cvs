#!/bin/ksh
# $MirOS$
#-
# Copyright (c) 2004, 2005
#	Thorsten "mirabile" Glaser <tg@66h.42h.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# All advertising materials mentioning features or use of this soft-
# ware must display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
#
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.
#-
# MirPorts Framework - Installation script
#
# What does this thing do?
# 1) detect which OS we are running on
# 2) build and install package tools to
#    /usr/sbin (MirOS), /usr/local/sbin (OpenBSD), /usr/mpkg/sbin (Darwin)
# 3) patch <bsd.sys.mk> if necessary
# 4) install generic makefile includes
#    and, if necessary, mirports.osdep.mk
# 5) patch /etc/mk.conf
# 6) augment user and group list

print "1. Detecting environment..."

function f_start
{
	cat >>$1 |&
}

function f_end
{
	exec 3>&p; exec 3>&-
}

cd $(dirname $0)
top=$(cd ../..; pwd)
ti=$top/infrastructure
if os="$(uname -M 2>/dev/null)"; then
	os=${os%% *}
else
	os="$(uname -s)"
fi
osver=$(uname -r | sed 's/\./_/')
[[ -z $SHELL ]] && SHELL=/bin/ksh
export SHELL

if ! tmp=$(mktemp /tmp/mirports.XXXXXXXXXX); then
	print cannot make temporary file
	exit 1
fi

trap 'rm -f $tmp ; exit 0' 0
trap 'rm -f $tmp ; exit 1' 1 2 3 13 15

if ! chown root $tmp; then
	print need root
	exit 1
fi

case $os in
Darwin)
	localbase=/usr/mpkg
	sysmk=$localbase/share/mmake
	mtar=$localbase/bin/tar
	pkgbin=$localbase/sbin

	cat $ti/templates/fake.mtree >$tmp
	(print '/@@local/d\ni\n'; IFS=/; s=;
	 for pc in $(print "$localbase"); do
		s="$s    "; print "$s$pc"
	 done; print '.\nwq') | ed -s $tmp
	mtree -U -e -d -n -p / -f $tmp
	mkdir -p $localbase/{db/pkg,etc}
	if ! fgrep $localbase /etc/profile >/dev/null 2>&1; then
		f_start /etc/profile
		print -p "export MANPATH=\$(manpath -q):$localbase/man"
		print -p "export PATH=$localbase/bin:\$PATH"
		f_end
	fi
	export PATH=$localbase/bin:$PATH
	;;
MirBSD)
	localbase=/usr/local
	sysmk=/usr/share/mk
	mtar=/bin/tar
	pkgbin=/usr/sbin

	ospl=$(uname -l | sed -e 's/^#//' -e 's/-.*$//' -e 's/^\(.\)./\1_/')
	ospm=${ospl%_*}
	ospl=${ospl#*_}
	# test is ancient -current or older, or modern
	if [[ $ospm -gt 7 ]]; then
		mirosnew=1
	else
		mirosnew=0
	fi
	( cd /usr/lib;
	  [[ -e libresolv.a && ! -e libdl.a ]] \
	    && ln libresolv.a libdl.a; \
	  [[ -e libexpat.so.0.0 && ! -e libexpat.so.4.0 ]] \
	    && ln -s libexpat.so.0.0 libexpat.so.4.0; \
	  for a in libpng.so.[01].*; do \
		b="$a"; \
		[[ -e $b ]] || b=nein; \
	  done; \
	  [[ $b != nein && ! -e libpng.so.4.0 ]] && ln -s $b libpng.so.4.0 )
	;;
OpenBSD)
	localbase=/usr/local
	sysmk=/usr/share/mk
	mtar=/bin/tar
	pkgbin=$localbase/sbin

	( cd /usr/lib;
	  [[ -e libresolv.a && ! -e libdl.a ]] \
	    && ln libresolv.a libdl.a )
	;;
*)
	print No support for the $os operating system.
	exit 1
	;;
esac

( cd $pkgbin
  rm -f mirports_tar
  print "#!$SHELL" >mirports_tar
  print "exec $mtar "'"$@"' >>mirports_tar
  chmod 555 mirports_tar
)

# detect compiler version and if it's GCC
if gv=$($ourCC -v 2>&1 | grep '/specs$'); then
	gv=${gv%/specs}
	gv=${gv##*/}
else
	gv=no
fi

print "2. Building package tools..."

cd $ti/pkgtools
rm -rf */obj
set -e
$MAKE cleandir
$MAKE obj
$MAKE cleandir
if [[ $os = Darwin ]]; then
	$MAKE depend INCS='-I/usr/mpkg/share/mmake'
	$MAKE PORTABLE=yes DB_DIR=$localbase/db \
	    INCS='-I/usr/mpkg/share/mmake' \
	    LIBS=/usr/mpkg/share/mmake/libhash.a
	$MAKE install PREFIX=$localbase MANDIR=$localbase/man/cat
elif [[ $os = MirBSD ]]; then
	$MAKE depend
	if [[ $mirosnew = 1 ]]; then
		$MAKE
	else
		$MAKE PORTABLE=yes
	fi
	$MAKE install
elif [[ $os = OpenBSD ]]; then
	$MAKE depend
	$MAKE PORTABLE=yes
	$MAKE install PREFIX=$localbase MANDIR=$localbase/man/cat
fi
set +e
rm -rf */obj

print -n "3. Patching <bsd.sys.mk>..."

if grep '\.ifndef.TRUEPREFIX' $sysmk/bsd.sys.mk >/dev/null 2>&1; then
	print not needed.
else
	if patch $sysmk/bsd.sys.mk \
	    $ti/install/patch-bsd_sys_mk; then
		print done.
		rm -f $sysmk/bsd.sys.mk.orig
	else
		print failed.
		exit 1
	fi
fi

print -n "4. Installing MirPorts system makefile includes..."

case $os in
Darwin)
	if ! install -c -o root -g wheel -m 644 \
	    $ti/install/mirports.osdep.mk-darwin \
	    $ti/mk/mirports.osdep.mk; then
		print failed.
		exit 1
	fi
	;;
MirBSD)
	if [[ $mirosnew = 0 ]]; then
		if ! install -c -o root -g wsrc -m 664 \
		    $ti/install/mirports.osdep.mk-mbsd \
		    $ti/mk/mirports.osdep.mk; then
			print failed.
			exit 1
		fi
	else
		rm -f $ti/mk/mirports.osdep.mk
	fi
	;;
OpenBSD)
	if ! install -c -o root -g wsrc -m 664 \
	    $ti/install/mirports.osdep.mk-obsd \
	    $ti/mk/mirports.osdep.mk; then
		print failed.
		exit 1
	fi
	print '/^#@@PKG_CMDDIR/s/^#@@//\nwq' | ed -s $ti/mk/mirports.osdep.mk
	;;
esac

if install -c -o root -g bin -m 444 \
    $ti/install/*.mk $sysmk/; then
	print done.
else
	print failed.
	exit 1
fi

print -n "5. Preparing /etc/mk.conf..."

touch /etc/mk.conf
if fgrep '#@@MIRPORTS start' /etc/mk.conf >/dev/null 2>&1; then
	ed -s /etc/mk.conf 2>/dev/null <<-EOF
		/#@@MIRPORTS start/,/#@@MIRPORTS end/c
		#@@MIRPORTS deleteme
		.
		w
		+g/^$/d
		-,.g/#@@MIRPORTS deleteme/d
		wq
	EOF
	print 'g/#@@MIRPORTS deleteme/d\nwq' | ed -s /etc/mk.conf
fi

f_start /etc/mk.conf
if ! fgrep '#@@MIRPORTS user1' /etc/mk.conf >/dev/null 2>&1; then
	print -p '#@@MIRPORTS user1'
	print -p '### Options for MirPorts (recommended)'
	print -p '# make clean descends into dependencies'
	print -p '# is overriden by certain ports though'
	print -p 'CLEANDEPENDS?=		yes'
	print -p '# install all subpackages by default on make install'
	print -p '# NOTE: earlier MirPorts versions defaulted to off!'
	print -p '#PREFER_SUBPKG_INSTALL?=no	# default: yes'
	print -p
fi

print -p '#@@MIRPORTS start'
print -p
print -p "_CC_IS_GCC=		$gv"
print -p

case $os in
Darwin)
	print -p "PORTSDIR=		$top"
	print -p "PKG_CMDDIR=		$localbase/sbin"
	;;
MirBSD)
	# nothing else here yet
	;;
OpenBSD)
	if [[ $top = /usr/ports ]]; then
		print -p "PKG_CMDDIR=		$localbase/sbin"
	else
		print -p "USE_MIRPORTS?=\t	yes"
		print -p
		print -p '.if ${USE_MIRPORTS:L} == "yes"'
		print -p "PORTSDIR=		$top"
		print -p "PKG_CMDDIR=		$localbase/sbin"
		print -p ".else"
		print -p "PORTSDIR=		/usr/ports"
		print -p ".endif"
	fi
	print -p
	;;
esac

print -p '#@@MIRPORTS end'
print -p
f_end
print done.

print -n "6. Augmenting user and group database..."

if [[ $os = @(Open|Mir)BSD ]]; then
	$SHELL $ti/scripts/mkuserdb
	print done.
else
	print not supported on $os, please do so manually!
fi

cat <<EOF

================================================
               Congratulations!
------------------------------------------------
 Your MirPorts Framework system is now set up
 completely and ready to run.
 If you have not yet done so, read the README
 file appropriate for your operating system for
 further information about how to use MirPorts:
 $ti/compat/README.${os}
================================================

EOF
exit 0
