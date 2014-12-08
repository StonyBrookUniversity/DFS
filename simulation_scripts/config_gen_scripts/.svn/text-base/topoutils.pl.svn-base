#! /usr/bin/perl

# Created by zafar
use strict;
use POSIX;

sub create_tree
{

	my $k = @_[0];
	my $i = 0; # Switch index
	my $m = 1; # Host index
	my $j = 0;
	#print "I am in the subroutine create_tree with k $k \n";
	# create root node: S0
	# Do sth like breadth-first search
	my $filename = "tree".$k;
	open(my $fh, '>', $filename) or die "Could not open file '$filename' $!";
	my $NumSwitches = 1 + $k + $k*$k;
	my $NumHosts = $k*$k;
	print $fh "NUMSWITCHES=$NumSwitches \n";
	print $fh "NUMHOSTNODES=$NumHosts \n";

	#my $j = $k+1;
	# Depth first search
	my $x = 1;
	for($i=2; $i <= $k+1; $i++)
	{
		print $fh "S1 S$i 1 \n";
		# This inner loop should go from k->2k, 2k->3k, 3k->4k
		# Lets look at this prob;em
		for ($j=($x*$k)+2; $j <=(($x+1)*$k)+1; $j++)
		{
			print $fh "S$i S$j 1 \n";
			print $fh "S$j H$m 1 \n";
			$m++;
		

		}
		$x++;	
	
	}

	close $fh;

}
sub create_fullmesh
{

	my $k = @_[0];
	print "$k \n";
	my $i = 0; # Switch index
	my $j = 0;
	print "I am in the subroutine create_fullmesh with $k switches \n";
	
	my $filename = "fullmesh".$k;
	open(my $fh, '>', $filename) or die "Could not open file '$filename' $!";
	
	my $NumSwitches = $k;
	my $NumHosts = $k;
	print $fh "NUMSWITCHES=$NumSwitches \n";
	print $fh "NUMHOSTNODES=$NumHosts \n";



	for($i=1; $i <= $k; $i++)
	{

		for($j=$i+1; $j <= $k; $j++)
		{
			print $fh "S$i S$j 1\n";
		}
	

		
	}

	for($i=1; $i <= $k; $i++)
	{
			print $fh "S$i H$i 1 \n";	
	
	}

	close $fh;

}

