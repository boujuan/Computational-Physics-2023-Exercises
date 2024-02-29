#!/usr/bin/fish

rm *.log

cc -o percol percolation1.c percol.c stacks.c -Wall -g

for L in 12 18 24 30 36 48
  for p in 0.1 0.2 0.3 0.4 0.45 0.5 0.52 0.54 0.56 0.57 0.58 0.59 0.60 0.61 0.62 0.64 0.66 0.68 0.7 0.8 0.9 1.0
    ./percol $L $p 1000 >> "percol_$L.log"
  end
end

gnuplot plot_script.gp

gnuplot plot_script_2.gp

eog percol_plots.png &
eog percol_plot_2.png &