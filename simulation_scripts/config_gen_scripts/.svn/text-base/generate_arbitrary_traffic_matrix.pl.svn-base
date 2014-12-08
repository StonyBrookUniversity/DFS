#! /usr/bin/perl

# Created by zafar
use strict;
use POSIX;



if ($#ARGV < 0)
{
	die "usage: number of tors\n";
}

	
	my $tor = $ARGV[0];
	my $i = 0; # Switch index
	my $m = 1; # Host index
	my $j = 0;
	#print "I am in the subroutine create_tree with k $k \n";
	# create root node: S0
	# Do sth like breadth-first search
	my $filename = "hotspot".$tor;
	open(my $fh, '>', $filename) or die "Could not open file '$filename' $!";

	#my $j = $k+1;
	# Depth first search
	my $x = 1;
	for($i=0; $i < $tor; $i++)
	{
		for ($j=0;$j <$tor; $j++)
		{
			if($i != $j)
			{
				print $fh "$i $j 100\n";
			}
		}	
		
	
	}

	close $fh;

