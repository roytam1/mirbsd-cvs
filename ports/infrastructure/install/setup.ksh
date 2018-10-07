# $MirOS: ports/infrastructure/install/setup.ksh,v 1.99 2014/05/29 18:40:45 tg Exp $
#-
# Copyright (c) 2005, 2008, 2014
#	Thorsten “mirabilos” Glaser <tg@mirbsd.de>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.
#-
# This script really installs the MirPorts Framework.

function usage
{
	print -u2 "Syntax: Setup.sh [-u|-U user[:group]]] [-e|-E sysconfdir]"
	print -u2 "\t[-l localbase] [-X xfbase] [-DiNT]"
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
		$fetch $f_dist $mirror$f_path
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
	test $sum != good || test -z "$f_key" || \
	    if gzsig verify -q $T/$f_key $f_dist 2>/dev/null; then
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

trap 'rm -rf $T; exit 1' 1 2 3 5 13 15
trap 'rm -rf $T; exit 0' 0

called_with="$*"

[[ -n $localbase ]] || localbase=/usr/mpkg
[[ -n $xfbase ]] || xfbase=/usr/X11R6
if [[ $interix = yes ]]; then
	user=$(id -un | sed 's! !\\ !g'):$(id -gn | sed 's! !\\ !g')
else
	user=root:bin
fi
etc=/etc
integer iopt=0
integer nopt=0
integer topt=0
d=0
while getopts "DE:ehil:NTU:uX:" opt; do
	case $opt {
	(D)	trap - 0 1 2 3 13 15
		d=1 ;;
	(E)	etc=${OPTARG%%*(/)} ;;
	(e)	etc=@LOCALBASE@/etc ;;
	(i)	iopt=1 ;;
	(l)	localbase=${OPTARG%%*(/)} ;;
	(N)	nopt=1 ;;
	(T)	topt=1 ;;
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
p=$localbase/bin:$localbase/sbin
if test $isinterix = no; then
	for a in /usr/local/bin /usr/bin /bin $xfbase/bin /usr/X11R6/bin \
	    /usr/sbin /sbin; do
		case :$p: in
		*:$a:*)	continue ;;
		esac
		test -d $a && p=$p:$a
	done
else
	# On Interix, /usr/bin is /bin; gzip lives in /usr/contrib/bin;
	# gcc has yet its own directory; we have X11R5 as well
	for a in /usr/local/bin /opt/gcc.3.3/bin /usr/contrib/bin /bin \
	    /usr/sbin /sbin $localbase/sbin $xfbase/bin /usr/X11R6/bin; do
		case :$p: in
		*:$a:*)	continue ;;
		esac
		test -d $a && p=$p:$a
	done
	test -n "$PATH_WINDOWS" && p=$p:/usr/contrib/win32/bin:$PATH_WINDOWS
	test -d /usr/X11R5/bin && p=$p:/usr/X11R5/bin

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
PATH=$p; export PATH
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
[[ $myuid = root ]] || export BINMODE=755
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
	export BOOTSTRAP=yes
	;;
(Interix*)
	defmanpath='/usr/share/man:/usr/X11R6/man:/usr/X11R5/man'
	export FETCH_CMD=$fetch BOOTSTRAP=yes
	;;
(MidnightBSD*)
	ismnbsd=yes
	defmanpath='/usr/local/man:/usr/share/man:/usr/X11R6/man' #XXX
	export BOOTSTRAP=yes
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

if [[ $ismirbsd$isopenbsd$ismnbsd = *yes* && $user != root:bin ]]; then
	print -u2 WARNING: Using the MirPorts Framework without sudo is
	print -u2 highly discouraged if you do not need to do so. Several
	print -u2 applications install programs with setuid/setgid bits
	print -u2 set, leading to potential exploits of your user account.
	print -u2 In contrast, they handle suid-root and sgid-wheel properly.
	print -u2
	if [[ $isopenbsd$ismnbsd = yes ]]; then
		print -u2 Even on OpenBSD and MidnightBSD, you should \
		    install MirPorts with sudo.
		print -u2
	fi
fi

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

if (( iopt )); then
	# we are run under Interix pdksh
	portsdir=$(cd "$ourpath"; pwd)
else
	portsdir=$(realpath $ourpath)
