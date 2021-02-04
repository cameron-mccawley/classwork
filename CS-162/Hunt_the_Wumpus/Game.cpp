/******************************
 * Program: Game.cpp
 * Author: Cameron McCawley
 * Date: 11/15/2019
 * Description: Definitions for Game class function.
 *				Most game logic is done here.
 * Input: Size of game grid and bool for debug mode
 * Output: A bool for if the player is quitting
 *****************************/

#include "Game.h"
#include "Bats.h"
#include "Pit.h"
#include "Event.h"
#include "Room.h"
#include "Wumpus.h"
#include "Gold.h"
#include "util.h"

#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Game::Game(){

}

/* Parameterized Game constructor
 * Takes in the size of the grid and
 * whether or not debug mode should be activated
 */
Game::Game(int s, bool d){
	size = s;
	srand(time(NULL)); //seed random
	x_start_pos = rand() % size; //Get random start pos
	y_start_pos = rand() % size;
	x_curr_pos = x_start_pos;
	y_curr_pos = y_start_pos;
	got_gold = false;
	player_win = false;
	player_dead = false;
	num_arrows = 3;
	debug = d;
	killed_wumpus = false;
	for(int i = 0; i < size; i++){  //Initialize 2d vector of Rooms
		vector<Room> row;
		for(int j = 0; j < size; j++){
			Room room;
			row.push_back(room);
		}
		map.push_back(row);
	}
	
	init_map();

}


/* Initializes the game map with events and initializes
 * each Room object's flags accordingly
 */
void Game::init_map(){
	//This function should only be called when initializing a new Game map
	//Can add new events to the map easily
	map[x_start_pos][y_start_pos].set_has_player(true);
	add_event(new Pit);
	add_event(new Pit);
	add_event(new Bats);
	add_event(new Bats);
	add_event(new Gold);
	add_event(new Wumpus);
	wumpus_x_start_pos = wumpus_x_pos;
	wumpus_y_start_pos = wumpus_y_pos;
}

/* Takes in an Event pointer and will set a random
 * empty room to point to that event
 */
void Game::add_event(Event *e){
	int x, y;
	x = rand() % size; //get a random room
	y = rand() % size;

	//if room not empty or has the player, then pick a different room
	while((map[x][y].get_has_player()) || !map[x][y].get_is_empty()){ 
		x = rand() % size;
		y = rand() % size;
	}

	if(e->get_type() == 'g'){
		gold_x = x;
		gold_y = y;
	}else if(e->get_type() == 'w'){
		wumpus_x_pos = x;
		wumpus_y_pos = y;
	}
	map[x][y].set_event(e);
	map[x][y].set_is_empty(false);
}

/* Moves the wumpus to a different
 * random empty room
 */
void Game::move_wumpus(){
	int temp_x = wumpus_x_pos;
	int temp_y = wumpus_y_pos;
	add_event(new Wumpus);
	map[temp_x][temp_y].remove_event();
}

/* Displays the percepts for all of the
 * events adjacent to the player
 */
void Game::display_percepts(){
	//checks if rooms are valid and not out of bounds
	bool no_check = true;
	if(y_curr_pos != 0 && !map[x_curr_pos][y_curr_pos - 1].get_is_empty()){ //check room above
		cout << map[x_curr_pos][y_curr_pos - 1].get_event()->percept() << endl;
		no_check = false;
	}
	if(y_curr_pos != size - 1 && !map[x_curr_pos][y_curr_pos + 1].get_is_empty()){ //check room below
		cout << map[x_curr_pos][y_curr_pos + 1].get_event()->percept() << endl;
		no_check = false;
	}
	if(x_curr_pos != 0 && !map[x_curr_pos - 1][y_curr_pos].get_is_empty()){ //check check room left
		cout << map[x_curr_pos - 1][y_curr_pos].get_event()->percept() << endl;
		no_check = false;
	}
	if(x_curr_pos != size - 1 && !map[x_curr_pos + 1][y_curr_pos].get_is_empty()){ //check room right
		cout << map[x_curr_pos + 1][y_curr_pos].get_event()->percept() << endl;
		no_check = false;
	}
	if(no_check){ cout << endl; }
	cout << endl;
}

/* Displays the game map with no
 * information as to what is in each room
 * except for the player
 */
void Game::display_map(){
	for(int i = 0; i < size; i++){
		cout << "\n+";
		for(int j = 0; j < size; j++){
			cout << "---+";
		}
		cout << "\n|";
		for(int j = 0; j < size; j++){
			cout << " ";
			if(map[i][j].get_has_player()){
				cout << "*";
			}else{
				cout << " ";
			}
			cout << " |";
		}
	}
	cout << "\n+";
	for(int i = 0; i < size; i++){
		cout << "---+";
	}
	cout << endl;

}

