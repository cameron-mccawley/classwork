/******************************************************
 * Program: Course.h
 * Author: Cameron McCawley
 * Date: 10/25/2019
 * Description: Course class and it's prototypes  
 * Input:
 * Output:
 * ******************************************************/


#pragma once
#include <string>
#include "structs.h"

class Course{
	public:
		Course();
		Course(std::string);
		Course(std::string, std::string, schedule*);
		Course(const Course &); //deep copy
		Course& operator= (const Course &);
		~Course();
		
		//init(string, string, int, string*, schedule*);

		void change_course_time(schedule* course_time);
		void enroll_student(std::string new_student);
		void unenroll_student(int);
		
		std::string get_name() const;
		std::string get_teacher() const;
		int get_current_enrolled() const;
		std::string* get_roster() const;
		schedule* get_course_time() const;

		void set_name(std::string);
		void set_teacher(std::string);
		void set_current_enrolled(int);
		void set_roster(std::string*);
		void set_course_time(schedule*);

	private:
		std::string name;
		std::string teacher;
		int current_enrolled;
		std::string* roster;
		schedule* course_time;

};
