# $MirOS: ports/net/irssi/files/randex.pl,v 1.2 2008/07/15 14:01:41 tg Exp $
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

use vars qw($VERSION %IRSSI);
$VERSION = '20080720';
%IRSSI = (
	authors		=> 'Thorsten Glaser',
	contact		=> 'tg@mirbsd.de',
	name		=> 'randex',
	description	=> 'implement MirSirc\'s randex protocol',
	license		=> 'MirOS',
	url		=> 'http://cvs.mirbsd.de/ports/net/sirc/dist/dsircp',
	changed		=> $VERSION,
	modules		=> 'BSD::arc4random',
	commands	=> "randex"
);

use BSD::arc4random qw(:all);
use Fcntl qw(:DEFAULT :flock);
use File::Path qw(mkpath);
use File::Basename qw(dirname);

our $irssi_ctcp_version_reply = '';

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

	$s = pack("u", arc4random_bytes(32, "for $towho"));
	chop($s);
	$recip->send_raw("PRIVMSG ${towho} :\caENTROPY ${s}\ca");
	Irssi::print("Initiating the RANDEX protocol with ${towho}");
}

sub
process_entropy_request
{
	my ($server, $args, $nick, $address, $target) = @_;
	my $evalue = pack("u", arc4random_bytes(32,
	    "from $nick $args $address $target"));
	chop($evalue);
	Irssi::print("${nick} initiated the RANDEX protocol with ${target}");
	$server->ctcp_send_reply("NOTICE ${nick} :\caRANDOM ${evalue}\ca");
}

sub
process_random_response
{
	my ($server, $args, $nick, $address, $target) = @_;
	my $t = (BSD::arc4random::have_kintf() ? "" : "not ") .
	    "pushing to kernel";

	arc4random_pushb("by $nick $args $address $target");
	Irssi::print("RANDEX protocol reply from $nick to $target, $t");
}

sub
process_ctcp_before
{
	my $v = Irssi::settings_get_str("ctcp_version_reply");

	if (!$v) {
		$v = 'irssi v$J - running on $sysname $sysarch';
	}
	$irssi_ctcp_version_reply = $v;
	$v .= " (RANDOM=" . $RANDOM . ")";
	Irssi::settings_set_str("ctcp_version_reply", $v);
}

sub
process_ctcp_after
{
	if ($irssi_ctcp_version_reply) {
		Irssi::settings_set_str("ctcp_version_reply",
		    $irssi_ctcp_version_reply);
	}
}

sub
randfile_loadstore
{
	my $randfile = Irssi::settings_get_str("randfile");
	my $tryread = 0;
	my $data = '';
	my $dlen = 0;
	my $fh;
	my $fhopen = 0;
	my $dir;

	$randfile = $ENV{'HOME'} . "/.pgp/randseed.bin"
	    if (!defined($randfile) || !$randfile);
	$dir = dirname($randfile);
	if (! -d $dir) {
		eval { mkpath([$dir]) };
		if ($@) {
			$randfile = "/tmp/randfile." . $RANDOM;
		}
	}
	$randfile = "/tmp/randfile." . $RANDOM unless (-d dirname($randfile));
	Irssi::settings_set_str("randfile", $randfile);
	stat($randfile);
	if (-b _ || -c _) {
		$tryread = 4;
	} elsif (-s _) {
		$tryread = -s $_;
	}
	if ($tryread && sysopen($fh, $randfile, O_RDWR)) {
		$fhopen = 1;
		$dlen = sysread($fh, $data, $tryread)
		    or $fhopen = 0;
		if (defined($dlen) && $dlen) {
			my $d = $data;

			$data = arc4random_bytes(256);
			$dlen = 256;
			arc4random_addrandom($d);
		} else {
			$dlen = 0;
			$data = '';
		}
		close($fh) unless $fhopen;
	}
	if (!$fhopen && sysopen($fh, $randfile, O_WRONLY | O_CREAT, 0600)) {
		$fhopen = 1;
	}
	if (!$fhopen) {
		Irssi::print("Cannot write to randfile '$randfile'!");
		return;
	}
	if (!flock($fh, LOCK_EX)) {
		Irssi::print("warning: cannot lock '$randfile'");
	}
	truncate($fh, 0);
	$data .= arc4random_bytes(512 - $dlen);
	syswrite($fh, $data, length($data));
	close($fh);
}

my $tmo_randfile = undef;
my $g_interval;

sub
randfile_timeout
{
	my $status = shift;
	my $interval = $g_interval = Irssi::settings_get_int("rand_interval");

	if (!defined($interval) || $interval !~ /^[0-9]+$/) {
		$interval = 900;
	}
	Irssi::settings_set_int("rand_interval", $interval);
	if (($status == 0 && $interval > 0) || $status == 1) {
		randfile_loadstore();
	}
	$interval = 900 if ($interval == 0);
	$tmo_randfile = Irssi::timeout_add_once($interval * 1000,
	    "randfile_timeout", 0);
}

sub
sig_setup_changed
{
	Irssi::timeout_remove($tmo_randfile) if defined($tmo_randfile);
	randfile_timeout(2)
	    if ($g_interval != Irssi::settings_get_int("rand_interval"));
}

sub
sig_quitting
{
	randfile_loadstore();
}

Irssi::settings_add_int("randex", "rand_interval", 900);
{
	my $randfile = $ENV{'RANDFILE'};

	if (!defined($randfile) || !$randfile) {
		$randfile = $ENV{'HOME'} . "/.pgp/randseed.bin";
	}
	Irssi::settings_add_str("randex", "randfile", $randfile);
}

Irssi::signal_add('gui exit', \&sig_quitting);
Irssi::command_bind('randex', 'cmd_randex');
Irssi::signal_add('ctcp msg entropy', \&process_entropy_request);
Irssi::signal_add('ctcp reply random', \&process_random_response);
Irssi::ctcp_register("ENTROPY");
Irssi::signal_add_first('ctcp msg version', \&process_ctcp_before);
Irssi::signal_add_last('ctcp msg version', \&process_ctcp_after);
Irssi::print("randex.pl ${VERSION} loaded, entropy is " .
    (BSD::arc4random::have_kintf() ? "" : "not ") .
    "pushed to the kernel");
randfile_timeout();
Irssi::signal_add('setup changed', \&sig_setup_changed);

1;
