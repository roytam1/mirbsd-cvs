#!/bin/mksh
set -e
cd "$(dirname "$0")"
set -x
cp 9x18.bdfc mirf18hw.bdfc
cp 18x18ko.bdfc mirf18fw.bdfc
ed -s mirf18hw.bdfc <fixedmir.ed
ed -s mirf18fw.bdfc <fixedmir.ed
bdfctool -Fd <mirf18hw.bdfc >mirf18hw.bdf
bdfctool -Fd <mirf18fw.bdfc >mirf18fw.bdf
