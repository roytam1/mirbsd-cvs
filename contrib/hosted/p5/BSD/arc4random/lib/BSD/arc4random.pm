# $MirOS: contrib/hosted/p5/BSD/arc4random/lib/BSD/arc4random.pm,v 1.20 2008/07/12 19:21:56 tg Exp $
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

package BSD::arc4random;

use 5.004_63;
use strict;
use warnings;
use integer;
use threads::shared;

BEGIN {
	require Exporter;
	require DynaLoader;
	use vars qw($VERSION @ISA @EXPORT @EXPORT_OK %EXPORT_TAGS);
	$VERSION = 1.03;
	@ISA = qw(Exporter DynaLoader);
	@EXPORT = qw();
	@EXPORT_OK = qw(
		&arc4random
		&arc4random_addrandom
		&arc4random_bytes
		&arc4random_pushb
		&arc4random_pushk
	);
	%EXPORT_TAGS = (
		all => [ @EXPORT_OK ],
	);
}

sub have_kintf() {}	# public constant function, prototyped

my $arcfour_lock : shared;

bootstrap BSD::arc4random $BSD::arc4random::VERSION;

sub
arc4random()
{
	lock($arcfour_lock);
	return &arc4random_xs();
}

sub
arc4random_addrandom($)
{
	my $buf = shift;

	lock($arcfour_lock);
	return &arc4random_addrandom_xs($buf);
}

sub
arc4random_pushb($)
{
	my $buf = shift;

	lock($arcfour_lock);
	return &arc4random_pushb_xs($buf);
}

sub
arc4random_pushk($)
{
	my $buf = shift;

	lock($arcfour_lock);
	return &arc4random_pushk_xs($buf);
}

sub
arc4random_bytes($;$)
{
	my ($len, $buf) = @_;
	my $val;
	my $vleft = 0;
	my $rv = '';
	my $idx = 0;

	if (defined($buf)) {
		$val = arc4random_pushb($buf);
		$vleft = 4;
	}
	while (($len - $idx) >= 4) {
		if ($vleft < 4) {
			$val = arc4random();
			$vleft = 4;
		}
		vec($rv, $idx / 4, 32) = $val;
		$idx += 4;
		$vleft = 0;
	}
	while ($idx < $len) {
		if ($vleft == 0) {
			$val = arc4random();
			$vleft = 4;
		}
		vec($rv, $idx, 8) = $val & 0xFF;
		$idx++;
		$val >>= 8;
		$vleft--;
	}
	return $rv;
}

# we are nice and re-seed perl's internal PRNG as well
srand(arc4random_pushb(pack("F*", rand(), rand(), rand(), rand())));

1;
__END__

=head1 NAME

BSD::arc4random - Perl interface to the arc4 random number generator

=head1 SYNOPSIS

  use BSD::arc4random qw(:all);
  $v = arc4random();
  if (!BSD::arc4random::have_kintf()) {
    $v = arc4random_addrandom("entropy to pass to the system");
  } else {
    $v = arc4random_pushb("entropy to pass to the system");
    $v = arc4random_pushk("entropy to pass to the kernel");
  }
  $s = arc4random_bytes(16);

=head1 DESCRIPTION

This set of functions maps the L<arc4random(3)> family of libc functions
into Perl code.
All functions listed below are ithreads-safe.
The internal XS functions are not, but you are not supposed
to call them, either.

On module load, perl's internal PRNG is re-seeded, as a bonus, using
B<srand> with an argument calculated from using B<arc4random_pushb>
on some entropy returned from B<rand>'s previous state.

=head2 LOW-LEVEL FUNCTIONS

=item B<arc4random>()

This function returns an unsigned 32-bit integer random value.

=item B<arc4random_addrandom>(I<pbuf>)

This function adds the entropy from I<pbuf> into the libc pool, then
returns an unsigned 32-bit integer random value from it.

=item B<arc4random_pushb>(I<pbuf>)

This function first pushes the I<pbuf> argument to the kernel if possible,
then the entropy returned by the kernel into the libc pool, then
returns an unsigned 32-bit integer random value from it.

=item B<arc4random_pushk>(I<pbuf>)

This function first pushes the I<pbuf> argument to the kernel if possible,
then returns an unsigned 32-bit integer random value from the kernel.

=item B<have_kintf>()

This constant function returns 1 if B<arc4random_pushb> and/or
B<arc4random_pushk> actually call the kernel interfaces, 0 if
they merely map to B<arc4random_addrandom> instead.

=head2 HIGH-LEVEL FUNCTIONS

=item B<arc4random_bytes>(I<num>[, I<pbuf>])

This function returns a string containing as many random bytes as
requested by the integral argument I<num>.
An optional I<pbuf> argument is passed to the system first.

=head1 AUTHOR

Thorsten Glaser E<lt>tg@mirbsd.deE<gt>

=head1 SEE ALSO

The L<arc4random(3)> manual page, available online at:
L<http://www.mirbsd.org/man/arc4random.3>

Perl's L<rand> and L<srand> functions via L<perlfunc> and L<perlfaq4>.

=head1 COPYRIGHT AND LICENSE

Copyright (c) 2008 Thorsten "mirabilos" Glaser

This module is covered by the MirOS Licence:
L<http://mirbsd.de/MirOS-Licence>

=cut
