/******************************
 * Program: Bats.h
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: Declaration of the Bats class
 *****************************/

#pragma once
#include "Event.h"
#include <string>

class Bats final : public Event{
	public:
		Bats();
		~Bats();
		char get_type();
		std::string percept();
	private:
		std::string m_percept;
};
