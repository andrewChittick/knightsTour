//main.cpp
//2/10/18
//Andrew Chittick
//knights tour program
//main along with user
//takes a list of starting positions from the user
//allows user to add/delete/modify this list
//sends to tour which completes the knights tour for each
//starting position
//a knights tour is the knight traveling to every
//space on a chess board without visiting the 
//same space twice


#include <iostream>
#include <forward_list>
#include <string>
#include <cstdlib>
#include <fstream>

#include "user.h"
#include "tour.h"

using namespace std;

int main(){//start main

	//initialize function(s)
	int startingPositions(forward_list<int> userList, forward_list<int>::iterator userListIT);

	//initialize variables
	bool keepGoing = true;
	int count;
	string choiceString;
	int choice;
	int modPos;

	//initialize a singly linked list to store 
	//users starting position inputs
	forward_list <int> userList;
	forward_list <int>::iterator userListIT;
	userListIT = userList.begin();

	//create an instance of User(xput(input/output))
	//Class User contains user interaction methods
	User xput;

	//start
	xput.welcome();//show welcome menu

	xput.setPosition();//get the users initial starting position
	//store that verified position in the singly linked list(userList)
	userList.push_front(xput.getPosition());

	//open a file for output
	fstream myFile;
       	myFile.open("knightsTourOutput.dat", ios::out);
	bool fileOpen;
	if (myFile.is_open()){
		fileOpen = true;
	}
	else{
		cout << ("Unable to open file.") << endl;
		fileOpen = false;
	}

	while (keepGoing == true){//take users input until they select begin tour or exit

		//display the users starting positions(numbered), returns count
		count = startingPositions(userList, userListIT);
		xput.menu();//show main menu
		getline(cin, choiceString);//get choice
		choice = atoi(choiceString.c_str());//convert it to an int

		switch(choice){//menu options

			case 1://Begin Tour
				if (fileOpen == true){//file opened
					//iterate thru userList
					cout << endl << ("Solutions...") << endl;
					myFile << ("Knights Tour Solutions") << endl << endl;
					for (userListIT=userList.begin(); userListIT!= userList.end(); userListIT++){
						cout << ("Starting Position: ") << *userListIT << endl << endl;
						myFile << ("Starting Position: ") << *userListIT << endl << endl;
						Tour knightTour;
						int* solution = knightTour.takeTour(*userListIT);//solve

						//write solution to file
						for (int i=0; i<64; i++){
							myFile.width(4);
							myFile << solution[i];
							if ((i+1)%8==0){
								myFile << endl;
							}
						}
						myFile << endl << endl;
						delete solution;
					}
				}
				else{//file unable to open  
					cout << ("No output file.") << endl;
					//iterate thru userList
					cout << endl << ("Solutions...") << endl;
					for (userListIT=userList.begin(); userListIT!= userList.end(); userListIT++){
						cout << ("Starting Position: ") << *userListIT << endl << endl;
						Tour knightTour;
						knightTour.takeTour(*userListIT);//solve
					}
				}
				keepGoing = false;
				break;
			case 2://Add starting position
				xput.setPosition();//set users new position
				userList.push_front(xput.getPosition());//store it in the list
				break;
			case 3://Modify starting position
				count = startingPositions(userList, userListIT);//display positions
				cout << ("Select position to modify") << endl;
				xput.setPosChoice(count);//set position to modify
				modPos = xput.getPosChoice();//get position
				xput.setPosition();//modify to...

				if (modPos == 1){//front element
					userList.pop_front();//delete it
					userList.push_front(xput.getPosition());//add new front element
				}
				else{
					userListIT = userList.begin();//reset iterator
					for (int i=0; i<(modPos-2); i++){//move iterator before node to be modified(and adjust for 0) 
						userListIT++;
					}
					//add new position
					userListIT = userList.insert_after (userListIT, xput.getPosition());//add it
					userListIT = userList.erase_after(userListIT);//delete old position
				}
				cout << ("modified") << endl;
				break;
			case 4://Delete starting position
				count = startingPositions(userList, userListIT);//display positions
				cout << ("Select position to delete") << endl;
				xput.setPosChoice(count);//set position to delete
				modPos = xput.getPosChoice();//get position

				if (modPos == 1){//front element
					userList.pop_front();//delete it
				}
				else{
					userListIT = userList.begin();//reset iterator
					for (int i=0; i<(modPos-2); i++){//move iterator before node to be deleted(and adjust for 0) 
						userListIT++;
					}
					userListIT = userList.erase_after(userListIT);//delete the position
				}
				cout << ("deleted") << endl;
				break;
			case 5://exit
				cout << ("goodbye") << endl;
				keepGoing = false;
				break;
			default:
				cout << ("invalid response") << endl;
				break;
		}//end switch
	}//end while
	
	myFile.close();//close file

	return(0);
}//end main

//displays the users starting position(numbered), and returns the total number of starting positions
int startingPositions(forward_list<int> userList, forward_list<int>::iterator userListIT){
	int count = 1;
	cout << ("Your chosen starting positions") << endl;
	for (userListIT = userList.begin(); userListIT != userList.end(); userListIT++){
		cout << count << ". ";
		cout << *userListIT << endl;
		count++;
	}
	count--;//adjust count
	return(count);//returns number of positions
}//end startingPositions()
