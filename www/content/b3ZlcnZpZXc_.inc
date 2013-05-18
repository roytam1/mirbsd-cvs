<!-- PageID: overview -->
<small class="rcsid">$MirOS: www/content/b3ZlcnZpZXc_.inc,v 1.18 2006/03/19 11:26:03 tg Exp $</small>
<h1>Quick Overview &ndash; All in one page</h1>

<h2>Status</h2><p>
 <a href="/?ann-8">MirOS #8</a> is the latest release.
 MirOS #8-stable has been opened, but there have not been any updates released yet.
 The <a href="/MirOS/current/i386/">latest snapshot</a> of the current development version (i386) is from 2006-02-15.
 The <a href="http://f.scarywater.net/miros/">BitTorrent tracker</a> contains a snapshot from 2006-02-25.
 MirPorts infrastructure and new installer (<a href="/?ports">docs</a>) are stable (note to use <tt>mmake</tt> as make(1) binary).
 We expect quite a percentage of individual ports to be broken or out of date due to lack of manpower.
</p>

<h2>Mailing lists</h2><ul>
 <li><a href="http://news.gmane.org/gmane.os.miros.general">http://news.gmane.org/gmane.os.miros.general</a>
  (archive of miros-discuss@MirBSD.org)</li>
 <li><a href="http://news.gmane.org/gmane.os.miros.cvs">http://news.gmane.org/gmane.os.miros.cvs</a>
  (archive of miros-changes@MirBSD.org, read-only)</li>
 <li>private list: miros-dev@MirBSD.org (developers only)</li>
</ul>

<h2>Mirrors known to work</h2><ul>
 <li>AnonCVS and AnonRSYNC<ul>
  <li>rsync://rsync.allbsd.org/mirbsd-cvs/ (empty pw) (IPv6 enabled)
   (rsyncd only)</li>
  <li>_anoncvs@anoncvs.66h.42h.de:/cvs (empty pw) <!-- (IPv6 enabled) -->
   (anoncvs and anonrsync)</li>
  <!-- li>_anoncvs@mirbsd.org:/cvs (empty pw)
   (anoncvs and anonrsync)</li -->
  <li>_anoncvs@herc.66h.42h.de:/cvs (port 57; private) (IPv6 enabled)
   (anoncvs and anonrsync)</li>
  <li>rsync://rsync.allbsd.org/mirbsd-old-cvs/ (empty pw) (IPv6 enabled)
   (rsyncd only)</li>