fi

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
usetmpdir=0
if [[ -z $PKG_TMPDIR ]]; then
	if ! f=$(mktemp /var/tmp/mirports.XXXXXXXXXX); then
		# May be Interix without mktemp.sh
		f=/tmp/mirports.$$$RANDOM
		if [[ -e $f ]]; then
			print -u2 Cannot generate temporary file.
			exit 1
		fi
		print >$f
		if [[ ! -e $f ]]; then
			print -u2 Cannot generate temporary file.
			exit 1
		fi
	fi
	g=$localbase/bin/.tmp.$$$RANDOM
	if ! builtin rename $f $g 2>&-; then
		usetmpdir=1
		export PKG_TMPDIR=$localbase/db/tmp
		if ! mkdir -p $PKG_TMPDIR; then
			print -u2 Cannot generate playpen base directory.
			exit 1
		fi
	else
		unset PKG_TMPDIR
	fi
	rm -f $f $g
else
	export PKG_TMPDIR
fi


# Install the ld(1) wrapper
rm -f $localbase/bin/ld
install -c -o $myuid -g $mygid -m 600 \
    $portsdir/infrastructure/install/ld-wrapper.ksh $localbase/bin/ld
ed -s $localbase/bin/ld <<-EOF
	1s!/bin/mksh!$MKSH!
	wq
EOF
chmod 555 $localbase/bin/ld
[[ $isdarwin = *yes* ]] && ln -f $localbase/bin/ld $localbase/db/libtool
[[ $isdarwin$ismnbsd = *yes* ]] && ln -f $localbase/bin/ld $localbase/db/collect2


# Check if we need to install mirmake
cd $T
cat >f <<EOF
_MIRMAKE_VER?=0
all:
	@echo \${_MIRMAKE_VER}
EOF
shmk=$localbase/share/mmake
mv=20061228
f_ver=$(make -f f all)
f_verexist=$($localbase/bin/mmake -f f all 2>/dev/null)
(( nopt )) || if [[ $f_ver -ge $mv ]]; then
	# Version matches; write a wrapper if needed
	sysmk=$(make -f f ___DISPLAY_MAKEVARS=.SYSMK)
	m=$(whence -p make)
	if [[ $f_verexist -ge $mv ]]; then
		# We have already been here, keep the port
		:
	elif [[ $sysmk = $shmk ]]; then
		# Trouble ahead
		[[ $m = /usr/bin/make ]] || rm -f $m
	else
		wrapper=1 # Write a wrapper
		if [[ -x $localbase/bin/mmake && \
		    $(mmake -f f all) -lt $mv ]]; then
			[[ $(head -1 $localbase/bin/mmake) \
			    = "#!$MKSH" ]] || wrapper=0
		fi
		if [[ $wrapper = 1 ]]; then
			rm -f $localbase/bin/mmake
			cat >$localbase/bin/mmake <<-EOF
				#!$MKSH
				exec $m -m $shmk -m $sysmk "\$@"
			EOF
			chown $myuid:$mygid $localbase/bin/mmake
			chmod 555 $localbase/bin/mmake
			mkdir -p $shmk
			# Fake package installation
			mkdir -p $localbase/db/pkg/mirmake-$f_ver-0-wrapper
			sed -e "s#/usr/mpkg#$localbase#" \
			    -e 's#@subdir@#devel/mirmake,wrapper#' \
			    <$portsdir/infrastructure/templates/basepkg.CONTENTS \
			    >$localbase/db/pkg/mirmake-$f_ver-0-wrapper/+CONTENTS
			print mirmake wrapper, created by Setup.sh \
			    >$localbase/db/pkg/mirmake-$f_ver-0-wrapper/+COMMENT
		else
			print Upgrading MirMake, please wait...
			(cd $portsdir/devel/mirmake; \
			    . $localbase/db/SetEnv.sh; \
			    mmake repackage reupgrade clean)
		fi
	fi
