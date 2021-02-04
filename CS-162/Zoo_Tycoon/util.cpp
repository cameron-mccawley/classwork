/************************************
* Program: util.cpp
* Author: Cameron McCawley
* Date: 10/31/19
* Description: utility function definitions
*************************************/


#include "util.h"
#include "Zoo.h"
#include <iostream>
#include <string>

#define ADULT_AGE 48
#define BABY_AGE 6
#define NUM_SPECIES 3

/*
Description: Welcomes the user to the game of Zoo Tycoon, and gives them 
					everything they need to know to play the game.
*/
void welcome_page(){
	std::cout << "Welcome to Zoo Tycoon! A game where you buy animals or something." << std::endl;
	std::cout << "Look, all ya need to know is that you've got $100,000 and a zoo at your disposal." << std::endl;
	std::cout << "Go buy some animals, make some moneys, and try not to go bankrupt.\nHave fun!" << std::endl;
	std::cout << "---------------------------------------------------------------------------" << std::endl;
}

/*
Description: Prompts the user if they want to continue to the next day or if 
			they want to quit. Quiting ends the game
*/
bool prompt_to_continue(){
	int input;

	std::cout << "Press [1] to move on to the next month, or [0] to quit" << std::endl;
	while(!(std::cin >> input) || (input != 0 && input != 1)){
		std::cin.clear();
		std::cin.ignore(80, '\n'); /*Note: If user inputs something over 80 characters, then 
									the error will throw for every character after 80*/

		std::cout << "Error! Not a valid option. Please try again: " << std::endl;
	}

	if(input == 0){
		return false;
	}else{
		return true;
	}
}

/*
Description: Prompts the user if they would like to buy an
			animal. If they say yes, then they are prompted for 
			which type of animal, and then how many they 
			will buy. 
*/
void prompt_for_animal(Zoo& zootopia){
	int num_buying;
	std::string input;
	int type;
	while(true){
		std::cout << "Would you like to buy any animals today? [y] or [n] " << std::endl;
		std::cin >> input;
		if(input == "y"){

			std::cout << "What type of animal do you want to buy?" << std::endl;
			std::cout << "[1] Sea lion ($700)\n[2] Black bear ($5,000)\n[3] Tiger($12,000)" << std::endl;
			while(!(std::cin >> type) || type < 1 || type > 3){
				std::cin.clear();
				std::cin.ignore(80, '\n');
				std::cout << "Error! Not a valid option, please try again." << std::endl;
			}

			std::cout << "Would you like to buy [1] or [2]?" << std::endl;
			while(!(std::cin >> num_buying) || num_buying < 1 || num_buying > 2){
				std::cin.clear();
				std::cin.ignore(80, '\n');
				std::cout << "Error! Not a valid option. please try again." << std::endl;
			}		

			buy_animals(type, num_buying, zootopia);
			return;

		}else if(input == "n"){
			std::cout << "Sounds good!" << std::endl;
			return;
		}else{
			std::cout << "Error! Not a valid option. Please try again." << std::endl;
		}
	}
}

/*
Description: This will call the appropriate add animal function
			based on the type and number of animals
			being bought
*/
void buy_animals(int type, int num, Zoo& zootopia){
	
	if(type == 1){
		for(int i = 0; i < num; i++){
			zootopia.add_sea_lion(ADULT_AGE);
			zootopia.set_money(zootopia.get_money() - 700.0); //$700 is cost of sea lion
		}
	}else if(type == 2){
		for(int i = 0; i < num; i++){
			zootopia.add_bear(ADULT_AGE);
			zootopia.set_money(zootopia.get_money() - 5000.0); //$5000 is cost of bear
		}
	}else{
		for(int i = 0; i < num; i++){
			zootopia.add_tiger(ADULT_AGE);
			zootopia.set_money(zootopia.get_money() - 12000.0); //$12000 is cost of tiger
		}
	}

}
