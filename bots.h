#pragma once
//======================================================================================
//Header file for bots: initially cBotRandom is defined here, but other bot classes
//can go here too
//
//(c) Patrick Dickinson, University of Lincoln, School of Computer Science, 2020
//======================================================================================

#include "botbase.h"
#include<vector>

class cBotRandom : public cBotBase
{
	virtual void ChooseNextGridPosition();
};

class cBotFollowAStar : public cBotBase
{
public:
	virtual void ChooseNextGridPosition();

	// Class Variable (set to false)
	int WhereInVectorPath;
	cBotFollowAStar() { WhereInVectorPath = 0; }
};

class cDijkstra
{
public:

	// Class Arrays
	bool closed[GRIDWIDTH][GRIDHEIGHT]; //whether or not location is closed
	float cost[GRIDWIDTH][GRIDHEIGHT]; //cost value for each location
	int linkX[GRIDWIDTH][GRIDHEIGHT]; //link X coord for each location
	int linkY[GRIDWIDTH][GRIDHEIGHT]; //link Y coord for each location
	bool inPath[GRIDWIDTH][GRIDHEIGHT]; //whether or not a location is in the final path

	// Class Functions
	virtual void Build(cBotBase &bot);
	void ChangeCost(float, int, int, int, int);

	// Class Variable (set to false)
	bool completed;
	cDijkstra() { completed = false; }
};

class cAStar : public cDijkstra
{
public:
	// Class Vector
	 std::vector<int> vectorPath;

	
	// Class Functions
	virtual void Build(cBotBase& bot);
};

// Declares external reference
extern cDijkstra gDijkstra;
extern cAStar gAStar;