fi
(( nopt )) || if [[ $(mmake -f f all 2>/dev/null) -lt $mv ]]; then
	if [[ $(cd $localbase/db/pkg && echo mirmake-*) != "mirmake-*" ]]; then
		print Upgrading MirMake, please wait...
		(cd $portsdir/devel/mirmake; \
		    . $localbase/db/SetEnv.sh; \
		    mmake repackage reupgrade clean)
	else
		# Too old (or nonexistant), install new mirmake
		dependdist make
		cd mirmake
		osmandir=man/cat
		if [[ $isinterix = yes ]]; then
			ostype=Interix
		elif [[ $ismnbsd = yes ]]; then
			ostype=MidnightBSD
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
		$SHELL ./Build.sh $ostype $localbase $osmandir mmake \
		    "" "" "" $SHELL $u
		$SHELL ./Install.sh
		set +e
		cd $T
		rm -rf mirmake
		# Fake package installation
		mkdir -p $localbase/db/pkg/mirmake-$f_ver-0-setup
		sed -e "s#/usr/mpkg#$localbase#" \
		    -e 's#@subdir@#devel/mirmake,setup#' \
		    <$portsdir/infrastructure/templates/basepkg.CONTENTS \
		    >$localbase/db/pkg/mirmake-$f_ver-0-setup/+CONTENTS
		print MirOS make variant, installed by Setup.sh \
		    >$localbase/db/pkg/mirmake-$f_ver-0-setup/+COMMENT
	fi
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
		mmake NOMAN=yes obj
		mmake NOMAN=yes depend
		mmake NOMAN=yes
		mmake NOMAN=yes install
		cd ../../../..
	done
	set +e
	# Building this without NOMAN=yes can be done by a port.
	rm -rf mirnroff
	# Fake package installation
	mkdir -p $localbase/db/pkg/nroff-$f_ver-0-setup
	sed -e "s#/usr/mpkg#$localbase#" \
	    -e 's#@subdir@#essentials/nroff,setup#' \
	    <$portsdir/infrastructure/templates/basepkg.CONTENTS \
	    >$localbase/db/pkg/nroff-$f_ver-0-setup/+CONTENTS
	print unix text processor, installed by Setup.sh \
	    >$localbase/db/pkg/nroff-$f_ver-0-setup/+COMMENT
fi
(( iopt )) && exit 0
unset NROFF


# Check if we need to install mtree
if [[ ! -x /usr/sbin/mtree && ! -x $localbase/bin/mtree ]]; then
	dependdist mtree
	set -e
	cd mtree
	mmake obj
	mmake depend
	mmake
	mmake install
	set +e
	cd ..
	rm -rf mtree
	# Fake package installation
	mkdir -p $localbase/db/pkg/mtree-$f_ver-0-setup
	sed -e "s#/usr/mpkg#$localbase#" \
	    -e 's#@subdir@#essentials/mtree,setup#' \
	    <$portsdir/infrastructure/templates/basepkg.CONTENTS \
	    >$localbase/db/pkg/mtree-$f_ver-0-setup/+CONTENTS
	print mtree >$localbase/db/pkg/mtree-$f_ver-0-setup/+COMMENT
fi
[[ $run_mtree = 0 ]] &&	mtree -U -e -d -n -p / -f $T/fake.mtree


# Write environmental stuff
cat >$localbase/db/SetEnv.sh <<-EOF
	LOCALBASE='$localbase'
	PORTSDIR='$portsdir'
	SYSCONFDIR='$etc'
	X11BASE='$xfbase'
	MAKECONF='$localbase/db/mmake.cfg'
	BINOWN='$myuid'
	BINGRP='$mygid'
	PATH='$PATH'
	MANPATH='$newmanpath'
	INFOPATH='$INFOPATH'
	PERL5LIB='$PERL5LIB'
	XAPPLRESDIR='$localbase/lib/X11/app-defaults'
	XDG_CACHE_HOME=\$HOME/.etc/xdg/cache
	XDG_CONFIG_DIRS='$etc/xdg:/etc/xdg'
	XDG_CONFIG_HOME=\$HOME/.etc/xdg/config
	XDG_DATA_DIRS='$localbase/share/:/usr/local/share/:/usr/share/'
	XDG_DATA_HOME=\$HOME/.etc/xdg/data
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
	export MANPATH INFOPATH PERL5LIB XAPPLRESDIR XDG_CACHE_HOME
	export XDG_CONFIG_DIRS XDG_CONFIG_HOME XDG_DATA_DIRS XDG_DATA_HOME
EOF
[[ $isinterix = yes ]] && cat >>$localbase/db/SetEnv.sh <<-EOF
	unset INCLUDE LIB
EOF
[[ $usetmpdir = 1 ]] && cat >>$localbase/db/SetEnv.sh <<-EOF
	PKG_TMPDIR='$PKG_TMPDIR'
	export PKG_TMPDIR
EOF
[[ $myuid = root ]] || \
    print 'BINMODE=755; export BINMODE' >>$localbase/db/SetEnv.sh
