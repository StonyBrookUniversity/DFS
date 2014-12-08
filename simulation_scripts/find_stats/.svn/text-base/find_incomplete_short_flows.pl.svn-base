#! /usr/bin/perl

# Created by zafar

use strict;
use POSIX;

if ($#ARGV < 0)
{
        die "usage: out_flowy \n";
}


my $float = '\d+\.\d+|\d+';

my $routefile = $ARGV[0];
my $outputfile = "results.txt";
open (f,"<$routefile") or die "Cant read routefile\n";
open(my $fh, '>', $outputfile) or die "Could not open file '$outputfile' $!";

my $data = "";
my $i = 0;
my %data = ();
my @array1 = ();
my $array1_size = 0;
my $id = "";
my %starts = ();
my %ends = ();
my %flow_size = ();
while ($data = <f>)
{
	chomp($data);
	if ($data =~ /ST:\s+($float)/)
	{
		my $starttime = $1;
		if ($data =~ /ID:\s+(TCP\d+)S\S+\s+SIZE\s+(\d+)/)
		{
			#print "here $data\n";
			my $flowid = $1;
			#print " flow id $flowid \n ";
			$starts{$flowid} = $starttime;
			$flow_size{$flowid} = $2;
		}
	}
	
	if ($data =~ /CT:\s+($float)/)
	{
		my $endtime = $1;
		if ($data =~ /ID:\s+(TCP\d+)/)
		{
			my $flowid = $1;
			$ends{$flowid} = $endtime;
		}
	}


}

my $key= "";
foreach $key (keys %starts)
{
#	print "came here $key $starts{$key}\n";
	 if (not defined $ends{$key} )
	{
		print "Incomplete $key $flow_size{$key}\n";
	}

}



close (f);
close $fh;
