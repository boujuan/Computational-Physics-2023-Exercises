#!/usr/bin/fish

# Compile the C program
gcc -o exponential_ex exponential_ex.c -lm

# Run the program with different parameters and save the output
for N in 1 3 5 10 100
    ./exponential_ex 100000 1 $N > output_$N.txt
end

# Create a gnuplot script
echo "set terminal pngcairo size 1280,760" > plot.gp
echo "set output 'plots.png'" >> plot.gp
echo "set multiplot layout 5,1 title 'Exponential Distribution'" >> plot.gp

for N in 1 3 5 10 100
    echo "plot 'output_$N.txt' using 1:2 with lines title 'N=$N', \\" >> plot.gp
    echo "'output_$N.txt' using 1:3 with lines title 'Gumbell N=$N'" >> plot.gp
end

# Run gnuplot
gnuplot plot.gp

# Display using gnome
eog plots.png &