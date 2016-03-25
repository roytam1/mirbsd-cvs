# $MirSecuCron$
# $MirOS: src/etc/csh.login,v 1.1 2009/09/06 15:08:00 tg Exp $

umask 022
if (${?USER} == 0) then
	set path=(/sbin /bin /usr/sbin /usr/bin /usr/local/bin /usr/mpkg/bin)
else if ($USER == "") then
	set path=(/sbin /bin /usr/sbin /usr/bin /usr/local/bin /usr/mpkg/bin)
else
	set path=(~/.etc/bin /usr/local/bin /usr/mpkg/bin /usr/bin /bin /usr/X11R6/bin /usr/sbin /sbin /usr/mpkg/sbin /usr/games)
endif
if (${?HOME} == 0) setenv HOME /
if (($HOME == "") || (! -d $HOME/.)) setenv HOME /
if (${?OSNAME} == 0) setenv OSNAME MirBSD
if (${?SHELL} == 0) setenv SHELL /bin/csh
if ($SHELL !~ *csh) setenv SHELL /bin/csh
if (${?TERM} == 0) setenv TERM unknown
if (($TERM == "") || ($TERM == "unknown")) then
	if (-x /usr/bin/tset) then
		setenv TERM vt100
		eval `limit core 0; /usr/bin/tset -sQ \?vt220`
	endif
endif
stty newcrt werase '^W' intr '^C' kill '^U' erase '^?' status '^T'

setenv BROWSER lynx
setenv CVSUMASK 002
setenv EDITOR /bin/ed
setenv IRCNAME "MirOS packages a kernel, userland and the attitude"
setenv IRCPORT 6667
setenv IRCSERVER irc.eu.freenode.net
unsetenv LC_ALL
setenv LC_CTYPE en_US.UTF-8
setenv PAGER /usr/bin/less
setenv XDG_CACHE_HOME ~/.etc/xdg/cache
setenv XDG_CONFIG_HOME ~/.etc/xdg/config
setenv XDG_DATA_HOME ~/.etc/xdg/data
