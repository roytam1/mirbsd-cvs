<?php
/* $MirOS: www/reloc.php,v 1.1 2006/03/30 12:50:26 tg Exp $ */
/*-
 * The MirOS Project - Webpages
 * Copyrighted material; read LICENCE for terms of use.
 *-
 * This script can be used to relocate single pages of our homepage.
 */

	ob_start();
	require "index.php";
	$contents = ob_get_contents();
	ob_end_clean();
	$mirror = "http://www.mirbsd.org/";
	echo ereg_replace("([[:space:]]href=\")/", "\\1$mirror", $contents);
?>
