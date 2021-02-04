CC = g++ -std=c++11 -g
exe_file = course_catalog
$(exe_file): Course.o University.o methods.o teacher_methods.o student_methods.o prog.o
	$(CC) Course.o University.o methods.o teacher_methods.o student_methods.o prog.o -o $(exe_file)
Course.o: Course.cpp
	$(CC) -c Course.cpp
University.o: University.cpp
	$(CC) -c University.cpp
methods.o: methods.cpp
	$(CC) -c methods.cpp
teacher_methods.o: teacher_methods.cpp
	$(CC) -c teacher_methods.cpp
student_methods.o: student_methods.cpp
	$(CC) -c student_methods.cpp
prog.o: prog.cpp
	$(CC) -c prog.cpp

clean:
	rm -f *.o $(exe_file) 

