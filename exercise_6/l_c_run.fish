#!/usr/bin/env fish

# Define variables
set title "Linear congruential generator histogram"
set output_file "l_c.log"
set data_style "histogram"
set source_file "linear_congruential.c"
set output_program "l_c.out"
set X_label "Random number"
set Y_label "Frequency"

# Check if two arguments are provided
if test (count $argv) -eq 2
    # Compile the C program
    gcc -o $output_program $source_file -lm

    # Run the program and redirect output to a file
    ./$output_program $argv[1] $argv[2] > $output_file

    # Call gnuplot to plot the histogram
    echo "set terminal wxt size 800,600 enhanced font 'Verdana,10' persist; set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb'black' behind; set title '$title' textcolor rgb 'white'; set border linewidth 1.5 linecolor rgb 'white'; set key textcolor rgb 'white'; set tics textcolor rgb 'white'; set xlabel '$X_label' textcolor rgb 'white'; set ylabel '$Y_label' textcolor rgb 'white'; set grid linecolor rgb 'white'; set style data $data_style; plot '$output_file' using 1:2 with boxes lc rgb 'white'" | gnuplot -persist
else
    echo "No arguments provided. Please provide the number of random numbers to generate and the seed."
end