/******************************
 * Program: Pit.cpp
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: Definitions for Pit class function
 *****************************/

#include "Pit.h"
#include <string>

/* Default constructor for Pit object.
 * Sets the percept accordingly
 */
Pit::Pit(){
	m_percept = "You feel a breeze.";
}

/* Pit object destructor.
 * Nothing to delete, but is still needed
 * to override Event destructor
 */
Pit::~Pit(){}

/* Returns a string which is 
 * the percept for the Pit
 */
std::string Pit::percept(){
	return this->m_percept;
}

/* Returns a char based on the type of event this
 * object is. In this case it is 'p' for pit
 */
char Pit::get_type(){
	return 'p';
}

