# $MirOS$
# Please remember to add the following line to /etc/rc.conf.local:
# 	syslogd_flags="-a /var/named/dev/log"
#
# The following lines should be added to /etc/rc.local:

if ! cmp -s /etc/rndc.key /var/named/etc/rndc.key ; then
	echo
	echo -n "rndc-confgen: generating new shared secret... "
	if @LOCALBASE@/sbin/rndc-confgen -a -t /var/named >/dev/null 2>&1; then
		chmod 0640 /var/named/etc/rndc.key >/dev/null 2>&1
		echo done.
	else
		echo failed.
	fi
fi

echo -n ' named';         @LOCALBASE@/sbin/named $named_flags

