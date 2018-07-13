//============================================================================
// Name        : Moore5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Implementation of Assignment 5, a program which creates
//				 a valid Sudoku board
//============================================================================


#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

class Board{
	vector<vector<char> > m_puzzle;
public:
	Board(){
		vector<char> r1 {'3','7','9','2','4','5','8','6','1'}; m_puzzle.push_back(r1);
		vector<char> r2 {'2','8','5','3','6','1','9','7','4'}; m_puzzle.push_back(r2);
		vector<char> r3 {'1','6','4','9','7','8','2','3','5'}; m_puzzle.push_back(r3);
		vector<char> r4 {'9','5','8','6','3','4','1','2','7'}; m_puzzle.push_back(r4);
		vector<char> r5 {'4','3','7','1','9','2','6','5','8'}; m_puzzle.push_back(r5);
		vector<char> r6 {'6','2','1','8','5','7','4','9','3'}; m_puzzle.push_back(r6);
		vector<char> r7 {'7','9','2','4','1','3','5','8','6'}; m_puzzle.push_back(r7);
		vector<char> r8 {'8','4','3','5','2','6','7','1','9'}; m_puzzle.push_back(r8);
		vector<char> r9 {'5','1','6','7','8','9','3','4','2'}; m_puzzle.push_back(r9);
	}

