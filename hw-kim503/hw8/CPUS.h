#ifndef CPUS_PLAYER_H_
#define CPUS_PLAYER_H_

#include "Trie.h"
#include "Move.h"
#include "Player.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Board.h"
#include <vector>

struct StartingSquare
{
	bool isHorizontal;
	unsigned int col;
	unsigned int row;
	//the minimum and maximum length of the string that can be formed legally
	int maxLength;
	int minLength;
};

class CPUS : public Player
{
public:
	//give CPU the board and all other info needed
	CPUS(std::string const & playername, unsigned int maxTiles, TrieSet* wordsTrie, Dictionary* dictionary, Board* board);
	~CPUS();
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


#endif /* CPUS_PLAYER_H_ */
