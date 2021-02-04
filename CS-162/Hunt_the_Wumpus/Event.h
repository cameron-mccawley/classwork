/******************************
 * Program:
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description:
 *****************************/

#pragma once
#include <string>

class Event{
	public:
		virtual ~Event() = 0;
		virtual std::string percept() = 0;
		virtual char get_type() = 0;	
		
};

