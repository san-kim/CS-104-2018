#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "simpleCharManager.h"

int main(int argc, char *argv[])
{
	simpleCharManager simplest_mem_manager;

	/*write driver code as described in the assignment to replace this */

	char* location1 = simplest_mem_manager.alloc_chars(13);
	//read into buffer location

	if(location1 != NULL)
	{
		*(location1) = 'H';
		*(location1+1) = 'e';
		*(location1+2) = 'l';
		*(location1+3) = 'l';
		*(location1+4) = 'o';
		*(location1+5) = ' ';
		*(location1+6) = 'w';
		*(location1+7) = 'o';
		*(location1+8) = 'r';
		*(location1+9) = 'l';
		*(location1+10) = 'd';
		*(location1+11) = '!';
		*(location1+12) = '\n';
	}

	std::cout << "Hello world!\n";

	if(location1 != NULL)
	{
		//free space
		simplest_mem_manager.free_chars(location1+6);
	}

	char* location2 = simplest_mem_manager.alloc_chars(11);
	
	if(location2 != NULL)
	{
		*(location2) = 'm';
		*(location2+1) = 'o';
		*(location2+2) = 'o';
		*(location2+3) = 'n';
		*(location2+4) = '!';
		*(location2+5) = ' ';
		*(location2+6) = 'B';
		*(location2+7) = 'y';
		*(location2+8) = 'e';
		*(location2+9) = '.';
		*(location2+10) = '\n';
	}

	return 0;
}

