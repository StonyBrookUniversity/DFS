#! /usr/bin/perl

# Created by zafar

use strict;
use POSIX;
require "topoutils.pl";

if ($#ARGV < 2)
{
	die "usage: topology_name(e.g., fatree) paramter#1(e.g., 2 for a 2-ary fatree) parameter#2(e.g., 200 for 200 switches, 0 if not required) \n";
}


## Create topology with atmost with 3 inputs -- topology, param#1, param#2
my $topologyname = $ARGV[0];
my $parameter1 = $ARGV[1];
my $parameter2 = $ARGV[2];


if($topologyname eq "tree")
{
	# Input is the degree of each switch
	print "The topology is $topologyname \n";
	# Call the function to create a simple k-ary tree
	&create_tree($parameter1);
}

if($topologyname eq "fullmesh")
{
	# Input are the number of racks
	print "The topology is $topologyname \n";
	# Call the function to create full mesh tree with n switches
	&create_fullmesh($parameter2);
}

if($topologyname eq "jellyfish")
{
	# Inputs the number of ports per switch and number of racks
 	print " In jellyfish loop \n";
	print "The topology is $topologyname \n";
	# Call the function to create full mesh tree with n switches
	&create_jellyfish($parameter1, $parameter2);
}

if($topologyname eq "fattree")
{
        # Inputs the number of ports per switch and number of racks
	print " In fattree loop \n";
        print "The topology is $topologyname \n";
        #Call the function to create full mesh tree with n switches
        &create_fattree($parameter1);
} 
