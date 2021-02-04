/******************************************************
* Program: util.cpp
* Author: Cameron McCawley
* Date: 12/06/2019
* Description:  Functions that help with running
*	the program
******************************************************/

#include "Node.hpp"
#include "Linked_List.hpp"
#include "util.h"
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

/******************************************************
* Function: get_type 
* Parameters: none
* Returns: int
* Description: Gets the type of data type that will
*	be used for the linked list
******************************************************/
int get_type(){
	string input;

	cout << "Which data type do you wish to use?" << endl;
	cout << "[1] Int\n[2] Unsigned Int" << endl;
	while(true){
		cin >> input;
		if(input == "1"){
			return 1;
		}else if(input == "2"){
			return 2;
		}else{
			cout << "Error! Not a valid option. Please try again: " << endl;
		}
	}	
}

/******************************************************
* Function: make_new_list
* Parameters: none
* Returns: bool
* Description: Returns true if the user would like to 
*	make a new linked list, false otherwise
******************************************************/
bool make_new_list(){
	string input;
	cout << "Would you like to make a new list? [y] or [n]" << endl;
	while(true){
		cin >> input;
		if(input == "y"){
			return true;
		}else if(input == "n"){
			return false;
		}else{
			cout << "Error! Not a valid option. Please try again: " << endl;
		}
	}	
}

/******************************************************
* Function: start
* Parameters: Linked_List<int>*
* Returns: void
* Description: Runs the main loop for a linked list of
*	ints
******************************************************/
void start(Linked_List<int>* list){
	int num;
	int choice;
	int index;
	while(true){
		cout << "Please enter an integer: " << endl;
		while(!(cin >> num)){
			cin.clear();
			cin.ignore(80, '\n');
			cout << "Error! Incompatable type, please try again: " << endl;
		}
		choice = get_choice();
		switch(choice){
			case 1: list->push_back(num);
				break;
			case 2: list->push_front(num);
				break;
			case 3:	cout << "Please enter index you wish to insert at: " << endl;
					while(!(cin >> index) || index < 0 || index > list->get_length()){
						cin.clear();
						cin.ignore(80, '\n');
						cout << "Error! Invalid input or OOB index, please try again: " << endl;
					}
					list->insert(num, index);
				break;
		}
		cout << "List: ";
		list->print();
		if(!add_to_list())
			break;	//break from main loop
	}
	
	if(ascending()){
		list->sort_ascending();
	}else{
		list->sort_descending();
	}
	cout << "Sorted List: ";
	list->print();
	cout << "You have " << list->get_num_primes() << " prime number(s) in your list." << endl;
}

/******************************************************
* Function: start
* Parameters: Linked_List<unsigned int>*
* Returns: void
* Description: runs the main loop for a linked list of
*	unsigned ints
******************************************************/
void start(Linked_List<unsigned int>* list){
	unsigned int num;
	int choice;
	int index;
	while(true){
		cout << "Please enter an unsigned integer: " << endl;
		while(!(cin >> num)){
			cin.clear();
			cin.ignore(80, '\n');
			cout << "Error! Incompatable type, please try again: " << endl;
		}
		choice = get_choice();
		switch(choice){
			case 1: list->push_back(num);
				break;
			case 2: list->push_front(num);
				break;
			case 3:	cout << "Please enter index you wish to insert at: " << endl;
					while(!(cin >> index) || index < 0 || index > list->get_length()){
						cin.clear();
						cin.ignore(80, '\n');
						cout << "Error! Invalid input or OOB index, please try again: " << endl;
					}
					list->insert(num, index);
				break; 
		}
		cout << "List: ";
		list->print();
		if(!add_to_list())
			break;	//break from main loop
	}
	if(ascending()){
		list->sort_ascending();
	}else{
		list->sort_descending();
	}
	cout << "Sorted List: ";
	list->print();
	cout << "You have " << list->get_num_primes() << " prime number(s) in your list." << endl;
}

/******************************************************
* Function: add_to_list
* Parameters: none
* Returns: bool
* Description: Prompts user if they want to add another
*	number to the linked list
******************************************************/
bool add_to_list(){
	string input;
	while(true){
		cout << "Would you like to add another number? [y] [n]" << endl;
		cin >> input;
		if(input == "y" || input == "yes"){
			return true;
		}else if(input == "n" || input == "no"){
			return false;
		}else{
			cout << "Invalid option. Please try again: " << endl;
		}
	}
}

/******************************************************
* Function: get_choice
* Parameters: none
* Returns: int
* Description: Prompts the user for how they want to add
*	their data to the linked list
******************************************************/
int get_choice(){
	int input;
	cout << "Would you like to\n[1] Append\n[2] Push\n[3] Insert" << endl;
	while(!(cin >> input) || (input < 1 || input > 3)){
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Error! Not a valid option. Please try again: " << endl;
	}
	return input;
}

/******************************************************
* Function: ascending
* Parameters: none
* Returns: bool
* Description: returns true if the user wishes to sort
*	the list in ascending order, and false otherwise
******************************************************/
bool ascending(){
	string input;
	while(true){
		cout << "Would you like to sort the list ascending or descending? [a] [d]" << endl;
		cin >> input;
		if(input == "a"){
			return true;
		}else if(input == "d"){
			return false;
		}else{
			cout << "Invalid option. Please try again: " << endl;
		}
	}
}

