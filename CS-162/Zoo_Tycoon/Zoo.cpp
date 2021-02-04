/************************************
* Program: Zoo.cpp
* Author: Cameron McCawley
* Date: 10/31/19
* Description: Zoo class prototype definition
*************************************/

#include "Zoo.h"
#include "Animal.h"
#include "Sea_lion.h"
#include "Tiger.h"
#include "Bear.h"

#include <cstdlib>
#include <string>
#include <iostream>

#define ADULT_AGE 48
#define BABY_AGE 6
#define NUM_SPECIES 3

/*
Description: Deafault constructor for Zoo object
*/
Zoo::Zoo(){
	money = 100000.0;
	months = 0;
	num_animals = 0;
	sea_lions = nullptr;
	bears = nullptr;
	tigers = nullptr;
	num_sea_lions = 0;
	num_bears = 0;
	num_tigers = 0;
	num_adults = 0;
	num_babies = 0;
	boost = 0;
	probability_for_sick = 4;
	base_food_cost = 80.0;
}

/*
Description: Deconstructor for Zoo object
*/
Zoo::~Zoo(){
	
	delete[] sea_lions;
	delete[] bears;
	delete[] tigers;
}

/*
Description: Takes in the type of animal and the age
			and calls the appropriate add function 
*/
void Zoo::add_animal(int type, int age){
	switch(type){
		case 1: add_sea_lion(age);
			break;
		case 2: add_bear(age);
			break;
		case 3: add_tiger(age);
			break;
		default:
			break;
	}
}

/*
Description: Adds a sea lion with a given age
*/
void Zoo::add_sea_lion(int age){
	Sea_lion new_sea_lion(age);
	Sea_lion *temp = new Sea_lion[num_sea_lions + 1];
	
	for(int  i = 0; i < num_sea_lions; i++){
		temp[i] = sea_lions[i];
	}
	delete[] sea_lions;
	
	temp[num_sea_lions] = new_sea_lion;
	num_sea_lions++;
	num_animals++;
	if(age >= ADULT_AGE) num_adults++;
	if(age < BABY_AGE) num_babies++;
	sea_lions = temp;
}

/*
Description: adds a bear with the given age
*/
void Zoo::add_bear(int age){
	Bear new_bear(age);
	Bear *temp = new Bear[num_bears + 1];
	
	for(int  i = 0; i < num_bears; i++){
		temp[i] = bears[i];
	}
	delete[] bears;
	
	temp[num_bears] = new_bear;
	num_bears++;
	num_animals++;
	if(age >= ADULT_AGE) num_adults++;
	if(age < BABY_AGE) num_babies++;
	bears = temp;
}

/*
Description: adds a tiger with a given age
*/
void Zoo::add_tiger(int age){
	Tiger new_tiger(age);
	Tiger *temp = new Tiger[num_tigers + 1];
	
	for(int i = 0; i < num_tigers; i++){
		temp[i] = tigers[i];
	}
	
	delete[] tigers;

	temp[num_tigers] = new_tiger;
	num_tigers++;
	num_animals++;
	if(age >= ADULT_AGE) num_adults++;
	if(age < BABY_AGE) num_babies++;
	tigers = temp;
}

/*
Description: removes a sea_lion at the given index
*/
void Zoo::remove_sea_lion(int index){
	bool found_index = false;
	Sea_lion *temp = new Sea_lion[num_sea_lions - 1];
	
	for(int i = 0; i < num_sea_lions - 1; i++){
		if(i == index){
			if(sea_lions[i].get_age() < BABY_AGE) num_babies--;
			if(sea_lions[i].get_age() >= ADULT_AGE) num_adults--;
	
			found_index = true;
		}
		if(found_index){
			temp[i] = sea_lions[i + 1];
		}else{
			temp[i] = sea_lions[i];
		}
	}
	num_animals--;
	num_sea_lions--;
	delete[] sea_lions;
	sea_lions = temp;
}

