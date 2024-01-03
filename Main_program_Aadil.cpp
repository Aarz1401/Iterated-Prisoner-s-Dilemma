#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>

//Program to simulate IPD 
//Created by : Aadil Chasmawala 

# define MAX_moves 20 //We have 20 iterations in this game , 20 moves for each player
# define MAX_players 2 // We have Maximum of 2 players
using namespace std;
void printmenu();//Function to print menu
//We will use a char value for cooperate or defect
// c --> cooperate
// d --> defect
//Strategy implements the 4 strategies
class Strategy {
private:
	int strat_code; // 4 codes corresepond to 4 strategies
	string strat_name;//We have added strat_name as an attribute

public:
	Strategy() {
		strat_code = 1;
		strat_name = "Random";
	}
	Strategy(int s) {
		this->setStrat(s);//Uses same code as setStrat
	}
	~Strategy() {
		//No dynamic allocation is used 
	}

	//Accessors
	int getStratCode() {
		return strat_code;
	}
	string getStratName() {
		return strat_name;
	}

	//Modifiers , Only setStrat needed as strat_name is set Automatically
	void setStrat(int s) {
		if (s == 1 || s == 2 || s == 3 || s == 4) {
			strat_code = s;
			if (s == 1) {
				strat_name = "Random";
			}
			else if (s == 2) {
				strat_name = "Tit for Tat";
			}
			else if (s == 3) {
				strat_name = "Evil";
			}
			else if (s == 4) {
				strat_name = "Cooperate";
			}
		}
		else {
			cout << "Strategy for a player was invalid, it was set to default Strategy (Random)" << endl;
			strat_code = 1;
			strat_name = "Random";
		}
	}

	//The following function decides the next move of the player and return it
	char cooperateOrDefect(char last_move_opp) {
		//Strategy 1: Random
		
		if (strat_code == 1) {
			//srand is seeded in main
			int random_num = rand() % 2;
			if (random_num == 1) {
				return 'c';
			}
			else {
				return 'd';
			}
		}
		//Strategy 2 : Tit for Tat
		else if (strat_code == 2) {

			//return last move of opponent
			return (last_move_opp);
		}
		//Strategy 3: Evil
		else if (strat_code == 3) {
			return 'd';
		}
		//Strategy 4: Cooperate
		else if (strat_code == 4) {
			return 'c';
		}
		else {
			cout << "Strategy not defined" << endl;
		}
		
	}


};
//Defines the class player
class Player {
private:
	int ID;
	int score;
	char moves[MAX_moves];
	int num_moves;
	Strategy strategy;
	static int num_players;
	string name; //Added an attribute name to make the game more interactive

public:
	//Default Constructor
	Player() {
		ID = num_players;
		score = 0;
		moves[MAX_moves] = { '\0' }; 
		for (int i = 0; i < MAX_moves; i++)
			moves[i] = '\0';
		num_moves = 0;
		num_players++;
		name = "Player";
		Strategy s;//Default constructor of Strategy
		strategy = s;
	}
	//Custom Constructor for custom name and Strategy

	Player(string n, Strategy s) {
		ID = num_players;
		score = 0;
		moves[MAX_moves] = { '\0' }; 
		for (int i = 0; i < MAX_moves; i++)
			moves[i] = '\0';
		num_moves = 0;
		num_players++;
		strategy = s;
		name = n;

	}

	//Destructor
	~Player() {
		//No dynamic allocation so nothing in Destructor function
	}

	//Accessors
	int getID() {
		return ID;
	}
	int getscore() {
		return score;
	}

	char* getmoves() {
		return moves;
	}
	int getnum_moves() {
		return num_moves;
	}
	Strategy getStrategy() {
		return strategy;
	}
	static int getnum_players() {
		return num_players;
	}
	string getName() {
		return name;
	}

	//Modifiers
	//No need for ID and num_players as they are automatically generated and updated

	void setscore(int s) {
		score = s;
	}
	void setmoves(int m[]) {
		for (int i = 0; i < MAX_moves; i++)
			moves[i] = m[i];
	}
	void setStrategy(Strategy s) {
		strategy = s;
	}
	void setName(string n) {
		name = n;
	}
	
