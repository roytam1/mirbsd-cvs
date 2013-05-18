#!/bin/mksh
# $MirOS: ports/infrastructure/install/setup.ksh,v 1.39 2005/12/18 03:49:22 tg Exp $
#-
# Copyright (c) 2005
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
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a nontrivial bug.
#-
# This script really installs the MirPorts Framework.

function usage
{
	print -u2 "Syntax: Setup.sh [-u|-U user[:group]]] [-e|-E sysconfdir]"
	print -u2 "\t[-l localbase] [-X xfbase]"
	print -u2 "  -e\tset sysconfdir (default /etc; -e: \$localbase/etc)"
	print -u2 "  -u\tinstall as user (default root:bin except on Interix)"
	exit 1
}

function dependdist
{
	what=$1
	#%%BEGIN ^K. sync Setup.sh with setup.ksh %% getfile
	. $ourpath/infrastructure/install/distinfo.sh
	cd $DISTDIR
	test -r $f_dist || case "$mirror" in
	/*)	# file
		test -r $mirror/$f_path && cp $mirror/$f_path .
		test -r $mirror/$f_dist && cp $mirror/$f_dist .
		;;
	*)	# http
		$fetch $mirror$f_path
		;;
	esac
	sum=unchecked
	if s=`md5 $f_dist 2>/dev/null`; then
		if test x"$s" = x"$f_md5"; then
			sum=good
		else
			sum=bad
		fi
	fi
	test $sum = bad || if s=`cksum $f_dist 2>/dev/null`; then
		if test x"$s" = x"$f_sum"; then
			sum=good
		else
			sum=bad
		fi
	fi
	test $sum = bad || if s=`md5sum $f_dist 2>/dev/null`; then
		if test x"$s" = x"$f_md5sum"; then
			sum=good
		else
			sum=bad
		fi
	fi
	test $sum != good || if gzsig verify -q $T/signkey $f_dist 2>/dev/null; then
		echo Note: cryptographically strong checksum verified successfully for $f_dist >&2
		sum=verygood
	fi
	if test $sum = unchecked; then
		echo Warning: Cannot check hashes for $f_dist >&2
		echo Please compare the following two lines manually >&2
		echo "$f_lsline" >&2
		echo ": `TZ=UTC /bin/ls -l $f_dist`" >&2
		echo Press RETURN to continue or abort if unsure. >&2
		read s
	fi

	if test $sum = bad; then
		echo Checksum verification failed >&2
		echo "false: $s" >&2
		cd
		rm -rf $T
		exit 1
	fi

	# Extract the distfile
	if gzip -dc $f_dist | (cd $T && cpio -id); then
		:
	else
		echo Build failed >&2
		cd
		rm -rf $T
		exit 1
	fi
	#%%END sync Setup.sh with setup.ksh %% getfile

	cd $T
}


if [[ $isinterix != @(yes|no) || -z $mirror || -z $DISTDIR \
    || -z $ourpath || -z $tempdir || -z $fetch ]]; then
	print -u2 ERROR: Do not call this script directly!
	rm -rf $tempdir
	exit 1
fi
T=$tempdir

trap 'rm -rf $T; exit 1' 1 2 3 13 15
trap 'rm -rf $T; exit 0' 0

[[ -n $localbase ]] || localbase=/usr/mpkg
[[ -n $xfbase ]] || xfbase=/usr/X11R6
if [[ $interix = yes ]]; then
	user=$(id -un | sed 's! !\\ !g'):$(id -gn | sed 's! !\\ !g')
else
	user=root:bin
fi
etc=/etc
iopt=0
d=0
while getopts "DE:ehil:U:uX:" opt; do
	case $opt {
	(D)	trap - 0 1 2 3 13 15
		d=1 ;;
	(E)	etc=${OPTARG%%*(/)} ;;
	(e)	etc=@LOCALBASE@/etc ;;
	(i)	iopt=1 ;;
	(l)	localbase=${OPTARG%%*(/)} ;;
	(U)	user=$OPTARG ;;
	(u)	user=$(id -un):$(id -gn) ;;
	(X)	xfbase=${OPTARG%%*(/)} ;;
	(*)	usage ;;
	}
done
shift $((OPTIND - 1))

[[ $isinterix = yes ]] && LD_LIBRARY_PATH=$LD_LIBRARY_PATH_ORG
[[ $etc = @LOCALBASE@* ]] && etc=$localbase${etc#@LOCALBASE@}
[[ $d = 1 ]] && set -x

# Divine paths again
#%%BEGIN sync Setup.sh with setup.ksh %% paths
if test $isinterix = no; then
	p=$localbase/bin
	for a in /usr/local/bin /usr/bin /bin $xfbase/bin /usr/X11R6/bin \
	    /usr/sbin /sbin $localbase/sbin; do
		case :$p: in
		*:$a:*)	continue ;;
		esac
		test -d $a && p=$p:$a
	done
	PATH=$p; export PATH
else
	# On Interix, /usr/bin is /bin; gzip lives in /usr/contrib/bin;
	# gcc has yet its own directory; we have X11R5 as well
	p=$localbase/bin
	for a in /usr/local/bin /opt/gcc.3.3/bin /usr/contrib/bin /bin \
	    /usr/sbin /sbin $localbase/sbin $xfbase/bin /usr/X11R6/bin; do
		case :$p: in
		*:$a:*)	continue ;;
		esac
		test -d $a && p=$p:$a
	done
	test -n "$PATH_WINDOWS" && p=$p:/usr/contrib/win32/bin:$PATH_WINDOWS
	test -d /usr/X11R5/bin && p=$p:/usr/X11R5/bin
	PATH=$p; export PATH

	LD_LIBRARY_PATH_ORG=$LD_LIBRARY_PATH
	case :$LD_LIBRARY_PATH: in
	*:$xfbase/lib:*) ;;
	*)	LD_LIBRARY_PATH=$xfbase/lib:$LD_LIBRARY_PATH ;;
	esac
	case :$LD_LIBRARY_PATH: in
	*:$localbase/lib:*) ;;
	*)	LD_LIBRARY_PATH=$localbase/lib:$LD_LIBRARY_PATH ;;
	esac
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH%%+(:)}
	export LD_LIBRARY_PATH LD_LIBRARY_PATH_ORG
fi
#%%END sync Setup.sh with setup.ksh %% paths

# Check some stuff
myuid=${user%%:*}
mygid=${user##*:}
test=.mirports.test.$$.$RANDOM
x=0; print -n >$T/$test && chown $myuid $T/$test && chgrp $mygid $T/$test \
    && chown $myuid:$mygid $T/$test && rm $T/$test && x=1
if [[ $x = 0 ]]; then
	print -u2 "Error: Cannot use UID '$myuid', GID '$mygid'!"
	exit 1
fi
if [[ -d $etc || $etc != @($localbase/)* ]]; then
	x=0; print -n >$etc/$test && chown $myuid $etc/$test && chgrp $mygid $etc/$test \
	    && chown $myuid:$mygid $etc/$test && rm $etc/$test && x=1
	if [[ $x = 0 ]]; then
		print -u2 "Error: Cannot access '$etc' for UID '$myuid', GID '$mygid'!"
		exit 1
	fi
fi
[[ $myuid = root ]] || export BINOWN=$myuid
[[ $mygid = bin ]] || export BINGRP=$mygid
if [[ $isinterix = no && $myuid != root ]]; then
	# mostly copied from above (%% paths), except for the export
	case :$LD_LIBRARY_PATH: in
	*:$xfbase/lib:*) ;;
	*)	LD_LIBRARY_PATH=$xfbase/lib:$LD_LIBRARY_PATH ;;
	esac
	case :$LD_LIBRARY_PATH: in
	*:$localbase/lib:*) ;;
	*)	LD_LIBRARY_PATH=$localbase/lib:$LD_LIBRARY_PATH ;;
	esac
	export LD_LIBRARY_PATH=${LD_LIBRARY_PATH%%+(:)}
fi
if [[ $isinterix = yes || $myuid != root ]]; then
	need_llp=yes
else
	need_llp=no
fi

isopenbsd=no
ismirbsd=no
isdarwin=no

case $(uname -s 2>/dev/null || uname) {
(Darwin*)
	isdarwin=yes
	defmanpath='/usr/local/share/man:/usr/X11R6/man:/usr/share/man'
	;;
(Interix*)
	defmanpath='/usr/share/man:/usr/X11R6/man:/usr/X11R5/man'
	export FETCH_CMD=$fetch BOOTSTRAP=yes
	;;
(MirBSD*)
	ismirbsd=yes
	defmanpath='/usr/local/man:/usr/share/man:/usr/X11R6/man'
	;;
(OpenBSD*)
	if uname -M >/dev/null 2>&1; then
		ismirbsd=yes
	else
		isopenbsd=yes
	fi
	defmanpath='/usr/local/man:/usr/share/man:/usr/X11R6/man' #XXX
	;;
(*)
	print -u2 Cannot determine operating system.
	exit 1
	;;
}

newmanpath=${MANPATH:-$defmanpath}
[[ :$newmanpath: = *:$localbase/man:* ]] || \
    newmanpath=$localbase/man:$newmanpath
newmanpath=${newmanpath%%+(:)}

case :$INFOPATH: in
*:$localbase/info:*) ;;
*)	INFOPATH=$localbase/info:$INFOPATH ;;
esac
export INFOPATH=${INFOPATH%%+(:)}

case :$PERL5LIB: in
*:$localbase/libdata/perl5:*) ;;
*)	PERL5LIB=$localbase/libdata/perl5:$localbase/libdata/perl5/site_perl:$PERL5LIB ;;
esac
export PERL5LIB=${PERL5LIB%%+(:)}

portsdir=$(readlink -nf $ourpath 2>/dev/null || (cd $ourpath && pwd -P))

cp $portsdir/infrastructure/templates/fake.mtree $T/fake.mtree
if [[ $myuid != root ]]; then
	print 'g/[ug]name=[a-z]*/s///g\n'"/^.set/s/   /" \
	    "uname=$myuid gname=$mygid /\nwq" \
	    | ed -s $T/fake.mtree
fi
(print '/@@local/d\ni\n'; IFS=/; s=;
 for pc in $(print "$localbase"); do
	s="$s    "; print "$s$pc"
 done; print '.\nwq') | ed -s $T/fake.mtree
if whence -p mtree >/dev/null; then
	mtree -U -e -d -n -p / -f $T/fake.mtree
	run_mtree=1
else
	mkdir -p $localbase/{bin,db,include,info,lib{,data,exec}} \
	    $localbase/{man/{cat,man}{1,2,3,4,5,6,7,8},sbin,share}
	run_mtree=0
fi
mkdir -p $etc


# Check if we need to install mirmake
cd $T
cat >f <<EOF
_MIRMAKE_VER?=0
all:
	@echo \${_MIRMAKE_VER}
EOF
shmk=$localbase/share/make
if [[ $(make -f f all) -ge 20051215 ]]; then
	# Version matches; check for ${.SYSMK}
	sysmk=$(make -f f ___DISPLAY_MAKEVARS=.SYSMK)
	if [[ $ismirbsd = yes && $sysmk = /usr/share/mk \
	    && $localbase = /usr/mpkg && $myuid = root && $mygid = bin ]]; then
		# On MirOS-Default, use /usr/share/mk
		shmk=/usr/share/mk
	elif [[ $sysmk = $shmk ]]; then
		: # Everything OK, we don't need to update
	else
		# Write a wrapper
		m=$(whence -p make)
		cat >$localbase/bin/make <<-EOF
			#!$MKSH
			exec $m -m $localbase/share/make -m $sysmk "\$@"
		EOF
		chown $myuid:$mygid $localbase/bin/make
		chmod 555 $localbase/bin/make
		mkdir -p $shmk
	fi
else
	# Too old, install new mirmake
	dependdist make
	cd mirmake
	osmandir=man/cat
	if [[ $isinterix = yes ]]; then
		ostype=Interix
	elif [[ $ismirbsd = yes ]]; then
		ostype=MirBSD
	elif [[ $isopenbsd = yes ]]; then
		ostype=OpenBSD
	elif [[ $isdarwin = yes ]]; then
		ostype=Darwin
		osmandir=man/man
	fi
	u=$myuid:$mygid
	[[ $u = root:bin ]] && u=
	set -e
	$SHELL ./Build.sh $ostype $localbase $osmandir make "" "" "" $SHELL $u
	$SHELL ./Install.sh
	set +e
	cd $T
	rm -rf mirmake
fi

# Copy <*.mk> includes
cd $portsdir/infrastructure/install
cp mirports.sys.mk $T/
ed -s $T/mirports.sys.mk <<-EOF
	/^PORTSDIR/s#@#$portsdir#
	/^LOCALBASE/s#@#$localbase#
	wq
EOF
install -c -o $myuid -g $mygid -m 444 bsd.port.mk $shmk/
install -c -o $myuid -g $mygid -m 444 bsd.port.subdir.mk $shmk/
install -c -o $myuid -g $mygid -m 444 $T/mirports.sys.mk $shmk/


# Check if we need to install nroff
if [[ ! -f /usr/bin/nroff && ! -f $localbase/bin/nroff ]]; then
	dependdist nroff
	set -e
	for subdir in mirnroff/src/{usr.bin/oldroff,share/tmac}; do
		cd $subdir
		make NOMAN=yes obj
		make NOMAN=yes depend
		make NOMAN=yes
		make NOMAN=yes install
		cd ../../../..
	done
	set +e
	# Building this without NOMAN=yes can be done by a port.
	rm -rf mirnroff
fi
[[ $iopt = 1 ]] && exit 0
unset NROFF


# Check if we need to install mtree
if [[ ! -x /usr/sbin/mtree && ! -x $localbase/bin/mtree ]]; then
	dependdist mtree
	set -e
	cd mtree
	make obj
	make depend
	make
	make install
	set +e
	cd ..
	rm -rf mtree
fi
[[ $run_mtree = 0 ]] &&	mtree -U -e -d -n -p / -f $T/fake.mtree


# Write environmental stuff
DISTDIR=$(readlink -nf $DISTDIR)

cat >$localbase/db/SetEnv.sh <<-EOF
	LOCALBASE='$localbase'
	PORTSDIR='$portsdir'
	SYSCONFDIR='$etc'
	X11BASE='$xfbase'
	MAKECONF='$localbase/db/make.cfg'
	BINOWN='$myuid'
	BINGRP='$mygid'
	PATH='$PATH'
	MANPATH='$newmanpath'
	INFOPATH='$INFOPATH'
	PERL5LIB='$PERL5LIB'
EOF
[[ $need_llp = yes ]] && \
    cat >>$localbase/db/SetEnv.sh <<-EOF
	LD_LIBRARY_PATH='$LD_LIBRARY_PATH'
EOF
[[ $MKSH = /bin/mksh ]] || \
    cat >>$localbase/db/SetEnv.sh <<-EOF
	MKSH='$MKSH'
EOF
cat >>$localbase/db/SetEnv.sh <<-EOF
	export LOCALBASE PORTSDIR SYSCONFDIR X11BASE MAKECONF
	export BINOWN BINGRP PATH LD_LIBRARY_PATH MKSH
	export MANPATH INFOPATH PERL5LIB
EOF
[[ $isinterix = yes ]] && cat >>$localbase/db/SetEnv.sh <<-EOF
	unset INCLUDE LIB
EOF

cat >$localbase/db/SetEnv.csh <<-EOF
	setenv LOCALBASE '$localbase'
	setenv PORTSDIR '$portsdir'
	setenv SYSCONFDIR '$etc'
	setenv X11BASE '$xfbase'
	setenv MAKECONF '$localbase/db/make.cfg'
	setenv BINOWN '$myuid'
	setenv BINGRP '$mygid'
	setenv PATH '$PATH'
	setenv MANPATH '$newmanpath'
	setenv INFOPATH '$INFOPATH'
	setenv PERL5LIB '$PERL5LIB'
EOF
[[ $need_llp = yes ]] && \
    cat >>$localbase/db/SetEnv.csh <<-EOF
	setenv LD_LIBRARY_PATH '$LD_LIBRARY_PATH'
EOF
[[ $MKSH = /bin/mksh ]] || \
    cat >>$localbase/db/SetEnv.csh <<-EOF
	setenv MKSH '$MKSH'
EOF
[[ $isinterix = yes ]] && cat >>$localbase/db/SetEnv.csh <<-EOF
	unsetenv INCLUDE
	unsetenv LIB
EOF

cat >$localbase/db/SetEnv.make <<-EOF
	LOCALBASE=	$localbase
	PORTSDIR?=	$portsdir
	SYSCONFDIR?=	$etc
	X11BASE?=	$xfbase
	MAKECONF=	$localbase/db/make.cfg
	BINOWN?=	$myuid
	BINGRP?=	$mygid
	_PORTPATH?=	$PATH
EOF
[[ $need_llp = yes ]] && \
    cat >>$localbase/db/SetEnv.make <<-EOF
	_OUR_LDLIBPATH=	$LD_LIBRARY_PATH
EOF
[[ $MKSH = /bin/mksh ]] || \
    cat >>$localbase/db/SetEnv.make <<-EOF
	MKSH=		$MKSH
EOF
[[ $DISTDIR = $portsdir/Distfiles ]] || \
    cat >>$localbase/db/SetEnv.make <<-EOF
	DISTDIR=	$DISTDIR
EOF

warn_makecfg=0
[[ -s $localbase/db/make.cfg ]] && warn_makecfg=1
if [[ ! -s $localbase/db/make.cfg ]]; then
	cat >$localbase/db/make.cfg <<-EOF
		# Default to include system-wide configuration
		.if exists(/etc/\${MAKE:T}.cfg)
		.  include "/etc/\${MAKE:T}.cfg"
		.endif

	EOF
	if [[ -e /etc/mk.conf ]]; then
		cat >>$localbase/db/make.cfg <<-EOF
			# Older system-wide configuration
			.include "/etc/mk.conf"

		EOF
	fi
	cat >>$localbase/db/make.cfg <<-EOF
		# Some stubs
	EOF
	if [[ $myuid = root ]]; then
		cat >>$localbase/db/make.cfg <<-EOF
			SUDO=			sudo	# Default on for root
		EOF
	else
		cat >>$localbase/db/make.cfg <<-EOF
			SUDO=				# Default off for user
		EOF
	fi
	cat >>$localbase/db/make.cfg <<-EOF
		#CLEANDEPENDS=		No	# Default to yes
		#PREFER_SUBPKG_INSTALL=	No	# Default to yes
	EOF
fi

cd $portsdir/infrastructure/pkgtools
export LOCALBASE=$localbase PORTSDIR=$portsdir
set -e
make cleandir
make obj
make cleandir
make depend
make PORTABLE=Yes PKG_USER="$myuid"
make install
set +e
rm -rf {add,create,delete,info,lib,pkg,rtfm,upgrade}/obj
unset LOCALBASE
cd $T


# Check if we need to install cpio
# (Only install if it isn't there; the user can use pkg_upgrade himself)
[[ $isdarwin$isinterix = *yes* ]] && \
    if ! pkg_info paxmirabilis >/dev/null 2>&1; then
	set -e
	cd $portsdir/archivers/mircpio
	make fake
	x=$(make show=_FAKE_COOKIE)
	cp ${x%.fake_done}$(make show=PREFIX)/bin/tar $localbase/bin/
	make package
	pkg_add -N $(make show=_PACKAGE_COOKIE)
	set +e
	make clean
	cd $T
fi


# Check if we need to install patch
[[ $isinterix = *yes* ]] && \
    if ! pkg_info patch >/dev/null 2>&1; then
	cd $portsdir/essentials/patch
	set -e
	make install
	set +e
	make clean
	cd $T
fi


# Check if we need to install cksum
[[ $isdarwin$isinterix = *yes* ]] && \
    if ! pkg_info mircksum >/dev/null 2>&1; then
	cd $portsdir/essentials/cksum
	set -e
	make install
	set +e
	make clean
	cd $T
fi


# Check if we need to install GNU m4
[[ $isinterix = *yes* ]] && \
    if ! pkg_info m4 >/dev/null 2>&1; then
	cd $portsdir/lang/m4
	set -e
	make install
	set +e
	make clean
	cd $T
fi
[[ $isinterix = *yes* ]] && unset BOOTSTRAP


# Check if we need to install GNU wget
[[ $isinterix = *yes* ]] && \
    if ! pkg_info wget >/dev/null 2>&1; then
	cd $portsdir/net/wget
	set -e
	make install
	set +e
	make clean
	cd $T
fi
[[ $isinterix = *yes* ]] && unset FETCH_CMD


# End of installation programme

if [[ $ismirbsd$isopenbsd = *yes* && $myuid = root ]]; then
	print Augmenting user and group database...
	$SHELL $portsdir/infrastructure/install/mkuserdb.ksh
else
	print Please add the required users to your system manually.
fi

[[ $warn_makecfg = 1 ]] && cat >&2 <<-EOF
	Warning: $localbase/db/make.cfg already existed before!
	Please verify if this file contains desired settings.
EOF
if [[ $ismirbsd = yes && $myuid = root && $localbase = /usr/mpkg ]]; then
	print Finished first-time setup... have fun.
else
	print Should be done now... have fun. Issue one of these commands:
	print "% source $localbase/db/SetEnv.csh"
	print "\$ . $localbase/db/SetEnv.sh"
fi
exit 0
