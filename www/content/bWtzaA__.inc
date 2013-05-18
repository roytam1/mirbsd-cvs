<!-- PageID: mksh -->
<small class="rcsid">$MirOS: www/content/bWtzaA__.inc,v 1.54 2006/09/07 14:31:13 tg Exp $</small>

<h1>mksh(1) R28</h1>
<p>This is the MirBSD&trade; Korn Shell, a more or less portable
 version of the pdksh derivate which comes, as an alternative to
 the default (and not used by anyone sane) C Shell, or (ancient)
 Bourne shell, with MirOS.</p>
<p>This website is always accessible via a redirection at <a
 href="http://mirbsd.de/mksh">http://mirbsd.de/mksh</a> and <a
 href="http://mirbsd.de/mksh-fornow">this page</a> is accessible
 even if the main webserver is unreachable again.</p>
<p>mksh is listed at <a href="http://directory.fsf.org/mksh.html">the
 FSF/UNESCO directory of Free Software</a>.</p>

<h2>Table of Contents</h2><ul>
 <li><a href="#clog">ChangeLog</a></li>
 <li><a href="#plans">future plans</a></li>
 <li><a href="#prefetch">Requirements</a></li>
 <li><a href="#fetch">Downloading</a></li>
 <li><a href="#extract">Unpacking</a></li>
 <li><a href="#build">Building</a>...</li>
 <li><a href="#buildbsd">on BSD</a></li>
 <li><a href="#buildsol">on Solaris</a></li>
 <li><a href="#buildgnu">on GNU and Mac OSX</a></li>
 <li><a href="#buildsfu">on Interix</a></li>
 <li><a href="#regress">Testsuite Results</a></li>
 <li><a href="#contrib">Additional information</a></li>
 <li><a href="#manual">Online manual page</a></li>
 <li><a href="#irc">Internet Relay Chat</a></li>
 <li><a href="#licence">Licence</a></li>
</ul>

<h2 id="clog">Recent Changes</h2>
<p>Changes in the current (unreleased) development version:</p><ul>
 <li>Begin porting mksh to the <a href="http://9fans.net/">Plan 9</a>
  ANSI'n'POSIX Environment (not finished)</li>
</ul>
<p>Upgrading to mksh R28 with these changes is highly recommended:</p><ul>
 <li>For these who build software as root, the regression testsuite
  has been adapted to pass when using a priviledgued shell. You have
  been warned, though. Do not compile software as root.</li>
 <li>Fix some more <tt>-Wchar-subscripts</tt> on NetBSD&reg;</li>
 <li>Adjust manual page to the fact that mksh can be used as
  <tt>/bin/sh</tt> although it's not specifically designed to</li>
 <li>Simplify mdoc/nroff macro load in manual page</li>
 <li>Add sample file: <tt>dot.mkshrc</tt></li>
 <li>Correct and enhance book citation list in the manual page</li>
 <li>Bring back the "version" editing command in both emacs and
  vi modes, at <tt>ESC ^V</tt> like AT&amp;T ksh93r+</li>
 <li>Fix typo which resulted in the wrong names for signals being
  printed (error codes were used instead) on GNU/Linux, Solaris
  and GNU/Cygwin. Ease changing signame/siglist sources.</li>
 <li>Some more code cleanup and redundancy removal</li>
 <li>Merge a few OpenBSD changes, yielding better multiline prompt
  support and textual improvements in the manual page</li>
 <li>Adjust $PS1 sizing, printing, and redrawal routines
  for mksh behaviour and single- and multiline prompts</li>
 <li>Unbreak build process on Cygwin, fix manpage generation</li>
 <li>For the AT&amp;T $PS1 hack (second char = CR), do not
  output the delimiting characters any more, even if they
  are printable &ndash; fixes platforms without non-printable
  characters (Interix, Cygwin) and prompt size calculation</li>
 <li>Calculate length of prompt in lines and columns-of-last-line
  instead of using some tricks to skip the beginning of the prompt,
  resulting in correct redrawing of prompts with ANSI colour codes</li>
 <li>Correct displaying of prompts spanning more than one line
  and/or with embedded newlines or carriage returns; correct
  documentation of $PS1 and the redraw editing command</li>
 <li>Change one of the testsuite "expected failure" tests from bug
  to feature &ndash; it might actually be required by make(1)</li>
 <li>Enable to bind key sequences which consist of the usual optional
  one or two pr&aelig;fices and the control character, as well as an
  optional trailing tilde (if the trailing character is not a tilde,
  it's processed as usual, but processing of the editing command is
  postponed until after the trailing character has been read)</li>
 <li>Bind the NetBSD&reg; wscons (vt220 / wsvt25), GNU screen and
  XFree86&reg; (xterm-xfree86) &quot;home&quot;, &quot;end&quot;
  and &quot;delete&quot; keys to ^A, ^E and ^D, respectively, except
  that &quot;delete&quot; does not act as logoff switch</li>
 <li>Correct <tt>Test.sh</tt> shebang line</li>
 <li>Make sure ^T is bound to 'transpose' as documented
  (bug spotted by hondza)</li>
 <li>Remove the 'stuff' and 'stuff-reset' editing commands</li>
 <li>Correct the manual page regarding the 'abort' command, its
  interaction with 'search-history' and how to exit the latter</li>
 <li>Bring back "set -o posix" turning off 'braceexpand'</li>
 <li>Mention IRC channel <tt>#mksh</tt>/Freenode in manual page</li>
 <li>Merge <tt>gensigs.sh</tt> into <tt>Build.sh</tt>, eliminating
  the need for <tt>$SHELL</tt> and making it more robust to broken
  user shells such as zsh, use the mksh just built for <tt>Test.sh</tt>;
  simplify CPPFLAGS and reduce size of generated table</li>
 <li>Run the signal name generator only if needed</li>
 <li>Use the -c option to GNU nroff, always</li>
 <li>Make the &quot;last command of a pipeline is executed in a
  subshell&quot; issue a dependable mksh feature</li>
 <li>Improve regression test comments and a few tests</li>
 <li>If $RANDOM is generated from arc4random(3), display at
  most 31 bits of it like nbsh(1), instead of only 15 bits.</li>
 <li>Rename the regression test script from Test.sh to test.sh</li>
 <li>Improve Build.sh output regarding other files than the binary</li>
 <li>Mention <tt>#ksh</tt>/Freenode in the manual page, since its
  founder (twkm) said it's okay and on-topic as well</li>
 <li>Fix persistent history, add regression test</li>
 <li>Check for arc4random(3) and arc4random_push(3) by using
  the compiler instead of hardcoding OSes which have and which
  don't, because that's not always true</li>
 <li>Fix some regression tests (based upon user feedback too)</li>
