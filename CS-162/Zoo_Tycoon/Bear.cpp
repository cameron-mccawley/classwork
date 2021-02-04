/************************************
* Program: Bear.cpp
* Author: Cameron McCawley
* Date: 10/31/19
* Description: Bear class prototype definition
*************************************/


#include "Bear.h"
#include "Animal.h"
/*
Description: Default constructor for
			bear object
*/

Bear::Bear(){
	
	set_babies_per_birth(2);
	set_cost(5000);
	set_food_mult(3);
}

/*
Description: Parameterized constructor for 
			bear object
*/
Bear::Bear(int a) : Animal(a){
	set_age(a);
	set_babies_per_birth(2);
	set_cost(5000);
	set_food_mult(3);
}

Bear::~Bear(){

}
