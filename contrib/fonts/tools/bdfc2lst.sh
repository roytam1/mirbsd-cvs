#!/bin/sh
# $MirOS: contrib/fonts/fixed/bdfc2lst,v 1.1 2012/09/01 20:57:14 tg Exp $
#-
# .bdfc -> .lst (list of characters contained within)

for i in *.bdfc; do
	o=${i%.bdfc}.lst
	sed -n '/^c \([0-9A-F][0-9A-F][0-9A-F][0-9A-F]\) .*$/s//\1/p' \
	    <"$i" | sort >"$o"
done
