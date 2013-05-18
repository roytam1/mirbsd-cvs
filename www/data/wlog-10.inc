Date: 10.03.2008
Author: tg@

<p>Our kernel now should handle signals wrt the extended i386/amd64
 ABI fine: thanks to the Debian GNU/kFreeBSD developer Aurelien
 “aurel32” Jarno, the direction flag (DF) is now cleared on traps.</p>
----
Date: 12.03.2008
Author: tg@

<p>The new cksum port sets a variable HAS_CKSUM, which will be used
 really soon now in the MirPorts infrastructure to replace all the
 old cruft (_CKSUM_A, _CKSUM_SIZE, _HASHES). From RSN on, you will
 either have our current cksum(1) from MirOS #10 or MirPorts, or
 you won’t, in which case it will only use the “cksum” algorithm
 of the OS’ own cksum programme (which is rather ubiquitous).</p>
<p>We have a new sample file, “portmdoc”, and I’ve converted yet
 another manpage to be fixed with regards to GNU groff, like I did
 with mksh(1) after the R33 release. Expect this to continue.</p>
<p>The FSF is now mistaking that lazy moronic finnish student’s
 excuse for a patch management system for a version control system
 as well… the config.{guess,sub} files are now in git. Yuck!</p>
----
Date: 13.03.2008
Author: tg@

<p>Besides from my TODO on MirPorts (and the portable subprojects)
 and MidnightBSD, and the release engineering process, and my other
 want-to-do hobbies like hercules(4) wsfb(4) support (and an XF86
 module, and emulation support for a HGC in qemu), and a couple of
 other things, Waldemar has made a point:</p>
<p>MirOS definitively needs to shift away from “we want to make
 OpenBSD better, and we do X, Y and Z” towards “we want to do X, Y
 and Z, specialise on W, support V, and while doing all that, we
 are of course as secure as OpenBSD and track their goodies, and by
 the way, we have GNOME and Frozen-Bubble”. This would give the MirOS
 Project an actual face, which could attract users and development
 capability/potential. (And it would imply a re-design of the Flyers’
 and website’s content…) We’ll have to think about it, but he is
 probably right.</p>
----
Date: 14.03.2008
Author: tg@
Title: GPLv3

<p>As written in my earlier entry (still to be ok’d by benz) about <a
 href="@@RELPATH@@permalinks/wlog-9_e20080313-tg-g10002.htm">GPLv3</a>,
 editors/nano is okay (for now). This means that rsync 3 is probably ok
 to go in now too (especially since we have no patches). It’s said to be
 much faster and less RAM-hungry, which is especially nice.</p>
----
Date: 14.03.2008
Author: tg@

<p>The <a href="@@RELPATH@@ports.htm">MirPorts Framework</a> can now be
 used on <a href="http://www.midnightbsd.org/">MidnightBSD</a> out of
 the box, no special patching needed. MirMake, MirCpio, MirCksum and the
 package tools have been updated appropriately.</p>
<p>However, MirLibtool support is still missing. This is trivial, I just
 don’t have the time to do it right now, as I should be doing the release
 at the moment. Still, feel free to play with it.</p>
<p>Yeah. I did port MirLibtool to mnbsd, and found a bug (in upstream,
 even) while doing it. Nicey. Both devel/glib1 (autoconf-2.13) and
 devel/libtool (autoconf-2.61) seem to work (regarding libtool build
 systems, shared library building/naming, etc.) for now. I’m a little
 bit unsure about shared library <em>naming</em> conventions, but you
 can follow FreeBSD’s, even though Todd Vierling and I think they are
 weird and/or not what one wants. (For insiders like Benny: they do not
 use current/age/revision, set the third number to 0.)</p>
<p>We have a new “p5” port module, which must now be referenced by any
 users of ${P5ARCH} which do not include the “perl” module.</p>
<p>pvalchev@obsd replied to my issues with the UMAC64 hash that I might
 want to report the bug in lingcc’s umoddi3 implementation upstream.
 This shall be my TODO, someone please remember me to do it (check how
 to reproduce on $common_os, with $latest_gcc, etc).</p>
<p>miod@openbsd is helping me with the tvtwo(4) card – unluckily, I’m
 unable to test diffs because my monitor is too small… Doesn’t anyone
 happen to want to give away a TFT that can do 1152x900 for free? ☺</p>
----
