CC = g++ -std=c++11
exe_file = zoo_tycoon
$(exe_file): Animal.o Zoo.o Tiger.o Sea_lion.o Bear.o util.o prog.o
	$(CC) Animal.o Zoo.o Tiger.o Sea_lion.o Bear.o util.o prog.o -o $(exe_file)
Animal.o: Animal.cpp
	$(CC) -c Animal.cpp
Zoo.o: Zoo.cpp
	$(CC) -c Zoo.cpp
Tiger.o: Tiger.cpp
	$(CC) -c Tiger.cpp
Sea_lion.o: Sea_lion.cpp
	$(CC) -c Sea_lion.cpp
Bear.o: Bear.cpp
	$(CC) -c Bear.cpp
util.o: util.cpp
	$(CC) -c util.cpp
prog.o: prog.cpp
	$(CC) -c prog.cpp

clean:
	rm -f *.o $(exe_file) 

