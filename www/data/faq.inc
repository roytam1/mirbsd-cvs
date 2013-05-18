RCSID: $MirOS: www/data/faq.inc,v 1.5 2010/07/12 20:48:25 tg Exp $
Title: Why don't I have colours on the console?

<p>The first virtual terminal is the system console, unless the
 system runs from serial console. Use Ctrl-Alt-F2 to switch to
 the second one, whose terminal type defaults to “wsvt25”, thus
 allowing colors and more advanced features.</p>
<p>This does not work on sparc, as there is only one virtual
 console on wsfb-using devices. You can, however, simply “export
 TERM=wsvtg” there, as the sparc system console, wsdisplay(4),
 emulates a colourful VT100/VT220 as well, in MirOS #10.</p>
----
Title: Where do I place my SSH public keys?
Section: Common ssh(1) and sshd(8) problems	XXX do this differently!

<p>sshd(8): The name is <tt>~/.etc/ssh/authorised_keys</tt> (british
 spelling), but <tt>~/.ssh/authorized_keys</tt> (upstream standard
 location) ought to work as well, for compatibility reasons.</p>
----
Title: SSH host key verification fails for your servers, e.g. on “cvs up”
Section: Common ssh(1) and sshd(8) problems	XXX do this differently!

<p>ssh(1): The <tt>anoncvs.mirbsd.org,85.214.23.162</tt> host entry
 in the MirOS #10 (RELEASE) default ssh <tt>known_hosts</tt> file is
 our old server, which ran on a Debian virtual host and, as such, was
 victim to the “private keys with only 15 bits of entropy” problem.
 A <i>[old broken link removed]</i> list of SSH host keys
 used by our publicly accessible servers contains the currently valid
 entries; <a href="@@RELPATH@@permalinks/news_e20080515-tg.htm">we
 reported the problem</a> earlier in the news.</p>
----
Title: How do I upgrade my system to latest -stable or -current?

<p>[… maybe write mircvs://www/src/uptodate.hts]</p>
----
Title: I don’t want the nightly calendar mails!

<pre>rm -f ~/.etc/calendar/calendar</pre>
<p>Get back from <tt>/etc/skel/.etc/calendar/calendar</tt> if needed.</p>
----
Title: Services? Stop, restart, …

<p class="boxhead">Use <tt>ports/sysutils/daemontools</tt> for external
 things. And, maybe, httpd(8), like this:</p><div class="boxtext">
 <pre>
	tg@blau:~ $ ssh www.mirbsd.org cat /service/httpd/run
	#!/bin/mksh

	exec 2&gt;&amp;1

	# enable core dumps for debugging
	cd /service/httpd
	ulimit -c unlimited

	exec /usr/sbin/httpd -F -u -DSSL
 </pre>
</div><p class="boxfoot">Don’t forget to chmod +x it.</p>
<p>Other services:</p><ul>
 <li>ntpd(8): <tt>cd /; sudo env -i /usr/sbin/ntpd <span
  class="u">-t</span></tt> (where <tt>-t</tt> is your
  <tt>$ntpd_flags</tt> from <tt>/etc/rc.conf{,.local}</tt>)</li>
 <li>sshd(8): <tt>cd /; sudo <a
  href="@@ABSPATH@@/cvs.cgi/src/scripts/cleanenv">cleanenv</a>
  - /usr/sbin/sshd</tt> (append <tt>$sshd_flags</tt> from
  <tt>/etc/rc.conf{,.local}</tt> if you have any)</li>
</ul>
----
