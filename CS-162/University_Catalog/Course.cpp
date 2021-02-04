/******************************************************
 * Program: Course.cpp
 * Author: Cameron McCawley
 * Date: 10/25/2019
 * Description: definitions of Course functions
 * Input:
 * Output:
 * ******************************************************/


#include <string>
#include <fstream>
#include <sstream>
#include "structs.h"
#include "Course.h"
using namespace std;

//default constructor
Course::Course(){
	roster = nullptr;
	course_time = nullptr;
	name = " ";
	current_enrolled = 0;
}

//constructor that takes in a string
//which is then parsed
Course::Course(string line){
	stringstream stream(line);
	course_time = new schedule;
	stream >> name >> teacher >> course_time->term >> course_time->days >> course_time->start_time;
	stream >> course_time->end_time >> course_time->location >> current_enrolled;
	roster = new string[current_enrolled];
	for(int i = 0; i < current_enrolled; i++){
		stream >> roster[i];
	}
}

//constructor that takes in string, string, and *s
Course::Course(string n, string t, schedule *s){
	name = n;
	teacher = t;
	course_time = new schedule;
	*course_time = *s;
	roster = nullptr;
	current_enrolled = 0;
}

//copy constructor
Course::Course(const Course &old_course){
	name = old_course.name;
	teacher = old_course.teacher;
	current_enrolled = old_course.current_enrolled;
	roster = new string[old_course.current_enrolled];
	for(int i = 0; i < old_course.current_enrolled; i++){
		roster[i] = old_course.roster[i];
	}
	course_time = new schedule;
	*course_time = *old_course.course_time;
}

//assignment operatror overload constructor
Course& Course::operator= (const Course &old_course){
	name = old_course.name;
	teacher = old_course.teacher;
	
	delete[] roster;
	roster = new string[old_course.current_enrolled];
	current_enrolled = old_course.current_enrolled;

	for(int i = 0; i < current_enrolled; i++){
		roster[i] = old_course.roster[i];
	}
		
	delete course_time;
	course_time = new schedule;
	*course_time = *old_course.course_time;
	return *this;
}

//destructor
Course::~Course(){
	delete[] roster;
	delete course_time;
}

/********************************************************
 * Funciton: change_course_time 
 * Parameters: schedule*
 * Returns: nothing
 * Description: changes the course time
 * *****************************************************/
void Course::change_course_time(schedule* s){
	delete course_time;
	course_time = new schedule;
	*course_time = *s;
}

/********************************************************
 * Funciton: enroll_student
 * Parameters: string
 * Returns: nothing
 * Description: Enrolls a new student to the course
 * *****************************************************/
void Course::enroll_student(string new_student){

	string* temp = new string[current_enrolled + 1];
	
	for(int i = 0; i < current_enrolled; i++){
		temp[i] = roster[i];
	}
	current_enrolled++;
	
	delete[] roster;
	
	roster = new string[current_enrolled];
	for(int i = 0; i < current_enrolled; i++){
		roster[i] = temp[i];
	}

	delete[] temp;
	roster[current_enrolled - 1] = new_student;	
}

/********************************************************
 * Funciton: unenroll_student
 * Parameters: int
 * Returns: nothing
 * Description: removes a student from the course 
 * *****************************************************/
void Course::unenroll_student(int index){
	bool found_student = false;
	string* temp = new string[current_enrolled - 1];
	for(int i = 0; i < current_enrolled - 1; i++){
		if(i == index){
			found_student = true;
		}
		if(found_student){
			temp[i] = roster[i + 1]; 
		}
		else{
			temp[i] = roster[i];
		}
	}
	current_enrolled--;
	delete[] roster;
	roster = new string[current_enrolled];
	for(int i = 0; i < current_enrolled; i++){
		roster[i] = temp[i];	
	}
	delete[] temp;
}

/********************************************************
 * Funciton: ACCESSORS
 * Parameters: none
 * Returns: Member variable
 * Description: Allows reading private members from outside
 *				the class
 * *****************************************************/
string Course::get_name() const{
	return name;
}

string Course::get_teacher() const{
	return teacher;
}

int Course::get_current_enrolled() const{
	return current_enrolled;
}

string* Course::get_roster() const{
	return roster;
}

schedule* Course::get_course_time() const{
	return course_time;
}

/********************************************************
 * Funciton: MUTATORS
 * Parameters: type must match member type
 * Returns: nothing
 * Description: Allows writeing to private members from 
 *				outside the class
 * *****************************************************/
void Course::set_name(string name){
	this->name = name;
}

void Course::set_teacher(string teacher){
	this->teacher = teacher;
}

void Course::set_current_enrolled(int current_enrolled){
	this->current_enrolled = current_enrolled;
}

void Course::set_roster(string* roster){
	this->roster = roster;
}

void Course::set_course_time(schedule* s){
	delete course_time;
	course_time = new schedule;
	*course_time = *s;
}

