/******************************
 * Program: Pit.h
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: Declaration of the Pit class
 *****************************/

#pragma once
#include "Event.h"
#include <string>

class Pit final : public Event{
	public:
		Pit();
		~Pit();
		char get_type();
		std::string percept();
	private:
		std::string m_percept;
};
