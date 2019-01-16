#include "Move.h"
#include "Board.h"
#include "Exceptions.h"
#include <iostream>
using namespace std;
/* Creates a PLACE move, starting at row y, column x, placing the tiles
	   described by the string tileString. If "horizontal" is true, then the tiles
	   are placed horizontally, otherwise vertically.
	   Coordinates start with 1.
	   The string m is in the format described in HW4; in particular, a '?'
	   must be followed by the letter it is to be used as.
*/
PlaceMove::PlaceMove (size_t x, size_t y, bool horizontal, string tileString, Player * p) : Move(p)
{
	place_row = y;
	place_column = x;
	is_horizontal_place = horizontal;
	place_tilestring = tileString;
	//inherited from Move class
}

PlaceMove::~PlaceMove()
{

}

/* Returns the vector of tiles associated with a PLACE/EXCHANGE move.
   Return value could be arbitrary for PASS moves. */
std::vector<Tile*> PlaceMove::tileVector ()
{
	//a copy of the pointers, wouldn't matter if we popped from here
	set<Tile*> phand = _player->getHandTiles();
	//same exact method as in player's takeTiles without changing the hand
	vector<Tile*> result;

	for(unsigned int j = 0; j<place_tilestring.size(); j++)
	{
		set<Tile*>::iterator it;
		for(it = phand.begin(); it != phand.end(); ++it)
		{
			//if the tile value equals a phand tile's char value
			if(toupper(place_tilestring[j]) == toupper((*it)->getLetter()))
			{
				//push_back the tile ptr to result vector
				result.push_back(*it);
				//pop from phand
				phand.erase(it);
				//skip next one if the character found is '?'
				if(place_tilestring[j] == '?')
				{
					j++;
				}
				//break this inner loop as to not incur repeat pops of one move character
				break;
			}
		}
	}
	return result;
}

	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/
