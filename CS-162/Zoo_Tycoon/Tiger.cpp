/************************************
* Program: Tiger.cpp
* Author: Cameron McCawley
* Date: 10/31/19
* Description: Tiger class prototype definition
*************************************/

#include "Tiger.h"
#include "Animal.h"

/*
Description: Default constructor for 
			tiger object
*/

Tiger::Tiger(){
	
	set_babies_per_birth(3);
	set_cost(12000);
	set_food_mult(5);
}

/*
Description: Parameterized constructor for
			tiger object
*/
Tiger::Tiger(int a) : Animal(a){
	set_age(a);
	set_babies_per_birth(3);
	set_cost(12000);
	set_food_mult(5);
}

Tiger::~Tiger(){

}
