#!/bin/sh
# $MirOS$
#
autoconf
(cd libdb/dist && . ./s_config)
(cd calendar/libical && autoconf)
