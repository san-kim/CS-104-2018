#include <cstddef>
#include "simpleCharManager.h"


simpleCharManager::simpleCharManager()
{
	//initialize all the buffer elements
	for(int i = 0; i<BUF_SIZE; i++)
	{
		buffer[i] = '\0';
	}

	free_place = buffer;
}

simpleCharManager::~simpleCharManager()
{

}
             
char* simpleCharManager::alloc_chars(int n)
{
	//error case
	if(n > BUF_SIZE || n == 0 || free_place+n > &buffer[BUF_SIZE])
	{
		return NULL;
	}

	//for(int i = 0; i<=BUF_SIZE-n; i++)
	for(int i = 0; i<=BUF_SIZE-n; i++)
	{
		//check whether buffer from index i to i+n is empty, increment 
		//i with the j value it stops at so that it doesnt have to read 
		//the same location buffer[i] twice.

		//go to next free place not allocated
		if(&buffer[i] < free_place)
		{
			continue;
		}
 
		int counter = 0;
		while(counter < n)
		{
			//if it finds something before n entries, fails
			if(buffer[i+counter] != '\0')
			{
				//increment the i value, avoiding needless repeats
				
				i = i+counter;
				break;
			}

			counter++;
		}
		
		//if it made it to the end without breaking aka succeeded
		if(counter == n)
		{
			free_place = free_place + n;
			return &buffer[i];
		}

	}

    return NULL;
}

void simpleCharManager::free_chars(char* p)
{
	//to find where in the buffer this pointer is situated
	bool exists = false;
	for(int j = 0; j<BUF_SIZE; j++)
	{
		if(&buffer[j] == p)
		{
			exists = true;
			break;
		}
	}	

	if(!exists)
	{
		return;
	}

	if(free_place > p)
	{
		free_place = p;
	}

	for(int i = 0; i<BUF_SIZE; i++)
	{
		//when location matches with p or later, then epmty buffer[i] member
		if(&buffer[i] >= p)
		{
			buffer[i] = '\0';
		}
	}
}         




