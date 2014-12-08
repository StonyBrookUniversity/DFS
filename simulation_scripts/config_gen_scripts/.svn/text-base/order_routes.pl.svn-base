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
my @array = ();
my $array_size = 0;
my $id = "";
my %starts = ();
my %ends = ();
my $src = "";
my $dst = "";
# Contains the routes ordered
my @route_array = ();
$route_array[63][0] = 00;
my $route_string = "";
my $id1; my $id2;


while ($data = <f>)
{
	chomp($data);
	my $route_string = "";
	@array = split(/ /, $data);
        $array_size = @array;
	chomp($array[1]); chomp($array[$array_size-2]);
	$src = $array[1];
	$dst = $array[$array_size -2];	
	for ($i=0; $i < $array_size; $i++)
	{
		$route_string = $route_string.$array[$i]." ";

	}	
	#print "$array[0] $src $dst $array[$array_size -1]\n";
	#print "@array \n";
	#print "$route_string \n";

	if($src =~ /S(\d+)/){ $id1 = $1;}
	if($dst =~ /S(\d+)/){ $id2 = $1;}

	$route_array[$id1-1][$id2-1] = $route_string;
	#print "the ids are : $id1 $id2 $route_array[$id1+$id2 -2] \n";

	
	#my $src_dst = "S".$src."S".$dst;
	

}


# Print the route array 

for($i=0; $i < 64; $i++) {
	for(my $j=0; $j < 64; $j++) {
		if ($i!=$j)
		{
 			print "$route_array[$i][$j]\n";
		}
	}
 } 
#my $key= "";
#foreach $key (keys %starts)
#{
#	print "came here $key $starts{$key}\n";
#	 if (not defined $ends{$key} )
#	{
#		print "Incomplete $key\n";
#	}

#}



close (f);
close $fh;
