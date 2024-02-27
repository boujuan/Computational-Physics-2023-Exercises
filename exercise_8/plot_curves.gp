# Set the terminal to png
set terminal pngcairo size 1280,760

# Set the output file name
set output 'density_curves.png'

# Set the labels for the axes
set xlabel 'p'
set ylabel 'rho(x)'

# set xrange []

# Set the title for the plot
set title 'Density Curves'

# Plot the data from the files
plot 'chain_heap_1.log' using 1:2 title 'm[1,2.4]' with lines, \
     'chain_heap_2.log' using 1:2 title 'm[1,100]' with lines, \
     'chain_heap_3.log' using 1:2 title 'm[1,1.1]' with lines, \
     'chain_heap_4.log' using 1:2 title 'm=1' with lines, \
     'chain_heap_5.log' using 1:2 title 'm=rand[1,10]' with lines