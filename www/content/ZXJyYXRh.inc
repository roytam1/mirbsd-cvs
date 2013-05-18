<!-- PageID: errata -->

<small class="rcsid">$MirOS: www/content/ZXJyYXRh.inc,v 1.3 2006/01/27 00:14:28 tg Exp $</small>

<h1>Errata for MirOS #8</h1>

<h1>Errata for MirOS #8semel</h1>

<p>Updates for the errata below can be found in the directory
 <tt>/MirOS/v8.1/updates/</tt> on your favourite <a
 href="/MirOS/v8.1/updates/">mirror</a>.</p>

<p>These updates are in chronological order. They may depend on one another,
 so you should install them in the order presented. They are signed with
 PGP, please check the signature before installing them.</p>

<ul>
<li>An updated MirPorts Framework installation set (snapshot) is
 available as <tt>ports8.ngz</tt> (usually taken from the last
 snapshot of MirOS-current).</li>
<li>The <a href="/?ann-8#last">Last Minute updates</a> section of
 the release announcement is also worth a read.</li>
</ul>

<h3>20060401: sendmail</h3>

<p><b>Download</b>:
 <a href="/MirOS/v8.1/updates/20060401.tar.gz">20060401.tar.gz</a>
 (<a href="/MirOS/v8.1/updates/20060401.tar.gz.asc">PGP signature</a>)</p>

<p>This update fixes the recent sendmail security problems (<a
 href="http://www.cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2006-0058">CVE-2006-0058</a>).
 Sendmail versions older than 8.13.6 are vulnerable to a timing attack
 that allows the execution of arbitrary code.</p>

<p>The update contains an updated version of sendmail. After installing, you should recreate the databases by issuing the command:</p>

<blockquote><pre>cd /usr/share/sendmail/cf &amp;&amp; sudo make
 regen-databases</pre></blockquote>

<p>You can also install the updated configuration files in <tt>/etc</tt>.
 To do this, copy <tt>/usr/share/sendmail/cf/openbsd-proto.mc</tt> to
 <tt>/etc/mail/sendmail.cf</tt>,
 <tt>/usr/share/sendmail/cf/openbsd-localhost.mc</tt> to
 <tt>/etc/mail/localhost.cf</tt>, and
 <tt>/usr/share/sendmail/cf/submit.mc</tt> to
 <tt>/etc/mail/submit.cf</tt>.</p>
