/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
	found = false;
	initializeVisited();
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << labirinth[i][j] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y) //pior caso - O(n) = n*n
{
	if (found)
		return true;

	if (visited[x][y] || labirinth[x][y] == 0)
			return false;
		else
			visited[x][y] = true;

	if (labirinth[x][y] == 2) {
		found = true;
		return false;
	}

	findGoal(x-1,y);
	findGoal(x+1,y);
	findGoal(x,y-1);
	findGoal(x,y+1);

	return found;
}


