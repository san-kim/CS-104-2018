#include "CPUS.h"
#include "Player.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Board.h"
#include "Move.h"
#include "Trie.h"
#include <set>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//constructor
CPUS::CPUS(string const & playername, unsigned int maxTiles, TrieSet* wordsTrie, Dictionary* dictionary, Board* board) 
	: Player(playername, maxTiles)
{
	this->maxTiles = maxTiles;
	this->isFirstTurn = false;
	this->wordsTrie = wordsTrie;
	this->dictionary = dictionary;
	this->board = board;
}

//destructor
CPUS::~CPUS()
{

}

void CPUS::updateHandSize()
{
	set<Tile*> playerhand_ =  this->getHandTiles();
	this->maxTiles = playerhand_.size();
}

void CPUS::setAsFirstPlayOfGame()
{
	isFirstTurn = true;
}

void CPUS::undoFirstPlaySet()
{
	isFirstTurn = false;
}

//if we find a tile, check top left right bottom, if any of them are blank, try to go as far left or top 
//until you are maxhandtiles number of blanks away from that tile or as far out as possible (if it is in bounds)

//return a set of starting square indeces if indeces were 1 to size
//each StartingSquare comes with: x, y coordinates, minimum maximum length the string can be given that square
//and whether or not this is a vertical square or a horizontal square (accounts for overlaps)
vector<StartingSquare> CPUS::startingSquares()
{
	vector<StartingSquare> starts;

	//check if it's an empty board, if it is, then start at starting square
	bool isEmptyBoard = true;;
	for(unsigned int i = 1; i <= board->getRows(); i++)
	{
		for(unsigned int j = 1; j<= board->getColumns(); j++)
		{
			if(board->isOccupiedSquare(i,j))
				isEmptyBoard = false;
		}
	}

	//if and only it's the very fist turn and must cover the starting square or if empty board
	if(isFirstTurn || isEmptyBoard == true)
	{
		StartingSquare s;
		s.isHorizontal = true;
		//edge case if it is larger than the width
		if(maxTiles > board->getColumns())
		{
			s.col = 1;
			s.row = board->getStarting_y();
			s.maxLength = board->getColumns();
			s.minLength = 1;
		}
		else
		{
			//otherwise just center it
			s.col = board->getStarting_x();
			s.row = board->getStarting_y();



			//this is where it seg faults
			//s.maxLength = maxTiles;
			s.maxLength = board->getColumns() - board->getStarting_x();



		}
		s.minLength = 1;
		starts.push_back(s);
		isFirstTurn = false;
		return starts;
	}

	//traverse through the board until we find a placed tile
	for(unsigned int i = 1; i <= board->getRows(); i++)
	{
		for(unsigned int j = 1; j<= board->getColumns(); j++)
		{
			//if we find an occupied square
			if(board->isOccupiedSquare(i,j))
			{
				unsigned int blanksleft = 0;
				unsigned int blanksright = 0;
				unsigned int blankstop = 0;
				unsigned int blanksbottom = 0;

				vector<int> leftblankindeces;
				vector<int> topblankindeces;

				//check that it isn't part of a string of letters left, we can ignore these permutations
				bool horizontalsandwich = false;
				if(j-1 >= 1 && j+1 <= board->getColumns())
				{	//if both occupied, no need to repeat check
					if(board->isOccupiedSquare(i,j-1) && board->isOccupiedSquare(i, j+1))
					{
						blanksleft = 0;
						horizontalsandwich = true;
					}
				}

				if(!horizontalsandwich) //otherwise, then there's a blank to the left of it
				{
					//find how many blanks to LEFT
					unsigned int left_column_index = j;
					while(blanksleft <= maxTiles)
					{
						left_column_index--;
						if(left_column_index == 0)
							break;
						//if its a blank tile
						if(board->isOccupiedSquare(i,left_column_index) == false)
						{
							if(blanksleft < maxTiles)
							{
								leftblankindeces.push_back(left_column_index);
								blanksleft++;
							}
							else 
								break;
						}
					}
				}

				if(!horizontalsandwich || board->isOccupiedSquare(i,j-1) == false )//otherwise, then there's a blank to the right of it
				{
					//find how many blanks to RIGHT
					unsigned int right_column_index = j;
					while(blanksright <= maxTiles)
					{
						right_column_index++;
						if(right_column_index == board->getColumns()+1)
							break;
						//if its a blank tile
						if(board->isOccupiedSquare(i,right_column_index) == false)
						{
							if(blanksright < maxTiles)
								blanksright++;
							else
								break;
						}
					}
				}

				//find how many blanks ABOVE
				bool verticalsandwich = false;
				if(i-1 >= 1 && i+1 <= board->getRows())
				{
					if(board->isOccupiedSquare(i-1,j) && board->isOccupiedSquare(i+1,j))
					{
						blankstop = 0;
						verticalsandwich = true;
					}
				}
				if(!verticalsandwich) //otherwise, then there's a blank above of it
				{
					unsigned int top_row_index = i;
					while(blankstop <= maxTiles)
					{
						top_row_index--;
						if(top_row_index == 0)
							break;
						//if its a blank tile
						if(board->isOccupiedSquare(top_row_index,j) == false)
						{
							if(blankstop < maxTiles)
							{
								topblankindeces.push_back(top_row_index);
								blankstop++;
							}
							else 
								break;
						}
					}
				}
				
				if(!verticalsandwich || board->isOccupiedSquare(i-1,j) == false )
				{
					unsigned int bottom_row_index = i;
					while(blanksbottom <= maxTiles)
					{
						bottom_row_index++;
						if(bottom_row_index == board->getRows()+1)
							break;
						//if its a blank tile
						if(board->isOccupiedSquare(bottom_row_index,j) == false)
						{
							if(blanksbottom < maxTiles)
								blanksbottom++;
							else 
								break;
						}
					}
				}

				
				//now that we have the blanks L,R,U,D on each tile, establish starting squares

				//if the number of blanks on the right is more than the maxTiles and not full edge case 
				if(blanksright > 0 && board->isOccupiedSquare(i,j+1) != true)
				{
					StartingSquare s;
					s.isHorizontal = true;
					s.col = j+1;
					s.row = i;
					s.minLength = 1;
					s.maxLength = blanksright;
					starts.push_back(s);
				}

				//if the number of blanks on the left is more than the maxTiles and not full edge case 
				if(blanksleft > 0)
				{
					for(unsigned int k = 0; k<leftblankindeces.size(); k++)
					{
						StartingSquare s;
						s.isHorizontal = true;
						s.col = leftblankindeces[k];
						s.row = i;
						s.maxLength = min(maxTiles, k+1+blanksright);
						//if we do not have enough blanks on the right to fully do maxTiles length string
						if(maxTiles-k-1 > blanksright)
							s.maxLength = blanksright + k + 1;
						s.minLength = k+1;
						starts.push_back(s);
					}
				}


				//if the number of blanks on the bottom is more than the maxTiles and not full edge case 
				if(blanksbottom > 0 && board->isOccupiedSquare(i+1,j) != true)
				{
					StartingSquare s;
					s.isHorizontal = false;
					s.col = j;
					s.row = i+1;
					s.minLength = 1;
					s.maxLength = blanksbottom;
					starts.push_back(s);
				}

				
				//if the number of blanks on the left is more than the maxTiles and not full edge case 
				if(blankstop > 0)
				{
					for(unsigned int k = 0; k<topblankindeces.size(); k++)
					{
						StartingSquare s;
						s.isHorizontal = false;
						s.col = j;
						s.row = topblankindeces[k];
						s.maxLength = min(k+blanksbottom+1, maxTiles);
						//if we do not have enough blanks on the right to fully do maxTiles length string
						if(maxTiles-k-1 > blanksbottom)
							s.maxLength = blanksbottom + k + 1;
						s.minLength = k+1;
						starts.push_back(s);
					}
				}
			}
		}
	}
	return starts;
}



