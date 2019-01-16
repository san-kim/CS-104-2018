#include "inventory.h"
#include <iostream>

using namespace std;

Inventory::Inventory()
{

}

/* Add an item to the inventory with the given name and amount. */
void Inventory::addItem(string itemname, int itemamount)
{
	for(int i = 0; i<(int)size(); i++)
	{
		if(at(i).name == itemname)
		{
			at(i).amount += itemamount;
			return;
		}
	}

	push_back(Item(itemname, itemamount));
}

/* Remove all items with this name from the inventory 
   while preserving the order of other items in the inventory.*/
void Inventory::removeItem(string targetItem)
{
	for(int i = 0; i < (int)size(); i++)
	{
		//find item with the name
		if(at(i).name == targetItem)
		{
			//from that element onwards "shift everything left" except for last
			for(int j = i; j < (int)size()-1; j++)
			{
				at(j).name = at(j+1).name;
				at(j).amount = at(j+1).amount;
			}
			//pop last element
			pop_back();
		}
	}
}
	
/* Return the number of items with this name from the inventory. */
int Inventory::getNumItems(string targetItem)
{
	for(int i = 0; i<(int)size(); i++)
	{
		if(at(i).name == targetItem)
		{
			return at(i).amount;
		}
	}
	return -1;
}

/* Print all the items in this format:
	name amount
	name amount
	name amount
*/
void Inventory::printAllItems()
{
	for(int i = 0; i<(int)size(); i++)
	{
		cout << at(i).name << " " << at(i).amount << endl;
	}
}