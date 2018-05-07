RCSID: $MirOS: www/data/wlog2018.inc,v 1.2 2018/05/05 23:58:21 tg Exp $
Title: FixedMisc [MirOS] 20180429 released
Date: 29.04.2018 17:30
Author: tg@
Tag: news pcli

<p>Today I’ve released another new CVS snapshot of the <a
 href="@@ABSPATH@@/MirOS/dist/mir/Foundry/"><tt>FixedMisc [MirOS]</tt>
 font</a>; as usual, the tarball contains the font in BDF form, with
 no conflict with the system <tt>Fixed [Misc]</tt> font; <a
 href="@@RELPATH@@cvs.cgi/contrib/fonts/fixed/">sources</a>
 for use (compilation, editing) with bdfctool(1) are in CVS.</p>
----
Date: 2018-05-05 17:11
Title: Website consolidation

<p>I’m currently working on consolidating <tt>mirsolutions.de</tt>
 (as my former business is long defunct) and “The MirOS Project”
 (that as of 2018 is also back to being my own one-man show / hobby)
 into <tt>www.mirbsd.org</tt> as my hobby / personal sorta homepage
 to not need any vhosts and simplify EU-DSGVO conformity. (I’ve also
 reduced logging.) Please excuse upheavals, as well as the continued
 presence of old, obsoleted or outdated content that may even be, as
 of now, completely wrong; I’ll fix it as time permits.</p>
----
Date: 2018-05-07 00:25
Title: mksh bugfix — thank you for the music
Tag: bug debian mksh pcli

<p>I’m currently working on an mksh(1) and bc(1) script that takes
 a pitch standard (e.g. “A₄ = 440 Hz” or “C₄ = 256 Hz”) and a config
 file describing a temperament (e.g. the usual equal temperament,
 or Pythagorean untempered pure fifths (with the wolf), or “just”
 intonation, Werckmeister Ⅲ, Vallotti or Bach/Lehman 1722 (to name
 a few; these are all temperaments that handle enharmonics the same
 or, for Pythagorean in out case, ignore the fact they’re unplayable).
 Temperaments are rule-based, like in ttuner. Well, I’m not quite
 there yet, but I’m already able to display the value for MuseScore
 to adjust its pitch standard (it can only take A₄-based values), a
 frequency table, and a list and table of cent deltas (useful for using
 or comparing with other tuners). Of course, right now, the cent deltas
 are all 0 because, well, they are equal temperament against equal
 temperament (as baseline), but I can calculate <em>that</em> with
 arbitrary and very high precision!</p>
<p>For outputting, I wanted to make the tables align nicely; column(1),
 which I normally use, was out because it always left-aligns, so I used
 string padding in Korn Shell — except I’m also a Unicode BMP fan, so I
 had F♯ and B♭ in my table headings, which were for some reason correctly
 right-aligned (for when the table values were integers) but not padded
 right when aligning with the decimal dot. So I worked around it, but
 also investigated.</p>
<p>Turns out that the desired length was used as second snprintf(3)
 argument, instead of, as in the right-align case, the buffer size.
 This worked only until multibyte characters happened. A fun bug,
 which only took about three minutes to find, and is covered by a
 new check in the testsuite even. Thought I’d share.</p>
<p>Feedback on and improvements for the tuner, once it’ll be done,
 are, of course, also welcome. I plan to port the algorithm (once
 I’ve got it down in a programming language I know <em>well</em>)
 to QML for inclusion in the tuner MuseScore plugin, even. Check <a
 href="@@ABSPATH@@/music/resources/tuner.sh">here, for now</a>, for
 my work in progress… it’s quite big already despite doing basically
 nothing. Foundation laid (or so…).</p>
----
