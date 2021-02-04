/******************************
 * Program: Game.h
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: Declaration of the Game class
 *****************************/

#pragma once

#include <vector>
#include <string>

#include "Room.h"

class Game{
	public:
		Game();
		Game(int, bool); //size of grid, debug mode active
		
		void display_map();
		void display_debug_map();
		void display_percepts();
		bool run_game(); //The game loop
		int end_game(); //called if the player wins or loses
		void encounter();
		void add_event(Event *);
		void init_map();
		void move_wumpus();
		void shoot_arrow(char);
		void move_player(char);
		void user_input();
		bool valid_input(char);
		void reset(); 
	private:
		bool debug;
		bool got_gold, killed_wumpus;
		bool player_dead, player_win;
		int x_start_pos, y_start_pos;
		int x_curr_pos, y_curr_pos;
		int gold_x, gold_y;
		int wumpus_x_pos, wumpus_y_pos;
		int wumpus_x_start_pos, wumpus_y_start_pos;

		int size;

		std::vector<std::vector<Room>> map; //Game map
		
		int num_arrows;

};
