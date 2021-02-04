/************************************
* Program: prog.cpp
* Author: Cameron McCawley
* Date: 10/31/19
* Description: Main driver file
*************************************/


#include "util.h"
#include "Zoo.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

/*
Description: Main function of our program. 
			Loops through all of the things that
			happen each month.
*/
int main(){
	welcome_page();	
	std::srand(std::time(0));
	Zoo zootopia;
	while(true){
		std::cout << "Month: " << zootopia.get_months() << std::endl;
		zootopia.age_animals();
		zootopia.pick_random_event();
		zootopia.generate_revenue();
		prompt_for_animal(zootopia);
		zootopia.subtract_food_cost();
		zootopia.display();
		if(zootopia.get_money() < 0){
			std::cout << "Oh no! You went bankrupt!!!" << std::endl;
			break;
		}
		if(!prompt_to_continue()) break;
		zootopia.set_months(zootopia.get_months() + 1);
	}
	



	std::cout << "Thank you for playing!" << std::endl;
	return 0;
}