	void makemove(char opponent_last_move) {
		//Makes move of the current player and adds it to the array of moves based on opponents previous move
		// Case for beginning the program (when opponent last move is not defined) is handled in playgame() of Game class
		char move = strategy.cooperateOrDefect(opponent_last_move);
		setLastMove(move);//adds move to array of moves

	}
	void printmoves() {
		//can we use until it reaches the \0 character
		for (int i = 0; i < MAX_moves; i++) {
			cout << moves[i] << endl;
		}
	}
	void setLastMove(char c) {
		//add the move to the array of moves
		moves[num_moves] = c;
		num_moves++;

	}
	void updateStrategy(Strategy s) {
		strategy = s;
		//Update and Set strategy can be used interchangeably as for this program, we do not update the strategy midway through the iterations
		//Defining them differently is useful where you can change strategy midway 
	}
	//Function for displaying player ID and name information
	void displayInformation() {
		cout << "Player ID is :" << this->getID() << endl;
		cout << "Player Name is :" << this->getName() << endl;
		cout << "Player Strategy is :" << this->getStrategy().getStratName() << endl;
	}
};
int Player::num_players = 0;
class Game {
private:

	Player p_array[MAX_players];
	int n_players;//Represents number of players added to the game

public:
	//Default constructor
	Game() {
		n_players = 2;
		//The attribute definition calls the default constructor of Player

	}
	//Custom constructor given an array of player objects
	//Note: The below constructor would use a shallow copy if array of player objects would be passed , as such there would be duplicate 
	// player objects while using it
	// So, i have passed the Names and Strategies of the Player objects that would replace the one created by instantiation of the Player array 
	// attribute
	//Because of this I have not used the custom constructor anywhere as the default constructor works well
	//Note:This program does not need a Custom constructor for Game but I have added one anyway (maybe useful for extending the program:)
	Game(string names[MAX_players], int strat_code[MAX_players], int np) {
		// here np has to be less than MAX_players by definition
		n_players = 2;//Default that is changed if (if statement) is executed.
		if (np <= MAX_players) {
			for (int i = 0; i < np; i++) {
				p_array[i].setName(names[i]);
				p_array[i].getStrategy().setStrat(strat_code[i]);
			}
			n_players = np;
		}
		else {
			cout << "ERROR:Number of players has to be less than MAX_players :" << MAX_players << endl;
			

		}
	}

	//Accessors
	Player* getP_array() {
		return p_array;
	}
	int getNumPlayers() {
		return n_players;
	}

	//Modifiers not needed for p_array or num_players (both are modified by add/remove and constructor functions)
	//Function to add a player object to game
	void add_player(Player p) { 
		if (n_players == MAX_players) {
			cout << "The Maximum number of players have been added , To add a new player please remove existing player" << endl;
		}
		else {
			p_array[n_players] = p;
			cout << "The Player with the name " << p.getName() << " and ID " << p.getID() << " was successfully added" << endl;
			n_players++;
		}


	}
	//Function to remove a player object from game
	void remove_player(Player p) {
		int index_player_remove = -1;

		if (n_players == 0) {
			cout << "There are no players added. Please add a player first to remove a player." << endl;
		}
		else {
			// Search for the player
			for (int i = 0; i < n_players; i++) {
				if (p_array[i].getID() == p.getID()) {
					index_player_remove = i;
					break; // Exit loop once player is found
				}
			}

			// Check whether player was found
			if (index_player_remove == -1) {
				cout << "The player to be removed was not found." << endl;
			}
			else {
				// Remove the player by shifting elements
				for (int i = index_player_remove; i < n_players - 1; i++) {
					p_array[i] = p_array[i+1]; 
				}
				n_players--; // Decrement the number of players after removal
				cout << "The Player with the name " << p.getName() << " and ID " << p.getID() << " was successfully removed" << endl;
			}
		}
	}


