<small class="rcsid">$MirOS: www/content/bWtzaA__.inc,v 1.9 2005/10/25 22:09:21 tg Exp $</small>

<p>Notice: this page has been auto-converted from the MirWiki
 and is not yet valid XHTML/1.1. We are sorry for the inconvenience.</p>

<h1>mksh R25</h1>
<p>
 This is a more or less portable version of the pdksh derivate
 Korn shell which comes, as an alternative to the default (and
 not used by anyone sane) C Shell, with MirOS.
</p>

<h3>Recent Changes</h3>
<p>Changes in the current development version:</p><ul>
 <li>(change revoked) <!-- On MirOS, integrate <a href="/man1/printf.htm">printf(1)</a>
  as shell builtin, mostly to speed up libtool and stuff
  (currently broken, thus disabled again). --></li>
</ul>
<p>New major version <b>R25</b> contains these changes:</p><ul>
 <li>Some manual page fixes and updates</li>
 <li>On window resizing, the COLUMNS and LINES variables are updated
  automatically, not only after the next command (from OpenBSD)</li>
 <li>Fix some redraw problem (from OpenBSD)</li>
 <li>Allow &lt; and &gt; for test and [, not only [[</li>
 <li>If an array index is out of bounds, tell which one (from OpenBSD)</li>
 <li>Add mknod(1) for pipes (user/root) and devices (root only) as a
  shell builtin &ndash; idea and some of the code from OpenBSD</li>
 <li>Improve compatibility with Solaris, GNU/Linux, Darwin, Interix</li>
 <li>Prevent redefinition of __rcsid string on systems without __RCSID
  macro (found by Han Boetes)</li>
 <li>Remove the need to manually specify -d on some OSes which need it</li>
 <li>Add a compiler flag to reduce some spurious Solaris-only warnings</li>
</ul>
<p>R24c is another clean-up release, with no change to KSH_VERSION.</p><ul>
 <li>Document stance on quoting policy in here documents</li>
 <li>More fixes for GCC 4 warnings</li>
</ul>
<p>R24b is a minor clean-up relase, recommended especially on Darwin.</p><ul>
 <li>please GCC 4 with the usual crazy set of warning flags</li>
 <li>remove 'version' editor binding and remap emacs ^V to quote-meta ('literal')</li>
 <li>use <a href="/man2/open.htm">open(2)</a> instead of <a href="/man3/creat.htm">creat(3)</a>, from OpenBSD</li>
 <li>fix order of includes</li>
 <li>some code simplification; no explicit LFS needed any more</li>
</ul>
<p>R24 is an <b>important bug fix</b> release and the new required
 minimum version to be installed for MirMake. Changes are:
</p><ul>
 <li>GNU/Cygwin is now supported but not officially tested</li>
 <li>DragonFly BSD is now supported and officially tested</li>
 <li>FreeBSD should work as a side effect of the above</li>
 <li>On NetBSD, <a href="/man3/arc4random.htm">arc4random(3)</a> can now be used if it exists</li>
 <li>no longer look at argv[0] to determine if restricted shell</li>
 <li>changes to $EDITOR and $VISUAL no longer affect the current editing mode</li>
 <li>emacs on, emacs-usemeta off is now the default editing mode</li>
 <li>the special "posix" and "sh" modes are gone</li>
 <li>code, test suites and documentation have been cleaned up a little</li>
 <li>Korn's bizarre /dev/fd hack is now no longer supported</li>
 <li>undo fix for Debian PR #71256 which turned to be bogus and break <a href="/man1/make.htm">make(1)</a></li>
 <li>fix compilation and invocation of test suite with whitespace in the pathnames for real, this time</li>
 <li>the distfile is now signed using <a href="/man1/gzsig.htm">gzsig(1)</a></li>
</ul>
<p>
R23 comes with an overhauled build system providing more flags for
easier configuration, a bug-fix if the relative path to $0 contained
a space, and does not need <a href="/man1/h2ph.htm">h2ph(1)</a> to build some headers any more.
Also, the code has cleaned up a bit and some manual page glitches
were corrected. Some of these changes originated by HanBoetes,
a few came via the OpenBSD project.
<p>
R22d is the first version which works if source or build directory
contain spaces in the pathname. It also allows building without
bothering to pre-format the manual page.
<p>
R22c contains some compile time warning fixes on non-MirOS platforms.
<p>
R22b contains an important fix regarding the <a href="/man3/srand.htm">srand(3)</a> initialisation
logic and a portability fix for NetBSD.
<p>
R22 is the result of three different kinds of work: integrating diffs
from Debian's pdksh package, as needed, including fixing bugs and of
course testing and fixing docs; fixing the dreaded emacs-mode filename
with brackets (hello AONE); much cleanup and polishing. Also, the new
codebase has been tested on a fair number of systems now, with more to
follow (maybe even new, currently unsupported, platforms).
<p>
R20b contains some minor arc4random and build fixes against R20.
<p>
R21 has been a three-way integration work from OpenBSD-current's ksh,
MirOS-current's ksh and portable mksh R20. This is the first release
to come without autoconf'd script; it is much smaller and installs
both faster and easier. Several bugs have been fixed, the testsuite
has been enhanced and the code was cleaned up largely. pdksh lookalikeness
was largely dropped, and support for octal and sedecimal (hexadecadic)
numbers via prefixing with <em>0</em> or <em>0x</em> has been added. &lt;b&gt;This is
an experimental release; it is not <i>yet</i> supported e.g. by <a href="wiki.cgi?MirMake" class=wikipagelink>MirMake</a>
or other tools&lt;/b&gt; but this will follow soon. <a href="wiki.cgi?MirbsdKsh" class=wikipagelink>MirbsdKsh</a> R21 is to be
the only shell available on <a href="wiki.cgi?MirOS" class=wikipagelink>MirOS</a> #9.
<p>
R20 integrated an experimental bugfix from millert@openbsd and shuffled
some code around. OS/2 support vanished, and the rest of the code shrank
and was optimised. This is the first version since v1.11 to work on SFU
(Interix) 3.5 as-is. The upgrade to R20 is <em>highly</em> recommended.
Note: the mksh R20 distfile has changed from before Dec 14, 16:00.
<p>
R19 changes back a bugfix from R18 which caused a regression (from
<a href="wiki.cgi?OpenBSD" class=wikipagelink>OpenBSD</a>) and changed behaviour to match ksh88 on Solaris (from <a href="wiki.cgi?OpenBSD" class=wikipagelink>OpenBSD</a>).
<p>
v1.18 (R18) fixes some core dump bugs and is a recommended update.
<p>
v1.17 comes out with the final <a href="wiki.cgi?MirOS" class=wikipagelink>MirOS</a> licence template applied, but not
yet OSI approved (it's not our fault though). There are regression fixes
and bug fixes; IFS field splitting now works as documented. This version
is a major improvement both over v1.16 and <a href="wiki.cgi?OpenBSD" class=wikipagelink>OpenBSD</a> /bin/ksh, so please
use it and report possible bugs.
<p>
v1.16 IS A BETA VERSION, use at your own risk. This version comes with
a code cleanup session (for compilation with -Wall -Werror -W -pedantic
and in preparation for doing an <a href="/man1/indent.htm">indent(1)</a> whack over the source; any
volunteers?) and some new features (with -T it spawns on a different
tty than you're on - cool for single user mode) and code removed (the
mailbox checking functionality, since everyone sane uses UW-IMAPD to
access his MBX format folder using IMAPS, port 993, even to localhost).
The code is also ANSIfied and protoised, in preparation for <a href="/man9/style.htm">style(9)</a>
aka KNF.
<p>
There were no v1.13, v1.14, and v1.15 was never released as portable
version. <a href="wiki.cgi?MirbsdKsh" class=wikipagelink>MirbsdKsh</a> version numbers were pretty much RCS IDs at the
time of writing this paragraph.
<p>
v1.12 fixes the manpages and minor stuff, as well as a signalling bug
and the inability to build without gcc installed as gcc. It also
adds installation hints for various operating systems.
<p>
v1.11 is a minor update to v1.10 with a few build and style fixes only.
<p>
<DL >
<dt><dd> Plans
</DL>
I'd like to switch the internal
integer type to 64 bits signed (any takers?).
<p>
<h2>Getting The Source</h2>

<p>
The current version is
<ul>
 <li><a href="https://mirbsd.mirsolutions.de:445/MirOS/dist/mir/mksh/mksh-R25.cpio.gz">https://mirbsd.mirsolutions.de:445/MirOS/dist/mir/mksh/mksh-R25.cpio.gz</a></li>
</ul>
<p>
<ul>
 <li>Please use <a href="/man1/gzsig.htm">gzsig(1)</a> to verify
  the integrity of the distfile instead!</li>
 <li>RMD160 (mksh-R25.cpio.gz) = 88f17da12b4a634fab40acee7105671ead3dc4d8</li>
 <li>4110975346 228743 /MirOS/dist/mir/mksh/mksh-R25.cpio.gz</li>
 <li>MD5 (mksh-R25.cpio.gz) = ec9095ee279225fed82523044803bc32</li>
</ul>
<p>
If you ever sit in front of an unfriendly operating
environment such as FreeBSD<a href="wiki.cgi?action=edit&id=FreeBSD" class=wikipageedit>?</a> or the default Interix,
first, do not use the sh or ksh which comes with them.
Use the C shell instead. (Kidding? No.)
Then, try wget, <a href="/man1/ftp.htm">ftp(1)</a> or fetch or GNU wget to retrieve above file;
usually, one of them succeeds.
If you must use a web browser for downloading the file,
please note that most of them, seen on Mozilla(TM) and
its derivates as well as Microsoft Internet Explorer,
have a bug where the file is saved correctly
as <em>mksh-R25.cpio.gz</em> but already decompressed.
<p>
<h2>Unpacking</h2>

<p>
On decent systems, you can just use
<ul>
 <li>tar xzf mksh-R25.cpio.gz</li>
</ul>
to extract the file.
<p>
On quite damaged systems such as everything which is not
<a href="wiki.cgi?MirOS" class=wikipagelink>MirOS</a> or anything else with <a href="wiki.cgi?MirCpio" class=wikipagelink>MirCpio</a> (paxmirabilis), use
<ul>
 <li>gzip -dc mksh-R25.cpio.gz | cpio -mid</li>
</ul>
<p>
Of course, skip the gzip stage (use cat) or the 'z' flag
if your browser already decompressed the file.
<p>
<h2>Building</h2>

<p>
You might have to take advantage of the AT&amp;T ksh, pdksh or GNU
bash which comes with the operating system. With hard effort,
Solaris /bin/sh could be made to suffice.
<p>
Different operating systems require different flags.
<p>
Manpage generation fails on systems which are not mdoc aware,
such as Sun Solaris, or have no <a href="/man1/nroff.htm">nroff(1)</a> installed, such as
MS Interix/Services<a href="wiki.cgi?action=edit&id=MirbsdKsh/Services" class=wikipageedit>?</a> for Unix. Use the <em>-r</em> command line option
in that case.
Stripping is done via the host's <a href="/man1/install.htm">install(1)</a> command's -s flag;
if stripping during installation fails just use the <em>mksh</em> binary.
On Solaris, use /usr/ucb/install instead.
<p>
<h3><a href="wiki.cgi?MirOS" class=wikipagelink>MirOS</a>, <a href="wiki.cgi?OpenBSD" class=wikipagelink>OpenBSD</a>, <a href="wiki.cgi?NetBSD" class=wikipagelink>NetBSD</a>, <a href="wiki.cgi?DragonFly" class=wikipagelink>DragonFly</a>, FreeBSD<a href="wiki.cgi?action=edit&id=FreeBSD" class=wikipageedit>?</a></h3>

<p>
<ul>
 <li>cd mksh; sh Build.sh</li>
 <li>install -c -s -o root -g bin -m 555 mksh /bin/mksh</li>
 <li>echo /bin/mksh &gt;&gt;/etc/shells</li>
 <li>install -c -o root -g bin -m 444 mksh.cat1 /usr/share/man/cat1/mksh.0</li>
</ul>
<p>
Attention: <a href="wiki.cgi?NetBSD" class=wikipagelink>NetBSD</a> 1.6.1/pmax (on a DECstation 5000/260) does not
come with a <em>stdbool.h</em> - simply write one yourself:
<p>
<PRE >
 typedef int bool;
 #define true 1
 #define false 0
</PRE>
<p>
This is pretty dead simple but enough for mksh.
<p>
<h3>Solaris</h3>

<p>
<ul>
 <li>cd mksh; sh Build.sh -d -r</li>
 <li>/usr/ucb/install -c -s -o root -g bin -m 555 mksh ~/.bin/mksh</li>
</ul>
<p>
If you get a <em>mksh</em> binary, install it to a place of your likes.
Get a preformatted manual page from another operating system.
<p>
<h3>GNU/Linux (and possibly others)</h3>

<p>
<ul>
 <li>cd mksh; sh Build.sh -d -r</li>
 <li>install -c -s -o root -g bin -m 555 mksh /bin/mksh</li>
 <li>echo /bin/mksh &gt;&gt;/etc/shells</li>
 <li>install -c -o root -g bin -m 444 mksh.1 /usr/share/man/man1/mksh.1</li>
 <li>(some systems use /usr/man/man1/)</li>
 <li>(update: pretty much <em>all</em> systems use /usr/man/man1/ - has GNU/Linux<a href="wiki.cgi?action=edit&id=MirbsdKsh/Linux" class=wikipageedit>?</a> world gone totally insane? GNU itself uses /man/man1/ or /share/man/man1/ ...?)</li>
 <li>install -c -o root -g bin -m 444 mksh.1 /usr/man/man1/mksh.1</li>
</ul>
<p>
There is an mksh port for Crux - <a href="http://crux.nu/">http://crux.nu/</a> - available
at <a href="http://www.xs4all.nl/~hanb/software/crux/han/mksh/">http://www.xs4all.nl/~hanb/software/crux/han/mksh/</a> (thanks
Han Boetes), and a Debian source package has been made by me
and uploaded by Bastian "waldi" Blank as a sponsor; it was
finally accepted into Debian unstable, soon to be in Debian
testing. A Gentoo ebuild is available, written by Hanno Boeck,
just "emerge mksh" to install it.
<p>
<h3>Mac OSX</h3>

<p>
<ul>
 <li>cd mksh; bash Build.sh -d -r</li>
 <li>install -c -s -o root -g wheel -m 555 mksh /bin/mksh</li>
 <li>echo /bin/mksh &gt;&gt;/etc/shells</li>
 <li>install -c -o root -g wheel -m 444 mksh.1 /usr/share/man/man1/mksh.1</li>
</ul>
<p>
Older version only.
Binaries: <a href="https://users.mirsolutions.de:446/~tg/binaries/mksh-1.17-macbin.tgz">https://users.mirsolutions.de:446/~tg/binaries/mksh-1.17-macbin.tgz</a>
mksh has even made its way into the Fink package management system.
<p>
<h3>Microsoft Services for Unix</h3>

<p>
It is recommended to use the C shell instead of the
Korn shell which comes with Interix/SFU 3.5, until
you built the mirbsdksh successfully.
Then, overwrite the stock ksh with mirbsdksh, it does
not break (in contrast to <a href="wiki.cgi?NetBSD" class=wikipagelink>NetBSD</a>(R) 1.5...), but you
still might want to save your original /bin/ksh under
/bin/msksh before you attempt to install mksh the first time.
<p>
<ul>
 <li>(note: You must have administrative privilegues to replace the existing pdksh binary.)</li>
 <li>$ exec /bin/csh</li>
 <li>(close all other ksh instances)</li>
 <li>% mv /bin/ksh /bin/msksh</li>
 <li>% cd mksh</li>
 <li>% env SHELL=/bin/msksh /bin/msksh Build.sh -r</li>
 <li>% install -c -s -m 555 mksh /bin/mksh</li>
 <li>% cd /bin</li>
 <li>% rm -f sh ksh</li>
 <li>% ln mksh sh</li>
 <li>% ln mksh ksh</li>
 <li>% exec /bin/mksh -l</li>
</ul>
<p>
You might want to get a preformatted man page from a
different operating system. Interix does not come with
a manual page formatter. Or use the binary package.
<p>
(Older) Binaries: <a href="https://users.mirsolutions.de:446/~tg/binaries/mksh-R20-winbin.tgz">https://users.mirsolutions.de:446/~tg/binaries/mksh-R20-winbin.tgz</a>
<p>
<h2>Official Testing</h2>

<p>
The <a href="wiki.cgi?MirOS" class=wikipagelink>MirOS</a> Project has tested mirbsdksh on the following operating systems:
<p>
<h3><a href="wiki.cgi?MirOS" class=wikipagelink>MirOS</a></h3>

<p>
<DL >
<dt><dd> mksh R25
</DL>
Obviously works, as part of the base install.
<p>
The portable mksh also works through its test suite and
some basic usability tests.
<p>
<h3><a href="wiki.cgi?NetBSD" class=wikipagelink>NetBSD</a></h3>

<p>
<DL >
<dt><dd> mksh R25
</DL>
I have replaced the standard shell on <a href="wiki.cgi?NetBSD" class=wikipagelink>NetBSD</a> 1.6.1/pmax
with mksh with good success and only one testsuite failure
in <em>heredoc-tmpfile-8</em>. On <a href="wiki.cgi?NetBSD" class=wikipagelink>NetBSD</a> 1.5/pmax it does
not work because the system scripts are not compatible
with the Korn shell. A NetBSD&reg; 2.0.2/i386 system it works well too.
<p>
<h3><a href="wiki.cgi?DragonFly" class=wikipagelink>DragonFly</a> BSD</h3>

<p>
<DL >
<dt><dd> mksh R25
</DL>
Portable mksh builds; the test suite succeeds.
<p>
<h3>GNU/Linux</h3>

<p>
<DL >
<dt><dd> mksh R25
</DL>
The test suite succeeds. Basic
command line usage works as well. The binary is not statically
linked, and there is no standard on where to install the man
page. Do not distribute the binaries outside your distribution's
package management system.
<p>
<h3>Solaris</h3>

<p>
<DL >
<dt><dd> mksh R25
</DL>
The testsuite works, and I'm using it on my shell account.
Please do not redistribute the binaries either; they are
dynamically linked.
<p>
<h3>Mac OSX</h3>

<p>
<DL >
<dt><dd> mksh R25
</DL>
The testsuite works, and it can be used to play around.
Apple does not install the tools needed for a static build.
<p>
<h3>Interix</h3>

<p>
<DL >
<dt><dd> mksh R25
</DL>
Works unmodified, better than system shell, good success.
<p>
<h3>GNU/Cygwin<a href="wiki.cgi?action=edit&id=MirbsdKsh/Cygwin" class=wikipageedit>?</a></h3>

<p>
<DL >
<dt><dd> mksh R24beta
</DL>
I heard it compiles. I could not test mksh R25 due to lack of a
shell account on a box with Cygwin installed.
<p>
<h2>Tab Completion, and the Prompt</h2>

<p>
Tab Completion is enabled by default.
You might want to have a look at
<ul>
 <li><a href="http://mirbsd.mirsolutions.de/cvs.cgi/contrib/samples/etc_profile">http://mirbsd.mirsolutions.de/cvs.cgi/contrib/samples/etc_profile</a></li>
</ul>
(or its source)
<ul>
 <li><a href="http://mirbsd.mirsolutions.de/cvs.cgi/src/etc/profile">http://mirbsd.mirsolutions.de/cvs.cgi/src/etc/profile</a></li>
</ul>
for an even better pre-configured mksh environment.
<p>
This especially comes handy for people used to the
GNU bash, which want their CWD, user/hostname etc.
in their $PS1 prompt.
<p>
<em>etc_profile</em> from above now also switches to mksh by default,
so you need not to rely on <em>chsh -s</em> and root to add mksh to
/etc/shells. Define DONTWANTMKSH=1 in ${HOME}/.profile.preinit
to disable this behaviour.
<p>
<h2>The history file</h2>
<p>If you don't want mksh to overwrite your other shell's history file
 with its own format...</p>
<pre>echo '[ -n "$KSH_VERSION" ] &amp;&amp; unset HISTFILE' &gt;&gt;~/.profile</pre>
<h2>The Manual Page</h2>

<p>
Online manpage: <a href="/man1/mksh.htm">mksh(1)</a>
<p>
<h2>Porting</h2>

<p>
Contact the <a href="wiki.cgi?MirOS" class=wikipagelink>MirOS</a> discussion mailing list, either via
eMail, or via <a href="news:gmane.os.miros.general">news:gmane.os.miros.general</a> on news.gmane.org,
if you are interested in having a new target supported.
<p>
<h1>Licence</h1>

<p>
<a href="wiki.cgi?MirbsdKsh" class=wikipagelink>MirbsdKsh</a> as a whole is licenced under the same terms as
shown in the <a href="wiki.cgi?LicenceTemplate" class=wikipagelink>LicenceTemplate</a> page, with the exception of
the file <em>alloc.c</em> which has been written by Marc Espie
from <a href="wiki.cgi?OpenBSD" class=wikipagelink>OpenBSD</a> and comes with a 2-clause UCB-style licence.
<p>
pdksh originally was public domain, with a few exceptions,
but these files are not part of mksh R21 or higher. The
mksh author (<a href="wiki.cgi?MirAbile" class=wikipagelink>MirAbile</a>) acknowledges the contributions of
these people who dedicated pdksh to the public, and asserts
a collective copyright on the code.
<p>
<a href="wiki.cgi?MirbsdKsh" class=wikipagelink>MirbsdKsh</a> comes with <em>strlfun.c</em> which is under the ISC
Licence aka OpenBSDLicenceTemplate<a href="wiki.cgi?action=edit&id=OpenBSDLicenceTemplate" class=wikipageedit>?</a>. This file is only a
'shouldbeinlibc' library for brain-dead GNU libc systems. <em>setmode.c</em> also comes under a different licence &ndash; a 3-clause UCB licence.
<p>
This all is documented in the file <em>copyright</em> in the
distfile, too.
</div>
