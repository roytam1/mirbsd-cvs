<?php
/* $MirOS: www/vend.php,v 1.18 2004/11/12 18:00:54 tg Exp $
 *-
 * Copyright (c) 1999, 2002, 2003, 2004
 *	Thorsten "mirabile" Glaser <tg@66h.42h.de>
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
 * This is the footer, mostly shared with Thorsten Glasers personal
 * homepage. Editors must be aware of the fact that I reserve the right
 * to synchronize these two.
 */

 // Check if we are initialized
 if ( (!isset($tg_init)) || ($tg_init != "v11") ) {
?><pre>

UNAUTHORIZED USE OF CODE - ERROR DETECTED!<br />
REPORT mailto:tg@trash.net RIGHT NOW!

<?php
	exit;
 }
?><div class="footer">
&bull; <a href="http://mirbsd.de/impressum">Impressum</a> &bull;
<a href="http://validator.w3.org/check/referer">Valid <?php
	echo substr_replace($tg_htt0, "/", strpos($tg_htt0, " "), 1)."!</a>\n";
?> - <a href="http://jigsaw.w3.org/css-validator/validator?warning=1&amp;profile=none&amp;uri=<?php
	echo urlencode($tg_sur);	?>">Valid CSS!</a><?php
?> - <small><a href="mailto:miros-discuss@66h.42h.de">eMail</a>
 contact to</small> the MirOS Project</div>
</body></html>
