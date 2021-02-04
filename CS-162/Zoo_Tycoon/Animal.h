/************************************
* Program: Animal.h
* Author: Cameron McCawley
* Date: 10/31/19
* Description: Animal Class
*************************************/
#pragma once

class Animal{

	public:
		Animal();
		Animal(int);
		~Animal();		
		void age_animal();

		int get_age() const;
		int get_num_babies() const;
		int get_cost() const;
		int get_babies_per_birth() const;
		int get_food_mult() const;
		int get_age_in_years() const;

		void set_age(int);
		void set_num_babies(int);
		void set_cost(int);
		void set_babies_per_birth(int);
		void set_food_mult(int);

	protected:
		int age;
		int num_babies;
		int babies_per_birth;
		int cost;
		int food_mult;
};