<!--  <li>_anoncvs@thor.66h.42h.de:/ncvs (empty pw) (IPv6 enabled)
   (anoncvs and anonrsync)</li>
  <li>_anoncvs@thor.66h.42h.de:/ocvs (empty pw) (IPv6 enabled)
   (anoncvs and anonrsync)</li> -->
 </ul></li>
 <li>CVSweb<ul>
  <li><a href="http://cvsweb.allbsd.org/cvsweb.cgi/?cvsroot=mirbsd">http://cvsweb.allbsd.org/cvsweb.cgi/?cvsroot=mirbsd</a></li>
  <li><a href="http://cvs.mirbsd.de/">http://cvs.mirbsd.de/</a> (should always work)</li>
  <!-- li><a href="https://mirbsd.mirsolutions.de:445/cvs.cgi/">http://mirbsd.mirsolutions.de/cvs.cgi/</a></li -->
 </ul></li>
 <li>Release<ul>
  <li><a href="http://f.scarywater.net/miros/BSD-8semel-full--i386-source.ISO.torrent">ISO (BitTorrent)</a> #8semel (i386)</li>
  <li><a href="http://www.mirbsd.org/MirOS/v8.1/i386/">Direct Download</a> #8semel (i386)</li>
  <li>(no #8semel/sparc released, please use MirOS #7 instead)</li>
  <li><a href="http://f.scarywater.net/miros/BSD-7quater-full.iso.torrent">ISO (BitTorrent)</a> #7quater (i386, sparc)</li>
  <li><a href="http://www.mirbsd.org/MirOS/v7.5/bsd/i386/">Direct Download</a> #7quinquies (i386)</li>
  <li><a href="http://www.mirbsd.org/MirOS/v7.4/bsd/sparc/">Direct Download</a> #7quater (sparc) + updates</li>
 </ul></li>
 <li>Snapshots<ul>
  <li><a href="http://f.scarywater.net/miros/">Please use our BitTorrent tracker</a> to download if available</li>
  <li><a href="http://www.mirbsd.org/MirOS/current/i386-20060215/">MirOS BSD #8-current/i386, 2006-02-15</a> (binary only)</li>
 </ul></li>
 <li>Website<ul>
  <li><a href="http://www.mirbsd.org/">http://www.mirbsd.org/</a></li>
 </ul></li>
 <li>CVS Repositories<ul>
  <li><a href="/MirOS/CVS/cvsrepo-20060215.cgz">/cvs</a> (4th, current)</li>
  <li><a href="/MirOS/CVS/cvsroot-historic.cgz">/ncvs /ocvs /lcvs</a> (1st, 2nd, 3rd combined, historic, final)</li>
 </ul></li>
</ul>

<h2>Cryptographical Information</h2>

<h3>gzsig(1)</h3>

<p>gzsig(1) is the current tool of choice for cryptographically signing
 work available from the MirOS Project. These are the keys used:</p><ul>
 <li><a href="http://mira.66h.42h.de/pub/gzsigkey.txt">ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAoEAy5akQiuw0znRhMD0djgQ7BiUPahG1QHJb9ZNApd6D5OnV98FO8Ofbfm4CF1Cvwr+IPnyKyPglQnaFgHF3LVynKMYSupKXnd0JrBR79TBmIVImBnIaTPcApRdWZEbMW5IdYhrWFHKlzk4vDxBXdcVE6QfiemWsYqkiuoJvLTLHXq7WUCQ5z7KuQetMnnP2bswV8SZuYy0IvzQRBVJbiTQzBvsHfyZUERLBZvjtPE9jTaLdTOkKvCuhuTzQAMmG8aYFt9S0p1K20eCCgWvJ5vu3ir875yBrtVPl2VzdFdo7Wv3kg1HOV+Sy7dQ2bIJ52mV8CnHI1W+ZMEjzQ64m75wH/AGsVb35E0sPJzFNCGj//8/kyKxRR1I0DSDOb+iE48twOrBRrUF5+ApwocqVdIa//Cbe1ArjzrEhwaKY0SitPcFwbVV8XadtsHXfdM5QnFwTsNobk2w+XLt9I5yL/SdE1NVVXBsAN1nejzDo8XTheD6o/m5O29WO3MSS7jt1PCYItVjN4ONK/Ztaa+zQcNK9itMy2tEJ1R/gI+AipOQi0JaHHAjcdYKxDbbJpurJAHvtLvKiJNqNUJPGpqCSfL8YqmDwf3Gs1SntRjgZNeOpAdiHl2qUewcB2vujROmLTQgxJ2HJTK8hKr+2nkZdEMkYYQ/wDtsGYohokU1GOGTjdr5d2vXW8MAWaF5UQDXQzPCT4RGjDLfvod4SM+GHn8t2eDJH8uHvUPU6AXcohM30zw/h9FPf18q7Oo0srwFpc0qjvwDxl9lgilsfaL23K2V5YFeTkO1llxnRdsTmSZ7UMsugBFu5bjGEL4hC/Sml0oH9F8hiV50fXWetsQvNB637Q== Thorsten "mirabile" Glaser &lt;tg@MirBSD.org&gt; SIGN</a></li>
</ul>

<h3>X.509</h3>

<p>We are using X.509 certificates emitted by <a
 href="http://www.CAcert.org/">CAcert</a> on our machines.
 While there is no known way to &quot;bootstrap&quot; trusting
 an external CA, for these who are still using PGP, tg@ has put
 a <a href="http://mira.66h.42h.de/pub/cacert.txt">clearsigned
 copy of the CAcert.org Root Certificate</a> on private webspace.
 Note that this is only a kind of timestamping, and we do not
 accept any responsibility or endorse their service or certificate.
 Neither has any of us (yet) checked their authenticity in person.</p>

<p>gzsig can also make use of X.509 certificates (which are just
 public keys and signatures of the CA for that key) to verify
 signed files, so you can make use of the CA trust chain.</p>

<h3>PGP (deprecated, obsolete)</h3>

<p>We used to have RFC1991 compatible PGP keys with which releases and
 snapshots were signed. These are the keys used (most recent first):</p><ul>
 <li>tg@ <a href="http://blackhole.pca.dfn.de:11371/pks/lookup?op=vindex&amp;fingerprint=on&amp;search=0x5CE51C3D">0x5CE51C3D</a> (no longer in use)</li>
 <li>bsiegert@ <a href="http://blackhole.pca.dfn.de:11371/pks/lookup?op=vindex&amp;fingerprint=on&amp;search=0xC246B025">0xC246B025</a></li>
 <li>tg@ <a href="http://blackhole.pca.dfn.de:11371/pks/lookup?op=vindex&amp;fingerprint=on&amp;search=0x68ED2381">0x68ED2381 (no longer in use)</li>
 <li>tg@ <a href="http://blackhole.pca.dfn.de:11371/pks/lookup?op=vindex&amp;fingerprint=on&amp;search=0xD7967B31">0xD7967B31 (no longer in use)</li>
 <li>tg@ <a href="http://blackhole.pca.dfn.de:11371/pks/lookup?op=vindex&amp;fingerprint=on&amp;search=0x8F1F22ED">0x8F1F22ED (no longer in use)</li>
</ul>
<p>Note that <tt>tg@</tt> does not use PGP at all any more.</p>
