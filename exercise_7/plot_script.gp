set terminal pngcairo size 1280,760
set output 'percol_plots.png'
set xrange [0:1]
set yrange [0:1]
set xlabel "p"
set ylabel "P(span)"
plot 'percol_12.log' using 1:2 with lines title 'L=12', \
     'percol_18.log' using 1:2 with lines title 'L=18', \
     'percol_24.log' using 1:2 with lines title 'L=24', \
     'percol_30.log' using 1:2 with lines title 'L=30', \
     'percol_36.log' using 1:2 with lines title 'L=36', \
     'percol_48.log' using 1:2 with lines title 'L=48'