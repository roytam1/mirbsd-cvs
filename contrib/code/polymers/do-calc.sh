#!/bin/sh
#
# $MirOS$
set -e

mkdir -p results
for i in $(jot -w '%03d' 1000 0)
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
}' - > results/stats
