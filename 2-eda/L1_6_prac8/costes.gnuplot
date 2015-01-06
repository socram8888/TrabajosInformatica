set terminal gif

set output 'costes.gif'
plot 'voraz.dat' w l, 'bt.dat' w l

set output 'sol.gif'
plot 'voraz_sol.dat' w l, 'bt_sol.dat' w l
