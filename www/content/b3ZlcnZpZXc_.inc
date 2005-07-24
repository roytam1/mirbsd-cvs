<small class="rcsid">$MirOS$</small>
<h1>Quick Overview &ndash; All in one page</h1>

<h2>Status</h2><p>
 MirOS #7 is the latest release.
 MirOS #7-stable has been EOL'd.
 MirOS-current is broken at the moment and does not build.
 There is currently no recommended snapshot to install; existing snapshots are quite broken.
 The best way to install MirOS at the moment is using the LinuxTag 2005 Special Edition CD-R.
 MirPorts are currently having a flag day; it is adviced to refrain from cvs update.
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
  <li>mirbsd-cvs@mirbsd.bsdadvocacy.org:/cvs (pw: anoncvs)
   (anoncvs only; broken RCS IDs)</li>
  <li>anoncvs@thor.66h.42h.de:/cvs (pw: anoncvs) (IPv6 enabled)
   (anoncvs and anonrsync)</li>
  <li>anoncvs@mirsolutions.de:/cvs (pw: anoncvs)
   (anoncvs and anonrsync)</li>
  <li>_anoncvs@herc.66h.42h.de:/cvs (port 57; private) (IPv6 enabled)
   (anoncvs and anonrsync)</li>
 </ul></li>
 <li>CVSweb<ul>
  <li><a href="https://mirbsd.mirsolutions.de:445/cvs.cgi/">http://mirbsd.mirsolutions.de/cvs.cgi/</a></li>
 </ul></li>
 <li>Release<ul>
  <li><a href="http://f.scarywater.net/miros/BSD-7quater-full.iso.torrent">ISO (BitTorrent)</a> #7quater (i386, sparc)</li>
  <li><a href="https://mirbsd.mirsolutions.de:445/MirOS/v7.5/bsd/i386/">Direct Download</a> #7quinquies (i386)</li>
  <li><a href="https://mirbsd.mirsolutions.de:445/MirOS/v7.4/bsd/sparc/">Direct Download</a> #7quater (sparc) + updates</li>
 </ul></li>
 <li>Snapshots<ul>
  <li>Currently, no suitable snapshot is available for download.</li>
 </ul></li>
 <li>Website<ul>
  <li><a href="http://mirbsd.bsdadvocacy.org/">http://mirbsd.bsdadvocacy.org/</a></li>
  <li><a href="https://mirbsd.mirsolutions.de:445/">http://mirbsd.mirsolutions.de/</a></li>
 </ul></li>
</ul>

<h2>Cryptographical Information</h2>

<h3><a href="/man1/gzsig.htm">gzsig(1)</a></h3>

<p>gzsig(1) is the current tool of choice for cryptographically signing
 work available from the MirOS Project. These are the keys used:</p><ul>
 <li><a href="http://mira.66h.42h.de/pub/gzsigkey.txt">ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAoEAy5akQiuw0znRhMD0djgQ7BiUPahG1QHJb9ZNApd6D5OnV98FO8Ofbfm4CF1Cvwr+IPnyKyPglQnaFgHF3LVynKMYSupKXnd0JrBR79TBmIVImBnIaTPcApRdWZEbMW5IdYhrWFHKlzk4vDxBXdcVE6QfiemWsYqkiuoJvLTLHXq7WUCQ5z7KuQetMnnP2bswV8SZuYy0IvzQRBVJbiTQzBvsHfyZUERLBZvjtPE9jTaLdTOkKvCuhuTzQAMmG8aYFt9S0p1K20eCCgWvJ5vu3ir875yBrtVPl2VzdFdo7Wv3kg1HOV+Sy7dQ2bIJ52mV8CnHI1W+ZMEjzQ64m75wH/AGsVb35E0sPJzFNCGj//8/kyKxRR1I0DSDOb+iE48twOrBRrUF5+ApwocqVdIa//Cbe1ArjzrEhwaKY0SitPcFwbVV8XadtsHXfdM5QnFwTsNobk2w+XLt9I5yL/SdE1NVVXBsAN1nejzDo8XTheD6o/m5O29WO3MSS7jt1PCYItVjN4ONK/Ztaa+zQcNK9itMy2tEJ1R/gI+AipOQi0JaHHAjcdYKxDbbJpurJAHvtLvKiJNqNUJPGpqCSfL8YqmDwf3Gs1SntRjgZNeOpAdiHl2qUewcB2vujROmLTQgxJ2HJTK8hKr+2nkZdEMkYYQ/wDtsGYohokU1GOGTjdr5d2vXW8MAWaF5UQDXQzPCT4RGjDLfvod4SM+GHn8t2eDJH8uHvUPU6AXcohM30zw/h9FPf18q7Oo0srwFpc0qjvwDxl9lgilsfaL23K2V5YFeTkO1llxnRdsTmSZ7UMsugBFu5bjGEL4hC/Sml0oH9F8hiV50fXWetsQvNB637Q== Thorsten "mirabile" Glaser &lt;tg@MirBSD.org&gt; SIGN</a></li>
</ul>

<h3>PGP</h3>

<p>We used to have RFC1991 compatible PGP keys with which releases and
 snapshots were signed. These are the keys used (most recent first):</p><ul>
 <li>tg@ <a href="http://blackhole.pca.dfn.de:11371/pks/lookup?op=vindex&fingerprint=on&search=0x5CE51C3D">0x5CE51C3D</a> (deprecated)</li>
 <li>bsiegert@ <a href="http://blackhole.pca.dfn.de:11371/pks/lookup?op=vindex&fingerprint=on&search=0xC246B025">0xC246B025</a></li>
 <li>tg@ <a href="http://blackhole.pca.dfn.de:11371/pks/lookup?op=vindex&fingerprint=on&search=0x68ED2381">0x68ED2381 (on server)</a> (deprecated)</li>
 <li>tg@ <a href="http://blackhole.pca.dfn.de:11371/pks/lookup?op=vindex&fingerprint=on&search=0xD7967B31">0xD7967B31</a> (revoked)</li>
 <li>tg@ <a href="http://blackhole.pca.dfn.de:11371/pks/lookup?op=vindex&fingerprint=on&search=0x8F1F22ED">0x8F1F22ED (well known)</a> (revoked)</li>
</ul>

<h3>X.509</h3>

<p>We are using X.509 certificates emitted by <a
 href="http://www.CAcert.org/">CAcert</a> on our machines.
 While there is no known way to &quot;bootstrap&quot; trusting
 an external CA, for these who are still using PGP, tg@ has put
 a <a href="http://mira.66h.42h.de/pub/cacert.txt">clearsigned
 copy of the CAcert.org Root Certificate</a> on private webspace.
 Note that this is only a kind of timestamping, and we do not
 accept any responsibility or endorse their service or certificate.</p>

<p><a href="/man1/ssh-keygen.htm">ssh-keygen(1)</a> in MirOS has
 options <b>-E</b> and <b>-I</b> which can convert keys between
 the OpenSSL X.509 and the gzsig OpenSSH format, so you can use
 your OpenSSL/CAcert private key to gzsign files, and recipients
 can use ssh-keygen to convert your X.509 certificate into the
 OpenSSH format then verify the signature.</p>
