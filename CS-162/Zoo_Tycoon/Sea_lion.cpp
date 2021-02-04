/************************************
* Program: Sea_lion.cpp
* Author: Cameron McCawley
* Date: 10/31/19
* Description: Sea_lion class prototype definitions
*************************************/

#include "Sea_lion.h"
#include "Animal.h"

/*
Description: Default constructor for Sea_lion
			object
*/
Sea_lion::Sea_lion(){
	
	set_babies_per_birth(1);
	set_cost(700);
	set_food_mult(1);
}

/*
Description: Parameterized constructor for Sea_lion object
*/
Sea_lion::Sea_lion(int a) : Animal(a){
	set_age(a);	
	set_babies_per_birth(1);
	set_cost(700);
	set_food_mult(1);
}

Sea_lion::~Sea_lion(){

}