/* Displays the game map but with information
 * as to what is in each room
 */
void Game::display_debug_map(){
	for(int i = 0; i < size; i++){
		cout << "\n+";
		for(int j = 0; j < size; j++){
			cout << "---+";
		}
		cout << "\n|";
		for(int j = 0; j < size; j++){
			cout << " ";
			//Check if room has Event, Escape rope, or Player
			if(!map[i][j].get_is_empty() || (map[i][j].get_has_player()) || (i == x_start_pos && j == y_start_pos)){
				if(map[i][j].get_has_player()){
					cout << "*";
				}
				if(i == x_start_pos && j == y_start_pos){
					cout << "r";
				}else if(!map[i][j].get_is_empty() && map[i][j].get_event()->get_type() == 'p'){
					cout << "p";
				}else if(!map[i][j].get_is_empty() && map[i][j].get_event()->get_type() == 'b'){
					cout << "b";
				}else if(!map[i][j].get_is_empty() && map[i][j].get_event()->get_type() == 'g'){
					cout << "g";
				}else if(!map[i][j].get_is_empty() && map[i][j].get_event()->get_type() == 'w'){
					cout << "w";
				}	

			}else{
				cout << " ";
			}
			cout << " |";
		}
	}
	cout << "\n+";
	for(int i = 0; i < size; i++){
		cout << "---+";
	}
	cout << endl;
}

/* Handles user input and deciding
 * what function to call depending on what
 * is entered by the user
 */
void Game::user_input(){
	char input;
	bool shooting = false;;
	input = getch(); //Waits for input, calls custom getch() function in util
	if(input == ' '){
		shooting = true;
		input = getch(); 
	}
	cout << "-----------------------------------------------------------" << endl;
	if(valid_input(input)){
		if(shooting){
			shoot_arrow(input);
		}else{
			move_player(input);
		}
	}else{
		cout << "Invalid input!" << endl;
	}
}

/* Takes in a char, and tests if it is a valid
 * input. Returns true if it is, false if not
 */
bool Game::valid_input(char input){
	if(input == 'w' || input == 'd' || input == 's' || input == 'a'){
		return true;
	}else{
		return false;
	}
}

/* Moves the player in the direction that is 
 * passed in.
 */
void Game::move_player(char dir){
	if(dir == 'w' && x_curr_pos != 0){ //Check there is no wall above player
		map[x_curr_pos][y_curr_pos].set_has_player(false);
		x_curr_pos -= 1;
		map[x_curr_pos][y_curr_pos].set_has_player(true);
	}else if(dir == 'd' && y_curr_pos != size - 1){ //check for wall to the right
		map[x_curr_pos][y_curr_pos].set_has_player(false);
		y_curr_pos += 1;
		map[x_curr_pos][y_curr_pos].set_has_player(true);
	}else if(dir == 's' && x_curr_pos != size - 1){ //Check for wall below
		map[x_curr_pos][y_curr_pos].set_has_player(false);
		x_curr_pos += 1;
		map[x_curr_pos][y_curr_pos].set_has_player(true);
	}else if(dir == 'a' && y_curr_pos != 0){ //Check for wall to the left
		map[x_curr_pos][y_curr_pos].set_has_player(false);
		y_curr_pos -= 1;
		map[x_curr_pos][y_curr_pos].set_has_player(true);
	}else{
		
	}
}

/* Shoots an arrow in the direction specified.
 * If the arrow comes in contact with the wumpus,
 * the wumpus dies. If the arrow goes three rooms 
 * without hitting anything or it hits a wall, the 
 * the wumpus has a 75% chance to wake up.
 */
void Game::shoot_arrow(char dir){
	if(num_arrows == 0){ //Cant shoot an arrow if they have no arrows
		cout << "Out of arrows!" << endl;
		return;
	}
	num_arrows -= 1;
	int arrow_x_pos = x_curr_pos;
	int arrow_y_pos = y_curr_pos;
	for(int i = 0; i < 3; i++){ //Check for three rooms
		
		if(dir == 'w' && arrow_x_pos - 1 >= 0){
			arrow_x_pos--;	
		}else if(dir == 'd' && arrow_y_pos + 1 <= (size - 1)){
			arrow_y_pos++;
		}else if(dir == 's' && arrow_x_pos + 1 <= (size - 1)){
			arrow_x_pos++;
		}else if(dir == 'a' && arrow_y_pos - 1 >= 0){
			arrow_y_pos--;
		}

		if(!map[arrow_x_pos][arrow_y_pos].get_is_empty() && map[arrow_x_pos][arrow_y_pos].get_event()->get_type() == 'w'){
			//Arrow and wumpus are in same room, so wumpus is dead
			cout << "You killed the wumpus!" << endl;
			killed_wumpus = true;
			map[arrow_x_pos][arrow_y_pos].remove_event();
			return;
		}	
	}
	//Arrow either missed or hit a wall, so calculate chance for wumpus to move
	cout << "Missed" << endl;
	int num = rand() % 4 + 1;
	if(num <= 3){ //75% chance
		cout << "Uh-oh! You woke up the wumpus.\nHe has moved to a different room." << endl;
		move_wumpus();
	}
}

