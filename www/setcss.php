<?php
/* $MirBSD: www/setcss.php,v 1.4 2004/05/08 23:00:47 tg Exp $
 *-
 * Copyright (c) 2004
 *	Thorsten Glaser <tg@66h.42h.de>
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
 * Checks for readability of chosen style sheet and sets cookie
 */

$parm = $_GET['sheet'];
$tmp = "vs".$parm.".css";
if (!is_readable($tmp)) {
	$parm = "";
}

if (!empty($parm)) {
	setcookie("usecss", $parm, time() + 31556736);
	$text = "Selected Stylesheet vs".$parm.".css";
} else {
	setcookie("usecss", "", time() + 60);
	$text = "Emptied Stylesheet cookie and set default CSS";
}
require("vbegin.php");
?>
 <title>MirOS CSS Select</title>
 <meta name="robots" content="noindex" />
</head><body>
<h1>CSS selection results</h1>
<p><?php echo $text; ?>.</p>
<p><a href="/?main"><big>Back</big> to the homepage</a></p>
</body></html>