/*
Description: removes a bear at the given index
*/
void Zoo::remove_bear(int index){
	bool found_index = false;
	Bear *temp = new Bear[num_bears - 1];

	for(int i = 0; i < num_bears - 1; i++){
		if(i == index){
			if(bears[i].get_age() < BABY_AGE) num_babies--;
			if(bears[i].get_age() >= ADULT_AGE) num_adults--;

			found_index = true;
		}
		if(found_index){
			temp[i] = bears[i + 1];
		}else{
			temp[i] = bears[i];
		}
	}
	num_animals--;
	num_bears--;
	delete[] bears;
	bears = temp;
}

/*
Description: removes a tiger at the given index
*/
void Zoo::remove_tiger(int index){
	bool found_index = false;
	Tiger *temp = new Tiger[num_tigers - 1];
	for(int i = 0; i < num_tigers - 1; i++){
		if(i == index){
			if(tigers[i].get_age() < BABY_AGE) num_babies--;
			if(tigers[i].get_age() >= ADULT_AGE) num_adults--;
			found_index = true;
		}
		if(found_index){
			temp[i] = tigers[i + 1];
		}else{
			temp[i] = tigers[i];
		}
	}
	num_animals--;
	num_tigers--;
	delete[] tigers;
	tigers = temp;
}

/*
Description: Picks one of the four random events that 
			can occur each month
*/
void Zoo::pick_random_event(){
	int is_sick = std::rand() % probability_for_sick + 1; //Probability depends on food
	boost = 0;
	if(is_sick == 1){ //animal gets sick
		if(num_animals != 0){
			sick();
			return;
		}
	}
	int event = std::rand() % 3 + 1;
	if(event == 1){ //adult animal has babies
		if(num_adults != 0){			
			birth();
			return;
		}
	}else if(event == 2){ //boom in zoo attendance
		boom();
		return;
	}
	std::cout << "No special event occurs during this month" << std::endl; //No special event

}

/*
Description: Calculates the boost in revenue gotten from
			the boost in attendance random event
*/
void Zoo::boom(){
	std::cout << "You got a boost in attendance!!!" << std::endl;
	for(int i = 0; i < num_sea_lions; i++){
		//TODO magic numbers AAAAAAAAAA
		boost += std::rand() % 250 + 151;
	}
	std::cout << "Becuase of the " << num_sea_lions << " sea lions you have, you get a boost of $" << boost << " this month!" << std::endl;

}

/*
Description: Picks a random animal to get sick, and 
			calls the appropriate sick function
*/
void Zoo::sick(){
	int type;
	int sick_boi_index;
	while(true){
		type = std::rand() % NUM_SPECIES + 1; //Pick random species of animal
		if(type == 1 && num_sea_lions != 0){ //sea lions
			sick_boi_index = std::rand() % num_sea_lions;
			sea_lion_sick(sea_lions[sick_boi_index], sick_boi_index);
			break;
		}else if(type == 2 && num_bears != 0){ //bears
			sick_boi_index = std::rand() % num_bears;
			bear_sick(bears[sick_boi_index], sick_boi_index);
			break;
		}else{ //tigers
			if(num_tigers != 0){
				sick_boi_index = std::rand() % num_tigers;
				tiger_sick(tigers[sick_boi_index], sick_boi_index);
				break;
			}
		}		
	}
}

/*
Description: Handles logic for when a sea_lion gets sick 
*/
void Zoo::sea_lion_sick(Sea_lion& sick_boi, int index){
	if(sick_boi.get_age() < BABY_AGE){
		std::cout << "Oh no! A baby sea lion got sick!" << std::endl;
		std::cout << "This is gonna cost you $" << sick_boi.get_cost() << std::endl;
		if(money >= sick_boi.get_cost()){
			std::cout << "Looks like you can afford it!" << std::endl;
			money -= sick_boi.get_cost();
		}else{
			std::cout << "Looks like you can't afford to cure him" << std::endl;
			std::cout << "Now he must D I E\nA shame too, he was only " << sick_boi.get_age() << " months old" << std::endl;
			remove_sea_lion(index);
		}
	}else{
		std::cout << "Oh no! An adult sea lion got sick!" << std::endl;
		std::cout << "This is gonna cost you $" << (sick_boi.get_cost() / 2) << std::endl; //Adults cost half their price to take care of when sick
		if(money >= (sick_boi.get_cost() / 2)){
			std::cout << "Looks like you can afford it!" << std::endl;
			money -= (sick_boi.get_cost() / 2);
		}else{
			std::cout << "Looks like you can't afford to cure him" << std::endl;
			std::cout << "Now he must D I E\nIt's ok though, he was at the ripe old age of " << sick_boi.get_age_in_years() << " years old" << std::endl;
			remove_sea_lion(index);
		}
	}
}

