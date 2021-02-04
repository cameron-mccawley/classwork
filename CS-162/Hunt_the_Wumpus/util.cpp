/******************************
 * Program: util.cpp
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: Defines functions needed for
 *				custom getch.
 *****************************/

#include "util.h"
#include <termios.h>
#include <cstdio>
#include <iostream>
using namespace std;

//init new terminal i/o settings
void init_termios(void){
	tcgetattr(0, &old); //grab old settings
	current = old; //set current to old as to not modify orginial settings
	current.c_lflag &= ~ICANON; //disable buffer IO

	current.c_lflag &= ~ECHO; //Disable Echo mode
	tcsetattr(0, TCSANOW, &current); //set the settings
}

/* Resests the serial interface attributes to the old setting
 */
void reset_termios(void){
	tcsetattr(0, TCSANOW, &old); //Set to old settings
}

/* Waits for user to enter a char and returns
 * the first char that is entered
 */
char getch(void){
	char ch;
	init_termios();
	ch = getchar();
	reset_termios();
	return ch;
}


