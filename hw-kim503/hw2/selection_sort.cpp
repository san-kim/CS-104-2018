#include "selection_sort.h"


Item* findMin(Item* head)
{
	//if empty
	if(head == nullptr)
	{
		return nullptr;
	}

	//if only one element
	if(head->next == nullptr && head->prev == nullptr)
	{
		return head;
	}

	Item* minimum = head;
	Item* location = head;
	while(location != nullptr)
	{
		if(location->getValue() < minimum->getValue())
		{
			minimum = location;
		}
		location = location->next;
	}

	return minimum;
}

Item* LLSelectionSort(Item* head)
{
	//if empty
	if(head == nullptr)
	{
		return nullptr;
	}

	//if only one item
	if(head->next == nullptr && head->prev == nullptr)
	{
		return head;
	}

	//pointer to the minimum valued Item of the entire list, will be head
	Item* newHead = findMin(head);

	Item* location = head;
	while(location != nullptr)
	{
		Item* minimum = findMin(location);
		//if they are not one and the same
		if(location != minimum)
		{
			//for case in which minimum is one after location,
			//weird switches
			if(location->next == minimum)
			{
				//points to the Item before these two consecutive Items
				Item* tprev = location->prev;
				//points to the Item after these two consecutive Items
				Item* tnext = minimum->next;

				location->prev = minimum;
				location->next = tnext;
				//if location does not belong at the very end
				if(tnext != nullptr)
				{	
					tnext->prev = location;
				}

				minimum->prev = tprev;
				minimum->next = location;
				//if minimum does not belong at the very front
				if(tprev != nullptr)
				{
					tprev->next = minimum;
				}
			}

			//for cases where minimum and location are at least
			//one Item apart
			else
			{
				//for updating min
				Item* tempprev = location->prev;
				Item* tempnext = location->next;
				//update location and the prev & next of the ones around it 
				location->next = minimum->next;
				location->prev = minimum->prev;
				//if not at beginning of list
				if(location->prev != nullptr)
				{
					location->prev->next = location;
				}

				//if not at end of list 
				if(location->next != nullptr)
				{
					location->next->prev = location;
				}

				//swap with location
				minimum->next = tempnext;
				minimum->prev = tempprev;
				//if not at beginning of list
				if(tempprev != nullptr)
				{
					tempprev->next = minimum;
				}

				//if not at end of list
				if(tempnext != nullptr)
				{
					tempnext->prev = minimum;
				}
			}

		}
		//increment location one place down
		location = minimum->next;
	}

	return newHead;
}