</ul>
<p>We recommended mksh <b>R27e</b> to be used:</p><ul>
 <li>Allow <tt>Test.sh</tt> to be passed parameters (-v)</li>
 <li>Fix all <tt>-Wchar-subscripts</tt> on Solaris/sparc64
  and NetBSD&reg;/alpha and remove <tt>-Wno-char-subscripts</tt>
  from Build.sh</li>
 <li>Correct date in version and manual page</li>
</ul>
<p>What became of mksh <b>R27d</b> in the meanwhile?</p><ul>
 <li>Changes for easier crossbuildability</li>
 <li>Honour $CPPFLAGS in gensigs.sh</li>
 <li>Only source ${ENV:-~/.mkshrc} for interactive (FTALKING) shells</li>
 <li>There's a chance that non-MirOS systems have arc4random_push(3)
  at some time in the future, so make it configurable.</li>
</ul>
<p>Featuring mksh <b>R27c</b> with these changes:</p><ul>
 <li>emacs-usemeta now behaves like vi-show8 (be careful with 0x80-0x9F)</li>
 <li>Portability cleanup and speed-up; refine pr&aelig;processor defns</li>
 <li>GNU groff compatible manual page</li>
 <li>Fixes for Solaris 10 support</li>
 <li>Add <tt>~/.mkshrc</tt> as $ENV feature (see manual page)</li>
 <li>Illustrate interactive shell tricks ($PS1) in manual page</li>
 <li>Enhance testsuite</li>
 <li>Incorporate some more code cleanup by OpenBSD</li>
 <li>Reference the O'Reilly books in the manual page</li>
 <li>R27c: fix packaging errors of previous versions</li>
</ul>
<p>Changes in the minor version <b>R26c</b>, relative to R26b:</p><ul>
 <li>Code cleanup by OpenBSD</li>
 <li>Documentation enhancements</li>
 <li>Fix gcc4 warnings in portable mksh</li>
