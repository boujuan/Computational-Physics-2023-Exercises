# Set the terminal to png
set terminal pngcairo size 1280,760

# Set the output file name
set output 'pt_plot.png'

# Set the labels for the axes
set xlabel 'sweep number'
set ylabel 'p'

# set xrange []

# Set the title for the plot
set title 'Ferromagnetic simulation with random initial spin configuration'

# dPTL20p0.00ID1000.out
set grid

file = 'dPTL20p0.00ID1000.out'

# Plot the data from the files
plot file using 1:3 with lines title 'T1', \
    file using 1:6 with lines title 'T2', \
    file using 1:9 with lines title 'T3'