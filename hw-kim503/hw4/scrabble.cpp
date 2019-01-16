#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <sstream>
#include "Bag.h"
#include "Board.h"
#include "ConsolePrinter.h"
#include "Dictionary.h"
#include "Exceptions.h"
#include "Move.h"
#include "Player.h"
#include "Square.h"
#include "Tile.h"

using namespace std;

//helper prototypes
void read_configuration(ifstream& ifile, int* handsize, string* tiles_inputfile, 
	string* dictionary_inputfile, string* board_inputfile, uint32_t* seed);
bool coversStartingSquare(Board& gameBoard, PlaceMove* player_move);

int main(int argc, char* argv[])
{
	if(argc < 2)
		return 1;
	//read config file
	ifstream ifile(argv[1]);
	if(ifile.fail())	
		return 1;

	int handsize;
	string tiles_inputfile;
	string dictionary_inputfile;
	string board_inputfile;
	uint32_t seed;

	read_configuration(ifile, &handsize, &tiles_inputfile, &dictionary_inputfile, &board_inputfile, &seed);

	cout << "Enter the number of players: " << endl;
	int player_count;
	cin >> player_count;

	cout << "Enter the names of the " << player_count << " players, ONE name per line:" << endl;
	//to read the first line properly
	string consumeline;
	getline(cin,consumeline);
	
	Player* players[player_count];
	for(int i = 0; i<player_count; i++)
	{
		string playername;
		getline(cin, playername);
		players[i] = new Player(playername, handsize);
	}

	//make dictionary, called gameDictionary
	Dictionary gameDictionary(dictionary_inputfile);
	//make board, called gameBoard
	Board gameBoard(board_inputfile);
	//make the bag, called tileBag
	Bag tileBag(tiles_inputfile, seed);
	//instantiate a ConsolePrinter
	ConsolePrinter board_printer;

	//give each player handsize # of tiles
	for(int i = 0; i<player_count; i++)
	{
		vector<Tile*> initial_draw = tileBag.drawTiles(handsize);
		players[i]->addTiles(initial_draw);
	}

	int currentPlayer = 0;
	int consecutive_passes = 0;
	bool FIRSTPLACEMOVE = true;
	bool wincondition = false;
	while(!wincondition)
	{	//print board
		board_printer.printBoard(gameBoard);
		//print player's hand
		cout << "\nPlayer " << players[currentPlayer]->getName() << "'s hand: ";
		set<Tile*> p_hand = players[currentPlayer]->getHandTiles();
		set<Tile*>::iterator it;
		for(it = p_hand.begin(); it != p_hand.end(); ++it)
		{
			cout << (*it)->getLetter();
		}
		//print scores
		cout << endl;
		for(int i = 0; i<player_count; i++)
		{
			cout << players[i]->getName() << "'s points: " << players[i]->getPoints() << endl;
		}

		//query for move
		cout << endl << players[currentPlayer]->getName() << "'s turn, please input a move: " << endl;
		string moveline;
		getline(cin, moveline);

		//change everything to upper if not already
		for(unsigned int i = 0; i<moveline.size(); i++)
		{
			moveline[i] = toupper(moveline[i]);
		}

		//creates type of move constructor

		Move* player_move = Move::parseMove(moveline, *(players[currentPlayer]));

		if(player_move->isPass())
		{
			consecutive_passes++;
			//if all players pass, then end game
			if(consecutive_passes == player_count)
			{
				int max = players[0]->getPoints();
				for(int k = 0; k<player_count; k++)
				{
					if(players[k]->getPoints() > max)
					{	//find maximum points
						max = players[k]->getPoints();
					}
				}
				int numWinners = 0;
				for(int k = 0; k<player_count; k++)
				{
					if(players[k]->getPoints() == max)
					{	//find how many players w/ max points
						numWinners++;
					}
				}
				if(numWinners == 1)
				{
					cout << endl;
					cout << "Winner: ";
					for(int k = 0; k<player_count; k++)
					{
						if(players[k]->getPoints() == max)
						{	//find how many players w/ max points
							cout << players[k]->getName() << endl;
						}
					} 
				}
				if(numWinners > 1)
				{
					cout << endl;
					cout << "Winners:";
					for(int k = 0; k<player_count; k++)
					{
						if(players[k]->getPoints() == max)
						{
							cout << " " << players[k]->getName();
						}
					}
					cout << endl;
				}

				delete player_move;
				wincondition = true;
				break;
			}
		}
		else
		{
			consecutive_passes = 0;
		}

		if(player_move->isWord())
		{	//for first place move, must be on starting square
			if(FIRSTPLACEMOVE)
			{
				//while it would not cover the starting square, aka failure get new input
				while(!coversStartingSquare(gameBoard, (PlaceMove*)player_move))
				{
					string a = "'s turn did not cover starting square, please input another move:";
					cout << endl << "ERROR - " << players[currentPlayer]->getName() << a << endl;
					//read in a new move and parse
					string inpt;
					getline(cin, inpt);
					delete player_move;
					player_move = Move::parseMove(inpt, *(players[currentPlayer]));
					if(player_move->isPass())
					{
						consecutive_passes++;
					}
				}
				//if it is now a successful place word over the starting square
				if(player_move->isWord())
					FIRSTPLACEMOVE = false;
			}
		}


		//try catch for errors, in both exchange and place

		bool success = false;
		while(success == false)
		{
			try
			{
				player_move->execute(gameBoard, tileBag, gameDictionary);
				success = true;
				//will exit loop if succeeds
			}
			catch(FileException &e)
			{
				cout << endl << e.getMessage() << " Insert a different input:" << endl;
				//read in another input
				string inpt;
				getline(cin, inpt);
				delete player_move;
				player_move = Move::parseMove(inpt, *(players[currentPlayer]));
				if(player_move->isPass())
				{
					consecutive_passes++;
				}

				//check
				if(consecutive_passes >= player_count)
				{
					if(consecutive_passes == player_count)
					{
						int max = players[0]->getPoints();
						for(int k = 0; k<player_count; k++)
						{
							if(players[k]->getPoints() > max)
							{	//find maximum points
								max = players[k]->getPoints();
							}
						}
						int numWinners = 0;
						for(int k = 0; k<player_count; k++)
						{
							if(players[k]->getPoints() == max)
							{	//find how many players w/ max points
								numWinners++;
							}
						}
						if(numWinners == 1)
						{
							cout << endl;
							cout << "Winner: ";
							for(int k = 0; k<player_count; k++)
							{
								if(players[k]->getPoints() == max)
								{	//find how many players w/ max points
									cout << players[k]->getName() << endl;
								}
							} 
						}
						if(numWinners > 1)
						{
							cout << endl;
							cout << "Winners:";
							for(int k = 0; k<player_count; k++)
							{
								if(players[k]->getPoints() == max)
								{
									cout << " " << players[k]->getName();
								}
							}
							cout << endl;
						}
						wincondition = true;
						delete player_move;
						break;
					}
				}
			}
		}

		//execute move will have happened when succeeded
		//delete the used move
		delete player_move;
		//check win condition		
		if(tileBag.tilesRemaining() == 0)
		{	//currentPlayer is only one who can have 0 tiles here
			if((players[currentPlayer]->getHandTiles()).size() == 0)
			{
				for(int k = 0; k<player_count; k++)
				{	//add all other players scores to this person, subtract from others
					if(k != currentPlayer)
					{
						players[currentPlayer]->addPoints(players[k]->handPoints());
						players[k]->addPoints(-1 * players[k]->handPoints());
					}
				}
				int max = players[0]->getPoints();
				for(int k = 0; k<player_count; k++)
				{
					if(players[k]->getPoints() > max)
					{	//find maximum points
						max = players[k]->getPoints();
					}
				}
				int numWinners = 0; //check for ties
				for(int k = 0; k<player_count; k++)
				{
					if(players[k]->getPoints() == max)
					{	//find how many players w/ max points
						numWinners++;
					}
				}
				if(numWinners == 1)
				{
					cout << endl << "Winner: ";
					for(int k = 0; k<player_count; k++)
					{
						if(players[k]->getPoints() == max)
						{	//find how many players w/ max points
							cout << players[k]->getName() << endl;
						}
					}
				}
				if(numWinners > 1)
				{
					cout << endl << "Winners:";
					for(int k = 0; k<player_count; k++)
					{
						if(players[k]->getPoints() == max)
						{
							cout << " " << players[k]->getName() << endl;
						}
					}
				}
			}
			wincondition = true;
			break;
		}
		
		//will be range 0 to player_count-1
		currentPlayer = (currentPlayer+1) % player_count;
	}

	for(int i = 0; i<player_count; i++)
	{
		delete players[i];
	}
}


