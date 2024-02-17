set terminal png size 1280, 941 crop

set output "plot07.png"
f(x) = a*x**b
fit f(x) "percol.dat" using 3:2 via a,b
set logscale xy
plot "percol.dat" using 3:2, f(x)
