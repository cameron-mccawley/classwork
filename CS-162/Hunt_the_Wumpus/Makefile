CC = g++ -std=c++11 -g
exe_file = app
$(exe_file): Event.o Pit.o Bats.o Gold.o Wumpus.o Room.o Game.o util.o prog.o
	$(CC) Event.o Pit.o Bats.o Gold.o Wumpus.o Room.o Game.o util.o prog.o -o $(exe_file)
Event.o: Event.cpp
	$(CC) -c Event.cpp
Pit.o: Pit.cpp
	$(CC) -c Pit.cpp
Bats.o: Bats.cpp
	$(CC) -c Bats.cpp
Gold.o: Gold.cpp
	$(CC) -c Gold.cpp
Wumpus.o: Wumpus.cpp
	$(CC) -c Wumpus.cpp
Room.o: Room.cpp
	$(CC) -c Room.cpp
Game.o: Game.cpp
	$(CC) -c Game.cpp
util.o: util.cpp
	$(CC) -c util.cpp
prog.o: prog.cpp
	$(CC) -c prog.cpp

clean:
	rm -f *.o $(exe_file) 

