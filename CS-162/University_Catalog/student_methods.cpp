/******************************************************
 * Program: student_methods.cpp
 * Author: Cameron McCawley
 * Date: 10/25/2019
 * Description: Methods that can be used when a student logs in.
 * Input:
 * Output:
 * ******************************************************/


#include "student_methods.h"
#include "University.h"
#include "Course.h"
#include "structs.h"
#include "methods.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

/********************************************************
 * Funciton: student_login
 * Parameters: none
 * Returns: string
 * Description: Prompts student for an ID, if ID cannot be 
 *				found in the database, then they have the
 *				option to register their name with their ID
 * *****************************************************/
string student_login(){
	string input;
	while(true){
		cout << "Please enter your student ID: " << endl;
		cin >> input;
		if(is_integer(input)){
			break;
		}else{
			cout << "ID must be an integer, please try again!" << endl;
		}
	}
	if(student_exists(input)){
		return input;
	}else{
		string choice;
		cout << "Couldn't find your ID in the current database." << endl;
		while(true){
			cout << "Would you like to register with this ID?\n[y] or [n]" << endl;
			cin >> choice;
			if(choice == "y"){
				add_new_student(input);					
				break;
			}else if(choice == "n"){
				return " ";
			}else{
				cout << "Sorry, did not recognize that as an option. Please try again." << endl;
			}
		}
	}
	return input;
	cout << "\nSuccess!" << endl;
}

/********************************************************
 * Funciton: student_options
 * Parameters: Reference to a University object, string
 * Returns: nothing
 * Description: Displays all of the options available to
 *				a logged in student. Acts like a hub for
 *				all the possible student options
 * *****************************************************/
void student_options(University& uni, string id){
	string option;
	while(true){
		cout << "Please choose an option:" << endl;
		cout << "[1] View entire catalog\n[2] Search catalog by term" << endl;
		cout << "[3] Search catalog by times\n[4] Enroll in course\n[5] Quit" << endl;
		cin >> option;	
		if(option == "1"){
			view_entire_catalog(uni);
		}else if(option == "2"){
			enroll(id, uni, 1);	
		}else if(option == "3"){
			enroll(id, uni, 3);
		}else if(option == "4"){
			enroll(id, uni, 3);
		}else if(option == "5"){
			return;
		}else{
			cout << "Error! \"" << option << "\" is not a valid option." << endl;
		}
	}
}

/********************************************************
 * Funciton: enroll_from_list
 * Parameters: none
 * Returns: bool
 * Description: Prompts the user for whether or not they
 *				would like to enroll of this last search
 *				result
 * *****************************************************/
bool enroll_from_list(){
	string input;
	while(true){
		cout << "Would you like to enroll from this list? [y] or [n]: " << endl;
		cin >> input;
		if(input == "y"){
			return true;
		}else if(input == "n"){
			return false;
		}else{
			cout << "Invalid input. Please try again!" << endl;
		}
	}
}

/********************************************************
 * Funciton: get_results
 * Parameters: Reference to a University object, int
 * Returns: Course*
 * Description: Creates an array of Course objects based
 *				on the parameter given in the search_type
 * *****************************************************/
Course * get_results(University& uni, int search_type){
	string input;
	if(search_type == 1){
		while(true){
			cout << "Please enter term. Use a single capital letter only! [F] [W] [S] [U] :" << endl;
			cin >> input;
			if(input != "F" && input != "W" && input != "S" && input != "U"){
				cout << "Error! Not a valid option. Please try again." << endl;
			}else{
				break;
			}
		}
		Course *r = uni.search_courses_by_term(input);
		return r;
	}else if(search_type == 2){
		Course *r = exclude_times(uni);
		return r;
	}else if(search_type == 3){
		Course *r = uni.get_courses();
		return r;
	}
	Course *r = uni.get_courses();
	return r;	
}

/********************************************************
 * Funciton: enroll
 * Parameters: string, reference to a University object, int
 * Returns: nothing
 * Description: Displayes the list of courses that match the
 *				search results and prompts them to enroll
 *				in them or continue to refine
 * *****************************************************/
