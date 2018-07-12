RCSID: $MirOS: www/data/ksh-chan.inc,v 1.35 2017/12/07 23:54:13 tg Exp $
Title: Homepage of the original Korn Shell
Link: http://www.kornshell.com/

This is the homepage for the original (AT&amp;T) Korn Shell,
where sources and binaries for ksh93 as well as information
are available. It is a modern shell with many features for
both interactive and script use, extensible, and can be used
as shared library. It’s also locale aware and thus Unicode
ready on most modern operating systems.
<a href="http://www2.research.att.com/~astopen/download/">Download</a>
----
Title: Homepage of the MirBSD Korn Shell
Link: @@RELPATH@@mksh.htm

This is the homepage of the MirBSD Korn Shell (mksh), which
is <strong>the</strong> actively developed successor of pdksh.
The focus is a compact yet featureful shell, so several of the
ksh93/bash/zsh extensions are present, while others, such as
floating point arithmetic, will not be provided, even though
the aim is as generic as ksh93’s (interactive and script use;
embedding is not yet possible) and to be very portable, also
to include some extensions of its own. It’s Unicode aware.
----
Title: Frequently Asked Questions for The MirBSD Korn Shell
Link: http://www.mirbsd.org/mksh-faq.htm

Questions you never knew you’d ask.
----
Title: (archived version of the) ksh FAQ
Link: http://web.archive.org/web/20130527195150/http://www2.research.att.com/~gsf/download/ksh/faq.html

FAQ for the Korn Shell, including which variants exist.
----
Title: ksh93 current development
Link: https://github.com/att/ast

Repository in which a user (situ) who is a Red Hat employee
continues development of AT&amp;T ksh93 reportedly AT&amp;T
have no further interest in Korn Shell.
----
Title: mksh external (optional) bugtracker
Link: https://bugs.launchpad.net/mksh

The MirOS Project normally uses eMail and IRC for bug handling.
However, some people prefer a web application. Launchpad offered,
so this is the mksh external bugtracker which such people can use.
Its bugmail will also be sent to the mksh mailing list.
----
Title: mksh snapshot downloads
Link: https://www.mirbsd.org/MirOS/dist/mir/mksh/snapshot/

Snapshots of the MirBSD Korn Shell can often be found here.
Versions with an “i” before the date (yyyymmdd) are of the
MAIN development branch, all others are of the stable bugfix
branch.
----
Title: mksh/Win32 Beta 14 announcement
Link: @@RELPATH@@permalinks/wlog-10_e20130718-tg.htm

Read about the currently published source and binary snapshot
of the developing port of mksh(1) to native Win32 API.
----
Title: Homepage of Glenn Fowler
Link: http://gsf.cococlyde.org/download

This site occasionally contains links to newer AT&amp;T material
than what’s available from the official sites.
----
Title: AT&amp;T Beta Downloads
Link: http://www2.research.att.com/sw/download/beta/

Beta versions of the original Korn Shell can often be found here.
----
Title: AT&amp;T Alpha Downloads
Link: http://www2.research.att.com/sw/download/alpha/

Alpha versions of the original Korn Shell can often be found here.
----
Title: Homepage of the Public Domain Korn Shell
Link: http://www.cs.mun.ca/~michael/pdksh/

This is the homepage of the Public Domain Korn Shell (pdksh),
where last development happened in 1999, when the original
Korn Shell used to be commercial/proprietary software.
----
Title: CVSweb for OpenBSD’s ksh
Link: http://cvsweb.openbsd.org/cgi-bin/cvsweb/src/bin/ksh/

This is OpenBSD’s version of pdksh, which has been enhanced
and bugfixed relative to it and eventually spawned mksh.
It has been ported to other operating systems several times:
<a href="http://web.archive.org/web/20090701170731/http://www.delilinux.de/oksh/">oksh in DeliLinux</a>,
<a href="http://people.freebsd.org/~tmclaugh/">OpenKSH by
 FreeBSD’s Tom McLaughlin</a>, etc.
----
Title: Unix sh manual page (current)
Link: http://osr507doc.sco.com/en/man/html.C/sh.C.html

SCO OpenServer™ documentation for sh (by Xinuos).
----
Title: Unix sh manual page (archived)
Link: http://web.archive.org/web/20110204094833/http://docsrv.sco.com:507/en/man/html.C/sh.C.html

The Internet Archive (Wayback Machine) link of the last
Unix sh manual page from SCO times.
----
Title: ksh88 manual page
Link: http://uw714doc.sco.com/en/man/html.1/ksh88.1.html

ksh88 was the AT&amp;T Korn Shell before ksh93 happened.
It lacks many features from later pdksh versions and
especially pdksh/mksh. It’s mainly suited for scripting
these days, and comes with many commercial/proprietary
operating systems.
----
Title: MKS Toolkit
Link: http://www.mkssoftware.com/products/tk/ds_tkdev.asp

