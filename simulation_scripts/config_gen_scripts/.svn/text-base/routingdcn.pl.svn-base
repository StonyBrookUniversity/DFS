

use strict;

require "inputfileparse.pl";
require "shortestpathutils.pl";
require "policyutils.pl";
use Data::Dumper;

if ($#ARGV < 1)
{
	die "usage: topologyfile outputfile \n";
}


## read the config with 4 inputs -- policy, topology, mbox, switch
my $topologyfile = $ARGV[0];
my $outputfile = $ARGV[1];

open (f,"<$topologyfile") or die "Cant read topology file\n";

## read the input file	
my ($TopologyNameRef,$TopologyIDRef,$NodeNametoIDRef, $NodeIDtoNameRef,$NumSwitches,$NumHostNodes) = read_topology($topologyfile);

my $NumNodes = $NumSwitches+$NumHostNodes;

## generate shortest paths
my $PathsRef  =  dijkstra_shortest_paths($NumNodes, $TopologyIDRef);
my $host_name = nodeidtoname(6);
my $i = 0;
my $start_index = $NumSwitches + 1;
open(my $fh, '>', $outputfile) or die "Could not open file '$outputfile' $!";

# First find the host-host routes that we want to printout
for ($i = $start_index; $i <= $NumNodes; $i++)
{
	my $j = $start_index;
	while (($j <= $NumNodes))
	{
		if ($j ne $i)
		{
			#print "$PathsRef->{$i}{$j} \n";
			my @array = split(/ /, $PathsRef->{$i}{$j});
			foreach (@array)
			{
				my $node_id = $_;
				# Convert nodeid to names
				my $node_name = nodeidtoname($node_id);
				# Printout host-host routes with node names
				print $fh "$node_name ";

			}
			print $fh  "\n";
			#print "@array \n";

			
		}
		$j++;
	}

}

# A routine to convert an id/number to Name for hosts and switches
sub nodeidtoname
{
	my $id = @_[0];
	if ($id > $NumSwitches) # Its a host
	{
		my $host_id = $id-$NumSwitches;
		my $name = "H".$host_id;
		return $name;
	}
	else # Its a switch
	{
		my $switch_id = $id;
		my $name = "S".$switch_id;
		return $name;
	
	}

}

close $fh;




