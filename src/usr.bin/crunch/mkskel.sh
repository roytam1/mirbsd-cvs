#!/bin/ksh
# $MirOS$
# $OpenBSD: mkskel.sh,v 1.2 2000/03/01 22:10:03 todd Exp $
#
# idea from flex; sed optimised by MirOS

print '/* File created via $MirOS$ */\n'
print 'const char *crunched_skel[] = {'

sed -e 's/\\/&&/g' -e 's/"/\\"/g' -e 's/.*/	"&",/' "$@"

print '	0\n};'
