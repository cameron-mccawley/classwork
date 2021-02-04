/******************************
 * Program: Room.h
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: Declaration of the Room class
 *****************************/

#pragma once

#include "Event.h"
#include <string>

class Room {
	public:
		Room();
		~Room();

		void remove_event();

		void set_is_empty(bool);
		void set_event(Event *);
		void set_has_player(bool);
		Event* get_event();
		bool get_has_player();
		bool get_is_empty();
		

	private:
		Event* event;
		bool is_empty;
		bool has_player;
		
};
