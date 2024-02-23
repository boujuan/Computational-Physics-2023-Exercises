#!/usr/bin/env fish
# Input arguments: num_runs, lambda

# Define variables
set title "Exponential generator histogram"
set output_file "exp.log"
set data_style "histogram"
set source_file "exponential.c"
set output_program "exp.out"
set X_label "Random number"
set Y_label "Frequency"
set plot_file "./output/exp_plot.png"

# Check if two arguments are provided
if test (count $argv) -eq 2
    # Compile the C program
    gcc -o $output_program $source_file -lm

    # Run the program and redirect output to a file
    ./$output_program $argv[1] $argv[2] > $output_file

    # Call gnuplot to plot the histogram
    echo "set terminal png size 800,600 enhanced font 'Verdana,10'; set output '$plot_file'; set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb'black' behind; set title '$title' textcolor rgb 'white'; set border linewidth 1.5 linecolor rgb 'white'; set key textcolor rgb 'white'; set tics textcolor rgb 'white'; set xlabel '$X_label' textcolor rgb 'white'; set ylabel '$Y_label' textcolor rgb 'white'; set grid linecolor rgb 'white'; set style data $data_style; plot '$output_file' using 1:2 with boxes lc rgb 'white'" | gnuplot
else
    echo "No arguments provided. Please provide the number of random numbers to generate and the seed."
end