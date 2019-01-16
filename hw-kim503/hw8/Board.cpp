#include "Board.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

/* constructor that initializes the board state with an empty board
           and the size and bonuses and start square based on the given file. */
Board::Board (std::string board_file_namey, std::string init_file_name)
{
	ifstream board_input(board_file_namey);
	board_input >> columns;
	while(board_input.fail())
	{
		board_input >> columns;
	}
	//read until it reaches an int, assume the format is correct 
	board_input >> rows;
	while(board_input.fail())
	{
		board_input >> rows;
	}

	//consume newline
	string newline_consume;
	getline(board_input,newline_consume);

	board_input >> starting_x;
	while(board_input.fail())
	{
		board_input >> starting_x;
	}
	//read until reaches int, assume format is correct
	board_input >> starting_y;
	while(board_input.fail())
	{
		board_input >> starting_y;
	}
	//consume newline again
	string newline_consume2;
	getline(board_input,newline_consume2);


	for(int i = 0; i<rows; i++)
	{
		string line;
		getline(board_input, line);
		stringstream ss(line);
		char readCharacter;

		vector<Square*> currentRow;
		for(int j = 0; j<columns; j++)
		{
			bool start = false;
			//check whether this is a start index:starting_x-1 and starting_y-1
			if(i == starting_y-1 && j == starting_x-1)
			{
				start = true;
			}

			ss >> readCharacter;

			if(readCharacter == '.')
			{
				Square* sq = new Square(1,1,start);
				currentRow.push_back(sq);
			}

			else if(readCharacter == '2')
			{
				Square* sq = new Square(2,1,start);
				currentRow.push_back(sq);
			}

			else if(readCharacter == '3')
			{
				Square* sq = new Square(3,1,start);
				currentRow.push_back(sq);
			}

			else if(readCharacter == 'd')
			{
				Square* sq = new Square(1,2,start);
				currentRow.push_back(sq);
			}

			else if(readCharacter == 't')
			{
				Square* sq = new Square(1,3,start);
				currentRow.push_back(sq);
			}
		}
		squareboard.push_back(currentRow);
	}	

	
	//if an init file exists, then instantiate accordingly
	if(init_file_name != "no init file")
	{
		ifstream init_file(init_file_name);
		for(int i = 0; i<rows; i++)
		{
			for(int j = 0; j<columns; j++)
			{
				char first;
				char second;
				char third;
				init_file >> first;
				init_file >> second;
				init_file >> third;
				//if the tile is blank
				if(first == '.' && second == '.' && third == '.')
				{
					continue;
				}

				//if the tile is not blank
				else
				{
					int points = (int)(second - '0') * 10 + (int)(third - '0');
					Tile* initTile = new Tile(first, points);
					squareboard[i][j]->placeTile(initTile);
				}
			}
			string consumespace;
			getline(init_file, consumespace);
		}
	}
}

Board::~Board()
{
	for(int i = 0; i<rows; i++)
	{
		for(int j = 0; j<columns; j++)
		{
			delete squareboard[i][j];
		}
	}
}

/* returns a vector of all words that would be formed by executing the
    given move. The first element of the pair is a string containing the word
    formed, and the second element is the score that that word earns
    (with all multipliers, but not the 50-point bonus for all letters).

    Words returned are all in uppercase.

	The last entry of the vector is always the "main" word formed
	in the direction chosen by the user; the others could be in arbitrary
	order. (This is helpful for backtracking search.)

    This function does not check that the words formed are actually in the dictionary.
    The words returned from this function must be checked against the dictionary to
    determine if the move is legal.	*/
