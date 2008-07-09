# $MirOS: contrib/code/Snippets/randex.pl,v 1.2 2008/07/08 23:36:27 tg Exp $
#-
# Copyright (c) 2008
#	Thorsten Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.
#-
# Irssi extension to support MirSirc's randex protocol

require BSD::arc4random;

use vars qw($VERSION %IRSSI);
$VERSION = '200807090012';
%IRSSI = (
	authors		=> 'Thorsten Glaser',
	contact		=> 'tg@mirbsd.de',
	name		=> 'randex',
	description	=> 'implement MirSirc\'s randex protocol',
	license		=> 'MirOS',
	url		=> 'http://cvs.mirbsd.de/ports/net/sirc/dist/dsircp',
	changed		=> $VERSION,
	modules		=> '',
	commands	=> "randex"
);

sub
cmd_randex
{
	my ($data, $server, $witem) = @_;
	my $recip = undef;
	my $towho;
	my $s;

	if (!$server || !$server->{connected}) {
		Irssi::print("Not connected to server");
		return;
	}

	if ($data) {
		$recip = $server;
		$towho = $data;
	} elsif ($witem && ($witem->{type} eq "QUERY")) {
		$recip = $witem->{server};
		$towho = $witem->{name};
	}
	if (!defined($recip)) {
		Irssi::print("You must specify a nick or channel!");
		return;
	}

	$s = pack("u", BSD::arc4random::arc4random_bytes(32, "for $towho"));
	chop($s);
	$recip->send_raw("PRIVMSG ${towho} :\caENTROPY ${s}\ca");
}

sub
process_entropy_request
{
	my ($server, $args, $nick, $address, $target) = @_;
	my $evalue = pack("u", BSD::arc4random::arc4random_bytes(32,
	    "from $nick $args"));
	chop($evalue);
	$server->ctcp_send_reply("NOTICE ${nick} :\caRANDOM ${evalue}\ca");
}

sub
process_random_response
{
	my ($server, $args, $nick, $address, $target) = @_;

	BSD::arc4random::arc4random_pushk("by $nick $args");
}

Irssi::command_bind('randex', 'cmd_randex');
Irssi::signal_add('ctcp msg entropy', \&process_entropy_request);
Irssi::signal_add('ctcp reply random', \&process_random_response);
Irssi::ctcp_register("ENTROPY");
