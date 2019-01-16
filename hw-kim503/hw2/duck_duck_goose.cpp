#include "duck_duck_goose.h"
#include <fstream>
using namespace std;

void simulateDDGRound(GameData * gameData, std::ostream & output)
{
	//store the size of the current circle
	int size = (gameData->playerList).size();
	//set the random moves from 0 to 4*size-1
	int moves = rand()%(4*size);
	
	//print ducks
	for(int i = 0; i<moves; i++)
	{
		//will get index at i = 0 to m-1
		output << (gameData->playerList).get(i) << " is a Duck." << endl;
	}

	//find goose's ID, will start at head (0) and go "moves" times
	int gooseID = (gameData->playerList).get(moves);
	output << gooseID << " is a Goose!" << endl;


	//set the speed of IT between 1-49
	int it_speed = rand()%49 + 1;
	//set the speed of goose between 1-49
	int goose_speed = rand()%49 + 1;

	//if they are a tie, reset until they are not 
	while(it_speed == goose_speed)
	{
		it_speed = rand()%49 + 1;
		goose_speed = rand()%49 + 1;
	}

	//if it wins
	if(it_speed > goose_speed)
	{	
		//replace the goose's spot w/ it's ID
		(gameData->playerList).set(moves, gameData->itPlayerID);
		gameData->itPlayerID = gooseID;
		//gooseID still stores this round's goose's ID, not the IT replacement
		output<< gameData->itPlayerID<< " took "<<gooseID << "'s spot!" << endl;


		//this will not be a winning case so skip bottom code
		return;
	}

	//if goose wins
	if(goose_speed > it_speed)
	{
		output << gameData->itPlayerID << " is out!" << endl;
	}

	//winner case, where it is already out, there is no virtual it right now
	if((gameData->playerList).size() == 1)
	{	
		output<< "Winner is "<< (gameData->playerList).get(moves)<< "!"<< endl;
		//set to 0 to indicate that it is over
		gameData->itPlayerID = 0;
	}

	else
	{
		//random index from 0 to n-2, one less than the total size 
		//this allows us to iterate thru all but the goose starting from goose
		//moves is the current index of the previous goose

		int randomIndex = moves + rand()%(size-1);


		//set new it
		gameData->itPlayerID = (gameData->playerList).get(randomIndex);
		output << gameData->itPlayerID << " was chosen as the new it." << endl;
		//remove it from the list
		(gameData->playerList).remove(randomIndex);
	}

}

int main(int argc, char* argv[])
{
	if(argc < 3) 
	{
		return 1;
	} 

	if(argc > 3)
	{
		return 1;
	}

	//read file and check that it exists
    ifstream ifile(argv[1]);
    if(ifile.fail()) 
    {
    	return 1;
    }

    ofstream ofile(argv[2]);
    if(ofile.fail()) 
    {
    	return 1;
    }

    unsigned int seed;
    ifile >> seed;
    if(ifile.fail())
    {
    	return 1;
    }
    srand(seed);

    int playercount;
    ifile >> playercount;
    if(ifile.fail())
    {
    	return 1;
    }

    unsigned int itID;
    ifile >> itID;
    if(ifile.fail())
    {
    	return 1;
    }



    GameData* game = new GameData;
    game->itPlayerID = itID;

    //what if you want to push back an id but it's greater than 2^16-1
    //one less than playercount because IT is also included in that count
    for(int i = 0; i<playercount-1; i++)
    {
    	unsigned int newID;
    	ifile >> newID;
	    if(ifile.fail())
	    {
	   		delete game;
	    	return 1;
	    }

    	(game->playerList).push_back(newID);
    }


    //run 
    if((game->playerList).size() == 0)
    {
	    delete game;
    	return 2;
    }


    while(game->itPlayerID != 0)
    {
    	simulateDDGRound(game, ofile);
	}

    delete game;
}