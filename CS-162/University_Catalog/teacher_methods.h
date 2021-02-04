/******************************************************
 * Program: teacher_methods.h
 * Author: Cameron McCawley
 * Date: 10/25/2019
 * Description: function prototypes
 * Input:
 * Output:
 * ******************************************************/


#include <string>
#include "Course.h"
#include "University.h"

bool log_teacher_in(University &);
void teacher_options(University &);
void add_course(University &);
void remove_course(University &);
void view_enrolled_students(University &);
void remove_student(University &);
void change_schedule_info(Course *, int, std::string);
void change_course_information(University &);

