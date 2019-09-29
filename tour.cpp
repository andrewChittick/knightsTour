//tour.cpp
//2/10/18
//Andrew Chittick
//contains a doubly linked list of boardstates
//boardstate contains all the data for each 
//move made on the knights tour


#include "tour.h"

using namespace std;

Tour::Tour(){
	//reset the current boardState
	for(int i=0; i<8; i++){//rows
		for(int j=0; j<8; j++){//columns
			current.board[i][j] = (-1);
		}
		current.validMoves[i]=0;
		current.movesMade[i]=0;
	}
	current.moveNumber = 0;
	current.movesAvailable = 0;
	current.cRow=0;
	current.cColumn=0;

	row=0;
	column=0;
}//end constructor


//repeats until tour is finished then displays solution
//makes each move then stores the boardState before
//making another move
//backtracks if a dead end is reached before completion
int* Tour::takeTour(int position){ 

	//initialize local variables
	int nextMoveIndex;
	int pastMovesMade[8];
	int sumIndexes = 0;


	//adjust/store starting position
	row = (position / 8);
	column = (position % 8);

	//initialize a doubly linked list (knightTour) of boardState(s)
	list <boardState> knightTour;
	knightTour.push_back(current);

	//set starting position
	current.board[row][column]=current.moveNumber;
	current.moveNumber++;
	current.cRow=row;
	current.cColumn=column;
	setValidMoves();
	//save initial position to knightTour list of boardState(s)
	knightTour.push_back(current);
	//start the tour
	//while move< 64(tour finished)
	while(current.moveNumber<64){

		setValidMoves();//see valid moves
		//get next move
		nextMoveIndex = nextMove();

		if (nextMoveIndex == 187){//fail
			//backtrack until more paths available
			do{
				//initialize pastMovesMade and sumIndexes
				//gives an array of previously tried moves
				//and the sum of those moves
				sumIndexes = 0;
				for (int i=0; i<8; i++){
					pastMovesMade[i]=current.movesMade[i];
					sumIndexes = sumIndexes + pastMovesMade[i];
				}
				//delete last boardstate from list
				knightTour.pop_back();
				//roll back one element
				current = knightTour.back();
				row = current.cRow;
				column = current.cColumn;
			}while(current.movesAvailable <= sumIndexes);

			//update current.movesMade
			for (int i=0; i<8; i++){
				current.movesMade[i]=pastMovesMade[i];
			}
			//make an alternative move
			nextMoveIndex = altMove(pastMovesMade);
		}

		else{//nextMoveIndex valid
			//reset it
			for (int i=0; i<8; i++){
				current.movesMade[i]=0;
			}
		}
		//next move index valid
		//count the move being made
		current.movesMade[nextMoveIndex]=1;
		setRowColumn(nextMoveIndex);
		//set new position
		current.cRow=row;
		current.cColumn=column;
		//make a move
		current.board[row][column]=current.moveNumber;
		//count it
		current.moveNumber++;
		//update valid moves
		setValidMoves();
		//save it
		knightTour.push_back(current);
	}//end while (tour over)
	
	//display/save solution
	int counter = 0;
	int *solution = new int[64];
	current = knightTour.back();
	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++){
			cout.width(4);
			cout << current.board[i][j];
			solution[counter] = current.board[i][j];
			counter++;
		}
		cout << endl;
	}
	cout << endl << endl;
	return(solution);
}//end takeTour