std::vector< std::pair<std::string, unsigned int> > Board::getPlaceMoveResults(PlaceMove &m) const
{

	vector< pair<string, unsigned int> > PlaceMove_results;
	//at this point ALL BLANKS WILL BE REPLACED
	//for case where you create more than 1 new words
	//when it is horizontal

	if(m.is_horizontal_place)
	{
 		unsigned int mainwordvalue = 0;
		int mainwordMultiplier = 1;

		int leftcount = 0;
		string leftword = "";
		//while it is legal bounds and finds stuff left of it (when it was a    c, - rcti to make arctic
		while(m.place_column-leftcount-1 > 0)
		{
			leftcount++;
			//if that square is occupied, keep going just in case more than 1 letter
			if(squareboard[m.place_row-1][m.place_column-leftcount-1]->isOccupied())
			{
				int yval = m.place_row-1;
				int xval = m.place_column-leftcount-1;
				leftword = squareboard[yval][xval]->getLetter() + leftword;

				//multipliers will be 1 for each of these preexisting letters
				mainwordvalue += squareboard[yval][xval]->getScore();
			}
			else
			{
				break;
			}
		}
		//at this point ALL BLANKS WILL BE REPLACED in tiles
		//this will get the tiles without the replacement after ?
		vector<Tile*> tilesplacemove = m.tileVector();

		string mainWord = "";

		int cross_counter = 0;
		for(unsigned int i = m.place_column; i<m.place_column + tilesplacemove.size(); i++)
		{
			//when it comes across a tile already in place
			if(squareboard[m.place_row-1][i-1 + cross_counter]->isOccupied())
			{
				//multipliers will be 1 if already preexisting tile
				mainwordvalue += squareboard[m.place_row-1][i-1 + cross_counter]->getScore();
				mainWord = mainWord + squareboard[m.place_row-1][i-1 + cross_counter]->getLetter();
				i--;
				cross_counter++;
			}

			else
			{
				//add to main word the letter of the tilestring if no overlap
				mainWord = mainWord + tilesplacemove[i - m.place_column]->getUse();
				int yval = m.place_row-1;
				int xval = i-1 + cross_counter;
				//do letter multiplier
				mainwordvalue += tilesplacemove[i-m.place_column]->getPoints() * squareboard[yval][xval]->getLMult();
				mainwordMultiplier *= squareboard[yval][xval]->getWMult();
			}
		}

		int rightcount = 0;
		string rightword = "";
		//whether the next one to right of end of word is within bounds of array indeces
		while(m.place_column + tilesplacemove.size() + cross_counter + rightcount-1 <= (unsigned int)(columns-1))
		{
			rightcount++;
			unsigned int nextindex = m.place_column + tilesplacemove.size() + cross_counter + rightcount-2;
			//if that squre is occupied, keep going just in case more than 1 letter
			if(squareboard[m.place_row-1][nextindex]->isOccupied())
			{
				rightword = rightword + squareboard[m.place_row-1][nextindex]->getLetter();
				mainwordvalue += squareboard[m.place_row-1][nextindex]->getScore();
			}
			else
			{
				break;
			}
		}

		//concatenate the left and right hand sides, apply word multipliers
		mainWord = leftword + mainWord + rightword;
		mainwordvalue *= mainwordMultiplier;

		//for all smaller words that are vertical
		int skip_counter = 0;
		for(unsigned int i = m.place_column; i<m.place_column + tilesplacemove.size(); i++)
		{
			//when it comes across a tile already in place, just skip
			if(squareboard[m.place_row-1][i-1 + skip_counter]->isOccupied())
			{
				i--;
				skip_counter++;
				//nothing to add when we run across something preexisting
				continue;
			}

			//else
			string result = "";
			result = result + tilesplacemove[i - m.place_column]->getUse();

			unsigned int wordscore = tilesplacemove[i-m.place_column]->getPoints();
			int Lmultiplier = squareboard[m.place_row-1][i-1 + skip_counter]->getLMult();
			wordscore = wordscore*Lmultiplier;
			int Wmultiplier = squareboard[m.place_row-1][i-1 + skip_counter]->getWMult();

			string up = "";
			int upcounter = 0;
			//while it is still in bounds
			while(m.place_row - upcounter > 1)
			{
				upcounter++;
				if(squareboard[m.place_row - upcounter - 1][i-1+skip_counter]->isOccupied())
				{	//these will be multiplier 1
					up = squareboard[m.place_row - upcounter - 1][i-1+skip_counter]->getLetter() + up;
					wordscore += squareboard[m.place_row - upcounter - 1][i-1+skip_counter]->getScore();
				}

				else //if there is nothing there
				{
					break;
				}
			}

			string down = "";
			int downcounter = 0;
			while((int)(m.place_row + downcounter) < rows)
			{
				downcounter++;
				if(squareboard[m.place_row + downcounter - 1][i-1+skip_counter]->isOccupied())
				{
					down = down + squareboard[m.place_row + downcounter - 1][i-1+skip_counter]->getLetter();
					wordscore += squareboard[m.place_row + downcounter - 1][i-1+skip_counter]->getScore();
				}

				else //if there is nothing there
				{
					break;
				}
			}

			if(up.size() == 0 && down.size() == 0)
			{	//if there is nothing above or below this element, go to next element
				continue;
			}

			else
			{
				result = up + result + down;
				wordscore = Wmultiplier * wordscore;
				pair<string,unsigned int> madeword(result, wordscore);
				PlaceMove_results.push_back(madeword);
			}
		}
		if(mainWord.size() != 1) // if it is of size 1, then word will be just the letter
		{
			pair<string,unsigned int> lastword(mainWord, mainwordvalue);
			PlaceMove_results.push_back(lastword);
		}
		return PlaceMove_results;
	}

	//when it is VERTICAL placement
	else
	{
		unsigned int mainwordvalue = 0;
		int mainwordMultiplier = 1;

		int upcount = 0;
		string upword = "";
		//while it is legal bounds and finds stuff on top of it (when it was arc  , - tic to make arctic
		while(m.place_row - upcount - 1 > 0)
		{
			upcount++;
			//if that squre is occupied, keep going just in case more than 1 letter
			if(squareboard[m.place_row - upcount - 1][m.place_column-1]->isOccupied())
			{
				int yval = m.place_row - upcount - 1;
				int xval = m.place_column-1;
				upword = squareboard[yval][xval]->getLetter() + upword;

				//multipliers will be 1 for each of these preexisting letters
				mainwordvalue += squareboard[yval][xval]->getScore();
			}
			else
			{
				break;
			}
		}
		//at this point ALL BLANKS WILL BE REPLACED in tiles
		//this will get the tiles without the replacement after ?
		vector<Tile*> tilesplacemove = m.tileVector();
		string mainWord = "";

		int cross_counter = 0;
		for(unsigned int i = m.place_row; i<m.place_row + tilesplacemove.size(); i++)
		{
			//when it comes across a tile already in place
			if(squareboard[i-1 + cross_counter][m.place_column-1]->isOccupied())
			{  
				mainWord = mainWord + squareboard[i-1 + cross_counter][m.place_column-1]->getLetter();
				//multipliers will be 1 if already preexisting tile
				mainwordvalue += squareboard[i-1 + cross_counter][m.place_column-1]->getScore();
				i--;
				cross_counter++;
			}

			else
			{
				//add to main word the letter of the tilestring if no overlap
				mainWord = mainWord + tilesplacemove[i - m.place_row]->getUse(); 
				int yval = i-1 + cross_counter;
				int xval = m.place_column-1;
				//do letter multiplier
				mainwordvalue += tilesplacemove[i-m.place_row]->getPoints() * squareboard[yval][xval]->getLMult();
				mainwordMultiplier *= squareboard[yval][xval]->getWMult();
			}
		}

		int downcount = 0;
		string downword = "";
		//whether the next one to right of end of word is within bounds of array indeces
		while(m.place_row + tilesplacemove.size() + cross_counter + downcount - 1 <= (unsigned int)(rows-1))
		{
			downcount++;
			unsigned int nextindex = m.place_row + tilesplacemove.size() + cross_counter + downcount-2;
			//if that squre is occupied, keep going just in case more than 1 letter
			if(squareboard[nextindex][m.place_column-1]->isOccupied())
			{
				downword = downword + squareboard[nextindex][m.place_column-1]->getLetter();
				mainwordvalue += squareboard[nextindex][m.place_column-1]->getScore();
			}
			else
			{
				break;
			}
		}

		//concatenate the upwards and downward sides, apply word multipliers
		mainWord = upword + mainWord + downword;
		mainwordvalue *= mainwordMultiplier;

		//for all smaller words that are vertical
		int skip_counter = 0;
		for(unsigned int i = m.place_row; i<m.place_row + tilesplacemove.size(); i++)
		{   
			//when it comes across a tile already in place, just skip
			if(squareboard[i-1 + skip_counter][m.place_column-1]->isOccupied())
			{
				i--;
				skip_counter++;
				//nothing to add when we run across something preexisting
				continue;
			}

			//else

			string result = "";
			result = result + tilesplacemove[i-m.place_row]->getUse();
			unsigned int wordscore = tilesplacemove[i-m.place_row]->getPoints();
			int Lmultiplier = squareboard[i-1 + skip_counter][m.place_column-1]->getLMult();
			wordscore = wordscore*Lmultiplier;
			int Wmultiplier = squareboard[i-1 + skip_counter][m.place_column-1]->getWMult();

			string left = "";
			int leftcounter = 0;
			//while it is still in bounds
			while(m.place_column - leftcounter > 1)
			{
				leftcounter++;
				if(squareboard[i-1+skip_counter][m.place_column-leftcounter-1]->isOccupied())
				{	//these will be multiplier 1
					left = squareboard[i-1+skip_counter][m.place_column-leftcounter-1]->getLetter() + left;
					wordscore += squareboard[i-1+skip_counter][m.place_column-leftcounter-1]->getScore();
				}

				else //if there is nothing there
				{
					break;
				}
			}

			string right = "";
			int rightcounter = 0;
			while(m.place_column + rightcounter < (unsigned int)(columns))
			{
				rightcounter++;
				if(squareboard[i-1+skip_counter][m.place_column+rightcounter-1]->isOccupied())
				{
					right = right + squareboard[i-1+skip_counter][m.place_column+rightcounter-1]->getLetter();
					wordscore += squareboard[i-1+skip_counter][m.place_column+rightcounter-1]->getScore();
				}

				else //if there is nothing there
				{
					break;
				}
			}

			if(left.size() == 0 && right.size() == 0)
			{	//if there is nothing above or below this element, go to next element
				continue;
			}

			else
			{
				result = left + result + right;
				wordscore = Wmultiplier * wordscore;
				pair<string,unsigned int> madeword(result, wordscore);
				PlaceMove_results.push_back(madeword);
			}
		}
		if(mainWord.size() != 1) // if it is of size 1, then word will be just the letter
		{
			pair<string,unsigned int> lastword(mainWord, mainwordvalue);
			PlaceMove_results.push_back(lastword);
		}
		return PlaceMove_results;
	}
}

