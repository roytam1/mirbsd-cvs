# $MirOS: ports/lang/egcs/gcc4.4/autogen.sh,v 1.3 2014/02/10 01:15:49 tg Exp $

rv=0

echo === toplev
cd "$WRKSRC"
NO_ACLOCAL=1 \
NO_AUTOHEADER=1 \
$MKSH "${PORTSDIR}/infrastructure/scripts/autogen.sh" || rv=1

export ACLOCAL_FLAGS='-I ../config'

echo === fixincludes
cd fixincludes
ACLOCAL_FLAGS="$ACLOCAL_FLAGS -I ../gcc" \
$MKSH "${PORTSDIR}/infrastructure/scripts/autogen.sh" || rv=1
cd ..

echo === gcc
cd gcc
$MKSH "${PORTSDIR}/infrastructure/scripts/autogen.sh" || rv=1
cd ..

echo === libcpp
cd libcpp
$MKSH "${PORTSDIR}/infrastructure/scripts/autogen.sh" || rv=1
cd ..

echo === libdecnumber
cd libdecnumber
$MKSH "${PORTSDIR}/infrastructure/scripts/autogen.sh" || rv=1
cd ..

echo === libgcc
cd libgcc
NO_ACLOCAL=1 \
NO_AUTOHEADER=1 \
$MKSH "${PORTSDIR}/infrastructure/scripts/autogen.sh" || rv=1
cd ..

echo === libiberty
cd libiberty
NO_ACLOCAL=1 \
$MKSH "${PORTSDIR}/infrastructure/scripts/autogen.sh" || rv=1
cd ..

#echo === libobjc
#cd libobjc
#$MKSH "${PORTSDIR}/infrastructure/scripts/autogen.sh" || rv=1
#cd ..

#echo === libssp
#cd libssp
#$MKSH "${PORTSDIR}/infrastructure/scripts/autogen.sh" || rv=1
#cd ..

echo === libstdc++-v3
cd libstdc++-v3
$MKSH "${PORTSDIR}/infrastructure/scripts/autogen.sh" || rv=1
cd ..

exit $rv
