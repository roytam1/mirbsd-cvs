#! /bin/sh -
# $MirOS$

if [ -e /usr/bin/mcpp ]; then
	exec /usr/bin/mcpp "$@"
fi

if [ -e /usr/libexec/cpp ]; then
	exec /usr/libexec/cpp "$@"
fi

exec mcpp "$@"

echo exec of cpp failed: $?
exit 1
