#! /usr/bin/perl

# Created by zafar

use strict;
use POSIX;

if ($#ARGV < 1)
{
        die "usage: log_file output_file_mice output_file_elephant \n";
}


my $float = '\d+\.\d+|\d+';

my $routefile = $ARGV[0];
my $outputfile = $ARGV[1];
my $outputfile_e = $ARGV[2];

open (f,"<$routefile") or die "Cant read logfile\n";
open(my $fh, '>', $outputfile) or die "Could not open file '$outputfile' $!";
open(my $fhe, '>', $outputfile_e) or die "Could not open file '$outputfile_e' $!";


my $data = "";
my $i = 0;
my %data = ();
my @array1 = ();
my $array1_size = 0;
my $id = "";
my %starts = ();
my %ends = ();
my %complete_times = ();

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

		my $c_time = $1;
		if($data =~ /ID:\s+TCP(\d+S\S+)/)
		{
			my $flowid = $1;
			$ends{$flowid} = $starts{$flowid};
			$complete_times{$flowid} = $c_time;
			
		}
	}
}

my $key= "";
my $source = "";
my $sink = "";
my $totaltraffic = 0;
my $ctime = 0;
foreach $key (keys %ends)
{
	#if($key =~ /S(\d+)S(\d+)/)
	#{	
		$totaltraffic = $totaltraffic + $ends{$key};
		if($ends{$key} < 20000)
		{
			$ctime = $complete_times{$key}/1000;	
			print $fh "$ctime\n";
		}
		else
		{
			
			$ctime = $complete_times{$key}/1000;	
			print $fhe "$ctime\n";
		}
	#}

}

print " The Total Traffic is $totaltraffic \n";

close (f);
close $fh;
close $fhe;
