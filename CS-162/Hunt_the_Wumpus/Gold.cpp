/******************************
 * Program: Gold.cpp
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: Definitions for Gold class function
 *****************************/

#include "Gold.h"
#include <string>

/* Default constructor for Gold object.
 * Sets the percept accordingly
 */
Gold::Gold(){
	m_percept = "You see a glimmer nearby.";
}

/* Gold object destructor.
 * Nothing to delete, but is still needed
 * to override Event destructor
 */
Gold::~Gold(){}

/* Returns a string which is 
 * the percept for the Gold
 */
std::string Gold::percept(){
	return this->m_percept;
}

/* Returns a char based on the type of event this
 * object is. In this case it is 'g' for gold
 */
char Gold::get_type(){
	return 'g';
}
