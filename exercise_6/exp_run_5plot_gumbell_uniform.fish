#!/usr/bin/fish

# Compile the C program
gcc -o exponential_ex_uniform exponential_ex_uniform.c -lm

# Run the program with different parameters and save the output
for N in 1 3 5 10 100
    ./exponential_ex_uniform 100000 1 $N > output_uniform_$N.txt
end

# Create a gnuplot script
echo "set terminal pngcairo size 1280,760" > plot_uniform.gp
echo "set output 'plots_uniform.png'" >> plot_uniform.gp
echo "set multiplot layout 5,1 title 'Uniform Distribution'" >> plot_uniform.gp

for N in 1 3 5 10 100
    echo "plot 'output_uniform_$N.txt' using 1:2 with lines title 'N=$N', \\" >> plot_uniform.gp
    echo "'output_uniform_$N.txt' using 1:3 with lines title 'Gumbell N=$N'" >> plot_uniform.gp
end

# Run gnuplot
gnuplot plot_uniform.gp

# Display using gnome
eog plots_uniform.png &