cat >>$localbase/db/SetEnv.sh <<-'EOF'
	if [ -z "$SSL_CERT_DIR" -a -d $LOCALBASE/share/ca-certificates/. ]; then
		SSL_CERT_DIR=$LOCALBASE/share/ca-certificates
		export SSL_CERT_DIR
	fi
	:
EOF

cat >$localbase/db/SetEnv.csh <<-EOF
	setenv LOCALBASE '$localbase'
	setenv PORTSDIR '$portsdir'
	setenv SYSCONFDIR '$etc'
	setenv X11BASE '$xfbase'
	setenv MAKECONF '$localbase/db/mmake.cfg'
	setenv BINOWN '$myuid'
	setenv BINGRP '$mygid'
	setenv PATH '$PATH'
	setenv MANPATH '$newmanpath'
	setenv INFOPATH '$INFOPATH'
	setenv PERL5LIB '$PERL5LIB'
	setenv XAPPLRESDIR '$localbase/lib/X11/app-defaults'
	setenv XDG_CACHE_HOME \$HOME/.etc/xdg/cache
	setenv XDG_CONFIG_DIRS '$etc/xdg:/etc/xdg'
	setenv XDG_CONFIG_HOME \$HOME/.etc/xdg/config
	setenv XDG_DATA_DIRS '$localbase/share/:/usr/local/share/:/usr/share/'
	setenv XDG_DATA_HOME \$HOME/.etc/xdg/data
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
[[ $usetmpdir = 1 ]] && cat >>$localbase/db/SetEnv.csh <<-EOF
	setenv PKG_TMPDIR '$PKG_TMPDIR'
EOF
[[ $myuid = root ]] || print 'setenv BINMODE 755' >>$localbase/db/SetEnv.csh
cat >>$localbase/db/SetEnv.csh <<-'EOF'
	if ( !($?SSL_CERT_DIR) && -d $LOCALBASE/share/ca-certificates/. ) then
		setenv SSL_CERT_DIR $LOCALBASE/share/ca-certificates
	endif
	true
EOF

cat >$localbase/db/SetEnv.make <<-EOF
	# called with $called_with

	LOCALBASE=	$localbase
	PORTSDIR?=	$portsdir
	SYSCONFDIR?=	$etc
	X11BASE?=	$xfbase
	MAKECONF=	$localbase/db/mmake.cfg
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
[[ $myuid = root ]] || print 'BINMODE?=	755' >>$localbase/db/SetEnv.make

. $localbase/db/SetEnv.sh

warn_makecfg=0
[[ -s $localbase/db/make.cfg && ! -s $localbase/db/mmake.cfg ]] \
    && mv $localbase/db/make.cfg $localbase/db/mmake.cfg
[[ -s $localbase/db/mmake.cfg ]] && warn_makecfg=1
if [[ ! -s $localbase/db/mmake.cfg ]]; then
	cat >$localbase/db/mmake.cfg <<-EOF
		# Default to include system-wide configuration
	EOF
	if [[ -e /etc/mk.conf ]]; then
		cat >>$localbase/db/mmake.cfg <<-EOF
			# Older system-wide configuration
			.include "/etc/mk.conf"

		EOF
	fi
	cat >>$localbase/db/mmake.cfg <<-EOF
		.if exists(/etc/make.cfg)
		.  include "/etc/make.cfg"
		.endif

		# Some stubs
	EOF
	if [[ $myuid = root ]]; then
		cat >>$localbase/db/mmake.cfg <<-EOF
			SUDO=			sudo	# Default on for root
		EOF
	else
		cat >>$localbase/db/mmake.cfg <<-EOF
			SUDO=				# Default off for user
		EOF
	fi
	cat >>$localbase/db/mmake.cfg <<-EOF
		#CLEANDEPENDS=		No	# Default to yes
		#PREFER_SUBPKG_INSTALL=	No	# Default to yes
		#VMEM_AUTOUNLOCK=	Yes	# Default to no
	EOF
fi

if (( nopt )); then
	[[ $warn_makecfg = 1 ]] && cat >&2 <<-EOF
		Warning: $localbase/db/mmake.cfg already existed before!
		Please verify if this file contains desired settings.
	EOF
	print Finished partial setup. Issue one of these commands:
	print "% source $localbase/db/SetEnv.csh"
	print "\$ . $localbase/db/SetEnv.sh"
	exit 0
