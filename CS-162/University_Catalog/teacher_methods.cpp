/******************************************************
 * Program: teacher_methods.cpp
 * Author: Cameron McCawley
 * Date: 10/25/2019
 * Description: Methods that can be used when a teacher logs in  
 * Input:
 * Output:
 * ******************************************************/


#include "teacher_methods.h"
#include "structs.h"
#include "methods.h"
#include "University.h"
#include "Course.h"
#include <string>
#include <iostream>

using namespace std;

/********************************************************
 * Funciton: log_teacher_int
 * Parameters: Reference to a University object
 * Returns: bool
 * Description: Prompts for id and password from teacher.
 *				returns true if ID and Pass match in the 
 *				teacher database
 * *****************************************************/
bool log_teacher_in(University& uni){
	string entered_id;
	string password;
	int id;
	teacher* t = uni.get_teachers();
	while(true){

		while(true){
			cout << "Please enter your ID:" << endl;
			cin >> entered_id;
			cout << endl;

			if(is_integer(entered_id)){
				id = stoi(entered_id);
				break;
			}else{
				cout << "Error! ID must only contain integer." << endl;
				if(prompt_to_quit()) return false;
			}
		}

		cout << "Please enter your password:" << endl;
		cin >> password;
		cout << endl;
		
		for(int i = 0; i < uni.get_num_teachers(); i++){
			if((id == t[i].id) && (password == t[i].password)){
				cout << "Logged in!" << endl;
				return true;
			}
		}
		cout << "Invalid ID or password!" << endl;
		if(prompt_to_quit()) return false;
	}
}

/********************************************************
 * Funciton: teacher_options
 * Parameters: Reference to University object
 * Returns: nothing
 * Description: Displays options available to a logged in teacher
 * *****************************************************/
void teacher_options(University& uni){
	string option;
	while(true){
		cout << "Please choose an option:" << endl;
		cout << "[0] View entire catalog\n[1] Change course information\n[2] Add course\n[3] Remove course" << endl;
		cout << "[4] View enrolled students\n[5] Remove enrolled student\n[6] Quit" << endl;
		cin >> option;
		if(option == "0"){
			view_entire_catalog(uni);
		}else if(option == "1"){
			change_course_information(uni);								
		}else if(option == "2"){
			add_course(uni);	
		}else if(option == "3"){
			remove_course(uni);	
		}else if(option == "4"){
			view_enrolled_students(uni);
		}else if(option == "5"){
			remove_student(uni);	
		}else if(option == "6"){
			return;
		}else{
			cout << "Error! \"" << option << "\" is not a valid option." << endl;
		}
	}
}

/********************************************************
 * Funciton: change_schedule_info
 * Parameters: Course*, int, string
 * Returns: nothing
 * Description: Allows teacher to choose what they want to
 *				change in a schedule, and then allows them to 
 *				change it.
 * *****************************************************/
void change_schedule_info(Course* c, int index, string input){
	schedule *s = new schedule;
	*s = *(c[index].get_course_time());
	if(input == "3"){ //term
		string t;
		cout << "Please enter terms. Do not use spaces: " << endl;
		cin >> t;
		s->term = t;
		cout << "\nSuccess!" << endl;
	}else if(input == "4"){ //time
		string st, et;
		cout << "Please enter new start time: " << endl;
		cin >> st;
		cout << "\nPlease enter new end time: " << endl;
		cin >> et;
		s->start_time = st;
		s->end_time = et;
		cout << "\nSuccess!" << endl;
	}else if(input == "5"){ //days
		string d;
		cout << "Please enter days. Do not use spaces: " << endl;
		cin >> d;
		s->days = d;
		cout << "\nSuccess!" << endl;
	}else if(input == "6"){ //location
		string l;
		cout << "Please enter new location. Do not use spaces: " << endl;
		cin >> l;
		s->location = l;
		cout << "\nSuccess!" << endl;
	}
	c[index].change_course_time(s);
	delete s;
}

/********************************************************
 * Funciton: change_course_information
 * Parameters: reference to university object
 * Returns: nothing
 * Description: Allows teacher to change information about
 *				a course after asking them what they want
 *				to change.
 * *****************************************************/