/*
Description: handles logic for when a bear gets sick
*/
void Zoo::bear_sick(Bear& sick_boi, int index){
	if(sick_boi.get_age() < BABY_AGE){
		std::cout << "Oh no! A baby bear got sick!" << std::endl;
		std::cout << "This is gonna cost you $" << sick_boi.get_cost() << std::endl;
		if(money >= sick_boi.get_cost()){
			std::cout << "Looks like you can afford it!" << std::endl;
			money -= sick_boi.get_cost();
		}else{
			std::cout << "Looks like you can't afford to cure him" << std::endl;
			std::cout << "Now he must D I E\nA shame too, he was only " << sick_boi.get_age() << " months old" << std::endl;
			remove_bear(index);
		}
	}else{
		std::cout << "Oh no! An adult bear got sick!" << std::endl;
		std::cout << "This is gonna cost you $" << (sick_boi.get_cost() / 2) << std::endl;
		if(money >= (sick_boi.get_cost() / 2)){
			std::cout << "Looks like you can afford it!" << std::endl;
			money -= (sick_boi.get_cost() / 2);
		}else{
			std::cout << "Looks like you can't afford to cure him" << std::endl;
			std::cout << "Now he must D I E\nIt's ok though, he was at the ripe old age of " << sick_boi.get_age_in_years() << " years old" << std::endl;
			remove_bear(index);
		}
	}
}

/*
Description: handles logic for when a tiger gets sick
*/
void Zoo::tiger_sick(Tiger& sick_boi, int index){
	if(sick_boi.get_age() < BABY_AGE){
		std::cout << "Oh no! A baby tiger got sick!" << std::endl;
		std::cout << "This is gonna cost you $" << sick_boi.get_cost() << std::endl;
		if(money >= sick_boi.get_cost()){
			std::cout << "Looks like you can afford it!" << std::endl;
			money -= sick_boi.get_cost();
		}else{
			std::cout << "Looks like you can't afford to cure him" << std::endl;
			std::cout << "Now he must D I E\nA shame too, he was only " << sick_boi.get_age() << " months old" << std::endl;
			remove_tiger(index);
		}
	}else{
		std::cout << "Oh no! An adult tiger got sick!" << std::endl;
		std::cout << "This is gonna cost you $" << (sick_boi.get_cost() / 2) << std::endl;
		if(money >= (sick_boi.get_cost() / 2)){
			std::cout << "Looks like you can afford it!" << std::endl;
			money -= (sick_boi.get_cost() / 2);
		}else{
			std::cout << "Looks like you can't afford to cure him" << std::endl;
			std::cout << "Now he must D I E\nIt's ok though, he was at the ripe old age of " << sick_boi.get_age_in_years() << " years old" << std::endl;
			remove_tiger(index);
		}
	}
}

