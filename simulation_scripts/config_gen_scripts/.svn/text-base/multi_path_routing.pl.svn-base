#!usr/bin/perl
# Script to create multiple-path routes between source and destination pairs
# The input is a topology file
require "shortestpathutils.pl";
require "inputfileparse.pl";


if ($#ARGV < 1)
{
	die "usage: topologyfile outputfile \n";
}

my $topologyfile = $ARGV[0];
my $outputfile = $ARGV[1];

open (f,"<$topologyfile") or die "Cant read topology file\n";
open(my $fh, '>', $outputfile) or die "Could not open file '$outputfile' $!";

# Read the topology file
my ($TopologyNameRef,$TopologyIDRef,$NodeNametoIDRef, $NodeIDtoNameRef,$NumSwitches,$NumHostNodes) = read_topology($topologyfile);
my $NumNodes = $NumSwitches+$NumHostNodes;
my $PathsRef  =  compute_multiple_shortest_paths($NumNodes, $TopologyIDRef);


# Now lets start writing the routes

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
			my $k = 0;
			while (defined $PathsRef->{$i}{$j}->{$k})
			{
			#print "$PathsRef->{$i}{$j} \n";
			my @array = split(/ /, $PathsRef->{$i}{$j}->{$k});
			my $iterator = 1;
			my $array_size = @array;

			foreach (@array)
			{
				my $node_id = $_;
				# Convert nodeid to names
				my $node_name = nodeidtoname($node_id);
				# Printout host-host routes with node names
				if($iterator < ($array_size))
				{
				print $fh "$node_name ";
				}
				else
				{
				print $fh "$node_name";
				}
		
				$iterator++;

			}
			if(($k+1) < ($PathsRef->{$i}{$j}->{"PATHS"}))
			{
			print $fh  ",";
			}
			#print "@array \n";
			$k++;
			}
			print $fh  "\n";

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



