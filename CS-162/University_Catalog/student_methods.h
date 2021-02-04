/******************************************************
 * Program: student_methods.h
 * Author: Cameron McCawley
 * Date: 10/25/2019
 * Description: function prototypes 
 * Input:
 * Output:
 * ******************************************************/


#include "University.h"
#include "Course.h"
#include <string>

void student_options(University &, std::string);
std::string student_login();
Course * exclude_times(University &); 
void add_new_student(std::string);
bool student_exists(std::string);
bool enroll_from_list();
Course * get_results(University &, int);
void enroll(std::string, University &, int);
bool refine_search();
void append_enrollment(std::string, std::string, std::string);

