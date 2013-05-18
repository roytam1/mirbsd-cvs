<!-- PageID: bt -->
<small class="rcsid">$MirOS: www/content/YnQ_.inc,v 1.5 2006/10/29 22:22:43 tg Exp $</small>
<!-- http://www.mirbsd.org/?bt#id -->
<h1>BitTorrent information</h1>
<p><strong>Warning:</strong> Not finished yet.</p>
<h2>Tracker</h2>
<p>This information represents the files shown on the <a
 href="http://f.scarywater.net/miros/">Scarywater MirOS tracker</a>.
 (Some of the files are also available on some other torrent site.)</p>
<p>The last field in the table denotes the architectures the torrent's
 contents are for: i386, sparc, or dual-arch. Releases are always
 labelled #&lt;versionnumber&gt;&lt;additional info&gt; while snapshots
 are usually labelled with their release date, rarely after the events
 on/for which they were released. If a lower-case letter &quot;c&quot;
 is added, the snapshot also contains a copy of the CVS repository.</p>
<h2>Generic information</h2>
<p>... (live, install, arch, dd to hda, etc)</p>
<p>Releases never contain Live CD functionality. The releases offered
 are always ISO images (single file torrent), dual-arch.</p>
<p>Snapshots are usually Live+Install CD ISOs for i386, and currently,
 multi-file downloads for sparc (since there isn't a point in making a
 live CD for sparc yet) missing a miniroot. Snapshots are almost always
 only for a single architecture.</p>
<h2>Information about specific torrents</h2>
<h3>Releases</h3>
<p>If you're helping us to seed, please seed as many old releases as
 possible as well. If you cannot seed them all, seed at least #9semel
 (latest for i386) and #7quater (latest for sparc), please.</p>
<h4 id="r9semel">#9-RELEASE</h4>
<h4 id="r8semel">MirOS #8</h4>
<h4 id="r7quater">#7quater</h4>
<h3>Snapshots</h3>
<h4 id="s20070311">2007-03-11</h4>
<p>CVS plus i386 Live and Installation CD (ISO, bzip2'd, bootable via El
 Torito, bootable as &quot;Live Hard Disc&quot;). No source cpioballs.
 Changelog (relative to 2007-01-27):</p><ul>
 <li>Several updated, fixed, or new ports</li>
 <li>Lots of security and bug fixes</li>
 <li>New versions of mksh, OpenSSH, OpenSSL, dhclient, libevent, libpcap,
  sendmail, spamd, the kernel console code, &#8230;</li>
 <li>New time zone data, keymap, etc.</li>
 <li>Better UTF-8 / Unicode support (only supported locale)</li>
 <li>script(1) supports ISO 8859-1 &lt;-&gt; UTF-8 translation</li>
 <li>Usability improvements in the jupp(1) text editor</li>
 <li>Improved boot loader</li>
 <li>Work around some bugs in the GNU Compiler Collection, fix some</li>
 <li>This is now MirOS #10-beta</li>
</ul>
<h4 id="s20060706">2006-07-06</h4>
<p>First inofficial sparc snapshot, just to publish what I've been
 done for two weeks on a 75 MHz HyperSPARC after cross-compiling the
 whole mess. No X11, miniroot, Live-CD, testing. Most manpages, but
 two libcs (due to an intermediate major bump while building). This
 one will be deprecated really soon in favour of MirOS #9bis release.</p>