	void setup() { //To add and remove players
		char option;
		bool option_3_not_select = true; //Boolean flag To exit loop if 3 is selected
		cout << setw(100) << setfill('_') << "_" << endl;
		cout << "                 SETUP                     " << endl;
		cout << setw(100) << setfill('_') << "_" << endl;


		while (option_3_not_select) {
			cout <<"Default game with 2 players has been created , you now have the following options :" << endl;
			cout << "You have the following options : " << endl;
			cout << "1.Add Player" << endl;
			cout << "2.Remove Player" << endl;
		    cout << "3.View information of players added " << endl;
			cout << "4.Exit Setup(Proceed with the default two players) and Run Game. " << endl;
			cout << setw(100) << setfill('_') << "_" << endl;
			cout << "Select your option(1,2,3 or 4) :" << endl;
			cin >> option;
			while (!(option == '1' || option == '2' || option == '3'|| option =='4')) {
				cout << "Option entered was not valid,Enter a valid option: " << endl;
				cin >> option;
			}
			//Code for adding a player
			if (option == '1') {
				if (n_players == MAX_players) {
					cout << "The Maximum number of players have been added , To add a new player please remove existing player" << endl;
				}
				else {
					string name;
					int strat;
					cout << "Enter name of the player:" << endl;
					cin >> name;
					cout << setw(100) << setfill('-') << "-" << endl;
					cout << "The strategies available are:" << endl;
					cout << setw(100) << setfill('-') << "-" << endl;
					cout << "1. Random  : The player Cooperates or Defects randomly" << endl;
					cout << "2. Tit for Tat :  The player makes the same move as his opponenet made on the last move" << endl;
					cout << "3. Evil : The player always defects " << endl;
					cout << "4. Cooperate : The player always cooperates" << endl;
					cout << "Enter Strategy of the player:" << endl;
					cin >> strat;
					Player p(name, strat);
					this->add_player(p); //(Add_player belongs to this game object and adds player to the same object)

				}



			}
			//Code for removing a player
			if (option == '2') {
				int ID;
				cout << "Enter ID of player to be removed" << endl;
				cin >> ID;
				bool player_found = false;
				for (int i = 0; i < n_players; i++) {
					if (p_array[i].getID() == ID) {
						player_found = true;
						this->remove_player(p_array[i]);//Removes the player
					}
				}
				if (player_found == false) {
					cout << "Player with the given ID could not be found, no players were removed .";
				}
				else {
					cout << "Player with given ID was removed successfully" << endl;
				}
			}
			
			//Code for displaying information
			if (option == '3') {
				cout << "The added Players are :" << endl;
				for (int i = 0; i < getNumPlayers(); i++) {
					cout << setw(100) << setfill('-') << "-" << endl;
					cout << "Player " << i+1 << endl;
					cout << setw(100) << setfill('-') << "-" << endl;
					p_array[i].displayInformation();
				}
			}
			cout << setw(100) << setfill('_') << "_" << endl;

			//Code for exiting loop and running game
			if (option == '4') {
				cout << "Setup Ended" << endl;
				option_3_not_select = false;
				cout << "Game Running....." << endl;

			}
		}


	}

