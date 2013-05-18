#!/bin/mksh
# $MirOS: src/usr.bin/crunch/mkskel.sh,v 1.2 2005/03/13 18:32:50 tg Exp $
# $OpenBSD: mkskel.sh,v 1.2 2000/03/01 22:10:03 todd Exp $
#
# idea from flex; sed optimised by MirOS

print '/* File created via $MirOS: src/usr.bin/crunch/mkskel.sh,v 1.2 2005/03/13 18:32:50 tg Exp $ */\n'
print 'const char *crunched_skel[] = {'

sed -e 's/\\/&&/g' -e 's/"/\\"/g' -e 's/.*/	"&",/' "$@"

print '	0\n};'
