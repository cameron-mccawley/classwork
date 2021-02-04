/******************************************************
* Program: prog.cpp
* Author: Cameron McCawley
* Date: 12/06/2019
* Description: Main driver file 
******************************************************/

#include "Node.hpp"
#include "Linked_List.hpp"
#include "util.h"
#include <cstdlib>
#include <ctime>

namespace type{
	const int INT = 1;
	const int UNSIGNED_INT = 2;
}

/******************************************************
* Function: main
* Returns: int
* Description: Runs the program
******************************************************/
int main(){
	srand(time(0));
	while(true){
		int type = get_type();
		if(type == type::INT){
			Linked_List<int>* list = new Linked_List<int>();
			start(list);
			delete list;
			if(!make_new_list()) 
				return 0;
	
		}else if(type == type::UNSIGNED_INT){
			Linked_List<unsigned int>* list = new Linked_List<unsigned int>();
			start(list);
			delete list;
			if(!make_new_list()) 
				return 0;
		}
	}
}
