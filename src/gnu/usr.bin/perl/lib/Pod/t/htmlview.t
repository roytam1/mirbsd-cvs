#!/usr/bin/perl -w                                         # -*- perl -*-

BEGIN {
   chdir 't' if -d 't';
   unshift @INC, '../lib';
   unshift @INC, '../lib/Pod/t';
   require "pod2html-lib.pl";
}

use strict;
use Test::More tests => 1;

convert_n_test("htmlview", "html rendering");

__DATA__
<?xml version="1.0" ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>NAME</title>
<meta http-equiv="content-type" content="text/html; charset=utf-8" />
<link rev="made" href="mailto:[PERLADMIN]" />
</head>

<body style="background-color: white">

<p><a name="__index__"></a></p>
<!-- INDEX BEGIN -->

<ul>

	<li><a href="#name">NAME</a></li>
	<li><a href="#synopsis">SYNOPSIS</a></li>
	<li><a href="#description">DESCRIPTION</a></li>
	<li><a href="#methods____other_stuff">METHODS =&gt; OTHER STUFF</a></li>
	<ul>

		<li><a href="#new__"><code>new()</code></a></li>
		<li><a href="#old__"><code>old()</code></a></li>
	</ul>

	<li><a href="#testing_for_and_begin">TESTING FOR AND BEGIN</a></li>
	<li><a href="#testing_urls_hyperlinking">TESTING URLs hyperlinking</a></li>
	<li><a href="#see_also">SEE ALSO</a></li>
</ul>
<!-- INDEX END -->

<hr />
<p>
</p>
<h1><a name="name">NAME</a></h1>
<p>Test HTML Rendering</p>
<p>
</p>
<hr />
<h1><a name="synopsis">SYNOPSIS</a></h1>
<pre>
    use My::Module;</pre>
<pre>
    my $module = My::Module-&gt;new();</pre>
<p>
</p>
<hr />
<h1><a name="description">DESCRIPTION</a></h1>
<p>This is the description.</p>
<pre>
    Here is a verbatim section.</pre>
<p>This is some more regular text.</p>
<p>Here is some <strong>bold</strong> text, some <em>italic</em> and something that looks 
like an &lt;html&gt; tag.  This is some <code>$code($arg1)</code>.</p>
<p>This <code>text contains embedded bold and italic tags</code>.  These can 
be nested, allowing <strong>bold and <em>bold &amp; italic</em> text</strong>.  The module also
supports the extended <strong>syntax </strong>&gt; and permits <em>nested tags &amp;
other <strong>cool </strong></em>&gt; stuff &gt;&gt;</p>
<p>
</p>
<hr />
<h1><a name="methods____other_stuff">METHODS =&gt; OTHER STUFF</a></h1>
<p>Here is a list of methods</p>
<p>
</p>
<h2><a name="new__"><code>new()</code></a></h2>
<p>Constructor method.  Accepts the following config options:</p>
<dl>
<dt><strong><a name="item_foo">foo</a></strong>

<dd>
<p>The foo item.</p>
</dd>
</li>
<dt><strong><a name="item_bar">bar</a></strong>

<dd>
<p>The bar item.</p>
</dd>
<p>This is a list within a list</p>
<ul>
<li>
<p>The wiz item.</p>
</li>
<li>
<p>The waz item.</p>
</li>
</ul>
<dt><strong><a name="item_baz">baz</a></strong>

<dd>
<p>The baz item.</p>
</dd>
</li>
</dl>
<p>Title on the same line as the =item + * bullets</p>
<ul>
<li><strong><a name="item_black_cat"><code>Black</code> Cat</a></strong>

<li><strong><a name="item_sat_on_the">Sat <em>on</em>&nbsp;the</a></strong>

<li><strong><a name="item_mat_3c_21_3e">Mat&lt;!&gt;</a></strong>

</ul>
<p>Title on the same line as the =item + numerical bullets</p>
<ol>
<li><strong><a name="item_cat">Cat</a></strong>

<li><strong><a name="item_sat">Sat</a></strong>

<li><strong><a name="item_mat">Mat</a></strong>

</ol>
<p>No bullets, no title</p>
<dl>
<dt>
<dd>
<p>Cat</p>
</dd>
</li>
<dt>
<dd>
<p>Sat</p>
</dd>
</li>
<dt>
<dd>
<p>Mat</p>
</dd>
</li>
</dl>
<p>
</p>
<h2><a name="old__"><code>old()</code></a></h2>
<p>Destructor method</p>
<p>
</p>
<hr />
<h1><a name="testing_for_and_begin">TESTING FOR AND BEGIN</a></h1>
<br>
<p>
blah blah
</p><p>intermediate text</p>
<more>
HTML
</more>some text<p>
</p>
<hr />
<h1><a name="testing_urls_hyperlinking">TESTING URLs hyperlinking</a></h1>
<p>This is an href link1: <a href="http://example.com">http://example.com</a></p>
<p>This is an href link2: <a href="http://example.com/foo/bar.html">http://example.com/foo/bar.html</a></p>
<p>This is an email link: <a href="mailto:mailto:foo@bar.com">mailto:foo@bar.com</a></p>
<pre>
    This is a link in a verbatim block &lt;a href=&quot;<a href="http://perl.org">http://perl.org</a>&quot;&gt; Perl &lt;/a&gt;</pre>
<p>
</p>
<hr />
<h1><a name="see_also">SEE ALSO</a></h1>
<p>See also <a href="/t/htmlescp.html">Test Page 2</a>, the <a href="/Your/Module.html">the Your::Module manpage</a> and <a href="/Their/Module.html">the Their::Module manpage</a>
manpages and the other interesting file <em>/usr/local/my/module/rocks</em>
as well.</p>

</body>

</html>
