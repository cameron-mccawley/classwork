/******************************
 * Program: Wumpus.cpp
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: Definitions for Wumpus class Functions
 *****************************/

#include "Wumpus.h"
#include <string>

/* Default constructor for Wumpus object.
 * Sets the percept accordingly
 */
Wumpus::Wumpus(){
	m_percept = "You smell a terrible stench.";
}

/* Wumpus object destructor.
 * Nothing to delete, but is still needed
 * to override Event destructor
 */
Wumpus::~Wumpus(){}

/* Returns a string which is 
 * the percept for the Wumpus
 */
std::string Wumpus::percept(){
	return this->m_percept;
}

/* Returns a char based on the type of event this
 * object is. In this case it is 'w' for wumpus
 */
char Wumpus::get_type(){
	return 'w';
}
