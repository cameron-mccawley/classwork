/******************************
 * Program: util.h
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: function prototypes for 
 *				functions dealing with termios
 *****************************/
#pragma once
#include <termios.h>

static struct termios old, current;

void init_termios(void);
void reset_termios(void);
char getch(void);
