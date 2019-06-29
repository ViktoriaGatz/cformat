#!/usr/bin/gnuplot
set terminal png size 800,480 enhanced font 'Arial, 16'
set output 'LZ78.png'

set style line 1 linecolor rgb 'red' linetype 1 linewidth 2
set style line 1 linecolor rgb 'blue' linetype 1 linewidth 2

set border linewidth 1
set key top left
set grid
set mytics 1
set format y "%.0f"
set xlabel "size file.lz78" font "Arial, 16"
set format x "%.0f"
set ylabel "size file.txt" font "Arial, 16"
set xtics 500 font "Arial, 12"
set ytics 500 font "Arial, 12"
set rmargin 4
set tmargin 2
set mxtics
plot "LZ78.dat" using 1:2 title "LZ78" with linespoints ls 1,\
"num.dat" using 1:2 title "normal" with linespoints ls 2
