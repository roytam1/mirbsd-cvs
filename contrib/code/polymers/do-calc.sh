#!/bin/mksh
#
# $MirOS: contrib/code/polymers/do-calc.sh,v 1.2 2005/03/20 18:19:13 bsiegert Exp $

RUNS=10000

set -e

mkdir -p results
for i in $(jot -w '%04d' $RUNS 0)
do
	./calc/poly-calc results/$i >> results/end2end
done
sort < results/end2end | awk '
/^[^#]/ {
	++count[$1]
}
END {	OFS="\t"
	for (i in count)
		print i, count[i]
}' - | sort -nbk 1 > results/stats

gnuplot stats.gnuplot > $RUNS.ps
ps2pdf $RUNS.ps
