//============================================================================
// Name        : Jacinta Moore
// Description : Assignment 1: Implementation of the game "Going to Boston" with
//               auto simulation of betting turned on
//============================================================================
#define AUTO_GET
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
// function for creating a random dice role
	int role() {return rand()%6+1; }

	int main() {

// allowance for betting
		int my_bank = 1000; int comp_bank=1000;
// function to generate random seeded numbers
		srand (time(0));
//Variable to count how many times the while loop rounds (i.e the round in the game)
 	 	 int counter = 0;
//While loop which sets up the game and conditions
		while (true) {

//counter to define which round in the game that it is
			 ++counter;
//variables for each role of the dice. A die is thrown a total of 6 times or 6 different roles.
// 3 dice are thrown in the first round (a,b,c). 2 dice are thrown in the second round (d,e) and one dice is thrown in the last round (f).
			int a, b, c, d, e, f;
				a = role();
				b = role();
				c = role();
				d = role();
				e = role();
				f = role();
//Variables for the computer dice throws. Same as for user except labeled with 'c' for computer
			int ca, cb, cc, cd, ce, cf;
				ca = role();
				cb = role();
				cc = role();
				cd = role();
				ce = role();
				cf = role();

//Output to the user showing the results of the two dice throws for him/her and for the computer and asking for a bet value
	cout << "[Round " << counter << "]" << "  You rolled (" << a << "," << b << ",?), machine rolled (" << ca << "," << cb << ",?)..." << endl;

//Inputting the bet value and checking that it is between the allowed $1 to 10.
			int bet;
#ifndef AUTO_GET
			cout << "How much are you going to bet: ";
			while (true) {
				cin >> bet;
				int high = 10; int low = 0;
											if ((bet <= low) || (bet > high))
											{cout << "- your bet must between $1 and $10, type again:";
											continue;}
											break;}

//Auto simulation
#else
							if (ca==cb) {
								bet= 1;}
							else if (a==b) {
								bet = 10;}
							else bet = rand()%5+1;
							cout << "Bet value is.." << bet << endl;
#endif
//find the maximum values of the dice for the players roles
			int max_role1 = (a<b?(b<c?c:b):(a<c?c:a));
			int max_role2 = ((d<e)?e:d);
			int score = max_role1 + max_role2 + f;

//find the maximum values of the dice for the computer roles
			int comp_max_role1 = (ca<cb?(cb<cc?cc:cb):(ca<cc?cc:ca));
			int comp_max_role2 = ((cd<ce)?ce:cd);
			int cscore = comp_max_role1 + comp_max_role2 + cf;

// If function to check if both players got "Big Fish"
			if( ((ca == cb) && (cb==cc)) && (a ==b) && (b ==c)) {
				cout << "Both got Big Fish : Tie!!" << endl<<endl;
			continue;
			}
//If function to check if player got "Big Fish" and computer didn't and then calculate the win
			if ( ((a == b) && (b==c)) && (ca!=cb) && (cb!=cc)) {
				cout << "You had (" << a <<", "<<b<<", "<< c<<")...Big Fish!!!" << endl;
				cout << "Machine had ("<<ca<<", " <<cb<< ", "<<cc<<")"<< "-> Machine rolled ("<<cd<<" ,"<<ce<<") and then rolled ("<<cf<<") -> Machine scored " <<cscore<<"."<<endl;
				my_bank += bet * 50;
				comp_bank -= bet *50;
				cout << "You won :) You have $" << my_bank << ", machine has $" << comp_bank <<"..."<< endl <<endl;
				if (comp_bank<=0)break;
				continue;
			}
//If function to check if computer got "Big Fish" but player didnt and then calculate the loss
			if ((ca == cb) && (cb==cc)) {
				cout << "Machine had (" << ca <<", "<<cb<<", "<<cc<<")...Big Fish!!!" << endl;
				cout << "You had ("<<a<<", " <<b<< ", "<<c<<")"<< "-> You rolled ("<<d<<" ,"<<e<<") and then rolled ("<<f<<") -> You scored " <<score<<"."<<endl;
				my_bank -= bet * 50;
				comp_bank += bet *50;
				cout << "You lost :( You have $" << my_bank << ", machine has $" << comp_bank <<"..."<< endl <<endl;
				if (my_bank<=0)break;
				continue;
			}
//If function to check if there is a tie where both the total amount of dice rolls for
// the player and computer are equal
			if (score == cscore) {
				cout << "Tied Game!" << endl;
				cout << "You had ("<<a<<", " <<b<< ", "<<c<<")"<<" -> You rolled ("<<d<<" ,"<<e<<") and then rolled ("<<f<<") -> You scored " <<score<<"."<<endl;
				cout << "Machine had ("<<ca<<", " <<cb<< ", "<<cc<<")"<<" -> Machine rolled ("<<cd<<" ,"<<ce<<") and then rolled ("<<cf<<") -> Machine scored " <<cscore<<"."<<endl;
				continue;
			}
//If function to check whether the player has won from the total scored from the 3 rolls of dice
			if (score > cscore) {
				cout << "You had ("<<a<<", " <<b<< ", "<<c<<")"<< " -> You rolled ("<<d<<" ,"<<e<<") and then rolled ("<<f<<") -> You scored " <<score<<"."<<endl;
				cout << "Machine had ("<<ca<<", " <<cb<< ", "<<cc<<")"<<" -> Machine rolled ("<<cd<<" ,"<<ce<<") and then rolled ("<<cf<<") -> Machine scored " <<cscore<<"."<<endl;
				my_bank += bet * (score - cscore);
				comp_bank -= bet *(score - cscore);
				cout << "You won :) You have $" << my_bank << ", machine has $" << comp_bank << "..."<< endl<<endl;
				if (my_bank<=0)break;
				continue;
			}
//If function to check whether player has loss from the total scored from the 3 dice rolls
			if (cscore > score){
				cout << "You had ("<<a<<", " <<b<< ", "<<c<<")"<<" -> You rolled ("<<d<<" ,"<<e<<") and then rolled ("<<f<<") -> You scored " <<score<<"."<<endl;
				cout << "Machine had ("<<ca<<", " <<cb<< ", "<<cc<<")"<<" -> Machine rolled ("<<cd<<" ,"<<ce<<") and then rolled ("<<cf<<") -> Machine scored " <<cscore<<"."<<endl;
				my_bank -= bet * (cscore - score);
				comp_bank += bet *(cscore - score);
				cout << "You lost :( You have $" << my_bank << ", machine has $" << comp_bank << "..."<< endl<<endl;
				if (comp_bank<=0) break;
				continue;
			}
		}
		cout<< (comp_bank<=0? "Game Over...You Win!!" : "Game Over...Machine Win!!") <<endl;

		return 0;
	}
