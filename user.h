//user.h
//header file for user.cpp
//Andrew Chittick
//2/10/18

#ifndef USER_H_EXISTS
#define USER_H_EXISTS

#include <iostream>
#include <cstdlib>
#include "user.h"

using namespace std;

class User{
	public:
		User();
		void welcome();
		void menu();
		int getPosition();
		void setPosition();
		int getPosChoice();
		void setPosChoice(int count);


	private:
		int position;
		string posString;
		int startPos;
		string posChoiceString;
		int posChoice;
};

#endif
