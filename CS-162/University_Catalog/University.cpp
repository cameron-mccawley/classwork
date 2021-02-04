/******************************************************
 * Program: University.cpp 
 * Author: Cameron McCawley
 * Date: 10/25/2019
 * Description: Definitions for University class 
 * Input:
 * Output:
 * ******************************************************/


#include "structs.h"
#include <iostream>
#include "University.h"
#include <string>
#include <fstream>
#include "Course.h"
using namespace std;

//This is the default constructor
University::University(){
	name = "";
	address = "";
	current_term = "";
	num_courses = 0;
	num_teachers = 0;
	num_results = 0;
	results = nullptr;
	courses = nullptr;
	teachers = nullptr;
}

//this is a constructor that takes in three references to fstreams
//This also initilizes all of the courses
University::University(fstream &university_stream, fstream &course_stream, fstream &teacher_stream){
	string course_line;
	int j = 0;
	results = nullptr;
	num_results = 0;
	getline(university_stream, name);
	getline(university_stream, address);
	getline(university_stream, current_term);
	num_courses = calculate_num_courses(course_stream);
	num_teachers = calculate_num_teachers(teacher_stream);
	courses = new Course[num_courses];
	teachers = new teacher[num_teachers];
	for(int i = 0; i < num_teachers; i++){
		teacher_stream >> teachers[i].id >> teachers[i].password >> teachers[i].first_name >> teachers[i].last_name;
	}
	
	while(getline(course_stream, course_line)){	
		courses[j] = Course(course_line);
		j++;
	}

}

//Copy constructor
University::University(const University &old_university){
	name = old_university.name;
	address = old_university.address;
	current_term = old_university.current_term;
	num_courses = old_university.num_courses;
	num_teachers = old_university.num_teachers;
	num_results = old_university.num_results;
	teachers = new teacher[old_university.num_teachers];
	courses = new Course[old_university.num_courses];
	results = new Course[old_university.num_results];
	for(int i = 0; i < old_university.num_courses; i++){
		courses[i] = old_university.courses[i];
	}
	for(int i = 0; i < old_university.num_teachers; i++){
		teachers[i] = old_university.teachers[i];
	}
	for(int i = 0; i < old_university.num_results; i++){
		results[i] = old_university.results[i];
	}
}

//Assignment operator overload
University& University::operator= (const University &old_university){
	name = old_university.name;
	address = old_university.address;
	current_term = old_university.current_term;
	
	delete[] teachers;
	delete[] results;
	delete[] courses;
	teachers = new teacher[old_university.num_teachers];
	courses = new Course[old_university.num_courses];
	results = new Course[old_university.num_results];
	num_results = old_university.num_results;
	num_teachers = old_university.num_teachers;
	num_courses = old_university.num_courses;
	for(int i = 0; i < old_university.num_courses; i++){
		courses[i] = old_university.courses[i];
	}
	for(int i = 0; i < old_university.num_teachers; i++){
		teachers[i] = old_university.teachers[i];
	}
	for(int i = 0; i < old_university.num_results; i++){
		results[i] = old_university.results[i];
	}

	return *this;	
}

//destructor
University::~University(){
	delete[] courses;
	delete[] teachers;
	delete[] results;
}

/********************************************************
 * Funciton: Calculate_num_teachers
 * Parameters: reference to fstream
 * Returns: int
 * Description: Calculates the number of teachers in 
 *				teachers.txt
 * *****************************************************/
int University::calculate_num_teachers(fstream &teacher_stream){
	string current_line;
	int count = 0;
	while(getline(teacher_stream, current_line)){
		count++;
	}
	teacher_stream.clear();
	teacher_stream.seekg(0, ios::beg);
	return count;
}

/********************************************************
 * Funciton: calculate_num_courses
 * Parameters: reference to fstream
 * Returns: int
 * Description: calculates the number of courses in the
 *				courses.txt file
 * *****************************************************/
int University::calculate_num_courses(fstream &course_stream){
	string current_line;
	int count = 0;
	while(getline(course_stream, current_line)){
		count++;
	}
	course_stream.clear();
	course_stream.seekg(0, ios::beg);
	return count;
}

/********************************************************
 * Funciton: search_courses_by_term
 * Parameters: string
 * Returns: Course*
 * Description: Returns an array of courses that have the 
 *				term entered by the user
 * *****************************************************/
