#!/bin/sh
# $MirOS$

REALPLAYER_HOME='@RPDIR@'
export REALPLAYER_HOME

exec $REALPLAYER_HOME/realplay "$@"