fi

f_ver=$(cd $portsdir/essentials/pkgtools && \
    mmake show='CVS_DISTDATE:C![^0-9]!!g')
if [[ $(cd $localbase/db/pkg && echo pkgtools-$f_ver-*) \
    != "pkgtools-$f_ver-*" ]]; then
	: # Current package tools are already installed
elif [[ $(cd $localbase/db/pkg && echo pkgtools-*) != "pkgtools-*" ]]; then
	print Upgrading package tools, please wait...
	(cd $portsdir/essentials/pkgtools; \
	    mmake repackage reupgrade clean)
else
	if (( topt == 0 )); then
		dependdist pkgtools
		cd $T/pkgtools
		app=
	else
		mkdir -p $T/pkgtools
		cd $T/pkgtools
		lndir $portsdir/infrastructure/pkgtools
		f_ver=20091227	# hardcoded here, update manually and seldom
		app=-opt_t
	fi
	export LOCALBASE=$localbase PORTSDIR=$portsdir
	set -e
	mmake obj
	mmake depend
	mmake PORTABLE=Yes BINOWN="$myuid"
	mmake install
	set +e
	unset LOCALBASE
	cd $T
	# Fake package installation
	mkdir -p $localbase/db/pkg/pkgtools-$f_ver-0$app
	sed -e "s#/usr/mpkg#$localbase#" \
	    -e 's#@subdir@#essentials/pkgtools,'${app#-}'#' \
	    <$portsdir/infrastructure/templates/basepkg.CONTENTS \
	    >$localbase/db/pkg/pkgtools-$f_ver-0$app/+CONTENTS
	print autopackage tools, created by Setup.sh ${app:+from CVS} \
	    >$localbase/db/pkg/pkgtools-$f_ver-0$app/+COMMENT
	unset app
fi


# Check if we need to install cpio
# (Only install if it isn't there; the user can use pkg_upgrade himself)
[[ $ismirbsd = no ]] && if ! pkg_info paxmirabilis >/dev/null 2>&1; then
	set -e
	cd $portsdir/archivers/mircpio
	mmake fake
	x=$(mmake show=_FAKE_COOKIE)
	rm -f $localbase/bin/tar
	vp=${x%.fake_done}$(mmake show=PREFIX)/bin
	cp $vp/tar $localbase/bin/
	mmake package
	PATH=$vp:$PATH $localbase/sbin/pkg_add -N $(mmake show=_PACKAGE_COOKIE)
	set +e
	mmake clean
	cd $T
fi


# Check if we need to install patch
[[ $isinterix$ismnbsd = *yes* ]] && \
    if ! pkg_info patch >/dev/null 2>&1; then
	cd $portsdir/essentials/patch
	set -e
	mmake install
	set +e
	mmake clean
	cd $T
fi


# Check if we need to install cksum
[[ $isdarwin$isinterix$ismnbsd = *yes* ]] && \
    if ! pkg_info cksum >/dev/null 2>&1; then
	cd $portsdir/essentials/cksum
	set -e
	mmake install
	set +e
	mmake clean
	cd $T
fi


# Check if we need to install GNU m4
[[ $isinterix$ismnbsd = *yes* ]] && \
    if ! pkg_info m4 >/dev/null 2>&1; then
	cd $portsdir/lang/m4
	set -e
	mmake install
	set +e
	mmake clean
	cd $T
fi
[[ $isdarwin$isinterix$ismnbsd = *yes* ]] && unset BOOTSTRAP


# Check if we need to install GNU wget
[[ $isinterix = *yes* ]] && \
    if ! pkg_info wget >/dev/null 2>&1; then
	cd $portsdir/net/wget
	set -e
	mmake install
	set +e
	mmake clean
	cd $T
fi
[[ $isinterix = *yes* ]] && unset FETCH_CMD


# End of installation program

[[ $ismirbsd = yes ]] || rm -rf $localbase/tmp

(( topt )) || if [[ $ismirbsd$isopenbsd = *yes* && $myuid = root ]]; then
	print Augmenting user and group database...
	$SHELL $portsdir/infrastructure/install/mkuserdb.ksh
else
	print Please add the required users to your system manually.
fi

[[ $warn_makecfg = 1 ]] && cat >&2 <<-EOF
	Warning: $localbase/db/mmake.cfg already existed before!
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
