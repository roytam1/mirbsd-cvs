<!-- PageID: irc -->
<small class="rcsid">$MirOS: www/content/aXJj.inc,v 1.3 2006/05/17 12:42:24 tg Exp $</small>

<h1>The MirOS Project on IRC</h1>

<h2>Table of Contents</h2><ul>
 <li><a href="#where">Where we are</a></li>
 <li>Freeforge: <a href="#ffinf">About the Network</a></li>
 <li>Freeforge: <a href="#ffcon">List of Servers</a></li>
 <li>Freeforge: <a href="#ffwww">WWW to IRC gateways</a></li>
 <li>Freenode: <a href="#fnqci">Quick connection instructions</a></li>
 <li>Freenode: <a href="#fninf">Further reading</a></li>
 <li>Freenode: <a href="#fnwww">WWW to IRC gateways</a></li>
</ul>

<h2 id="where">Where we are</h2>
<p>The MirOS Developers' main IRC channel is <tt>#mirbsd</tt> on
 the Freeforge network (see below), although we also hang around
 in some other channels. <tt>#bsd</tt> on Freeforge is a social
 channel like <tt>#mirbsd</tt> but with a little broader focus
 and more percentage of English talk (both channels are multilanguage).
 <tt>#mksh</tt> on Freenode, on the other hand, is intended to be
 more a technical channel (and &lt;quote src=&quot;Han&quot;&gt;lekker
 bash bashen! ;-)&lt;/quote&gt;) and mainly English-only. While
 <tt>#mirbsd</tt> and <tt>#bsd</tt> (the channels on Freeforge)
 are suggesting the UTF-8 character set, <tt>#mksh</tt> (Freenode)
 welcomes these who still use ISO-8859-1 as IRC encoding (though
 you won't need any umlauts there anyway).</p>

<p>Historically, we have been in <tt>#deutsch</tt> on Freenode
 (now defunct) first, then sat around in <tt>#deutsch</tt> on
 OFTC (now defunct) for a while. The move to OFTC was motioned
 by some Freenode politics, such as the over-use of cloaks for
 e.g. Gentoo developers (hurting my eyes), forcing users to use
 UTF-8 encoding (new channel, new guidelines), less strict Use
 of the Network policy, and yielded a sort of quiet channel &ndash;
 all the trolls didn't get it that we moved. On the other hand,
 the move to Freeforge was motioned by the will to have encryption
 all over the place; we moved kind of late though because there
 were some more reasons to stay on OFTC (socially), but these
 have moved to Freeforge with us. Sadly, we did lose some user
 base in the process.</p>

<h2>Freeforge</h2>
<p>Disclaimer: the Freeforge IRC network is neither run nor
 managed by MirOS staff, not even in personal union. But we
 support and endorse this network and have sponsored access
 to two boxen to the project to run their IRC d&aelig;mon on.
 Also, we consider Freeforge the successor to <tt>#deutsch</tt>
 and the next channel meeting (now: network meeting) has been
 planned to accomodate these facts.</p>

<h3 id="ffinf">About the Network</h3>
<p>The Freeforge IRC network is run by a team of three volunteers
 in their spare time on sponsored servers (two of them are hosted
 by Thorsten Glaser of MirOS). They use ratbox-ircd and some kind
 of weird services on top of that; one however gets used to these
 rather quickly. <a href="http://freeforge.net/">This poor excuse
 of a website</a> has now been filled with some outdated content,
 so this page you are currently reading (or, at the semi-official
 <a href="http://www.mirbsd.org/?irc">reference link</a>) is (for
 now) the primary source of information regarding Freeforge.</p>

<p>Freeforge guarantees that all server-to-server communication is
 secured by strong TLS encryption and also offers IRCS (IRC over
 TLS) to its end users. Whether a user is connected via TLS or not
 is shown in his /WHOIS information. Most of the servers are also
 connected to some kind of VPN, enabling people on these VPNs to
 easily connect securely without the need to use an SSL-capable
 IRC client or a proxy like "openssl(1) s_client". (However, at
 the moment there is no way to distinguish VPN users from non-VPN
 users, nor is there a way to make a channel exclusively for use
 of SSL or SSL/VPN users, although this is planned.)</p>

<p>The TLS X.509 certificates are signed by a free certification
 authority, <a href="https://www.cacert.org/">CAcert</a>. You must
 install the CAcert Root Certificate in your client in order to be
 able to validate the IRC servers. (If you don't, why are you using
 TLS anyway? Well, opportunistic encryption. That's good, too.)
 At the moment, the Freeforge IRC D&aelig;mon X.509 Certificates
 are, however, broken in two respects: they are issued to a CommonName
 of &quot;irc.freeforge.net&quot; (which is no round-robin, in contrast
 to &quot;irc.66h.42h.de&quot; aka &quot;irc.mirbsd.org&quot;) and are
 signed by the CAcert Class 3 Root but do not include the Class 3 Root
 CA Certificate in the X.509 certificate chain (effectively requiring
 clients to add the Class 3 Root CA Certificate, which is <strong>not</strong>
 a CA root certificate, to the root store). The author of this document
 hopes these issues will be resolved by the Freeforge team soon.</p>

<p>We highly recommend to register your nicknames with the Freeforge
 services. To do this, first register a services user with USERSERV,
 then ask NICKSERV to register your current nickname to that user.
 On login, message your credentials to USERSERV. Either of these bots
 can be queried the word HELP in order to get usage instructions.</p>

<h3 id="ffcon">List of Servers</h3>
<p>The standard way to connect to IRC is to open a TCP connection to
 one of the servers on port 6666 (non-SSL) or 6668 (TLS secured).
 Some of Freeforge's servers also offer IRC on the legacy
 port 6667 (also non-encrypted).</p>

<p>Thorsten Glaser of MirOS has set up a DNS round-robin for these who
 want to "simply connect to Port 6666/6668 and it works". You can use
 either of irc.mirbsd.org, irc4.mirbsd.org or irc6.mirbsd.org (for
 both address families, IPv4 only, and IPv6 only, respectively).</p>

<p>The following is a list of servers, indicating their capabilities,
 connectivity, etc.</p><ul>
<!-- li>zeus: zeus.freeforge.net (IPv4 only), gecko2.tb.as8758.net (IPv6
 only <strong>but no port 6667</strong>, only 6666 (non-SSL), 6668 (TLS)).
 The IPv4 portion of this server is included in the MirBSD round-robin;
 the IPv6 portion as well (beware!).
 This server is located at Strato, Berlin, Germany with an 100 Mbit
 IPv4 connection and an IPv6 tunnel to Switzerland.</li -->
<li>zeus: this server has been cancelled.</li>
<li>thor: this server has been cancelled.</li>
<li>maou: this server has been cancelled.</li>
<!-- li>maou: maou.66h.42h.de (IPv4 only). Included in the MirBSD round-robin.
 Also located at Strato, Berlin, Germany with an 100 Mbit pipe.</li -->
<li>herc: This server supports both IPv4 and IPv6 and all three ports
 (6668 TLS/SSL secured, 6666 and 6667 unencrypted), and both addresses
 are included in the MirBSD round-robin, although its DNS entry,
 <tt>herc.66h.42h.de</tt>, is IPv6-only and IPv4 connections are unstable
 due to gouvernment-mandated ISP regulations). Located in Bad Godesberg,
 Germany, behind a customer-grade ADSL connection with 0.5 Mbit IPv4
 to Cologne and an IPv6 tunnel to Hamburg.</li>
<li>bender: missing information will be filled in later</li>
<li>hephaistos: missing information will be filled in later</li>
</ul>

<p>As a special service to our customers, the IRC servers listed
 above (except bender) can also be used as time servers (NTP/SNTP;
 also time/daytime on the 66h.42h.de servers).</p>

<address>(to be continued)</address>
