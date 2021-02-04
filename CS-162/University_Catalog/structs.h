/******************************************************
 * Program: structs.h
 * Author: Cameron McCawley
 * Date: 10/25/2019
 * Description: prototypes structures
 * Input:
 * Output:
 * ******************************************************/


#pragma once
#include <string>

struct teacher{
	int id;
	std::string password;
	std::string first_name;
	std::string last_name;
};

struct schedule{
	std::string days;
	std::string start_time;
	std::string end_time;
	std::string term;
	std::string location;
};


