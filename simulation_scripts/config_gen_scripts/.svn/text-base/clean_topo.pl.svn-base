#! /usr/bin/perl

# Created by zafar

use strict;
use POSIX;

if ($#ARGV < 0)
{
        die "usage: inputfile outputfile \n";
}


my $float = '\d+\.\d+|\d+';

my $routefile = $ARGV[0];
my $outputfile = $ARGV[1];;
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

while ($data = <f>)
{
	chomp($data);
	@array1 = split(/ /, $data);
	if ($array1[0] =~ /S\d+/)
	{
		print $fh  "@array1 \n";
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
