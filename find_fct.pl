#! /usr/bin/perl

# Created by zafar

use strict;
use POSIX;

if ($#ARGV < 2)
{
        die "usage: source destination output\n";
}


my $float = '\d+\.\d+|\d+';

my $sourcefile = $ARGV[0];
my $dstfile = $ARGV[1];
my $outputfile = $ARGV[2];
open (f1,"<$sourcefile") or die "Cant read sourcefile\n";
open (f2,"<$dstfile") or die "Cant read destfile\n";
open(my $fh, '>', $outputfile) or die "Could not open file '$outputfile' $!";

my $data = "";
my %flow_ts = ();
my %flow_fs = ();
while ($data = <f1>)
{
	chomp($data);
	$data =~ (/\S+\s+\S+\s+\d+.\d+\s+(\d+.\d+)\s+\d+.\d+\s+(\d+.\d+\S+)\s+tcp/);
	print "$1, $2\n";
	$flow_fs{$2} = $1;

}

while ($data = <f2>)
{
	chomp($data);
	$data =~ (/\S+\s+\S+\s+(\d+.\d+)\s+\d+.\d+\s+\d+.\d+\s+(\d+.\d+\S+)\s+tcp/);
	print "$1, $2\n";
	$flow_ts{$2} =$1;
}

my $key= "";
my $flow_fct = 0;

foreach $key (keys %flow_fs)
{

	$flow_fct = $flow_ts{$key} - $flow_fs{$key};
	print $fh "$flow_fct \n";

}





close(f2);
close(f1);
close $fh;
