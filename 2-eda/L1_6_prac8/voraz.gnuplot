set terminal gif
set output 'voraz.gif'
plot 'voraz_solo.dat' w l, x*(x-1)/2
