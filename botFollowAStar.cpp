#include "bots.h"
#include "stdlib.h"

// Included for testing purposes
#include<iostream>
using namespace std;

void cBotFollowAStar::ChooseNextGridPosition()
{


	if (WhereInVectorPath != 0)
	{
		SetNext((gAStar.vectorPath[WhereInVectorPath]), (gAStar.vectorPath[WhereInVectorPath]), gLevel);
		WhereInVectorPath += 2;
	}
	
	if (WhereInVectorPath >= gAStar.vectorPath.size())
	{
		WhereInVectorPath = 0;
	}
}