//given a starting square, backtrack
void CPUS::backtrack_squares_horizontal(TrieNode* currentNode, vector<Tile*> currentWord, unsigned int lettersPlaced, unsigned int currentRow, 
unsigned int currentCol, unsigned int targetlength, vector<Tile*>& tilesinHand, vector<PlaceMove*>& wordsFormed, StartingSquare& start)
{
	//for horizontal
	//base case, either success or failure, should only backtrack up till this amount
	if(lettersPlaced == targetlength)
	{
		//CHECK everything to the RIGHT of it if there are any more tiles
		while(currentCol <= board->getColumns())
		{	//check whether right square is occupied
			if(board->isOccupiedSquare(currentRow, currentCol) == true)
			{
				char childLetter = board->getSquare(currentCol,currentRow)->getLetter();
				//FAIL case where next letter is not in word
				if(wordsTrie->getChildNode(currentNode, childLetter) == NULL)
				{
					return;
				}
				//otherwise go to next node
				currentNode = wordsTrie->getChildNode(currentNode, childLetter);
				currentWord.push_back(board->getSquare(currentCol,currentRow)->getTile());
				currentCol++;
			}
			//otherwise, stop checking if right square is not connected
			else
				break;
		}

		//check inset, if it is inSet == true, it is a word and success, otherwise go back
		if(currentNode->inSet == true)
		{
			//concatenate result including ? case
			string result = "";
			for(unsigned int i = 0; i<currentWord.size(); i++)
			{	//only if that square is not occupied, we add that letter to our result string
				if(board->isOccupiedSquare(start.row, start.col+i) != true)
				{
					result = result + currentWord[i]->getLetter();
					if(currentWord[i]->getLetter() == '?')
					{
						result = result + currentWord[i]->getUse();
					}
				}
			}

			PlaceMove* madeMove = new PlaceMove(start.col, start.row, start.isHorizontal, result, &(*this));
			wordsFormed.push_back(madeMove);
		}
		return;
	}

	else
	{	
		//CONSIDER TILES IN BETWEEN ALREADY THERE 
		while(currentCol <= board->getColumns())
		{	//check whether right square is occupied
			if(board->isOccupiedSquare(currentRow, currentCol) == true)
			{
				char childLetter = board->getSquare(currentCol,currentRow)->getLetter();
				//FAIL case where next letter is not in word
				if(wordsTrie->getChildNode(currentNode, childLetter) == NULL)
				{
					return;
				}
				//otherwise go to next node
				currentNode = wordsTrie->getChildNode(currentNode, childLetter);
				currentWord.push_back(board->getSquare(currentCol,currentRow)->getTile());
				currentCol++;
			}
			//otherwise, stop checking if right square is not connected
			else
				break;
		}

		//now for the backtracking portion
		unsigned int loopsize = tilesinHand.size();
		for(unsigned int i = 0; i < loopsize; i++) 
		{
			//only do front ones so we go through all of them once
			Tile* addTile = *(tilesinHand.begin());
			tilesinHand.erase(tilesinHand.begin());

			//if it has a ? then try among the 26 pos, all the children that exist
			if(addTile->getLetter() == '?')
			{
				int counter = 0;
				for(int j = 0; j<26; j++)
				{
					//only add the children that are in trie for efficiency
					if(currentNode->children[j] != NULL)
					{
						counter++;

						addTile->useAs((char)(j + 'a'));
						TrieNode* nextChild = currentNode->children[j];
						currentWord.push_back(addTile);

						backtrack_squares_horizontal(nextChild, currentWord, lettersPlaced+1, currentRow, currentCol+1, 
													 targetlength, tilesinHand, wordsFormed, start);
						//reset what the letter is
						currentWord.erase(currentWord.begin() + (currentWord.size()-1));
						addTile->useAs('?');
					}
				}
				//if there were no down this path, failed as ? is all possible letters
				if(counter == 0)
				{
					tilesinHand.push_back(addTile);
					return;
				}

				//reset
				tilesinHand.push_back(addTile);
			}
			//if it is not a ?, but an already designated letter
			else
			{
				TrieNode* nextChild = wordsTrie->getChildNode(currentNode, addTile->getUse());
				//if this prefix does not exist, move on
				if(nextChild == NULL)
				{
					tilesinHand.push_back(addTile);
					return;
				}
				//otherwise go deeper
				currentWord.push_back(addTile);
				
				backtrack_squares_horizontal(nextChild, currentWord, lettersPlaced+1, currentRow, currentCol+1, 
											 targetlength, tilesinHand, wordsFormed, start);
				//reset
				currentWord.erase(currentWord.begin() + (currentWord.size()-1));
				tilesinHand.push_back(addTile);
			}
		}
	}
}

