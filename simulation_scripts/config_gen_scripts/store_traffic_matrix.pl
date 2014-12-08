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
		if ($data =~ /ID:\s+TCP\d+(S\S+)\s+SIZE\s+(\d+)/)
		{
			#print "here $1 $2\n";
			my $flowid = $1;
			#print " flow id $flowid \n ";
			if(exists $starts{$flowid}){
			$starts{$flowid} = $starts{$flowid} + $2;}
			else{
			$starts{$flowid} = $2;}
		}
	}
	


}

my $key= "";
my $source = "";
my $sink = "";

foreach $key (keys %starts)
{
	if($key =~ /S(\d+)S(\d+)/)
	{	
		$source = $1 -1;
		$sink = $2 - 1;	
		print $fh "$source $sink $starts{$key}\n";
		
	}

}



close (f);
close $fh;
