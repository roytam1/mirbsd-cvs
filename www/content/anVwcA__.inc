<!-- PageID: jupp -->
<small class="rcsid">$MirOS: www/content/anVwcA__.inc,v 1.13 2006/11/05 21:38:22 tg Exp $</small>
<h1>jupp &ndash; the Editor</h1>
<p>
 The current version is <em>joe-3.1jupp7</em>.
 This page is accessible under <a href="http://mirbsd.de/jupp">http://mirbsd.de/jupp</a> usually.
</p>

<h2>About</h2>
<p>
 This is the portable, GNU automake/autoconf using, GPL (version 1)
 licenced, MirOS Special version of JOE's Own Editor which is
 currently developed at <a href="http://joe-editor.sf.net/">http://joe-editor.sf.net/</a>
</p>
<p>
 Kudos to Joe H. Allen for bringing me a better WordStar&trade;-compatible
 editor than Intergalactic Digital Research, DR Editor R2.00, DR DOS 5.
</p>

<h3>ChangeLog</h3>

<p>Changes for joe-3.1jupp7:</p><ul>
<li>Bugfix in bundled strlcat() implementation</li>
<li>Bugfix (off-by-one array bounds) in from_uni()</li>
<li>New option "vispace" to make spaces and tabs visible, like in
  Microsoft&#174; Works&#174;. Works best with Unicode.</li>
<li>"noxon" and "baud" are now menu entries; these two and
  "keepup" have been moved to the top so they can be switched
  quickly if you're in an ssh situation</li>
<li>Disable funny behaviour of keys in menus, fixes POLS</li>
<li>Reduce memory usage a little</li>
<li>In the options menu, if "return" is hit instead of entering a value,
  and it is not a string, it's handled sensitively: numbers keep their
  value, syntax gets unset, and encoding gets reset to the fdefault map.</li>
<li>Nicely format the options menu (as columns); print values for the
  syntax and encoding options as well in the oversight, use ellipsis for
  strings which aren't displayed otherwise</li>
<li>Spelling fixes in the options menu</li>
<li>Honour internationalisation framework of MirOS #9-current and newer</li>
</ul>

<p>Changes for joe-3.1jupp6:<br />
 Non-code (documentation) updates.
 Regenerate externally fetched files and autotools stuff.
</p>

<p>Changes for joe-3.1jupp5:<br />
 Documentation updates.
 Regenerate externally fetched files and autotools stuff.
 Fix help URI in jupprc.
</p>

<p>Changes for joe-3.1jupp4:<br />
 Keyboard fixes and DEC VT320/VT420 support in jupprc.
 Update of externally fetched subsystems. gzsig'd distfile.
</p>

<p>Changes for joe-3.1jupp3:<br />
 Overhaul of jupprc, especially improving Linux and MS-DOS keybindings.
 Several minor fixes. Conversion back to autoconf 2.59, automake 1.9.
</p>

<p>Changes for joe-3.1jupp2:<br />
 Fix make install in mkinstalldirs for users who wish to install jupp,
 but where the shell is not <a href="/?mksh">MirbsdKsh</a> but GNU bash.
</p>

<p>General<br />
 Please see the CVSweb at <a
  href="http://cvs.mirbsd.de/contrib/code/jupp/">http://cvs.mirbsd.de/contrib/code/jupp/</a>
 for more details.
</p>

<p>Basic differences of jupp are:</p>
<ul>
 <li>obviously, another flavour, jupp, similar to jstar</li>
 <li>utf-8 support on non-locale-aware OSses</li>
 <li>bug and security fixes</li>
 <li>tab completion fixes</li>
 <li>code cleanup</li>
 <li>compiles with -Wall -Werror (on MirBSD)</li>
 <li>improved options menu</li>
 <li>visibled spaces</li>
</ul>

<h2>Retrieval</h2>

<h3>Download</h3>
<ul>
 <li><a href="http://www.mirbsd.org/MirOS/dist/jupp/joe-3.1jupp7.cpio.gz">http://www.mirbsd.org/MirOS/dist/jupp/joe-3.1jupp7.cpio.gz</a></li>
</ul>

<p>Check the sums!</p>
<ul>
 <li>Please use gzsig(1) to verify
  the integrity of the distfile instead!</li>
 <li>RMD160 (joe-3.1jupp7.cpio.gz) = 6b1e329f177a84769afe9e2b2812eebd770d4b52</li>
 <li>3005792967 400544 /MirOS/dist/jupp/joe-3.1jupp7.cpio.gz</li>
 <li>MD5 (joe-3.1jupp7.cpio.gz) = cc5c01fd701978bd582a33f84b4f49dc</li>
 <li>TIGER (joe-3.1jupp7.cpio.gz) = f3bca5cf6572e214b68dd9382af4290a977f6d374582e27d</li>
</ul>

<h3>Unpacking</h3>
<p>
 For more detailed information, refer to <a href="/?mksh">MirbsdKsh</a>,
 it shows in detail how to use cpio(1).
</p>

<h2>Installation</h2>
<p>
 This is just another GNU autotools programme, so doing
</p><ul>
 <li>CFLAGS='-O2 yourcflagshere -fno-omit-frame-pointer' $SHELL ./configure</li>
 <li>make</li>
 <li>$SUDO make install</li>
</ul><p>
 should be fine - it even works with BSD make on MirOS without
 further patching. I'd be interested though if UTF-8 support
 works under MS-DOS or DR DOS (to close the circle...).
</p>

<h2>Binaries</h2>
<p>Currently, there are no precompiled binaries for Unix&reg;ish
 systems available. But we offer the following:</p><ul>
 <li><a href="http://mira.66h.42h.de/pub/jdos16.exe">JUPP 2.8 for
  MS-DOS&reg;</a> (16-bit, should work on 8086), self-extracting
  LHarc archive, copy jupp.exe and jupprc to your DOS directory (<a
  href="http://mira.66h.42h.de/pub/jdos16.exe.asc">OpenPGP
  signature</a>)</li>
 <li><a href="http://mira.66h.42h.de/pub/jupp-w32.exe">JUPP 3.1.6
  for Windows&reg;</a> (cygwin stand-alone compiled, comes with its
  own copy of cygwin1.dll and a .inf file for easy installation),
  self-extracting LHarc archive, right-click on <tt>setup.inf</tt>,
  select <b style="font-weight:normal; text-decoration:underline;">I</b>nstall,
  wait a few seconds, remove directory (<a
  href="http://mira.66h.42h.de/pub/jupp-w32.exe.asc">OpenPGP
  signature</a>)</li>
</ul>

<h1>Finally...</h1>
<pre>
gl hf
//mirabile
</pre>
