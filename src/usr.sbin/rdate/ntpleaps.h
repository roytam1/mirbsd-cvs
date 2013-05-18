/* $MirOS: src/usr.sbin/rdate/leapsecs.h,v 1.1 2006/05/29 23:38:31 tg Exp $ */

/*
 * Converts a time_t measured in kernel ticks into a UTC time_t
 * using leap second information stored in /etc/localtime or an
 * equivalent indicator (e.g. the TZ environment variable).
 * If the kernel time is already measured in UTC instead of TAI
 * and a POSIX conformant time zone is set, this is a no-op.
 */
time_t tick2utc(time_t);
