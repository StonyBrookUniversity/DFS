#! /usr/bin/perl

# Created by zafar

use strict;
use POSIX;

if ($#ARGV < 1)
{
        die "usage: log_file output_file \n";
}


my $float = '\d+\.\d+|\d+';

my $routefile = $ARGV[0];
my $outputfile = $ARGV[1];
open (f,"<$routefile") or die "Cant read logfile\n";
open(my $fh, '>', $outputfile) or die "Could not open file '$outputfile' $!";

my $data = "";
my $i = 0;
my %data = ();
my @array1 = ();
my $array1_size = 0;
my $id = "";
my %starts = ();
my %ends = ();

while ($data = <f>)
{
	chomp($data);
	if ($data =~ /ST:\s+($float)/)
	{
		#my $starttime = $1;
		if ($data =~ /ID:\s+TCP(\d+S\S+)\s+SIZE\s+(\d+)/)
		{
			#print "here $1 $2\n";
			my $flowid = $1;
			#print " flow id $flowid \n ";
			#if(exists $starts{$flowid}){
			$starts{$flowid} = $2;
			#else{
			#$starts{$flowid} = $2;}
		}
	}

	if ($data =~ /CT:\s+($float)/)
	{
		if($data =~ /CT:\s+($float)\s+ID:\s+TCP(\d+S\S+)/)
		{
			my $flowid = $2;
			#print "$2 and $1 \n";
			#print "$starts{$flowid} $1 \n";
			$ends{$flowid} = $1/($starts{$flowid});
			print "$ends{$flowid} $starts{$flowid} $1 \n";
		}
	}
}

my $key= "";
my $source = "";
my $sink = "";
my $totaltraffic = 0;

foreach $key (keys %ends)
{
	#if($key =~ /S(\d+)S(\d+)/)
	#{	
		$totaltraffic = $totaltraffic + $ends{$key};	
		print $fh "$key $ends{$key}\n";
		
	#}

}

print " The Total Traffic is $totaltraffic \n";

close (f);
close $fh;
