<?php
/* $MirOS: www/getnam.php,v 1.7 2005/08/04 09:03:33 tg Exp $ */
/*-
 * The MirOS Project - Webpages
 * Copyrighted material; read LICENCE for terms of use.
 *-
 * This is a fake of the "master" CMS manager file.
 * Find out which filename to use for generation!
 */

	require("vfuncs.php");

	if (!empty($_SERVER["QUERY_STRING"])) {
		$rqx = urldecode($_SERVER["QUERY_STRING"]);
	} else {
		$rqx = "main";
	}
	$rq = mybase64($rqx).".inc";

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
<p>Backlinks: <a href="/">Home</a> <a href="/?<?php
 echo $rqx; ?>">to <?php echo $rqx; ?> (<?php echo $rq; ?>)</a></p>
<p>Please don't forget to check for correct XHTML validation, even
 if it sometimes sucks. Character set to use for include files is
 ISO_646.irv:1991 (US-ASCII compatible); utf-8 is tolerated but you
 <strong>will</strong> get a problem with me! :)</p>
<?php $tg_realm=0; include("vend.php"); ?>
