<?php
/* $MirOS: www/getnam.php,v 1.3 2004/11/04 10:14:26 tg Exp $
 *-
 * Copyright (c) 1999, 2002, 2003 Thorsten Glaser <tg@66h.42h.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. All marketing or advertising materials mentioning features or
 *    use of this product must display the following acknowledgement:
 *    * This product includes material provided by Thorsten Glaser.
 * 4. Neither the name of Thorsten Glaser or the MirOS project nor
 *    the names of their contributors may be used to endorse or pro-
 *    mote products derived from this software without specific prior
 *    written permission.
 * 5. If this work is used on world wide web pages, the authors must
 *    be given due credits in the site's imprint.
 * 6. This licence automatically ends if the site of licensee is not
 *    easily distinguishable from Thorsten Glaser's personal homepage
 *    or the MirOS project's site.
 * 7. This licence does not cover usage of the pictures used on the
 *    pages, especially not the BSD Dæmon or the MirOS/MirAbile logo.
 *
 * This work is provided "as is" with no explicit or implicit warran-
 * ties whatsoever to the maximum extend permitted by applicable law;
 * in no event may an author or contributor be held liable for damage
 * that is, directly or indirectly, caused by the work, even if advi-
 * sed of the possibility of such damage.
 *-
 * This is a fake of the "master" CMS manager file.
 * Find out which filename to use for generation!
 */

	require("vfuncs.php");

	if (!empty($_SERVER["QUERY_STRING"])) {
		$rq = urldecode($_SERVER["QUERY_STRING"]);
	} else {
		$rq = "main";
	}
	$rq = mybase64($rq).".inc";

	require("vbegin.php");
?>
 <title>The MirOS Project :: Internal Information Page</title>
 <meta name="robots" content="index, follow" />
</head><body>
<h1>File Name Generation</h1>
<p>The file you requested:
 <tt><?php echo $_SERVER["QUERY_STRING"]; ?></tt> (still
 in urlencoded form) has the following filename:</p><pre>
<?php echo "www/content/".$rq; ?>
</pre>
<p>Please don't forget to check for correct XHTML validation, even
 if it sometimes sucks. Character set to use for include files is
 ISO_646.irv:1991 (US-ASCII compatible); utf-8 is tolerated but you
 <strong>will</strong> get a problem with me! :)</p>
<?php $tg_realm=0; include("vend.php"); ?>
