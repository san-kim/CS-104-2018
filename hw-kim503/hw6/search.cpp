#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 2)
		return 0;

	ifstream ifile(argv[1]);
	if(ifile.fail())
		return 0;

	//read in file
	int differentLetters;
	int rows, columns;
	ifile >> differentLetters >> rows >> columns;
	if(ifile.fail())
		return 0;

	//read in the map of characters
	char countrymap[rows][columns];
	string extraline;
	getline(ifile, extraline);
	for(int i = 0; i<rows; i++)
	{
		for(int j = 0; j<columns; j++)
			ifile >> countrymap[i][j];
		getline(ifile, extraline);
	}	

	//edge and base cases 
	if(rows == 0 || columns == 0)
	{
		cout << 0 << endl;
		return 0;
	}
	if(rows == 1 && columns == 1)
	{
		cout << 1 << endl;
		return 0;
	}

	bool visitedLocations[rows][columns];
	for(int i = 0; i<rows; i++)
		for(int j = 0; j<columns; j++)
			visitedLocations[i][j] = false;

	queue< pair<int, int> > differentCountryqueue;
	pair<int,int> startingLetterPair(0,0);
	differentCountryqueue.push(startingLetterPair);

	int maxCountrySize = 0;

	//this while loop will loop the number of different countries there are
	while(differentCountryqueue.empty() == false)
	{
		int differentRow = differentCountryqueue.front().first;
		int differentCol = differentCountryqueue.front().second;
		//check if the new country has already been visited, if so then pop
		if(visitedLocations[differentRow][differentCol] == true)
		{
			differentCountryqueue.pop();
		}

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
			//initialize this country's size to 1 as we have one initial location
			int thiscountrysize = 1;
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
						//update country size and visited locations
						thiscountrysize++;
						visitedLocations[currentRow][currentCol-1] = true;
					}
					//for when it is a different character we have not visited before, push back to differentqueue
					else if(visitedLocations[currentRow][currentCol-1] == false && 
							countryChar != countrymap[currentRow][currentCol-1])
					{
						pair<int,int> founddiffCountry(currentRow, currentCol-1);
						differentCountryqueue.push(founddiffCountry);
					}
				}

				//RIGHT location, check bounds and if it has been visited
				if(currentCol+1 < columns)
				{	//for out of bounds errors if the above is true, check if visited and same character					
					if(visitedLocations[currentRow][currentCol+1] == false && 
					   countryChar == countrymap[currentRow][currentCol+1])
					{
						pair<int,int> foundPair(currentRow, currentCol+1);
						sameCountryqueue.push(foundPair);
						//update country size and visited locations
						thiscountrysize++;
						visitedLocations[currentRow][currentCol+1] = true;
					}
					//for when it is a different character we have not visited before, push back to differentqueue
					else if(visitedLocations[currentRow][currentCol+1] == false && 
							countryChar != countrymap[currentRow][currentCol+1])
					{
						pair<int,int> founddiffCountry(currentRow, currentCol+1);
						differentCountryqueue.push(founddiffCountry);
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
						//update country size and visited locations
						thiscountrysize++;
						visitedLocations[currentRow-1][currentCol] = true;
					}
					//for when it is a different character we have not visited before, push back to differentqueue
					else if(visitedLocations[currentRow-1][currentCol] == false && 
							countryChar != countrymap[currentRow-1][currentCol])
					{
						pair<int,int> founddiffCountry(currentRow-1, currentCol);
						differentCountryqueue.push(founddiffCountry);
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
						//update country size and visited locations
						thiscountrysize++;
						visitedLocations[currentRow+1][currentCol] = true;
					}
					//for when it is a different character we have not visited before, push back to differentqueue
					else if(visitedLocations[currentRow+1][currentCol] == false && 
							countryChar != countrymap[currentRow+1][currentCol])
					{
						pair<int,int> founddiffCountry(currentRow+1, currentCol);
						differentCountryqueue.push(founddiffCountry);
					}
				}
			}

			if(maxCountrySize < thiscountrysize)
			{
				maxCountrySize = thiscountrysize;
			}
		}
	}

	cout << maxCountrySize << endl;

	return 0;
}