/* Core game loop that runs until 
 * the the player decides to play a
 * new map or quit the game.  Returns true
 * for new game, false for quit
 */
bool Game::run_game(){
	
	while(true){
		
		if(debug){
			display_debug_map();
		}else{
			display_map();
		}
		if(player_win || player_dead){
			int choice = end_game();
			switch(choice){
				case 1: continue; //reset game
				case 2: return true; // play on new board
				case 3: return false; //end game
			}
		}
		display_percepts();
		user_input();
		cout << endl;
		encounter();
	}

}	

/* Called when the player wins or loses.
 * Prompts for one of three options and returns an
 * int corresponding to the option picked
 */
int Game::end_game(){
	char input;
	cout << "Would you like to:\n[1] Play again on same board\n[2] Play again on new board" << endl;
	cout << "[3] Quit the game" << endl;

	while(true){
		input = getch(); //Wait for input
		if(input != '1' && input != '2' && input != '3'){
			cout << "Error! Invalid input, please try again." << endl;
		}else{
			break;
		}
	}

	switch(atoi(&input)){ //This cant get called unless input is an integer
		case 1: reset();
			return 1;
		case 2: return 2;
		case 3: return 3;
	}

}

/* Logic for what happens when a player enters a room.
 * Checks if there is an encounter, if there is, the encounter will
 * be ran. Will also test to see if the player
 * has met the winning conditions
 */
void Game::encounter(){
	if(!map[x_curr_pos][y_curr_pos].get_is_empty()){ //Check that the room has an Event

		if(map[x_curr_pos][y_curr_pos].get_event()->get_type() == 'p'){ //Check for pit
			cout << "You fell into a pit!!!" << endl;
			player_dead = true;	
		}else if(map[x_curr_pos][y_curr_pos].get_event()->get_type() == 'b'){ //Check for Bats
			cout << "Ahhh bats!!!\nThey carry you into a random room." << endl;
			map[x_curr_pos][y_curr_pos].set_has_player(false);
			x_curr_pos = rand() % size; //Get random room
			y_curr_pos = rand() % size;
			map[x_curr_pos][y_curr_pos].set_has_player(true);
			encounter(); //Recursive call to encounter(). In case the new room has another event
		}else if(map[x_curr_pos][y_curr_pos].get_event()->get_type() == 'g'){ //check for Gold
			cout << "You found the gold!" << endl;
			got_gold = true;
			map[x_curr_pos][y_curr_pos].remove_event();
		}else if(map[x_curr_pos][y_curr_pos].get_event()->get_type() == 'w'){ //Check for wumpus
			cout << "You were eaten by the wumpus." << endl;
			player_dead = true;
		}

	}else if(got_gold && x_curr_pos == x_start_pos && y_curr_pos == y_start_pos){ //Check if win conditions have been met
		cout << "You made it out alive with the gold!\nCongrats!" << endl;
		player_win = true;
	}
}

/* Sets the game setting to the exact
 * setting that were played before.
 */
void Game::reset(){
	num_arrows = 3;
	got_gold = false;
	player_dead = false;
	killed_wumpus = false;
	player_win = false;
	map[x_curr_pos][y_curr_pos].set_has_player(false);
	x_curr_pos = x_start_pos;
	y_curr_pos = y_start_pos;
	map[x_curr_pos][y_curr_pos].set_has_player(true);
	map[wumpus_x_pos][wumpus_y_pos].remove_event();
	wumpus_x_pos = wumpus_x_start_pos;
	wumpus_y_pos = wumpus_y_start_pos;
	map[wumpus_x_pos][wumpus_y_pos].set_event(new Wumpus);
	map[wumpus_x_pos][wumpus_y_pos].set_is_empty(false);

	map[gold_x][gold_y].remove_event();	
	map[gold_x][gold_y].set_event(new Gold);
	map[gold_x][gold_y].set_is_empty(false);
}

