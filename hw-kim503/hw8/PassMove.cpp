#include "Move.h"

/* Constructs a pass move. */
PassMove::PassMove(Player * player) : Move(player)
{

}

PassMove::~PassMove()
{

}


/* Executes this move, whichever type it is.
	This may throw exceptions; students: it's up to you to
	decide (and document) what exactly it throws*/
void PassMove::execute(Board & board, Bag & bag, Dictionary & dictionary)
{
	//nothing to be done when passed
}