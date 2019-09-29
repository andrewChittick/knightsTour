//user.cpp
//Andrew Chittick
//2/10/18
//contains menus, and user interactons
//gets all user input
//including starting positions

#include "user.h"

using namespace std;

User::User(){
	User::position = (0);//set default position
}//end default constructor


void User::welcome(){//Welcomes/explains program to user and shows a chess board with positions

	cout << ("Welcome to Knight's Tour") << endl;
	cout << ("You will input starting positions for a knight on a chess board") << endl;
	cout << ("Below is a chess board representation of the starting positions") << endl;

	//print a chess board with starting position 0-63
	int number = 0;
	for (int r=0; r<8; r++){
		for (int c=0; c<8; c++){
			cout.width(4);
			cout << number;
			number++;
		}
		cout << endl;
	}
}//no longer welcome


void User::menu(){//main menu
	cout << ("Would you like to...") << endl;
	cout << ("1. Begin Knight's Tour") << endl;
	cout << ("2. Add a starting position") << endl;
	cout << ("3. Modify a starting position") << endl;
	cout << ("4. Delete a starting position") << endl;
	cout << ("5. Exit") << endl;
	cout << ("Your choice (1-5):  ");
}//end menu()


void User::setPosition(){//asks user for a starting position and verifies
	//ask for users input
	cout << ("Please choose a starting position for the knight (0-63):  ") << endl;
	getline(cin, posString);//get input
	startPos = atoi(posString.c_str());//convert input into int

	if (startPos<64){//not too big
		if (startPos > (-1)){//not too small
			position = startPos;//data verified
		}
	}
	else{
		position = 0;//default(bad input/user)
	}
}//end setPosition()

int User::getPosition(){
	return (position);
}//end getPosition()


void User::setPosChoice(int count){
	bool keepGoing = true;

	while (keepGoing == true){
		cout << ("Your choice (1-") << count << ("):  ");
		getline(cin, posChoiceString);//get input
		posChoice = atoi(posChoiceString.c_str());//convert userPosString into an int

		if (posChoice > count){
			cout << ("Invalid choice, try again.") << endl;
		}
		else if (posChoice < 1){
			cout << ("Invalid choice, try again.") << endl;
		}
		else{
			posChoice = (posChoice);
			keepGoing = false;
		}
	}//end while
}//end setCount()


int User::getPosChoice(){
	return (posChoice);
}//end getCount()