void change_course_information(University& uni){
	string input;
	int index = prompt_for_index(uni);
	Course *c = uni.get_courses();
	while(true){
		cout << "What would you like to change?" << endl;
		cout << "[1] Name\n[2] Teacher\n[3] Term\n[4] Time\n[5] Days\n[6] Location\n[7] Back to options" << endl;
		cin >> input;
		if(input == "1"){
			string n;
			cout << "Please enter new name: " << endl;
			cin >> n;
			c[index].set_name(n);
			cout << "\nSuccess!" << endl;
		}else if(input == "2"){
			string t;
			cout << "Please enter new name. Use underscores instead of spaces: " << endl;
			cin >> t;
			c[index].set_teacher(t);
			cout << "\nSuccess!" << endl;
		}else if(input == "3" || input == "4" || input == "5" || input == "6"){
			change_schedule_info(c, index, input);	
		}else if(input == "7"){
			return;
		}else{
			cout << "Error! \"" << input << "\" is not a valid option." << endl;
		}
	}
}

/********************************************************
 * Funciton: remove_student
 * Parameters: reference to university object
 * Returns: nothing
 * Description: Unenrolls a student from a course
 * *****************************************************/
void remove_student(University& uni){
	string input;
	int student_index;
	int course_index = prompt_for_index(uni);
	if(course_index == -1) return;
	Course *c = uni.get_courses();
	string *r = c[course_index].get_roster();
	cout << "CHOOSE STUDENT" << endl;
	for(int i = 0; i < c[course_index].get_current_enrolled(); i++){
		cout << "[" << i << "] " << r[i] << endl;
	}
	while(true){
		cout << "Please enter index of student you wish to unenroll, or press [q] to return to options: " << endl;
		cin >> input;
		if(input == "q" || input == "Q"){
			return;
		}else if(is_integer(input)){
			student_index = stoi(input);
			break;
		}else{
			cout << "Error! Invalid input!" << endl;
		}
	}
	c[course_index].unenroll_student(student_index);
}

/********************************************************
 * Funciton: add_course
 * Parameters: reference to university object
 * Returns: nothing
 * Description: Allows a teacher to add a new course 
 * *****************************************************/
void add_course(University& uni){
	string name, teacher;
	schedule *s = new schedule;
	cout << "USE UNDERSCORES FOR SPACES" << endl;
	cout << "Please enter name of course: " << endl;
	cin >> name;
	cout << "\nPlease enter name of teacher: " << endl;
	cin >> teacher;
	cout << "\nPlease enter the days of the week this class is held: " << endl;
	cin >> s->days;
	cout << "\nPlease enter start time: " << endl;
	cin >> s->start_time;
	cout << "\nPlease enter end time: " << endl;
	cin >> s->end_time;
	cout << "\nPlease enter term this course is held: " << endl;
	cin >> s->term;
	cout << "\nPlease enter location: " << endl;
	cin >> s->location;
	cout << endl;
	Course c(name, teacher, s);
	uni.add_to_catalog(c);
	delete s;
}

/********************************************************
 * Funciton: remove_course
 * Parameters: reference to university object 
 * Returns: nothing
 * Description: allows teacher to remove a course
 * *****************************************************/
void remove_course(University& uni){
	int index = prompt_for_index(uni);
	if(index == -1) return;	
	uni.remove_from_catalog(index);
}

/********************************************************
 * Funciton: view_enrolled_student
 * Parameters: reference to university object
 * Returns: nothing
 * Description: lets teacher view the IDs of the currently 
 *				enrolled students in a course
 * *****************************************************/
void view_enrolled_students(University& uni){
	int index = prompt_for_index(uni);
	if(index == -1) return;
	Course * c = uni.get_courses();
	cout << "\n" << c[index].get_name() << ": " << c[index].get_current_enrolled() << " students" << endl;
	string *r = c[index].get_roster();
	for(int i = 0; i < c[index].get_current_enrolled(); i++){
		cout << r[i] << endl;
	}
	cout << endl;
}

