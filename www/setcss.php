<?php
/* $MirOS$ */
/*-
 * The MirOS Project - Webpages
 * Copyrighted material; read LICENCE for terms of use.
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
