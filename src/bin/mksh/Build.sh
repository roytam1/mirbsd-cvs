#!/bin/sh
# $MirOS: src/bin/mksh/Build.sh,v 1.65 2006/11/09 00:08:25 tg Exp $
#-
# Environment: CC, CFLAGS, CPPFLAGS, LDFLAGS, LIBS, NROFF

v()
{
	$e "$*"
	eval "$@"
}

upper()
{
	echo "$@" | tr qwertyuiopasdfghjklzxcvbnm QWERTYUIOPASDFGHJKLZXCVBNM
}

ac_test()
{
	f=$1
	fu=`upper $f`
	fd=$3
	test x"$fd" = x"" && fd=$f
	test 0 = "$HAVE_$fu" && return
	test 1 = "$HAVE_$fu" && return
	if test x"$2" = x""; then
		ft=1
	else
		ft=`upper $2`
		eval ft=\$HAVE_$ft
	fi
	if test 0 = "$ft"; then
		eval HAVE_$fu=0 CPPFLAGS=\"\$CPPFLAGS -DHAVE_$fu=0\"
		return
	fi
	$e ... $fd
	cat >scn.c
	$CC $CFLAGS $CPPFLAGS $LDFLAGS $NOWARN scn.c $LIBS 2>&1 | sed 's/^/] /'
	if test -f a.out || test -f a.exe; then
		eval HAVE_$fu=1
		$e "==> $fd... yes"
	else
		eval HAVE_$fu=0
		$e "==> $fd... no"
	fi
	rm -f scn.c a.out a.exe
	eval CPPFLAGS=\"\$CPPFLAGS -DHAVE_$fu=\$HAVE_$fu\"
}

addsrcs()
{
	eval i=\$$1
	test 0 = $i && case " $SRCS " in
	*\ $2\ *)	;;
	*)		SRCS="$SRCS $2" ;;
	esac
}

if test -d mksh; then
	echo "$0: Error: ./mksh is a directory!" >&2
	exit 1
fi

: ${CFLAGS='-O2 -fno-strict-aliasing -Wall'}
: ${CC=gcc} ${NROFF=nroff}
curdir=`pwd` srcdir=`dirname "$0"`
echo | $NROFF -v 2>&1 | grep GNU >&- 2>&- && NROFF="$NROFF -c"

e=echo
q=0
r=0
x=0

for i
do
	case $i in
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
		echo "$0: Unknown option '$i'!" >&2
		exit 1
		;;
	esac
done

if test $x = 0; then
	LDSTATIC=-static
	SRCS=
	sigseen=
	NOWARN=-Wno-error
fi
SRCS="$SRCS alloc.c edit.c eval.c exec.c expr.c funcs.c histrap.c"
SRCS="$SRCS jobs.c lex.c main.c misc.c shf.c syn.c tree.c var.c"

test $x = 1 || case `uname -s 2>/dev/null || uname` in
CYGWIN*)
	LDSTATIC=
	sigseen=:
	;;
Darwin)
	LDSTATIC=
	CPPFLAGS="$CPPFLAGS -D_FILE_OFFSET_BITS=64"
	;;
Interix)
	CPPFLAGS="$CPPFLAGS -D_ALL_SOURCE"
	;;
Linux)
	CPPFLAGS="$CPPFLAGS -D_POSIX_C_SOURCE=2 -D_BSD_SOURCE -D_GNU_SOURCE"
	CPPFLAGS="$CPPFLAGS -D_FILE_OFFSET_BITS=64"
	LDSTATIC=
	sigseen=:
	;;
SunOS)
	CPPFLAGS="$CPPFLAGS -D_BSD_SOURCE -D__EXTENSIONS__"
	CPPFLAGS="$CPPFLAGS -D_FILE_OFFSET_BITS=64"
	LDSTATIC=
	sigseen=:
	r=1
	;;
esac