/*
Description: Picks a random adult animal to give birth to 
			baby animals
*/
void Zoo::birth(){
	int type;
	while(true){
		type = std::rand() % NUM_SPECIES + 1; //Pick random species to give birth
		if(type == 1 && num_sea_lions != 0){ //sea lions
			for(int i = 0; i < num_sea_lions; i++){
				if(sea_lions[i].get_age() >= ADULT_AGE){ //Make sure animal is an adult
					std::cout <<"An adult sea lion gave birth to " << sea_lions[i].get_babies_per_birth() << " babies!!!" << std::endl;
					for(int j = 0; j < sea_lions[i].get_babies_per_birth(); j++){
						add_sea_lion(0);
					}
					return;
				}
			}
		}else if(type == 2 && num_bears != 0){ //bears
			for(int i = 0; i < num_bears; i++){
				if(bears[i].get_age() >= ADULT_AGE){ 
					std::cout <<"An adult bear gave birth to " << bears[i].get_babies_per_birth() << " babies!!!" << std::endl;
					for(int j = 0; j < bears[i].get_babies_per_birth(); j++){
						add_bear(0);
					}
					return;
				} 
			}
		}else if(type == 3 && num_tigers != 0){ //tigers
			for(int i = 0; i < num_tigers; i++){
				if(tigers[i].get_age() >= ADULT_AGE){
					std::cout <<"An adult tiger gave birth to " << tigers[i].get_babies_per_birth() << " babies!!!" << std::endl;
					for(int j = 0; j < tigers[i].get_babies_per_birth(); j++){
						add_tiger(0);
					}
					return;
				}
			}
		} 
	}
}

/*
Description: Ages all of the animals one month
*/
void Zoo::age_animals(){
	for(int i = 0; i < num_sea_lions; i++){
		sea_lions[i].age_animal();
		if(sea_lions[i].get_age() == BABY_AGE) num_babies--; //See if animal transitions into a new part of life (baby -> adolescence -> adult)
		if(sea_lions[i].get_age() == ADULT_AGE) num_adults++;
	}
	for(int i = 0; i < num_bears; i++){
		bears[i].age_animal();
		if(bears[i].get_age() == BABY_AGE) num_babies--;
		if(bears[i].get_age() == ADULT_AGE) num_adults++;
	}
	for(int i = 0; i < num_tigers; i++){
		tigers[i].age_animal();
		if(tigers[i].get_age() == BABY_AGE) num_babies--;
		if(tigers[i].get_age() == ADULT_AGE) num_adults++;
	}
}

/*
Description: Calculates the total revenue earned for the current month
*/
void Zoo::generate_revenue(){
	revenue = boost;	
	for(int i = 0; i < num_sea_lions; i++){
		if(sea_lions[i].get_age() < BABY_AGE){
			revenue += ((sea_lions[i].get_cost() * 0.2) * 2); //Babies generate twice as much
		}else{
			revenue += (sea_lions[i].get_cost() * 0.2);
		}
	}
	for(int i = 0; i < num_bears; i++){
		if(bears[i].get_age() < BABY_AGE){
			revenue += ((bears[i].get_cost() * 0.1) * 2);
		}else{
			revenue += (bears[i].get_cost() * 0.1);
		}
	}
	for(int i = 0; i < num_tigers; i++){
		if(tigers[i].get_age() < BABY_AGE){
			revenue += ((tigers[i].get_cost() * 0.1) * 2);
		}else{
			revenue += (tigers[i].get_cost() * 0.1);
		}
	}
	money += revenue;
	std::cout << "Zoo generated $" << revenue << " this month!" << std::endl;
	
}

/*
Description: Generates the new base food cost for the next month
			Also allows the user to pick between 3 different food
			options, which affect the probability for an 
			animal getting sick
*/
void Zoo::generate_new_food_cost(){
	double percent;
	int food_choice;
	int r = std::rand() % 41 + 80; // Picks a random number between 80 and 120
	percent = r * 0.01;
	base_food_cost = base_food_cost * percent; //converts to a percentage
	std::cout << "What kind of animal food would you like to buy?" << std::endl;
	std::cout << "[1] Regular (Cost: +0%. Chances for sickness: +0%)\n[2] Premium (Cost: +100%. Chances for sickness: -50%)" << std::endl;
	std::cout << "[3] Cheap (Cost: -50%. Chances for sickness: +100%)" << std::endl;
	while(!(std::cin >> food_choice) || food_choice < 1 || food_choice > 3){
		std::cin.clear();
		std::cin.ignore(80, '\n');
		std::cout << "Error! Invalid input. Please try again." << std::endl;
	}
	switch(food_choice){ //Change probability based on food bought
		case 1: probability_for_sick = 4; 
				break;
		case 2: probability_for_sick = 8;
				base_food_cost *= 2;
				break;
		case 3: probability_for_sick = 2;
				base_food_cost /= 2;
				break;
	}
}

