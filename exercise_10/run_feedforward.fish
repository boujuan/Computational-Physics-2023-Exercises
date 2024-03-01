#!/usr/bin/fish

function run_program
    # Check the first argument
    switch $argv[1]
        case 'm'
            # cc feed_forward_fragment.c -o feed_forward -lm -Wall
            set program './feed_forward'
            set output_dir './majority'
        case 'p'
            # cc feed_forward_framgent.c -o feed_forward_parity -lm -Wall
            set program './feed_forward_parity'
            set output_dir './parity'
        case '*'
            echo "'m' or 'p' as 1st arg"
            return 1
    end

    set output_filename (string join "" $program "_")

    # Remove the first argument
    set argv (string split " " $argv | tail -n +2)

    for arg in $argv
        set output_filename $output_filename"_"$arg
    end
    mkdir -p $output_dir
    $program $argv > $output_dir/$output_filename.out
    # Plot the output using gnuplot
    echo "set terminal png; set xlabel 't'; set ylabel 'e(t)'; set output '$output_dir/$output_filename.png'; plot '$output_dir/$output_filename.out'" | gnuplot
    eog $output_dir/$output_filename.png &
end

run_program $argv