The MKS ksh is the one David Korn lost some disapproving
words about. Nevertheless, it implements some part of the
Korn Shell language and is available for certain systems.
----
Title: Which shell and version do I run? Ⅰ
Link: http://www.mirbsd.org/cvs.cgi/contrib/code/Snippets/getshver?rev=HEAD

mirabilos’ <a href="http://www.mirbsd.org/cvs.cgi/~checkout~/contrib/code/Snippets/getshver?rev=HEAD;content-type=text%2Fplain">getshver</a>
is a script that tells you which shell it runs under. It
currently supports most Bourne Shell, POSIX Shell, Korn
Shell, Z Shell, C Shell variants as well as the TCL Shell.
----
Title: Which shell and version do I run? Ⅱ
Link: http://www.in-ulm.de/~mascheck/various/whatshell/whatshell.sh.html

Sven Mascheck also has a shell detector, with emphasis on
shells without any version variable; mostly supports old
Bourne-compatible shells including POSIX and Korn Shell
and some Z Shell but no C Shell or TCL.
----
Title: Which shell and version do I run? Ⅲ
Link: http://stchaz.free.fr/which_interpreter

This one is a tad hilarious, as it’s got support for things like
DOS <tt>CMD.EXE</tt> and possibly <tt>COMMAND.COM</tt>, Tcl, Perl,
Python and whatnot. It’s a tad terse on the Korn Shell side, though.
----
Title: shbot, as seen in #bash and #ksh
Link: https://github.com/geirha/shbot

<p class="boxhead"><tt>shbot</tt> is a bot that takes from an IRC
 channel or query commands of the form…</p><div class="boxtext">
 <pre>
	k# print ${.sh.version}
	m# print $KSH_VERSION
 </pre>
</div><p class="boxfoot">… runs them in a throw-away VM and show
 the result back to the requestor.</p>
<p>The <a href="http://www.vidarholen.net/contents/evalbot/">original
 evalbot code</a> might be of interest, as well as the <a
 href="https://github.com/geirha/shbot/blob/master/triggers">current
 list of triggers</a> for the <tt>shbot</tt> instance on <a
 href="@@RELPATH@@irc.htm">Freenode</a>. Query “sbot” to <tt>greybot</tt>
 to get what <tt>geirha</tt> says is the closest thing to documentation
 at the moment.</p>
----
Title: comp.unix.shell Frequently Asked Questions
Link: http://cfajohnson.com/shell/cus-faq.html

FAQ of the Usenet group <tt>comp.unix.shell</tt>
----
Title: csh Programming Considered Harmful
Link: http://www.faqs.org/faqs/unix-faq/shell/csh-whynot/

Rather polarising article about why the C Shell is not desirable.
----
Title: Morris Bolsky, The KornShell Command and Programming Language
ISBN: 978-0-13-516972-8 (0-13-516972-0)

Prentice Hall PTR, xvi + 356 pages, 1989.
Covers ksh88.
----
Title: Morris I. Bolsky and David G. Korn, The New KornShell Command and Programming Language (2nd Edition)
ISBN: 978-0-13-182700-4 (0-13-182700-6)

Prentice Hall PTR, xvi + 400 pages, 1995.
Covers ksh93; co-authored by its creator.
----
Title: Stephen G. Kochan and Patrick H. Wood, UNIX Shell Programming
ISBN: 978-0-672-48448-3 (0-672-48448-X)

Hayden, Revised Edition, xi + 490 pages, 1990.
----
Title: IEEE Standard for Information Technology – Portable Operating System Interface (POSIX)
ISBN: 978-1-55937-255-8 (1-55937-255-9)

IEEE Press, Part 2: Shell and Utilities, xvii + 1195 pages, 1993.
----
Title: The Open Group Base Specifications Issue 7 – IEEE Std 1003.1-2008 – Shell &#38; Utilities
Link: http://www.opengroup.org/onlinepubs/9699919799/utilities/toc.html

Online version of the POSIX/SUSv4 standard on shells.
----
Title: Bill Rosenblatt, Learning the Korn Shell
ISBN: 978-1-56592-054-5 (1-56592-054-6)

O'Reilly, 360 pages, 1993.
It’s a good introduction and reference to ksh88; most of it
(except the DEBUG trap related part) also applies to pdksh/mksh.
The ridge between shell scripting and shell programming is
surpassed a few times.
----
Title: Bill Rosenblatt and Arnold Robbins, Learning the Korn Shell, Second Edition
ISBN: 978-0-596-00195-7 (0-596-00195-9)

O'Reilly, 432 pages, 2002.
Second Edition of the famous ksh book from O’Reilly, targeting
ksh93 this time.
----
Title: Barry Rosenberg, KornShell Programming Tutorial
ISBN: 978-0-201-56324-5 (0-201-56324-X)

Addison-Wesley Professional, xxi + 324 pages, 1991.
According to the old <tt>#ksh</tt> topic, this is a “good book”.
----
Title: Introduction into Korn Shell (ksh) Programming
Link: http://www.bolthole.com/solaris/ksh.html

