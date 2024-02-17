set terminal png size 1280, 941 crop

p1(x)=0.5**x*exp(-0.5)/gamma(x+1)
p2(x)=2**x*exp(-2)/gamma(x+1)

set output "plot10_1.png"
plot "graphs.dat" using 1:2, p1(x), "graphs1.dat" using 1:2, p2(x)

set output "plot10_2.png"
plot "graph_100.dat" using 1:2 with line, "graph_200.dat" using 1:2 with line, "graph_500.dat" using 1:2 with line, "graph_1000.dat" using 1:2 with line, 