void PlaceMove::execute(Board & board, Bag & bag, Dictionary & dictionary)
{
	//count # of blanks
	int blank_count = 0;
	for(unsigned int p = 0; p<place_tilestring.size(); p++)
	{
		if(place_tilestring[p] == '?')
		{
			blank_count++;
		}
	}
	//numer of tiles without ? replacements
	size_t tiles_actually_played = place_tilestring.size() - blank_count;

	//make sure that player has the tiles they want to remove, accounts for ? replacements
	if(_player->hasTiles(place_tilestring, true))
	{
		//if the starting location was already occupied, throw error
		if(board.getSquare(place_column, place_row)->isOccupied())
		{
			//THROW ERROR, starting pos already occupied
			throw FileException("ERROR: " + _player->getName() + " cannot start placing tile over existing tile!");
		}
		//if it is not adjacent to any other tile
		bool isAdjacent = false;
		if(is_horizontal_place)
		{	//is okay if it is the first tile, let it pass
			for(unsigned int i = place_column; i<place_column + tiles_actually_played; i++)
			{	//if it is start and is not occupied must be first turn, let it pass this check
				if(board.getSquare(i, place_row)->isOccupied() == false && board.getSquare(i, place_row)->isStart())
					isAdjacent = true;
			}

			for(unsigned int i = place_column; i<place_column + tiles_actually_played; i++)
			{
				//when it comes across a tile already in place, means its automatically adjacent
				if(board.getSquare(i, place_row)->isOccupied())
					isAdjacent = true;
				//check if any of the row below it is occupied and thus adjacent
				if(place_row > 1)
				{
					if(board.getSquare(i, place_row-1)->isOccupied())
						isAdjacent = true;
				}
				//check if any of the row above it is occupied and thus adjacent
				if(place_row < board.getRows())
				{
					if(board.getSquare(i, place_row+1)->isOccupied())
						isAdjacent = true;
				}
			}
			if(place_column > 1)
			{	//check the square left of start
				if(board.getSquare(place_column-1, place_row)->isOccupied())
					isAdjacent = true;
			}
			if(place_column + tiles_actually_played - 1< board.getColumns())
			{	//check square right of end
				if(board.getSquare(place_column + tiles_actually_played, place_row)->isOccupied())
					isAdjacent = true;
			}

			if(!isAdjacent)
			{
				throw FileException("ERROR: " + _player->getName() + " must place tiles adjacent to others!");
			}
		}
		//if vertical
		if(!is_horizontal_place)
		{	//is okay if it is the first tile, let it pass
			for(unsigned int i = place_row; i<place_row + tiles_actually_played; i++)
			{	//if empty and is start, must mean it is first placemove of game
				if(board.getSquare(place_column,i)->isOccupied()==false && board.getSquare(place_column,i)->isStart())
					isAdjacent = true;
			}
			for(unsigned int i = place_row; i<place_row + tiles_actually_played; i++)
			{
				//when it comes across a tile already in place, means its automatically adjacent
				if(board.getSquare(place_column, i)->isOccupied())
					isAdjacent = true;
				//check if any of the column left it is occupied and thus adjacent
				if(place_column > 1)
				{
					if(board.getSquare(place_column-1, i)->isOccupied())
						isAdjacent = true;
				}
				//check if any of the column right it is occupied and thus adjacent
				if(place_column < board.getColumns())
				{
					if(board.getSquare(place_column+1, i)->isOccupied())
						isAdjacent = true;
				}
			}
			if(place_row > 1)
			{	//check if square directly above is occupied
				if(board.getSquare(place_column, place_row-1)->isOccupied())
					isAdjacent = true;
			}
			if(place_row + tiles_actually_played-1 < board.getRows())
			{	//check if square directly below is occupied
				if(board.getSquare(place_column, place_row + tiles_actually_played)->isOccupied())
					isAdjacent = true;
			}

			if(!isAdjacent)
			{
				throw FileException("ERROR: " + _player->getName() + " must place tiles adjacent to others!");
			}
		}

		//if horizontal and end is out of bounds
		if(is_horizontal_place)
		{
			int cross_counter = 0;
			for(unsigned int i = place_column; i<place_column + tiles_actually_played; i++)
			{
				//when it comes across a tile already in place
				if(board.getSquare(i+cross_counter, place_row)->isOccupied())
				{
					i--;
					cross_counter++;
				}
			}

			if((place_column + tiles_actually_played + cross_counter-1) > board.getColumns())
			{
				//THROW ERROR, out of bounds end
				throw FileException("ERROR: " + _player->getName() + " cannot go out of bounds horizontally!");
			}
		}
		//if vertical and end is out of bounds
		if(!is_horizontal_place)
		{
			int cross_counter = 0;
			for(unsigned int i = place_row; i<place_row+tiles_actually_played; i++)
			{
				if(board.getSquare(place_column, i+cross_counter)->isOccupied())
				{
					cross_counter++;
					i--;
				}
			}

			if((place_row + tiles_actually_played + cross_counter-1) > board.getRows())
			{
				//THROW ERROR, out of bounds end
				throw FileException("ERROR: " + _player->getName() + " cannot go out of bounds vertically!");
			}
		}
		//reset before we set just in case they are being used as something else, still in hand, so all should be unset
		_player->errorResetBlanks();
		//set the ?s to their replaced characters here, but reset later back to use = ? if fails
		_player->setBlanks(place_tilestring);
		//check all words formed by this move in board against dictionary
		vector< pair<string, unsigned int> > words_formed = board.getPlaceMoveResults(*this);

		bool allwordssuccess = true;
		unsigned int pointsEarned = 0;
		for(unsigned int k = 0; k<words_formed.size(); k++)
		{
			if(dictionary.isLegalWord(words_formed[k].first) == false)
			{
				allwordssuccess = false;
				break;
			}
			
			pointsEarned += words_formed[k].second;
		}

		if(allwordssuccess == false || words_formed.size() == 0)
		{
			_player->errorResetBlanks();
			//THROW ERROR, illegal word made
			throw FileException("ERROR: " + _player->getName() + " has made a word that doesn't exist!");
		}

		_player->addPoints(pointsEarned);

		//if successful place
		//put pieces on board
		board.executePlaceMove(*this);
		//true for place, remove the tiles from player's hand
		vector<Tile*> placedTiles = _player->takeTiles(place_tilestring, true);
		//draw tiles used
		vector<Tile*> draw_Tiles;
		//if not enough tiles to draw fully
		if(placedTiles.size() > bag.tilesRemaining())
			draw_Tiles = bag.drawTiles(bag.tilesRemaining());
		else
			draw_Tiles = bag.drawTiles(placedTiles.size());
		//give player the drawn tiles
		_player->addTiles(draw_Tiles);
	}

	else
	{	//THROW AN EXCEPTION, dont have the tiles they want to play
		throw FileException("ERROR: " + _player->getName() + " doesn't have those tiles to play!");
	}
}