bool coversStartingSquare(Board& gameBoard, PlaceMove* player_move)
{
	bool coversStarting = false;
	int blank_count = 0;
	for(unsigned int p = 0; p < (player_move->place_tilestring).size(); p++)
	{
		if((player_move->place_tilestring)[p] == '?')
			blank_count++;
	}
	//numer of tiles without ? replacements
	size_t tiles_actually_played = (player_move->place_tilestring).size() - blank_count;
	if(player_move->is_horizontal_place)
	{	//must cover first square
		for(unsigned int i = player_move->place_column; i<player_move->place_column + tiles_actually_played; i++)
		{	//if it is start, aka legal start
			if(gameBoard.getSquare(i, player_move->place_row)->isStart())
				coversStarting = true;
		}
	}
	//if vertical
	else if(player_move->is_horizontal_place == false)
	{	//must cover first square
		for(unsigned int i = player_move->place_row; i<player_move->place_row + tiles_actually_played; i++)
		{	//if it is a starting square, aka legal
			if(gameBoard.getSquare(player_move->place_column, i)->isStart())
				coversStarting = true;
		}
	}
	return coversStarting;
}


//read configuration file
void read_configuration(ifstream& ifile, int* handsize, string* tiles_inputfile, 
	string* dictionary_inputfile, string* board_inputfile, uint32_t* seed)
{
	string config_word;
	while(ifile >> config_word)
	{
		if(config_word == "HANDSIZE:")
		{
			string line;
			getline(ifile, line);
			stringstream ss(line);
			//consume all whitespace
			ss >> *handsize;
			//will read until it finds an int or reaches end
			while(ifile.fail())
			{
				ss >> *handsize;
			}
		}

		else if(config_word == "TILES:")
		{
			string line;
			getline(ifile, line);
			stringstream ss(line);
			char wspace = '\n';
			//consume all whitespace
			while(isspace(wspace))
			{
				ss >> wspace;
			}
			ss >> *tiles_inputfile;
			//the last wspace would be the first char of the string so concatenate
			*tiles_inputfile = wspace + *tiles_inputfile;
		}

		else if(config_word == "DICTIONARY:")
		{
			string line;
			getline(ifile, line);
			stringstream ss(line);
			char wspace = '\n';
			//consume all whitespace
			while(isspace(wspace))
			{
				ss >> wspace;
			}
			ss >> *dictionary_inputfile;
			//the last wspace would be the first char of the string so concatenate
			*dictionary_inputfile = wspace + *dictionary_inputfile;
		}

		else if(config_word == "BOARD:")
		{
 			string line;
			getline(ifile, line);
			stringstream ss(line);
			char wspace = '\n';
			//consume all whitespace
			while(isspace(wspace))
			{
				ss >> wspace;
			}
			ss >> *board_inputfile;
			//the last wspace would be the first char of the string so concatenate
			*board_inputfile = wspace + *board_inputfile;
		}

		else if(config_word == "SEED:")
		{
			string line;
			getline(ifile, line);
			stringstream ss(line);
			//consume all whitespace
			ss >> *seed;
			//will read until it finds an int or reaches end
			while(ifile.fail())
			{
				ss >> *seed;
			}
		}
	}
}