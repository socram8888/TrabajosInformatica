
# ALL
all: test_dijkstra bomberos costes

# COMUNES
grafo.o: grafo.cpp grafo.h
	g++ -Wall -c grafo.cpp

dijkstra.o: grafo.o dijkstra.cpp dijkstra.h
	g++ -Wall -c dijkstra.cpp

# TEST DIJKSTRA
test_dijkstra.o: dijkstra.o test_dijkstra.cpp
	g++ -Wall -c test_dijkstra.cpp

test_dijkstra: test_dijkstra.o
	g++ -Wall grafo.o dijkstra.o test_dijkstra.o -o test_dijkstra

# BOMBEROS
bomberos.o: dijkstra.o bomberos.cpp
	g++ -Wall -c bomberos.cpp

bomberos: bomberos.o
	g++ -Wall grafo.o dijkstra.o bomberos.o -o bomberos

# COSTES
costes.o: dijkstra.o costes.cpp
	g++ -Wall -c costes.cpp

costes: costes.o
	g++ -Wall grafo.o dijkstra.o costes.o -o costes

# GRAFICA
costes_exec: costes
	./costes

costes_grafica: costes_exec grafica.gnuplot
	gnuplot grafica.gnuplot

# CLEAN
clean:
	$(RM) *.o
	$(RM) test_dijkstra test_dijkstra.exe
	$(RM) bomberos bomberos.exe
	$(RM) costes costes.exe
	$(RM) dijkstra.dat grafico.gif
