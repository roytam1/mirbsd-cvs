#!/bin/mksh
# $MirOS: src/usr.bin/lex/mkskel.sh,v 1.2 2005/07/07 13:39:50 tg Exp $
# $OpenBSD: mkskel.sh,v 1.2 1996/06/26 05:35:39 deraadt Exp $


cat <<!
/* File created from flex.skl via mkskel.sh */

#include "flexdef.h"

const char *skel[] = {
!

sed \
    -e 's/\$Mir''OS:/$miros:/g' \
    -e 's/\\/&&/g' \
    -e 's/"/\\"/g' \
    -e 's/.*/	"&",/' \
    "$@"

cat <<!
	NULL
};
!