/*
Description: Subtracts the cost of food for the current month
*/
void Zoo::subtract_food_cost(){
	double total_deductions = 0;
	generate_new_food_cost();
	for(int i = 0; i < num_sea_lions; i++){
		total_deductions += sea_lions[i].get_food_mult() * base_food_cost;
	}
	for(int i = 0; i < num_bears; i++){
		total_deductions += bears[i].get_food_mult() * base_food_cost;
	}
	for(int i = 0; i < num_tigers; i++){
		total_deductions += tigers[i].get_food_mult() * base_food_cost;
	}

	std::cout << "Food for this month cost you $" << total_deductions << std::endl;
	money -= total_deductions;
}

/*
Description: Displays all the imortant information 
			at the end of the month
*/
void Zoo::display() const{
	int adult_sea_lions = 0;
	int adult_bears = 0;
	int adult_tigers = 0;
	int baby_sea_lions = 0;
	int baby_bears = 0;
	int baby_tigers = 0;
	for(int i = 0; i < num_sea_lions; i++){ //Get the number of babies and adults for each animal
		if(sea_lions[i].get_age() < BABY_AGE) baby_sea_lions++;
		if(sea_lions[i].get_age() >= ADULT_AGE) adult_sea_lions++;
	}
	for(int i = 0; i < num_bears; i++){
		if(bears[i].get_age() < BABY_AGE) baby_bears++;
		if(bears[i].get_age() >= ADULT_AGE) adult_bears++;
	}
	for(int i = 0; i < num_tigers; i++){
		if(tigers[i].get_age() < BABY_AGE) baby_tigers++;
		if(tigers[i].get_age() >= ADULT_AGE) adult_tigers++;
	}

	std::cout << "---------------------------------------" << std::endl;
	std::cout << "            End of Month #" << months << std::endl;
	std::cout << "---------------------------------------" << std::endl;	
	std::cout << "Number of Total Babies: " << num_babies << std::endl;
	std::cout << "Number of Total Adolescents: " << num_animals - num_babies - num_adults << std::endl;
	std::cout << "Number of Total Adults: " << num_adults << std::endl;
	std::cout << std::endl;
	std::cout << "Number of Total Sea Lions: " << num_sea_lions << std::endl;
	std::cout << "          Number of Baby Sea Lions: " << baby_sea_lions << std::endl;
	std::cout << "          Number of Adolescent Sea Lions: " << num_sea_lions - baby_sea_lions - adult_sea_lions << std::endl;
	std::cout << "          Number of Adult Sea Lions: " << adult_sea_lions <<std::endl;
	std::cout << "\nNumber of Total Bears: " << num_bears << std::endl;
	std::cout << "          Number of Baby Bears: " << baby_bears << std::endl;
	std::cout << "          Number of Adolescent Bears: " << num_bears - baby_bears - adult_bears << std::endl;
	std::cout << "          Number of Adult Bears: " << adult_bears << std::endl;
	std::cout << "\nNumber of Total Tigers: " << num_tigers << std::endl;
	std::cout << "          Number of Baby Tigers: " << baby_tigers << std::endl;
	std::cout << "          Number of Adolescent Tigers: " << num_tigers - baby_tigers - adult_tigers << std::endl;
	std::cout << "          Number of Adult Tigers: " << adult_tigers << std::endl;
	std::cout << std::endl;
	std::cout << "TOTAL ANIMALS: " << num_animals << std::endl;
	std::cout << "TOTAL MONEY: $" << money << std::endl;
	std::cout << std::endl;
}

/*
Description: Accessor functions for Zoo
*/
int Zoo::get_months() const{
	return months;
}

double Zoo::get_money() const{
	return money;
}

/*
Description: Mutator functions for Zoo
*/
void Zoo::set_months(int months){
	this->months = months;
}

void Zoo::set_money(double money){
	this->money = money;
}

