#!/usr/bin/perl
open(IN, "<$ARGV[0]") || die("Cant open\n");

$min = 0;
#$max = 100;
#$max = 4150;
#$max = $ARGV[1];
$max = 4150;
$bins = 300.0;

$total = 0;

while(<IN>) {
	chomp;
	($diff_1,$diff_2,$diff_3,$diff_4,$diff_5,$diff_6) = split;

	$bin = int(($diff_1-$min)/($max-$min)*$bins);
	if($bin<0) {next }
	$numbers_1[$bin]++;
	$total_1++;
	
	$bin = int(($diff_2-$min)/($max-$min)*$bins);
	if($bin<0) {next }
	$numbers_2[$bin]++;
	$total_2++;

	$bin = int(($diff_3-$min)/($max-$min)*$bins);
	if($bin<0) {next }
	$numbers_3[$bin]++;
	$total_3++;

	$bin = int(($diff_4-$min)/($max-$min)*$bins);
	if($bin<0) {next }
	$numbers_4[$bin]++;
	$total_4++;

	$bin = int(($diff_5-$min)/($max-$min)*$bins);
	if($bin<0) {next }
	$numbers_5[$bin]++;
	$total_5++;

	$bin = int(($diff_6-$min)/($max-$min)*$bins);
	if($bin<0) {next }
	$numbers_6[$bin]++;
	$total_6++;

}

$cdf_1 = $cdf_2 = $cdf_3 = $cdf_4 = $cdf_5 = $cdf_6 = 0;
for($i=0;$i<$bins;$i++) {
	#$cdf_1 = $numbers_1[$i]/$total_1;
	$cdf_1 += $numbers_1[$i]/$total_1;
	$cdf_2 += $numbers_2[$i]/$total_2;
	$cdf_3 += $numbers_3[$i]/$total_3;
	$cdf_4 += $numbers_4[$i]/$total_4;
	$cdf_5 += $numbers_5[$i]/$total_5;
	$cdf_6 += $numbers_6[$i]/$total_6;
	printf "%f %f %f %f %f %f %f\n", $min + ($i)/$bins*($max-$min), $cdf_1 , $cdf_2 , $cdf_3, $cdf_4, $cdf_5, $cdf_6;
}
