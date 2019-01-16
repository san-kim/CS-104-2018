#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "flexCharManager.h"

int main(int argc, char *argv[])
{
  	flexCharManager simplest_mem_manager;

	/*replace with driver code as specificed in the assignment*/
  	//final check
  	//read white space as well from stringstream
	
	char* location1 = simplest_mem_manager.alloc_chars(6);
	//read into buffer location

	if(location1 != NULL)
	{
		*(location1) = 'H';
		*(location1+1) = 'e';
		*(location1+2) = 'l';
		*(location1+3) = 'l';
		*(location1+4) = 'o';
		*(location1+5) = ' ';
	}

	char* location2 = simplest_mem_manager.alloc_chars(7);
	if(location2 != NULL)
	{
		*(location2) = 'w';
		*(location2+1) = 'o';
		*(location2+2) = 'r';
		*(location2+3) = 'l';
		*(location2+4) = 'd';
		*(location2+5) = '!';
		*(location2+6) = '\n';
	}

	std::cout << "Hello world!\n";

	//free space
	if(location2 != NULL)
	{
		simplest_mem_manager.free_chars(location2);
	}


	char* location3 = simplest_mem_manager.alloc_chars(11);

	if(location3 != NULL)
	{
		*(location3) = 'm';
		*(location3+1) = 'o';
		*(location3+2) = 'o';
		*(location3+3) = 'n';
		*(location3+4) = '!';
		*(location3+5) = ' ';
		*(location3+6) = 'B';
		*(location3+7) = 'y';
		*(location3+8) = 'e';
		*(location3+9) = '.';
		*(location3+10) = '\n';
	}
	
	return 0;
}