void Tour::setValidMoves(){
	//see what moves are valid from the current position
	//saves to current.validMoves array
	//sends to moveValid to add potential moves from that
	//position to current.validMoves array

	int* tempValidMoves = moveValid(row, column);

	//reset current.movesAvailable
	current.movesAvailable=0;
	//set validMoves and movesAvailable
	for (int i=0; i<8; i++){
		current.validMoves[i] = tempValidMoves[i];
		current.movesAvailable=current.movesAvailable+tempValidMoves[i];
	}

	//add the amount of moves available from each
	//valid move to the corresponding position of
	//current.validMoves array
	//finished product:current.validMoves[i]=0-not a valid move
	//		   current.validMoves[i]=1-valid move/dead end
	//		   current.validMoves[i]=2-valid move/1 move from this position
	//		   current.validMoves[i]=8-valid move/all moves but previous valid
	//i=0:(i+2),(j+1); 1:(i+2),(j-1)
	//  2:(i+1),(j+2); 3:(i+1),(j-2)
	//  4:(i-2),(j+1); 5:(i-2),(j-1)
	//  6:(i-1),(j+2); 7:(i-1),(j-2)
	if (current.validMoves[0] == (1)){//move is valid
		//check valid moves from this position
		int* tempValidMoves = moveValid((row+2),(column+1));
		//add sum of tempValidMoves to validMoves[]
		for (int i=0; i<8; i++){
			current.validMoves[0]=current.validMoves[0]+tempValidMoves[i];
		}
	}
	if (current.validMoves[1] == (1)){//move is valid
		//check valid moves from this position
		int* tempValidMoves = moveValid((row+2),(column-1));
		//add sum of tempValidMoves to validMoves[]
		for (int i=0; i<8; i++){
			current.validMoves[1]=current.validMoves[1]+tempValidMoves[i];
		}
	}
	if (current.validMoves[2] == (1)){//move is valid
		//check valid moves from this position
		int* tempValidMoves = moveValid((row+1),(column+2));
		//add sum of tempValidMoves to validMoves[]
		for (int i=0; i<8; i++){
			current.validMoves[2]=current.validMoves[2]+tempValidMoves[i];
		}
	}
	if (current.validMoves[3] == (1)){//move is valid
		//check valid moves from this position
		int* tempValidMoves = moveValid((row+1),(column-2));
		//add sum of tempValidMoves to validMoves[]
		for (int i=0; i<8; i++){
			current.validMoves[3]=current.validMoves[3]+tempValidMoves[i];
		}
	}
	if (current.validMoves[4] == (1)){//move is valid
		//check valid moves from this position
		int* tempValidMoves = moveValid((row-2),(column+1));
		//add sum of tempValidMoves to validMoves[]
		for (int i=0; i<8; i++){
			current.validMoves[4]=current.validMoves[4]+tempValidMoves[i];
		}
	}
	if (current.validMoves[5] == (1)){//move is valid
		//check valid moves from this position
		int* tempValidMoves = moveValid((row-2),(column-1));
		//add sum of tempValidMoves to validMoves[]
		for (int i=0; i<8; i++){
			current.validMoves[5]=current.validMoves[5]+tempValidMoves[i];
		}
	}
	if (current.validMoves[6] == (1)){//move is valid
		//check valid moves from this position
		int* tempValidMoves = moveValid((row-1),(column+2));
		//add sum of tempValidMoves to validMoves[]
		for (int i=0; i<8; i++){
			current.validMoves[6]=current.validMoves[6]+tempValidMoves[i];
		}
	}
	if (current.validMoves[7] == (1)){//move is valid
		//check valid moves from this position
		int* tempValidMoves = moveValid((row-1),(column-2));
		//add sum of tempValidMoves to validMoves[]
		for (int i=0; i<8; i++){
			current.validMoves[7]=current.validMoves[7]+tempValidMoves[i];
		}
	}//current.validMoves[] all set
}//end setValidMoves()


void Tour::setRowColumn(int index){
	//set new row and column using given index
	switch(index){
		case 0://(i+2),(j+1)
			Tour::row=Tour::row+2;
			Tour::column=Tour::column+1;
			break;
		case 1://(i+2),(j-1)
			Tour::row=Tour::row+2;
			Tour::column=Tour::column-1;
			break;
		case 2://(i+1),(j+2)
			Tour::row=Tour::row+1;
			Tour::column=Tour::column+2;
			break;
		case 3://(i+1),(j-2)
			Tour::row=Tour::row+1;
			Tour::column=Tour::column-2;
			break;
		case 4://(i-2),(j+1)
			Tour::row=Tour::row-2;
			Tour::column=Tour::column+1;
			break;
		case 5://(i-2),(j-1)
			Tour::row=Tour::row-2;
			Tour::column=Tour::column-1;
			break;
		case 6://(i-1),(j+2)
			Tour::row=Tour::row-1;
			Tour::column=Tour::column+2;
			break;
		case 7://(i-1),(j-2)
			Tour::row=Tour::row-1;
			Tour::column=Tour::column-2;
			break;
		default://problems
			cout << ("BIG TROUBLE") << endl;
			break;
	}//end switch
}//end setRowColumn()