	void play_game(Player& p1, Player& p2) {

		//Make initial random moves
		p1.setLastMove((rand() % 2 == 0) ? 'c' : 'd');
		p2.setLastMove((rand() % 2 == 0) ? 'c' : 'd');


		//Run game after initial moves
		for (int i = 1; i < MAX_moves; i++) {
			p1.makemove(p2.getmoves()[i - 1]); //Makes move based on the i-1 th value
			p2.makemove(p1.getmoves()[i - 1]);// Makes move based on the i-1 th value
		}


	}
	void calc_scores(Player& p1, Player& p2) {
		//Scoring system
		int score1(0), score2(0);
		for (int i = 0; i < MAX_moves; i++) {
			if (p1.getmoves()[i] == 'c' && p2.getmoves()[i] == 'c') {
				score1 += 3;
				score2 += 3;
			}
			if (p1.getmoves()[i] == 'c' && p2.getmoves()[i] == 'd') {
				score1 += 0;
				score2 += 5;
			}
			if (p1.getmoves()[i] == 'd' && p2.getmoves()[i] == 'c') {
				score1 += 5;
				score2 += 0;
			}
			if (p1.getmoves()[i] == 'd' && p2.getmoves()[i] == 'd') {
				score1 += 1;
				score2 += 1;
			}
			p1.setscore(score1);
			p2.setscore(score2);

		}

	}
	void report_results(Player p1, Player p2) {
		//print results after calculation
		cout << "The results are:" << endl;
		cout << setw(100) << setfill('_') << "_" << endl;
		cout << "Strategies of players are:" << endl;
		cout << "Player 1 : " << p1.getStrategy().getStratCode() << "." << p1.getStrategy().getStratName() << endl;
		cout << "Player 2 : " << p2.getStrategy().getStratCode() << "." << p2.getStrategy().getStratName() << endl;
		cout << setw(100) << setfill('_') << "_" << endl;
		cout << "Score of Player 1 (Name : " << p1.getName() << " ) and (ID :  " << p1.getID() << " ) is :" << endl;
		cout << p1.getscore() << endl;
		cout << setw(100) << setfill('_') << "_" << endl;
		cout << "Score of Player 2 (Name : " << p2.getName() << " ) and (ID :  " << p2.getID() << " )is :" << endl;
		cout << p2.getscore() << endl;
		cout << setw(100) << setfill('_') << "_" << endl;
		//Print winner message (or TIE)
		if (p1.getscore() > p2.getscore()) {
			cout << "Player 1 with name " << p1.getName() << " and ID " << p1.getID() << " Has won the game!!" << endl;

		}
		else if (p1.getscore() < p2.getscore()) {
			cout << "Player 2 with name " << p2.getName() << " and ID " << p2.getID() << " Has won the game!! " << endl;
		}
		else {
			cout << "ITS A TIE !!" << endl;
		}
		cout << setw(100) << setfill('_') << "_" << endl;

	}

};

int main() {
	printmenu();
	srand(static_cast<unsigned int>(std::time(nullptr))); //Seed the random number generator

	//Note: instantiating each player object seperately and then again instantiating array will create 4 player objects , we need only
	//2 player objects 
    Game g1;
	//Uses default constructor of Game which uses default constructor of Player(which in turn uses default constructor of Strategy).
	//This is done to avoid duplicating player objects while instantiating a Game object to make sure IDs are generated sequentially.
	int strat_1;
	int strat_2;
	cout << "Enter the Strategy for Player 1" << endl;
	cin >> strat_1;
	cout << "Enter the Strategy for Player 2" << endl;
	cin >> strat_2;
	//Set name and Strategy based on user input
	g1.getP_array()[0].setStrategy(strat_1);
	g1.getP_array()[0].setName("P1");
	g1.getP_array()[1].setStrategy(strat_2);
	g1.getP_array()[1].setName("P2");

	g1.setup();//Run setup to add/drop players
	bool setup_success = false;
	do {
		if (g1.getNumPlayers() == 2) {
			setup_success = true;
			cout << "Running the game between the 2 added players, the final outcome is :" << endl;
			g1.play_game(g1.getP_array()[0], g1.getP_array()[1]); 
			g1.calc_scores(g1.getP_array()[0], g1.getP_array()[1]);
			g1.report_results(g1.getP_array()[0], g1.getP_array()[1]);
		}
		else {
			cout << "There should be atleast two players to run the game , Please add a player and try again" << endl;
			g1.setup();
		}
	} while (setup_success == false);


	return 0;
}
void printmenu() {
	cout << setw(100) << setfill('_') << "_" << endl;
	cout << "ITERATED PRISONER'S DILEMMA" << endl;
	cout << setw(100) << setfill('_') << "_" << endl;
	cout << "We will be simulating the Iterated Prisoner's Dilemma for 2 players:" << endl;
	cout << " We will simulate it for " << MAX_moves << " iterations" << endl;
	cout << "The 2 default players are Player 1 and Player 2 (and they are named P1 and P2) " << endl; // Should we give String name as one of the attributes? :)
	cout << "The strategies available are:" << endl;
	cout << setw(100) << setfill('_') << "_" << endl;
	cout << "1. Random  : The player Cooperates or Defects randomly" << endl;
	cout << "2. Tit for Tat :  The player makes the same move as his opponenet made on the last move" << endl;
	cout << "3. Evil : The player always defects " << endl;
	cout << "4. Cooperate : The player always cooperates" << endl;
	cout << setw(100) << setfill('_') << "_" << endl;
}
