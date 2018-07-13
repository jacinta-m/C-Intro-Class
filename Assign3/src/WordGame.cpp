//============================================================================
// Name        : Moore3.cpp
// Author      : Jacinta Moore
// Version     :
// Copyright   : Your copyright notice
// Description : Implementation of Assignment 3: An Animal Quiz, where animal
//				names are scrambled and the user has to guess them
//============================================================================

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <algorithm>
#include <ctime>
#include <string>

using namespace std;


vector<string> tokens(string l){
	vector <string> vw;
	string word;
	bool found = false;
	for (int i =0, len=l.length(); i <len; ++i){
		if (!isspace(l[i])){
			word +=l[i];
			found = true;
			continue;
		}
		if (!found)continue;
			vw.push_back(word);
			word = "";
			found = false;
	}
	if (found) vw.push_back(word);
	return vw;
}

int main() {

	vector<string>animals;
	vector<string>temp_animals;
	string line;
	vector<string>input;
	string answerline;
	int count = 0;
	int misses = 0;
	int success = 0;

	cout<< "Enter at least five animal names, e.g., cat, dog, etc..."<<endl;

	while (true){
		cout<< " > ";
		getline(cin,line);
		if(line==""){
			if (animals.size()<5){
				cout<<"Please enter at least 5 animals"<<endl;
			}
			else {
				break;
			}
			}

		vector<string> vs = tokens(line);
		int len = vs.size();
		for(int i=0; i<len; i++){
			animals.push_back(vs[i]);
		}
	}

	for(int i=0, len = animals.size(); i<len; i++){
		temp_animals.push_back(animals[i]);
		cout<<i+1<<" : "<<animals[i]<<endl;
	}

	while(true){
		srand((unsigned int)time(0));
		int times = rand()%3;
		string question;
		vector<string> selectWords;

		random_shuffle(temp_animals.begin(),temp_animals.end());
		for(int i=0; i<=times; ++i){
			selectWords.push_back(temp_animals[i]);
			question += selectWords[i];
		}

		for(int i=0; i<count; ++i){
			question[i]='_';
		}
		random_shuffle(question.begin(),question.end());

		while(true){
			random_shuffle(question.begin(),question.end());
			int num = selectWords.size();
			cout<< "What are " << num <<" animal"<< (num == 1 ? "" :"s")<< " in "<<question<<" ? ";

		while(true){
			input.clear();
			getline(cin,answerline);
			if(answerline=="quit"){
				break;
			}
			else if (answerline=="?"){
				for(int i=0, len=animals.size(); i<len;++i){
					cout << i+1<< ": "<<animals[i]<<endl;
				}
				break;
					}
			else {
				if (answerline=="") break;
					vector<string> avs = tokens(answerline);
					int anslen = avs.size();
					for(int i=0; i<anslen; i++){
						input.push_back(avs[i]);
					}
					if(input.size()<selectWords.size()||input.size()>selectWords.size()){
						cout<<"Your number of input is incorrect.Enter again :";
					}
					else {break;}
				}
					}
		break;
		}
		if(answerline=="quit"){cout<<"Bye..."<<endl;break;}

		sort(selectWords.begin(),selectWords.end());
		sort(input.begin(),input.end());

		int unsigned check = 0;
		for(int i=0, len=selectWords.size(); i<len;++i){
			if(selectWords ==input){
					++check;
			}
		}
		if(check== selectWords.size()){
			++success;
			misses=0;
			cout<<"Yes!"<<endl;
			if(success%2==0){
				++count;
				cout<<"Succeeded two consecutive times, challenge goes up"<<endl;
			}
		}
		else {cout<<"Nope!"<<endl;
			++misses;
			success=0;
			if(misses%2==0){
				--count;
				cout<<"Missed two consecutive times, challenge goes down"<<endl;
			}
		}
		if (count<0){count=0;}
		cout<<endl;
	}
	return 0;
}


