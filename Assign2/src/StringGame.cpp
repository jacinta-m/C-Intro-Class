//============================================================================
// Name        : Moore2.cpp
// Author      : Jacinta Moore
// Version     :
// Copyright   : Your copyright notice
// Description : Implementation of Assignment 2 : A 7 string typing game where
//				the user has 7 seconds to reproduce the string
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
using namespace std;

int absolute(int ran, int in){// function to return the absolute value
 return abs(ran - in );
 }

int main() {

	srand(time(0));
	int points = 1000;

	while(true){
		if(points <=0){
			cout<< "You lose all your points. Bye..."; break;
		}
		if(points >= 5000){
		cout<<"You win the game. Bye..."; break;
		}

		string randomString = "";
		cout<< "Your current points "<< points<<", just type -> ";
// To generate a 7 character random string
		int len = 7;
		for (int i=0; i< len; ++i){
			int random = rand()%10+1;
			if (random <=4){
				char letter = 'a'+ rand()%26;
				randomString+= letter;
				cout << randomString[i];
			}
			else if (random<=8){
				char capletter = 'A'+ rand()%26;
				randomString+= capletter;
				cout << randomString[i];
			}
			else if (random == 9){
				randomString += '0';
				cout << "[0-9]";
			}
			else{
				randomString+= '*';
				cout << "[%-&]";
			}
		}
		cout<<":";
//Implementation of the timer
		string input;
		chrono::steady_clock::time_point begin = chrono::steady_clock::now();
		cin>> input;
		chrono::steady_clock::time_point end= chrono::steady_clock::now();
		int timer =(chrono::duration_cast<chrono::microseconds>(end - begin).count())/1000;
		int timeallowance = 7000;
		int delay = timer - timeallowance;

// Comparison of the Computer generated string to the User typed in string
		while (randomString.size() != input.size()){
				if (randomString.size() < input.size()){
					randomString += " ";
				}
					else {
						input +=" ";
				}
		}
		int penalty =0;
		int ranlen = randomString.size();
		for (int i=0; i< ranlen; ++i){
			if (randomString[i]=='0'){
				if (!isdigit(input[i])){
					penalty += absolute(randomString[i],input[i]);
				}
			}
			else if (randomString[i]=='*'){
				if(isalnum(input[i])){
					penalty += absolute(randomString[i],input[i]);
				}
			}
			else {
				penalty += absolute(randomString[i],input[i]);
			}
		}
// Calculation of win / loss
		if (penalty == 0 && delay<=0 ){
			cout<< timer<< " milliseconds, you made it within the interval of 7000..." <<endl;
			points += 500;
		}
		else if (penalty==0 && delay>0){
			cout << timer << " milliseconds, you *failed* it within the interval of 7000..."<<endl;
			cout << "You matched correctly, your penalty is "<< delay <<"..."<<endl;
			points -= delay;
		}
		else if(penalty>0 && timer<=timeallowance){
			cout<< timer<< " milliseconds, you made it within the interval of 7000..." <<endl;
			cout<< "String offset is "<< penalty <<", your penalty is "<<penalty<<"..."<<endl;
			points -= penalty;
		}
		else {
			cout<< timer<< " milliseconds, you *failed* it within the interval of 7000..." <<endl;
			cout<< "String offset is "<< penalty<<", your total penalty is "<<(2*penalty +delay)<<"..."<<endl;
			points -= 2*penalty + delay;
		}
		cout<<""<<endl;
	}
return 0;
}
