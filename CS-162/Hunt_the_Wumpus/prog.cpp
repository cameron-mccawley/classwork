/******************************
 * Program: prog.cpp
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: This file contains the main function, 
 *				which runs the game.
 * Input: Two command line arguents, and int and a bool 
 *****************************/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include "util.h"
#include "Game.h"
using std::cout;
using std::endl;

/* main function of program.
 * Takes in two command line arguments, and int and a bool.
 * Program will exit early if the two command line argumets are not 
 * provided or if they are invalid.
 */
int main(int argc, char *argv[]){
	bool debug;
	bool play;
	if(argc != 3){
		std::cout << "Error! Must enter in exactly two arguments.\nNow exiting program..." << std::endl;
		return 0;
	}
	if(atoi(argv[1]) < 4){
		std::cout << "Error! Size must not be less than 4\nNow exiting program..." << std::endl;
		return 0;
	}
	if(argv[2] == std::string("true")){
		debug = true;
	}else if(argv[2] == std::string("false")){
		debug = false;
	}else{
		std::cout << "Error! Did not enter \'true\' or \'false\'.\nNow exiting program..." << std::endl;
		return 0;
	}
	
	while(true){
		Game* game = new Game(atoi(argv[1]), debug);
		play = game->run_game();
		delete game;
		if(!play){ //if they want to quit
			break;
		}
	}
	cout << "Goodbye!" << endl;
	return 0;
}

