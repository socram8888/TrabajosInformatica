
# ALL
all: voraz backtracking costes

graficas: voraz_grafica costes_grafica

# COMUN
grafo.o: grafo.cpp grafo.h
	g++ -Wall -c grafo.cpp

voraz_algo.o: grafo.o voraz_algo.h voraz_algo.cpp
	g++ -Wall -c voraz_algo.cpp

backtracking_algo.o: grafo.o backtracking_algo.h backtracking_algo.cpp
	g++ -Wall -c backtracking_algo.cpp

# VORAZ
voraz.o: voraz_algo.o voraz.cpp
	g++ -Wall -c voraz.cpp

voraz: voraz.o
	g++ -Wall grafo.o voraz_algo.o voraz.o -o voraz

# BACKTRACKING
backtracking.o: backtracking_algo.o backtracking.cpp
	g++ -Wall -c backtracking.cpp

backtracking: backtracking.o
	g++ -Wall grafo.o backtracking_algo.o backtracking.o -o backtracking
	
# GRAFICA VORAZ
voraz_exec: voraz
	./voraz

voraz_grafica: voraz_exec voraz.gnuplot
	gnuplot voraz.gnuplot

# COSTES
costes.o: voraz_algo.o backtracking_algo.o costes.cpp
	g++ -Wall -c costes.cpp

costes: costes.o
	g++ -Wall grafo.o voraz_algo.o backtracking_algo.o costes.o -o costes

# GRAFICA COSTES
costes_exec: costes
	./costes

costes_grafica: costes_exec costes.gnuplot
	gnuplot costes.gnuplot

# CLEAN
clean:
	$(RM) *.o
	$(RM) voraz voraz.exe
	$(RM) backtracking backtracking.exe
	$(RM) costes costes.exe
	$(RM) voraz_solo.dat voraz.gif
	$(RM) voraz.dat voraz_sol.dat bt.dat bt_sol.dat sol.gif costes.gif
