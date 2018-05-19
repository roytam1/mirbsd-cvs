RCSID: $MirOS: www/data/wlog2018.inc,v 1.4 2018/05/19 16:47:48 tg Exp $
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
Date: 2018-05-19 18:45 +0200
Title: Progress report from the Movim packaging sprint at MiniDebconf
Tag: debian

<p>Nik wishes you to know that the Movim packaging sprint (sponsored
 by the DPL, thank you!) is handled under the umbrella of the Debian
 Edu sprint (similarily sponsored) since this package is handled by
 the Teckids Debian Task Force, personnel from Teckids e.V.</p>
<p>After arriving, I’ve started collecting knowledge first. I reviewed
 upstream’s <tt>composer.json</tt> file and Wiki page about dependencies
 and, after it quickly became apparent that we need <em>much</em> more
 information (e.g. which versions are in sid, what the package names are,
 and, most importantly, <strong>recursive</strong> dependencies), a <a
 href="https://wiki.teckids.org/wiki/MovimPaketierungsNotizen">Wiki page
 of our own</a> grew. Then I made a hunt for information about how to
 package stuff that uses PHP Composer upstream, and found the, ahem,
 wonderfully abundant, structured, plentiful and clear documentation from
 the Debian PHP/PEAR Packaging team. (Some time and reverse-engineering
 later I figured out that we just ignore <tt>composer</tt> and read its
 control file in <tt>pkg-php-tools</tt> converting dependency information
 to Debian package relationships. Much time later I also figured out it
 mangles package names in a specific way and had to rename one of the
 packages I created in the meantime… thankfully before having uploaded
 it.) Quickly, the Wiki page grew listing the package names we’re supposed
 to use. I created a package which I could use as template for all others
 later.</p>
<p>The upstream Movim developer arrived as well — we have quite an amount
 of upstream developers of various projects attending MiniDebConf, to the
 joy of the attendees actually directly involved in Debian, and this makes
 things much easier, as he immediately started removing dependencies (to
 make our job easier) and fixing bugs and helping us understand how some
 of those dependencies work. (I also contributed code upstream that replaces
 some Unicode codepoints or sequences thereof, such as 3⃣ or ‼ or 👱🏻‍♀️,
 with &lt;img…/&gt; tags pointing to the SVG images shipped with Movim, with
 a description (generated from their Unicode names) in the alt attribute.)</p>
<p>Now, Saturday, all dependencies are packaged so far, although we’re still
 waiting for maintainer feedback for those two we’d need to NMU (or have them
 upload or us take the packages over); most are in NEW of course, but that’s
 no problem. Now we can tackle packaging Movim itself — I guess we’ll see
 whether those other packages actually work then ☺</p>
<p>We also had a chance to fix bugs in other packages, like guacamole-client
 and musescore.</p>
<p>In the meantime we’ve also had the chance to socialise, discuss, meet, etc.
 other Debian Developers and associates and enjoy the wonderful food and superb
 coffee of the “Cantina” at the venue; let me hereby express heartfelt thanks
 to the MiniDebConf organisation for this good location pick!</p>
<p><strong>Update</strong>, later this night: we took over the remaining two
 packages with permission from their previous team and uploader, and have
 already started with actually packaging Movim, discovering untold gruesome
 things in the <em>upstream</em> of the two webfonts it bundles.</p>
----
