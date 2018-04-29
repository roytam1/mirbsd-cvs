#!/bin/mksh
# $MirOS$

# 9x18.bdfc/18x18ko.bdfc are compatibility Fixed [Misc] overrides
# 6x13.bdfc is omitted because it’s Fixed [Misc], not FixedMisc [MirOS]
# ⇒ FixedMisc is one point/pixel size only
# The 9x18/ subdirectory is not currently usable

set -e
cd "$(dirname "$0")"
set -x
cp 9x18.bdfc mirf18hw.bdfc
cp 18x18ko.bdfc mirf18fw.bdfc
ed -s mirf18hw.bdfc <fixedmir.ed
ed -s mirf18fw.bdfc <fixedmir.ed
bdfctool -Fd <mirf18hw.bdfc >mirf18hw.bdf
bdfctool -Fd <mirf18fw.bdfc >mirf18fw.bdf
bdfctool -Fd <mirf16v8.bdfc >mirf16v8.bdf
[[ $1 = dist ]] || exit 0
mkdir dist
mv mirf18hw.bdf mirf18fw.bdf mirf16v8.bdf dist/
rm mirf18hw.bdfc mirf18fw.bdfc
cp README.dist dist/README