//Tour::makeMove()
//returns an array(moves) of 8 positions
//0=move not available
//1=move available
//moves[0]=(i+2),(j+1)
//moves[1]=(i+2),(j-1)
//moves[2]=(i+1),(j+2)
//moves[3]=(i+1),(j-2)
//moves[4]=(i-2),(j+1)
//moves[5]=(i-2),(j-1)
//moves[6]=(i-1),(j+2)
//moves[7]=(i-1),(j-2)
int* Tour::moveValid(int tRow, int tCol){
	//initialize an array of moves available
	int* moves = new int[8];//making moves
	for (int i=0; i<8; i++){
		moves[i]=0;
	}

	if (tRow<6){//row+2 valid
		if (tCol<7){//column+1 valid
			if (current.board[tRow+2][tCol+1] == (-1)){
				moves[0]=1;//(i+2),(j+1)
			}
		}
		if (tCol>0){//column-1 valid
			if (current.board[tRow+2][tCol-1] == (-1)){
				moves[1]=1;//(i+2),(j-1)
			}
		}
	}
	if (tRow<7){//row+1 valid
		if (tCol<6){//column+2 valid
			if (current.board[tRow+1][tCol+2] == (-1)){
				moves[2]=1;//(i+1),(j+2)
			}
		}
		if (tCol>1){//column-2 valid
			if (current.board[tRow+1][tCol-2] == (-1)){
				moves[3]=1;//(i+1),(j-2)
			}
		}
	}
	if (tRow>1){//row-2 valid
		if (tCol<7){//column+1 valid
			if (current.board[tRow-2][tCol+1] == (-1)){
				moves[4]=1;//(i-2),(j+1)
			}
		}
		if (tCol>0){//column-1 valid
			if (current.board[tRow-2][tCol-1] == (-1)){
				moves[5]=1;//(i-2),(j-1)
			}
		}
	}
	if (tRow>0){//row-1 valid
		if (tCol<6){//column+2 valid
			if (current.board[tRow-1][tCol+2] == (-1)){
				moves[6]=1;//(i-1),(j+2)
			}
		}
		if (tCol>1){//column-2 valid
			if (current.board[tRow-1][tCol-2] == (-1)){
				moves[7]=1;//(i-1),(j-2)
			}
		}
	}
	return (moves);
}//end moveValid()


int Tour::nextMove(){//returns index of next move to be made
	//initialize local variables
	int nextMoveIndex;
	int lowMoves=9;

	if (current.movesAvailable == 0){//no moves available
		//backtrack
		nextMoveIndex=187;
	}
	else if (current.movesAvailable == 1){//only 1 possible move
		for (int i=0; i<8; i++){//find available move
			if (current.validMoves[i]>0){
				nextMoveIndex=i;//make move
			}
		}
	}
	else{//multiple moves available
		if (current.moveNumber<32){//w/warnsdoff
			//compare validMoves available
	        	//save fewest exits available to lowMoves
			for (int i=0; i<8; i++){
				if (current.validMoves[i]>0){//move valid
					if (current.validMoves[i]<lowMoves){//fewer exits
						lowMoves=current.validMoves[i];
						nextMoveIndex=i;
					}
				}
			}
		}
		else{//without warnsdoff
			for (int i=0; i<8; i++){
				if (current.validMoves[i]>0){//move valid
					nextMoveIndex=i;
				}//highest valid index saved
			}
		}
	}
	return(nextMoveIndex);
}//end nextMove()


//makes a move opposite of normal(nextMove)
int Tour::altMove(int past[]){//returns index of next alternative move to be made
	//initialize local variable
	int nextMoveIndex = 987;

	for (int i=0; i<8; i++){
		if (past[i]<1){//move hasnt been made yet
			if (current.validMoves[i]>0){//move valid
				nextMoveIndex = i;
			}
		}
	}
	return(nextMoveIndex);
}//end altMove()
