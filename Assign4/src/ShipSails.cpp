//============================================================================
// Name        : Moore4.cpp
// Author      : Jacinta Moore
// Version     :
// Copyright   : Your copyright notice
// Description : Implementation of Assignment #4, which is the card game
//				 My Ship Sails
//============================================================================

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <string>
#include <iomanip>

using namespace std;

class Card{
public:
	char m_suit;
	int m_face;
	Card(const char s='S', const int n=0): m_suit(s), m_face(n){}
	friend ostream& operator<<(ostream&, const Card&);
};

ostream& operator<<(ostream& o, const Card& c){
	o<<c.m_suit;
	switch(c.m_face){
	case 1: o<<'A'; break;
	case 11: o<<'J'; break;
	case 12: o<<'Q'; break;
	case 13: o<< 'K';break;
	default: o<<c.m_face;
	}
	return o;
}
class Player {
private:
	int m_name;
	vector<Card> m_deck;
public:
	Player(const int& n): m_name(n) {m_deck.reserve(7);}
	void push_back(const Card& c) {m_deck.push_back(c);}
	friend ostream& operator<<(ostream& o, const Player& p);

	int check(vector<Player>& players){
		vector<int>counter(4);
		int win = 1;
		for(int i=0, len=m_deck.size(); i<len; i++){
			if (m_deck[i].m_suit =='S') {counter[0]++;}
			if (m_deck[i].m_suit =='C') {counter[1]++;}
			if (m_deck[i].m_suit =='D') {counter[2]++;}
			if (m_deck[i].m_suit =='H') {counter[3]++;}
		}
		for(int i=0,len=counter.size(); i<len;++i){
			if (counter[i]==7){
				win = 2;
				}
			}
		return win;
	}

	Card User(vector<Player>& players, const char& choice){
		Card temp0;
		switch(choice){
		case 'a': temp0=m_deck[0]; swap(m_deck[0],m_deck[m_deck.size()-1]); m_deck.pop_back();break;
		case 'b': temp0=m_deck[1]; swap(m_deck[1],m_deck[m_deck.size()-1]); m_deck.pop_back();break;
		case 'c': temp0=m_deck[2]; swap(m_deck[2],m_deck[m_deck.size()-1]); m_deck.pop_back();break;
		case 'd': temp0=m_deck[3]; swap(m_deck[3],m_deck[m_deck.size()-1]); m_deck.pop_back();break;
		case 'e': temp0=m_deck[4]; swap(m_deck[4],m_deck[m_deck.size()-1]); m_deck.pop_back();break;
		case 'f': temp0=m_deck[5]; swap(m_deck[5],m_deck[m_deck.size()-1]); m_deck.pop_back();break;
		case 'g': temp0=m_deck[6]; swap(m_deck[6],m_deck[m_deck.size()-1]); m_deck.pop_back();break;
		}
		return temp0;
	}

	Card Removes(vector<Player>& players){
		vector<int>count(4);
		for(int i=0, len=m_deck.size();i<len; i++){
			if (m_deck[i].m_suit =='S') {count[0]++;}
			if (m_deck[i].m_suit =='C') {count[1]++;}
			if (m_deck[i].m_suit =='D') {count[2]++;}
			if (m_deck[i].m_suit =='H') {count[3]++;}
		}
		int min = 10;
		char type = 10;
		for(int i=0, len=count.size();i<len; i++){
			if(count[i]!=0 && count[i]<min){
				min = count[i];
				type = i;
			}
		}
		switch(type){
		case 0: type ='S'; break;
		case 1: type ='C'; break;
		case 2: type ='D'; break;
		case 3: type ='H';break;
		}
		Card temp;
		for(int i =0, len=m_deck.size(); i<len; ++i){
			if(m_deck[i].m_suit==type){
				temp = m_deck[i];
				swap(m_deck[i], m_deck[m_deck.size()-1]);
				m_deck.pop_back();
				break;
			}
		}
		count.clear();
		return temp;
	}
	void Move(vector<Player>& players, const Card& d){
		m_deck.push_back(d);}
	void Print(vector <Player>& players){
		for(int i=0, len=m_deck.size(); i<len; ++i){
			char choice = 'a' +i;
			cout <<setw(8)<< "("<< choice<<")"<<setw(2)<<m_deck[i]<< " ";
		}
		cout<<endl<<endl;
	}
};

ostream& operator<<(ostream& o, const Player& p) {
	o<< "Player: " << p.m_name << " has ";
	for(int i =0, len = p.m_deck.size(); i< len; ++i){
		char choice = 'a'+i;
		o <<setw(8)<< "("<< choice<<")"<<setw(2)<< p.m_deck[i]<< " ";
	}
	return o;
}

int main() {
	srand(time(0));
	vector<Card> deck;deck.reserve(52);
	for (int i=1; i<=13; ++i){ deck.push_back(Card('S',i));}
	for (int i=1; i<=13; ++i) {deck.push_back(Card('H',i));}
	for (int i=1; i<=13; ++i) {deck.push_back(Card('C',i));}
	for (int i=1; i<=13; ++i) {deck.push_back(Card('D',i));}
	random_shuffle(deck.begin(), deck.end());
//Dealing 7 cards to 5 Players
	vector<Player>players;
	for (int i=0; i<5; ++i){
	players.push_back(Player(i));}
	for(int i =0, len=players.size();i<len;++i){
		for(int j=0; j<7;++j){
			Card c= deck.back();
			players[i].push_back(c);
			deck.pop_back();
		}
	}
	while(true){
//Checking for the winner
		vector<int> winner;
		bool win = false;
		for(int i =0, len=players.size();i<len;++i){
			int wins = players[i].check(players);
			winner.push_back(wins);}
		for(int i =0, len=winner.size(); i<len;++i){
				 if(winner[i]==2){
				 cout<< "My Ship Sails! -- Player "<<i<< " Won..."<<endl;
				 win = true;}
		}
		if (win == true){break;}
//Asking the user which card to pass and passing it to the next player
		players[0].Print(players);
		char choice;
		while(true){
			cout<<"Which one to replace? ";
			cin>>choice;
			if (choice >='a'&& choice <='g'){cout<<endl;break;}
			if(choice=='?'){
				for(int i =1, len=players.size();i<len;++i){
					cout<<players[i]<<endl;
				}
			}
			else {cout<<"Wrong Input!";}
		}
		Card d = players[0].User(players,choice);
		cout<< "Hint:"<<" Player "<<0<<" passed "<< d << " to player "<<1<<endl;
		players[1].Move(players,d);
//Card Passing amongst other Players
		for (int i=1; i<5; ++i){
			Card d = players[i].Removes(players);
		if(i<4){
			cout<< "Hint:"<<" Player "<<i<<" passed "<< d << " to player "<<i+1<<endl;
			players[i+1].Move(players,d);}
		else{cout<< "Hint:"<<" Player "<<i<<" passed "<< d << " to player 0"<<endl<<endl;
			players[0].Move(players,d);}
		}
	}
	cout<<endl<<"[ Final card distributions  ]"<<endl;
	for(int i =0, len=players.size();i<len;++i){
		cout<<players[i]<<endl;}
	return 0;
}
