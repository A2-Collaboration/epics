#!/usr/bin/perl
use strict;
use warnings;
use Net::Telnet ();
use Time::HiRes qw(usleep);
use lib "$ENV{EPICS_BASE}/lib/perl";
use CA;

my $chan = CA->new("TAGG:MagneticField.A");
CA->pend_io(3);

my $t = new Net::Telnet (Timeout => 1, Port => 4000);

$t->open('10.32.165.31');
$t->binmode(1);
$t->telnetmode(0);
$t->timeout(0);
#$t->dump_log(1);
my $out = "READMAGFIELD\r";
foreach my $c (split(//,$out)) {
  $t->put($out);
  usleep(100e3);
}
my $val = $t->get(Errmode => 'return');
# the device not always responds...so just exit then
exit unless defined $val;
$val = substr($val,0,8); # extract field, other chars are not interesting

$chan->put($val);
CA->pend_io(3);

print "Magnetic field: $val mGauss\n";
