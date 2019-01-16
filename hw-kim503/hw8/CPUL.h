#ifndef CPUL_PLAYER_H_
#define CPUL_PLAYER_H_

#include "Trie.h"
#include "Move.h"
#include "Player.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Board.h"
#include "CPUS.h"
#include <vector>

class CPUL : public Player
{
public:
	//give CPU the board and all other info needed
	CPUL(std::string const & playername, unsigned int maxTiles, TrieSet* wordsTrie, Dictionary* dictionary, Board* board);
	~CPUL();
	std::vector< StartingSquare > startingSquares();
	void setAsFirstPlayOfGame();
	void undoFirstPlaySet();
	void updateHandSize();
	PlaceMove* chooseMove();

private:
	bool isFirstTurn;
	TrieSet* wordsTrie;
	Dictionary* dictionary;
	Board* board;
	std::string name;
	unsigned int maxTiles;
	void backtrack_squares_horizontal(TrieNode* currentNode, std::vector<Tile*> currentWord, unsigned int lettersPlaced, 
		unsigned int currentRow, unsigned int currentCol, unsigned int length, std::vector<Tile*>& tilesinHand, 
		std::vector<PlaceMove*>& wordsFormed, StartingSquare& start);
	void backtrack_squares_vertical(TrieNode* currentNode, std::vector<Tile*> currentWord, unsigned int lettersPlaced, 
		unsigned int currentRow, unsigned int currentCol, unsigned int length, std::vector<Tile*>& tilesinHand, 
		std::vector<PlaceMove*>& wordsFormed, StartingSquare& start);
};


#endif /* CPUL_PLAYER_H_ */
