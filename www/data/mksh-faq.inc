RCSID: $MirOS: www/data/mksh-faq.inc,v 1.4 2018/08/09 23:55:24 tg Exp $
ToC: spelling
Title: How do you spell <tt>mksh</tt>? How do you pronounce it?

<p>The <a href="mksh.htm">shell</a> is spelt either “<tt>mksh</tt>” (with <a
 href="https://en.wikipedia.org/wiki/Wikipedia:Manual_of_Style/Capital_letters#Items_that_require_initial_lower_case">an
 initial lowercase letter</a>, this is important) or “MirBSD Korn Shell”.</p>
<p>I usually pronounce it as “<span xml:lang="de-DE-1901">em-ka-es-ha</span>”,
 that is, the letters individually in my native German, or say “MirBSD Korn
 Shell”, although it is manageable, mostly for Slavic speakers, to actually
 say “mksh” as if it were a word ☺</p>
<p>Oh… I’ve run into this one, didn’t I? “MirBSD” is pronounced “<span
 xml:lang="de-DE-1901">Mir-Be-Es-De</span>” germanically, for anglophones
 “Mir-beas’tie” is fine.</p>
----
ToC: sowhatismksh
Title: I’m a $OS (<i>Android, …</i>) user, so what’s mksh?

<p>mksh is a so-called (Unix) “shell” or “command interpreter”, similar to
 <tt>COMMAND.COM</tt>, <tt>CMD.EXE</tt> or PowerShell on other operating
 systems you might know. Basically, it runs in a terminal (“console” or
 “DOS box”) window, taking user input and running that as commands. It’s
 also used to write so-called (shell) “script”s, short programs made by
 putting several of those commands into a “batch file”.</p>
<p>On Android, mksh is used as the system shell — basically, the one
 running commands at system startup, in the background, and on user
 behalf (but never of its own). Any privilege pop-ups you might <a
 href="https://forum.xda-developers.com/showthread.php?t=1963976">be
 encountering</a> are therefore <a
 href="https://forum.xda-developers.com/showpost.php?p=33550523&amp;postcount=1553">not
 caused by mksh</a> but by some other code invoking mksh to do something
 on its behalf.</p>
----
ToC: kornshell
Title: How does this relate to ksh or the Korn Shell?

<p>The Korn Shell (AT&amp;T ksh) was authored by David Korn; two major
 flavours exist (ksh88 and ksh93), the latter having been maintained
 until 2012 (last formal release) and 2014 (last beta snapshot), with
 development having been taken up by a third party around November 2017.
 A ksh86 did exist.</p>
<p>AT&amp;T ksh88 is “the (original) Korn Shell”. Other implementations,
 of varying quality (MKS Toolkit’s MKS ksh being named as an example of
 the lower end, MirBSD’s mksh at the upper end). They are all <em>not</em>
 “Korn Shell” or “ksh”. However, mksh got blessed by David Korn, as long
 as it cannot be confused with the original Korn Shell.</p>
<p>The POSIX shell standard, while lacking most Korn Shell features, was
 largely based on AT&amp;T ksh88, with some from the Bourne shell.</p>
<p>mksh is the currently active development of what started as the Public
 Domain Bourne Shell in the mid-1980s with ksh88-compatibl-ish extensions
 having been added later, making the Public Domain Korn Shell (pdksh),
 which, while never officially blessed, was the only way for most to get
 a Korn Shell-like command interpreter for AT&amp;T’s was proprietary,
 closed-source code for a very long time. pdksh’s development ended in
 1999, with some projects like Debian and NetBSD® creating small bug fixes
 (which often introduced new bugs) as part of maintenance. Around 2003,
 OpenBSD started cleaning up their shipped version of pdksh, removing old
 and compatibility code and modernising it. In 2002, development of what
 is now mksh started as the system shell of MirBSD, which took over almost
 all of OpenBSD’s cleanup, adding compatibility to other operating systems
 back on top of it, and after 2004, independent, massive development of
 bugfixes including a complete reorganisation of the way the parser works,
 and of new features both independent and compatible with other shells
 (ksh93, GNU bash, zsh, BSD csh) started and was followed by working with
 the group behind POSIX to fix issues both in the standard and in mksh.
 mksh became the system shell in several other operating systems and Linux
 distributions and Android and thus is likely the Korn shell, if not Unix
 shell, flavour with the largest user base. It has replaced pdksh in all
 contemporary systems except QNX, NetBSD® and OpenBSD (who continue to
 maintain their variant on “low flame”).</p>