Course * University::search_courses_by_term(string term){
	num_results = 0;
	for(int i = 0; i < num_courses; i++){
		if(courses[i].get_course_time()->term == term){
			num_results++;
		}
	}
	int j = 0;
	delete[] results;
	results = new Course[num_results];
	for(int i = 0; i < num_courses; i++){
		if(courses[i].get_course_time()->term == term){
			results[j] = courses[i];
			j++;
		}
	}
	return results;
}

/********************************************************
 * Funciton: search_courses_by_times
 * Parameters: string*, int
 * Returns: Course*
 * Description: returns an array of courses that do not contain
 *				the start times entered in by the user
 * *****************************************************/
Course * University::search_courses_by_times(string* times, int num_times){
	if(results == nullptr){
		num_results = num_courses;
		results = new Course[num_courses];
		for(int i = 0; i < num_courses; i++){
			results[i] = courses[i];
		}
	}	
	for(int i = 0; i < num_times; i++){
		for(int j = 0; j < num_results; j++){
			if(results[j].get_course_time()->start_time == times[i]){
				remove_result(j);
				j--;	
			}
		}
	}
	return results;
}

/********************************************************
 * Funciton: add_to_catalog
 * Parameters: Course
 * Returns: none
 * Description:  Adds a Course to the course catalog
 * *****************************************************/
void University::add_to_catalog(Course course_to_add){
	Course* temp = new Course[num_courses + 1];
	
	for(int i = 0; i < num_courses; i++){
		temp[i] = courses[i];
	}
	delete[] courses;
	courses = new Course[num_courses + 1];
	for(int i = 0; i < num_courses; i++){
		courses[i] = temp[i];
	}
	delete[] temp;
	num_courses++;
	courses[num_courses - 1] = course_to_add;
}

/********************************************************
 * Funciton: remove_result
 * Parameters: int
 * Returns: nothing
 * Description: removes an element from the results array
 * *****************************************************/
void University::remove_result(int index){
	bool found = false;
	Course* temp = new Course[num_results - 1];
	for(int i = 0; i < num_results - 1; i++){
		if(i == index){
			found = true;
		}
		if(found){
			temp[i] = results[i + 1]; 
		}
		else{
			temp[i] = results[i];
		}
	}
	num_results--;
	delete[] results;
	results = new Course[num_results];
	for(int i = 0; i < num_results; i++){
		results[i] = temp[i];	
	}
	delete[] temp;
}

/********************************************************
 * Funciton: remove_from_catalog
 * Parameters: int
 * Returns: nothing
 * Description: removes a Course from the courses array
 * *****************************************************/
void University::remove_from_catalog(int index_of_course){
	bool found_course = false;
	Course* temp = new Course[num_courses - 1];
	for(int i = 0; i < num_courses - 1; i++){
		if(i == index_of_course){
			found_course = true;
		}
		if(found_course){
			temp[i] = courses[i + 1]; 
		}
		else{
			temp[i] = courses[i];
		}
	}
	num_courses--;
	delete[] courses;
	courses = new Course[num_courses];
	for(int i = 0; i < num_courses; i++){
		courses[i] = temp[i];	
	}
	delete[] temp;
}

/********************************************************
 * Funciton: ACCESSORS
 * Parameters: none
 * Returns: Member variavle 
 * Description: Allows access to private members from 
 *				outside the class
 * *****************************************************/
int University::get_num_teachers() const{
	return num_teachers;
}

string University::get_name() const{
	return name;
}

int University::get_num_results() const{
	return num_results;
}

Course * University::get_results() const{
	return results;
}

string University::get_address() const{
	return address;
}

string University::get_current_term() const{
	return current_term;
}

teacher* University::get_teachers() const{
	return teachers;
}

int University::get_num_courses() const{
	return num_courses;
}

Course* University::get_courses() const{
	return courses;
}

/********************************************************
 * Funciton: MUTATORS
 * Parameters: Must match type of member variable
 * Returns: nothing
 * Description: Allows change to private members from outside
 *				the class
 * *****************************************************/
void University::set_num_teachers(int num_teachers){
	this->num_teachers = num_teachers;
}

void University::set_name(string name){
	this->name = name;
}

void University::set_address(string address){
	this->address = address;
}

void University::set_current_term(string current_term){
	this->current_term = current_term;
}

void University::set_teachers(teacher* teachers){
	this->teachers = teachers;
}

void University::set_num_courses(int num_courses){
	this->num_courses = num_courses;
}

void University::set_courses(Course* courses){
	this->courses = courses;
}

void University::set_num_results(int num_results){
	this->num_results = num_results;
}