</ul>
<p>Changes in the minor version <b>R26b</b>, relative to R26:</p><ul>
 <li>Makeup changes to copyright file (change comment leader)</li>
 <li>Sync licence with MirOS template (disclaimer changed a little)</li>
 <li>When building, generate a <tt>./Test.sh</tt> on the fly which
  can be used instead of having to copy and paste a long line to run
  the regression test suite (still no way to run ifs.sh as we cannot
  distribute it, though).</li>
 <li>Add a few programming tricks to the manual page</li>
 <li>Fix abuse of unquoted characters in the manual page</li>
 <li>(no actual source code changes)</li>
</ul>
<p>New major version <b>R26</b> changed this, relative to R25b:</p><ul>
 <li>Change the behaviour of <tt>\"</tt> in here documents to
  adhere SUSv3 (inspired by OpenBSD, most code by tg@)</li>
</ul>
<p>New minor version <b>R25b</b> contains these changes:</p><ul>
 <li><tt>arc4random_push(3)</tt> does not exist on older MirOS
  systems; fixes build on MirOS #7quater</li>
 <li>Add GNU Cygwin to the list of supported platforms</li>
</ul>
<p>New major version <b>R25</b> contains these changes:</p><ul>
 <li>Some manual page fixes and updates</li>
 <li>On window resizing, the COLUMNS and LINES variables are updated
  automatically, not only after the next command (from OpenBSD)</li>
 <li>Fix some redraw problem (from OpenBSD)</li>
 <li>Allow &lt; and &gt; for test and [, not only [[</li>
 <li>If an array index is out of bounds, tell which one (from OpenBSD)</li>
 <li>Add mknod(8) for pipes (user/root) and devices (root only) as a
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
 <li>use open(2) instead of creat(3), from OpenBSD</li>
 <li>fix order of includes</li>
 <li>some code simplification; no explicit LFS needed any more</li>
</ul>
<p>R24 is an <b>important bug fix</b> release and the new required
 minimum version to be installed for MirMake. Changes are:
</p><ul>
 <li>GNU/Cygwin is now supported but not officially tested</li>
 <li>DragonFly BSD is now supported and officially tested</li>
 <li>FreeBSD should work as a side effect of the above</li>
 <li>On NetBSD, arc4random(3)
  can now be used if it exists</li>
 <li>no longer look at argv[0] to determine if restricted shell</li>
 <li>changes to $EDITOR and $VISUAL no longer affect the current
  editing mode</li>
 <li>emacs on, emacs-usemeta off is now the default editing mode</li>
 <li>the special "posix" and "sh" modes are gone</li>
 <li>code, test suites and documentation have been cleaned up a little</li>
 <li>Korn's bizarre /dev/fd hack is now no longer supported</li>
 <li>undo fix for Debian PR #71256 which turned to be bogus and break make(1)</li>
 <li>fix compilation and invocation of test suite with whitespace in the
  pathnames for real, this time</li>
 <li>the distfile is now signed using gzsig(1)</li>
</ul>
<p>R23 comes with an overhauled build system providing more flags for
 easier configuration, a bug-fix if the relative path to $0 contained
 a space, and does not need h2ph(1) to
 build some headers any more. Also, the code has cleaned up a bit and
 some manual page glitches were corrected. Some of these changes
 originated by Han Boetes, a few came via the OpenBSD project.</p>
<p>R22d is the first version which works if source or build directory
 contain spaces in the pathname. It also allows building without
 bothering to pre-format the manual page.</p>
<p>R22c contains some compile time warning fixes on non-MirOS platforms.</p>
<p>R22b contains an important fix regarding the srand(3) initialisation logic and a
 portability fix for NetBSD.</p>
<p>R22 is the result of three different kinds of work: integrating diffs
 from Debian's pdksh package, as needed, including fixing bugs and of
 course testing and fixing docs; fixing the dreaded emacs-mode filename
 with brackets (hello AONE); much cleanup and polishing. Also, the new
 codebase has been tested on a fair number of systems now, with more to
 follow (maybe even new, currently unsupported, platforms).</p>
<p>R20b contains some minor arc4random and build fixes against R20.</p>
<p>R21 has been a three-way integration work from OpenBSD-current's ksh,
 MirOS-current's ksh and portable mksh R20. This is the first release
 to come without autoconf'd script; it is much smaller and installs
 both faster and easier. Several bugs have been fixed, the testsuite
 has been enhanced and the code was cleaned up largely. pdksh lookalikeness
 was largely dropped, and support for octal and sedecimal (hexadecadic)
 numbers via prefixing with <em>0</em> or <em>0x</em> has been added.
 <strong>This is an experimental release; it is not <i>yet</i> supported
 e.g. by <a href="/?MirMake">MirMake</a> or other tools</strong> but this
 will follow soon. MirbsdKsh R21 is to be the only shell available on
 MirOS #9.</p>
<p>R20 integrated an experimental bugfix from millert@openbsd and shuffled
 some code around. OS/2 support vanished, and the rest of the code shrank
 and was optimised. This is the first version since v1.11 to work on SFU
 (Interix) 3.5 as-is. The upgrade to R20 is <em>highly</em> recommended.
 Note: the mksh R20 distfile has changed from before Dec 14, 16:00.</p>
<p>R19 changes back a bugfix from R18 which caused a regression (from
 OpenBSD) and changed behaviour to match ksh88 on Solaris (from OpenBSD).</p>
<p>v1.18 (R18) fixes some core dump bugs and is a recommended update.</p>
<p>v1.17 comes out with the final MirOS licence template applied, but not
 yet OSI approved (it's not our fault though). There are regression fixes
 and bug fixes; IFS field splitting now works as documented. This version
 is a major improvement both over v1.16 and OpenBSD /bin/ksh, so please
 use it and report possible bugs.</p>
<p>v1.16 IS A BETA VERSION, use at your own risk. This version comes with
 a code cleanup session (for compilation with -Wall -Werror -W -pedantic
 and in preparation for doing an indent(1)
 whack over the source; any volunteers?) and some new features (with -T
 it spawns on a different tty than you're on - cool for single user mode)
 and code removed (the mailbox checking functionality, since everyone sane
 uses UW-IMAPD to access his MBX format folder using IMAPS, port 993, even
 to localhost). The code is also ANSIfied and protoised, in preparation for
 style(9) aka KNF.</p>
<p>There were no v1.13, v1.14, and v1.15 was never released as portable
 version. MirbsdKsh version numbers were pretty much RCS IDs at the
 time of writing this paragraph.</p>
<p>v1.12 fixes the manpages and minor stuff, as well as a signalling bug
 and the inability to build without gcc installed as gcc. It also
 adds installation hints for various operating systems.</p>
<p>v1.11 is a minor update to v1.10 with a few build and style fixes only.</p>

<h2 id="plans">Future Plans</h2><ul>
<li>bash-style multiline command line editing, as an option (the current
 horizontally scrolled one is finally (with R28) bug-free even with
 multiline and very long prompts optionally with embedded newlines,
 and more suitable for small terminals)</li>
<li>I'd like to switch the internal integer type to 64 bits
 signed (any takers?). This includes 2^64-1 (not 2^31-1) as
 maximum valid array index; typeset -i&lt;number&gt; is unsigned.</li>
<li>Adding <tt>goto</tt> and <tt>label</tt> keywords/commands.</li>
<li>Adding builtins <tt>realpath</tt>, <tt>fstat</tt>, <tt>lstat</tt>,
 <tt>traverse</tt>.</li>
</ul>

<h2 id="prefetch">Requirements</h2>

<p>Of course, your system must be operational for compiling
 programmes. You will need some sort of bourne compatible
 shell, compiler, assembler, linker (has not been tested with
 anything other than GCC), and associated tools.</p>

<p>ed(1) is the standard <tt>FCEDIT</tt> history editor and
 as such must be located in <tt>/bin/ed</tt> &ndash; note that
 if your GNU/Linux distribution (which usually don't include
 ed(1) in the standard installation, sadly) installs ed someplace
 else ask them to change it to the <tt>/bin/ed</tt> location <a
 href="http://www.pathname.com/fhs/pub/fhs-2.3.html#SPECIFICOPTIONS2">standardised
 by the FHS Guidelines</a> instead.</p>

<p>For running the regression test, you also need a suitably
 up-to-date perl(1) installation. We don't know how recent
 is up-to-date enough.</p>

<h2 id="fetch">Getting The Source</h2>

<p>The current version is <a
 href="http://www.mirbsd.org/MirOS/dist/mir/mksh/mksh-R28.cpio.gz">http://www.mirbsd.org/MirOS/dist/mir/mksh/mksh-R28.cpio.gz</a></p>
<ul>
 <li>Please use gzsig(1) to verify the integrity of the distfile instead!
  Hashes are only so you know which distfile you want.</li>
 <li>RMD160 (mksh-R28.cpio.gz) = 511926e621b73be23e0ae48fe1c09c2e1bfa7500</li>
 <li>3110135037 230291 /MirOS/dist/mir/mksh/mksh-R28.cpio.gz</li>
 <li>MD5 (mksh-R28.cpio.gz) = 1869f79961c365c65116974706a56c67</li>
</ul>

<h2>Installation</h2>
<p>If you ever sit in front of an unfriendly operating
 environment such as GNU, FreeBSD or the default Interix,
 first, do not use the sh or ksh which comes with them.
 Use the C shell instead. (Kidding? No.)
 Then, try wget, ftp(1) or
 fetch or GNU wget to retrieve above file;
 usually, one of them succeeds.
 If you must use a web browser for downloading the file,
 please note that most of them, seen on Mozilla&reg; and
 its derivates as well as Microsoft&reg; Internet Explorer,
 have a bug where the file is saved correctly
 as <em>mksh-R28.cpio.gz</em> but already decompressed.</p>

<h3 id="extract">Unpacking</h3>
<p>On decent systems, you can just use <tt>tar xzf mksh-R28.cpio.gz</tt>
 to extract the file. On quite damaged systems such as basically everything
 which is not MirOS or anything else with <a href="/?MirCpio">MirCpio</a>
 (paxmirabilis) or some other kind of paxtar, use <tt>gzip -dc
 mksh-R28.cpio.gz | cpio -mid</tt> or <tt>gzip -dc mksh-R28.cpio.gz |
 pax -r</tt> instead.</p>
<p>Of course, skip the gzip stage (use cat) or the 'z' flag
 if your browser already decompressed the file.</p>

<h3 id="build">Building</h3>
<p>You might have to take advantage of the AT&amp;T ksh, pdksh or GNU
 bash which comes with the operating system. With hard effort,
 Solaris <tt>/bin/sh</tt> could be made to suffice.</p>
<p>Different operating systems used to require different flags,
 but the syntax shown below should work on every system supported.</p>
<p>Manpage generation fails on systems which are not mdoc aware,
 such as Sun Solaris, or have no nroff(1)
 installed, such as MS Interix/Services for Unix. Use the <em>-r</em>
 command line option in that case.
 Stripping is done via the host's install(1)
 command's -s flag; if stripping during installation fails just use the
 <em>mksh</em> binary. On Solaris, use /usr/ucb/install instead.</p>
<p>The testsuite can be run by the dynamically generated <tt>Test.sh</tt>
 shell script which executes the first perl(1) found in your path to run
 the testsuite on the just built executable. Note that it is built in the
 current directory, not the source directory, if these are different.</p>
<h3 id="buildbsd">Most operating systems (BSD)</h3>
<ul>
 <li>cd mksh; env SHELL=/bin/sh sh Build.sh &amp;&amp; ./test.sh</li>
 <li>install -c -s -o root -g bin -m 555 mksh /bin/mksh</li>
 <li>echo /bin/mksh &gt;&gt;/etc/shells</li>
 <li>install -c -o root -g bin -m 444 mksh.cat1 /usr/share/man/cat1/mksh.0</li>
 <li>install -c -o root -g bin -m 644 dot.mkshrc /etc/skel/.mkshrc</li>
</ul>
<p style="margin-bottom:0px;">Attention: NetBSD 1.6.1/pmax (for example
 on a DECstation 5000/260) does not come with a <em>stdbool.h</em> &ndash;
 simply write one yourself:</p>
<div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;">
 <pre>
	typedef int bool;
	#define true 1
	#define false 0
 </pre>
</div><p style="margin-top:0px;">This is pretty simple but enough for mksh.</p>

<h3 id="buildsol">Solaris</h3>
<p>The Solaris port of mksh is sponsored by Der Verein <a
 href="http://www.trash.net/verein/">trash.net</a> which
 provides me a shell account on a Solaris 8 (Ultrasparc)
 box. Let me express a &quot;thank you&quot; to these guys;
 I suggest to support them because they are doing great
 things like Netzladen e.V. where I are involved in.</p>
<p>Tonnerre LOMBARD has made it possible to build and
 test (from time to time) mksh on a Solaris 10 box.</p>
<ul>
 <li>cd mksh; env SHELL=/bin/sh sh Build.sh -r &amp;&amp; ./test.sh</li>
 <li>/usr/ucb/install -c -s -o root -g bin -m 555 mksh ~/.bin/mksh</li>
</ul>
<p>If you get a <em>mksh</em> binary, install it to a place of your likes.
 Get a preformatted manual page from another operating system, or install
 nroff (or GNU groff) with the mdoc package to build it yourself.</p>

<h3 id="buildgnu">Mac OSX, GNU/Linux (and possibly others)</h3>
<ul>
 <li>cd mksh; env SHELL=/bin/sh sh Build.sh -r &amp;&amp; ./test.sh</li>
 <li>install -c -s -o root -g bin -m 555 mksh /bin/mksh</li>
 <li>echo /bin/mksh &gt;&gt;/etc/shells</li>
 <li>install -c -o root -g bin -m 444 dot.mkshrc /usr/share/doc/mksh/examples/</li>
 <li><em>and one of</em> (usually the first one on non-GNU/Linux)</li>
 <li>install -c -o root -g bin -m 444 mksh.1 /usr/share/man/man1/mksh.1</li>
 <li>install -c -o root -g bin -m 444 mksh.1 /usr/man/man1/mksh.1</li>
</ul>
<p>There is an mksh port for <a href="http://crux.nu/">Crux Linux</a>
 available at <a
 href="http://www.xs4all.nl/~hanb/software/crux/han/mksh/">http://www.xs4all.nl/~hanb/software/crux/han/mksh/</a> (thanks
 Han Boetes), and a Debian source package has been made by me
 and uploaded by Bastian "waldi" Blank as a sponsor; it is
 now part of Debian unstable and Debian testing. A Gentoo ebuild
 is available, written by Hanno Boeck, just "emerge mksh" to
 install it. mksh is also part of Fink thanks to Andreas "gecko2"
 Gockel, but called "mirbsdksh" (not mksh) there.</p>

<h3 id="buildsfu">Microsoft Services for Unix</h3>
<p>It is recommended to use the C shell instead of the
 Korn shell which comes with Interix/SFU 3.5, until
 you built the mirbsdksh successfully. (Also avoids ETXTBUSY.)
 Then, overwrite the stock ksh with mirbsdksh, it does
 not break (in contrast to NetBSD&reg; 1.5...), but you
 still might want to save your original /bin/ksh under
 /bin/msksh before you attempt to install mksh the first time:</p>
<ul>
 <li>(note: You must have administrative privilegues to replace the existing pdksh binary.)</li>
 <li>$ exec /bin/csh</li>
 <li>(close all other ksh instances)</li>
 <li>% mv /bin/ksh /bin/msksh</li>
 <li>% cd mksh</li>
 <li>% env SHELL=/bin/msksh /bin/msksh Build.sh -r</li>
 <li>% ./test.sh</li>
 <li>% install -c -s -m 555 mksh /bin/mksh</li>
 <li><em>(optionally)</em></li>
 <li>% cd /bin</li>
 <li>% rm -f sh ksh</li>
 <li>% ln mksh sh</li>
 <li>% ln mksh ksh</li>
 <li>% exec /bin/mksh -l</li>
</ul>
<p>You might want to get a preformatted man page from a
 different operating system. Interix does not come with
 a manual page formatter (but using <a href="/?MirMake">MirMake</a>,
 the portable make(1), you can build MirOS nroff(1)).</p>

<h2 id="regress">Official Testing</h2>

<p>The MirOS Project has tested mksh on the following operating systems,
 asked people to test, and hunted mksh down in these packaging systems:</p>
<ul>
 <li>mksh R28<ul>
  <li>MirOS BSD #9-stable (i386)</li>
  <li>MirOS BSD #7-stable (sparc)</li>
  <li>Solaris 8 (sun4u) SUNW,Ultra-60</li>
  <li>NetBSD 3.0_STABLE (i386)</li>
  <li>DragonFly BSD 1.3-Preview (i386)</li>
  <li>Debian GNU/Linux 3.1-testing 2.6.16-2-686 (i386)</li>
  <li>Debian GNU/Linux 3.1-testing 2.6.17-2-vserver-s390x (s390x)</li>
  <li>Debian GNU/Linux 3.1-stable 2.4.27-2-k7 (i386)</li>
  <li>Darwin 8.7.0 Mac OSX 10.4 (powerpc)</li>
  <li>Debian GNU/Linux 3.1-unstable (all architectures) &ndash; debianised</li>
  <li>OpenBSD 3.9 (sparc64) &ndash; via <a href="http://www.mirbsd.org/GBG/mksh-obsdport.tgz">contributed port</a></li>
  <li>CYGWIN_NT-5.0 1.5.19(0.150/4/2) 2006-01-20 13:28 (i386) &ndash; testsuite not run</li>
  <li>Interix SFU 3.5 (Windows&reg; 2000 Pro) SP-8.0.1969.1 (i386) &ndash; testsuite not run</li>
  <li>NetBSD 3.0 (mac68k) &ndash; tested by Jonathan "ciruZ" Schleifer</li>
  <li>Darwin 8.7.1 Mac OSX 10.4 (i386) &ndash; tested by Angelo Laub</li>
  <li>Solaris 8 (sun4m) SUNW,SPARCstation-5 &ndash; tested by Angelo Laub</li>
  <li>FreeWRT GNU/Linux SVN 2.4-BRCM (mipsel) &ndash; part of FreeWRT: testsuite not run</li>
  <li>FreeBSD (unknown) &ndash; part of FreeBSD Ports: not tried</li>
  <li>Gentoo GNU/Linux (i386 powerpc) &ndash; part of Portage: not tried</li>
 </ul></li>
 <li>mksh R28&szlig;<ul>
  <li>NetBSD 1.6.1 (pmax)</li>
   <!-- missing:
  <li>MirOS BSD #9-stable (sparc)</li>
  <li>CRUX GNU/Linux (i386) &ndash; not tested, via Han Boetes</li>
  <li>Solaris 10 (?) &ndash; tested by Tonnerre Lombard</li>
  <li>pkgsrc</li>
  <li>Mac OSX Panther (powerpc) &ndash; not tested, via Fink</li>
  <li>Plan 9 POSIX Environment</li>
   -->
 </ul></li>
 <li>mksh R27e<ul>
  <li>Debian GNU/Linux (i386, S/390): works (debianised)</li>
  <li>FreeWRT GNU/Linux (mipsel): works (package contained)</li>
  <li>MirOS #9 (i386, sparc): both as part of base installation and via ports</li>
  <li>Solaris 8 (sparc64): works (testsuite and usage on the shell
   account; please do not distribute the binaries)</li>
  <li>Generic GNU/Linux information: on most distributions, the testsuite
   succeeds without trouble after installing ed(1). We must build a dynamic
   executable because otherwise it dlopen(3)s at runtime the exact versions
   of the shared libraries available at build time and stuff might break, so
   do not distribute binaries, they are distribution- and buildhost-specific.
   Manual page generation usually succeeds with recent versions of GNU groff,
   but the place to install them is not unified.</li>
  <li>CRUX GNU/Linux (i386): works (package by Han Boetes who even uses mksh
   as /bin/sh and tells everyone to ditch bash)</li>
  <li>Available under FreeBSD as ports/shells/mksh</li>
  <li>Ubuntu GNU/Linux (amd64 i386 powerpc): part of &quot;edgy universe&quot;</li>
 </ul></li>
 <li>mksh R27d<ul>
  <li>There is a DragonFly pkgsrc in
   preparation, I wonder why they haven't been committed yet.</li>
  <li>Has been verified to build on NetBSD/alpha.</li>
 </ul></li>
 <li>mksh R27c<ul>
  <li>Solaris 10: Tonnerre says it passes test suite. His X login
   manager crashes when using mksh as default shell (also under
   GNU/Linux for him, can't reproduce), and scp(1) seems to fail.</li>
  <li>An <a href="http://pdb.finkproject.org/pdb/package.php/mirbsdksh">mksh
   package</a> exists in the Fink package manager for Mac OSX.</li>
 </ul></li>
 <li>mksh R26c<ul>
  <li>Windows&reg; 2000 / Interix (SFU 3.5): works, no testsuite (perl
   too old); can be used to replace system shell except for its I18N
   and Win32 features.</li>
  <li>NetBSD&reg; 1.6.1/pmax: I have replaced the standard shell
   with mksh with good success and only one testsuite failure
   in <em>heredoc-tmpfile-8</em>. On NetBSD&reg; 1.5/pmax this
   trick does not work because the system scripts are not compatible
   with the Korn shell.</li>
  <li>Gentoo GNU/Linux (ppc, x86): an official ebuild exists.</li>
 </ul></li>
 <li>mksh R25b<ul>
  <li>MirOS #7: works well</li>
  <li>GNU/Cygwin: builds, testsuite succeeds, basic usage.</li>
 </ul></li>
 <li>mksh R25<ul>
  <li>NetBSD&reg; 2.0.2/i386: works well</li>
  <li>DragonFly BSD: Portable mksh builds; the test suite succeeds.</li>
  <li>Mac OSX Tiger: The testsuite works, and it can be used to play around.
   Apple does not install the tools needed for a static build.</li>
  <li>Nexenta OS (i386): part of &quot;elatte&quot; GNU/Solaris</li>
  <li>Ubuntu GNU/Linux (amd64 i386 powerpc): part of &quot;dapper universe&quot;</li>
 </ul></li>
 <li>mksh R24<ul>
  <li>Mac OSX Panther: I don't see a difference to Tiger.</li>
 </ul></li>
</ul>

<h2 id="contrib">Tab Completion, and the Prompt</h2>

<h3>Official samples</h3>

<p>mksh R28 and up come with a sample dot.mkshrc file.
 For more ideas what one can do with <strong>mksh</strong> I recommend
 one to look at both the -rHEAD revision and the revision history of
 the files shown below.</p>

<h3>More (outdated) hints</h3>

<p>Tab Completion is enabled by default.
 You might want to have a look at <a
 href="http://cvs.mirbsd.de/contrib/samples/etc_profile">http://cvs.mirbsd.de/contrib/samples/etc_profile</a>
 (or its origin <a href="http://cvs.mirbsd.de/src/etc/profile">http://cvs.mirbsd.de/src/etc/profile</a>)
 for an even better pre-configured mksh environment.</p>
<p>This especially comes handy for people used to the
 GNU bash which want their CWD, user/hostname etc.
 in their $PS1 prompt.</p>
<p><em>etc_profile</em> from above now also switches to mksh by default,
 so you need not to rely on <em>chsh -s</em> and root to add mksh to
 <tt>/etc/shells</tt>. Define DONTWANTMKSH=1 in ${HOME}/.profile.preinit
 to disable this behaviour.</p>
<p>(Note that <em>etc_profile</em> is outdated and no longer maintained.)</p>

<h2>The history file</h2>
<p>Since a few versions, mksh does not write a history file by default
 any more. To enable writing of a persistent history (not clashing with
 other shells' history files), execute the following command:</p>
<pre>echo 'case $KSH_VERSION in *MIRBSD*) export HISTFILE=~/.mksh-history ;; esac' &gt;&gt;~/.profile</pre>
<p>If you don't want mksh to overwrite your other shell's history file
 with its own format...</p>
<pre>echo '[ -n "$KSH_VERSION" ] &amp;&amp; unset HISTFILE' &gt;&gt;~/.profile</pre>

<h2>Porting</h2>
<p>Contact the MirOS discussion mailing list, either via
 eMail, or via <a href="news:gmane.os.miros.general">news:gmane.os.miros.general</a>
 on news.gmane.org, if you are interested in having a new target supported.
 You're also welcome on <a href="#irc">IRC</a>.</p>

<h2 id="manual">The Manual Page</h2>
<p>Online manpage: mksh(1) or <a
 href="http://www.mirbsd.org/GBG/mksh.pdf">mksh.pdf</a></p>

<h2 id="irc">Internet Relay Chat</h2>

<p>The official portable mksh discussion channel is <tt>#mksh</tt> in
 the Freenode IRC network (irc.freenode.net:6667 non-SSL). However,
 you will find more activity in the channel <tt>#mirbsd</tt> in the
 Freeforge IRC network (irc.mirbsd.org:6668 SSL, irc.mirbsd.org:6666
 non-SSL) instead, where mksh discussions are on topic as well. For
 generic Korn Shell discussion (AT&amp;T and mksh both on-topic), go
 to <tt>#ksh</tt> on Freenode (see above).</p>

<p>Read our <a href="/?irc">MirOS IRC page</a> for detailled information
 about the networks.</p>

<h1 id="licence">Licence</h1>
<p>MirbsdKsh as a whole is licenced under the BSD/MIT/X11-style <a
 href="http://mirbsd.de/MirOS-Licence">MirOS licence</a> with advertising
 clause; the file <em>alloc.c</em> which has been written by OpenBSD's Marc
 Espie and comes under a 2-clause UCB-style licence. On some operating
 systems, additional files under a 3-clause UCB licence, or the <a
 href="http://mirbsd.de/ISC-Licence">ISC licence</a> may be built.</p>
<p>Read the <a href="/cvs.cgi/src/bin/mksh/copyright?rev=HEAD">full
 terms</a> in CVSweb.</p>
<p>pdksh originally was public domain, with a few exceptions,
 but these files are not part of mksh R21 or higher. The
 mksh author (mirabilos) acknowledges the contributions of
 these people who dedicated pdksh to the public, and asserts
 a collective copyright on the code.</p>
<p>The MirBSD Korn shell is not related to the <a
 href="http://www.kornshell.com/">original Korn Shell</a>.</p>
