#!/bin/mksh
# $MirOS: contrib/code/jupp/Make-w32.sh,v 1.14 2017/01/11 21:23:52 tg Exp $

usage() {
	print -ru2 "Usage: $0 [-bCgn]"
	print -ru2 '	Builds jupp32 (with debugging if -g): clean (unless -n),'
	print -ru2 '	configure (unless -n), make, package (unless -b), clean (unless -C)'
	exit 1
}

nopkg=0
nocln=0
debug=0
contb=0
while getopts "bCgn" c; do
	case $c {
	(b)	nopkg=1 ;;
	(C)	nocln=1 ;;
	(g)	debug=1 ;;
	(n)	contb=1 ;;
	(*)	usage ;;
	}
done

extrawarnings="-Wall -Wextra"
(( debug )) && extrawarnings="$extrawarnings -g3"
extrawarnings="$extrawarnings -Wno-unused-parameter"
echo "N: gcc-3.4.4-999 does not support -Wno-missing-field-initializers"
echo "N: expect warnings about those, they are known, do not report them"
extrawarnings="$extrawarnings -Wno-old-style-definition -Wno-strict-prototypes"
extrawarnings="$extrawarnings -Wno-cast-qual"
extrawarnings="$extrawarnings -Wno-missing-prototypes -Wno-missing-declarations"

export LC_ALL=C
set -ex
[[ -s configure && -s jupprc && -s charmaps/klingon.in ]]

jupp=$(sed -n "/^PACKAGE_VERSION='3\.1jupp\([0-9]*\)[~'].*\$/s//\1/p" configure)
jwin=
while (( jupp > 34 )); do
	jwin=${jwin}z
	(( jupp -= 25 ))
done
typeset -i1 tmp
(( tmp = 1#a - 10 + jupp ))
jwin=$jwin${tmp#1#}
jtop=jwin31$jwin
typeset -u jWIN=$jwin

if (( contb )); then
	[[ -s mkw32/build/Makefile ]]
else
	rm -rf mkw32
	mkdir mkw32{,/{build,$jtop}}
fi
cd mkw32/build
export CFLAGS='-Os -march=i486 -mtune=pentium-mmx'
export CPPFLAGS='-DJUPPRC_BUILTIN_NAME=\"jupp32rc\"'
(( contb )) || mksh ../../configure \
    --prefix=c:/windows/system32 \
    --sysconfdir=c:/windows/system32 \
    --disable-dependency-tracking \
    --disable-terminfo \
    --disable-search-libs \
    --disable-getpwnam \
    --disable-termidx \
    --enable-win32reloc
make AM_CFLAGS="$extrawarnings"
if (( nopkg )); then
	ln -f joe.exe jupp.exe
	ln -sf ../../jupprc .
	exit 0
fi
cp charmaps/* syntax/* ../$jtop/
cp jmacsrc joerc jpicorc jstarrc ../$jtop/
cp joe.exe ../$jtop/jupp32.exe
cd ../..
cp COPYING mkw32/$jtop/copying.txt
cp /bin/cygwin1.dll mkw32/$jtop/
cp joe.txt mkw32/$jtop/jupp32.txt
cp jupprc mkw32/$jtop/jupp32rc
cd mkw32/$jtop
:>setup.inf
for x in *; do
	[[ $x = *[A-Z]* ]] || continue
	mv "$x" ../_TMP
	typeset -l lc
	lc=$x
	mv ../_TMP "$lc"
done
sed -b -e "s!@jwin@!$jupp!g" -e "s!@ts@!$(date -u +%m/%d/%Y)!g" \
    <../../setup.inf | while IFS= read -r line; do
	if [[ $line = '@files@'* ]]; then
		stat -c '%n=1,,%s' *
	else
		print -r -- "$line"
	fi
done >setup.inf
sed -bi "/^setup.inf=1,,/s/^.*\$/$(stat -c '%n=1,,%s' setup.inf)/" setup.inf
sed -bi "/^setup.inf=1,,/s/^.*\$/$(stat -c '%n=1,,%s' setup.inf)/" setup.inf
chmod 444 *
cd ..
zip -D -X -9 -k ../JWIN31$jWIN.ZIP $jtop/*
cd ..
ls -l JWIN31$jWIN.ZIP
(( nocln )) || rm -rf mkw32
