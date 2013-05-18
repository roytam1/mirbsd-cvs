<!-- PageID: mksh -->
<small class="rcsid">$MirOS: www/content/bWtzaA__.inc,v 1.111 2007/06/04 22:03:18 tg Exp $</small>

<h1>mksh(1) R29</h1>
<p>This is the MirBSD&trade; Korn Shell, a more or less portable
 version of the pdksh derivate which comes, as an alternative to
 the default (and not used by anyone sane) C Shell, or (ancient)
 Bourne shell, with MirOS.</p>
<p>Go directly to the <a href="#toc">Table of Contents</a>.</p>
<p>This website is always accessible via a redirection at <a
 href="http://mirbsd.de/mksh">http://mirbsd.de/mksh</a> and <a
 href="http://mirbsd.de/mksh-fornow">this page</a> is accessible
 even if the main webserver is unreachable again.</p>
<p>mksh is listed at <a href="http://directory.fsf.org/mksh.html">the
 FSF/UNESCO directory of Free Software</a>.</p>

<h2 id="toc">Table of Contents</h2><ul>
 <li><a href="#clog">ChangeLog</a></li>
 <li><a href="#vsn">on version numbers</a> – for packagers</li>
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

<h2>Some notes for OpenBSD users who stumble upon this site...</h2>
<p>I'd like to state a few things, now that mksh has been brought
 up on misc@openbsd.org: It's an actively developed pdksh-based
 korn shell with <strong>all</strong> improvements from the OpenBSD
 /bin/ksh <em>except</em> "bash-like $PS1" &ndash; but whoever
 really needs it can patch it in himself, I prefer to convert the
 GNU bash (bloated-again shell) prompts to Korn shell syntax though.
 mksh R29 <!-- , which has just been tagged today (March 5th), --> is a new
 milestone in development &ndash; see below. The most user-visible
 part is support for UTF-8 command line editing without the need to
 pull in full wchar_t, iconv, locale, I18N, etc. bloat &ndash; that's
 why it even works on non-locale-aware operating systems like OpenBSD.
 It also features an autoconf-like build script without all the well
 known annoyances of the GNU tools, compiles cleanly even with some
 really crazy GCC warning options, is const-clean, and contains many
 bug fixes over both pdksh and the OpenBSD ksh. Also, certain limits
 have been removed, e.g. arrays can have (almost &ndash; due to the
 size of the internal index type only 2<sup>31</sup>-1) members. It's
 still smaller and much faster than comparable shells, and there's a
 method to make it even smaller (run the build script with $CPPFLAGS
 defined to some subset of -DMKSH_SMALL (as small as possible),
 -DMKSH_ASSUME_UTF8 (don't look for setlocale(3) and nl_langinfo(CODESET)
 but always enable the utf-8 command line editing mode), -DMKSH_NEED_MKNOD
 (integrate mknod(8) in mksh even if compiled with -DMKSH_SMALL, e.g.
 for the install floppy), -DMKSH_NOPWNAM (do not link in the calls to
 getpwnam(3) so that mksh can be built statically on OSes with PAM).
 There's also support for <tt>~/.mkshrc</tt>, which is sourced by all
 interactive shells, login shell or not, and a sample <tt>dot.mkshrc</tt>
 with a nice $PS1 is included. mksh(1) is licenced under the terms of
 the MirOS licence, which is very similar to the historic permission
 clause and the MIT licence; alloc.c and setmode.c (not needed for BSD)
 are 2/3-clause BSD, strlcpy.c is ISC. But mksh is not Public Domain
 (mostly because European authors cannot dedicate their work into PD
 before they're long dead). This webpage is about to be rewritten.
 mksh is already part of many porting systems, i.e. FreeBSD&reg; ports,
 NetBSD&reg; pkgsrc&reg;, FreeWRT, Debian, Ubuntu, Gentoo, Crux (via
 Han Boetes), OpenSuSE Build Service, Sourcemage, Fink, some chinese
 GNU/Linux distribution, &#8230; and compiles under many obscure OSes,
 e.g. Interix (SFU / Windows NT POSIX subsystem), Cygwin, Solaris,
 GNU/HURD, GNU/kFreeBSD, all BSDs, old, modern and embedded GNU/Linux,
 Mac OSX, and soon on Minix 3, Plan 9 and some commercial *nixes.</p>
<p>Read the manual page &ndash; HTML: mksh(1) &ndash; PDF: <a
 href="http://www.mirbsd.org/GBG/mksh.pdf">MirBSD Korn Shell</a></p>
<p>If you need help converting your $PS1, join <tt>#!/bin/mksh</tt>
 (yes, that's really the name of the channel, no kidding) on Freenode.</p>

<h2 id="clog">Recent Changes</h2>
<p>Changes in the current (unreleased) development version:</p><ul>
 <li>Begin porting mksh to the <a href="http://9fans.net/">Plan 9</a>
  ANSI'n'POSIX Environment (not finished)</li>
 <li>Plan porting mksh to <a href="http://www.minix3.org/">Minix 3</a>
  (not finished yet)</li>
 <li>Begin work on building on Solaris with Sun's compiler (contributed
  by Jupp “cnuke” Söntgen) – not public, not finished yet</li>
 <li>No longer build a statically linked shell by default; do not try,
  do not provide any means; user has to use LDFLAGS instead.</li>
 <li>Remove some probably dead mirtoconf checks</li>
 <li>Remove commented out <tt>-fwhole-program --combine</tt> check and
  still active <tt>-fno-tree-vrp</tt> bug workaround thing, the latter
  because the bug seems to only appear for functions that also exist as
  a builtin (which was declared with the nonnull attribute)</li>
 <li>Fix a long-standing typo, 10x moritz@obsd</li>
 <li>Make mksh compilable with SUNpro 12 (inside compat_linux(8)) for
  real, both targetting a Linux binary – Total failed: 12 (11 unexpected) –
  and a native MirOS BSD binary – which works more than just fine…</li>
 <li>Prefer more common signal names (SIGCHLD) over uncommon ones (SIGCLD)</li>
 <li>Quieten gcc and support SUNpro 5.8 on Solaris 10 on sparc64</li>
 <li>Optimise signal handling and detection; enable compilers whose
  præprocessor doesn't have <tt>-dD</tt> to generate list of signals</li>
 <li>Optimise mirtoconf meta-checks for persistent history etc.</li>
</ul>
<p>Please use mksh R29f because of below modifications:</p><ul>
 <li>Fix detection of function prototypes (data declaractions were ok)</li>
 <li>Fix a regression introduced in R29e regarding the scroll bar</li>
 <li>Recommendation on <a href="#vsn">version numbering</a> changed;
  suffixes b, c, … match .2, .3, … like alphabetical numbering order</li>
</ul>
<p>Dedicated to David Ramsey and Coverity, mksh R29e unveils:</p><ul>
 <li>Don't poll in strcasestr(3) if setlocale(3) isn't used</li>
 <li>Remove some redundant or unused functions</li>
 <li>Fix a horizontal scrolling on tabcomplete bug, reported by David
  Ramsey, thanks a lot!</li>
 <li>Fix the utf8bom-3 regression test on MirBSD-current</li>
 <li>Some workarounds around problems found by Coverity Scan, mostly
  issues with Scan, but the changes help gcc to optimise better</li>
 <li>Fix a null pointer dereference in error path, mis-use of strchr(3)
  to search for a NUL byte, and two possible out-of-bounds array
  accesses, found by Coverity Scan, many thanks!</li>
 <li>Optimise <tt>dot.mkshrc</tt> further</li>
 <li>Fix a cursor mis-positioning on backspace bug, reported by David
  Ramsey again, thanks!</li>
 <li>Fix a scrollbar mis-display on delete bug, reported by David Ramsey</li>
 <li>Fix a scrollbar mis-display on insertion bug, discovered while
  fixing the above bug</li>
 <li>Correct displaying of scrollbar on delete, with help from dramsey</li>
</ul>
<p>Portability improvements in mksh R29d contain:</p><ul>
 <li>Unbreak testsuite on Mac OSX (whose brain-dead file system does
  non-standard Unicode decomposing and normalisation on filenames,
  thus rendering ANOTHER of our tests unusable *sigh*)</li>
 <li>Port to AIX, thanks to Kurt Telep</li>
 <li>Minor fixes for HP-UX, thanks to HP Testdrive Programme</li>
 <li>size optimisation if utf-8 is assumed to be always on</li>
 <li>Do not scan for and use “-fwhole-program --combine” because it's the
  cause of at least http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=408850
  and breakage with FORTIFY_SOURCE on SuSE; thanks to Pascal Bleser (yaloki),
  Marcus Rückert (darix), Martin Zobel-Helas, Steve Langasek (vorlon) for
  tracking this bug down in two different places; Closes: Debian #421518</li>
 <li>small manual page fixes</li>
 <li>copy $PATH from Build.sh to test.sh; thanks to a test account on Sun
  Solaris 11 donated by Julian Wiesener (yofuh) I was able to verify that
  you want to prefix $PATH with <tt>/usr/xpg4/bin</tt> because the other
  tools (<tt>/usr/bin</tt>, <tt>/usr/ccs</tt>, et al.) suck major arse…</li>
 <li>Note: the SuSE package in the Buildservice was created by darix (without
  my knowledge), is maintained by loki now</li>
 <li>Note: the PDF manual page is now PDF 1.3 (Acrobat 4.x) again</li>
</ul>
<p>Minor bugfixes in mksh R29c – you might want it:</p><ul>
 <li>Regression fix: mksh has some kind of “encoded string” format;
  use wdcopy() not str_save() to duplicate this; affects formatting of
  an error message (and below item) only though</li>
 <li>Bugfix: pdksh has an out-of-bounds memory access; the area of code
  has been touched by OpenBSD developers but the problem not fixed by
  them; some optimisations turned this (for the error message formatting
  of the above item) into a memory corruption bug that was <em>only</em>
  triggering an actual issue on Debian GNU/Linux experimental on IA-64
  with some beta version of GNU glibc; add an appropriate bounds check</li>
 <li>Add mirtoconf check for “large file support” needed on some obscure
  platforms; requested by bsiegert@, idea from GNU autoconf (thanks)</li>
 <li>Add zsh workaround to Build.sh (just to be on the safe side; zsh
  isn't bourne sh or posix sh compatible, but I didn't find any severe
  problems with using it to build mksh yet, it's a weird shell though)</li>
 <li>If execve(2) fails with ENOEXEC, try and parse a shebang line
  ourselves, in case the kernel can do less than we do, unless MKSH_SMALL</li>
 <li>Strip off and ignore an UTF-8 Byte Order Mark (U+FEFF, 0xEF 0xBB 0xBF)
  at the beginning of input (file, -c option, stdin, interactive, eval)
  and when processing shebang lines and enable utf8 mode if encountered</li>
 <li>Enhancements to the <tt>dot.mkshrc</tt> file, whose status (in MirBSD
  itself) is now upgraded from “sample file for portable mksh to show off to
  other OSes” to “used as skeleton file in the default installation” – gets
  us rid of duplicating this stuff in /etc/profile (MirBSD native) a̲n̲d̲ makes
  sure that users of portable mksh also have the latest goodies</li>
 <li>When doing shebang parsing, accept not only LF and NUL but also CR as
  markers for end of the (first) line</li>
 <li>If executing fails, tell the user what exactly failed, too</li>
</ul>
<p>Immediately upgrade to mksh R29b please:</p><ul>
 <li>Bugfix: display UTF-8 control characters (U+0080..U+009F, i.e.
  everything with a wcwidth(3) of -1) the same as ASCII control
  characters (U+0001..U+001F), i.e. with a ctrl caret followed by
  its value XOR U+0040; subsequently treat their width as 2;
  fix crash (CPU hog in spinning loop) on meta-tab+backspace</li>
 <li>Fix setlocale description in manual page</li>
 <li>in the utf-8 mode, invalid multibytes are now handled more strictly:<ul>
   <li>if it's in x_literal() (“quote” / ^V) mode, it's accepted like now</li>
   <li>if it's a mb sequence start, it's rejected with a beep</li>
   <li>if it's a mb continuation, the whole sequence is silently rejected</li>
  </ul>
  This makes command line editing when accidentally hitting, e.g. with
  my mircvs://contrib/samples/dot.Xmodmap layout, Mode_switch-x much
  more robust.</li>
 <li>remove unused utf_width() macro</li>
 <li>if $CC supports -fstack-protector-all, add it to CFLAGS</li>
 <li>shut up some more gcc 4.1.2 warnings</li>
 <li>if $CC supports -fno-tree-vrp and is subject to the <a
  href="http://gcc.gnu.org/bugzilla/show_bug.cgi?id=30785">null pointer
  test optimised away</a> bug, use -fno-tree-vrp to work around it</li>
 <li>in Build.sh, simplify a.out / a.exe (Cygwin) issues</li>
 <li>shrink the manual page to 39 pages sized DIN A4 when built as PS/PDF</li>
 <li>fix a typo in the manual page</li>
</ul>
<p>Please upgrade to mksh R29 due to the following changes:</p><ul>
 <li>Fix portability of regression tests using fgrep(1), twice</li>
 <li>Fix description of $RANDOM in manual page</li>
 <li>Fix build under OpenSolaris Build 47 (reported in IRC)</li>
 <li>Use easier __RCSID() stuff from MirOS #9-current</li>
 <li>Don't shebang with spaces in test.sh creation</li>
 <li>Remove -fno-strength-reduce from default CFLAGS, the compiler bug
  was fixed between gcc 2.7.2 and gcc 2.7.2.1&#8230;</li>
 <li>Avoid unaligned memory access causing SIGBUS on IA-64 on Debian</li>
 <li>Convert to autoconf-style check for function and header file existence
  of &lt;sys/param.h&gt;, arc4random(3), arc4random_push(3),
  setlocale(3) and LC_CTYPE, nl_langinfo(3) and CODESET, getmode(3) and
  setmode(3), strcasestr(3), and strlcpy(3)</li>
 <li>Add <tt>set -o utf8-hack</tt> aka <tt>mksh -U</tt> which
  changes the Emacs editing mode to an experimental CESU-8 aware
  multibyte mode (not implemented using wide chars unless internally
  needed; does not require OS support); check setlocale(LC_CTYPE, "")
  and nl_langinfo(CODESET) if found to auto-enable utf-8 mode
  in interactive shells</li>
 <li>Simplify and clean up code; try to remove or replace function calls
  by smaller equivalents; spot a few non-fatal off-by-one errors</li>
 <li>If Build.sh is called with <tt>-DMKSH_SMALL</tt> in the CPPFLAGS
  environment variable, the built-in mknod(8) will not be included,
  and other functionality and verbose usage messages will be excluded;
  some macros will be turned into functions to save space and to check
  if the utf8-hack should be enabled, nl_langinfo(3) is not called.
  The -T option to mksh(1) and persistent history are not supported.</li>
 <li>Hand-optimise the code to be small, even in the normal build</li>
 <li>Unbreak the -d option to <tt>Build.sh</tt></li>
 <li>Check for <tt>cc</tt> options -Wno-error, -fwhole-program --combine,
  and (if MKSH_SMALL) -fno-inline and use them if they don't fail</li>
 <li>The autoconf-style (&#8220;mirtoconf&#8221;) checks have been enhanced,
  improved and be made more verbose by default</li>
 <li>Rewrite a few functions both to save space and to simplify/unify
  the code; also spotted a few bugs in existing (inherited) code</li>
 <li>Fix format string mistakes and wrong function and data prototypes</li>
 <li>Correct zero-padding for right-justified strings; add regression test</li>
 <li>EXECSHELL is now ${EXECSHELL:-/bin/sh} again</li>
 <li>Remove duplicate code if feasible; rewrite remaining code to solve
  all use cases, or use standard library functions such as qsort(3);
  rework the ctypes and chtypes stuff, get rid of libc/ctype.h</li>
 <li>Change the eaccess() code to not use setreuid(2) and friends, like
  OpenBSD ksh and apparently pdksh. I'm not too sure about the implications,
  except that they only affect setuid shell scripts.</li>
 <li>Use setresuid(2) and friends, and setgroups(3) and &lt;grp.h&gt; instead
  of seteuid(2), setuid(2) etc. on operating systems that support them</li>
 <li>Work around (i.e. remove) all but two <tt>-Wcast-qual</tt> issues</li>
 <li>Work around a bug in the GNU implementation of the Berkeley mdoc macros
  which comes with GNU groff (only visible in MirOS with groff -mgdoc, but
  shows on other operating systems), discovered by crib in IRC</li>
 <li><tt>$RANDOM</tt> is always an unsigned 15-bit decimal integer, for all
  Korn shell derivates; idea from twkm in IRC</li>
 <li>Improve/correct description of typeset command in manpage, and
  implementation of <tt>typeset -p</tt> in mksh</li>
 <li>Remove the non-standard emacs-usemeta and vi-show8 shell options,
  assume the user either has a 7-bit environment, an 8-bit clean terminal,
  or a UTF-8 environment (preferred), and the dummy sh option</li>
 <li>Build.sh fix for conservative (old) versions of gcc; help Debian</li>
 <li>Compute user-given ulimit value times ulimit unit as an rlim_t value,
  not as long value; catches some 32 bit overflows on 32 bit platforms
  due to a missing cast</li>
 <li>Fix some typos in the manual page</li>
 <li>Build.sh add notes for old and non-gcc compilers (TODO)</li>
 <li>Upgrade licence to latest template (revision 1.20)</li>
 <li>Fix reverse logic error in strcasecmp(3) vs strcasestr(3) issue</li>
 <li>Enhance sample ~/.mkshrc</li>
 <li>Prevent segfaults when setlocale(3) or nl_langinfo(3) return NULL</li>
 <li>Use RLIMIT_AS if RLIMIT_VMEM is not found</li>
 <li>Don't expand <tt>~foo/</tt> if MKSH_SMALL, spares getpwnam(3) call</li>
 <li>Fix and autoconfify signal list generation</li>
 <li>Build.sh now uses $TARGET_OS as "uname -s" output for cross builds</li>
 <li>Set flag for regression tests that can't succeed if MKSH_SMALL</li>
 <li>Don't even check for setlocale(3) if MKSH_SMALL, unless overridden
  by user / build environment</li>
 <li>Scan for C Preprocessor, use $CPP if $CC -E fails</li>
 <li>Fix possible nil pointer dereferences and signal name mismatches</li>
 <li>Scan for __attribute__((...)) and -std=gnu99 (req'd on Solaris 10)</li>
 <li>Correct $LDSTATIC logic, unbreak -d, don't let the user override
  (or need to) $SRCS, $sigseen</li>
 <li>Simplify TIOCGWINSZ handling, no need to catch SIGWINCH any more;
  window size changes are processed after input line editing ends (i.e.
  the lines are entered or <tt>ESC #</tt> (emacs mode) is pressed) and
  at startup; ^L (redraw) can't change window size on the fly</li>
 <li>Add -fwrapv to standard CFLAGS, just to be safe, like with when I
  added -fno-strict-aliasing; this is pending a bug fix in gcc, see <a
  href="http://gcc.gnu.org/bugzilla/show_bug.cgi?id=30477">PR#30477</a></li>
 <li>autoconfify compiler flags, c preprocessor</li>
 <li>add option to avoid pulling in getpwnam(3) in !MKSH_SMALL</li>
 <li>scan for certain headers, types; improve portability</li>
 <li>speed up autoconfiguration process in failure case</li>
 <li>finally fix static vs dynamic linking issues</li>
 <li>fix manpage (.Nm macro) glitch with GNU nroff 1.15</li>
 <li>improve auto-detection of which regression tests are valid</li>
 <li>mention failure to revoke(2) is possibly insecure</li>
 <li>if MKSH_SMALL, don't include -T support and don't scan
  for revoke() function</li>
 <li>new #ifdef MKSH_NEED_MKNOD to embed mknod(8) even if
  MKSH_SMALL is enabled</li>
 <li>do not scan for revoke() on GNU/Linux since it always fails</li>
 <li>simplify GNU/Linux CPPFLAGS and use them for GNU/HURD and
  GNU/kFreeBSD (tested on Debian experimental, thanks to the
  ftbfs.de autobuilder and Michael "azeem" Banck)</li>
 <li>fix the 'bind' (no args) builtin output</li>
 <li>new #ifdef MKSH_ASSUME_UTF8 to not check setlocale() and
  nl_langinfo(CODESET) if we want to always enable the utf-8
  command line editing mode</li>
 <li>tabcomplete a newline to singlequote+newline+singlequote
  instead of backslash+newline which is eaten; thanks to
  Thomas E. "TGEN" Spanjaard for noticing</li>
 <li>remove shebang line from check.pl which isn't +x anyway</li>
 <li>fix 'hd' alias in dot.mkshrc example to not run off
  an ANSI standard 80 column screen; simplify</li>
 <li>integrate MKSH_NEED_MKNOD and MKSH_ASSUME_UTF8 with Build.sh</li>
 <li>Work around Solaris /usr/ucb/tr, Solaris /usr/xpg4/bin/tr,
  Minix 3 /usr/bin/tr, and SUSv3 deficiencies</li>
 <li>Fix compilation on more platforms (Interix, Cygwin, Linux 2.0 libc5,
  Debian GNU/kFreeBSD, Debian GNU/HURD, &#8230;)</li>
 <li>Use autoconfiguration for persistent history stuff</li>
 <li>Fix the code (add "const" in like 1001 places) to be able to
  build without <tt>-Wno-cast-qual</tt> (hope it's safe now)</li>
 <li>Optionally use const-debugging versions of strchr(3), strstr(3),
  to work around deficiencies in ANSI C</li>
 <li>The above directly led to our own strcasestr(3) implementation
  for OSes which don't have it</li>
 <li>Optimise <tt>dot.mkshrc</tt> macros</li>
 <li>Let <tt>dot.mkshrc</tt> not return failure early</li>
 <li>Remove shadowing warnings for more OSes</li>
 <li>Support old ash(1) versions in Build.sh</li>
 <li>Support use of <tt>_NSIG</tt> for <tt>NSIG</tt></li>
 <li>Optimise ctags(1) generation</li>
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

<h2 id="vsn">Recommendations on version numbering</h2>
<p>mksh by default uses a version numbering scheme that uses full integers,
 prefixed by a capital letter R significing “Release”. If minor updates are
 required or requested, a lower-case letter from the standard latin alphabet
 will be appended, starting at ‘b’ and ending at ‘z’ (but usually way before
 or at ‘i’). If a packaging system cannot handle version numbers such as
 <tt>mksh-R29b</tt> (source) -&gt; <tt>mksh-R29b-1</tt>, <tt>mksh-R29bp1</tt>
 (binary), packagers OUGHT TO map this to a numerical system as follows:
 <tt>mksh-29.2-1</tt>, <tt>mksh-29.2.1</tt>, <tt>mksh-29.2nb0</tt>, depending
 on the packaging-system local policy for build numbers / patchlevels.</p>
<p>Schemes to AVOID are <tt>mirbsdksh-1.29b</tt>, <tt>mksh-2.9.2</tt>, or
 worse. Please adhere to our recommendations so that users are able to locate
 mksh in their operation environment of choice.</p>

<h3 id="editor">/bin/ed</h3>
<p>While we're at it – recommendations for packagers – there is another set
 of do's and dont's: location of the UNIX® standard text editor. As outlined
 in traditional unixoid operating system standards, manifested into POSIX,
 and – for these three-letter words that aren't Unix, no matter which of the
 kernels they use in their variety of so-called distributions – the <a
 href="http://www.pathname.com/fhs/pub/fhs-2.3.html#SPECIFICOPTIONS2">FHS</a>
 (FSSTND): ed lives in <tt>/bin/ed</tt>, period.</p>
<p>Patching mksh's to look for ed in ANY other location is a MUST NOT.</p>

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
<li>for a b in …; do (like make(1) does)</li>
<li>A sensible website</li>
<li>Build on more platforms</li>
<li>Build with platforms' native tools</li>
<li>bash-style <a
 href="http://article.gmane.org/gmane.os.miros.general/5580">array
 initialisation</a> (mapping <tt>x=(a b c)</tt> to <tt>set -A
 x -- a b c</tt>)</li>
</ul>

<h2 id="prefetch">Requirements</h2>
<p>Of course, your system must be operational for compiling
 programmes. You will need some sort of bourne compatible
 shell, compiler, assembler, linker (has not been tested with
 anything other than GCC), and associated tools. At the moment,
 the following operating systems are supported: any recent BSD
 UNIX&reg;, Darwin and Apple Mac OSX, GNU/Cygwin, Interix aka
 Microsoft&reg; Services for Unix 3.5, GNU/Linux at least with
 libc5, glibc, uClibc, Sun Solaris 8 (other versions, especially
 9, 10, and OpenSolaris (with GCC) might work), Debian GNU/HURD,
 Debian GNU/kFreeBSD. Not supported are
 basically any others. Patches to add support for compilers
 other than GCC and platforms other than these listed above,
 especially these supported by NetBSD&reg; pkgsrc&reg;, are
 welcome &ndash; a port to Plan 9 APE has been started, as
 are ports to Minix 3 (no job control, but not worse than a
 Plan 9 port) and the UNIX&reg;en supported by pkgsrc&reg;,
 i.e., IRIX, AIX, HP-UX, BSD/OS (should work), OSF/1 (Tru64),
 SCO Unixware (did I miss any?). Of course, we need shell
 accounts on them boxes for that.</p>

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

<p>The current version is:</p><ul>
 <li><a href="http://www.mirbsd.org/MirOS/dist/mir/mksh/mksh-R29f.cpio.gz">http://www.mirbsd.org/MirOS/dist/mir/mksh/mksh-R29f.cpio.gz</a></li>
 <li><a href="http://pub.allbsd.org/MirOS/dist/mir/mksh/mksh-R29f.cpio.gz">http://pub.allbsd.org/MirOS/dist/mir/mksh/mksh-R29f.cpio.gz</a></li>
 <li>Please use gzsig(1) to verify the integrity of the distfile instead!
  Hashes are only so you know which distfile you want.</li>
 <li>RMD160 (mksh-R29f.cpio.gz) = eddf9b3292d50171d8b9d6429279f0eb42a4b9ff</li>
 <li>TIGER (mksh-R29f.cpio.gz) = 5b21adea37e42274bd692518ddd4dedcff5f65e6f113a90b</li>
 <li>2910491928 240805 /MirOS/dist/mir/mksh/mksh-R29f.cpio.gz</li>
 <li>MD5 (mksh-R29f.cpio.gz) = 83b4ca84faa1a1ea4cf6db6eb41a0384</li>
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
 as <em>mksh-R29f.cpio.gz</em> but already decompressed.</p>

<h3 id="extract">Unpacking</h3>
<p>On decent systems, you can just use <tt>tar xzf mksh-R29f.cpio.gz</tt>
 to extract the file. On quite damaged systems such as basically everything
 which is not MirOS or anything else with <a href="/?MirCpio">MirCpio</a>
 (paxmirabilis) or some other kind of paxtar, use <tt>gzip -dc
 mksh-R29f.cpio.gz | cpio -mid</tt> or <tt>gzip -dc mksh-R29f.cpio.gz |
 pax -r</tt> instead.</p>
<p>Of course, skip the gzip stage (use cat) or the 'z' flag
 if your browser already decompressed the file.</p>

<h3 id="build">Building</h3>
<p>You might have to take advantage of the AT&amp;T ksh, pdksh or GNU
 bash which comes with the operating system. With hard effort,
 Solaris <tt>/bin/sh</tt> and even ash could be made to suffice.</p>
<p>Different operating systems used to require different flags,
 but the syntax shown below should work on every system supported.</p>
<p>Manpage generation fails on systems which are not mdoc aware,
 such as Sun Solaris, or have no nroff(1)
 installed, such as MS Interix/Services for Unix. Use the <em>-r</em>
 command line option in that case.
 Stripping is done via the host's install(1)
 command's -s flag; if stripping during installation fails just use the
 <em>mksh</em> binary. On Solaris, use /usr/ucb/install instead.</p>
<p>The testsuite can be run by the dynamically generated <tt>test.sh</tt>
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
<p>On inferiour operating systems, such as OpenBSD, you might need a <a
 href="/cvs.cgi/contrib/code/Snippets/setlocale.c?rev=HEAD">different
 setlocale() implementation</a> than the one provided with the system
 for proper unicode auto-detection/initialisation support.</p>

<h3 id="buildsol">Solaris</h3>
<p>The Solaris port of mksh is sponsored by Der Verein <a
 href="http://www.trash.net/verein/">trash.net</a> which
 provides me a shell account on a Solaris 8 (Ultrasparc)
 box. Let me express a &quot;thank you&quot; to these guys;
 I suggest to support them because they are doing great
 things like Netzladen e.V. where I are involved in.</p>
<p>Tonnerre LOMBARD has made it possible to build and
 test (from time to time) mksh on a Solaris 10 box.<br />
 Julian “yofuh” Wiesener provides a shell account on a
 Sun Solaris 11 (beta) zone, thanks as well.</p>
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
 Gockel, but called "mirbsdksh" (not mksh) there (with hope for a
 migration to the official “mksh” denomination). Thanks to morfic
 (Daniel Goller), Sourcemage (SMGL) has an mksh spell, originally
 crafted by yours truly, debugged and fixed together. FreeWRT also
 comes with mksh, as does OpenWrt. Ubuntu, <a
 href="http://www.gnusolaris.org/">Nexenta OS</a>, <a
 href="http://grml.org/">grml</a>, and other Debian derivates either
 probably have it as well or even are known to. <a
 href="http://dev-loki.blogspot.com/">Pascal &quot;loki&quot; Bleser</a>
 of <a href="http://planet.fosdem.org/">FOSDEM</a> fame has packaged mksh
 for SuSE GNU/Linux (fixed for Fedora and Debian, *old* packages at: <a
 href="http://linux01.gwdg.de/~pbleser/rpm-navigation.php?cat=System/mksh/">link
 to (broken) webinterface)</a>, which is hosted at at least two mirrors, a <a
 href="http://ftp.gwdg.de/pub/linux/misc/suser-guru/rpm/packages/System/mksh/">primary</a>
 and a <a href="http://ftp.skynet.be/pub/suser-guru/rpm/packages/System/mksh/">fast</a>
 site. Since recently, mksh can be found in the OpenSuSE <a
 href="http://en.opensuse.org/Build_Service">Build Service</a> for several
 RPM-based GNU/Linux distributions within a subtree of <a
 href="http://software.opensuse.org/download/shells/">the shells repo</a>.
 Arch GNU/Linux <a href="http://aur.archlinux.org/packages.php?do_Details=1&amp;ID=3431">also
 packages mksh</a>. <strong>NOTE:</strong> These packages usually have
 <em>not</em> been provided and/or tested by the mksh developers and are not
 guaranteed to work properly; also, they might deliver an older version.
</p>

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
 <li>mksh R29d<ul>
  <li>Darwin 8.9.0 Mac OSX 10.4 (powerpc)</li>
  <li>AIX 5.3 ML05 – thanks Gurft</li>
  <li>Solaris 5.10 Generic_118833-36 (sun4u) 32-bit, 64-bit</li>
 </ul></li>
 <li>mksh R29c<ul>
  <li>MirOS #10-beta (i386 gcc3.4.6)</li>
  <li>Solaris 8 (sun4u gcc3.4.3) both without and with -m64</li>
  <li>DragonFly 1.9-dev (i386 gcc3.4.6)</li>
  <li>NetBSD 3.0-stable (i386 gcc3.3.3)</li>
  <li>Cygwin 1.5.24-2 (i386 gcc3.4.4 win2k)</li>
  <li>Interix 3.5 (i386 gcc3.3 win2k)</li>
  <li>OpenBSD 4.0 (sparc64 gcc3.3.5)</li>
  <li>Debian etch (i386, ia64, amd64 gcc4.1.1-21)</li>
  <li>FreeBSD 6.1 (i386, ia64 gcc3.4.4)</li>
  <li>HP-UX 11i B.11.11 (PA-RISC gcc3.4.2) <em>no regression test run</em></li>
  <li>HP-UX 11i v2 B.11.23 (ia64 gcc3.4.3)</li>
  <li>– tests by third parties –</li>
  <li>Solaris 10 (sun4us gcc4.0.3 "gccfss") 32-bit, 64-bit – thanks Ankon</li>
 </ul></li>
 <li>mksh R29 &ndash; release candidate<ul>
  <li>MirOS #7-stable (sparc gcc2.95), #9-current (i386 gcc3.4.6)</li>
  <li>Linux 2.0 (i386 libc5 gcc2.7.2.3), 2.4 (mipsel uClibc gcc3.4.4),
   2.6 (i386 glibc gcc4.1.2pre, s390x glibc gcc4.1.2pre)</li>
  <li>Solaris 8 (sun4u gcc3.4.3)</li>
  <li>Mac OSX 10.4 [I think] (macppc gcc4.0.2apple)</li>
  <li>NetBSD 3.0-stable (i386 gcc3.3.3)</li>
  <li>DragonFly 1.9-dev (i386 gcc3.4.6)</li>
  <li>OpenBSD 4.0 (sparc64 gcc3.3.5)</li>
  <li>Cygwin 1.5.19(0.150/4/2) 2006-01-20 13:28 (i386 gcc3.4.4 win2k)</li>
  <li>Interix 3.5 (i386 gcc3.3 win2k)</li>
 </ul></li>
 <li>mksh-2007-02-18<ul>
  <li>MirOS #9uAC (i386, gcc 3.4.6+SSP), as part of base system, as part
   of installer, run with stand-alone Build.sh</li>
  <li>Debian 4.0-experimental (i386, kfreebsd-amd64, kfreebsd-i386),
   gcc 4.1.1-21 (4.1.2-prerelease), autobuilder via Debian rules</li>
  <li>Debian 4.0-testing (i386, 2.6.16-2-686, gcc 4.1.1-21), manually via
   Debian rules)</li>
  <li>Solaris 8 (sun4u), both -m32 and -m64 (gcc 3.4.3) via Build.sh</li>
  <li>FreeWRT GNU/Linux trunk (mipsel, gcc 3.4.4), via ADK</li>
 </ul></li>
 <li>mksh-current<ul>
  <li>OpenSolaris Build 47</li>
  <li>Linux td156 2.6.8-3-mckinley-smp #1 SMP Sat Jul 15 11:48:36 UTC 2006 ia64 GNU/Linux</li>
 </ul></li>
 <li>mksh R28<ul>
  <li>MirOS BSD #9-stable (i386)</li>
  <li>MirOS BSD #7-stable (sparc)</li>
  <li>Solaris 8 (sun4u) SUNW,Ultra-60</li>
  <li>NetBSD 3.0_STABLE (i386)</li>
  <li>DragonFly BSD 1.3-Preview (i386)</li>
  <li>DragonFly BSD 1.7-DEVELOPMENT (i386 SMP)</li>
  <li>Debian GNU/Linux 3.1-testing 2.6.16-2-686 (i386)</li>
  <li>Debian GNU/Linux 3.1-testing 2.6.17-2-vserver-s390x (s390x)</li>
  <li>Debian GNU/Linux 3.1-stable 2.4.27-2-k7 (i386)</li>
  <li>Darwin 8.7.0 Mac OSX 10.4 (powerpc)</li>
  <li>Debian GNU/Linux 3.1-unstable (all architectures except ia64) &ndash; debianised</li>
  <li>OpenBSD 3.9 (sparc64) &ndash; via <a href="http://www.mirbsd.org/GBG/mksh-obsdport.tgz">contributed port</a></li>
  <li>Debian GNU/Linux 3.1-stable 2.4.27-2-k7 (i386) &ndash; via an experimental pkgsrc&reg; package</li>
  <li>CYGWIN_NT-5.0 1.5.19(0.150/4/2) 2006-01-20 13:28 (i386) &ndash; testsuite not run</li>
  <li>Interix SFU 3.5 (Windows&reg; 2000 Pro) SP-8.0.1969.1 (i386) &ndash; testsuite not run</li>
  <li>NetBSD 3.0 (mac68k) &ndash; tested by Jonathan "ciruZ" Schleifer</li>
  <li>Darwin 8.7.1 Mac OSX 10.4 (i386) &ndash; tested by Angelo Laub</li>
  <li>Solaris 8 (sun4m) SUNW,SPARCstation-5 &ndash; tested by Angelo Laub</li>
  <li>FreeWRT GNU/Linux SVN 2.4-BRCM (mipsel) &ndash; part of FreeWRT: testsuite not run</li>
  <li>FreeBSD (unknown) &ndash; part of FreeBSD Ports: not tried</li>
  <li>Gentoo GNU/Linux (i386 powerpc) &ndash; part of Portage: not tried</li>
  <li>CRUX GNU/Linux (i386) &ndash; via Han Boetes' repository: not tested</li>
  <li>Sourcemage GNU/Linux (amd64) &ndash; <a href="http://distro.ibiblio.org/pub/linux/distributions/sourcemage/codex/test/shell-term-fm/mksh/">via
   test grimoire</a>: not tried</li>
  <li>generic pkgsrc&reg; &ndash; not tested; ONLY_FOR_PLATFORMS not honoured</li>
 </ul></li>
 <li><p style="margin-bottom:0px;">Attention: NetBSD 1.6.1/pmax (for example
   on a DECstation 5000/260) does not come with a <em>stdbool.h</em> &ndash;
   simply write one yourself (not required for mksh R29 and up):</p>
  <div style="border:4px ridge blue; margin:0px 24px 0px 24px; padding:12px;">
   <pre>
	typedef int bool;
	#define true 1
	#define false 0
   </pre>
  </div><p style="margin-top:0px;">This is pretty simple but enough for mksh.</p>
 </li>
 <li>mksh R28&szlig;<ul>
  <li>NetBSD 1.6.1 (pmax)</li>
   <!-- missing:
  <li>MirOS BSD #9-stable (sparc)</li>
  <li>Solaris 10 (?) &ndash; tested by Tonnerre Lombard</li>
  <li>Mac OSX Panther (powerpc) &ndash; not tested, via Fink</li>
  <li>Plan 9 POSIX Environment</li>
   -->
 </ul></li>
 <li>mksh R27e<ul>
  <!-- li>Solaris 8 (sparc64): works (testsuite and usage on the shell
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
  <li>Available under FreeBSD as ports/shells/mksh</li -->
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

<p>From <em>mksh R29c</em> onwards, the <tt>dot.mkshrc</tt> file is
 actually used in MirOS BSD as well.</p>

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
 href="http://www.kornshell.com/">original (AT&amp;T) Korn Shell</a>,
 other that it, like AT&amp;T ksh, tries to implement a programming
 language known as Korn Shell.</p>
