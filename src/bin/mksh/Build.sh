#!/bin/sh
# $MirOS: src/bin/mksh/Build.sh,v 1.41 2006/08/12 18:49:21 tg Exp $
#-
# This script recognises CC, CFLAGS, CPPFLAGS, LDFLAGS, LIBS and NROFF.

CC="${CC:-gcc}"
CFLAGS="${CFLAGS--O2 -fno-strict-aliasing -fno-strength-reduce -Wall}"
srcdir="${srcdir:-`dirname "$0"`}"
curdir="`pwd`"

: ${NROFF:=nroff}
echo | $NROFF -v 2>&1 | fgrep GNU >&- 2>&- && NROFF="$NROFF -c"

e=echo
q=0
r=0
x=0

while [ -n "$1" ]; do
	case $1 in
	-d)
		LDSTATIC=
		;;
	-q)
		e=:
		q=1
		;;
	-r)
		r=1
		;;
	-x)
		x=1
		;;
	*)
		echo "$0: Unknown option '$1'!" >&2
		exit 1
		;;
	esac
	shift
done

v()
{
	$e "$*"
	eval "$@"
}

[ $x = 1 ] || LDSTATIC=-static
[ $x = 1 ] || SRCS=
SRCS="$SRCS alloc.c edit.c eval.c exec.c expr.c funcs.c histrap.c"
SRCS="$SRCS jobs.c lex.c main.c misc.c shf.c syn.c tree.c var.c"

[ $x = 1 ] || case "`uname -s 2>/dev/null || uname`" in
CYGWIN*)
	LDSTATIC= # they don't want it
	SRCS="$SRCS compat.c"
	CPPFLAGS="$CPPFLAGS -DNEED_COMPAT"
	;;
Darwin)
	LDSTATIC= # never works
	CPPFLAGS="$CPPFLAGS -D_FILE_OFFSET_BITS=64"
	;;
Interix)
	CPPFLAGS="$CPPFLAGS -D_ALL_SOURCE -DNEED_COMPAT"
	;;
Linux)
	# Hello Mr Drepper, we all like you too...</sarcasm>
	SRCS="$SRCS compat.c strlfun.c"
	CPPFLAGS="$CPPFLAGS -D_POSIX_C_SOURCE=2 -D_BSD_SOURCE -D_GNU_SOURCE"
	CPPFLAGS="$CPPFLAGS -D_FILE_OFFSET_BITS=64 -DNEED_COMPAT"
	LDSTATIC= # glibc dlopens the PAM library with getpwnam at runtime
	;;
SunOS)
	SRCS="$SRCS compat.c"
	CPPFLAGS="$CPPFLAGS -D_BSD_SOURCE -D_POSIX_C_SOURCE=200112L"
	CPPFLAGS="$CPPFLAGS -D__EXTENSIONS__"
	CPPFLAGS="$CPPFLAGS -D_FILE_OFFSET_BITS=64 -DNEED_COMPAT"
	LDSTATIC= # alternatively you need libdl... same suckage as above
	;;
esac

(echo '#include <signal.h>' | $CC $CPPFLAGS -E -dD - \
    | grep '[	 ]SIG[A-Z0-9]*[	 ]' \
    | sed 's/^\(.*[	 ]SIG\)\([A-Z0-9]*\)\([	 ].*\)$/\2/' \
    | while read name; do
	( echo '#include <signal.h>'; echo "__mksh_test: SIG$name" ) \
	    | $CC $CPPFLAGS -E - | fgrep __mksh_test: | sed \
	    's/^__mksh_test: \([0-9]*\).*$/		{ \1, "'$name'" },/'
done | fgrep -v '{ ,' >signames.inc) || exit 1
(v "cd '$srcdir' && exec $CC $CFLAGS -I'$curdir' $CPPFLAGS" \
    "$LDFLAGS $LDSTATIC -o '$curdir/mksh' $SRCS $LIBS") || exit 1
test -x mksh || exit 1
[ $r = 1 ] || v "$NROFF -mdoc <'$srcdir/mksh.1' >mksh.cat1" \
    || rm -f mksh.cat1
[ $q = 1 ] || v size mksh
echo "#!$curdir/mksh" >Test.sh
echo "exec perl '$srcdir/check.pl' -s '$srcdir/check.t'" \
    "-p '$curdir/mksh' -C pdksh \$*" >>Test.sh
chmod 755 Test.sh
$e
$e To test mksh, execute ./Test.sh
$e
$e Installing the shell:
$e "# install -c -s -o root -g bin -m 555 mksh /bin/mksh"
$e "# fgrep -qx /bin/mksh /etc/shells || echo /bin/mksh >>/etc/shells"
$e "# install -c -o root -g bin -m 444 dot.mkshrc /usr/share/doc/mksh/examples/"
$e
$e Installing the manual:
if test -s mksh.cat1; then
	$e "# install -c -o root -g bin -m 444 mksh.cat1" \
	    "/usr/share/man/cat1/mksh.0"
	$e or
fi
$e "# install -c -o root -g bin -m 444 mksh.1 /usr/share/man/man1/mksh.1"
