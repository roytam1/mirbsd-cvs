<?php
/* $MirOS$ */
/*-
 * The MirOS Project - Webpages
 * Copyrighted material; read LICENCE for terms of use.
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