Basic tutorial for shell scripting, with focus on ksh.
----
Title: IBM Developerworks articles on Korn shell scripting
Link: http://www.ibm.com/developerworks/aix/library/au-kornshellscripting/

Korn shell scripting is something all UNIX® users should learn how to
use. Shell scripting provides you with the ability to automate many
tasks and can save you a great deal of time. It may seem daunting at
first, but with the right instruction you can become highly skilled in
it. This article will teach you to write your own Korn shells scripts.
----
Title: ksh - An Extensible High Level Language
Link: https://www.usenix.org/legacy/publications/library/proceedings/vhll/full_papers/korn.ksh.a

Overview of design (good and bad sides) and features of ksh,
with the advent of the new ksh93, and some history, from
David G. Korn himself.
----
Title: Unix shell scripting with ksh/bash
Link: http://www.dartmouth.edu/~rc/classes/ksh/

Course Handout for a class on shell scripting at Dartmouth university.
----
Title: * Portable Shell::
Link: http://www.gnu.org/software/autoconf/manual/html_node/Portable-Shell.html

Part of the GNU Autoconf manual dealing with how to make shell
scripts portable (if desirable to not target one specific shell,
such as ksh93 or mksh, and making that one portable). Interesting
for archæologists as well.
----
Title: Sven Mascheck’s Unix and Shell page
Link: http://www.in-ulm.de/~mascheck/

Plethora of historic and recent information on shells on
various unicēs, the shebang, urban legends, etc.
----
Title: GreyCat on processes, environments and inheritance
Link: http://mywiki.wooledge.org/ProcessManagement

Greg Wooledge’s Wiki ⇒ Notes on process management, such as,
how to properly kill one. Read also other pages from the
CategoryShell, although his KornShell page is somewhat out
of date and doesn’t apply to mksh often.
----
Title: A Guide to Unix Shell Quoting
Link: http://www.mpi-inf.mpg.de/~uwe/lehre/unixffb/quoting-guide.html

Uwe Waldmann’s lengthy, exhaustive guide to quoting correctly.
----
Title: UNIX Shell Quote Tutorial
Link: http://www.grymoire.com/Unix/Quote.html

Short tutorial for correct quoting in the pre-POSIX Bourne
Shell, as well as the C Shell.
----
Title: Plänet Commandline
Link: http://planet-commandline.org/?Amber+Screen

RSS/Atom aggregator with topics related to the command line.
----
Title: Programming Language News – Shell
Link: http://web.archive.org/web/20101211175816/http://plnews.org/category/Languages__Shell/

Generic shell-related newsfeed.
----
Title: Shell-Toolkit (shellsnippets)
Link: https://evolvis.org/plugins/scmgit/cgi-bin/gitweb.cgi?p=shellsnippets/shellsnippets.git

Loose collection of fragments of shell scripts and programmes of random
usefulness, which may or may not work. The intent is to have a collection
of code to aid those who learn by reading other peoples’ code by providing
some examples of (hopefully) better than average quality.
----
Title: Solaris ksh93-integration project
Link: http://web.archive.org/web/20090927131746/http://opensolaris.org/os/project/ksh93-integration

Homepage of the project attempting to integrate ksh93 in Solaris,
replacing both ksh88 and their Bourne (nōn-POSIX) <tt>/bin/sh</tt>.
(Although <tt>mirabilos</tt> thinks that the old ksh88 should not
be available as <tt>/usr/bin/oksh</tt> but rather ksh88, due to
oksh’s existence as pdksh derivate.)
----
Title: OpenSolaris shell coding style guidelines
Link: http://web.archive.org/web/20121103080047/http://hub.opensolaris.org/bin/view/Project+shell/shellstyle

[DRAFT] Bourne/Korn Shell Coding Conventions
----
Title: Evolution of shells in Linux – From Bourne to Bash and beyond
Link: https://www.ibm.com/developerworks/linux/library/l-linux-shells/index.html

11-page article in IBM developerWorks by M. Tim Jones; Summary:
Pointing and clicking is fine for most day-to-day computing tasks,
but to really take advantage of the strengths of Linux over other
environments, you eventually need to crack the shell and enter the
command line. Lots of command shells are available, from Bash and
Korn to C shell and various exotic and strange shells. Learn which
shell is right for you.
----
Title: bosh – Schily Bourne Shell
Link: http://schilytools.sourceforge.net/bosh.html

Documentation and source code project based on the Bourne Shell
codebase. Maintained by J�rg/Jvrg/Joerg/Jörg Schilling.
----
Title: KornShell Documentation
Link: http://kornshell.com/doc/

Collection of ksh-related documents (links, books, etc.) similar to
this one. Maintained by David G. Korn; some links may be stale.
----
Title: The UNIX Grymoire
Link: http://www.grymoire.com/Unix/

Collection of Unix-related documents, with some sections on shells
and related utilities.
----
