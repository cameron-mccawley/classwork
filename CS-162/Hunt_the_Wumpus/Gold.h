/******************************
 * Program: Gold.h
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: Declaration of the Gold class
 *****************************/

#pragma once
#include "Event.h"


class Gold final : public Event{
	public:
		Gold();
		~Gold();
		char get_type();
		std::string percept();
	private:
		std::string m_percept;
};