sub create_jellyfish
{

	my $k = @_[0];
	my $N = @_[1];
	my $i  = 0; my $j = 0;
	print "$k and $N \n";
	my @switch_available = [];
	# Keep track of the degree of the table, initialize to 0 for each of the N switch
	my @degree_table = [];	

	for ($i=0; $i < $N; $i++) {$degree_table[$i]=0;}

	# Table consisting of all switch states
	my %switch_table = ();

	# Creates N-arrays for each of the switches
	for ($i=0; $i < $N; $i++) {@{$switch_table{$i}} = ();}

	# Fillup all the arrays

	for ($j=0; $j < $N; $j++){ for ($i=0; $i < $N; $i++) {$switch_table{$j}[$i] = $i;}}
	print " $switch_table{7}[7] \n"; 

	# push (@planets, 'jupiter');
	# Table of switches that have non-zero ports still left
	for ($i=0; $i < $N; $i++) { $switch_available[$i] = $i;}

	my $filename = "jellyfish".$k.$N;
	open(my $fh, '>', $filename) or die "Could not open file '$filename' $!";
	
	
	# A While loop that keeps adding links until
	# No two switches with free port
	while ($#switch_available != 0)
	{

		# Randomly pick a number from the $switch_available array
		my $range = $#switch_available;
		my $random_index = int(rand($range)) + 1;	
		my $random_number1 = $switch_available[$random_index];


		# Pick the second random switch 
		$range = $#{$switch_table{$random_number1}};
		$random_index = int(rand($range)) + 1;
		my $random_number2 = $switch_table{$random_number1}[$random_index];
		print "$random_number1 $random_number2   \n";
		

		# Remove the elements from the respective arrays
		@{$switch_table{$random_number1}} = grep { $_ != $random_number2 } @{$switch_table{$random_number1}};
		@{$switch_table{$random_number2}} = grep { $_ != $random_number1 } @{$switch_table{$random_number2}};


		# Increase the degree of these two switches 
		$degree_table[$random_number1]++;
		$degree_table[$random_number2]++;
		
		# If degree = k, remove the switch from the list of available switches
		if($degree_table[$random_number1] == $k){@degree_table = grep { $_ != $random_number1 } @degree_table;}
		if($degree_table[$random_number2] == $k){@degree_table = grep { $_ != $random_number2 } @degree_table;}


		# The last condition if there is a switch with two empty ports or if there is a switch with one empty port
		if ($#switch_available==1)
		{
			# If the degree of the switch is 1, delete the switch


			# Else if it has two free ports, break a link and reconnect

		}
		

	
		$random_number1++; 
		$random_number2++; 
	
		print $fh "S$random_number1 S$random_number2 1 \n";

	}
	
	
	

	close $fh;

	# The algorithm now goes in here
	# Generate two random number bw 1 and N, these are pair of random switches that we connect
	# We need to keep track of the degree left for each switch and the list of switches its connected to.
	#my $random_number1 = int(rand($range)) + $minimum;		


}

sub create_fattree 
{

	my $k = @_[0];
        my $i = 0; # Switch index
        my $m = 1; # Host index
        my $j = 0;
	my $z = 0;
	
	my $filename = "fattree".$k;
        open(my $fh, '>', $filename) or die "Could not open file '$filename' $!";
        my $NumSwitches = ($k/2)**2 + ($k/2)*$k + ($k/2)*$k;
        my $NumHosts = ($k/2)*$k;
        print $fh "NUMSWITCHES=$NumSwitches \n";
        print $fh "NUMHOSTNODES=$NumHosts \n";

	# Create the edge switches, the aggregation switches and the core switches	
	my @edge_switches = ();
	my @agg_switches = ();
	my @core_switches = ();

	for ($i=0; $i < ($k/2)*$k; $i++)
	{
		$j = $i + 1;
		$edge_switches[$i] = "S".$j;
		print "The edge switch is $edge_switches[$i] \n";

	}


	for ($i=($k/2)*$k; $i < ($k/2)*2*$k; $i++)
	{
		$j = $i + 1;
		$agg_switches[$z] = "S".$j;
		print "The aggregation switch is $agg_switches[$z] \n";
		$z++;

	}

	$z = 0;
	for ($i=($k/2)*2*$k; $i <  $NumSwitches; $i++)
	{
		$j = $i + 1;
		$core_switches[$z] = "S".$j;
		print "The core switch is $core_switches[$z] \n";
		$z++;

	}


	# Now lets do the interconnections
	# First we connect the edge switches with the aggregation switches in the same pod
	my $pod = 1;
	my $y  = 0;
	while ($pod <= $k)
	{	
		# Each for loop iteration goes through the a single pod and makes the interconnections
		for ($i = (($pod-1)*($k/2)); $i < $pod*($k/2); $i++)
		{	
	
		# Take the first edge switch, the connect it to $k/2 of the first aggregation switches
		# Repeat this for the first k/2 edge switches	
			$y = $i + 1;
			print $fh "$edge_switches[$i] H$y 1\n";  

				
			for ($j = (($pod-1)*($k/2)); $j < $pod*($k/2); $j++)
			{
				print $fh "$edge_switches[$i] $agg_switches[$j] 1\n";  
			}
		}	
		$pod++;
	}
	# Then we make the interconnections between the aggregation switches and the core swicthes	
	# The idea is the following, pick a aggregation switch connected it to the first k/2 core switches, 
	# next switch connect to next k/2 core switch, and this we do for each pod
	# For each pod

	$pod = 1;
 	my $z ;	
	while ($pod <= $k)
	{
		$z = 0;
		for ($i = (($pod-1)*($k/2)); $i < $pod*($k/2); $i++)
		{
			for ($j = $z*($k/2); $j < ($z+1)*($k/2); $j++)
			{
				print $fh "$agg_switches[$i] $core_switches[$j] 1\n";  
			}
			$z++;

		}		
		$pod++;	
		

	}

        close $fh;


}

1;
