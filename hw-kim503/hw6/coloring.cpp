#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;


vector<vector<int> > makeAdjacencyMatrix_BFS(int differentCountries, vector<vector<char> > countrymap, 
											 int rows, int cols);
void backtracking_search(int column, int lastColumn, vector<vector<int> >& adjacencymatrix, bool& oneprint);


int main(int argc, char* argv[])
{
	if(argc != 2)
		return 0;

	ifstream ifile(argv[1]);
	if(ifile.fail())
		return 0;

	//read in file
	int differentCountries;
	int rows, columns;
	ifile >> differentCountries >> rows >> columns;
	if(ifile.fail())
		return 0;

	//initialize countrymap with temp values of 0
	vector< vector<char> > countrymap;
	for(int i = 0; i<rows; i++)
	{	
		vector<char> ithline;
		for(int j = 0; j<columns; j++)
		{
			ithline.push_back('0');
		}
		countrymap.push_back(ithline);
	}

	//read in the map of characters
	string extraline;
	getline(ifile, extraline);
	for(int i = 0; i<rows; i++)
	{
		for(int j = 0; j<columns; j++)
			ifile >> countrymap[i][j];
		getline(ifile, extraline);
	}	

	//edge cases and error cases
	if(rows == 0 || columns == 0 || differentCountries == 0)
	{
		return 0;
	}

	if(differentCountries == 1)
	{
		cout << "A 1" << endl;
		return 0;
	}

	//make adjacency matrix using BFS from search algorithm repurposed, 
	//all adjacencies are initially -1, all non-adjacencies are initially 0
	vector< vector<int> > adjacencymatrix = makeAdjacencyMatrix_BFS(differentCountries, countrymap, rows, columns);
	bool oneprint = false;
	backtracking_search(0, differentCountries, adjacencymatrix, oneprint);

	return 0;
}


//backtracking search, column will represent current letter we are trying to set color
//maxColumn is how we know we are done, will always be # of columns, aka 1 after last column's index
//oneprint is to just print 1 solution
void backtracking_search(int column, int lastColumn, vector<vector<int> >& adjacencymatrix, bool& oneprint)
{
	//just to print one solution per file
	if(oneprint == false)
	{
		//if we have set all colors successfully, print! :)
		if(column == lastColumn)
		{
			//iterate through columns
			for(int i = 0; i<lastColumn; i++)
			{
				//to find the color of each letter/country, go through its column and find its nonzero color
				int color = 0;
				//for rows this time, but it is a square matrix so same dimensions for rows 
				for(int j = 0; j<lastColumn; j++)
				{
					if(adjacencymatrix[j][i] != 0)
					{
						color = adjacencymatrix[j][i];
					}
				}

				cout << (char)('A' + i) << " " << color << endl;
			}
			//so it only prints 1
			oneprint = true;
			return;
		}

		//we got work to do
		else
		{
			//for each color
			for(int i = 1; i<=4; i++)
			{
				int trycolor = i;

				//check to see whether color trying to set conflicts with its neighboring colors
				bool isViableColorinRow = true;
				for(int c = 0; c < lastColumn; c++)
				{
					//check whether any of its neibhors have that color
					//the row is the column for the element because this is a square matrix
					if(adjacencymatrix[column][c] == trycolor)
					{
						isViableColorinRow = false;
					}
				}

				//if it is a viable color in its row, proceed
				if(isViableColorinRow)
				{
					//change its entire column to that color to indicate to its neibhors color change, 
					//the "threats"
					for(int r = 0; r<lastColumn; r++)
					{
						if(adjacencymatrix[r][column] != 0)
						{
							adjacencymatrix[r][column] = trycolor;
						}
					}

					//to next column
					backtracking_search(column+1, lastColumn, adjacencymatrix, oneprint);

					//change entire column to -1 unchanged color to indicate failed color try, "remove threat"
					for(int r = 0; r<lastColumn; r++)
					{
						if(adjacencymatrix[r][column] != 0)
						{
							adjacencymatrix[r][column] = -1;
						}
					}
				}
			}
		}
	}
}	