void enroll(string id, University& uni, int search_type){
	bool ref = false;
	Course *r = get_results(uni, search_type);
	if(search_type == 3){
		uni.set_num_results(uni.get_num_courses());
	}
	while(true){
		for(int i = 0; i < uni.get_num_results(); i++){
			cout << "[" << i << "] " << r[i].get_name() << " " << r[i].get_course_time()->term << " ";
			cout << r[i].get_course_time()->start_time << " - " << r[i].get_course_time()->end_time << endl;
		}

		if(enroll_from_list()){
			string str_index;
			int index;
			while(true){
				cout << "Please enter index of course you wish to enroll in: " << endl;
				cin >> str_index;
				if(is_integer(str_index)){
					index = stoi(str_index);
					break;
				}else{
					cout << "Error! Invalid input." << endl;
				}
			}
			r[index].enroll_student(id);
			append_enrollment(id, r[index].get_name(), r[index].get_course_time()->term);
			copy(uni, r[index]);
			uni.set_num_results(uni.get_num_courses());
			return;
		}else{
			if(refine_search()){
				r = exclude_times(uni);
			}else{
				uni.set_num_results(uni.get_num_courses());
				return;
			}
		}
	}
}

/********************************************************
 * Funciton: refine_search
 * Parameters: none
 * Returns: bool
 * Description: prompts user if they would like to either
 *				continue to refine their search results
 *				or to quit back to the student options
 * *****************************************************/
bool refine_search(){
	string choice;
	while(true){
		cout << "[1] to refine search by time" << endl;
		cout << "[2] to quit" << endl;
		cin >> choice;
		if(choice == "1"){
			return true;
		}else if(choice == "2"){	
			return false;	
		}else{
			cout << "Error! Not a valid option. Please try again." << endl;
		}
	}
}

/********************************************************
 * Funciton: exclude_times 
 * Parameters: Reference to a University object
 * Returns: Course*
 * Description: Lets user enter in times to exclude from
 *				search results
 * *****************************************************/
Course * exclude_times(University& uni){
	int num_times = 0;
	string input;
	string num;
	while(true){
		cout << "How many entries would you like to add to the exclusion list?" << endl;
		cin >> num;
		if(is_integer(num)){
			num_times = stoi(num);
			break;
		}else{
			cout << "Error! Invalid input. Please try again. " << endl;
		}
	}
	cout << "Please enter times you wish to exclude. Seperate times with a space. " << endl;
	cin.ignore();
	getline(cin, input);
	string* times = new string[num_times];
	stringstream stream(input);
	for(int i = 0; i < num_times; i++){
		stream >> times[i];
	}
	Course *r = uni.search_courses_by_times(times, num_times);	
	delete[] times;	
	return r;
}

/********************************************************
 * Funciton: append_enrollment
 * Parameters: string, string, string
 * Returns: nothing
 * Description: adds the name and term of a course to the 
 *				end of the student's line in the enrollment.txt 
 *				file.
 * *****************************************************/
void append_enrollment(string id, string course, string term){
	string line;
	int j = 0;
	string name;
	string comp_id;
	int num_lines = 0;
	ifstream e("enrollment.txt");
	while(getline(e, line)){
		num_lines++;
	}
	e.clear();
	e.seekg(0, ios::beg);
	string *logs = new string[num_lines];
	while(getline(e, line)){
		logs[j] = line;
		j++;
	}
	e.close();
	for(int i = 0; i < num_lines; i++){
		stringstream stream(logs[i]);
		stream >> name >> comp_id;
		if(comp_id == id){
			logs[i].append(" ");
			logs[i].append(course);
			logs[i].append(" ");
			logs[i].append(term);
			break;
		}
	}
	ofstream new_enrollment("enrollment.txt", ios::trunc);
	for(int i = 0; i < num_lines; i++){
		new_enrollment << logs[i] << "\n";
	}
	new_enrollment.close();
	delete[] logs;
}

/********************************************************
 * Funciton: add_new_student
 * Parameters: string
 * Returns: nothing
 * Description: Adds a new student to the end of the 
 *				enrollment.txt file
 * *****************************************************/
void add_new_student(string id){
	string name;
	ofstream enrollment_stream("enrollment.txt", ios::app);
	cout << "Please enter your name. Use underscores for spaces: " << endl;
	cin >> name;
	enrollment_stream << name << " " << id;
	cout << "\nSuccess!" << endl;
	enrollment_stream.close();
}

/********************************************************
 * Funciton: student_exist
 * Parameters: string
 * Returns: bool
 * Description: tests to see if the student logging in
 *				already exists in the enrollment.txt file 
 * *****************************************************/
bool student_exists(string id){
	ifstream enrollment_stream("enrollment.txt");
	string line;
	string name;
	string comp_id;
	while(getline(enrollment_stream, line)){
		stringstream stream(line);
		stream >> name >> comp_id;
		if(comp_id == id){
			enrollment_stream.close();
			return true;
		}
	}
	enrollment_stream.close();
	return false;
}
