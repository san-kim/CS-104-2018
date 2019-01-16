#include "healer.h"

using namespace std;

Healer::Healer(string name) : Player(name) //calls Player constructor
{
	
}

void Healer::doAction(Player* target)
{
	int health = target->getHP() + 75;
	if(health > target->getMaxHP())
	{
		health = target->getMaxHP();
	}
	target->setHP(health);
}