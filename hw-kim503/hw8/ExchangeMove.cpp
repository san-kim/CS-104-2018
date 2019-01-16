#include "Move.h"
#include "Exceptions.h"
using namespace std;

/* Creates an EXCHANGE move, exchanging the tiles listed in the
   string (formatted according to the EXCHANGE command description)
   with new tiles from the bag.
   */
ExchangeMove::ExchangeMove(string tileString, Player * p) : Move(p)
{
	//inherited from Move class
	exchange_tile_string = tileString;
}

ExchangeMove::~ExchangeMove() 
{

}

/* Executes this move, whichever type it is.
   This may throw exceptions; students: it's up to you to
   decide (and document) what exactly it throws*/
void ExchangeMove::execute(Board & board, Bag & bag, Dictionary & dictionary)
{	
	//if there are fewer tiles remaining in the bag than the player requests
	if(bag.tilesRemaining() < exchange_tile_string.size())
	{
		//THROW AN EXCEPTION? -- the player is trying to exchange more than is left in bag
		throw FileException("ERROR: " + _player->getName() + " cannot exchange more tiles than left in bag!");
	}

	else
	{
		//make sure that player has the tiles they want to remove
		if(_player->hasTiles(exchange_tile_string, false))
		{
			//false for exchange, instantiate discarded tiles
			vector<Tile*> discard = _player->takeTiles(exchange_tile_string, false);
			bag.addTiles(discard);
			//we want to draw the number of tiles we removed
			vector<Tile*> draw_tiles = bag.drawTiles(discard.size());
			//give the drawn tiles to player
			_player->addTiles(draw_tiles);
		}

		else
		{
			//THROW AN EXCEPTION -- doesnt have the tiles necessary to exchange
			throw FileException("ERROR: " + _player->getName() + " does not have necessary tiles to exchange!");
		}
	}
}

//Add more public/protected/private functions/variables here.