/******************************************************
 * Program: prog.cpp
 * Author: Cameron McCawley
 * Date: 10/25/2019
 * Description: Main program
 * Input:
 * Output:
 * ******************************************************/


#include "structs.h"
#include "Course.h"
#include "University.h"
#include "methods.h"
#include "teacher_methods.h"
#include "student_methods.h"
#include <fstream>
#include <iostream>
using namespace std;

/********************************************************
 * Funciton: main
 * Parameters: none
 * Returns: int
 * Description: Runs the main program 
 * *****************************************************/
int main(){
	int choice;
	string student_id;
	fstream course_stream("courses.txt");
	fstream teachers_stream("teachers.txt");
	fstream university_stream("university.txt");
	University uni(university_stream, course_stream, teachers_stream);
	cout << "Welcome to " << uni.get_address() << endl;		
	while(true){
		choice = welcome_page();
		switch(choice){
			case 1:
				student_id = student_login();
				if(student_id == " ") break;
				student_options(uni, student_id);	
				break;
			case 2: 
				if(log_teacher_in(uni)){
					teacher_options(uni);	
				}
				break;
			case 3:
				course_stream.close();
				teachers_stream.close();
				university_stream.close();
				update_files(uni);
				cout << "Goodbye!" << endl;
				
				return 0;
		}
	}
}
