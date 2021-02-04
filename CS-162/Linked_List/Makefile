CC = g++ -std=c++11
exe_file = app
$(exe_file): util.o prog.o
	$(CC) util.o prog.o -o $(exe_file)
util.o: util.cpp
	$(CC) -c util.cpp
prog.o: prog.cpp
	$(CC) -c prog.cpp

clean:
	rm -f *.o $(exe_file) 

