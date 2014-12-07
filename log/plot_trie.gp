#! /usr/bin/gnuplot

plot 'data/hybrid.dat' using 2:3
Y_MAX=GPVAL_Y_MAX
Y_MIN=GPVAL_Y_MIN
set yrange [Y_MIN-(Y_MAX-Y_MIN)*0.05:Y_MAX+(Y_MAX-Y_MIN)*0.05] reverse


X_MAX=GPVAL_X_MAX
X_MIN=GPVAL_X_MIN
set xrange [X_MIN-(X_MAX-X_MIN)*0.05:X_MAX+(X_MAX-X_MIN)*0.05] 

set terminal png medium size 1980,1020 enhanced font 'Verdana,10'
set output "images/hybrid.png"

set style line 1 lc rgb "red" lt 1 lw 2.5 pt 7 pi -1 ps 2.5
set pointintervalbox 4 

unset key; unset tics; unset border

plot 'data/hybrid.dat' using 2:3 with linespoints ls 1 notitle, \
	'data/hybrid.dat' using 2:3:1 with labels notitle tc rgb "white" offset 0


