#include "stackint.h"
using namespace std;

StackInt::StackInt()
{

} 

StackInt::~StackInt()
{
	while(!list.empty())
	{
		pop();
	}
}

/**
* Returns true if the stack is empty, false otherwise
*/
bool StackInt::empty() const
{
	//O(1) operation as it just checks whether count == 0
	return list.empty();
}

/**
* Pushes a new value, val, onto the top of the stack
*/
void StackInt::push(const int& val)
{
	//push_back() in circular_list_int is a O(1) operation
	list.push_back(val);
}

/**
* Returns the top value on the stack
*/
int StackInt::top() const
{
	//if empty
  	if(list.empty())
  	{
  		//error case ?
  		return -100;
  	}

  	//returns the top value of the stack in constant time
  	return list.get(list.size()-1);
}

/**
* Removes the top element on the stack
*/
void StackInt::pop()
{
  	//if empty do nothing
  	if(list.empty())
  	{
  		return;
	}
		
	//remove is written such that big theta runtime is constant for when size is 1 
	//and when the index is the last element, or count-1
	list.remove(list.size()-1);
}