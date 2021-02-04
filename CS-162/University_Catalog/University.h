/******************************************************
 * Program: University.h
 * Author: Cameron McCawley
 * Date: 10/25/2019
 * Description: University Class and it's prototypes 
 * Input:
 * Output:
 * ******************************************************/

#pragma once
#include <fstream>
#include <string>
#include "structs.h"
#include "Course.h"

class University{
	public:
		University();
		University(std::fstream &, std::fstream &, std::fstream &);
		University(const University &); //deep copy
		University& operator= (const University &);
		~University();
		
		int calculate_num_courses(std::fstream &);
		int calculate_num_teachers(std::fstream &);

		Course * search_courses_by_term(std::string term);
		Course * search_courses_by_times(std::string* times, int num_times);
		
		void remove_result(int index);
		void add_to_catalog(Course course_to_add);
		void remove_from_catalog(int index_of_course);
		
		int get_num_teachers() const;
		std::string get_name() const;
		std::string get_address() const;
		std::string get_current_term() const;
		teacher* get_teachers() const;
		int get_num_results() const;
		int get_num_courses() const;
		Course* get_courses() const;
		Course* get_results() const;
		
		void set_num_teachers(int);
		void set_name(std::string);
		void set_address(std::string);
		void set_current_term(std::string);
		void set_teachers(teacher*);
		void set_num_courses(int);
		void set_courses(Course*);
		void set_num_results(int);
		
		
	private:
		int num_teachers;
		std::string name;
		std::string address;
		std::string current_term;
		teacher* teachers;
		int num_courses;
		int num_results;
		Course* courses;
		Course* results;
};

