#!/usr/bin/gnuplot
reset
set terminal png
set output "images/timeAdd.png"
set boxwidth 0.75 absolute
set xtic auto # set xtics automatically
set ytic auto # set ytics automatically
set xlabel "NB words"
set ylabel "Time"
set label "Yield Point" at 0.003,260
set arrow from 0.0028,250 to 0.003,280
set grid
set xr [0:23086]
set yr [0.00:13.00]
plot "data/timeAdd.dat" using 1:2 title 'Briandais Tree' with linespoints, \
     "data/timeAdd.dat" using 1:3 title 'Hybrid Trie' with linespoints
     
