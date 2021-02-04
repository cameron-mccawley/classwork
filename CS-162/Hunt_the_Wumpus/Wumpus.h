/******************************
 * Program: Wumpus.h
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: Declaration of the Wumpus class
 *****************************/

#pragma once
#include "Event.h"
#include <string>

class Wumpus final : public Event{
	public:
		Wumpus();
		~Wumpus();
		std::string percept();
		char get_type();
	private:
		std::string m_percept;
};
