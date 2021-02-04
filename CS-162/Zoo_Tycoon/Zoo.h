/************************************
* Program: Zoo.h
* Author: Cameron McCawley
* Date: 10/31/19
* Description: Zoo class
*************************************/

#pragma once
#include "Sea_lion.h"
#include "Bear.h"
#include "Tiger.h"
#include "Animal.h"

class Zoo{

	public:
		Zoo();
		~Zoo();
		
		void add_animal(int, int);
		void add_sea_lion(int);
		void add_bear(int);
		void add_tiger(int);

		void remove_sea_lion(int);
		void remove_bear(int);
		void remove_tiger(int);

		void pick_random_event();
		void birth();
		void sick();
		void sea_lion_sick(Sea_lion&, int);
		void bear_sick(Bear&, int);
		void tiger_sick(Tiger&, int);
		void boom();
		
		void age_animals();
		void generate_revenue();
		void generate_new_food_cost();
		void subtract_food_cost();
		void display() const;

		double get_money() const;
		int get_months() const;
	
		void set_money(double);
		void set_months(int);

	private:
		Sea_lion *sea_lions;
		Bear *bears;
		Tiger *tigers;
		double money;	
		int months;
		int num_sea_lions;
		int num_bears;
		int num_tigers;
		int num_animals;
		int num_adults;
		int num_babies;
		int boost;
		int revenue;
		double base_food_cost;
		int probability_for_sick;
};
