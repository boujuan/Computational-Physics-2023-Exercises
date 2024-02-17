set terminal png size 1280, 941 crop

set output "plot09_1.png"
plot "rw_N100_l0.50_mcT1000.000.histo" using 1:2 with line, "rw_N100_l0.50_mcT-2.000.histo" using 1:2 with line, "_rw_N100_l0.50_mcT-1.000.histo" using 1:2 with line, 

set output "plot09_2.png"
plot "timeseries.dat" using 1:2 with line

B(x) = gamma(100+1)/(gamma(x+1)*gamma(100-x+1))*2**(-100)
P(x) = B((x+100)/2)/2
G(x) = exp(-x*x/(2*100))/sqrt(2*pi*100)

set output "plot09_3.png"
set logscale y
plot [0:100] "rw_N100_l0.50_mcT1000.000.histo" u 1:($2*1*exp($1/(1000))) with line, "rw_N100_l0.50_mcT-2.000.histo" u 1:($2*100000*exp($1/(-2))) with line, "_rw_N100_l0.50_mcT-1.000.histo" u 1:($2*10**18.5*exp($1/(-1))) with line, P(x), G(x)