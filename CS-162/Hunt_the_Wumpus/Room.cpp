/******************************
 * Program:
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: Definitions for Room class functions.
 *				Each Room has a set of flags that 
 *				help tell what is in it
 *****************************/

#include "Room.h"
#include "Event.h"

/* Room default constructor.
 * Initializes member variables
 */
Room::Room(){
	event = nullptr;
	is_empty = true;
	has_player = false;
}

/* Room destructor.
 * Frees memory allocated for event
 */
Room::~Room(){
	delete event;
}

/* Removes whatever event is pointing to
 * and sets the pointer to nullptr.
 * Function should not be called if event is already nullptr
 */
void Room::remove_event(){
	delete event;
	event = nullptr;
	is_empty = true;
}

/* Mutator functions for Room class
 */
void Room::set_event(Event *e){
	event = e;	
}

void Room::set_is_empty(bool e){
	is_empty = e;
}

void Room::set_has_player(bool p){
	has_player = p;
}

/* Accessor functions for Room class
 */
Event* Room::get_event(){
	return event;
}

bool Room::get_is_empty(){
	return is_empty;
}

bool Room::get_has_player(){
	return has_player;
}