//given a starting square, backtrack
void CPUS::backtrack_squares_vertical(TrieNode* currentNode, vector<Tile*> currentWord, unsigned int lettersPlaced, unsigned int currentRow, 
unsigned int currentCol, unsigned int targetlength, vector<Tile*>& tilesinHand, vector<PlaceMove*>& wordsFormed, StartingSquare& start)
{
	//for vertical
	//base case, either success or failure, should only backtrack up till this amount
	if(lettersPlaced == targetlength)
	{
		//CHECK everything to the RIGHT of it if there are any more tiles
		while(currentRow <= board->getRows())
		{	//check whether right square is occupied
			if(board->isOccupiedSquare(currentRow, currentCol) == true)
			{
				char childLetter = board->getSquare(currentCol,currentRow)->getLetter();
				//FAIL case where next letter is not in word
				if(wordsTrie->getChildNode(currentNode, childLetter) == NULL)
				{
					return;
				}
				//otherwise go to next node down
				currentNode = wordsTrie->getChildNode(currentNode, childLetter);
				currentWord.push_back(board->getSquare(currentCol,currentRow)->getTile());
				currentRow++;
			}
			//otherwise, stop checking if right square is not connected
			else
				break;
		}

		//check inset, if it is inSet == true, it is a word and success, otherwise go back
		if(currentNode->inSet == true)
		{
			//concatenate result including ? case
			string result = "";
			for(unsigned int i = 0; i<currentWord.size(); i++)
			{	//only if that square is not occupied, we add that letter to our result string
				if(board->isOccupiedSquare(start.row+i, start.col) != true)
				{
					result = result + currentWord[i]->getLetter();
					if(currentWord[i]->getLetter() == '?')
					{
						result = result + currentWord[i]->getUse();
					}
				}
			}

			PlaceMove* madeMove = new PlaceMove(start.col, start.row, start.isHorizontal, result, &(*this));
			wordsFormed.push_back(madeMove);
		}
		return;
	}

	else
	{	
		//CONSIDER TILES IN BETWEEN ALREADY THERE 
		while(currentRow <= board->getRows())
		{	//check whether right square is occupied
			if(board->isOccupiedSquare(currentRow, currentCol) == true)
			{
				char childLetter = board->getSquare(currentCol,currentRow)->getLetter();
				//FAIL case where next letter is not in word
				if(wordsTrie->getChildNode(currentNode, childLetter) == NULL)
				{
					return;
				}
				//otherwise go to next node
				currentNode = wordsTrie->getChildNode(currentNode, childLetter);
				currentWord.push_back(board->getSquare(currentCol,currentRow)->getTile());
				currentRow++;
			}
			//otherwise, stop checking if right square is not connected
			else
				break;
		}

		//now for the backtracking portion
		unsigned int loopsize = tilesinHand.size();
		for(unsigned int i = 0; i < loopsize; i++) 
		{
			//only do front ones so we go through all of them once
			Tile* addTile = *(tilesinHand.begin());
			tilesinHand.erase(tilesinHand.begin());

			//if it has a ? then try among the 26 pos, all the children that exist
			if(addTile->getLetter() == '?')
			{
				int counter = 0;
				for(int j = 0; j<26; j++)
				{
					//only add the children that are in trie for efficiency
					if(currentNode->children[j] != NULL)
					{
						counter++;

						addTile->useAs((char)(j + 'a'));
						TrieNode* nextChild = currentNode->children[j];
						currentWord.push_back(addTile);

						backtrack_squares_vertical(nextChild, currentWord, lettersPlaced+1, currentRow+1, currentCol, 
												   targetlength, tilesinHand, wordsFormed, start);
						//reset what the letter is
						currentWord.erase(currentWord.begin() + (currentWord.size()-1));
						addTile->useAs('?');
					}
				}
				//if there were no down this path, failed as ? is all possible letters
				if(counter == 0)
				{
					tilesinHand.push_back(addTile);
					return;
				}

				//reset
				tilesinHand.push_back(addTile);
			}
			//if it is not a ?, but an already designated letter
			else
			{
				TrieNode* nextChild = wordsTrie->getChildNode(currentNode, addTile->getUse());
				//if this prefix does not exist, move on
				if(nextChild == NULL)
				{
					tilesinHand.push_back(addTile);
					return;
				}
				//otherwise go deeper
				currentWord.push_back(addTile);
				
				backtrack_squares_vertical(nextChild, currentWord, lettersPlaced+1, currentRow+1, currentCol, 
										   targetlength, tilesinHand, wordsFormed, start);
				//reset
				currentWord.erase(currentWord.begin() + (currentWord.size()-1));
				tilesinHand.push_back(addTile);
			}
		}
	}
}


