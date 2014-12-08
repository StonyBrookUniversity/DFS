#!/bin/sh
gnuplot << EOF
set terminal postscript eps enhanced color "Arial" 22
set output "$1"

set xrange [0.00001:12]
set yrange [0:1]

#set key at 150, 0.97 
#set nokey
set logscale x
#set xtics 0,20, 100
set ylabel "CDF"
set xlabel "Flow Completion Time (s)"
#set label 1 "Hotspot Traffic Model\n" at 120, 0.15

#set arrow from 8.502,0 to 8.502,1 nohead

plot 'duration.bin' using 1:2 w lp ps 0.1  lc 1 ti 'Random'#, 'short_16_0_cdf' using 1:2 w lp ps 0.1 lc 2 ti 'Fully Flexible'
