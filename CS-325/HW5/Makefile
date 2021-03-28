CC = g++ -std=c++11
exe_file = mst
$(exe_file): Vertex.o Graph.o main.o
	$(CC) Vertex.o Graph.o main.o -o $(exe_file)
Vertex.o: Vertex.cpp
	$(CC) -c Vertex.cpp
Graph.o: Graph.cpp
	$(CC) -c Graph.cpp
main.o: main.cpp
	$(CC) -c main.cpp
	
clean:
	rm -f *.o $(exe_file) 