//this function checks all words formed and chooses highest scoring, returns NULL if it cannot form a word/should be PASSMOVE
PlaceMove* CPUS::chooseMove()
{
	//find all starting squares
	vector<StartingSquare> start_squares = this->startingSquares();

	//our resulting PlaceMoves that make words, but not necessarily fully checked by board's getPlaceMoveResults()
	vector<PlaceMove*> result_PlaceMoves; 

	//tiles in hand in a vector form
	vector<Tile*> tilesinHand;
	set<Tile*> playerHand = this->getHandTiles();
	set<Tile*>::iterator iter;
	for(iter = playerHand.begin(); iter != playerHand.end(); ++iter)
	{
		tilesinHand.push_back(*iter);
	}



	//do backtracking search on all starting squares
	for(unsigned int i = 0; i<start_squares.size(); i++)
	{	

		//populate result_PlaceMoves with all possible permutations of words
		//backtrack for each specific length of the starting square
		for(int targetlength = start_squares[i].minLength; targetlength <= start_squares[i].maxLength; targetlength++)
		{	//empty working currentWord vector
			vector<Tile*> currentWord;
			unsigned int zero = 0;
			if(start_squares[i].isHorizontal)
			{
				backtrack_squares_horizontal(wordsTrie->getRootNode(), currentWord, zero, start_squares[i].row, 
				start_squares[i].col, targetlength, tilesinHand, result_PlaceMoves, start_squares[i]);
			}

			else
			{
				backtrack_squares_vertical(wordsTrie->getRootNode(), currentWord, zero, start_squares[i].row, 
				start_squares[i].col, targetlength, tilesinHand, result_PlaceMoves, start_squares[i]);
			}
		}
	}

	//make sure that it checks out with getPlaceMoveResults, iterate through the vector
	unsigned int maxScore = 0;
	vector<PlaceMove*>::iterator highestMove = result_PlaceMoves.end();

	//iterate through, finding all legal ones and finding highest scoring one as well
	vector<PlaceMove*>::iterator it;
	for(it = result_PlaceMoves.begin(); it != result_PlaceMoves.end(); ++it)
	{
		//get the results of the words formed by dereferencing iterator, dereferencing to get PlaceMove,
		//and accessing board's getPlaceMoveResults

		this->errorResetBlanks();
		this->setBlanks((*it)->place_tilestring);

		vector< pair<string, unsigned int> > words_formed = board->getPlaceMoveResults(*(*it));


		bool allwordssuccess = true;
		unsigned int pointsEarned = 0;
		for(unsigned int k = 0; k<words_formed.size(); k++)
		{
			if(dictionary->isLegalWord(words_formed[k].first) == false)
			{
				allwordssuccess = false;
				break;
			}
			pointsEarned += words_formed[k].second;
		}

		//if it failed a placing, then remove it as a legal PlaceMove from the results vector
		if(allwordssuccess == false || words_formed.size() == 0)
		{
			this->errorResetBlanks();
			continue;
		}

		//if it is a legal word, compare points, if it is greater score, then update what the max PlaceMove is
		else if(pointsEarned > maxScore)
		{
			maxScore = pointsEarned;
			highestMove = it;
		}
	}

	//if there was no moves that were found that are legal, aka should be passmove
	if(maxScore == 0 || highestMove == result_PlaceMoves.end())
	{
		return NULL;
	}

	//free memory that's not the main placemove
	for(unsigned int i = 0; i<result_PlaceMoves.size(); i++)
	{	//if it's not the highestMove's placeMove pointer then delete it
		if(result_PlaceMoves[i] != *highestMove)
		{
			delete result_PlaceMoves[i];
		}
	}

	return *highestMove;
}