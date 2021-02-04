/******************************
 * Program: Bats.cpp
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: Function definitions for the Bats class
 *****************************/

#include "Bats.h"
#include <string>

/* Default constructor for Bats object.
 * Sets the percept accordingly
 */
Bats::Bats(){
	m_percept = "You hear wings flapping.";
}

/* Bats object destructor.
 * Nothing to delete, but is still needed
 * to override Event destructor
 */
Bats::~Bats(){}

/* Returns a string which is 
 * the percept for the Bats
 */
std::string Bats::percept(){
	return this->m_percept;	
}

/* Returns a char based on the type of event this
 * object is. In this case it is 'b' for bat
 */
char Bats::get_type(){
	return 'b';
}
