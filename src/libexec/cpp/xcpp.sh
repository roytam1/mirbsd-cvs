#!/bin/sh
# $MirOS: src/libexec/cpp/xcpp.sh,v 1.1.7.1 2005/03/06 16:33:40 tg Exp $

if [ -e /usr/bin/mcpp ]; then
	exec /usr/bin/mcpp "$@"
fi

if [ -e /usr/libexec/cpp ]; then
	exec /usr/libexec/cpp "$@"
fi

exec mcpp "$@"

echo exec of cpp failed: $?
exit 1
