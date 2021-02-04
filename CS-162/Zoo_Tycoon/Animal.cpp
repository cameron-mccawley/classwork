/************************************
* Program: Animal.cpp
* Author: Cameron McCawley
* Date: 10/31/19
* Description: Animal class prototype definitions
*************************************/

#include "Animal.h"

/*
Description: Animal default constructor
*/
Animal::Animal(){
	age = 0;
	num_babies = 0;
	cost = 0;
	babies_per_birth = 0;
	food_mult = 0;
}

/*
Description: Parameterized animal constructor
*/
Animal::Animal(int a){
	age = a;
	num_babies = 0;
	cost = 0;
	babies_per_birth = 0;
	food_mult = 0;
}

Animal::~Animal(){

}

/*
Description: Incremnets the animals age
			by one
*/
void Animal::age_animal(){
	age += 1;
}

/*
Description: Accessor functions for private
			data members of Animal
*/
int Animal::get_age() const{
	return age;
}

int Animal::get_num_babies() const{
	return num_babies;
}

int Animal::get_cost() const{
	return cost;
}

int Animal::get_babies_per_birth() const{
	return babies_per_birth;
}

int Animal::get_food_mult() const{
	return food_mult;
}

/*
Description: Returns the age in years
			of the animal object
*/
int Animal::get_age_in_years() const{
	return age / 12;
}

/*
Description: Mutator funtions for private
			animal data members
*/
void Animal::set_age(int a){
	age = a;
}

void Animal::set_num_babies(int num_babies){
	this->num_babies = num_babies;
}

void Animal::set_cost(int cost){
	this->cost = cost;
}

void Animal::set_babies_per_birth(int babies_per_birth){
	this->babies_per_birth = babies_per_birth;
}

void Animal::set_food_mult(int food_mult){
	this->food_mult = food_mult;
}
