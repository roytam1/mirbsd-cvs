<?php
/* $MirOS$ */
/*-
 * The MirOS Project - Webpages
 * Copyrighted material; read LICENCE for terms of use.
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
