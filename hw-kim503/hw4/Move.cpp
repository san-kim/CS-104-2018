#include "Move.h"
#include "Board.h"
#include <sstream>
#include <string>
using namespace std;

/* Parses the given move m, and constructs the corresponding move subclass.
	m is assumed to be in the format described on the assignment sheet for a move command.
	The player passed in is used to verify that the proposed tiles are
	in fact in the player's hand.
	It can handle all three types of move (PASS, EXCHANGE, PLACE).
	Coordinates start with 1.
*/

Move::Move(Player* player)
{
	_player = player; 
}

Move::~Move()
{
	
}

Move * Move::parseMove(string moveString, Player &p)
{
	stringstream ss(moveString);
	string command;
	ss >> command;

	if(command == "EXCHANGE")
	{
		string tilestring;
		ss >> tilestring;

		//make it all uppercase
		for(int i = 0; i<(int)tilestring.size(); i++)
		{
			tilestring[i] = toupper(tilestring[i]);
		}

		Move* result = new ExchangeMove(tilestring, &p);
		return result;
	}

	else if(command == "PLACE")
	{
		char direction;
		int row, col;
		string tilestring;
		ss >> direction >> row >> col >> tilestring;

		//make it all uppercase
		for(int i = 0; i<(int)tilestring.size(); i++)
		{
			tilestring[i] = toupper(tilestring[i]);
		}

		bool horizontal = false;
		if(direction == '-')
		{
			horizontal = true;
		}

		else if(direction == '|')
		{
			horizontal = false;
		}

		Move* result = new PlaceMove(col, row, horizontal, tilestring, &p);
		return result;
	}

	else if(command == "PASS")
	{
		Move* result = new PassMove(&p);
		return result;
	}

	return nullptr;
}