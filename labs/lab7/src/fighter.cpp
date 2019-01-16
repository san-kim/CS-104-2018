#include "fighter.h"

using namespace std;

Fighter::Fighter(string name) : Player(name) //calls Player constructor
{
	
}

void Fighter::doAction(Player* target)
{
	int health = target->getHP() - 75;
	target->setHP(health);
}