<p>dtksh is the “Desktop Korn Shell”, a build of AT&amp;T ksh93 with some
 additional built-in utilities for graphics programming (windows, menu
 bars, dialogue boxes, etc.) utilising Motif bindings.</p>
<p>MKS ksh is a proprietary reimplemention aiming for, but not quite
 getting close to, ksh88 compatibility.</p>
<p>SKsh is an AmigaOS-specific Korn Shell-lookalike by Steve Koren.</p>
<p>The <a href="@@RELPATH@@ksh-chan.htm">Homepage of the <tt>#ksh</tt>
 channel on Freenode IRC</a> contains more information about the Korn
 Shell in general and its flavours.</p>
----
ToC: packaging
Title: How should I package mksh? (common cases)

<p>Export a few environment variables, namely <tt>CC</tt> (the C compiler),
 <tt>CPPFLAGS</tt> (all C præprocessor definitions), <tt>CFLAGS</tt> (only
 compiler flags, <em>no</em> <tt>-Dfoo</tt> or anything!), <tt>LDFLAGS</tt>
 (for anything to pass to the C compiler while linking) and <tt>LIBS</tt>
 (appended to the linking command line after everything else. You might
 wish to <tt>export LDSTATIC=-static</tt> for a static build as well.</p>
<p>When cross-compiling, <tt>CC</tt> is the <em>cross</em> compiler (mksh
 currently does not require a compiler targetting the build system), but
 you <em>must</em> also export <tt>TARGET_OS</tt> to whatever system you
 are compiling for, e.g. “Linux”. For most operating systems, that’s just
 the uname(1) output. Some very rare systems also need <tt>TARGET_OSREV</tt>;
 consult the source code of <tt>Build.sh</tt> for details.</p>
<p>Create two subdirectories, say <tt>build-mksh</tt> and <tt>build-lksh</tt>.
 In each of them, start a compilation by issuing <tt>sh ../Build.sh -r</tt>
 followed by running the testsuite<a href="#packaging-fn1">¹</a> via
 <tt>./test.sh</tt>. For lksh(1) add <tt>-DMKSH_BINSHPOSIX</tt> to
 <tt>CPPFLAGS</tt> and use <tt>sh ../Build.sh -r -L</tt> to compile.</p>
<p>See <a href="#testsuite-fails">below</a> if the testsuite fails.</p>
<p>Install <tt>build-mksh/mksh</tt> as <tt>/bin/mksh</tt> (or similar),
 <tt>build-lksh/lksh</tt> as <tt>/bin/lksh</tt> with a symlink(7) to it
 from <tt>/bin/sh</tt> (if desred), and <tt>mksh.1</tt> and <tt>lksh.1</tt>
 as manpages (mdoc macropackage required). Install <tt>dot.mkshrc</tt>
 either as <tt>/etc/skel/.mkshrc</tt> (meaning your users will have to
 manually resynchronise their home directories’ copies after every package
 upgrade) or as <tt>/etc/mkshrc</tt>, in which case you install a <a
 href="https://evolvis.org/plugins/scmgit/cgi-bin/gitweb.cgi?p=alioth/mksh.git;a=blob;f=debian/.mkshrc;hb=HEAD">redirection
 script like Debian’s</a> into <tt>/etc/skel/.mkshrc</tt>. If you need a <a
 href="TaC-mksh.txt">summary of the licence information</a>, take it.</p>
<p>At runtime, the presence of <tt>/bin/ed</tt> as default history editor
 is recommended, as well as a manpage formatter; you can also install
 preformatted manpages from <tt>build-*ksh/*ksh.cat1</tt> if nroff(1) (or
 <tt>$NROFF</tt>) is available at build time by removing the <tt>-r</tt>
 flag from either <tt>Build.sh</tt> invocation.</p>
<p>Some shell features require the ability to create temporary files and
 FIFOS (cf. mkfifo(2))/pipes at runtime. Set <tt>TMPDIR</tt> to a suitable
 location if <tt>/tmp</tt> isn’t it; if this is known ahead of time, you
 can add <tt>-DMKSH_DEFAULT_TMPDIR=\"/path/to/tmp\"</tt> to CPPFLAGS. We
 currently are unable to determine one on Android because its bionic libc
 does not expose any method suitable to do so in the generic case.</p>
<p id="packaging-fn1">① To run the testsuite, ed(1) must be available as
 <tt>/bin/ed</tt>, and perl(1) is needed. When cross-compiling, the version
 of the first <tt>ed</tt> binary on the <tt>PATH</tt> <em>must</em> be the
 same as that in the target system on which the tests are to be run, in
 order to be able to detect which flavour of ed to adjust the tests for.
 Busybox ed is broken beyond repair, and all three ed-related tests will
 always fail with it.</p>
----
ToC: testsuite-fails
Title: The testsuite fails!

<p>The mksh testsuite has uncovered numerous bugs in operating systems
 (kernels, libraries), compilers and toolchains. It is likely that you
 just ran into one. If you’re using LTO (the <tt>Build.sh</tt> option
 <tt>-c lto</tt>) try to disable it first — especially GCC is a repeat
 offender breaking LTO and its antecessor <tt>-fwhole-program --combine</tt>
 and tends to do wrong code generation quite a bit. Otherwise, try
 lowering the optimisation levels, bisecting, etc.</p>
----
ToC: makefile
Title: Why doesn’t this use a Makefile to build?

<p>Not all supported target operating environments have a make utility
 available, and shell was required for “mirtoconf” (like autoconf)
 already anyway, so it was chosen to run the make part as well.</p>
<p>You can, however, add the <tt>-M</tt> flag to your <tt>Build.sh</tt>
 invocations to let it produce a <tt>Makefrag.inc</tt> file <em>tailored
 for this specific build</em> which you can then include in a Makefile,
 such as with the BSD make(1) “.include” command or <a
 href="https://www.gnu.org/software/make/manual/make.html#Include">GNU
 make</a> equivalent. It even contains, for the user to start out with,
 a commented-out example of how to do that in the most basic manner.</p>
----
ToC: oldbsd
Title: Why do other BSDs and QNX still use pdksh instead of mksh?

<p>Some systems are resistent to change, mostly due to bikeshedding
 (some people would, for example, rather see all shells banned to
 ports/pkgsrc®) and hysterial raisins (historical reasons ☻). Most
 BSDs have mksh packages available, and it works on all of them and
 QNX just fine.</p>
<p>In fact, on all of these systems, you can replace their 1999-era
 <tt>/bin/ksh</tt> (which is a pdksh) with mksh. On at least NetBSD®
 1.6 and up (not 1.5) and OpenBSD, even <tt>/bin/sh</tt> is fair game.</p>
<p>MidnightBSD notably has adopted mksh as system shell (thanks laffer1).</p>
----
ToC: openbsd
Title: Why is there no mksh in OpenBSD’s ports tree?

OpenBSD don’t like people who fork off their project at all; heck,
they don’t even like the people they themselves forked off (NetBSD®).
Several people tried over the years to get one committed, but nobody
dared so as to not lose their commit bit. If you try, succeed, and
survive Theo, however, kudos to you! See also <a href="#oldbsd">the
“other BSDs” FAQ entry</a>.
----
ToC: os2
Title: I’m an OS/2 user, what do I need to know?

This issue is discussed at more length in the <a href="#faq">FAQ
section in the manpage</a>. You can install plain mksh (usually
by compiling it yourself) which behaves like one expects from a
Unix shell in a Unix environment (LF line endings, binary mode
file I/O, etc.) or “mksh-os2” from komh (binaries on Hobbes),
which are built from the same source with the <tt>-T</tt> flag,
enabling “textmode” to behave more similar to native applications
(CR+LF line endings, text mode file I/O, etc).
----
ToC: book
Title: I’d like an introduction.

Unfortunately, nobody has written a book about mksh yet, although
other shells have received (sometimes decent) attention from authors
and publishers. This FAQ lists a subset of things packagers and
generic people ask, and the mksh(1) manpage is more of a reference,
so you are probably best off starting with a shell-agnostic, POSIX
or ksh88 reference such as the first edition (the second one deals
with ksh93 which differs far more from mksh than ksh88, as ancient
as it is, does) of the O’Reilly book (⚠ disclaimer: only an example,
not a recommendation) and going forward by reading scripts (the
“shellsnippets” repository referenced in the <tt>#ksh</tt> channel
homepage (see the top of this document) has many examples) and
trying to understand them and the mksh specifics from the manpage.
----
ToC: ps1conv
Title: My prompt from &lt;<i>some other shell</i>&gt; does not work!

<a href="#contact">Contact</a> us on the mailing list or on IRC,
we'll convert it for you. Also have a look at the PS1 section in
the mksh(1) manpage (search for “otherwise unused char”, e.g. with
<tt>/</tt> in less(1), to spot it quickly).
----
ToC: current
Title: Can mksh set the title of the window according to the command running?

There’s no such thing as “the command currently running”; consider
pipelines and delays (<tt>cmd1 | (cmd2; sleep 3; cmd3) | cmd4</tt>).
There is, however, a way to make the shell display the command <em>line</em>
during the time it is executed; for testing, you will need to download <a
href="https://evolvis.org/plugins/scmgit/cgi-bin/gitweb.cgi?p=shellsnippets/shellsnippets.git;a=blob;f=mksh/terminal-title;hb=HEAD">this
script</a> and <tt>source</tt> it. For merging into your <tt>~/.mkshrc</tt>
you should first understand how it works: lines 4–18 set a <tt>PS1</tt>
(prompt) equivalent to lines 84–96 of the stock <tt>dot.mkshrc</tt>, with
one change: line 15 (<tt>print &gt;/dev/tty …</tt>) is new, inserted just
before the <tt>return</tt> command of the function substitution in the
default prompt; this is what you’ll need to merge into your own, custom,
prompt (if you have one; otherwise pull this adaption to the default
one). Line 19 is the only other thing in this script rebinding the Ctrl-M
key (which is normally produced by the Enter/Return key) to code that…
does <em>something crazy</em>. This trick however <em>does funny things with
multiline commands</em>, so if you type something out in multiple lines,
for example <strong>here documents</strong> or <strong>loops</strong> press
<strong>Ctrl-J instead of Enter/Return</strong> after <em>each</em> line
including the first (at PS1) and final (at PS2) one.
----
ToC: completion
Title: What about programmable tab completion?

The shell itself provides static deterministic tab completion.
However, you can use hooks like reprogramming the Tab key to a
command line editor macro, and using the <tt>evaluate-region</tt>
editor command (modulo a bugfix and possibly adding another,
convenience, editor command) together with shell functions to
implement a programmable completion engine. Multiple people have
been considering doing so in our IRC channel; we’ll hyperlink to
these engines when they are available.
----
ToC: faq
Title: My question is not answered here!

Check out the FAQ section at the end of the mksh(1) manual page which
contains questions that are in user scope; this webpage collects those
about mksh in general, by packagers, etc.
----
ToC: contact
Title: How do I contact you (to say thanks)?

You can say hi in the <tt>#!/bin/mksh</tt> channel on Freenode <a
 href="irc.htm">IRC</a>, although a <a
 href="danke.htm">donation</a> wouldn’t be amiss ☺ The <a
 href="http://www.mail-archive.com/miros-mksh@mirbsd.org/">mailing
list</a> can also be used.
----
