/******************************************************
 * Program: methods.cpp
 * Author: Cameron McCawley
 * Date: 10/25/2019
 * Description: Definitions of methods that are used by both 
 *				students as well as teachers
 * Input:
 * Output:
 * ******************************************************/


#include "methods.h"
#include "Course.h"
#include "structs.h"
#include "University.h"
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

/********************************************************
 * Funciton: welcome_page
 * Parameters: none
 * Returns: int
 * Description: Dislays the welcome page, giving the user
 *				their initial option when running the
 *				program
 * *****************************************************/
int welcome_page(){
	int pick;
	cout << "Welcome!" << endl;
	while(true){
		cout << "Please choose an option:\n1 = login as student, 2 = login as teacher, 3 = end program" << endl;
		cin >> pick;
		if(cin.fail() || pick <= 0 || pick > 3){
			cin.clear();
			cin.ignore();
			cout << "ERROR! Please enter a valid option" << endl;
		}else{
			break;
		}
	}
	return pick;
}

/********************************************************
 * Funciton: prompt_to_quit
 * Parameters: none
 * Returns: bool
 * Description: prompts the user if the would like to quit
 * *****************************************************/
bool prompt_to_quit(){
	string option;
	cout << "Would you like to quit? [y] or [n]" << endl;
	while(true){
		cin >> option;
		cout << endl;
		if(option == "y" || option == "Y"){
			return true;
		}
		else if(option == "n" || option == "N"){
			return false;
		}
		else{
			cout << "Error! \"" << option << "\" is not a valid option. Please try again." << endl;
		}
	}
}

/********************************************************
 * Funciton: is_integer
 * Parameters: reference to a string
 * Returns: bool
 * Description: tests to see if a string is comprised of
 *				only integers
 * *****************************************************/
bool is_integer(string& id){
	if(id.empty()){
		return false;
	}
	char *ptr;
	strtol(id.c_str(), &ptr, 10);
	return(*ptr == 0);
}

/********************************************************
 * Funciton: copy
 * Parameters: reference to university object, reference
 *			   to course object
 * Returns: nothing
 * Description: copies the contents of the course object
 *				to the results array 
 * *****************************************************/
void copy(University& uni, Course& r){
	Course *c = uni.get_courses();
	for(int i = 0; i < uni.get_num_courses(); i++){
		if((c[i].get_name() == r.get_name()) && (c[i].get_course_time()->term == r.get_course_time()->term)){
			c[i] = r;
			return;
		}
	}
}

/********************************************************
 * Funciton: prompt_for_index
 * Parameters: reference to a university object
 * Returns: int
 * Description: prompts the user for the index of the course
 *				they wish to do things with
 * *****************************************************/
int prompt_for_index(University& uni){
	int index;
	string input;
	Course *c = uni.get_courses();
	cout << "CHOOSE COURSE" << endl;
	for(int i = 0; i < uni.get_num_courses(); i++){
		cout << "[" << i << "] " << c[i].get_name() << " " << c[i].get_course_time()->term << endl;
	}
	while(true){
		cout << "Please enter index of course, or press [q] to go back to options" << endl;
		cin >> input;
		if(input == "q"){
			return -1;
		}else if(is_integer(input)){
			index = stoi(input);
			break;
		}else{
			cout << "Error! Invalid input!" << endl;
		}
	}
	return index;
}

/********************************************************
 * Funciton: update_files
 * Parameters: reference to a university object
 * Returns: nothing
 * Description: Updates the courses.txt file to match the
 *				contents of the university class
 * *****************************************************/
void update_files(University& uni){
	ofstream c_stream("courses.txt", ios::trunc);
	Course *c = uni.get_courses();
	for(int i = 0; i < uni.get_num_courses(); i++){
		c_stream << c[i].get_name() << " " << c[i].get_teacher() << " " << c[i].get_course_time()->term << " ";
		c_stream << c[i].get_course_time()->days << " " << c[i].get_course_time()->start_time << " ";
		c_stream << c[i].get_course_time()->end_time << " " << c[i].get_course_time()->location << " ";
		c_stream << c[i].get_current_enrolled() << " ";
		string *r = c[i].get_roster();
		for(int j = 0; j < c[i].get_current_enrolled(); j++){
			c_stream << r[j] << " ";
		}
		c_stream << "\n";
	}
	c_stream.close();
}

/********************************************************
 * Funciton: view_entire_catalog
 * Parameters: reference to a university object
 * Returns: nothing
 * Description: prints out the entire course catalog
 * *****************************************************/
void view_entire_catalog(University& uni){
	Course *c = uni.get_courses();
	for(int i = 0; i < uni.get_num_courses(); i++){
		cout << "Name: " << c[i].get_name() << "\nTeacher: " << c[i].get_teacher() << endl;
		cout << "Term: " << c[i].get_course_time()->term << "\nDays: " << c[i].get_course_time()->days << endl;
		cout << "Start Time: " << c[i].get_course_time()->start_time << endl;
		cout << "End Time: " << c[i].get_course_time()->end_time << endl;
		cout << "Location: " << c[i].get_course_time()->location << "\n" << endl;
	}
}
