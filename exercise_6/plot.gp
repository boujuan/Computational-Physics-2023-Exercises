set terminal pngcairo size 1280,760
set output 'plots.png'
set multiplot layout 5,1 title 'Exponential Distribution'
plot 'output_1.txt' using 1:2 with lines title 'N=1', \
'output_1.txt' using 1:3 with lines title 'Gumbell N=1'
plot 'output_3.txt' using 1:2 with lines title 'N=3', \
'output_3.txt' using 1:3 with lines title 'Gumbell N=3'
plot 'output_5.txt' using 1:2 with lines title 'N=5', \
'output_5.txt' using 1:3 with lines title 'Gumbell N=5'
plot 'output_10.txt' using 1:2 with lines title 'N=10', \
'output_10.txt' using 1:3 with lines title 'Gumbell N=10'
plot 'output_100.txt' using 1:2 with lines title 'N=100', \
'output_100.txt' using 1:3 with lines title 'Gumbell N=100'
