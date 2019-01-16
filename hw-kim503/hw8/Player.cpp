#include "Player.h"

using namespace std;
/* Constructor giving the player the given name, and setting their points to 0.
	   Does not give the player any tiles.
	*/
Player::Player (string const & name, size_t maxTiles)
{
	points = 0;
	this->name = name;
	max_tiles = maxTiles;
}

/* Destructor for a player. Deletes all the tiles the player still has. */
Player::~Player ()
{
	set<Tile*>::iterator it;
	for(it = hand.begin(); it != hand.end(); ++it)
	{
		delete *it;
	}
}

/* Returns the set of tiles the player currently holds. */
set<Tile*> Player::getHandTiles() const
{
	return hand;
}

/* Reads a move string and confirms that the player has the tiles necessary to
   execute this move.

   The move string is case-insensitive.

   The boolean resolveBlanks states whether this is a PLACE or EXCHANGE move.
   If resolveBlanks is true, then when the string contains a '?',
   the next letter is interpreted as the letter to use the blank as.

   By definition, if this function returns true, then takeTiles() would
   succeed.
 */

bool Player::hasTiles(string const & move, bool resolveBlanks) const
{
	//so we can easily pop & check without worries
	vector<char> handtiles;

	//if PLACE
	if(resolveBlanks)
	{
		//instantiate handtiles, a copy of the characters in hand
		set<Tile*>::iterator it;
		for(it = hand.begin(); it != hand.end(); ++it)
		{
			//push back the letters of the hand only
			handtiles.push_back((*it)->getLetter());
		}

		//to check later whether all move characters are contained
		int originalHandSize = (int)handtiles.size();

		//iterate thru move string
		for(unsigned int i = 0; i < move.size(); i++)
		{
			vector<char>::iterator vit;
			//iterate thru handtiles letter copy of hand
			for(vit = handtiles.begin(); vit != handtiles.end(); ++vit)
			{
				//check whether move character is contained within hand copy
				if(toupper(move[i]) == toupper(*vit))
				{
					//erase that element
					handtiles.erase(vit);
					//if it is a ? then skip the next character of move
					if(move[i] == '?')
					{
						//skip next element
						i++;
					}
					//break inner forloop to not repeat erase 
					break;
				}
			}
		}
		//count number of ?'s
		int blankcounter = 0;
		for(unsigned int k = 0; k<move.size(); k++)
		{
			if(move[k] == '?')
				blankcounter++;
		}

		//at this point handtiles.size() should be = originalHandsize - (the move size-the number of ?)
		//if succeeded
		if(handtiles.size() > originalHandSize - (move.size() - blankcounter))
		{
			return false;
		}
		return true;
	}

	//if EXCHANGE
	else
	{
		//instantiate handtiles, a copy of the characters in hand
		set<Tile*>::iterator it;
		for(it = hand.begin(); it != hand.end(); ++it)
		{
			//push back the letters of the hand only
			handtiles.push_back((*it)->getLetter());
		}

		//to check later whether all move characters are contained
		int originalHandSize = (int)handtiles.size();

		//iterate thru move string
		for(unsigned int i = 0; i < move.size(); i++)
		{
			vector<char>::iterator vit;
			//iterate thru handtiles letter copy of hand
			for(vit = handtiles.begin(); vit != handtiles.end(); ++vit)
			{
				//check whether move character is contained within hand copy
				if(toupper(move[i]) == toupper(*vit))
				{
					//erase that element
					handtiles.erase(vit);
					//break inner forloop to not repeat erase 
					break;
				}
			}
		}

		//at this point handtiles.size() should be = originalHandsize - the move size
		//if succeeded
		if(handtiles.size() > originalHandSize - move.size() )
		{
			return false;
		}
		return true;
	}
}


/* Reads a move string, finds the corresponding tiles in the player's hand, and
   removes and returns those tiles in the order they appear in the move string.

   The move string is case-insensitive.

   The boolean resolveBlanks states whether this is a PLACE or EXCHANGE move.
   If resolveBlanks is true, then when the string contains a '?',
   the next letter is interpreted as the letter to use the blank as,
   and the "use" field of the tile is set accordingly.

   The move string is assumed to have correct syntax.
*/
vector<Tile*> Player::takeTiles (string const & move, bool resolveBlanks)
{
	//assume that move is the tilestring here

	//in the case of PLACE
	if(resolveBlanks)
	{
		vector<Tile*> removedTiles;
		for(unsigned int j = 0; j<move.size(); j++)
		{
			set<Tile*>::iterator it;
			for(it = hand.begin(); it != hand.end(); ++it)
			{
				//if the tile value equals a hand tile's char value
				if(toupper(move[j]) == toupper((*it)->getLetter()))
				{
					//push_back the tile ptr to removedTiles vector
					removedTiles.push_back(*it);
					//pop from hand
					hand.erase(it);
					//skip next one if the character found is '?'
					if(move[j] == '?')
					{
						j++;
					}
					//break this inner loop as to not incur repeat pops of one move character
					break;
				}
			}
		}
		return removedTiles;
	}

	//in the case of EXCHANGE
	else
	{
		vector<Tile*> removedTiles;
		for(unsigned int j = 0; j<move.size(); j++)
		{
			set<Tile*>::iterator it;
			for(it = hand.begin(); it != hand.end(); ++it)
			{
				//if the tile value equals a hand tile's char value
				if(toupper(move[j]) == toupper((*it)->getLetter()))
				{
					//push_back the tile ptr to removedTiles vector
					removedTiles.push_back(*it);
					//pop from hand
					hand.erase(it);
					//break this inner loop as to not incur repeat pops of one move character
					break;
				}
			}
		}
		return removedTiles;
	}
}

// Adds all the tiles in the vector to the player's hand.
void Player::addTiles (vector<Tile*> const & tilesToAdd)
{
	for(unsigned int i = 0; i < tilesToAdd.size(); i++)
	{
		hand.insert(tilesToAdd[i]);
	}
}	


//to set all blank tile values
void Player::setBlanks(string const & move)
{
	set<Tile*>::iterator it;
	for(unsigned int i = 0; i<move.size(); i++)
	{
		//when a blank is found
		if(move[i] == '?')
		{
			//assume input is correct, read what it should be
			char use_as_character = move[i+1];
			for(it = hand.begin(); it != hand.end(); ++it)
			{
				//find the first unchanged ?
				if((*it)->getLetter() == '?' && (*it)->getUse() == '?')
				{
					(*it)->useAs(use_as_character);
					break;
				}
			}
		}
	}
}

//to reset tile values of blanks in case of errors
void Player::errorResetBlanks()
{
	set<Tile*>::iterator it;
	for(it = hand.begin(); it != hand.end(); ++it)
	{
		//find all unchanged ?'s and change them back to '?'
		if((*it)->getLetter() == '?' && (*it)->getUse() != '?')
		{
			(*it)->useAs('?');
		}
	}
}


void Player::addPoints(int pointswon)
{
	points += pointswon;
}

int Player::getPoints()
{	
	return points;
}

string Player::getName()
{
	return name;
}

int Player::handPoints()
{
	int sum = 0;

	set<Tile*>::iterator it;
	for(it = hand.begin(); it != hand.end(); ++it)
	{
		sum += (*it)->getPoints();
	}
	return sum;
}

size_t Player::getMaxTiles() const
{
	return max_tiles;
}