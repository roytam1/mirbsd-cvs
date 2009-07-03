# $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $
#-
# Copyright (c) 2009
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
# standalone (interactive use) randex Bot plugin for MirSirc (beta)

my $userinterval = 30;
my $channelinterval = 600;

use BSD::arc4random qw(:all);
use POSIX qw(strftime);

@users = ();

sub hook_nameslist {
  local($g, $m, $c, $r)=split(/ +/, $args, 4);
  return unless &eq($c, "##/dev/arandom");
  $r =~ s/^://;
  my @nicks = split(/ +/, $r);

  foreach my $luser (@nicks) {
    $luser =~ s/^[\@\+]//;
    next if (&eq($luser, "chanserv") ||
      &eq($luser, $nick));
    push (@users, $luser);
  }
# $logging && print LOG "=>D: names_hook, appending <$r> to users yielding <@users>\n";
}
&addhook("353", "nameslist");

sub timetrigger {
  my $interval;
  my $target;

  if (@users) {
    $target = shift @users;
    $interval = arc4random_uniform($userinterval) + ($userinterval / 2);
  } else {
    $target = "##/dev/arandom";
    $interval = arc4random_uniform($channelinterval) + ($channelinterval / 2);
    &sl("NAMES ##/dev/arandom");
  }
  &timer($interval, "&timetrigger");
# $logging && print LOG "=>D: writing to $target, users is <@users>\n";

  local($t) = pack("u", arc4random_bytes(32, "$target @users"));
  chop($t);

  &sl("PRIVMSG $target :\caENTROPY $t\ca");
}

sub hook_joined {	# whenever someone joins
  return if &eq($who, $nick);
  return unless &eq($_[0], "##/dev/arandom");

  local($t) = pack("u", arc4random_bytes(32, "$who ($user\@$host) joined $_"));
  chop($t);

  &sl("PRIVMSG $who :\caENTROPY $t\ca");
  push @users, $who;
# $logging && print LOG "=>D: <$who> joined, users is now <@users>\n";
}
&addhook("join", "joined");

sub hook_left {
  my $i;

  return if &eq($who, $nick);
  return unless &eq($_[0], "##/dev/arandom");

  arc4random_pushb("$who ($user\@$host) left $_");
  if (@users) {
    for ($i = 0; $i <= $#users; $i++) {
      if (&eq($users[$i], $who)) {
#	$logging && print LOG "=>D: LEFT $i <$who> eq <$users[$i]>\n";
	splice (@users, $i, 1);
	last;
#     } else {
#	$logging && print LOG "=>D: LEFT $i <$who> ne <$users[$i]>\n";
      }
    }
  }
# $logging && print LOG "=>D: <$who> left, users is now <@users>\n";
}
&addhook("leave", "left");
&addhook("signoff", "left");

&timetrigger;
print "randexPlug.pl initialised.\n";
1;