//more or less from search.cpp and repurposed for adjacency matrix
vector<vector<int> > makeAdjacencyMatrix_BFS(int differentCountries, vector<vector<char> > countrymap, 
											 int rows, int cols)
{
	vector< vector<int> > adjacencymatrix;
	//initialize all to 0
	for(int i = 0; i<differentCountries; i++)
	{
		vector<int> line;
		for(int j = 0; j<differentCountries; j++)
		{	
			line.push_back(0);
		}
		adjacencymatrix.push_back(line);
	}


	//BFS portion repurposed from search

	bool visitedLocations[rows][cols];
	for(int i = 0; i<rows; i++)
		for(int j = 0; j<cols; j++)
			visitedLocations[i][j] = false;

	//push our first country at 0,0 to the differentCountryqueue
	queue< pair<int, int> > differentCountryqueue;
	pair<int,int> startingLetterPair(0,0);
	differentCountryqueue.push(startingLetterPair);

	//this while loop will loop the number of different countries there are
	while(differentCountryqueue.empty() == false)
	{
		int differentRow = differentCountryqueue.front().first;
		int differentCol = differentCountryqueue.front().second;
		//check if the new country has already been visited, if so then pop
		if(visitedLocations[differentRow][differentCol] == true)
			differentCountryqueue.pop();

		//country has not been explored previously, run BFS and find its size
		else
		{
			differentCountryqueue.pop();
			//mark the first one as visited
			visitedLocations[differentRow][differentCol] = true;

			//this queue will search this one country
			queue< pair<int,int> > sameCountryqueue;
		
			//enqueue the first node of the country
			pair<int,int> letterPair(differentRow, differentCol);
			sameCountryqueue.push(letterPair);

			//find out what this country's character is from what we read in
			char countryChar = countrymap[differentRow][differentCol];

			//this while loop will run the size of this country # of times, inside is O(1)
			while(sameCountryqueue.empty() == false)
			{
				int currentRow = sameCountryqueue.front().first;
				int currentCol = sameCountryqueue.front().second;
				//dequeue front of queue for the location we are analyzing
				sameCountryqueue.pop();

				//LEFT location, check bounds and if it has been visited
				if(currentCol-1 >= 0)
				{	//for out of bounds errors if the above is true, check if visited and same character
					if(visitedLocations[currentRow][currentCol-1] == false && 
					   countryChar == countrymap[currentRow][currentCol-1])
					{
						pair<int,int> foundPair(currentRow, currentCol-1);
						sameCountryqueue.push(foundPair);
						//update visited locations
						visitedLocations[currentRow][currentCol-1] = true;
					}
					//for when it is a different character we have not visited before, push back to differentqueue
					else if(visitedLocations[currentRow][currentCol-1] == false && 
							countryChar != countrymap[currentRow][currentCol-1])
					{
						pair<int,int> founddiffCountry(currentRow, currentCol-1);
						differentCountryqueue.push(founddiffCountry);
					}
					//for our adjacency matrix, we need adjacency even if visited before
					if(countryChar != countrymap[currentRow][currentCol-1])
					{
						//set the adjacency matrix entry of this country and this different country
						int matrix_row_index = (int)(countryChar) - (int)('A');
						int matrix_col_index = (int)(countrymap[currentRow][currentCol-1]) - (int)('A');
						adjacencymatrix[matrix_row_index][matrix_col_index] = -1;
					}
				}

				//RIGHT location, check bounds and if it has been visited
				if(currentCol+1 < cols)
				{	//for out of bounds errors if the above is true, check if visited and same character					
					if(visitedLocations[currentRow][currentCol+1] == false && 
					   countryChar == countrymap[currentRow][currentCol+1])
					{
						pair<int,int> foundPair(currentRow, currentCol+1);
						sameCountryqueue.push(foundPair);
						//update visited locations
						visitedLocations[currentRow][currentCol+1] = true;
					}
					//for when it is a different character we have not visited before, push back to differentqueue
					else if(visitedLocations[currentRow][currentCol+1] == false && 
							countryChar != countrymap[currentRow][currentCol+1])
					{
						pair<int,int> founddiffCountry(currentRow, currentCol+1);
						differentCountryqueue.push(founddiffCountry);
					}

					//for our adjacency matrix, we need adjacency even if visited before
					if(countryChar != countrymap[currentRow][currentCol+1])
					{
						//set the adjacency matrix entry of this country and this different country
						int matrix_row_index = (int)(countryChar) - (int)('A');
						int matrix_col_index = (int)(countrymap[currentRow][currentCol+1]) - (int)('A');
						adjacencymatrix[matrix_row_index][matrix_col_index] = -1;
					}
				}

				//UP location, check bounds and if it has been visited
				if(currentRow-1 >= 0)
				{	//for out of bounds errors if the above is true, check if visited and same character
					if(visitedLocations[currentRow-1][currentCol] == false && 
					   countryChar == countrymap[currentRow-1][currentCol])
					{
						pair<int,int> foundPair(currentRow-1, currentCol);
						sameCountryqueue.push(foundPair);
						//update visited locations
						visitedLocations[currentRow-1][currentCol] = true;
					}
					//for when it is a different character we have not visited before, push back to differentqueue
					else if(visitedLocations[currentRow-1][currentCol] == false && 
							countryChar != countrymap[currentRow-1][currentCol])
					{
						pair<int,int> founddiffCountry(currentRow-1, currentCol);
						differentCountryqueue.push(founddiffCountry);
					}

					//for our adjacency matrix, we need adjacency even if visited before
					if(countryChar != countrymap[currentRow-1][currentCol])
					{
						//set the adjacency matrix entry of this country and this different country
						int matrix_row_index = (int)(countryChar) - (int)('A');
						int matrix_col_index = (int)(countrymap[currentRow-1][currentCol]) - (int)('A');
						adjacencymatrix[matrix_row_index][matrix_col_index] = -1;
					}
				}

				//DOWN location, check bounds and if it has been visited
				if(currentRow+1 < rows)
				{	//for out of bounds errors if the above is true, check if visited and same character
					if(visitedLocations[currentRow+1][currentCol] == false && 
					   countryChar == countrymap[currentRow+1][currentCol])
					{
						pair<int,int> foundPair(currentRow+1, currentCol);
						sameCountryqueue.push(foundPair);
						//update visited locations
						visitedLocations[currentRow+1][currentCol] = true;
					}
					//for when it is a different character we have not visited before, push back to differentqueue
					else if(visitedLocations[currentRow+1][currentCol] == false && 
							countryChar != countrymap[currentRow+1][currentCol])
					{
						pair<int,int> founddiffCountry(currentRow+1, currentCol);
						differentCountryqueue.push(founddiffCountry);
					}

					//for our adjacency matrix, we need adjacency even if visited before
					if(countryChar != countrymap[currentRow+1][currentCol])
					{
						//set the adjacency matrix entry of this country and this different country
						int matrix_row_index = (int)(countryChar) - (int)('A');
						int matrix_col_index = (int)(countrymap[currentRow+1][currentCol]) - (int)('A');
						adjacencymatrix[matrix_row_index][matrix_col_index] = -1;
					}
				}
			}
		}
	}

	return adjacencymatrix;
}