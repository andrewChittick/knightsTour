//tour.h
//header file for tour.cpp
//2/10/18
//Andrew Chittick

#ifndef TOUR_H_EXISTS
#define TOUR_H_EXISTS

#include <iostream>
#include <cstdlib>
#include <list>

#include "tour.h"

using namespace std;

class Tour{
	public:
		Tour();
		int* takeTour(int position);
		void setValidMoves();
		void setRowColumn(int index);
		int* moveValid(int tRow, int tCol);
		int nextMove();
		int altMove(int past[]);
	private:
		struct boardState{
			int board[8][8];
			int moveNumber;
			int movesAvailable;
			int validMoves[8];
			int cRow;
			int cColumn;
			int movesMade[8];
		};
		boardState current;
		int row;
		int column;
};

#endif
