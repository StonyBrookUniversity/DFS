#!/usr/bin/perl
use warnings;
use strict;
use Statistics::Descriptive;

#
# Warning: untested code.
#


if ($#ARGV < 1)
{
        die "usage: log_file output_file\n";
}


my $outputfile = $ARGV[1];
my @data = `cat $ARGV[0] | awk '{print \$1}' `;


open(my $fh, '>', $outputfile) or die "Could not open file '$outputfile' $!";

my $stat = Statistics::Descriptive::Full->new();
$stat->add_data(@data);
$stat->sort_data();
(my $value_25, my $index_25 ) = $stat->percentile(25);
(my $value_75, my $indexi_75 ) = $stat->percentile(75);
my $min = $stat->min();
my $max = $stat->max();
my $median = $stat->median();
chomp($min,$value_25, $median,$value_75,$max);

print $fh "$min $value_25 $median $value_75 $max \n";

close $fh
