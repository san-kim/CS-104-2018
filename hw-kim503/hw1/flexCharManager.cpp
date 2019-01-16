#include "flexCharManager.h"
#include <iostream>

flexCharManager::flexCharManager()
{
	for(int i = 0; i<BUF_SIZE; i++)
	{
		buffer[i] = '\0';
	}

	//start with array size 2
	used_memory = new Mem_Block*[2];
	
	//*(used_memory[0])
	//Mem_Block**new_used_memory = new Mem_Block*[4];

	used_mem_size = 2;

	active_requests = 0;
	free_mem = BUF_SIZE;
}

flexCharManager::~flexCharManager()
{
	for(int i = 0; i < active_requests; i++)
	{
		delete used_memory[i];
	}

	delete [] used_memory;
}
             
char* flexCharManager::alloc_chars(int n)
{
	//error case
	if(n > BUF_SIZE || n == 0)
	{
		return NULL;
	}

	for(int i = 0; i<=BUF_SIZE-n; i++)
	{
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

			//check if it's already allocated
			bool isAllocated = false;
			for(int k = 0; k<active_requests; k++)
			{
				char* start_ptr = used_memory[k]->physical_location;
				int block_size = used_memory[k]->size;

				if(&buffer[i+counter] >= start_ptr &&
				   &buffer[i+counter] < start_ptr + block_size)
				{
					isAllocated = true;
					break;
				}
			}
			//if it's already allocated, continue traversing
			if(isAllocated == true)
			{
				i = i+counter;
				break;
			}

			counter++;
		}
		
		//if it made it to the end without breaking, succeeded
		if(counter == n)
		{
			//used_memory array RESIZE operation (if needed)

			//if no more available space in array
			if(used_mem_size <= 0)
			{
 
				//double spaces to array, active requests = the full count
				Mem_Block** temp_array = new Mem_Block*[active_requests*2];
				//copy current used_memory into temp array
				for(int k = 0; k<active_requests; k++)
				{
					temp_array[k] = used_memory[k];
				}
				//delete old used_memory's place on the stack
				delete [] used_memory;
				used_memory = temp_array;

				//doubles the effective total block count
				used_mem_size = active_requests;
			}

			char* location = &buffer[i];
			//append to end of used_memory array
			used_memory[active_requests] = new Mem_Block(n,location);
			free_mem = free_mem - n;
			active_requests++;
			used_mem_size--;

			return location;
		}
	}

    return NULL;
}

void flexCharManager::free_chars(char* p)
{
	//iterate thru the used_memory array to see whether this is in a mem_block
	for(int j = 0; j<active_requests; j++)
	{
		char* start_ptr = used_memory[j]->physical_location;
		int block_size = used_memory[j]->size;
		//check whether p falls in the bounds of a Mem_Block
		if(p == start_ptr)
		{
			//if it is within bounds, clear the block from buffer
			for(int k = 0; k < block_size; k++)
			{
				*(start_ptr + k) = '\0';
			}
			
			//delete the mem_block but not the array element
			Mem_Block* temp_toDelete = used_memory[j];
			used_memory[j] = NULL;
			delete temp_toDelete;

			//to maintain order in used_memory, keep everything leftwards 
			//without gaps shift everything right of location one left, 
			//unless it's the last element

			for(int i = j; i<active_requests-1; i++)
			{
				used_memory[i] = used_memory[i+1];
			}

			free_mem = free_mem + block_size;
			active_requests--;
			used_mem_size++;


			//RESIZE operation if needed
			//resize condition
			if(active_requests*4 < (active_requests + used_mem_size) 
				&& (active_requests + used_mem_size) > 2)
			{
				//add half the spaces to used_memory
				Mem_Block** temp_array = 
				new Mem_Block*[(active_requests+used_mem_size)/2];

				//copy current used_memory into temp array
				for(int k = 0; k<active_requests; k++)
				{
					temp_array[k] = used_memory[k];
				}
				
				//delete old used_memory's place on the stack
				delete [] used_memory;
				used_memory = temp_array;

				//doubles the effective total block count
				used_mem_size = (active_requests + used_mem_size)/2 
								 - active_requests;
			}

			break;
		}
	}
}         


 