/* Executes the given move by taking tiles and placing them on the board.
   This function does not check for correctness of the move, so could
   segfault or cause other errors if called for an incorrect move.
   When a blank tile '?' is placed on the board, it is treated as a letter,
   i.e., the corresponding square has that letter (with score 0) placed on it.
*/
void Board::executePlaceMove (PlaceMove & m)
{
	vector<Tile*> placeTiles = m.tileVector();
	bool horiz = m.is_horizontal_place;
	int firstRow = m.place_row-1;
	int firstColumn = m.place_column-1;

	//if horizontal orientation
	if(horiz)
	{
		int overlaps = 0;
		for(int i = 0; i<(int)placeTiles.size(); i++)
		{
			//if cross over, then skip this square
			if(squareboard[firstRow][firstColumn + i + overlaps]->isOccupied())
			{
				//increment number of overlaps, do nothing to change board 
				overlaps++;
				//decrement to stay on this tile, still needs to be placed
				i--;
			}
			else //when it is empty
			{
				squareboard[firstRow][firstColumn + i + overlaps]->placeTile(placeTiles[i]);
			}
		}
	}
	//if vertical
	else
	{
		int overlaps = 0;
		for(int i = 0; i<(int)placeTiles.size(); i++)
		{
			//if cross over, then skip this square
			if(squareboard[firstRow + i + overlaps][firstColumn]->isOccupied())
			{
				//increment number of overlaps, do nothing to change board 
				overlaps++;
				//decrement to stay on this tile, still needs to be placed
				i--;
			}
			else //when it is empty
			{
				squareboard[firstRow + i + overlaps][firstColumn]->placeTile(placeTiles[i]);
			}
		}
	}
}

/* Returns a pointer to the Square object representing the
	(y,x) position of the board. Indexing starts at 1 here.
	This is needed only to display the board. */
Square * Board::getSquare (size_t x, size_t y) const
{
	return squareboard[y-1][x-1];
}

/* Returns the number of rows of the board.*/
size_t Board::getRows() const
{
	return rows;
}

/* Returns the number of columns of the board.*/
size_t Board::getColumns() const
{
	return columns;
}

bool Board::isOccupiedSquare(size_t y, size_t x)
{
	return squareboard[y-1][x-1]->isOccupied();
}

int Board::getStarting_x()
{
	return starting_x;
}
	
int Board::getStarting_y()
{
	return starting_y;
}