	friend ostream& operator<< (ostream& o, const Board& b){
		cout << "   ";
		for (int col = 0; col <9; ++col) o << setw(3) << char('A'+col);
		o << endl;
		for ( int row=0; row < 9; ++row){
			o << setw(3)<<char('P'+ row);
			for ( int col=0; col < 9; ++ col)
				o << setw(3)<< b.m_puzzle[row][col];
				o<< endl;
		}
		return o;
	}

bool check_row(){
	char r_duplicates[9];
	vector <int> non_value(9,0);
	int count;
	bool check_r = true;
//Check for non valid values in rows
	for(int row = 0; row<9; ++row){
		for(int col = 0; col<9; ++col){
			if ((m_puzzle[row][col] <= '0') || (m_puzzle[row][col] > '9')){
				++non_value[row];
				check_r=false;
			}
		}
	}
	for(int x=0; x<9; ++x){
		if(non_value[x]!=0)
		cout << "Found inconsistency in row "<< char ('P'+ x)<<"..."<<endl;
	}
//Check for duplicates in rows
	for(int row = 0; row<9; ++row){
		for(int col = 0; col<9; ++col)
			r_duplicates[col]=m_puzzle[row][col];
				for(int x=0; x<9; ++x){
				count=x;
				if(r_duplicates[x]==r_duplicates[++count]){
					cout<<"Found inconsistency in row "<< char ('P' + row)<<"..."<<endl;
				check_r=false;
			}
		}
	}
	if(check_r==false){return false;}
	return true;
}

bool check_column(){
	char c_duplicates[9];
	vector <int> c_non_value(9,0);
	int c_count;
	bool check_c;
//Check for non valid values in columns
	for(int row = 0; row < 9; ++row){
		for(int col = 0; col < 9; ++col){
			if ((m_puzzle[row][col] <= '0') || (m_puzzle[row][col] > '9')){
				++c_non_value[col];
				check_c= false;
			}
		}
	}
	for(int x=0; x<9; ++x){
		if(c_non_value[x]!=0)
		cout << "Found inconsistency in column "<< char ('A'+ x)<<"..."<<endl;
	}
//Check for duplicates in columns
	for(int j = 0; j < 9; ++j){
		for(int i = 0; i<9; ++i){
			c_duplicates[i]=m_puzzle[i][j];
		}
		for (int x=0; x<9; ++x){
			c_count=x;
	 		if(c_duplicates[x]==c_duplicates[++c_count]){
	 			cout<<"Found inconsistency in column "<< char ('A' + j)<<endl;
	 			check_c=false;
			}
		}
	}
	if(check_c==false){return false;}
	return true;
}

bool check_comp(){
	char comp_duplicates[9];
	int compcount;
	bool check_cmp;
//Check for non valid values in components
	for(int a=0; a<=6; a+=3){
		for (int b=0; b<=6; b+=3){
			for (int i =0; i< 3; ++i){
				for (int j = 0; j < 3; ++j){
					if ((m_puzzle[a+i][b+j] <= '0') || (m_puzzle[a+i][b+j] > '9')){
						cout<< "Found inconsistency in component starting at row " <<char ('P'+ (a))<< " and column "<<char ('A'+(b))<<"..."<<endl;
						check_cmp= false;
					}
				}
			}
		}
	}
//Check for duplicate values in components
	for(int a=0; a<=6; a+=3){
		for(int b=0; b<=6; b+=3){
			for(int i, count=0; i<3; ++i){
				for(int j=0; j<3; ++j){
					comp_duplicates[++count]= m_puzzle[a+i][b+j];
				}
			}
			for (int x=0; x<9; ++x){
				compcount=x;
				if(comp_duplicates[x]==comp_duplicates[++compcount]){
					cout<< "Found inconsistency in component starting at row " <<char ('P'+ x)<< " and column "<<char ('A'+x)<<"..."<<endl;
					check_cmp= false;
			 	}
			}
		}
	}
	if(check_cmp==false){return false;}
	return true;
}

bool Allowed(const int& a, const int& b){
//Testing whether swap meets the Sudoku rules
	if((a==0)||(a==3)||(a==6)){
		if((b==a+1)||(b==a+2)){
			return true;
		}
	}
	if((a==1)||(a==4)||(a==7)){
			if((b==a-1)||(b==a+1)){
				return true;
			}
		}
	if((a==2)||(a==5)||(a==8)){
			if((b==a-1)||(b==a-2)){
				return true;
			}
		}
return false;
}

bool Swap_row(){ //Swapping rows
	vector<char>temp(9);
	int a,b;
	do{
	a = rand()%9;
	b = rand()%9;}
	while(a==b);
	cout<<"Trying to swap rows "<<char ('P'+ a)<<" and " <<char ('P'+ b)<<"..."<<endl;
	if (!Allowed(a,b)){
		if((a < 3) && (b < 6 )){
			for(int a=0; a<3; ++a){
			cout<< "- Rows "<< char ('P'+ a) << " and " << char ('P'+ (a+3)) << " were swapped..."<<endl;
				for(int j=0; j<9; ++j){
					temp[j]=m_puzzle[a][j];
					m_puzzle[a][j]=m_puzzle[(a+3)][j];
					m_puzzle[(a+3)][j]=temp[j];
				}
			}
		}
		if((a < 3) && (b >= 6 )){
			for(int a=0; a<3; ++a){
				cout<< "- Rows "<< char ('P'+ a) << " and " << char ('P'+ (a+6)) << " were swapped..."<<endl;
				for(int j=0; j<9; ++j){
					temp[j]=m_puzzle[a][j];
					m_puzzle[a][j]=m_puzzle[(a+6)][j];
					m_puzzle[(a+6)][j]=temp[j];
				}
			}
		}
		if(((a < 6) && (a>2)) && (b < 3 )){
			for(int a=3; a<6; ++a){
				cout<< "- Rows "<< char ('P'+ a) << " and " << char ('P'+ (a-3)) << " were swapped..."<<endl;
				for(int j=0; j<9; ++j){
					temp[j]=m_puzzle[a][j];
					m_puzzle[a][j]=m_puzzle[(a-3)][j];
					m_puzzle[(a-3)][j]=temp[j];
				}
			}
		}
		if(((a < 6) && (a >2)) && (b >= 6 )){
			for(int a=3; a<6; ++a){
				cout<< "- Rows "<< char ('P'+ a) << " and " << char ('P'+ (a+3)) << " were swapped..."<<endl;
				for(int j=0; j<9; ++j){
					temp[j]=m_puzzle[a][j];
					m_puzzle[a][j]=m_puzzle[(a+3)][j];
					m_puzzle[(a+3)][j]=temp[j];
				}
			}
		}
		if(((a >= 6) && ((b < 6)) && (b > 2 ))){
			for(int a=6; a<9; ++a){
				cout<< "- Rows "<< char ('P'+ a) << " and " << char ('P'+ (a-3)) << " were swapped..."<<endl;
				for(int j=0; j<9; ++j){
					temp[j]=m_puzzle[a][j];
					m_puzzle[a][j]=m_puzzle[(a-3)][j];
					m_puzzle[(a-3)][j]= temp[j];
				}
			}
		}
		if((a >= 6) && (b < 3 )){
			for(int a=6; a<9; ++a){
				cout<< "- Rows "<< char ('P'+ a) << " and " << char ('P'+ (a-6)) << " were swapped..."<<endl;
				for(int j=0; j<9; ++j){
					temp[j]=m_puzzle[a][j];
					m_puzzle[a][j]=m_puzzle[(a-6)][j];
					m_puzzle[(a-6)][j]=temp[j];
				}
			}
		}
	}
	else {
		cout<< "- Rows "<< char ('P'+ a) << " and " << char ('P'+ b) << " were swapped..."<<endl;
	for(int i = 0; i<9; ++i){
		temp[i]=m_puzzle[a][i];
		m_puzzle[a][i]=m_puzzle[b][i];
		m_puzzle[b][i]=temp[i];
	}
}
	return true;
}

bool Swap_col(){//Swapping columns
	int a,b;
	do{
	a = rand()%9;
	b = rand()%9;}
	while(a==b);
	vector<char>temp (9);

	cout<<"Trying to swap columns "<<char ('A'+ a)<<" and " <<char ('A'+ b)<<"..."<<endl;
	if (!Allowed(a,b)){
		if((a < 3) && (b < 6 )){
			for(int a=0; a<3; ++a){
				cout<< "- Columns "<< char ('A'+ a) << " and " << char ('A'+ (a+3)) << " were swapped..."<<endl;
					for(int j=0; j<9; ++j){
						temp[j]=m_puzzle[j][a];
						m_puzzle[j][a]=m_puzzle[j][(a+3)];
						m_puzzle[j][(a+3)]=temp[j];
					}
			}
		}
		if((a < 3) && (b >= 6 )){
			for(int a=0; a<3; ++a){
			cout<< "- Columns "<< char ('A'+ a) << " and " << char ('A'+ (a+6)) << " were swapped..."<<endl;
				for(int j=0; j<9; ++j){
					temp[j]=m_puzzle[j][a];
					m_puzzle[j][a]=m_puzzle[j][(a+6)];
					m_puzzle[j][(a+6)]=temp[j];
				}
			}
		}
		if(((a < 6) && (a>2)) && (b < 3 )){
			for(int a=3; a<6; ++a){
			cout<< "- Columns "<< char ('A'+ a) << " and " << char ('A'+ (a-3)) << " were swapped..."<<endl;
				for(int j=0; j<9; ++j){
					temp[j]=m_puzzle[j][a];
					m_puzzle[j][a]=m_puzzle[j][(a-3)];
					m_puzzle[j][(a-3)]=temp[j];
				}
			}
		}
		if(((a < 6) && (a>2)) && (b >= 6 )){
			for(int a=3; a<6; ++a){
			cout<< "- Columns "<< char ('A'+ a) << " and " << char ('A'+ (a+3)) << " were swapped..."<<endl;
				for(int j=0; j<9; ++j){
					temp[j]=m_puzzle[j][a];
					m_puzzle[j][a]=m_puzzle[j][(a+3)];
					m_puzzle[j][(a+3)]=temp[j];
				}
			}
		}
		if(((a >= 6) && ((b < 6)) && (b > 2 ))){
			for(int a=6; a<9; ++a){
			cout<< "- Columns "<< char ('A'+ a) << " and " << char ('A'+ (a-3)) << " were swapped..."<<endl;
				for(int j=0; j<9; ++j){
					temp[j]=m_puzzle[j][a];
					m_puzzle[j][a]=m_puzzle[j][(a-3)];
					m_puzzle[j][(a-3)]= temp[j];
				}
			}
		}
		if((a >= 6) && (b < 3 )){
			for(int a=6; a<9; ++a){
			cout<< "- Columns "<< char ('A'+ a) << " and " << char ('A'+ (a-6)) << " were swapped..."<<endl;
				for(int j=0; j<9; ++j){
					temp[j]=m_puzzle[j][a];
					m_puzzle[j][a]=m_puzzle[j][(a-6)];
					m_puzzle[j][(a-6)]=temp[j];
				}
			}
		}
	}
	else {
		cout<< "- Columns "<< char ('A'+ a) << " and " << char ('A'+ b) << " were swapped..."<<endl;
	for(int i = 0; i<9; ++i){
		temp[i]=m_puzzle[i][a];
		m_puzzle[i][a]=m_puzzle[i][b];
		m_puzzle[i][b]=temp[i];
	}
	}
	return true;
}

void Erase(){//Erasing numbers to create a Sudoku game
	int blank = '-';
	while(true){
		int a = rand()%8;
		int b = rand()%8;
		if(m_puzzle[a][b]!= blank){
			cout<<"Erasing row "<<char ('P'+a)<< " column "<<char('A'+b)<<endl;
			m_puzzle[a][b] = blank;break;}
		}
}
};

int main() {
	srand(time(0));
	cout <<"Welcome Sudoku Initializer !" << endl;
	Board b;
	cout << b;
	while(true){
		cout<< ">";
		string input;
		cin >> input;
		if ((input!= "quit")&&(input!="show")&&(input!="verify")&&(input!="swap")&&(input!="erase"))
			{cout<< "Error: please enter a valid command"<<endl;}
		if (input=="quit") {cout<<"Bye..."<<endl; break;}
		if (input=="show"){cout<< b;}
		if (input=="verify") {bool check_r = b.check_row();
							  bool check_c = b.check_column();
						      bool check_cp= b.check_comp();
						      if(check_r && check_c && check_cp == true){cout<<"- All columns, rows, and components are OK..."<<endl;
						      }}
		if (input=="swap"){
			int selector = rand()%2;
				if(selector==0)
					b.Swap_row();
			else b.Swap_col();
		}
		if (input=="erase"){b.Erase();}
	}
	return 0;
}