if test x"$sigseen" = x:; then
	$e Generating list of signal names
	NSIG=`printf %d "\`(echo '#include <signal.h>';echo mksh_cfg: NSIG) | \
	    $CC $CPPFLAGS -E - | grep mksh_cfg | sed 's/^mksh_cfg: //'\`" 2>&-`
	test $NSIG -gt 1 || exit 1
	echo '#include <signal.h>' | $CC $CPPFLAGS -E -dD - | \
	    grep '[	 ]SIG[A-Z0-9]*[	 ]' | \
	    sed 's/^\(.*[	 ]SIG\)\([A-Z0-9]*\)\([	 ].*\)$/\2/' | \
	    while read name; do
		( echo '#include <signal.h>'; echo "mksh_cfg: SIG$name" ) | \
		    $CC $CPPFLAGS -E - | grep mksh_cfg: | \
		    sed 's/^mksh_cfg: \([0-9]*\).*$/\1:'$name/
	done | grep -v '^:' | while IFS=: read nr name; do
		nr=`printf %d "$nr" 2>&-`
		test $nr -gt 0 && test $nr -lt $NSIG || continue
		case $sigseen in
		*:$nr:*) ;;
		*)	echo "		{ $nr, \"$name\" },"
			sigseen=$sigseen$nr:
			;;
		esac
	done >signames.inc
	test -f signames.inc || exit 1
fi

$e Scanning for functions... please ignore any errors.

ac_test arc4random <<-'EOF'
	#include <stdlib.h>
	int main(void) { arc4random(); return (0); }
EOF

ac_test arc4random_push arc4random <<-'EOF'
	#include <stdlib.h>
	int main(void) { arc4random_push(1); return (0); }
EOF

ac_test setlocale_ctype '' 'setlocale(LC_CTYPE, "")' <<'EOF'
	#include <locale.h>
	int main(void) { setlocale(LC_CTYPE, ""); return (0); }
EOF

ac_test langinfo_codeset setlocale_ctype 'nl_langinfo(CODESET)' <<'EOF'
	#include <langinfo.h>
	int main(void) { nl_langinfo(CODESET); return (0); }
EOF

ac_test setmode <<-'EOF'
	#include <unistd.h>
	int main(int ac, char *av[]) { setmode(av[0]); return (ac); }
EOF

ac_test strlcat <<-'EOF'
	#include <string.h>
	int main(int ac, char *av[]) { strlcat(av[0], av[1], 1); return (ac); }
EOF

ac_test strlcpy <<-'EOF'
	#include <string.h>
	int main(int ac, char *av[]) { strlcpy(av[0], av[1], 1); return (ac); }
EOF

ac_test sys_param_h '' '<sys/param.h>' <<'EOF'
	#include <sys/param.h>
	int main(void) { return (0); }
EOF

$e ... done.
addsrcs HAVE_SETMODE setmode.c
addsrcs HAVE_STRLCAT strlfun.c
addsrcs HAVE_STRLCPY strlfun.c

(v "cd '$srcdir' && exec $CC $CFLAGS -I'$curdir' $CPPFLAGS" \
    "-DHAVE_CONFIG_H -DCONFIG_H_FILENAME=\\\"sh.h\\\"" \
    "$LDFLAGS $LDSTATIC -o '$curdir/mksh' $SRCS $LIBS") || exit 1
result=mksh
test -f mksh.exe && result=mksh.exe
test -f $result || exit 1
test $r = 1 || v "$NROFF -mdoc <'$srcdir/mksh.1' >mksh.cat1" || \
    rm -f mksh.cat1
test $q = 1 || v size $result
case $curdir in
*\ *)	echo "#!./mksh" >test.sh ;;
*)	echo "#!$curdir/mksh" >test.sh ;;
esac
echo "exec perl '$srcdir/check.pl' -s '$srcdir/check.t'" \
    "-p '$curdir/mksh' -C pdksh \$*" >>test.sh
chmod 755 test.sh
i=install
test -f /usr/ucb/$i && i=/usr/ucb/$i
$e
$e Installing the shell:
$e "# $i -c -s -o root -g bin -m 555 mksh /bin/mksh"
$e "# grep -qx /bin/mksh /etc/shells || echo /bin/mksh >>/etc/shells"
$e "# $i -c -o root -g bin -m 444 dot.mkshrc /usr/share/doc/mksh/examples/"
$e
$e Installing the manual:
if test -f mksh.cat1; then
	$e "# $i -c -o root -g bin -m 444 mksh.cat1" \
	    "/usr/share/man/cat1/mksh.0"
	$e or
fi
$e "# $i -c -o root -g bin -m 444 mksh.1 /usr/share/man/man1/mksh.1"
$e
$e Run the regression test suite: ./test.sh
$e Please also read the sample file dot.mkshrc and the fine manual.
