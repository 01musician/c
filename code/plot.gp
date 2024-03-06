# Gnuplot script to plot data.txt
set terminal pngcairo
set output "plot.png"
set title "Sine Function"
set xlabel "X"
set ylabel "Y"
plot "data.txt" with lines title "sin(x)"

