#include "circular_list_int.h"

	// standard no-argument constructor
	CircularListInt::CircularListInt()
	{

	}

	// Destructor. Should delete all data allocated by the list. 
	CircularListInt::~CircularListInt()
	{		
		//because count will change as we run remove

		while(count > 0)
		{
			//deletes everything, resets head, and decrements count
			remove(count-1);
		}
	}

	// Finds the pointer to an item at the given index.
	// Handles wrapping the index around if it is ?= the size of the list.
	// Assumes that the size of the list is not 0.
	CircularListInt::Item* CircularListInt::findItem(size_t index) const
	{
		index = index%count;
		Item* location = head;
		for(int i = 0; i<(int)index; i++)
		{
			location = location->next;
		}
		return location;
	}

	// Gets item at an index.
	//If an index is passed that is larger then the number of items in the list,
	// it should "wrap around" back to the first element.
	// If there are no elements in the list, returns 0.
	int CircularListInt::get(size_t index) const
	{
		if(count == 0)
		{
			return 0;
		}

		//if head 
		if(index%count == 0)
		{
			return head->value;
		}

		//if last element
		if(index%count == count-1)
		{
			return head->prev->value;
		}

		Item* location = findItem(index);
		return location->value;
	}

	// get length of list.
	size_t CircularListInt::size() const
	{
		return count;
	}

	// returns true iff the list is empty.
	bool CircularListInt::empty() const
	{
		if(count == 0)
		{
			return true;
		}

		return false;
	}

	// Inserts (a copy of) the given item at the end of list.
	void CircularListInt::push_back(int value)
	{
		Item* newItem = new Item(value);

		// if empty
		if(count == 0)
		{
			head = newItem;
			head->next = head;
			head->prev = head;
			count++;
			return;
		}

		// location is at the last current element
		// location = head if one element, works for if one element
		Item* location = head->prev;
		//make a new item prev and next pointers
		newItem->prev = location;
		newItem->next = head;

		//update prev and net pointers of items around them
		head->prev = newItem;
		location->next = newItem;

		count++;
	}

	// Sets the item at the given index to have the given value.
	// If an index is passed that is >= the number of items in the list, it 
	//should "wrap around" back to the first element.
	void CircularListInt::set(size_t index, int value)
	{
		if(count == 0)
		{
			return; 
		}

		//gives you the location that you want to set
		Item* setLocation = findItem(index);
		setLocation->value = value;
	}

	// Removes the item at the given index from the list.
	// List elements after the removed element are pulled forward, so their 
	// indicies decrease by one.
	// If an index is passed that is larger then the number of items in the
	// list, it should "wrap around" back to the first element.
	void CircularListInt::remove(size_t index)
	{

		if(count == 0)
		{
			return;
		}

		if(count == 1)
		{
			delete head;
			head = nullptr;
			count = 0;
			return;
		}

		//if it is the last element and more than 1 element
		if(index%count == count-1)
		{
			Item* lastElement = head->prev;
			lastElement->next->prev = lastElement->prev;
			lastElement->prev->next = lastElement->next;

			delete lastElement;
			count--;
			return;
		}

		//if it is not at front or back and size > 1
		Item* removeLocation = findItem(index);

		if(removeLocation == head)
		{
			head = removeLocation->next;
		}

		//sets the one after's prev to equal this location's prev
		removeLocation->next->prev = removeLocation->prev;
		removeLocation->prev->next = removeLocation->next;

		delete removeLocation;

		count--;
	}