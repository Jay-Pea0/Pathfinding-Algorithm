#include "bots.h"
#include "stdlib.h"
// Included for testing purposes
#include<iostream>
using namespace std;

void cDijkstra::Build(cBotBase &bot)
{
	//Initialize given data arrays
	for (int col = 0; col < GRIDWIDTH; col++)
	{
		for (int row = 0; row < GRIDHEIGHT; row++)
		{
			closed[col][row] = false;
			cost[col][row] = 999;
			linkX[col][row] = -5;
			linkY[col][row] = -4;
			inPath[col][row] = false;
		}
	}


	// Set bot's position to cost 0
	cost[bot.PositionX()][bot.PositionY()] = 0;
	
	

	// Create array to store the smallest X and Y coordinates
	// Runs until it closes the position the player is in

	while (!closed[gTarget.PositionX()][gTarget.PositionY()])
	{
		// Finds the coordinates of the smallest costing open square on the grid, and closes it

		// Start values for smallest X and y coordinates
		// Doesn't matter where starts, because since it goes through the whole grid, it'll be overwritten
		int SmallestX = 0;
		int SmallestY = 0;

		// For each column for each row, check to find lowest cost, that's not closed, and not blocked
		for (int col = 0; col < GRIDWIDTH; col++)
		{

			for (int row = 0; row < GRIDHEIGHT; row++)
			{
				if ((cost[col][row] < cost[SmallestX][SmallestY]) and (closed[col][row] == false) and (gLevel.isValid(col, row)))
				{
					SmallestX = col;
					SmallestY = row;
				}
			}
		}

		// Close Current Space
		closed[SmallestX][SmallestY] = true;


		// Hozizontal and Vertical Changes
		// +1 X
		ChangeCost(1, SmallestX, SmallestY, 1, 0);
		// -1 X
		ChangeCost(1, SmallestX, SmallestY, (-1), 0);
		// +1 Y
		ChangeCost(1, SmallestX, SmallestY, 0, 1);
		// -1 Y
		ChangeCost(1, SmallestX, SmallestY, 0, (-1));


		// Diagonal Changes
		// +1 X, +1 Y
		ChangeCost(1.4, SmallestX, SmallestY, 1, 1);
		// +1 X, -1 Y
		ChangeCost(1.4, SmallestX, SmallestY, 1, (-1));
		// -1 X, +1 Y
		ChangeCost(1.4, SmallestX, SmallestY, (-1), 1);
		// -1 X, -1 Y
		ChangeCost(1.4, SmallestX, SmallestY, (-1), (-1));
	}

	// Find the path back to starting position
	// Will be set to true when we are back at the bot position
	bool done = false;
	// Start of path
	int nextClosedX = gTarget.PositionX();
	int nextClosedY = gTarget.PositionY();
	while (!done)
	{
		// Adds current Co-ordinates to the path
		inPath[nextClosedX][nextClosedY] = true;
		// Sets integers to XY of just added co-ordinate
		int tmpX = nextClosedX;
		int tmpY = nextClosedY;
		// New X and Y of path = linkX and linkY of last X and Y
		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];

		// If next X and Y = bot position, set done to true (ending the loop)
		if ((nextClosedX == bot.PositionX()) && (nextClosedY == bot.PositionY())) done = true;
	}
	completed = true;

}

// Funtion to change the cost of locations in array
void cDijkstra::ChangeCost(float ChangeInCost, int SmallX, int SmallY, int ChangeX, int ChangeY)
{
	int XOfChange = SmallX + ChangeX;
	int YOfChange = SmallY + ChangeY;

	//Ifs are seperated for testing purposes
	// If the coordinates aren't closed
	if (closed[XOfChange][YOfChange] == false)
	{
		// If the coodinates are valid
		if (gLevel.isValid((XOfChange), (YOfChange)))
		{
			// If the potential cost is lower than the current cost
			if ((cost[XOfChange][YOfChange]) > (cost[SmallX][SmallY] + 1))
			{

				// Set linkX and linkY
				linkX[XOfChange][YOfChange] = SmallX;
				linkY[XOfChange][YOfChange] = SmallY;

				// Set new cost
				cost[XOfChange][YOfChange] = (cost[SmallX][SmallY] + ChangeInCost);
			}
		}
	}
}

// Create global object of type cDijkstra
cDijkstra gDijkstra;




