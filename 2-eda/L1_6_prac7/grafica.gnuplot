set terminal gif
set output 'grafica.gif'
plot 'dijkstra.dat' w l, x*x w l, 2*x*x-x w l, x*(x-1)/2 w l
