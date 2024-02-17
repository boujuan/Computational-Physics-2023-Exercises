set terminal png size 1280, 941 crop

set output "plot06_1.png"
plot "mu_5_runs_0" using 1:2 with line, "mu_5_runs_100" using 1:2, "mu_5_runs_10000" using 1:2, "mu_5_runs_1000000" using 1:2

set output "plot06_2.png"
plot "mu_10_runs_0" using 1:2 with line, "mu_10_runs_1000000" using 1:2, "mu_50_runs_0" using 1:2 with line, "mu_50_runs_1000000" using 1:2, "mu_100_runs_0" using 1:2 with line, "mu_100_runs_1000000" using 1:2
